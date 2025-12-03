#pragma once

#ifndef Sensor_flame_h
#define Sensor_flame_h

#include <cstdint>

#include "wiring_private.h"


class Sensor_flame{
  private:

  uint8_t m_do_pin;
  uint8_t m_a0_pin;

  public:
  Sensor_flame(const uint8_t pin_do_pin,const uint8_t pin_a0_pin)
    : m_do_pin(pin_do_pin), m_a0_pin(pin_a0_pin) {
    pinMode(m_do_pin, INPUT);
  }

  const int read_do() const {
    return digitalRead(m_do_pin);
  }

  const int read_a0() const {
    return analogRead(m_a0_pin);
  }
};

#endif
