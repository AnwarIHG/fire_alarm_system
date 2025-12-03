#pragma once

#ifndef Sensor_gas_h
#define Sensor_gas_h

#include <cstdint>

#include "wiring_private.h"

/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-gas-sensor
 */

/*

#define DO_PIN 16  // ESP32's pin GPIO16 connected to DO pin of the MQ2 sensor

void setup() {
  // initialize serial communication
  Serial.begin(9600);
  // initialize the ESP32's pin as an input
  pinMode(DO_PIN, INPUT);

  Serial.println("Warming up the MQ2 sensor");
  delay(20000);  // wait for the MQ2 to warm up
}

void loop() {
  int gasState = digitalRead(DO_PIN);

  if (gasState == HIGH)
    Serial.println("The gas is NOT present");
  else
    Serial.println("The gas is present");
}


#define AO_PIN 36  // ESP32's pin GPIO36 connected to AO pin of the MQ2 sensor

void setup() {
  // initialize serial communication
  Serial.begin(9600);

  // set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetAttenuation(ADC_11db);
  Serial.println("Warming up the MQ2 sensor");
  delay(20000);  // wait for the MQ2 to warm up
}

void loop() {
  int gasValue = analogRead(AO_PIN);

  Serial.print("MQ2 sensor AO value: ");
  Serial.println(gasValue);
}

*/



class Sensor_gas{

  private:

  static int m_gas_threshold;

  const uint8_t m_pin_D0;
  const uint8_t m_pin_A0;

  public:

  static void set_gas_threshold(int gas_threshold) {
    m_gas_threshold = gas_threshold;
  };

  inline Sensor_gas(uint8_t pin_D0,uint8_t pin_A0) : m_pin_D0(pin_D0), m_pin_A0(pin_A0) {
    pinMode(m_pin_A0, INPUT);
    pinMode(m_pin_D0, INPUT);
  }

  inline const int read_A0() const { 
    return analogRead(m_pin_A0);
  }

  inline const int read_D0() const { 
    return digitalRead(m_pin_D0);
  }

};

#endif // Sensor_gas_h
