
#include <AsyncMqttClient.h>

#include "config.h"
#include "util.cpp"
#include <WiFi.h>
#include <WiFiType.h>
#include <esp_event.h>
#include <string.h>
// 全局MQTT客户端
AsyncMqttClient asyncMqttClient;

void connectToWifi()
{
  Serial.print("Try to connect Wi-Fi:");
  Serial.println(WIFI_SSID);
  sleep(3);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

void connectToMqtt()
{
  if (WiFi.isConnected())
  {
    Serial.print("Try to connect mqtt server:");
    Serial.println(MQTT_HOST.toString());
    sleep(3);
    asyncMqttClient.setServer(MQTT_HOST, MQTT_PORT);
    asyncMqttClient.setClientId(clientId);
    asyncMqttClient.setCredentials(username, password);
    asyncMqttClient.connect();
  }
}
// 初始化
void init()
{
  connectToWifi();
}
void setup()
{

  Serial.begin(115200);
  Serial.println();
  Serial.println("┌*********************************┐");
  Serial.println("|       EZLINKER ON ESP32         |");
  Serial.println("└*********************************┘");
  sleep(1);

  // 监控WIFI事件
  WiFi.onEvent([](WiFiEvent_t event) {
    switch (event)
    {
    case SYSTEM_EVENT_STA_GOT_IP:
      Serial.print("WiFi connected success IP is :");
      Serial.println(WiFi.localIP());
      sleep(1);
      connectToMqtt();
      break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      connectToWifi();
      break;
    default:
      break;
    }
  });
  // 连接WIFI
  asyncMqttClient.onConnect([](bool sessionPresent) {
    Serial.print("Success to connect mqtt server:");
    Serial.println(MQTT_HOST);
    asyncMqttClient.subscribe(s2cTopic, 2);
  });
  // 离线回调
  asyncMqttClient.onDisconnect([](AsyncMqttClientDisconnectReason reason) {
    Serial.println("Disconnected from mqtt server.");
    // 当WIFI连接成功以后再连接MQTT
    if (WiFi.isConnected())
    {
      connectToMqtt();
    }
    else
    {
      connectToWifi();
    }
  });
  // 消息到达回调
  asyncMqttClient.onMessage([](char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total) {
    Serial.print("Message received:");
    Serial.println(payload);
  });
  // 发送成功回调
  asyncMqttClient.onPublish([](uint16_t packetId) {

  });
  // 上面配置好以后，初始化连接
  init();
}

void loop()
{
}