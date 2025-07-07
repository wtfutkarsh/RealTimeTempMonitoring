#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include "DHT.h"

// LCD setup
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27

// RTC setup
RTC_DS3231 rtc;

// DHT setup
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

// Threshold temperature (°C)
#define TEMP_THRESHOLD 30.0

void setup() {
  lcd.init();
  lcd.backlight();

  dht.begin();

  if (!rtc.begin()) {
    lcd.print("RTC not found!");
    while (1);
  }
}

void loop() {
  // Read time
  DateTime now = rtc.now();

  // Read temperature
  float temp = dht.readTemperature();

  lcd.clear();

  // Display time
  lcd.setCursor(0, 0);
  lcd.print(now.hour());
  lcd.print(":");
  if (now.minute() < 10) lcd.print("0");
  lcd.print(now.minute());
  lcd.print(":");
  if (now.second() < 10) lcd.print("0");
  lcd.print(now.second());

  // Display temperature
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temp);
  lcd.print(" C");

  // Check threshold
  if (temp > TEMP_THRESHOLD) {
    delay(2000); // Show reading before warning
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WARNING:");
    lcd.setCursor(0, 1);
    lcd.print("HIGH TEMP!");
    delay(2000);
  } else {
    delay(1000);
  }
}
