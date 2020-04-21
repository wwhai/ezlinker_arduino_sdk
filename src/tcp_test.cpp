// #include <Arduino.h>
// #include <AsyncTCP.h>

// AsyncClient client;
// constexpr IPAddress serverIP(192, 168, 1, 10);
// constexpr uint16_t serverPort = 8888;

// void onConnect(void* arg, AsyncClient* c) {
//   Serial.print("We're connected!\n");
//   c.write("hello server");
// }

// void onDisconnect(void* arg, AsyncClient* c) {
//   Serial.print("We're disconnected!\n");
// }

// void onData(void* arg, AsyncClient* c, void* data, size_t len) {
//   uint8_t* d = reinterpret_cast<uint8_t*>(data);
//   Serial.print("We received some data: 0x");
//   for (size_t i = 0; i < len; ++i) Serial.printf("%02x", d[i]);
//   Serial.print("\n");
// }

// void setup() {
//   Serial.begin(115200);
//  client.onConnect(onConnect);
//   client.onDisconnect(onDisconnect);
//   client.onData(onData);

//   // I've left out the WiFi connecting stuff.
//   // Obviously, you can only call connect when WiFi is up.
//   client.connect(serverIP, serverPort);
// }

// void loop() {
//   delay(1);
// }