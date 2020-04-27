#include <iostream>
#include <string>
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
using namespace std;

typedef struct TopicGroup
{
    string s2c;
    string c2s;
    string status;
};

class EZMqttClient
{
private:
    //WIFI
    string ssid;
    string wifiPassword;
    // Host
    IPAddress host;
    // Mqtt Server Port
    int port = 1883;
    // Mqtt ClientID
    string clientId;
    // Mqtt username
    string username;
    // Mqtt password
    string password;
    // Mqtt Topic {"${s2c}", "${c2s}", "${status}"}
    TopicGroup topicGroup;
    // 全局MQTT客户端
    AsyncMqttClient asyncMqttClient;
    // MQTT重新连接定时器
    TimerHandle_t mqttConnectTimer;
    // WIFI重新连接定时器
    TimerHandle_t wifiConnectTimer;

private:
    void (*onMessage)(char *topic,
                      char *payload,
                      AsyncMqttClientMessageProperties properties,
                      size_t len,
                      size_t index,
                      size_t total);

    void connectToWifi()
    {
        Serial.println("Connecting to Wi-Fi...");
        WiFi.onEvent(this->onWifiEvent);
        WiFi.begin(this->ssid.c_str(), this->wifiPassword.c_str());
    }

    void onWifiEvent(WiFiEvent_t event)
    {
        switch (event)
        {
        case SYSTEM_EVENT_STA_GOT_IP:
            Serial.print("WiFi connected IP address is :");
            Serial.println(WiFi.localIP());
            xTimerStop(this->wifiConnectTimer, 0);
            xTimerStart(this->mqttConnectTimer, 0);
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("WiFi lost connection");
            // 当WIFI链接失败的时候,需要停止MQTT的连接定时器
            xTimerStop(this->mqttConnectTimer, 0);
            // 然后开启重新连接WIFI的定时器
            xTimerStart(this->wifiConnectTimer, 0);
            break;
        default:
            break;
        }
    }
    void connectToMqtt()
    {
        // WIFI连接成功以后再连接MQTT
        if (WiFi.isConnected())
        {
            Serial.println("Connecting to mqtt server...");
            asyncMqttClient.setServer(this->host, this->port);
            asyncMqttClient.setClientId(this->clientId.c_str());
            asyncMqttClient.setCredentials(this->username.c_str(), this->password.c_str());
            asyncMqttClient.onConnect = this->onConnect;
            asyncMqttClient.onMessage = this->onMessage;
            asyncMqttClient.onDisconnect = this->onDisconnect;
            asyncMqttClient.connect();
        }
    }
    ///////////////////////////////////////////////////////////////////////////////
    void onConnect(bool sessionPresent)
    {
        asyncMqttClient.subscribe(this->topicGroup.s2c.c_str(), 2);
        xTimerStop(this->mqttConnectTimer, 0);
        xTimerStop(this->wifiConnectTimer, 0);
    }
    void onDisconnect(AsyncMqttClientDisconnectReason reason)
    {
        Serial.println("Disconnected from MQTT server.");
        // 当WIFI连接成功以后再连接MQTT
        if (WiFi.isConnected())
        {
            xTimerStart(mqttConnectTimer, 0);
        }
        else
        {
            xTimerStart(this->wifiConnectTimer, 0);
        }
    }
    void onPublish(uint16_t packetId)
    {
    }
    ///////////////////////////////////////////////////////////////////////////////

public:
    EZMqttClient();
    EZMqttClient(string ssid,
                 string wifiPassword,
                 IPAddress host,
                 int port,
                 string clientId,
                 string username,
                 string password,
                 TopicGroup topicGroup)
    {
        this->ssid = ssid;
        this->wifiPassword = ssid;
        this->host = host;
        this->port = port;
        this->clientId = clientId;
        this->username = username;
        this->password = password;
        this->topicGroup = topicGroup;
    }
    // 初始化
    void init(void(*onNessage))
    {
        Serial.begin(115200);
        this->onMessage = onMessage;
        mqttConnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(this->connectToMqtt));
        wifiConnectTimer = xTimerCreate("wifiTimer", pdMS_TO_TICKS(2000), pdFALSE, (void *)0, reinterpret_cast<TimerCallbackFunction_t>(this->connectToWifi));
        xTimerStart(wifiConnectTimer, 0);
    }
    ~EZMqttClient();
};