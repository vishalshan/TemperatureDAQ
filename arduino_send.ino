/******************************************
 *Website: www.elegoo.com
 * 
 *Time:2017.12.12
 *THIS CODE WILL WORK ONLY WITH THE PYTHON SCRIPT NAMED "D:\Vishal\Arduino experiments\findarduino.py"
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

 /*
  
  */
typedef union{
  float floatingPoint;
  byte binary[4];
}binaryFloat;
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  //Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  
  //float starttime = 09.30;
  //Serial.print("The time a which we staretd monitoring is ");
  //Serial.println(starttime);
}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  float temperatureF = (sensors.getTempCByIndex(0)*9/5) + 32; // This is the temperature in Farenheit
  int temperatureD = (sensors.getTempCByIndex(0)); // This is the temperature in degree celcius.
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  //Serial.print("Temperature for the device 1 (index 0) is: ");
  //Serial.print(temperatureF);
  //Serial.print("°F & ");
  //Serial.print(temperatureD);
  //Serial.print("°C time elapsed in minutes is : ");
  //Serial.println(Time);
  Status = Serial.availableForWrite();

  //binaryFloat hi;
  //hi.floatingPoint = temperatureD;
  //Serial.write(hi.binary[3]);
  Serial.write(temperatureD);
  //Serial.println(hi.binary[3]);
  //Serial.write(hi.binary[2]);
  //Serial.println(hi.binary[2]);
  //Serial.write(hi.binary[1]);
  //Serial.println(hi.binary[1]);
  //Serial.write(hi.binary[0]);
  //Serial.println(hi.binary[0]);
  //Serial.println(temperatureD);
  /*Serial.print(hi.binary[0]);
  Serial.print(hi.binary[1]);
  Serial.print(hi.binary[2]);
  Serial.println(hi.binary[3]);
  */
  delay(6000);
}
