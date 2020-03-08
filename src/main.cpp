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
// WIFI SSID
#define WIFI_SSID "206-public"
// WIFI 密码
#define WIFI_PASSWORD "665544332211"
// MQTT Server
#define MQTT_HOST IPAddress(192, 168, 2, 142)
// MQTT 端口
#define MQTT_PORT 1883
// 下行
const char *c2sTopic = "687giyhbU^&YYHOU/c2s";
// 上行
const char *s2cTopic = "687giyhbU^&YYHOU/s2c";
// 状态
const char *stateTopic = "687giyhbU^&YYHOU/state";

AsyncMqttClient asyncMqttClient;
TimerHandle_t mqttReconnectTimer;
TimerHandle_t wifiReconnectTimer;

void connectToWifi()
{
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void connectToMqtt()
{
  Serial.println("Connecting to mqtt server...");
  asyncMqttClient.setClientId("687giyhbU^&YYHOU");
  asyncMqttClient.setCredentials("Y&TOHUBo8yhiol&UJ)", "&UNBkjL63541tgHB");
  asyncMqttClient.connect();
}

void WiFiEvent(WiFiEvent_t event)
{
  // Serial.printf("[WiFi-event] event: %d\n", event);
  switch (event)
  {
  case SYSTEM_EVENT_STA_GOT_IP:
    Serial.println("WiFi connected");
    Serial.print("IP address: ");
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
}
/**
 * 
 * MQtt连接成功以后,订阅s2c,QOS=2
 * 
 */
void onMqttConnect(bool sessionPresent)
{
  Serial.print("Connected to MQTT;Session present:");
  Serial.println(sessionPresent);
  asyncMqttClient.subscribe(s2cTopic, 2);
  // asyncMqttClient.publish("test/lol", 0, true, "test 1");
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
  Serial.println("Disconnected from MQTT server.");

  if (WiFi.isConnected())
  {
    xTimerStart(mqttReconnectTimer, 0);
  }
}

// void onMqttSubscribe(uint16_t packetId, uint8_t qos)
// {
//   Serial.println("Subscribe acknowledged.");
//   Serial.print("  packetId: ");
//   Serial.println(packetId);
//   Serial.print("  qos: ");
//   Serial.println(qos);
// }

// void onMqttUnsubscribe(uint16_t packetId)
// {
//   Serial.println("Unsubscribe acknowledged.");
//   Serial.print("  packetId: ");
//   Serial.println(packetId);
// }

void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
  Serial.print("Data received:");
  Serial.println(payload);
}

void onMqttPublish(uint16_t packetId)
{
  Serial.println("Publish successfully.");
}

void setup()
{
  Serial.begin(115200);
  Serial.println("EZlinker sdk V0.1");
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  wifiReconnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(connectToWifi));

  WiFi.onEvent(WiFiEvent);

  asyncMqttClient.onConnect(onMqttConnect);
  asyncMqttClient.onDisconnect(onMqttDisconnect);
  // asyncMqttClient.onSubscribe(onMqttSubscribe);
  // asyncMqttClient.onUnsubscribe(onMqttUnsubscribe);
  asyncMqttClient.onMessage(onMqttMessage);
  asyncMqttClient.onPublish(onMqttPublish);
  asyncMqttClient.setServer(MQTT_HOST, MQTT_PORT);

  connectToWifi();
}

void loop()
{
}