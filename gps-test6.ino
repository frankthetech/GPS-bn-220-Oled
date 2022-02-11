/******************************************************************************
  testing bn-220 gps on teensy lc with oled screen  10-feb-22
******************************************************************************/
#include <SPI.h>
#include <Wire.h>
#include <TinyGPS++.h> // Include the TinyGPS++ library
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);

TinyGPSPlus tinyGPS; // Create a TinyGPSPlus object

#define GPS_BAUD 9600 // GPS module baud rate. bn-220 = 9600.

#define gpsPort Serial1  // Alternatively, use Serial1 on the Leonardo

#define SerialMonitor Serial

void setup()
{
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  SerialMonitor.begin(9600);
  gpsPort.begin(GPS_BAUD);
  display.display();
  delay(2000);
  // Clear the buffer.
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15,0);
  display.println("GPS starting..!");
  display.display();
  delay(2000);
}

void loop()
{
  // print position, altitude, speed, time/date, and satellites:
  //printGPSInfo();
  printScrn();
  
  // "Smart delay" looks for GPS data while the Arduino's not doing anything else
  smartDelay(1000); 
}

void printScrn(){
  display.clearDisplay();
  
  display.setTextSize(1);
  display.setCursor(10,0);
  display.print("GPS On    #Sats ");
  display.setCursor(105,0);
  display.print(tinyGPS.satellites.value());
  
  display.setCursor(4,24);
  display.print("Speed ");
  display.setTextSize(2);
  display.print(tinyGPS.speed.mph(),0);
  display.setTextSize(1);
  display.print(" MPH");

  display.setCursor(0,44);
  display.print("Course ");
  display.setTextSize(2);
  display.print(tinyGPS.course.deg(),0);
  display.setTextSize(1);
  display.print(" DEG");
  
  display.display(); 
}

void printGPSInfo()
{
  // Print latitude, longitude, altitude in feet, course, speed, date, time,
  // and the number of visible satellites.
  SerialMonitor.print("Lat: "); SerialMonitor.println(tinyGPS.location.lat(), 6);
  SerialMonitor.print("Long: "); SerialMonitor.println(tinyGPS.location.lng(), 6);
  SerialMonitor.print("Alt: "); SerialMonitor.println(tinyGPS.altitude.feet());
  SerialMonitor.print("Course: "); SerialMonitor.println(tinyGPS.course.deg());
  SerialMonitor.print("Speed: "); SerialMonitor.println(tinyGPS.speed.mph());
  SerialMonitor.print("Date: "); printDate();
  SerialMonitor.print("Time: "); printTime();
  SerialMonitor.print("Sats: "); SerialMonitor.println(tinyGPS.satellites.value());
  SerialMonitor.println();
}

// This custom version of delay() ensures that the tinyGPS object
// is being "fed". From the TinyGPS++ examples.
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {
    // If data has come in from the GPS module
    while (gpsPort.available())
      tinyGPS.encode(gpsPort.read()); // Send it to the encode function
    // tinyGPS.encode(char) continues to "load" the tinGPS object with new
    // data coming in from the GPS module. As full NMEA strings begin to come in
    // the tinyGPS library will be able to start parsing them for pertinent info
  } while (millis() - start < ms);
}

// printDate() formats the date into dd/mm/yy.
void printDate()
{
  SerialMonitor.print(tinyGPS.date.day());
  SerialMonitor.print("/");
  SerialMonitor.print(tinyGPS.date.month());
  SerialMonitor.print("/");
  SerialMonitor.println(tinyGPS.date.year());
}

// printTime() formats the time into "hh:mm:ss", and prints leading 0's
// where they're called for.
void printTime()
{
  SerialMonitor.print(tinyGPS.time.hour());
  SerialMonitor.print(":");
  if (tinyGPS.time.minute() < 10) SerialMonitor.print('0');
  SerialMonitor.print(tinyGPS.time.minute());
  SerialMonitor.print(":");
  if (tinyGPS.time.second() < 10) SerialMonitor.print('0');
  SerialMonitor.println(tinyGPS.time.second());
}

