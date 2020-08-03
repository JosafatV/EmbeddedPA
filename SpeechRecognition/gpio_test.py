from gpiozero import LED, Button
from time import sleep

r_led = LED(17)
y_led = LED(22)
g_led = LED(27)
btn = Button(2)

def semafore():
    g_led.on()
    sleep(0.5)
    g_led.off()
    y_led.on()
    sleep(0.5)
    y_led.off()
    r_led.on()
    sleep(0.5)
    r_led.off()

while True:
    if but.is_pressed:
        print(" +++ Starting debug test +++")
        semafore()
    else:
        sleep(0.1)

