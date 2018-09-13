#include <Adafruit_NeoPixel.h> 

// Define
#define NUM_LEDS 30 //30 LED'S per strip
#define DATA_PIN 1  //output pin on ATTiny85

// Init Vars
uint8_t j = 0;
uint8_t direction=1;

// Start Strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

#ifdef __AVR__
  #include <avr/power.h>
#endif

int contador = 0;
int colorTime = 500;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  
    // initialize the digital pin as an output.
    //pinMode(0, OUTPUT); //LED on Model B
    pinMode(1, OUTPUT); //LED on Model A   

    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() {
    if (contador == 0)
    {
      //digitalWrite(0, HIGH);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(1, HIGH);
      contador = 1;
    } else {
      //digitalWrite(0, LOW);   // turn the LED on (HIGH is the voltage level)
      digitalWrite(1, LOW);
      contador = 0;
    }

    // choose a pattern
    //pickPatternOnePixel();
    colorEvenOdd();

    // set direction
    if (direction == 1) { j++;  } else {  j--; }

    if (j > 254) { direction = 0; }
    if (j < 1) { direction = 1; }   
}

/* pick a pattern */
void pickPatternOnePixel() {
    //https://www.rapidtables.com/web/color/Yellow_Color.html

    // CONTINUOUS
    // scanner, color and delay - RGB
    scanner(strip.Color(0,128,0),colorTime);     //green
    scanner(strip.Color(255,255,0),colorTime);   //yellow
    //
    scanner(strip.Color(0,100,0),colorTime);     //darkgreen
    scanner(strip.Color(255,215,0),colorTime);   //gold

    // HALF
    // scanner, color and delay - RGB
    scannerHalf(strip.Color(0,128,0),colorTime);     //green
    scannerHalf(strip.Color(255,255,0),colorTime);   //yellow
    //
    scannerHalf(strip.Color(0,100,0),colorTime);     //darkgreen
    scannerHalf(strip.Color(255,215,0),colorTime);   //gold
}

void colorEvenOdd() {
    uint32_t colorGreen;
    uint32_t colorYellow;

    colorGreen  = strip.Color(0,128,0);   //green
    colorYellow = strip.Color(255,255,0); //yellow

    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        if ( (i % 2) == 0) {
          strip.setPixelColor(i, colorGreen);
        } else {
          strip.setPixelColor(i, colorYellow);
        }
    }
    strip.show();
    delay(colorTime);

    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        if ( (i % 2) == 0) {
          strip.setPixelColor(i, colorYellow);
        } else {
          strip.setPixelColor(i, colorGreen);
        }
    }
    strip.show();
    delay(colorTime);
}


// fast version 
void colorFast(uint32_t c, uint8_t wait) {
    for (uint16_t i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, c);
    }
    strip.show();
    delay(wait);
}

// scanner
void scanner(uint32_t c,uint8_t wait) {
        for(int i=0; i< strip.numPixels(); i++) {
            colorFast(0,0);
            strip.setPixelColor(i,c);
            strip.show();
            delay(wait);
        }
        for(int i=strip.numPixels(); i>0; i--) {
            colorFast(0,0);
            strip.setPixelColor(i,c);
            strip.show();
            delay(wait);
        }    
}

// scanner
void scannerHalf(uint32_t c,uint8_t wait) {
    uint8_t k = 0;

    k = strip.numPixels();
    for(int i=0; i< (strip.numPixels() / 2); i++) {
        colorFast(0,0);
        strip.setPixelColor(i,c);
        strip.show();
    
        k--;
        strip.setPixelColor(k,c);

        strip.show();
        delay(wait);
    }

    k = (strip.numPixels() / 2) + 1;
    for(int i=(strip.numPixels() / 2) - 1; i>1; i--) {
        colorFast(0,0);
        strip.setPixelColor(i,c);
        strip.show();
    
        k++;
        strip.setPixelColor(k,c);

        strip.show();
        delay(wait);
    }
}

