#include <AsyncMqttClient.h>

#include "config.h"
#include "util.cpp"
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

private:
    void connectToWifi()
    {
        Serial.print("Try to connect Wi-Fi:");
        Serial.println(WIFI_SSID);
        sleep(3);
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }

    void onWifiEvent(WiFiEvent_t event)
    {
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
    }
    void connectToMqtt()
    {
        sleep(2);
        // WIFI连接成功以后再连接MQTT
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
    ///////////////////////////////////////////////////////////////////////////////
    void onConnect(bool sessionPresent)
    {
        asyncMqttClient.subscribe(this->topicGroup.s2c.c_str(), 2);
    }
    void onDisconnect(AsyncMqttClientDisconnectReason reason)
    {
        Serial.println("Disconnected from MQTT server.");
        if (WiFi.isConnected())
        {
            this->connectToMqtt();
        }
        else
        {
            this->connectToWifi();
        }
    }
    void onPublish(uint16_t packetId)
    {
    }
    void onMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
    {
        onData(topic, payload);
    }
    // 用户接口
    void (*onData)(char *topic, char *payload);

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
    void init(void (*onData)(char *topic, char *payload))
    {
        Serial.begin(115200);
        this->onData = onData;
        this->connectToWifi();
    }
    ~EZMqttClient();
};