#include <iostream>
#include <string>
using namespace std;
class EZMqttClient
{
private:
    // Host
    char host[16];
    // Mqtt Server Port
    int port = 1883;
    // Mqtt ClientID
    char clientId[64];
    // Mqtt username
    char username[64];
    // Mqtt password
    char password[64];
    // Mqtt Topic
    string topic[3] = {"${s2c}", "${c2s}", "${status}"};

public:
    EZMqttClient(/* args */);
    ~EZMqttClient();
    // Init Config
    void init(char host[16], int port, char clientId[64], char username[64], char password[64], string topic[3])
    {
    }
};