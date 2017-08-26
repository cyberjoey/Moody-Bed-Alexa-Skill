#include "neopixel.h" // use for local build

// IMPORTANT: Set pixel PIN, COUNT, and TYPE
// Supported pixel types: WS2812, WS2812B, WS2812B2, WS2811, TM1803, TM1829, SK6812RGBW
#define PIXEL_PIN D1
#define PIXEL_COUNT 30
#define PIXEL_TYPE SK6812RGBW

#define PIXEL_PIN2 D2
#define PIXEL_COUNT2 60
#define PIXEL_TYPE2 WS2812

#define BRIGHTNESS 50 // 0 - 255

Adafruit_NeoPixel ring = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
Adafruit_NeoPixel ring2 = Adafruit_NeoPixel(PIXEL_COUNT2, PIXEL_PIN2, PIXEL_TYPE2);

void setup() {
  Serial.begin(9600);

  ring.setBrightness(BRIGHTNESS);
  ring.begin();
  ring.show(); // Initialize all pixels to 'off'
  ring2.setBrightness(BRIGHTNESS);
  ring2.begin();
  ring2.show(); // Initialize all pixels to 'off'

  Particle.function("state", setLightState);
  Particle.function("color", setLightColor);
  Particle.function("brightness", setLightBrightness);
}

// Uncomment to test the NeoPixel ring
/*void loop() {
  changeColor(ring.Color(0, 255, 0)); // GRB
  ring.show();
}*/

int setLightState(String state) {
  Serial.println("state: " + state);

  if(state == "on") {
    ring.setBrightness(BRIGHTNESS);
    ring2.setBrightness(BRIGHTNESS);
    changeColor(ring.Color(255,255,255)); // GRB+W
    changeColor2(ring2.Color(255,255,255)); // GRB+W
  }
  else if(state == "off") {
    ring.setBrightness(0);
    ring.show();
    ring2.setBrightness(0);
    ring2.show();
  }
}

int setLightColor(String color) {
  Serial.println("color: " + color);

  if(color == "red") {
    changeColor(ring.Color(0, 255, 0)); // GRB
    changeColor2(ring2.Color(255, 0, 0)); // GRB
  }
  else if(color == "green") {
    changeColor(ring.Color(255, 0, 0)); // GRB
    changeColor2(ring2.Color(0, 255, 0)); // GRB
  }
  else if(color == "blue") {
    changeColor(ring.Color(0, 0, 255));
    changeColor2(ring2.Color(0, 0, 255));
  }
  else if(color == "white") {
    changeColor(ring.Color(255, 255, 255)); // GRB+W
    changeColor2(ring2.Color(255, 255, 255)); // GRB+W
  }
  else if(color == "purple") {
    changeColor(ring.Color(0, 255, 255));
    changeColor2(ring2.Color(255, 0, 255));
  }

  else if(color == "relax") {
    changeColor(ring.Color(170, 255, 0));
    changeColor2(ring2.Color(255, 170, 0));
  }
}

int setLightBrightness(String brightness) {
  int brightnessInt = brightness.toInt();

  if(brightnessInt >= 0 && brightnessInt <= 255) {
    Serial.println("brightness: " + brightness);

    ring.setBrightness(brightnessInt);
    ring.show();
    ring2.setBrightness(brightnessInt);
    ring2.show();

    return brightnessInt;
  }
  else {
    Serial.println("Brightness level is invalid");

    return -1;
  }
}

void changeColor(uint32_t color) {
  for(uint16_t i=0; i < PIXEL_COUNT; i++) {
    ring.setPixelColor(i, color);
    ring.show();
  }
}
void changeColor2(uint32_t color) {
  for(uint16_t i=0; i < PIXEL_COUNT2; i++) {
    ring2.setPixelColor(i, color);
    ring2.show();
  }
}
