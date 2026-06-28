#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <Arduino.h>

int i = 0;
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define SET      8
#define AUX      9
#define TXD     11
#define RXD     10
#define EN      12 
#define VCC     13
#define GND    GND
SoftwareSerial APCport(RXD, TXD);  

Adafruit_BMP280 bmp;
/*
   This sample sketch demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  APCport.begin(9600);    
  
  pinMode(SET,OUTPUT);
  pinMode(AUX,INPUT);
  pinMode(EN,OUTPUT);
  pinMode(VCC,OUTPUT);

  digitalWrite(SET,HIGH);
  digitalWrite(VCC,HIGH);
  digitalWrite(EN,HIGH);
  ss.begin(GPSBaud);
  unsigned status;
  status = bmp.begin();
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                 Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                 Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                 Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                 Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  Serial.println("CLAN NK;Location Lat;Location Long;Date;Time;Temperature (C);Pressure (Pa);Approx Altitude (m);UV");
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void write_config()
{
  Serial.println(F("ESTABLECIENDO NUEVA CONFIGURACION...\n"));
  digitalWrite(SET, LOW);               // poner en modo configuracion
  delay(50);

//Parametros de configuración
  APCport.print("WR 418000 1 9 3 0");   
  APCport.write(0x0D);                  
  APCport.write(0x0A);                  
  delay(100);
  digitalWrite(SET, HIGH);              
}

void displayInfo()
{
  Serial.print("CLAN NK;");
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(";");
    Serial.print(gps.location.lng(), 6);
    Serial.print(";");
  }
  else
  {
    Serial.print("INVALID;");
    Serial.print("INVALID;");
  }

  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.print(gps.date.year());
    Serial.print(";");
  }
  else
  {
    Serial.print("INVALID;");
  }

  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print("0");
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print("0");
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print("0");
    Serial.print(gps.time.second());
    Serial.print(".");
    if (gps.time.centisecond() < 10) Serial.print("0");
    Serial.print(gps.time.centisecond());
    Serial.print(";");
  }
  else
  {
    Serial.print("INVALID;");
  }

  Serial.print(bmp.readTemperature());
  Serial.print(";");
  Serial.print(bmp.readPressure());
  Serial.print(";");
  Serial.print(bmp.readAltitude(1013.25));
  Serial.print(";");
{
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
}

}
