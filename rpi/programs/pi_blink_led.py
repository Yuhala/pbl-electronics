import RPi.GPIO as GPIO
import time

ledPin = 14
GPIO.setmode(GPIO.BCM)
#GPIO.setwarnings(False)

#set led pin as output
GPIO.setup(ledPin, GPIO.OUT)

#set initial led state as low (i.e off)
GPIO.output(ledPin, GPIO.LOW)
print(">>>> Blink LED with Raspberry PI!! >>>>> Press Ctrl + C to exit")

try:
    while 1:
        GPIO.output(ledPin, GPIO.HIGH)
        print("LED ON")
        time.sleep(0.1)
        GPIO.output(ledPin, GPIO.LOW)
        print("LED OFF")
        time.sleep(0.1)
except KeyboardInterrupt:
    GPIO.cleanup()