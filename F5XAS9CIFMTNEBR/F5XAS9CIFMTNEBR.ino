#include <OneWire.h>
#include <DallasTemperature.h>

#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile

RH_ASK driver;
 
// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
 
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  if (!driver.init())
         Serial.println("init failed");

  // Start up the library
  sensors.begin();
}
 
 
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("\n Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");

  // std:string msg = sprintf("Temps: 1 %f, 2 %f, 3 %f", sensors.getTempCByIndex(0), sensors.getTempCByIndex(1), sensors.getTempCByIndex(2))

  String message = String("Temps: ");
  message = message + String("Sensor 1: ") + String(sensors.getTempCByIndex(0)); 
  message = message + String(" Sensor 2: ") + String(sensors.getTempCByIndex(1)); 
  message = message + String(" Sensor 3: ") + String(sensors.getTempCByIndex(2)); 

  const char *msg = message.c_str();

  Serial.println(msg);
  
  driver.send((uint8_t *)msg, strlen(msg));
  driver.waitPacketSent();

  delay(1000);
}
