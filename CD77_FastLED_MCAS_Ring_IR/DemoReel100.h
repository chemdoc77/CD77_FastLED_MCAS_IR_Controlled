#ifndef DemoReel100.h
#define DemoReel100.h

// This sketch is based on the DemoReel100 SketchFastLED examples Sketch located at:
//https://github.com/FastLED/FastLED/blob/master/examples/DemoReel100/DemoReel100.ino
//It was modified by Chemdoc77.

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few 
// of the kinds of animation patterns you can quickly and easily 
// compose using FastLED.  
//
// This example also shows one easy way to define multiple 
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014

#
#define FRAMES_PER_SECOND  120

//Predeclare functions

void rainbow();
void rainbowWithGlitter();
void addGlitter( fract8 chanceOfGlitter);
void confetti();
void sinelon();
void bpm();
void juggle();
void nextPatterndm100();

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternListdr100[])();
SimplePatternListdr100 gPatternsdr100 = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };


void nextPatterndr100()
{
  // add one to the current pattern number, and wrap around at the end
 gCurrentPatternNumberdr100 = (gCurrentPatternNumberdr100 + 1) % ARRAY_SIZE( gPatternsdr100);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, ghuedr100, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( ghuedr100 + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( ghuedr100, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, ghuedr100+(i*2), beat-ghuedr100+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}





#endif
