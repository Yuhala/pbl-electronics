

## Setting up Raspberry Pi on Ubuntu 18: Headless setup (i.e., no monitor, keyboard, mouse)

This Readme provides information on how to set up a raspberry pi board without peripherals. The instructions here are based on my experience while setting up a raspberry pi 3B+ for an Adeept RaspTank Robot, based the first part of these instructions can be used for setting up a raspberry pi board for other purposes.

### Download and flash Raspberry Pi OS image

## Using BalenaEtcher (not good for headless; ssh issues)
- Download `balenaEtcher` tool for ubuntu: [balenaEtcher](https://www.balena.io/etcher/)
- Download a compatible Raspberry Pi OS image for your board: [Raspberry Pi OS Downloads](https://www.raspberrypi.com/software/operating-systems/). The `Lite` versions do not come with an embedded GUI and have less software included (`364MB` vs `2.7GB`). We will use the `Lite` version: `Raspberry Pi OS Lite`.
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

### Weather station
- TODO: use dht11 sensor to read indoor temperature and humidity.

