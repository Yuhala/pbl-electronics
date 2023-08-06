#
# Python module to control Tapo Light bulbs
# Peterson Yuhala
#

from PyP100 import PyL530
import time

user = "x" # user you set in Advanced Settings -> Camera Account
password = "x!" # password you set in Advanced Settings -> Camera Account fb@2k!
host = "192.168.1.154" # ip of tapo bulb (find it with nmap scan)

l530 = PyL530.L530(host, user, password)


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
    

def blink_bulb(sleep_time):
    while(1):
        turn_bulb_on()
        time.sleep(sleep_time)
        turn_bulb_off()
        time.sleep(sleep_time)

    
def tapo_l530_tests():
    l530.handshake() #Creates the cookies required for further methods
    l530.login() #Sends credentials to the plug and creates AES Key and IV for further methods

    l530.turnOn() #Turns the connected plug on
    l530.turnOff() #Turns the connected plug off
    l530.toggleState() #Toggles the state of the connected plug

    l530.turnOnWithDelay(10) #Turns the connected plug on after 10 seconds
    l530.turnOffWithDelay(10) #Turns the connected plug off after 10 seconds

    #All the bulbs have the same basic functions as the plugs and additionally allow for the following functions.
    l530.setBrightness(50) #Sets the brightness of the connected bulb to 50% brightness
    l530.setColorTemp(2700) #Sets the color temperature of the connected bulb to 2700 Kelvin (Warm White)
    l530.setColor(30, 80) #Sets the color of the connected bulb to Hue: 30°, Saturation: 80% (Orange)


connect_to_bulb()
turn_bulb_off()
blink_bulb(3)