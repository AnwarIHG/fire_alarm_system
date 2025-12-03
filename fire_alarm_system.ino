// #include <LiquidCrystal_I2C.h>
// #include <ESP32Servo.h>
#include<espnow.h>

// #include "./Sensor_gas.hpp"
// #include "./Sensor_temp.hpp"
// #include "./Sensor_flame.hpp"

#define LCD_COLS 16
#define LCD_ROWS 2

// LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);  

// Sensor_gas::set_gas_threshold(600);
// Sensor_gas rom1 = Sensor_gas(10);
// Serial.print(rom1.read());
// Sensor_tmep temperatures = Sensor_tmep(11);

// void test_serveo(){
//   // rotates from 0 degrees to 180 degrees
//   for (int pos = 0; pos <= 180; pos += 1) {
//     // in steps of 1 degree
//     servoMotor.write(pos);
//     delay(15); // waits 15ms to reach the position
//   }
//
//   // rotates from 180 degrees to 0 degrees
//   for (int pos = 180; pos >= 0; pos -= 1) {
//     servoMotor.write(pos);
//     delay(15); // waits 15ms to reach the position
//   }
// }

// Sensor_gas test = Sensor_gas(GPIO12,GPIO14);


void setup() {
  // Sensor_gas::set_gas_threshold(600);

  Serial.begin(9600);
  // analogReadResolution(10);
  
  // pinMode(LED_BUILTIN,OUTPUT);

  // initialize LCD
  // lcd.init();
  // turn on LCD backlight                      
  // lcd.backlight();
}

void loop() {

  digitalWrite(LED_BUILTIN,HIGH);
  delay(1000);

  digitalWrite(LED_BUILTIN,LOW);
  delay(1000);

  // set cursor to first column, first row
  // lcd.setCursor(0, 0);
  // print message
  // lcd.print("Hello, World!");
  // delay(1000);
  // clears the display to print new message
  // lcd.clear();
  // set cursor to first column, second row
  // lcd.setCursor(0,1);
  // lcd.print("quark IHG");
  // delay(1000);
  // lcd.clear(); 
}
