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

#include <IRremote.h>
#include <SoftwareSerial.h>

const byte rxPin = 9;                  // bluetooth receiver pin
const byte txPin = 8;                  // bluetooth transmission pin
SoftwareSerial BTSerial(rxPin, txPin); // Create bluetooth object

int recvPin = 11; // IR receiver pin

int redLed = 13; // Red LED pin

IRrecv irrecv(recvPin);
decode_results results;

/**
 * Contains all bluetooth related code.
 * Connect bluetooth module to device and
 * read messages sent.
 */
void runBluetooth();

/**
 * Contains infrared related code.
 *
 */
void runInfrared();

void setup()
{
  irrecv.enableIRIn(); // Initialize the IR receiver
  pinMode(redLed, OUTPUT);
  digitalWrite(redLed, LOW);
  pinMode(rxPin, INPUT);  // receiver pin receives bluetooth message, so it is INPUT.
  pinMode(txPin, OUTPUT); // transmission pin sends bluetooth message, so it is OUTPUT.
  BTSerial.begin(9600);   // Initialize the bluetooth software serial object to send and receive at txPin and rxPin;

  /**
   * Begin serial monitor at 9600 baud rate. The baud rate defines the
   * rate at which information is transferred between devices.
   */
  Serial.begin(9600);
}

String messageBuffer = "";
String message = "";

void loop()
{
  //runInfrared();
  runBluetooth();
}

void runBluetooth()
{
  /**
   * Check if there are characters in the serial buffer
   *
   */
  while (BTSerial.available() > 0)
  {
    char data = (char)BTSerial.read(); // read the unit data in the serial object
    messageBuffer += data;              // add the read data to the message buffer
    /**
     * We use semicolons to end a complete bluetooth message
     *
     */
    if (data == ';')
    {
      message = messageBuffer; // read the full bluetooth message
      messageBuffer = "";      // clear the message buffer
      Serial.print(message);   // print received message in serial monitor
    }
  }
}

void runInfrared()
{
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
       * Button to to turn on red LED.
       * Replace the value xxx if the "if test" to the HEX code of the button.
       */
      digitalWrite(redLed, HIGH);
    }
    if (results.value == 0xFFB04F)
    {
      /**
       * Button to to turn off red LED.
       * Replace the value xxx if the "if test" to the HEX code of the button.
       */
      digitalWrite(redLed, LOW);
    }

    /**
     * Flush old results and receive new signal from ir remote control.
     */
    irrecv.resume();
  }
}
