# -*- coding: utf-8 -*-
"""
Created on Tue Apr 28 21:52:16 2020

@author: visha


To terminate the loop execution, press ctrl+c while the cursor is active om the 
console window. Pressing ctrl+c when the cursor is active in any other window
will not stop execution.

The program is meant to connect to an active serial port on which the arduino 
has been connected, the name of the arduino device will have to be specified 
beforehand and can be found under "Manage Devices" section of the pc. 

The program will save an excel file at the current directory with the name "Tempdata_Todaysdate".
If you run the program more than once on the same day, the old file will be replaced.
"Column A" in the excel sheet will have the time stamp
"Colum B" will contain the corresponding temperature value as an integer. 

The get_ports() method will return a list of all active serial ports
The findarduino(portsFound) method shall take the list of ports found by 
get_ports() and retrun a communication port name which is associated with 
the device name mentioned. E.g: if COM6 is associated with the device, the 
function will return COM6
 
"""
import serial                                #for serial communication
import serial.tools.list_ports
import xlsxwriter as xl
from datetime import date
from datetime import datetime
import time
today = date.today()
Date_formatted = today.strftime("%b-%d-%Y")
filename = 'Tempdata_%s.xlsx'%(Date_formatted)
workbook = xl.Workbook(filename)
worksheet = workbook.add_worksheet()
def get_ports():
    ports = serial.tools.list_ports.comports()
    return ports

def findarduino(portsFound):
    commport = 'None'
    numconnections = len(portsFound)
    
    for i in range(0,numconnections):
        port = portsFound[i]
        strport = str(port)
        print('For i = ' + str(i) + ', Port name is ' + strport)
        if 'USB-SERIAL CH340' in strport:                                       #Change 'USB-SERIAL CH340' to the name which shows up when you connect your arduino device to your PC. You can find the name through "Manage Devices" menu of your windows pc
            splitport = strport.split(' ')
            commport = (splitport[0])
    print('Value of commport variable being returned by findarduino() function is '+ commport)
    return commport 

portsfound = get_ports()
connectport = findarduino(portsfound)
print('Trying to connect to ' + connectport)
if connectport != 'None':
    ser = serial.Serial(connectport, baudrate = 9600,timeout=1)
    print('Connected to ' + connectport)
else:
    print('Connection Issue!')
    
print('Done')
try:
    for i in range(0,60):
            incoming = ser.inWaiting()                                          #Number of incoming bytes in buffer
            message = ser.read(1)                                               #Reading 1 byte
            message = int.from_bytes(message, 'little')                         #Added this from https://stackoverflow.com/questions/45010682/how-can-i-convert-bytes-object-to-decimal-or-binary-representation-in-python
            print("The number of bytes in serial buffer is " + str(incoming))   #Printing the number of bytes
            print(message)                                                      #Printing the temperature
            now = datetime.now()
            current_time = now.strftime('%H:%M:%S')
            column_name_1 = 'A%i'%(i+1)
            column_name_2 = 'B%i'%(i+1)
            worksheet.write(column_name_1,current_time)
            worksheet.write(column_name_2,message)
            time.sleep(6)                                                       #Sample time should match that of the arduino
    '''
    When the sampling rate of the python script is higher than that of the TX rate of the arduino, sample points in between 
    the arduino TX pings will be an empty buffer and provide a value of 0. Similarly if the sampling rate of the python script
    is lower than the arduino, then the serial buffer gets filled up and would lead to delayed and NON REAL TIME updates.
    The solution is to match the sample rates of both the systems. Also we could check for the bytes in the buffer.
    
    '''
except KeyboardInterrupt:
    print('Terminating loop')
    pass
workbook.close()
ser.close()
print("Excel workbook and serial monitor closed succesfully")
