#include <EEPROM.h>
#include <String.h>
#include <string.h>
typedef struct
{
    // MQTT端口
    int port;
    // 服务器地址
    char host[];
    // MQTT ClientId
    char clientId[];
    // MQTT 用户名
    char username[];
    // MQTT密码
    char password[];
} SystemConfig;

void setup()
{
    Serial.begin(115200);
    Serial.println("EZlinker sdk V0.1");
    SystemConfig cfg;
    // Host
    strcpy(cfg.host, "127.0.0.1");
    // 端口
    cfg.port = 1883;
    // 客户端ID
    strcpy(cfg.clientId, "clientid");
    // MQTT 用户名
    strcpy(cfg.username, "username");
    // MQTT密码
    strcpy(cfg.password, "password");
    // 构建保存到ROM的字符串
    String sc = String();
    sc.concat(String(cfg.port));
    sc.concat(String(cfg.host));
    sc.concat(String(cfg.clientId));
    sc.concat(String(cfg.username));
    sc.concat(String(cfg.password));

    EEPROM.begin(sc.length());
    for (size_t i = 0; i < sc.length(); i++)
    {
        Serial.print("The char[");
        Serial.print(i);
        Serial.print("] is: ");
        Serial.println(sc.charAt(i));
        EEPROM.write(i, sc.charAt(i));
    }
    EEPROM.commit();
    for (size_t i = 0; i < sc.length(); i++)
    {
        Serial.printf("The address[%d]  value is :%c\n", i, EEPROM.read(i));
    }
}

void loop()
{
}