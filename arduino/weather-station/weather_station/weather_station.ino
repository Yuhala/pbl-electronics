/*
 *
 *  Created on Tue Nov 01 2022
 *
 *  The MIT License (MIT)
 *  Copyright (c) 2022 Peterson Yuhala
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 *  and associated documentation files (the "Software"), to deal in the Software without restriction,
 *  including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 *  subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all copies or substantial
 *  portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 *  TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 *  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 *  The circuit:
 *
 *
 */

#include "DHT.h"
#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

/**
 * This pin is connected to pin 2 of the DHT22 module.
 */
#define DHTPIN 13

#define DHTTYPE DHT22 // DHT 22 (AM2302) module

#define buzzer 7 // buzzer to arduino pin 7

// Create DHT sensor object: program entity which represents the DHT22 module
DHT dht(DHTPIN, DHTTYPE);

hd44780_I2Cexp lcd;

void setup()
{
  lcd.begin(16, 2);
  lcd.backlight(); // Turn LCD backlight on

  // Initialize serial monitor
  // Serial.begin(9600);
  // Serial.println("DHT 22 test >>>>>>");
  // Initialize DHT sensor for 16mhz Arduino
  dht.begin();
  // Set buzzer pin as output
  pinMode(buzzer, OUTPUT);
}

void loop()
{

  // Wait 2 seconds between measurements
  delay(2000);

  // Read temperature
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  // Verify for correct results
  if (isnan(h) || isnan(t))
  {
    Serial.println("Failed to read data from DHT sensor >>>>");
    return;
  }

  lcd.setCursor(0, 1); // try 0,0
  /**
   * Print temperature on the LCD
   *
   */
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print("*C");
  lcd.setCursor(1, 0); // try 0, 1
  /**
   * Print the humidity on the LCD
   *
   */
  lcd.print("Humid: ");
  lcd.print(h);
  lcd.print("%");

  /**
   * Print temperature and humidity on serial monitor
   *
   */
  // Serial.print("Humidity: ");
  // Serial.print(h);
  // Serial.println(" %");

  // Serial.print("Temperature: ");
  // Serial.print(t);
  // Serial.print(" *C ");

  /**
   * Turn off buzzer alarm if temperature > 25*C
   * PYuhala: this is just a test, try changing the threshold.
   *
   */
  if (t > 25)
  {
    tone(buzzer, 1000); // Send 1KHz sound signal ...
    delay(200);         // buzz for 200 ms
    noTone(buzzer);     // Stop sound signal
  }
}
