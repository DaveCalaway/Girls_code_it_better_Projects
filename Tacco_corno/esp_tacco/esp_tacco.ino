/*
   Tacco corno GCIB 2017 Focherini Carpi

   Davide Gariselli
*/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// ---------------------
//#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>
#define NUM_LEDS 5
#define DATA_PIN 5 // D5
CRGB leds[NUM_LEDS];
#define BRIGHTNESS  128
// ---------------------

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
//  char ssid[] = "Azionecoop";
//  char pass[] = "azionecoop2014";

char ssid[] = "xxx";
char pass[] = "xxx";

void showled(int R, int G, int B) {
  //FastLED.clear();
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB( R, G, B);
  }
  FastLED.show();
}

//Add a zeRGBa Widget and set it to MERGE mode. Choose Virtual Pin V1
BLYNK_WRITE(V1) {
  int R = param[0].asInt();
  int G = param[1].asInt();
  int B = param[2].asInt();

  showled(R, G, B);

  // Do something with x and y
  Serial.print("R = ");
  Serial.print(R);
  Serial.print("; G = ");
  Serial.print(G);
  Serial.print("; B = ");
  Serial.print(B);
  Serial.println();
}


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness( BRIGHTNESS );
  Blynk.begin(auth, ssid, pass);
}


void loop() {
  Blynk.run();
}

