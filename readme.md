# Ezlinker-Arduino-sdk
这是一个用PlatformIO构建的项目。PlatformIO安装方法请查看此处文档:https://docs.platformio.org/en/latest/ide/pioide.html
## 1. 下载依赖
```
pio run
```
## 2. 上传固件
```
pio run --target upload
```
## 3. 开发指南
目前支持MQTT协议，后期会加入COAP，HTTP，TCP，UDP等协议的支持，下面是使用方法:
#### 3.1 选择协议
首先需要选择当前设备的协议模式，需要打开config.h进行配置,配置文件如下：
``` c++
#ifndef __CONFIG_H__
#define __CONFIG_H__
//******************NETWORK-CONFIG*****************
// WIFI SSID
#define WIFI_SSID "OrayBox-1D48"
// WIFI 密码
#define WIFI_PASSWORD "665544332211"
//******************SERVER-CONFIG******************
// MQTT Server
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
#define TCP_PORT 5690
// UDP 服务器
#define UDP_HOST IPAddress(10, 168, 1, 159)
// UDP 端口
#define UDP_PORT 5690

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
```
假如说我们目前是MQTT协议，则只需要配置如下即可：
``` c++
#ifndef __CONFIG_H__
#define __CONFIG_H__
//******************NETWORK-CONFIG*****************
// WIFI SSID
#define WIFI_SSID "OrayBox-1D48"
// WIFI 密码
#define WIFI_PASSWORD "665544332211"
//******************MQTT-SERVER********************
// MQTT Server
#define MQTT_HOST IPAddress(10, 168, 1, 159)
// MQTT 端口
#define MQTT_PORT 1883
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
#endif
```
其他协议也是一样的,只需要注释不要的即可。
#### 3.2 网络配置
目前仅支持WIFI，后期会加入GPRS或者是以太网支持。
```c++
// WIFI SSID
#define WIFI_SSID "NetWorrkSSID"
// WIFI 密码
#define WIFI_PASSWORD "665544332211"
```
#### 3.3 服务器配置

```c++
// MQTT Server
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
#define TCP_PORT 5690
// UDP 服务器
#define UDP_HOST IPAddress(10, 168, 1, 159)
// UDP 端口
#define UDP_PORT 5690

```