#include "VoltageSensor.hpp"
#include "Accelerometer.hpp"
#ifdef ESP32

#include <Arduino.h>
#include "PollingSensorTask.hpp"

#include "ThingProperties.h"
#include "Conversions.h"

#include "SoftwareSerial.h"

// 9 = RX, 10 = TX
SoftwareSerial fonaSerial(9, 10, false, 256);

#if !defined(TINY_GSM_RX_BUFFER)
#define TINY_GSM_RX_BUFFER 650
#endif

#define TINY_GSM_MODEM_SIM808


#include "TinyGSMClient.h"

//#define SerialMon Serial
#define SerialAT fonaSerial

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
 StreamDebugger debugger(SerialAT, SerialMon);
 TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

TinyGsmClient client(modem);

#define DEFAULT_BUFFER_SIZE 10

VoltageSensor* voltageSensor;
Accelerometer* accelSensor;

PollingSensorTask<voltage_t>* voltageSensorTask;
PollingSensorTask<accel_t>* accelSensorTask;

void setup() {
    Serial.begin(115200);
    SerialAT.begin(9600);
    delay(6000);

    Serial.println("Starting init");

    modem.init();

    Serial.println("Initiating GPRS");

    modem.gprsConnect("Fido-core-appl1.apn");

    Serial.println("Connected!");
    Serial.printf("Minimal stack size %d\n", configMINIMAL_STACK_SIZE);
    voltageSensor = new VoltageSensor(DEFAULT_BUFFER_SIZE);
    accelSensor = new Accelerometer(DEFAULT_BUFFER_SIZE);
    voltageSensor->addListener([](const voltage_t& newValue) {
        updateBatteryVoltage(convertVoltageToFloat(newValue));
    });

        accelSensor->addListener([](const accel_t& newValue){
            updateAcceleration(newValue);
        });

    // })
    // TODO: Note that voltageSensor will throw an exception if collect is not called before get(). See if we can apply RAII

    voltageSensorTask = new PollingSensorTask<voltage_t>(voltageSensor, 200, "T_VoltageSensor", 12800 * 100, 5);
    accelSensorTask = new PollingSensorTask<accel_t>(accelSensor,200,"T_AccelSensor",1280*100,5);

    initProperties();
    ArduinoCloud.begin(ArduinoIoTPreferredConnection);

    Serial.println("Begin Connection");

    setDebugMessageLevel(2);
    ArduinoCloud.printDebugInfo();

}

void loop() {
    ArduinoCloud.update();

}

#else
#ifndef PIO_UNIT_TESTING
int main() {
    printf("Starting");
    VoltageSensor sensor(10);
    Accelerometer sens_accel(10);
    sensor.collect();
    sens_accel.collect(10);
    printf("Get Value %d", sensor.get());
    return 0;
}
#endif
#endif
