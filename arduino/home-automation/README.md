## Home automation
Home automation or domotics involves automatic control of home appliances by electronic systems. These automations are the basis of smart homes. Popular home
automation systems comprise Amazon Alexa, Google Home, etc. In this project, we leverage an Arduino MC to build a home automation system that can
switch on and off lights, fans, etc via infra-red remote control and bluetooth, e.g using a mobile phone.

## Identification of components
- Arduino Uno (x1)
- IR receiver (x1)
- IR remote control (x1)
- Bluetooth module (x1)
- Jumper wires: M-M (x); M-F (x)
- 
- Red LED (x1)
- 

## IDE setup
- Download and install the `IRremote` library: `Tools --> Manage libraries --> search for IRremote (by Armin Joachimsmeyer) --> Install`

## Circuit diagram


## Circuit construction (connections)

### Part I: Infrared
- Signal pin `S` of the IR receiver to Arduino pin 11.
- Ground pin `-` of the IR receiver to ground on the breadboard.
- VCC pin of the IR receiver to +5V.
- Red LED to Arduino pin 13 through a 220 ohm resistor. The longer leg of the LED is the `+` terminal, and the shorter one is the `-` terminal.

### Part II: Bluetooth

## Arduino program

## Part I: Infrared
- After building the circuit, open the Arduino program and compile. Make sure there are no compilation errors. A successful compilation prints `Done compiling` in the IDE terminal.
- Connect the Arduino Uno to a laptop USB port using the USB cable.
- Upload the program to the Arduino Uno. Make sure the upload is successful. A successful upload prints the message `Done uploading` in the IDE terminal.
- Each time a button on the IR remote control is pressed, it sends a signal to the IR receiver which in turn sends the code to the Arduino Uno microcontroller. We can observe the hexadecimal code corresponding to a button on the remote control using the `Serial Monitor` of the Arduino IDE. 
- Open the `serial monitor`: `Tools --> Serial Monitor`. 
- Point the remote control towards the IR receiver and press a button: observe that each time a button is pressed, a HEX code is written in the serial monitor. 
- We will use `button 1` to turn on the red LED, and `button 3` to turn if off. So press `1` on the remote control and note its HEX code; do the same for `3` and note its HEX code. Ignore any codes with `FFFFFF`.
- Modify the Arduino code which turns on and off the red LED to test for the codes you noted above. For example, if the code for `button 1` is: `FF6897`, change the code from `if(results.value == 000)` to `if(results.value == 0xFF6897)`.
- Recompile your program and upload to the Arduino again.
- Now when you press `button 1`, the red LED is turned on, and when you press `button 3`, the red LED is turned off.

## Part II: Bluetooth
