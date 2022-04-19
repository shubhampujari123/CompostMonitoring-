#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include "SD.h"
#include "SPI.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#define DS18B20PIN 4
OneWire oneWire(DS18B20PIN);
int sensor1 = 25;
int value ;
DallasTemperature sensor(&oneWire);
// Create the lcd object address 0x3F and 16 columns x 2 rows 
LiquidCrystal_I2C lcd (0x27, 16,2);  //
int moisturePercentage;
int methane= 14;
long lastMsg = 0;
char msg[50];



void setup()
{
  
   Serial.begin(115200);
   sensor.begin();
 lcd. init ();
  lcd. backlight ();
    delay(1000);
  lcd.clear();
   lcd. setCursor (0, 0);
   lcd.print ("Whiz Key Pvt.Ltd  ");
   //lcd. setCursor (16, 1);
  //lcd.print ("Welcome ");
  delay(2000);
  lcd.clear();
  lcd. setCursor (9, 0);
  lcd.print((char)223);
  lcd. setCursor (10, 0);
  lcd.print ("C");
   lcd. setCursor (0, 0);
  lcd.print ("Tmp:");
   lcd. setCursor (9,0 );
   lcd. setCursor (0, 1);
  lcd.print ("Moisture:");
 
   lcd. setCursor (11, 1);
  lcd.print ("%");

}

void loop()
{
 sensor.requestTemperatures(); 
value = analogRead(sensor1);
value = map(value,0,4096,100,0);
 float tempinC = sensor.getTempCByIndex(0);
  lcd. setCursor (0, 0);
  lcd. setCursor (4, 0);
  lcd. print (tempinC);
  lcd. setCursor (9, 1);
  lcd. print (value);
 

}
//------------------------------------------------------------------

//------------------------------------------------------------------
