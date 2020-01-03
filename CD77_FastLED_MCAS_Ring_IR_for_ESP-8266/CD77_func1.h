#ifndef CD77_func1.h
#define CD77_func1.h

// Chemdoc77 basic functions 1


void cd77_colorwipe2(CRGB color,  uint8_t wait) {
  for (uint8_t i = 0; i <NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.delay(wait);
  }
    fill_solid( leds, NUM_LEDS, CRGB::Black);  
    FastLED.delay(wait);
}


void cd77_colorwipe(CRGB color,  uint8_t wait) {
  for (uint8_t i = 0; i <NUM_LEDS; i++) {
    leds[i] = color;
    FastLED.delay(wait);
  }
}

//==============================    

void cd77_colorwipe_dot(CRGB color, uint8_t wait) {
  for (uint8_t i = 0; i <NUM_LEDS; i++) {
    leds[i] = color;
   // FastLED.show();
    FastLED.delay(wait);
    leds[i] = CRGB::Black;
    FastLED.show();
   // delay(wait);
    
  }
}

#endif
