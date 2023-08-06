#
# Python module to control Tapo Light bulbs
# Peterson Yuhala
#

from PyP100 import PyL530

import RPi.GPIO as GPIO
import time
import DDIR


user = "petersonyuhala@gmail.com" # user you set in Advanced Settings -> Camera Account
password = "Facebook@2000!" # password you set in Advanced Settings -> Camera Account fb@2k!
host = "192.168.1.154" # ip of tapo bulb (find it with nmap scan)

l530 = PyL530.L530(host, user, password)
irSensorPin = 8


def turn_bulb_on():
    global l530
    l530.turnOn() #Turns the connected plug on    
    

def turn_bulb_off():
    global l530
    l530.turnOff() #Turns the connected plug on
    
    
    
def connect_to_bulb():
    global l530
    l530.handshake() #Creates the cookies required for further methods
    l530.login() #Sends credentials to the plug and creates AES Key and IV for further methods
    print(">>>>> Connected to Tapo Bulb successfully >>>>>")


def do_ir_control(data):
    hex_code = str(hex(data))
    if(hex_code == '0xffa25d'):
        turn_bulb_on()
    elif(hex_code == '0xff9867'):
        turn_bulb_off()

def read_ir_signals():
    DDIR.setup(irSensorPin)
    try:
        print("Starting IR Listener")
        while True:            
            GPIO.wait_for_edge(irSensorPin, GPIO.FALLING)
            code = DDIR.on_ir_receive(irSensorPin)
            if code:
                do_ir_control(code)
            else:
                print("Invalid code")
    except KeyboardInterrupt:
        pass
    except RuntimeError:
        pass
    

connect_to_bulb()
read_ir_signals()
#turn_bulb_off()
#blink_bulb(3)

