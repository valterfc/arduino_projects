//by ValterFC
//https://github.com/valterfc

#include <Adafruit_NeoPixel.h> 

// Define
#define NUM_LEDS 1  //WS2812B - Number of LEDS
//#define LED_PIN 0 //LED on Model B
#define LED_PIN 1   //LED on Model A

#define DATA_PIN 2  //output pin -----> WS2812B Data IN
#define RASP_PIN 0  //input pin <----- Raspberry Pi UART TX

int raspVal = 0;
int colorTime = 200; //50

// Start Strip
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

int ledCTRL = 0;

void setup() {
    //---------------------------------------------------------------
    //test without Raspberry (Pull UP Pin to use - only for test)
    //PIN 5 pull up (+) -----(RESISTOR  -----> RASP_PIN (PIN 0) (-)
    //pinMode(5, OUTPUT); // initialize the digital pin as an output
    //digitalWrite(5, HIGH); // pull up
    //---------------------------------------------------------------

    pinMode(LED_PIN , OUTPUT); // initialize the digital pin as an output
    pinMode(RASP_PIN, INPUT ); // initialize input
    digitalWrite(RASP_PIN, LOW); // pull down

    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    setColorRED(); //default color
}

void loop() {
    raspVal = digitalRead(RASP_PIN); // read the input pin from Raspberry Pi

    //blink LED if NOT Raspberry Value / turn on if Raspberry Value
    if ((ledCTRL == 0) || (raspVal == HIGH)) {
      digitalWrite(LED_PIN, HIGH); // turn the LED on (HIGH is the voltage level)
      ledCTRL = 1;
    } else {
      digitalWrite(LED_PIN, LOW);  // turn the LED off (LOW is 0 level)
      ledCTRL = 0;
    }

    //LED WS2812B - blink if Raspberry Value / turn RED if NOT Raspberry Value (Halt / Not Connected)
    if (raspVal == HIGH) {
      // choose a pattern
      pickPattern();
    } else {
      setColorRED();
    }

    //delay(500);
    //delay(50);
}

/* pick a pattern */
void pickPattern() {
    // scanner, color and delay - RGB
    //scanner(strip.Color(0,255,0),colorTime);
    //scanner(strip.Color(200,0,100),colorTime);
    //scanner(strip.Color(64,0,200),colorTime);

    //https://www.rapidtables.com/web/color/blue-color.html
    scanner(strip.Color(0,191,255),colorTime);   //deepskyblue
    scanner(strip.Color(30,144,255),colorTime);  //dodgerblue
    scanner(strip.Color(0,0,255),colorTime);     //blue
    
    //https://www.rapidtables.com/web/color/orange-color.html
    scanner(strip.Color(255,215,0),colorTime);   //gold
    scanner(strip.Color(255,165,0),colorTime);   //orange
    scanner(strip.Color(255,140,0),colorTime);   //darkorange
    
    //https://www.rapidtables.com/web/color/green-color.html
    scanner(strip.Color(0,255,0),colorTime);     //lime
    scanner(strip.Color(0,128,0),colorTime);     //green
    scanner(strip.Color(0,100,0),colorTime);     //darkgreen
}

// reset Color
void resetColor() {
  strip.setPixelColor(0,0);
  strip.show();
}

void setColorRED() {
  //resetColor();
  strip.setPixelColor(0,strip.Color(255,0,0)); //color RED
  strip.show();
  delay(colorTime);
}

// scanner
void scanner(uint32_t c,uint8_t wait) {
  resetColor();
  strip.setPixelColor(0,c);
  strip.show();
  delay(wait);

  resetColor();
  strip.setPixelColor(0,c);
  strip.show();
  delay(wait);
}

