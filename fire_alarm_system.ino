#include <cstdint>

#include <espnow.h>
#include <core_esp8266_features.h>

#include <LiquidCrystal_I2C.h>
#include <elapsedMillis.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define LCD_COLS 16
#define LCD_ROWS 2

#define BAZER    D3
#define FLAME    D4
#define GAS_1    D6
#define GAS_2    D7
#define TEMP     D5

#define MAX_TEMP 55.f

#define THERSH_HOLD 700

#define lcd_show_roms_temps_DELAY 10000

const uint32_t warm_up_time = 60000;

static const char *roms_names[5] = {
  "rome 1",
  "rom 2",
  "rom 3",
  "rom 4",
  "rom 5"
};

static float roms_temp[5] = {0};
static bool danger = false;
static int8_t danger_rom = -1;
static uint8_t dev_cont = 0;

static LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);

OneWire oneWire(TEMP);
DallasTemperature sensors = DallasTemperature(&oneWire);

void lcd_loading(const uint32_t &interval){

  static elapsedMillis time_elapsed;

  while (time_elapsed < interval) {
    lcd.setCursor(4, 0);
    lcd.print("loading");
    lcd.setCursor(6, 1);

    for (int i = 0; i < 3; i++){
      lcd.print(".");
      delay(250);
    }

    lcd.setCursor(6, 1);
    for (int i = 0; i < 3; i++){
      lcd.print(" ");
      delay(250);
    }
    delay(777);
  }
}

void lcd_show_rom_temp(const char *str,const float &temp) {
  lcd.print(str);
  lcd.setCursor(0, 1);
  lcd.print(temp);
  lcd.print("c");
}

void lcd_show_roms_temps(const uint8_t count, float *temps, const char **roms){
  for (uint8_t i = 0; i < count; i++) {
    lcd_show_rom_temp(roms[i],temps[i]);
    delay(lcd_show_roms_temps_DELAY);
    lcd.clear();
  }
}

void setup() {

  // initialize LCD
  lcd.init();

  // turn on LCD backlight                      
  lcd.backlight();

  dev_cont = sensors.getDeviceCount();

  // Serial.begin(115200);
  // sensors.begin(); 
  // pinMode(LED_BUILTIN,OUTPUT);

  pinMode(BAZER, OUTPUT);

  pinMode(GAS_1, INPUT);
  pinMode(GAS_2, INPUT);
}

void loop() {

  lcd.clear();
  lcd_loading(warm_up_time);

  sensors.requestTemperatures();

  for (uint8_t i = 0; i < dev_cont; i++) {
    roms_temp[i] = sensors.getTempCByIndex(i); 
    if ( sensors.getTempCByIndex(i) >= MAX_TEMP) {
      danger = true;
      danger_rom = i;
    }
  }

  if (!digitalRead(FLAME)){
    danger = true;
  }

  if (!digitalRead(GAS_1) || digitalRead(GAS_2) >= THERSH_HOLD) {
    danger = true;
  }

  // lcd.clear();
  // if (!danger && danger_rom != -1)
  //   lcd_show_roms_temps(sizeof(roms_names), roms_temp,roms_names);
  // else
  //   lcd_show_rom_temp(roms_names[danger_rom], roms_temp[danger_rom]);

  if (danger) {
    digitalWrite(BAZER, HIGH);
    delay(125);
    digitalWrite(BAZER, LOW);
    delay(50);
    digitalWrite(BAZER, HIGH);
  } else {
    digitalWrite(BAZER, LOW);
  }

  delay(15);

  danger = false;
  danger_rom = -1;
}
