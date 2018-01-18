#include <FastLED.h>

#define LED_TYPE    WS2812B
#define DATA_PIN    3       // Data pin led data written out
#define COLOR_ORDER GRB     // Impact the show of the color
#define BRIGHTNESS  5
#define NUM_LEDS    140     // How many leds in the strip
CRGB leds[NUM_LEDS];        // Array of leds

#define SPACE 14

uint8_t gHue = 0; // rotating "base color" used by many of the patterns

void setup() { 
  delay(2000);// power-up safety delay
  Serial.begin(9600);
  Serial.println("resetting");
  LEDS.addLeds<LED_TYPE,DATA_PIN,GRB>(leds,NUM_LEDS);
  LEDS.setBrightness(BRIGHTNESS);
}

void fadeall() { 
  for(int i = 0; i < NUM_LEDS; i++) { 
      leds[i].nscale8(230); }
}

void loop() { 

  //WhitePurple();
  //Jungle();
  //MiddleOut();
  //Blink();
  //SparkSlowToFast();
  //GlowGradient();
  //BeatsPerMinute();
  //Confetti();
  Sinelon();
  //ClearAll();
  
}

void WhitePurple() {

  // First slide the led in one direction
  for(int i = 0; i < SPACE; i++) {
    for(int j=0;j<NUM_LEDS/SPACE;j++){
      if(j%2==0)leds[i+SPACE*j] = CRGB::White;
      else      leds[i+SPACE*j] = CRGB::Purple;
      
    }
    FastLED.show(); 
    delay(80);
  }

  delay(300);
  for(int i = 0; i < SPACE; i++) {
    for(int j=0;j<NUM_LEDS/SPACE;j++){
      leds[i+SPACE*j] = CRGB::Black;
    }
    FastLED.show(); 
    delay(100);
  }
  
}

void Jungle() {

  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 1;//select the color purple
  }

  FastLED.show(); 
  
}

void MiddleOut() {
  
  for(int i = 0; i < NUM_LEDS/2 ; i++){
    leds[NUM_LEDS/2+i] = CRGB::DarkOrchid;
    leds[NUM_LEDS/2-i] = CRGB::DarkOrchid;
    FastLED.show(); 
    delay(25);
  }
  for(int i = 0; i < NUM_LEDS/2 ; i++){
    leds[NUM_LEDS/2+i] = CRGB::DarkSalmon;
    leds[NUM_LEDS/2-i] = CRGB::DarkSalmon;
    FastLED.show(); 
    delay(25);
  }
  
  for(int i = 0; i < NUM_LEDS/2 ; i++){
    leds[NUM_LEDS-i] = CRGB::Black;
    leds[i] = CRGB::Black;
    FastLED.show(); 
    delay(25);
  }
  for(int i = 0; i < NUM_LEDS/4+1 ; i++){
    leds[NUM_LEDS-i] = CRGB::MediumSlateBlue;
    leds[NUM_LEDS/2+i] = CRGB::MediumSlateBlue;
    leds[NUM_LEDS/2-i] = CRGB::MediumSlateBlue;
    leds[i] = CRGB::MediumSlateBlue;
    FastLED.show(); 
    delay(25);
  }
  
  
}

void Blink(){
  fill_solid(leds,NUM_LEDS,0);
  for(int i = 0; i < 6 ; i++){
    leds[ random8(NUM_LEDS) ] += CRGB::White;
    leds[ random8(NUM_LEDS) ] += CRGB::Purple;
    leds[ random8(NUM_LEDS) ] += CRGB::DarkOrchid;
  }
  FastLED.show(); 
  delay(25);
}

void GlowGradient(){
  //fill_gradient(leds,0, CHSV(50,255,255) ,NUM_LEDS-1, CHSV(150,255,255), SHORTEST_HUES);
  for(int i = 1; i < 60 ; i=i+1){
    fill_gradient_RGB(leds,0, CRGB::Purple ,NUM_LEDS-1, CRGB::Grey);
    LEDS.setBrightness(i);
    FastLED.show();
    delay(10); 
  }
  for(int i = 59; i >0 ; i=i-1){
    fill_gradient_RGB(leds,0,CRGB::Purple,NUM_LEDS-1,CRGB::Grey);
    LEDS.setBrightness(i);
    FastLED.show();
    delay(10); 
  }
  for(int i = 1; i < 60 ; i=i+1){
    fill_gradient_RGB(leds,0, CRGB::Gray ,NUM_LEDS-1, CRGB::Purple);
    LEDS.setBrightness(i);
    FastLED.show();
    delay(10); 
  }
  for(int i = 59; i >0 ; i=i-1){
    fill_gradient_RGB(leds,0,CRGB::Gray,NUM_LEDS-1,CRGB::Purple);
    LEDS.setBrightness(i);
    FastLED.show();
    delay(10); 
  }
}

void SparkSlowToFast(){
  
  
}
void BeatsPerMinute(){
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
  FastLED.show(); 
  delay(50);
}

void Confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
  FastLED.show(); 
  delay(50);
}

void Sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CRGB::Purple;
  FastLED.show(); 
  delay(10);
}

void ClearAll() {
  for(int i = 0; i < NUM_LEDS ; i++){
    leds[i] = CRGB::Black;
    FastLED.show(); 
  }
}
