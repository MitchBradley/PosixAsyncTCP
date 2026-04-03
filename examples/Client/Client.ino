#include <AsyncTCP.h>

AsyncClient client;

void setup() {
  Serial.begin(115200);

  client.onConnect([](void* arg, AsyncClient* c) {
    (void)arg;
    c->write("GET / HTTP/1.0\r\n\r\n");
  });

  client.onData([](void* arg, AsyncClient* c, void* data, size_t len) {
    (void)arg;
    (void)c;
    Serial.write((const uint8_t*)data, len);
  });

  client.onDisconnect([](void* arg, AsyncClient* c) {
    (void)arg;
    (void)c;
    Serial.println("Disconnected");
  });

  client.connect(IPAddress(127, 0, 0, 1), 80);
}

void loop() {
  delay(1000);
}
