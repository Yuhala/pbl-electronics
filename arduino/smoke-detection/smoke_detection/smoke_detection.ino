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

#define buzzer 7        // buzzer to arduino pin 7
#define redLed 13       // red LED to arduino pin 13 through 220ohm resistor
#define greenLed 12     // green LED to arduino pin 12 through 220ohm resistor
#define gasSensorPin A0 // the analog pin of gas sensor is connected to arduino analog pin A0
  
void setup()
{
    pinMode(buzzer, OUTPUT);     // the buzzer sends a sound as OUTPUT
    pinMode(redLed, OUTPUT);     // the red LED produces an OUTPUT signal i.e light
    pinMode(greenLed, OUTPUT);     // the green LED produces an OUTPUT signal i.e light
    digitalWrite(redLed, LOW);   // the red LED should be off at the start
    digitalWrite(greenLed, LOW); // the green LED is off at the start
    // Serial.begin(115200);        // begin the serial monitor
}
void loop()
{
    /**
     * Read gas concentration from gas sensor
     *
     */
    int gasValue = analogRead(gasSensorPin);

    // Serial.println(gasValue);
    /**
     * If the gas concentration is greater than 400 parts per million,
     * turn on the buzzer, turn off the green LED, and flash the red LED
     *
     */

    if (gasValue >= 85)
    {
        tone(buzzer, 1000); // Send 1KHz sound signal ...
        delay(200);         // buzz for 200 ms
        noTone(buzzer);     // Stop sound signal

        /**
         * Turn of green LED and
         * Flash the red LED (danger, fire!!);
         *
         */
        digitalWrite(greenLed, LOW);
        digitalWrite(redLed, HIGH);
        delay(50);
        digitalWrite(redLed, LOW);
    }
    else
    {
        /**
         * If gas concentration is lower than threshold, turn on the green LED
         *
         */
        digitalWrite(greenLed, HIGH);
    }
}
