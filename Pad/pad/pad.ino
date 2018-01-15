/*  Pads - Girls code it better 2017/18
    Board: Pro Micro - 5V/16MHz ( https://goo.gl/ktnDG2 )
    DaveCalaway ( https://goo.gl/UdFf25 )
*/

#include "Keyboard.h"
#include "Mouse.h"

// buttons
const int upButton = 2;
const int downButton = 3;
const int leftButton = 4;
const int rightButton = 5;
// mouse
const int mouseLeft = 6;
const int upMouse = 7;
const int downMouse = 8;
const int leftMouse = 9;
const int rightMouse = 10;
const int jumpButton = 14;

const int responseDelay = 50;

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

  Serial.begin(9600);
  // initialize mouse control:
  Mouse.begin();
  Keyboard.begin();
}

void loop() {
  // check buttons states for move the body
  for ( byte i = 0; i < 6; i++) {
    button_read = digitalRead(Button[i]);
    if (button_read == LOW) {
      Serial.println("ok");
      delay(responseDelay);
      button_(i);
    }
  }
  // check buttons states for move the eyes
  for ( byte i = 0; i < 4; i++) {
    mouse_read = digitalRead(mouse[i]);
    if (mouse_read == LOW) {
      //Serial.println("ok");
      delay(responseDelay);
      mouse_(i);
    }
  }

}

void mouse_(byte i) {
  if (i == 0) // up
    Mouse.move(0, -40);
  if (i == 1) // down
    Mouse.move(0, 40);
  if (i == 2) // left
    Mouse.move(-40, 0);
  if (i == 3) // right
    Mouse.move(40, 0);
}

void button_(byte i) {
  if (i == 0) // up
    Keyboard.write('w');
  if (i == 1) // down
    Keyboard.write('s');
  if (i == 2) // left
    Keyboard.write('a');
  if (i == 3) // right
    Keyboard.write('d');
  if (i == 4) // mouseLeft
    Mouse.click(MOUSE_LEFT);
  if (i == 5) // jumpButton
    Keyboard.write(' ');
}

