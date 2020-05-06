/******************************************
 *The sensor was ordered from: www.elegoo.com
 *Author: Vishal Shanbhag
 *Time:2020.May.04
 *THIS CODE WILL WORK WITH THE PYTHON SCRIPT NAMED "findarduino.py" ON THE RECEIVING SIDE
 *We are writing to the serial monitor the temperature in °C which has been received from the DS18B20 sensor.
 ******************************************/
// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Defining the variable Time 
int Time = 1;
bool Status;
/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  //Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
}

/*
 * Main function, get and send the temperature across the serial bus
 */
void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  int temperatureF = (sensors.getTempCByIndex(0)*9/5) + 32; // This is the temperature in Farenheit
  int temperatureD = (sensors.getTempCByIndex(0));          // This is the temperature in degree celcius.
  Serial.write(temperatureD);                               // Writing temperatureD to serial port
  delay(6000);                                              // Delay of 6000 ms i.e 6 seconds. The same sample time needs to be set in the Python script on the receiving side.
}
