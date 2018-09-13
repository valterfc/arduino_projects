#include <Adafruit_NeoPixel.h> 

// Define
#define NUM_LEDS 30 //30 LED'S per strip
#define DATA_PIN 1  //output pin on ATTiny85

// Start Strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

#ifdef __AVR__
  #include <avr/power.h>
#endif

int colorTime = 10000;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  doPaintLEDs();
}

void doPaintLEDs() {
  //https://www.rapidtables.com/web/color/blue-color.html
  //https://www.rapidtables.com/web/color/green-color.html
  
  colorEvenOdd(strip.Color(0,191,255),strip.Color(0,0,139)); //deepskyblue / darkblue
  colorEvenOdd(strip.Color(0,0,255),strip.Color(0,0,139));   //blue / darkblue
  colorEvenOdd(strip.Color(0,128,0),strip.Color(0,100,0));   //green / darkgreen
}

void colorEvenOdd(uint32_t color1, uint32_t color2) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        if ( (i % 2) == 0) {
          strip.setPixelColor(i, color1);
        } else {
          strip.setPixelColor(i, color2);
        }
    }
    strip.show();
    delay(colorTime);

    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        if ( (i % 2) == 0) {
          strip.setPixelColor(i, color2);
        } else {
          strip.setPixelColor(i, color1);
        }
    }
    strip.show();
    delay(colorTime);
}

