// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN   8    // Digital IO pin connected to the button.  This will be
// driven with a pull-up resistor so the switch should
// pull the pin to ground momentarily.  On a high -> low
// transition the button press logic will execute.

#define PIXEL_PIN    5    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 120

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int showType = 0;
uint32_t c = strip.Color(0, 0, 0);
int r = 0;
int g = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
}

void loop() {
//  for (int i = 0; i < 2; i++) {
//    breathRed();
//  }
  
  while(digitalRead(BUTTON_PIN)) {
    fillOutIn(0,0,0,60);
    delay(100);
    fillOutIn(255,0,0,60);
    delay(100);
  }

  
  for (int green = 0; green < 200; green = green + 40) {
    for (int i = 0; i < strip.numPixels() / 2; i++) {
      strip.setPixelColor(strip.numPixels() / 2 - i-1, strip.Color(200-green, green, 0));
      strip.setPixelColor(strip.numPixels() / 2 + i, strip.Color(200-green, green, 0));
      strip.show();
      delay(30);
    }
  }
  
  for (int i = 200; i > 50 ; i--) {
    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(0, i, 0));
    }
    strip.show();
    delay(10);
  }


  while (HIGH) {
    breathGreen();
  }

}

void fillInOut(int red, int green, int blue, int wait){

  for (int i = 0; i < strip.numPixels() / 2; i++) {
    strip.setPixelColor(strip.numPixels() / 2 - i-1, strip.Color(red, green, blue));
    strip.setPixelColor(strip.numPixels() / 2 + i, strip.Color(red, green, blue));
    strip.show();
    delay(wait);
  }   
}

void fillOutIn(int red, int green, int blue, int wait){

  for (int i = strip.numPixels() / 2; i > 0; i--) {
    strip.setPixelColor(strip.numPixels() / 2 - i-1, strip.Color(red, green, blue));
    strip.setPixelColor(strip.numPixels() / 2 + i, strip.Color(red, green, blue));
    strip.show();
    delay(wait);
  }    
}

void breathRed() {
  for (int i = 50; i < 225 ; i++) {
    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(i, 0, 0));
    }
    strip.show();
    delay(10);
  }
  for (int i = 225; i > 50; i--) {
    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(i, 0, 0));
    }
    strip.show();
    delay(10);
  }
}

void breathGreen() {
  for (int i = 50; i < 225 ; i++) {
    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(0, i, 0));
    }
    strip.show();
    delay(10);
  }
  for (int i = 225; i > 50; i--) {
    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(0, i, 0));
    }
    strip.show();
    delay(10);
  }
}

void basicFlutter() {
  for (int i = 1; i < 80; i++) {
    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, strip.Color(255, 255, 255));
    }
    strip.show();
    delay(random(20, 200));
    for (int j = 0; j < strip.numPixels(); j++) {
      strip.setPixelColor(j, 0, 0, 0);
    }
    strip.show();
    delay(random(20, 200));
  }
}
