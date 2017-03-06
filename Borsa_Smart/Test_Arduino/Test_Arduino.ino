/* Author: Davide Gariselli for Girl Code It Better Course.
   In testing V0.5
   Borsa Smart con colori decisi dai gruppi.
   
   GEMMA Adafruit Black PCB.
   Board: Adafruit Gemma 8MHz
   Programmer: USBtinyISP
   It does not need a selected port.

   Note that you need to press the button once to start the first animation!
*/

#include <Adafruit_NeoPixel.h>
//--------------------------------------
#define ngruppi 4

#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
// driven with a pull-up resistor so the switch should
// pull the pin to ground momentarily.  On a high -> low
// transition the button press logic will execute.

#define PIXEL_PIN    1    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 10
//---------------------------------------
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;
int wait = 50;

// RGB to 32bit : http://goo.gl/Du7X1
// int = 16bit , long = 32bit
// maximum 32bit array dimension argument is 12, SRAM. For that example the array dimension is 10
//uint32_t spento[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // uncommet for wipe off
uint32_t gruppo1[] = {14745600, 16744448, 16774912, 65289, 65399, 50431, 2559, 5570815, 8978687, 16711927}; // 5 Super Girls
uint32_t gruppo2[] = {16711680, 16735744, 16776960, 65280, 65535, 255, 5242960, 39679, 1138786, 16777215}; // best tecnology girls
uint32_t gruppo3[] = {835752, 13238497, 14803200, 14745712, 57637, 7340257, 16721422, 35993, 3014403, 206335}; // REALLY FASHION COSTANZA
uint32_t gruppo4[] = {12125445, 16535552, 12893440, 587631, 208917, 16740003, 66368, 2406878, 2290, 5177394}; // hight tecnology girls


void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.setBrightness(64);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      showType++;
      if (showType > ngruppi)
        showType = 0;
      startShow(showType);
    }
  }

  // Set the last button state to the old state.
  oldState = newState;
}

void startShow(int i) {
  switch (i) {
    case 0: // Initialize all pixels to 'off'
      //colorWipeAll(spento); //uncommet for wipe off & comment the next two lines
      strip.clear();
      strip.show();
      break;
    case 1: colorWipeAll(gruppo1);
      break;
    case 2: colorWipeAll(gruppo2);
      break;
    case 3: colorWipeAll(gruppo3);
      break;
    case 4: colorWipeAll(gruppo4);
      break;
  }
}

void colorWipeAll(uint32_t gruppo[]) {
  uint8_t j = 0;
  uint8_t i = 0;
  for (i, j; j < strip.numPixels(); j++, i++) {
    if (i == 10) i = 0;
    strip.setPixelColor(j, gruppo[i]);
    strip.show();
    delay(wait);
  }
}
