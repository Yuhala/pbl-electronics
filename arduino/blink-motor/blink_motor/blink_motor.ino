
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
 *
 */

#include <IRremote.h>

int motorPin = 3; // motor pin: PWM
int recvPin = 11; // IR receiver pin

IRrecv irrecv(recvPin);
decode_results results;


void setup() {
  irrecv.enableIRIn(); // Initialize the IR receiver
  pinMode(motorPin,OUTPUT);
  /**
   * Begin serial monitor at 9600 baud rate. The baud rate defines the
   * rate at which information is transferred between devices.
   */
  Serial.begin(9600);
}

void loop() {
  if (irrecv.decode(&results))
  {
    /**
     * Press some buttons on the ir remote control and read the corresponding
     * hexadecimal codes.
     */
    Serial.println(results.value, HEX);

    if (results.value == 0xFF6897)
    {
      /**
       * Button to to turn on motor.
       * Replace the value xxx if the "if test" to the HEX code of the button.
       */
      digitalWrite(motorPin, HIGH);
    }
    if (results.value == 0xFFB04F)
    {
      /**
       * Button to to turn off motor.
       * Replace the value xxx if the "if test" to the HEX code of the button.
       */
      digitalWrite(motorPin, LOW);
    }

    /**
     * Flush old results and receive new signal from ir remote control.
     */
    irrecv.resume();
  }
}
