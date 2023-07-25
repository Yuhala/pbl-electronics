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
 *
 */

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#define echoPin 2    // connect echo pin of ultrasonic module to digital pin 2 of arduino
#define triggerPin 3 // connect trigger pin of ultrasonic module to digital pin 3 of arduino
#define buzzer 7     // buzzer to arduino pin 7

/**
 *  Variables
 *
 */
long duration; // variable to store the duration of the sound
int distance;  // variable to store the distance measured

hd44780_I2Cexp lcd; // create the LCD object

void setup()
{
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    // Set buzzer pin as output
    pinMode(buzzer, OUTPUT);

    /**
     * Initialize LCD object
     *
     */

    lcd.begin(16, 2);
    lcd.backlight(); // Turn LCD backlight on
}

void loop()
{
    // Clears the trigPin condition
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    /**
     * The speed of sound is 340 m/s = 0.034 cm/microsecond
     *
     */
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)

    /**
     * Print temperature on the LCD
     *
     */
    lcd.setCursor(0, 1); // try 0,0
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print(" cm");

    /**
     * If obstacle is within 10 cm from the ultrasonic module,
     * turn on buzzer alarm for 200 ms.
     *
     */
    if (distance <= 10)
    {
        tone(buzzer, 1000); // Send 1KHz sound signal ...
        delay(200);         // buzz for 200 ms
        noTone(buzzer);     // Stop sound signal
    }
}
