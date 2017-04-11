/*
   Tacco corno GCIB 2017 Focherini Carpi
   The program is made for ESP8266 NodeMCU, one NeoPixel strip on pin D5.
   The dashboard is Blynk, with On-Off -switch-,single color -button- and
   zeRGBa -widget- .
   I used a level shifter for control the data to the NeoPixel.
   If you use Adafruit Feather HUZZAH you don't need the level shifter.
   
   Maker: Davide Gariselli
   Teacher: Elena Menozzi
*/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// ----------- FastLed ---------------
#include <FastLED.h>
#define NUM_LEDS 5 // remeber, use an external power if u want to use leds>10
#define DATA_PIN 5 // D5
CRGB leds[NUM_LEDS];
#define BRIGHTNESS  128 // 2^8 value
// -----------------------------------
// if you want to use integer nuumber:  R*256*256 + G*256 + B = int
int colors[NUM_LEDS * 3] = {249, 10, 10, 255, 102, 0, 250, 242, 14, 13, 255, 21, 13, 94, 255}; // only 2^8 colors
bool power = 0;
// ---------------------

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxx";
char pass[] = "xxx";

// ON-OFF
BLYNK_WRITE(V0) {
  power = param.asInt();
  if ( power == 0 ) {
    Serial.println("Power OFF");
    for (int i = 0; i < NUM_LEDS; i++)
      leds[i].setRGB( 0, 0, 0);
    FastLED.show();
  }
  else
    Serial.println("Power ON");
}

// COLORS BUTTON
BLYNK_WRITE(V2) {
  bool button = param.asInt();
  int j = 0;
  if ( button == 1 && power == 1) {
    Serial.println("colors");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB( colors[j], colors[j + 1], colors[j + 2]);
      j = j + 3;
    }
    FastLED.show();
  }
}

//Add a zeRGBa Widget and set it to MERGE mode. Choose Virtual Pin V1
BLYNK_WRITE(V1) {
  if ( power == 1 ) {
    int G = param[0].asInt();
    int R = param[1].asInt();
    int B = param[2].asInt();

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB( R / 4, G / 4, B / 4);
    }
    FastLED.show();

    // Do something with x and y
    Serial.print("R = ");
    Serial.print(R);
    Serial.print("; G = ");
    Serial.print(G);
    Serial.print("; B = ");
    Serial.print(B);
    Serial.println();
  }
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
