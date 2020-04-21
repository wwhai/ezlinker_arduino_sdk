#ifndef __CONFIG_H__
#define __CONFIG_H__
//******************NETWORK-CONFIG*****************
// WIFI SSID
#define WIFI_SSID "OrayBox-1D48"
// WIFI 密码
#define WIFI_PASSWORD "665544332211"
//*****************SERVER-CONFIG*******************
#define MQTT_HOST IPAddress(10, 168, 1, 159)
// MQTT 端口
#define MQTT_PORT 1883
// COAP 服务器
#define COAP_HOST IPAddress(10, 168, 1, 159)
// COAP 端口
#define COAP_PORT 5690
// TCP 服务器
#define TCP_HOST IPAddress(10, 168, 1, 159)
// TCP 端口
#define TCP_PORT 1884
// UDP 服务器
#define UDP_HOST IPAddress(10, 168, 1, 159)
// UDP 端口
#define UDP_PORT 1885

//********************MQTT-ARGS********************
// 平台下发的客户端ID
const char *clientId = "D-FJ-FZ-2020042100001";
// 平台下发的客户端Username
const char *username = "2881ae115e788c5db5a0248ff47b5595";
// 平台下发的客户端Password
const char *password = "2c23e7b6e5e924a139921528b6ec17fa";
// 平台下发的客户端 token
const char *token = "MmMyM2U3YjZlNWU5MjRhMTM5OTIxNTI4YjZlYzE3ZmE=";
// 下行
const char *c2sTopic = "/mqtt/in/687giyhbU^&YYHOU/c2s";
// 上行
const char *s2cTopic = "/mqtt/out/687giyhbU^&YYHOU/s2c";
// 状态
const char *stateTopic = "/mqtt/687giyhbU^&YYHOU/state";
//*******************HTTP-AGRS*********************
// 平台下发的客户端ID
//const char *clientId = "D-FJ-FZ-2020042100001";
// 平台下发的客户端Username
//const char *username = "2881ae115e788c5db5a0248ff47b5595";
// 平台下发的客户端Password
//const char *password = "2c23e7b6e5e924a139921528b6ec17fa";
// 平台下发的客户端 token
//const char *token = "MmMyM2U3YjZlNWU5MjRhMTM5OTIxNTI4YjZlYzE3ZmE=";
//
//*******************COAP-AGRS*********************
// 平台下发的客户端ID
//const char *clientId = "D-FJ-FZ-2020042100001";
// 平台下发的客户端Username
//const char *username = "2881ae115e788c5db5a0248ff47b5595";
// 平台下发的客户端Password
//const char *password = "2c23e7b6e5e924a139921528b6ec17fa";
// 平台下发的客户端 token
//const char *token = "MmMyM2U3YjZlNWU5MjRhMTM5OTIxNTI4YjZlYzE3ZmE=";
//********************TCP-AGRS*********************
// 平台下发的客户端ID
//const char *clientId = "D-FJ-FZ-2020042100001";
// 平台下发的客户端Username
//const char *username = "2881ae115e788c5db5a0248ff47b5595";
// 平台下发的客户端Password
//const char *password = "2c23e7b6e5e924a139921528b6ec17fa";
// 平台下发的客户端 token
//const char *token = "MmMyM2U3YjZlNWU5MjRhMTM5OTIxNTI4YjZlYzE3ZmE=";
//********************UDP-AGRS*********************
// 平台下发的客户端ID
//const char *clientId = "D-FJ-FZ-2020042100001";
// 平台下发的客户端Username
//const char *username = "2881ae115e788c5db5a0248ff47b5595";
// 平台下发的客户端Password
//const char *password = "2c23e7b6e5e924a139921528b6ec17fa";
// 平台下发的客户端 token
//const char *token = "MmMyM2U3YjZlNWU5MjRhMTM5OTIxNTI4YjZlYzE3ZmE=";

#endif