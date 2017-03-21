/*
   Tacco corno GCIB 2017 Focherini Carpi

   Davide Gariselli
*/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// ----------- FastLed ---------------
#include <FastLED.h>
#define NUM_LEDS 8
#define DATA_PIN 5 // D5
CRGB leds[NUM_LEDS];
#define BRIGHTNESS  128
// -----------------------------------
int colori[NUM_LEDS] = {}; // only 2^8
bool power = 0;
// ---------------------

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Azionecoop";
char pass[] = "azionecoop2014";

// ON-OFF
BLYNK_WRITE(V0) {
  power = param.asInt();
  if ( power == 0 ) {
    Serial.println("Power OFF");
    FastLED.clear();
  }
  else
    Serial.println("Power ON");
}

// COLORS BUTTON
BLYNK_WRITE(V2) {
  bool button = param.asInt();
  int j = 0;
  if ( button == 1 && power == 1) {
    Serial.println("Colori");
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB( colori[j], colori[j + 1], colori[j + 2]);
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

    //FastLED.clear();
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setRGB( R/4, G/4, B/4);
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

