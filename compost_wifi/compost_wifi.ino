#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
#include "SparkFunHTU21D.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "ThingSpeak.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#define DS18B20PIN 4
OneWire oneWire(DS18B20PIN);
DallasTemperature sensor(&oneWire);
// Create the lcd object address 0x3F and 16 columns x 2 rows 
LiquidCrystal_I2C lcd (0x27, 16,2);  //

const char * apiKey = "0V5TMR4AHZPA8WAQ";     //  Enter your Write API key from ThingSpeak
const char *ssid =  "tpdefault";     // replace with your wifi ssid and wpa2 key
const char *pass =  "manas12345";
const char* server = "api.thingspeak.com";

WiFiClient  client;
unsigned long myChannelNumber = 1;
char MQ135_PIN = 35;
char MQ09_PIN = 14;
int sensor1 = 25;
int value ;   
int moisturePercentage;
char Mq09_data;
char Mq135_data;
int air = 12;
int methane= 14;

void setup() 
{
       Serial.begin(115200);
       
       sensor.begin();
       Serial.println("Connecting to ");     // connecting to wifi
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
ThingSpeak.begin(client);
lcd. init ();
lcd. backlight ();
 lcd.clear();
 lcd. setCursor (0, 0);
  delay(1000);
lcd.clear();

 lcd. setCursor (0, 0);
 lcd.print ("Whiz Key Pvt.Ltd  ");
 //lcd. setCursor (16, 1);
//lcd.print ("Welcome ");
delay(2000);
lcd.clear();
//sensors.begin();
lcd. init ();
lcd. backlight ();

}

void loop() 
{
sensor.requestTemperatures(); 
float tempinC = sensor.getTempCByIndex(0);
lcd. setCursor (0, 0);
lcd. setCursor (6, 0);
lcd.print((char)223);
lcd. setCursor (7, 0);
lcd.print ("C");
 lcd. setCursor (2, 1);
lcd.print ("Moisture:");
lcd. setCursor (2, 2);
lcd.print ("%");
lcd. setCursor (0, 0);
lcd.print ("Tmp:");
  lcd. setCursor (4, 0);
lcd. print (tempinC);
Serial.print("Temp == ");
Serial.println(tempinC);



value = analogRead(sensor1);
value = map(value,0,4096,100,0);
Serial.print(value);
lcd. setCursor (11, 1);
lcd. print (value);
air = analogRead(12);
methane = analogRead(14);
 
int x = ThingSpeak.writeFields(myChannelNumber, apiKey);
delay(2000);
lcd.clear();
lcd. setCursor(0, 0);
lcd.print ("Ammonia:");
lcd. setCursor(9, 0);
lcd.print(air);
lcd. setCursor(0, 1);
lcd.print ("Methane:");
lcd. setCursor(9, 1);
lcd.print(methane);
delay(2000);
lcd.clear();
ThingSpeak.setField(1, tempinC);
ThingSpeak.setField(3,value);
ThingSpeak.setField(4,air);
ThingSpeak.setField(5,methane);

}
