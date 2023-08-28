//
// Created by etara on 2023-08-28.
//
#include "Sensor.hpp"
#include "Adafruit_LIS3DH.h"
class Accelerometer: public Sensor{
private:
    vals[3];
public:
    Adafruit_LIS3DH accel_handle
    sensors_event_t event;
    Accelerometer(): Sensor(){
        Adafruit_LIS3DH accel_handle = Adafruit_LIS3DH();

    };
    void AccelData(uint8_t buffer, Adafruit_LIS3DH a_handle,){
        try {
            a_handle.read();
            vals[0] = a_handle.x;
            vals[1] = a_handle.y;
            vals[2] = a_handle.z;
            addValue(vals);
            printf("Data saved successfully!")
        }
        catch{
            printf("Error in saving data");
        }
    }
};
