#include <Adafruit_NeoPixel.h>
#include <WiFiNINA.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

const char* ssid = "PLUSNET-FMGC";
const char* password = "746987bc73";

#define ioServer "io.adafruit.com"
#define ioPort 1883
#define ioUsername "s1858422"
#define ioKey "aio_AUQg81yZ4AcZh0NLPMyvCtSrrY7p"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, ioServer, ioPort, ioUsername, ioKey);
Adafruit_MQTT_Subscribe dataFeed = Adafruit_MQTT_Subscribe(&mqtt, ioUsername "/feeds/tilt-control");

#define LED_PIN 6
#define LED_COUNT 50 // Number of LEDs
#define FOLLOW_LIGHT_LENGTH 19

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

int x = 0; // sensor value in cm
int xLed = 0; // position of active LED

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  while (!Serial) {}
  connectToWiFi(ssid, password);

  strip.begin();
  strip.show();

  mqtt.subscribe(&dataFeed);
}

void loop() {
  // put your main code here, to run repeatedly:

  connectToMQTT();

  Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(2000))) {
    if (subscription == &dataFeed) {
      Serial.print("Got: ");
      Serial.println((char *)dataFeed.lastread);


      String ioData = (char *)dataFeed.lastread;

      int distance = ioData.toInt();
      Serial.print("Distance: ");
      Serial.println(distance);

      x = distance;

      //calculate the led (300 LEDs / 500cm)
      xLed = round(0.6 * x);
      strip.clear();
      strip.fill(strip.Color(255, 255, 255), xLed, FOLLOW_LIGHT_LENGTH);
      delay(500);
      strip.setBrightness(10);
      strip.show();



    }
  }

}
