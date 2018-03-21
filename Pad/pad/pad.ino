/*  Pads - Girls code it better 2017/18
    Make a big pad for every pc game! Plus use 2 neopixel strips for play with light!
    Board: Pro Micro - 5V/16MHz ( https://goo.gl/ktnDG2 )
    DaveCalaway ( https://goo.gl/UdFf25 )
*/

#include <FastLED.h> // https://github.com/FastLED/FastLED/wiki/Basic-usage
#include <Keyboard.h>
#include <Mouse.h>

// buttons for move feet
const int upButton = 2; // W
const int downButton = 3; // S
const int leftButton = 4; // A
const int rightButton = 5; // D
const int jumpButton = 14; // JUMP

// mouse for head
const int upMouse = 7;
const int downMouse = 8;
const int leftMouse = 16;
const int rightMouse = 6;
const int mouseLeft = 15; // click left mouse


// neopixels
const int STRIP1_PIN = 9;
#define NUM_LEDS_STRIP1      16
int delay_strip1 = 500;
CRGB strip1[NUM_LEDS_STRIP1];

const int STRIP2_PIN = 10;
#define NUM_LEDS_STRIP2      16
int delay_strip2 = 500;
CRGB strip2[NUM_LEDS_STRIP2];

const int responseDelay = 70;
const int mouseReaction = 20;

byte Button[6] = {upButton, downButton, leftButton, rightButton, mouseLeft, jumpButton};
byte mouse[4] = {upMouse, downMouse, leftMouse, rightMouse};

byte mouse_read = 1;
byte button_read = 1;

void setup() {
  // initialize digital pins
  for ( byte i = 0; i < 6; i++) {
    pinMode(Button[i], INPUT_PULLUP);
  }
  for ( byte i = 0; i < 4; i++) {
    pinMode(mouse[i], INPUT_PULLUP);
  }

  //Serial.begin(9600);
  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
  FastLED.addLeds<NEOPIXEL, STRIP1_PIN>(strip1, NUM_LEDS_STRIP1);
  FastLED.addLeds<NEOPIXEL, STRIP2_PIN>(strip2, NUM_LEDS_STRIP2);
}

void loop() {
  // strip function
  for (int dot = 0; dot < NUM_LEDS_STRIP1; dot++) {
    strip1[dot] = CRGB::Blue;
    FastLED.show();

    button_check();

    delay(30);
    // clear this led for the next time around the loop
    strip1[dot] = CRGB::Black;
  }
}

void mouse_(byte i) {
  if (i == 0) // up
    Mouse.move(0, -(mouseReaction));
  if (i == 1) // down
    Mouse.move(0, mouseReaction);
  if (i == 2) // left
    Mouse.move(-(mouseReaction), 0);
  if (i == 3) // right
    Mouse.move(mouseReaction, 0);
}

void button_(byte i) {
  if (i == 0) // up
    //Keyboard.write('w');
    Keyboard.press('w');
  if (i == 1) // down
    Keyboard.press('s');
  if (i == 2) // left
    Keyboard.press('a');
  if (i == 3) // right
    Keyboard.press('d');
  if (i == 4) // mouseLeft
    Mouse.click(MOUSE_LEFT);
  if (i == 5) // jumpButton
    Keyboard.press(' ');
}

void button_check() {
  for ( byte i = 0; i < 6; i++) {
    // check buttons states for move the body
    button_read = digitalRead(Button[i]);
    // check buttons states for move the eyes
    mouse_read = digitalRead(mouse[i]);
    if (button_read == LOW) {
      //Serial.println("ok");
      button_(i);
      delay(responseDelay);
      Keyboard.releaseAll();
    }
    if (mouse_read == LOW && i < 4) {
      //Serial.println("ok");
      delay(responseDelay);
      mouse_(i);
    }
  }
}
