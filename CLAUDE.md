# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a **firmware project for the Adafruit QT Py ESP32-C3** microcontroller. It uses the Arduino framework with PlatformIO as the build system. The target is a RISC-V based ESP32-C3 with 160 MHz CPU and built-in WiFi/Bluetooth capabilities.

## Build and Development

### Building

```bash
pio run
```

Builds the firmware for `adafruit_qtpy_esp32c3`. Output binary is at `.pio/build/adafruit_qtpy_esp32c3/firmware.elf`.

### Uploading to Device

```bash
pio run -t upload
```

### Cleaning Build

```bash
pio run -t clean
```

### Environment

- **Toolchain**: riscv32-esp-elf-gcc v8.4.0 (RISC-V 32-bit)
- **C Standard**: gnu99
- **C++ Standard**: gnu++11
- **Optimization**: Size-optimized (-Os)
- **Architecture**: RISC-V with IMC extensions

## IDE and Debugging

### Recommended Setup

- **IDE**: VS Code with the PlatformIO IDE extension
- **Debugging**: Three pre-configured debug sessions in `.vscode/launch.json`
  - "PIO Debug" - Standard debug with upload
  - "PIO Debug (skip Pre-Debug)" - Debug without upload step
  - "PIO Debug (without uploading)" - Debug existing binary

IntelliSense and code navigation are pre-configured for the entire ESP32 IDF toolchain.

## Code Structure

```
src/main.cpp         - Entry point with setup() and loop() functions
include/             - Project header files
lib/                 - Project-specific libraries
test/                - Unit tests (currently empty)
platformio.ini       - Build configuration
```

## Testing

The project is configured for unit testing with PlatformIO's Unity test framework. Add test files to the `test/` directory following [PlatformIO test conventions](https://docs.platformio.org/en/latest/advanced/unit-testing/index.html).

To run tests (once added):

```bash
pio test
```

## Key Libraries Available

The Arduino Core for ESP32 provides:

- **Networking**: WiFi, WiFiClientSecure, AsyncUDP, HTTPClient, DNSServer
- **Communication**: SPI, I2C (Wire), UART, BluetoothSerial, BLE
- **Storage**: EEPROM, SPIFFS, LittleFS, SD, FFat
- **Cryptography**: MbedTLS, OpenSSL
- **Utilities**: Ticker, Preferences, Update, ArduinoOTA

Use `#include <library_name.h>` to include these in your code.

## Dependency Management

Dependencies are managed through PlatformIO's library manager. Add dependencies in `platformio.ini` under the `[env:adafruit_qtpy_esp32c3]` section with:

```ini
lib_deps =
    library-name
    owner/library-name@version
```

## Device Specifications

- **Board**: Adafruit QT Py ESP32-C3
- **CPU**: 160 MHz RISC-V
- **RAM**: 384 KB
- **Flash**: 4 MB
- **Features**: WiFi 802.11 b/g/n, Bluetooth 5.0 LE, USB Type-C CDC
