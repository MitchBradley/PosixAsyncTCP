#include <AsyncTCP.h>

AsyncServer server(8080);

void setup() {
  Serial.begin(115200);

  server.onClient([](void* arg, AsyncClient* client) {
    (void)arg;

    client->onData([](void* arg, AsyncClient* c, void* data, size_t len) {
      (void)arg;
      (void)data;
      (void)len;

      const char* body = "hello from PosixAsyncTCP\n";
      c->write("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nConnection: close\r\n\r\n");
      c->write(body);
      c->close();
    });
  });

  server.begin();
  Serial.println("Listening on 8080");
}

void loop() {
  delay(1000);
}
