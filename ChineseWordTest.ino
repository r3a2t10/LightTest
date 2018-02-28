#include "Arduino.h"
#include "SoftwareSerial.h"
#include <FastLED.h>
#include <SPI.h>
#include <SD.h>

#define LED_TYPE    WS2812B
#define DATA_PIN    3       // Data pin led data written out
#define COLOR_ORDER GRB     // Impact the show of the color
#define BRIGHTNESS  2
#define SPACE       20      // devide how many leds a block
#define NUM_LEDS    200     // How many leds in the strip
CRGB leds[NUM_LEDS];        // Array of leds

#define DISPLAYTIME        5  //display an effect for how long
#define FRAMES_PER_SECOND  120 //frames per second

#define COLORSTRINGLEN 51
File myFile;

void setup() { 
  delay(2000);// power-up safety delay
  Serial.begin(9600);
  Serial.println(F("resetting"));
  LEDS.addLeds<LED_TYPE,DATA_PIN,GRB>(leds,NUM_LEDS).setCorrection(TypicalLEDStrip);;
  LEDS.setBrightness(BRIGHTNESS);

  
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { WhitePurple,
                                //Jungle,
                                //MiddleOut,
                                //Blink,
                                //SparkSlowToFast,
                                //GlowGradient,
                                //Confetti,
                                //Sinelon,
                                //NTHUpattern, 
                                ChineseWord
                                };
                                
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

void loop() { 

    // Call the current pattern function once, updating the 'leds' array
     gPatterns[gCurrentPatternNumber]();

    // insert a delay to keep the framerate modest
    FastLED.delay(1000/FRAMES_PER_SECOND); 

    // change patterns periodically
     EVERY_N_SECONDS( DISPLAYTIME ) { 
       ClearAll();
       nextPattern(); } 
   
    //WhitePurple();
    //Jungle();
    //MiddleOut();
    //Blink();
    //SparkSlowToFast();
    //GlowGradient();
    //Confetti();
    //Sinelon();
    //NTHUpattern();
    //ClearAll();
  
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void WhitePurple() {
  
  ClearAll();
  LEDS.setBrightness(random(30,50));
  // First slide the led in one direction
  for(int z=2;z>0;z--){
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

  for(int z=2;z>0;z--){
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
  Serial.println(F("WhitePurple():done!"));
  
}

void Jungle() {
  
  ClearAll();
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
  
  ClearAll();
  LEDS.setBrightness(random(30,50));

  for(int i = 1; i < NUM_LEDS/4 ; i++){
    leds[NUM_LEDS/2+i] = CRGB::DarkOrchid;
    leds[NUM_LEDS/2-i] = CRGB::DarkOrchid;
    FastLED.show(); 
    delay(10);
  }
  for(int i = 1; i < NUM_LEDS/4 ; i++){
    leds[NUM_LEDS/4*3+i] = CRGB::MediumSlateBlue;
    leds[NUM_LEDS/4-i] = CRGB::MediumSlateBlue;
    FastLED.show(); 
    delay(5);
  }
  for(int i = 1; i < NUM_LEDS/4 ; i++){
    leds[NUM_LEDS/2+i] = CRGB::Black;
    leds[NUM_LEDS/2-i] = CRGB::Black;
    FastLED.show(); 
    delay(20);
  }
  for(int i = 1; i < NUM_LEDS/4 ; i++){
    leds[NUM_LEDS/2+i] = CRGB::DarkSalmon;
    leds[NUM_LEDS/2-i] = CRGB::DarkSalmon;
    FastLED.show(); 
    delay(15);
  }
  for(int i = 1; i < NUM_LEDS/2 ; i++){
    leds[NUM_LEDS-i] = CRGB::Black;
    leds[i] = CRGB::Black;
    FastLED.show(); 
    delay(10);
  }
  for(int i = 1; i < NUM_LEDS/4 ; i++){
    leds[NUM_LEDS-i] = CRGB::MediumSlateBlue;
    leds[NUM_LEDS/2+i] = CRGB::MediumSlateBlue;
    leds[NUM_LEDS/2-i] = CRGB::MediumSlateBlue;
    leds[i] = CRGB::MediumSlateBlue;
    FastLED.show(); 
    delay(20);
  }
  for(int i = 1; i < NUM_LEDS/4 ; i++){
    leds[NUM_LEDS-i] = CRGB::Black;
    leds[NUM_LEDS/2+i] = CRGB::Black;
    leds[NUM_LEDS/2-i] = CRGB::Black;
    leds[i] = CRGB::Black;
    FastLED.show(); 
    delay(10);
  }
  for(int i = 1; i < NUM_LEDS/4 ; i++){
    leds[NUM_LEDS/4-i] = CRGB::Gray;
    leds[NUM_LEDS/4+i] = CRGB::Gray;
    leds[NUM_LEDS/4*3-i] = CRGB::Gray;
    leds[NUM_LEDS/4*3+i] = CRGB::Gray;
    FastLED.show(); 
    delay(10);
  }
  
  
  
}

void Blink(){
  
  ClearAll();
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

  ClearAll();
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

  ClearAll();
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
  ClearAll();
  LEDS.setBrightness(random(30,50));
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
  for(int j = 5; j >0 ; j-- ){
    ClearAll();
    LEDS.setBrightness(random(30,50));
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
}

void fadeall() { 
  for(int i = 0; i < NUM_LEDS; i++) { 
      leds[i].nscale8(1000); }
}

void NTHUpattern(){

  ClearAll();
  LEDS.setBrightness(20);
  
  int dDevideIn = 5;
  int delaytime = 150;

  int bound_0 = NUM_LEDS/5*0;
  int bound_1 = NUM_LEDS/5*1;
  int bound_2 = NUM_LEDS/5*2;
  int bound_3 = NUM_LEDS/5*3;
  int bound_4 = NUM_LEDS/5*4;
  int bound_5 = NUM_LEDS/5*5;
  
  fill_solid(leds,NUM_LEDS,0);
  FastLED.show(); 
  delay(delaytime*10);
  //====================================
  //N:
  //1
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_5,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //2
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_1,CRGB::Purple,bound_2,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //3
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_2,CRGB::Purple,bound_3,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //4
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_3,CRGB::Purple,bound_4,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //5
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_5,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //====================================
  fill_solid(leds,NUM_LEDS,0);
  FastLED.show(); 
  delay(delaytime);
  delay(delaytime);
  //====================================
  //T:
  //1
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_1,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //2
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_1,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //3
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_5,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //4
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_1,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //5
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_1,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //====================================
  fill_solid(leds,NUM_LEDS,0);
  FastLED.show(); 
  delay(delaytime);
  delay(delaytime);
  //====================================
  //H:
  //1
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_5,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //2
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_2,CRGB::Purple,bound_3,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //3
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_2,CRGB::Purple,bound_3,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //4
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_2,CRGB::Purple,bound_3,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //5
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_5,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //====================================
  fill_solid(leds,NUM_LEDS,0);
  FastLED.show(); 
  delay(delaytime);
  delay(delaytime);
  //====================================
  //U:
  //1
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_5,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //2
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_4,CRGB::Purple,bound_5,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //3
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_4,CRGB::Purple,bound_5,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //4
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_4,CRGB::Purple,bound_5,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //5
  fill_solid(leds,NUM_LEDS,0);
  fill_gradient_RGB(leds,bound_0,CRGB::Purple,bound_5,CRGB::Purple);
  FastLED.show(); delay(delaytime);
  //====================================
  fill_solid(leds,NUM_LEDS,0);
  FastLED.show();
  delay(delaytime*10);
}

void ChineseWord(){

  readSD();
  Serial.println(F("ChineseWord():done!"));
  
}

void readSD(){

  
  
  myFile = SD.open("test.txt");
  if (myFile) {
    //Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      String colorstring = "";
      colorstring = myFile.readStringUntil('\n');
      Serial.println(colorstring);
      char  buf[COLORSTRINGLEN];
      int   len=COLORSTRINGLEN;
      colorstring.toCharArray(buf, len);

      // make char to int
      //int a = (buf[9]-'0') + (buf[10]-'0');
      //Serial.print(F("a:"));Serial.println(a);
      
      //for(int y=0;y<colorstring.length();y++){
      //  Serial.print(y);Serial.print(":");Serial.println(buf[y]);
      //}
      
      CRGB tmp = CRGB::Black;
      int delaytime = 150;
      
      fill_solid(leds,NUM_LEDS,0);
      for(int x=0;x<colorstring.length();x++){//run buf & light
          if((buf[x]-'0') == 0){tmp = CRGB::Black;}
          else {tmp = CRGB::Purple;}
          //int bound_0 = NUM_LEDS/colorstring.length()*x;
          //int bound_1 = NUM_LEDS/colorstring.length()*(x+1);
          //fill_gradient_RGB(leds,bound_0,tmp,bound_1,tmp); 
          fill_solid(leds+NUM_LEDS/colorstring.length()*x,NUM_LEDS/colorstring.length(),tmp);
      }
      FastLED.show();//delay(delaytime);
    }
    // close the file:
    myFile.close();
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  
}

void ClearAll() {
  fill_solid(leds,NUM_LEDS,0);
  //FastLED.show();
}
