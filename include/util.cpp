#include <EEPROM.h>
// 系统配置用的结构体
#ifndef _UTIL_H_
#define _UTIL_H_

typedef struct
{
    // MQTT端口
    int port = 1883;
    // 服务器地址
    char host[16];
    // MQTT ClientId
    char clientId[64];
    // MQTT 用户名
    char username[64];
    // MQTT密码
    char password[64];
} SystemConfig;
void saveConfig()
{
}
#endif