#Devant Yadav, Akuete Akwei, Charles Lejtman
import serial #Serial imported for Serial communication
import time #Required to use delay functions
import pyautogui #Turns serial data into keyboard input

ArduinoSerial = serial.Serial('com7',9600) #Create Serial port object called serial that reads serial data on com port 7
time.sleep(2) #wait for 2 seconds for the communication to get established

while 1:
    incoming = str (ArduinoSerial.readline()) #read the serial data and log it to the console
    print incoming
    
  

    if 'Forward' in incoming:
        pyautogui.typewrite(['up'], 1.0)

    if 'Backward' in incoming:
        pyautogui.typewrite(['down'], 1.0) 

    if 'Left' in incoming:
        pyautogui.typewrite(['left'], 1.0)
        

    if 'Right' in incoming:
        pyautogui.typewrite(['right'], 1.0)

    incoming = "";
