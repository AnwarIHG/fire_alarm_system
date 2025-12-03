#pragma once

#ifndef Sensor_temp_h
#define SenSor_temp_h

#include <cstdint> 
#include <cmath>

#include <OneWire.h>
#include <DallasTemperature.h>

#include "HardwareSerial.h"


class Sensor_tmep {
  private:
    OneWire m_oneWire;
    DallasTemperature m_sensors;
    DeviceAddress m_temp_device_address;
    int numberOfDevices;

  public:

    Sensor_tmep(uint8_t pin) : m_oneWire(pin), m_sensors(&m_oneWire) {
      m_sensors.begin();
      numberOfDevices = m_sensors.getDeviceCount();
    }

    inline void read() const {
      m_sensors.requestTemperatures();
    }

    inline const float getCelsius(const uint8_t index) {
      if (index > numberOfDevices) return NAN;

      if (m_sensors.getAddress(m_temp_device_address, index)){
        return m_sensors.getTempC(m_temp_device_address);
      }
    }

    inline const float getFahrenheit(const uint8_t index) {
      if (index > numberOfDevices) return NAN;
      float c = getCelsius(index);
      return c * 1.8f + 32.0f;
    }

    inline void printAddress(DeviceAddress deviceAddress) {
      for (uint8_t i = 0; i < 8; i++) {
        if (deviceAddress[i] < 16) Serial.print("0");
        Serial.print(deviceAddress[i], HEX);
      }
    }

    inline void debug_info(){

      // locate devices on the bus
      Serial.print("Locating devices...");
      Serial.print("Found ");
      Serial.print(numberOfDevices, DEC);
      Serial.println(" devices.");

      // Loop through each device, print out address
      for(int i=0;i<numberOfDevices; i++) {
        // Search the wire for address
        if(m_sensors.getAddress(m_temp_device_address, i)) {
          Serial.print("Found device ");
          Serial.print(i, DEC);
          Serial.print(" with address: ");
          printAddress(m_temp_device_address);
          Serial.println();
        } else {
          Serial.print("Found ghost device at ");
          Serial.print(i, DEC);
          Serial.print(" but could not detect address. Check power and cabling");
        }
      }
    }
};

#endif // SenSor_temp_h
