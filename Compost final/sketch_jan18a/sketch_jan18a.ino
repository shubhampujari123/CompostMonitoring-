#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "SparkFunHTU21D.h"

#include "SD.h"
#include "SPI.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define DS18B20PIN 4
OneWire oneWire(DS18B20PIN);

DallasTemperature sensor(&oneWire);
// Create the lcd object address 0x3F and 16 columns x 2 rows 
LiquidCrystal_I2C lcd (0x27, 16,2);  //
HTU21D myHumidity;
const char* ssid = "tpdefault";
const char* password = "manas12345";
const char* mqtt_server = "139.59.90.224";
WiFiClient espClient;
PubSubClient client(espClient);
char MQ135_PIN = 35;
char MQ09_PIN = 14;

int sensor1 = 25;
int value ; 
int moisturePercentage;
char Mq09_data;
char Mq135_data;
int air = 12;
int methane= 14;
long lastMsg = 0;
char msg[50];



void setup()
{
  
         Serial.begin(115200);
         sensor.begin();
       Serial.println("Connecting to ");     // connecting to wifi
       Serial.println(ssid);
       WiFi.begin(ssid, password);
      
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
        Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, 1883);
 
  
 lcd. init ();
  lcd. backlight ();

   //writeFile(SD, "/Readings.txt", 'HEllo');
    delay(1000);
  lcd.clear();
   myHumidity.begin();
   lcd. setCursor (0, 0);
   lcd.print ("Whiz Key Pvt.Ltd  ");
   //lcd. setCursor (16, 1);
  //lcd.print ("Welcome ");
  delay(2000);
  lcd.clear();
  //sensors.begin();
 
  lcd. setCursor (6, 0);
  lcd.print((char)223);
  lcd. setCursor (7, 0);
  lcd.print ("C");
   lcd. setCursor (0, 0);
  lcd.print ("Tmp:");
   lcd. setCursor (9,0 );
   lcd. setCursor (2, 1);
  lcd.print ("Moisture:");
   lcd. setCursor (13, 1);
  lcd.print ("%");

}

void loop()
{
  if (!client.connected()) {
  reconnect();
 }
 client.loop();
 value = analogRead(sensor1);
value = map(value,0,4096,100,0);
Serial.print(value);
lcd. setCursor (11, 1);
lcd. print (value);
 sensor.requestTemperatures(); 
 float tempinC = sensor.getTempCByIndex(0);
  lcd. setCursor (0, 0);
  Mq135_data = analogRead(MQ135_PIN);
  Serial.println("ºF");
  Serial.print("Mq09_data  ==  ");
  Serial.println(Mq09_data);
  Serial.print("Mq135_data  ==  ");
  Serial.println(Mq135_data);
  lcd. setCursor (4, 0);
  lcd. print (tempinC);


 

  lcd. setCursor (11, 1);
  //lcd. print (value1);
  String dataPacket = String (tempinC) + ","+ ","+String (air) +"," +String(methane) ;
client.publish("compost/wifi/1",dataPacket.c_str());
  
}
//------------------------------------------------------------------
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("WMS/APP1");
      

     // client.subscribe("esp/vib");


    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
 
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "WMS/APP1") {
    Serial.println(messageTemp);
    if(messageTemp=="1"){
    }
  //String dataPacket = String(Rotation2) + "," + String(Rotation3) + "," + String(Rotation1) + "," + viber2 + "," + viber1 + "," + viber3 + "," + Channel1 + "," + Channel2 + "," + Channel3 ;
    
    }
}
void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//------------------------------------------------------------------
