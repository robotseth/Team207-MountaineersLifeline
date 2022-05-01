from machine import UART,Pin
import time

uart1 = UART(1, baudrate=9600, tx=17, rx=16)

while True:
    time.sleep(.01)
    if uart1.any():
        try:
            bin_data = uart1.read().decode()
        except:
            bin_data = uart1.read()
        print('{}'.format(bin_data)) #Echo String:
        