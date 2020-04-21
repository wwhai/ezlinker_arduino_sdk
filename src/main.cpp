/*
This example uses FreeRTOS softwaretimers as there is no built-in Ticker library
*/
extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#include <AsyncMqttClient.h>

#include <WiFi.h>
#include <WiFiType.h>
#include <esp_event.h>
#include <string.h>
#include <ArduinoLog.h>
#include "config.h"
#include "util.cpp"
// 全局MQTT客户端
AsyncMqttClient asyncMqttClient;
// MQTT重新连接定时器
TimerHandle_t mqttReconnectTimer;
// WIFI重新连接定时器
TimerHandle_t wifiReconnectTimer;

void connectToWifi()
{
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void connectToMqtt()
{
  Serial.println("Connecting to mqtt server...");
  asyncMqttClient.setServer(MQTT_HOST, MQTT_PORT);
  asyncMqttClient.setClientId(clientId);
  asyncMqttClient.setCredentials(username, password);
  asyncMqttClient.connect();
}

void setup()
{

  Serial.begin(115200);
  Serial.println("Mqtt client started on esp32-dev");
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));
  // 监控WIFI事件
  WiFi.onEvent([](WiFiEvent_t event) {
    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.print("WiFi connected IP address is :");
      Serial.println(WiFi.localIP());
      connectToMqtt();
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      // 当WIFI链接失败的时候,需要停止MQTT的连接定时器
      xTimerStop(mqttReconnectTimer, 0);
      xTimerStart(wifiReconnectTimer, 0);
      break;
    default:
      break;
    }
  });
  // 连接WIFI
  connectToWifi();
  // 连接成功回调
  asyncMqttClient.onConnect([](bool sessionPresent) {
    Serial.println("Connected to MQTT;Session present is:");
    Serial.print(sessionPresent);

    asyncMqttClient.subscribe(s2cTopic, 2);
  });
  // 离线回调
  asyncMqttClient.onDisconnect([](AsyncMqttClientDisconnectReason reason) {
    Serial.println("Disconnected from MQTT server.");
    // 当WIFI连接成功以后再连接MQTT
    if (WiFi.isConnected())
    {
      xTimerStart(mqttReconnectTimer, 0);
    }
  });
  // 消息到达回调
  asyncMqttClient.onMessage([](char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
    Serial.println("Message received:");
    Serial.print(payload);
  });
  // 发送成功回调
  asyncMqttClient.onPublish([](uint16_t packetId) {

  });
}

void loop()
{
}