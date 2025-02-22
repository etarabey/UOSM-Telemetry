//
// Created by Jeremy Cote on 2023-08-27.
//
#include "../Inc/UOSMCoreConfig.h"

#ifdef ESP32
#include <Arduino.h>
#include <SPI.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

static char messageBuf[MAX_SERIAL_PRINT_LENGTH];

void GPIO_DigitalWrite(uint8_t pin, uint8_t val) {
#ifdef ESP32
    digitalWrite(pin, val);
#endif
}

void SPI_Transfer(void *data, uint32_t size) {
#ifdef ESP32
    SPI.transfer(data, size);
#endif
}

void ExternalSerialPrint(const char * message, ...) {
#ifdef ESP32
    va_list args;
    va_start(args, message);
    Serial.printf(message, args);
    va_end(args);
#endif
}
void ExternalSerialPrintln(const char * message, ...) {
#ifdef ESP32
    va_list args;
    va_start(args, message);
    uint16_t len = vsprintf(messageBuf, message, args);
    messageBuf[len] = '\n';
    messageBuf[len+1] = '\r';
    Serial.printf(messageBuf, args);
    va_end(args);
#endif
}

#ifdef __cplusplus
}
#endif