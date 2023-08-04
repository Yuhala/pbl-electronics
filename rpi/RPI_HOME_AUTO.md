

## Setting up Raspberry Pi on Ubuntu 18: Headless setup (i.e., no monitor, keyboard, mouse)

This Readme provides information on how to set up a raspberry pi board without peripherals. The instructions here are based on my experience while setting up a raspberry pi 3B+ for an Adeept RaspTank Robot, based the first part of these instructions can be used for setting up a raspberry pi board for other purposes.

### Download and flash Raspberry Pi OS image

## Using BalenaEtcher (not good for headless; ssh issues)
- Download `balenaEtcher` tool for ubuntu: [balenaEtcher](https://www.balena.io/etcher/)
- Download a compatible Raspberry Pi OS image for your board: [Raspberry Pi OS Downloads](https://www.raspberrypi.com/software/operating-systems/). The `Lite` versions do not come with an embedded GUI and have less software included (`364MB` vs `2.7GB`). We will use the `Lite` version: `Raspberry Pi OS Lite`. We use `2023-05-03-raspios-bullseye-armhf-lite.img.xz` in this tutorial.
- Connect a microSD card to your PC and use `balenaEtcher` to flash the downloaded OS image to the card. This is pretty straight forward, no need for a long tutorial.
- Leave the microSD card connected to your PC for now.

- After flashing, you should see two partitions in the microSD card: `rootfs` and `bootfs`. 


## Using Raspberry Pi Imager (recommended)
- On Linux: `sudo snap install rpi-imager`. Download and run for windows.
- Use `rpi-imager` to setup ssh username (e.g., pi), pass, and hostname (e.g., `pi-homeauto`).
- Flash the OS on SD card. After flashing insert sd card in pi and power up the pi.




- Raspberry Pi OS will use this information at boot time to automatically configure WiFi access for you Pi.

### Setup your pi board
- Unmount and remove the microSD card from your PC, insert it into your Pi board and power up the board.
- A green led flashing means the Pi has completed booting.


### Getting your Pi IP address.

#### Using arp-scan
- This IMO is the quickest solution to obtain your Pi's IP address but you could use `nmap` too. See next section.
- Install and run `arp-scan`
```
sudo apt install arp-scan
sudo arp-scan --localnet

```
- A sample result of the scan:
![arp-scan](imgs/arp-scan.png)
- The Pi IP here is `130.125.11.172`.



#### Using nmap
- Install `nmap` and `net-tools`.
```
sudo apt install nmap net-tools
```
- Run `ifconfig | grep netmask` in the terminal to obtain your subnet mask IP. 
- Example `ifconfig` results: the output ` inet 130.125.11.148  netmask 255.255.255.0` means the subnet mask IP is `130.125.11.0` and subnet mask `/24`. That is the first 24 bits (8x3) are masked.
- For `netmask 255.255.0.0`, the subnet mask will be `/16`.
- Run `nmap` with your subnet mask to scan your subnet and obtain your Pi's IP address.
```
nmap -sP 130.125.11.0/24

```
- Locate your Pi in the list (mine found the Pi but the name was absent)


### SSH into your Pi
- Run the command `ssh pi@pi-IP-address` or `ssh pi@pi-homeauto`. For example:
```
ssh pi@130.125.11.172
```
- `Are you sure you want to continue connecting (yes/no)?`: enter `yes`.
- `pi@130.125.11.172's password:`: the default Pi password is `raspberry`.
- You should now have a remote connection to your Pi.


### Update your source lists and install some useful packages
- In the ssh terminal of your Pi, enter the following commands:

```
sudo apt update && sudo apt install git -y 
```

### Remote development on your Pi with vscode
- I'm a fan of `vscode` and use it as my main `IDE`. You can configure `vscode` to access folders and files remotely on your Pi. Doing this you can easily write scripts and test on your Pi board remotely.
- See this tutorial for setting up [remote development using SSH in vscode](https://code.visualstudio.com/docs/remote/ssh).
- For development on your Raspberry Pi, the [official documentation]() is a gold mine. Have fun.

### Setting up remote development with vscode.
- We will use `vscode` IDE as our primary IDE. Since we have a headless setup, we will need to access our Pi files remotely. Use vscode ssh to connect to the Pi.


### GPIO control
- RPI 3B+ has 40 GPIO pinsTo identify the GPIO pins, run the `pinout` command inside your Pi's terminal.
- All sensors work on 3.3V logic; so no sensors should be used that work on 5V. No more than 3.3V should be supplied to a GPIO pin.
- Checkout T-cobbler breakout board to connect sensors using a breadboard.

## Basic GPIO programming: turn on/off LED.
- Create a folder: `homeauto` and a python script: `piauto.py` in that directory.
```
mkdir homeauto
touch piauto.py
```
- Open this folder in vscode SSH.
- In your Python script, import the `RPI.GPIO` module used to control GPIO pins.
```
import RPi.GPIO as GPIO
```
- Pin scheme declaration: this defines how the GPIO pins are numbered. There are two modes: `BCM` mode which refers to the pins by the `Broadcom SoC Channel` number; in simple language the pin  numbering is exactly as shown in the output of the `pinout` command (`GPIOxx`). Thee second mode: `BOARD` mode means the pin numbering follows the numbering on the plug -i.e., the numbers printed on the board, e.g,. P1 etc. We will use the `BCM` mode.
```
GPIO.setmode(GPIO.BCM)
```
- Pin mode declaration: This is similar to Arduino pin modes, where each GPIO pin can be either input or output. If you want to control an LED for ex,  set the pin mode to `OUTPUT`. If the pin is to be used as an input pin (e.g., temperature sensor) set it as an `INPUT` pin. We will use pin `GPIO14` (see pinout diagram) as an output pin to control our LED. NB: there is nothing special about GPIO pin 14, you can pick any other GPIO pin. I chose pin 14 b/c it is next to a ground pin (GND) which I will need.

```
GPIO.setup(14,GPIO.IN)
```
- GPIO states: you can make the state of a GPIO output pin high (3.3V) or low (0V). Use `GPIO.output(pin,GPIO.HIGH)` or `GPIO.output(pin,GPIO.LOW)` to set it high or low respectively. 
- To read the status of a GPIO pin, use `digitalRead(pin)`. You can use software pull-up or pull-down functions to ensure a well-defined state on a pin.
- To add delays use `time.sleep(delay-in-seconds)`, e.g., `time.sleep(0.5)`. You can use PCM to dim LEDs.
- For analog input, you will need an `analog to digital converter` (ADC). Some examples of ADC chips: MCP3008, ADS1x15


### Web control interface
- TODO: create button to turn on/off led.
- Add some news or updates to the interface, e.g., weather forcast details and outdoor weather details


## Part 1: creating a simple Flask web-server in the Pi.
- We will use Flask, a web framework developed in Python. 
- Setup python virtual environment in the `homeauto` folder and install Flask. The virtual env allows to isolate the projects dependencies from other system-wide conflicting Python dependencies.
```
sudo apt update && sudo apt upgrade
sudo apt install python3-pip python3-venv
python3 -m venv home-auto-env
source home-auto-env/bin/activate
pip install flask
```
- Setup the Flask app folder: `web-control-panel`. Create subdirectories: `static` and `templates`, and the main application file: `app.py`.
- See code in ??.

```

```
- Run the Flask app with: `flask --app app run -h pi-IP-address`
- The default port for Flask applications is `5000`. To see the web interface, open the web browser on a PC connected on the same network as your Pi and type: `pi-ip-address:5000`. For example, my Pi's IP is `192.168.1.123`, so I enter: `192.168.1.123:5000` in the browser window. You should see the hello message printed in your browser.

### Turn LED on/off with web button
- Create a Flask route: `turn_on_led`.
```
@app.route('/turn-on-led', methods=['POST'])
def turn_on_led():
    GPIO.output(ledPin, GPIO.HIGH)
    return render_template('home.html')
```
- Create a simple web page containing a form with a button. This page will be the home page, i.e., for route `/`. The submit method of the form should call the route `turn_on_led`.
- See ??
- Remember we are working in our virtual environment so `RPi.GPIO` is not yet install. To install it do: 
```
pip install RPi.GPIO
```
- Run you Flask app: `flask --app app run -h rpi-IP-address`
- The LED should turn on/blink when the button is clicked.
- Use the same idea to create a button and route to turn off the LED.
```
@app.route('/turn-off-led', methods=['POST'])
def turn_led_off():
    GPIO.output(ledPin, GPIO.LOW)
    return render_template('home.html')
```

### Weather station
- TODO: use dht11 sensor to read indoor temperature and humidity.
- TODO: add graph for daily temp and humidity variations

- Install `Adafruit-DHT` package. It gets readings from the DHT11 sensors for RPi.
```
pip install Adafruit-DHT
```
- 
# Controlling Tapo cameras
### Getting camera info
- Install `pytapo` and test library.
```
pip install pytapo
pip install -U pytest
```
- Initiate library. To obtain the Tapo camera's IP address, perform the `nmap` scan done previously and search for the device with name: ` C200_xxxx`.

```
from pytapo import Tapo

user = "petersonyuhala" # user you set in Advanced Settings -> Camera Account
password = "" # password you set in Advanced Settings -> Camera Account
host = "" # ip of the camera, example: 192.168.1.52

tapo = Tapo(host, user, password)

print(tapo.getBasicInfo())
```
### Rotating camera


### Getting camera stream


### Smart curtains


### Controlling Tapo Light Bulbs.
- Install `PyP100` python package.
```
pip install PyP100
```
- Get Tapo bulb IP address using via an `nmap` scan. NB: You may need to scan multiple times to see the bulb name (e.g., `L530`) in the scan report. Example scan report:
```
Nmap scan report for C200_0C8F53 (192.168.1.131)
Host is up (0.013s latency).
Nmap scan report for L530 (192.168.1.154)
Host is up (0.011s latency).
```

- Connect to it and control with the code below.
```
from PyP100 import PyL530

user = "email@gmail.com"
password = "Password123"
bulb_ip = "192.168.X.X"

l530 = PyL530.L530(bulb_ip, user, password)

l530.handshake() #Creates the cookies required for further methods
l530.login() #Sends credentials to the plug and creates AES Key and IV for further methods

p100.turnOn() #Turns the connected plug on
p100.turnOff() #Turns the connected plug off
p100.toggleState() #Toggles the state of the connected plug

p100.turnOnWithDelay(10) #Turns the connected plug on after 10 seconds
p100.turnOffWithDelay(10) #Turns the connected plug off after 10 seconds

p100.getDeviceInfo() #Returns dict with all the device info of the connected plug
p100.getDeviceName() #Returns the name of the connected plug set in the app

#All the bulbs have the same basic functions as the plugs and additionally allow for the following functions.
l530.setBrightness(50) #Sets the brightness of the connected bulb to 50% brightness
l530.setColorTemp(2700) #Sets the color temperature of the connected bulb to 2700 Kelvin (Warm White)
l530.setColor(30, 80) #Sets the color of the connected bulb to Hue: 30°, Saturation: 80% (Orange)
```
- See: https://pypi.org/project/PyP100/ for more information.

### NFC door lock


### Check more info on particular IP after nmap scan
- 