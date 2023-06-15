#include "HX711.h"
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
const int LOADCELL_DOUT_PIN = D2;
const int LOADCELL_SCK_PIN = D3;
const int LOADCELL_DOUT_PIN2 = D6;
const int LOADCELL_SCK_PIN2 = D7;
HX711 scale;
HX711 scale2;
int WEIGHT1 = 0;
int WEIGHT2 = 0;
#define  CAM D1
#define GAS A0
#define BUZZER D8

#define WLAN_SSID       "Siri" 
#define WLAN_PASS       "123456789"
#define MQTT_SERV      "io.adafruit.com"
#define MQTT_PORT  1883           
#define MQTT_NAME  "smart_pantry223"
#define MQTT_PASS  "aio_ORmq57w6dEHI7rKT8SY9mpAFtS26"
////////////////////////////////// Feeds  ///////////////////////////////////////////////////////////////////////////
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Publish ITEM1 = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/w1");
Adafruit_MQTT_Publish ITEM2 = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/w2");
Adafruit_MQTT_Publish GASFEED = Adafruit_MQTT_Publish(&mqtt, MQTT_NAME "/f/gas");

void setup() {
  Serial.begin(9600);
  pinMode(CAM,OUTPUT);
    pinMode(BUZZER,OUTPUT);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
Serial.println();
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.print(WiFi.localIP());
  Serial.println("HX711 Demo");
    digitalWrite(CAM,HIGH);

  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);


  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided

  Serial.println("Readings:");

//////////////////////////////////////////////////

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale2.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale2.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale2.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale2.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)

  scale2.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale2.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale2.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale2.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale2.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale2.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided

  Serial.println("Readings:");
  MQTT_connect();
  digitalWrite(BUZZER,HIGH);
  delay(500);
  digitalWrite(BUZZER,LOW);
}

void loop() {
  //Serial.print("one reading:\t");
 //Serial.println(scale.get_units(), 1);
int GASVALUE = analogRead(GAS);
Serial.print("GAS VALUE:");Serial.println(GASVALUE);
  WEIGHT1 = scale.get_units();
  Serial.print("WEIGHT1:");Serial.println(WEIGHT1);
delay(500);
 // Serial.print("SECOND reading:\t");
  WEIGHT2 = scale2.get_units();
    Serial.print("WEIGHT2:");Serial.println(WEIGHT2);

  if(WEIGHT2>5){
    WEIGHT2=WEIGHT2+20;
     // Serial.println(WEIGHT2+20);

  }
  else{
  WEIGHT2=WEIGHT2;
  }

  if((WEIGHT1<10) && (WEIGHT1>0)){
    digitalWrite(CAM,LOW);
    delay(100);
    digitalWrite(CAM,HIGH);
    digitalWrite(BUZZER,HIGH);
    delay(500);
    digitalWrite(BUZZER,LOW);
  }
    if((WEIGHT2<10) && (WEIGHT2>0)){
    digitalWrite(CAM,LOW);
    delay(100);
    digitalWrite(CAM,HIGH);
    digitalWrite(BUZZER,HIGH);
    delay(500);
    digitalWrite(BUZZER,LOW);
  }
    if(GASVALUE>1000){
    digitalWrite(CAM,LOW);
    delay(100);
    digitalWrite(CAM,HIGH);
    digitalWrite(BUZZER,HIGH);
    delay(500);
    digitalWrite(BUZZER,LOW);
  }
  
 if (ITEM1.publish(WEIGHT1))
  {
    Serial.println("VALUE UPDATED");
    delay(2000);
  }
   if (ITEM2.publish(WEIGHT2))
  {
    Serial.println("VALUE UPDATED");
    delay(2000);
  }
  if (GASFEED.publish(GASVALUE))
  {
    Serial.println("VALUE UPDATED");
    delay(2000);
  
  }
//String Output="";
//Output = "W1:";
//Output+=WEIGHT1;
//Output+="*";
//Output+= "W2:";
//Output+=WEIGHT2;
//Output+="#";
//Output+= "SP:";
//Output+="yes";
//Output+="&";
//Serial.println(Output);
}
void MQTT_connect()
{
  int8_t ret;
  if (mqtt.connected())
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0)
    {
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);
       retries--;
       if (retries == 0)
       {
         while (1);
       }
    }
  Serial.println("MQTT Connected!");
}
