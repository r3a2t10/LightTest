#include <FastLED.h>

#define LED_TYPE    WS2812B
#define DATA_PIN    3       // Data pin led data written out
#define COLOR_ORDER GRB     // Impact the show of the color
#define BRIGHTNESS  5
#define SPACE       14      // devide how many leds a block
#define NUM_LEDS    140     // How many leds in the strip
CRGB leds[NUM_LEDS];        // Array of leds

#define DISPLAYTIME        10  //display an effect for how long
#define FRAMES_PER_SECOND  120 //frames per second

void setup() { 
  delay(2000);// power-up safety delay
  Serial.begin(9600);
  Serial.println("resetting");
  LEDS.addLeds<LED_TYPE,DATA_PIN,GRB>(leds,NUM_LEDS).setCorrection(TypicalLEDStrip);;
  LEDS.setBrightness(BRIGHTNESS);
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { WhitePurple,
                                Jungle,
                                MiddleOut,
                                Blink,
                                SparkSlowToFast,
                                GlowGradient,
                                Confetti,
                                Sinelon };
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

void loop() { 

   // Call the current pattern function once, updating the 'leds' array
    gPatterns[gCurrentPatternNumber]();

    // insert a delay to keep the framerate modest
    FastLED.delay(1000/FRAMES_PER_SECOND); 

    // change patterns periodically
    EVERY_N_SECONDS( DISPLAYTIME ) { nextPattern(); } 
   
    //WhitePurple();
    //Jungle();
    //MiddleOut();
    //Blink();
    //SparkSlowToFast();
    //GlowGradient();
    //Confetti();
    //Sinelon();
    //ClearAll();
  
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void WhitePurple() {

  // First slide the led in one direction
  for(int z=5;z>0;z--){
      for(int i = 0; i < SPACE; i++) {
        for(int j=0;j<NUM_LEDS/SPACE;j++){
          if(j%2==0)leds[i+SPACE*j] = CRGB::White;
          else      leds[i+SPACE*j] = CRGB::Purple;
          FastLED.show(); 
          delay(1);
          fadeall();
        }
      }
  }

  for(int z=5;z>0;z--){
      for(int i = 0; i < SPACE; i++) {
        for(int j=0;j<NUM_LEDS/SPACE;j++){
          if(j%2==0)leds[SPACE*(j+1)-i] = CRGB::White;
          else      leds[SPACE*(j+1)-i] = CRGB::Purple;
          FastLED.show(); 
          delay(1);
          fadeall();
        }
      }
  }
  
}

void Jungle() {
  
  //dark to light
  for(int i = 1; i < 60 ; i=i+1){
    fadeToBlackBy( leds, NUM_LEDS, 20);
    byte dothue = 430;
    for( int i = 0; i < 8; i++) {
      leds[beatsin16( i+9, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
      dothue += 1;//select the color purple
    }
    //add some glitter
    if(random8()<40)leds[ random8(NUM_LEDS) ] += CRGB::White;
    //set dynamic bright
    LEDS.setBrightness(i);
    FastLED.show(); 
  }

  //light to dark
  for(int i = 60; i > 1 ; i=i-1){
    fadeToBlackBy( leds, NUM_LEDS, 20);
    byte dothue = 430;
    for( int i = 0; i < 10; i++) {
      leds[beatsin16( i+9, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
      dothue += 1;//select the color purple
    }
    //add some glitter
    if(random8()<40)leds[ random8(NUM_LEDS) ] += CRGB::White;
    //set dynamic bright
    LEDS.setBrightness(i);
    FastLED.show(); 
  }
  
}

void MiddleOut() {
  
  LEDS.setBrightness(random(30,50));
  for(int i = 0; i < NUM_LEDS/4 ; i++){
    leds[NUM_LEDS/2+i] = CRGB::DarkOrchid;
    leds[NUM_LEDS/2-i] = CRGB::DarkOrchid;
    FastLED.show(); 
    delay(10);
  }
  for(int i = 0; i < NUM_LEDS/4+1 ; i++){
    leds[NUM_LEDS/4*3+i] = CRGB::MediumSlateBlue;
    leds[NUM_LEDS/4-i] = CRGB::MediumSlateBlue;
    FastLED.show(); 
    delay(5);
  }
  for(int i = 0; i < NUM_LEDS/4+1 ; i++){
    leds[NUM_LEDS/2+i] = CRGB::Black;
    leds[NUM_LEDS/2-i] = CRGB::Black;
    FastLED.show(); 
    delay(20);
  }
  for(int i = 0; i < NUM_LEDS/4+1 ; i++){
    leds[NUM_LEDS/2+i] = CRGB::DarkSalmon;
    leds[NUM_LEDS/2-i] = CRGB::DarkSalmon;
    FastLED.show(); 
    delay(15);
  }
  
  for(int i = 0; i < NUM_LEDS/2 ; i++){
    leds[NUM_LEDS-i] = CRGB::Black;
    leds[i] = CRGB::Black;
    FastLED.show(); 
    delay(10);
  }
  for(int i = 0; i < NUM_LEDS/4+1 ; i++){
    leds[NUM_LEDS-i] = CRGB::MediumSlateBlue;
    leds[NUM_LEDS/2+i] = CRGB::MediumSlateBlue;
    leds[NUM_LEDS/2-i] = CRGB::MediumSlateBlue;
    leds[i] = CRGB::MediumSlateBlue;
    FastLED.show(); 
    delay(20);
  }
  for(int i = 0; i < NUM_LEDS/4+1 ; i++){
    leds[NUM_LEDS-i] = CRGB::Black;
    leds[NUM_LEDS/2+i] = CRGB::Black;
    leds[NUM_LEDS/2-i] = CRGB::Black;
    leds[i] = CRGB::Black;
    FastLED.show(); 
    delay(10);
  }
  for(int i = 0; i < NUM_LEDS/4+1 ; i++){
    leds[NUM_LEDS/4-i] = CRGB::Gray;
    leds[NUM_LEDS/4+i] = CRGB::Gray;
    leds[NUM_LEDS/4*3-i] = CRGB::Gray;
    leds[NUM_LEDS/4*3+i] = CRGB::Gray;
    FastLED.show(); 
    delay(10);
  }
  
}

void Blink(){
  fill_solid(leds,NUM_LEDS,0);
  for(int i = 0; i < 6 ; i++){
    leds[ random8(NUM_LEDS) ] += CRGB::White;
    leds[ random8(NUM_LEDS) ] += CRGB::Purple;
    leds[ random8(NUM_LEDS) ] += CRGB::DarkOrchid;
    LEDS.setBrightness(random(1,61));
  }
  FastLED.show(); 
  delay(25);
}

void GlowGradient(){
  
  //fill_gradient(leds,0, CHSV(50,255,255) ,NUM_LEDS-1, CHSV(150,255,255), SHORTEST_HUES);
  for(int i = 1; i < 60 ; i=i+1){
    fill_gradient_RGB(leds,0, CRGB::Purple ,NUM_LEDS-1, CRGB::Grey);
    for(int y=10;y>0;y--)leds[ random8(NUM_LEDS) ] = CRGB::Black;
    LEDS.setBrightness(i);
    FastLED.show();
    delay(10); 
  }
  for(int i = 59; i >0 ; i=i-1){
    fill_gradient_RGB(leds,0,CRGB::Purple,NUM_LEDS-1,CRGB::Grey);
    for(int y=10;y>0;y--)leds[ random8(NUM_LEDS) ] = CRGB::Black;
    LEDS.setBrightness(i);
    FastLED.show();
    delay(10); 
  }
  for(int i = 1; i < 60 ; i=i+1){
    fill_gradient_RGB(leds,0, CRGB::Gray ,NUM_LEDS-1, CRGB::Purple);
    for(int y=10;y>0;y--)leds[ random8(NUM_LEDS) ] = CRGB::Black;
    LEDS.setBrightness(i);
    FastLED.show();
    delay(10); 
  }
  for(int i = 59; i >0 ; i=i-1){
    fill_gradient_RGB(leds,0,CRGB::Gray,NUM_LEDS-1,CRGB::Purple);
    for(int y=10;y>0;y--)leds[ random8(NUM_LEDS) ] = CRGB::Black;
    LEDS.setBrightness(i);
    FastLED.show();
    delay(10); 
  }
}

void SparkSlowToFast(){
  
  for(int j = 2; j >0 ; j-- ){

          for(int i = 1; i < 60 ; i=i+1){
            fill_gradient_RGB(leds,0, CRGB::Purple ,NUM_LEDS-1, CRGB::Gray);
            LEDS.setBrightness(i);
            FastLED.show();
            delay(j); 
          }
          delay(j*10);
          for(int i = 1; i < 60 ; i=i+1){
            fill_gradient_RGB(leds,0, CRGB::Gray ,NUM_LEDS-1, CRGB::Purple);
            LEDS.setBrightness(i);
            FastLED.show();
            delay(j); 
          }
          delay(j*10);
          for(int i = 1; i < 60 ; i=i+1){
            fill_gradient_RGB(leds,0, CRGB::Purple ,NUM_LEDS/2, CRGB::Gray);
            fill_gradient_RGB(leds,NUM_LEDS/2, CRGB::Gray ,NUM_LEDS, CRGB::Purple);
            LEDS.setBrightness(i);
            FastLED.show();
            delay(j); 
          }
          delay(j*10);
          for(int i = 1; i < 60 ; i=i+1){
            fill_gradient_RGB(leds,0, CRGB::Gray ,NUM_LEDS/2, CRGB::Purple);
            fill_gradient_RGB(leds,NUM_LEDS/2, CRGB::Purple ,NUM_LEDS, CRGB::Gray);
            LEDS.setBrightness(i);
            FastLED.show();
            delay(j); 
          }
          delay(j*10);
          for(int i = 1; i < 60 ; i=i+1){
            fill_gradient_RGB(leds,0, CRGB::Purple ,NUM_LEDS/4, CRGB::Gray);
            fill_gradient_RGB(leds,NUM_LEDS/4, CRGB::Gray ,NUM_LEDS/2, CRGB::Purple);
            fill_gradient_RGB(leds,NUM_LEDS/2, CRGB::Purple ,NUM_LEDS/4*3, CRGB::Gray);
            fill_gradient_RGB(leds,NUM_LEDS/4*3, CRGB::Gray ,NUM_LEDS, CRGB::Purple);
            LEDS.setBrightness(i);
            FastLED.show();
            delay(j); 
          }
          delay(j*10);
          for(int i = 1; i < 60 ; i=i+1){
            fill_gradient_RGB(leds,0, CRGB::Gray ,NUM_LEDS/4, CRGB::Purple);
            fill_gradient_RGB(leds,NUM_LEDS/4, CRGB::Purple ,NUM_LEDS/2, CRGB::Gray);
            fill_gradient_RGB(leds,NUM_LEDS/2, CRGB::Gray ,NUM_LEDS/4*3, CRGB::Purple);
            fill_gradient_RGB(leds,NUM_LEDS/4*3, CRGB::Purple ,NUM_LEDS, CRGB::Gray);
            LEDS.setBrightness(i);
            FastLED.show();
            delay(j); 
          }
          delay(j*10);
          for(int i = 1; i < 60 ; i=i+1){
            for(int z=0;z<8;z++){
              if(z%2==0) fill_gradient_RGB(leds,NUM_LEDS/8*z , CRGB::Gray   ,NUM_LEDS/8*(z+1)  , CRGB::Purple);
              else       fill_gradient_RGB(leds,NUM_LEDS/8*z , CRGB::Black   ,NUM_LEDS/8*(z+1)  , CRGB::Black);
            }
            LEDS.setBrightness(i);
            FastLED.show();
            delay(j); 
          }
          delay(j*10);
          for(int i = 1; i < 60 ; i=i+1){
            for(int z=0;z<8;z++){
              if(z%2==0) fill_gradient_RGB(leds,NUM_LEDS/8*z , CRGB::Black   ,NUM_LEDS/8*(z+1)  , CRGB::Black);
              else       fill_gradient_RGB(leds,NUM_LEDS/8*z , CRGB::Purple   ,NUM_LEDS/8*(z+1)  , CRGB::Gray);
            }
            LEDS.setBrightness(i);
            FastLED.show();
            delay(j); 
          }
          delay(j*10);
    
  }
  
}

void Confetti() 
{
  LEDS.setBrightness(random(5,30));
  uint8_t gHue = 440; //near purple
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 4);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(30), 200+ random8(64), 255);
  FastLED.show(); 
  //delay(5);
}

void Sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 10);
  //fadeToBlackBy(leds,num_led,x):x=fade out time,if smaller fade out slower
  //beatsin16(x,low,high):x=bigger faster
  int pos1 = beatsin16( 20, 0, NUM_LEDS);
  leds[pos1] += CRGB::Purple;
  int pos2 = beatsin16( 20, 0, NUM_LEDS);
  leds[NUM_LEDS-1-pos2] += CRGB::White;
  FastLED.show(); 
  delay(10);
}

void fadeall() { 
  for(int i = 0; i < NUM_LEDS; i++) { 
      leds[i].nscale8(1000); }
}

void ClearAll() {
  for(int i = 0; i < NUM_LEDS ; i++){
    leds[i] = CRGB::Black;
    FastLED.show(); 
  }
}
