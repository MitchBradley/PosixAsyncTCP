# PosixAsyncTCP

PosixAsyncTCP is an AsyncTCP-compatible library for HOST/POSIX targets (Linux/macOS), designed to provide the same callback-driven TCP API shape used by async web stacks.

## Features

- AsyncClient and AsyncServer APIs similar to AsyncTCP/RPAsyncTCP
- Non-blocking socket I/O using POSIX sockets
- Callback model for connect, disconnect, data, ack, timeout, and poll
- Connection state tracking and ACK timeout handling
- Intended for hosted simulation and desktop testing workflows

## Installation

### Arduino IDE (manual)

1. Download this repository as ZIP.
2. Install via Arduino Library Manager -> Add .ZIP Library.

### PlatformIO

Add to your project dependencies:

```ini
lib_deps =
  MitchBradley/PosixAsyncTCP
```

Or use as a local library during development.

## Basic usage

```cpp
#include <AsyncTCP.h>

AsyncServer server(8080);

void setup() {
  server.onClient([](void* arg, AsyncClient* client) {
    (void)arg;
    client->onData([](void* arg, AsyncClient* c, void* data, size_t len) {
      (void)arg;
      (void)data;
      (void)len;
      c->write("ok\n");
      c->close();
    });
  });

  server.begin();
}

void loop() {
  delay(1000);
}
```

## Examples

- [Client](examples/Client/Client.ino)
- [Server](examples/Server/Server.ino)

## API notes

Main header: `src/AsyncTCP.h`

Core classes:

- `AsyncClient`
- `AsyncServer`
- `PosixAsyncTCPManager`

## Compatibility

- Framework: Arduino
- Platform: native/HOST POSIX environments

## License

LGPL-3.0
5. **Signal Handling** — select() interrupted by signals; use non-blocking in callbacks

## Building on Different Systems

### macOS

```bash
brew install cmake
cmake -B build
cmake --build build
```

### Linux (Ubuntu/Debian)

```bash
sudo apt-get install cmake build-essential
cmake -B build
cmake --build build
```

### Windows (WSL2)

```bash
# In WSL2
sudo apt-get install cmake build-essential
cmake -B build
cmake --build build
```

## Debugging

### Enable Verbose Output

Uncomment debug logging in `PosixAsyncTCP.cpp`:

```cpp
// Uncomment for debug output
// #define DEBUG_POSIX_ASYNC 1

#ifdef DEBUG_POSIX_ASYNC
    #define LOG_DEBUG(fmt, ...) printf("[AsyncTCP] " fmt "\n", ##__VA_ARGS__)
#else
    #define LOG_DEBUG(fmt, ...) do {} while(0)
#endif
```

### Common Issues

**Port already in use:**
```bash
lsof -i :<port>  # Find process using port
kill -9 <pid>    # Kill it (if safe)
```

**Address already in use (TIME_WAIT):**
```bash
# Wait ~30 seconds or setsockopt(SO_REUSEADDR) in code
# (Already enabled in implementation)
```

**Client connections fail:**
- Verify server is listening: `netstat -an | grep :<port>`
- Check firewall: `sudo pfctl -s nat` (macOS)
- Enable debug logging to see socket errors

## Contributing

To extend PosixAsyncTCP:

1. Follow the existing callback pattern
2. Add unit tests for new features
3. Update INTEGRATION.md with usage examples
4. Ensure thread safety (use `std::lock_guard` for shared state)
5. Keep API compatible with ESP32 AsyncTCP

## See Also

- [INTEGRATION.md](INTEGRATION.md) — Detailed integration guide
- [PosixAsyncTCP.h](PosixAsyncTCP.h) — Full API documentation
- [FluidNC WebUI](../../WebUI/) — Main integration point
- [POSIX Sockets](https://man7.org/linux/man-pages/man7/socket.7.html) — System reference

## License

Same as FluidNC (GPL v3). See [LICENSE](../../../LICENSE).

---

**Questions?** Check INTEGRATION.md or open an issue on GitHub.
