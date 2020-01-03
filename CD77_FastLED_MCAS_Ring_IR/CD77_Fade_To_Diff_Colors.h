#ifndef CD77_Fade_To_Diff_Colors.h
#define CD77_Fade_To_Diff_Colors.h

// This sketch by Chemdoc77 is based on Mark Kriegsman's PaletteCrossfade.ino

// at: https://gist.github.com/kriegsman/1f7ccbbfa492a73c015e



uint16_t i_pal=0;
CRGBPalette16 CD77_red_pal_fade(CRGB::Red);
CRGBPalette16 CD77_blue_pal_fade(CRGB::Blue);
CRGBPalette16 CD77_yellow_pal_fade(CRGB::Yellow);
CRGBPalette16 CD77_green_pal_fade(CRGB::Green);
CRGBPalette16 CD77_purple_pal_fade(CRGB::Purple);

CRGBPalette16 CD77_Pallette_Array_fade[]= {CD77_red_pal_fade,CD77_blue_pal_fade,CD77_green_pal_fade,CD77_purple_pal_fade};

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
uint8_t Pal_Array_fade_Size = ARRAY_SIZE(CD77_Pallette_Array_fade);

//========= Declare functions

void CD77_ChangePalettePeriodically_fade( uint16_t wait_Pal_Array_time);
void FillLEDsFromPaletteColors_fade( uint8_t colorIndex);


// This example shows how to cross-fade between different color palettes
// using the function nblendPaletteTowardPalette.
//
// The basic idea is that you always have a "current palette" that you're
// pulling colors from with ColorFromPalette, and you have a "target palette"
// which is the 'next' palette that you want to get to.
// 
// After that, implementation is relatively simple: just periodically call
//   nblendPaletteTowardPalette( currentPalette, targetPalette);
// If the current palette is not yet equal to the target palette, this 
// function will make a few small changes to the current palette to make
// it slightly more like the target.  Over time, the current palette will
// come to be equal to the target.
// There's no need to test the current and target for equality; it's safe
// to keep calling nblendPaletteTowardPalette even after current reaches target.
// For faster blending, call nblendPaletteTowardPalette twice per loop.


CRGBPalette16 currentPalette_fade( CRGB::Black);


CRGBPalette16 targetPalette_fade( CRGBPalette16(CRGB::Red) );


void CD77_Slow_Fade_Pal(uint8_t wait_pal_change, uint16_t UPDATES_PER_SECOND_Fade){
  CD77_ChangePalettePeriodically_fade( wait_pal_change);  // modified by CD77

  // Crossfade current palette slowly toward the target palette
  //
  // Each time that nblendPaletteTowardPalette is called, small changes
  // are made to currentPalette to bring it closer to matching targetPalette.
  // You can control how many changes are made in each call:
  //   - the default of 24 is a good balance
  //   - meaningful values are 1-48.  1=veeeeeeeery slow, 48=quickest
  //   - "0" means do not change the currentPalette at all; freeze
  
  uint8_t maxChanges =  20; //48;//5; //24; 
  nblendPaletteTowardPalette( currentPalette_fade, targetPalette_fade, maxChanges);


  static uint8_t startIndex = 0;
  startIndex = startIndex + 3;//1; /* motion speed */
  FillLEDsFromPaletteColors_fade( startIndex);

 // FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND_Fade);
}

void FillLEDsFromPaletteColors_fade( uint8_t colorIndex)
{
  uint8_t brightness = 255;
  CRGB color=ColorFromPalette( currentPalette_fade, 1, brightness, LINEARBLEND);
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
   // colorIndex += 3;
  }
}


void CD77_ChangePalettePeriodically_fade( uint16_t wait_Pal_Array_time)
{
EVERY_N_SECONDS_I(Array_time, 5){ 
  Array_time.setPeriod( wait_Pal_Array_time );
  i_pal++;
  if (i_pal > Pal_Array_fade_Size-1) {i_pal = 0;}
   targetPalette_fade = CD77_Pallette_Array_fade[i_pal];
  }
  
}














#endif
