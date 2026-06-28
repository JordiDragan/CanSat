import serial
import time

archivo = open('dades_cansat.csv','w',newline='')
serialArduino = serial.Serial("COM8",9600)
time.sleep(1)

while True:

    cad = serialArduino.readline().decode('ascii')
    if cad.startswith("CLAN NK;"):
        print(cad)
        archivo.write(cad)
