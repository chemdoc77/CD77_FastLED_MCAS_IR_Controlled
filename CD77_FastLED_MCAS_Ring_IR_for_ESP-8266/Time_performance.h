#ifndef Time_performance.h
#define Time_performance.h

/*
 
This sketch is based on the Time Performance sketch by Mark Kriegsman of FastLED at:
 https://gist.github.com/kriegsman/a916be18d32ec675fea8
 
*/


#define TC(HOURS,MINUTES,SECONDS) \
  ((uint32_t)(((uint32_t)((HOURS)*(uint32_t)(3600000))) + \
  ((uint32_t)((MINUTES)*(uint32_t)(60000))) + \
  ((uint32_t)((SECONDS)*(uint32_t)(1000)))))


#define AT(HOURS,MINUTES,SECONDS) if( atTC(TC(HOURS,MINUTES,SECONDS)) )
#define FROM(HOURS,MINUTES,SECONDS) if( fromTC(TC(HOURS,MINUTES,SECONDS)) )

static bool atTC( uint32_t tc)
{
  bool maybe = false;
  if( gTimeCode >= tc) {
    if( gLastTimeCodeDoneAt < tc) {
      maybe = true;
      gLastTimeCodeDoneAt = tc;
    }
  }
  return maybe;
}

static bool fromTC( uint32_t tc)
{
  bool maybe = false;
  if( gTimeCode >= tc) {
    if( gLastTimeCodeDoneFrom <= tc) {
      maybe = true;
      gLastTimeCodeDoneFrom = tc;
    }
  }
  return maybe;
} 

void RestartPerformance()
{
  gLastTimeCodeDoneAt = 0;
  gLastTimeCodeDoneFrom = 0;
  gTimeCodeBase = millis();
}


//=========== Performance Functions ===================

void Performance_red_white_dot()
{
   FROM(0,0,00.010)   { cd77_colorwipe_dot(CRGB::Red,  75);}
   FROM(0,0,02.000)   { cd77_colorwipe_dot(CRGB::Grey, 75);}
   AT(0,0,04.000)     { RestartPerformance(); }
   
}
  
void Performance_green_yellow_dot()
{
   FROM(0,0,00.000)   {  cd77_colorwipe_dot(CRGB::Green,  75);}
   FROM(0,0,02.000)   {  cd77_colorwipe_dot(CRGB::Yellow, 75);}
   AT(0,0,04.000)     {  RestartPerformance(); }
  
}

void Performance_red_blue_line()
{
  FROM(0,0,00.000)   { cd77_colorwipe2(CRGB::Red,  75);}
  FROM(0,0,02.000)   { cd77_colorwipe2(CRGB::Blue, 75);}
  AT(0,0,04.000)     { RestartPerformance(); }

}
  


void Performance_chase()
{
  FROM(0,0,00.000)   {CD77_chase_one_color_symet(CRGB::Red, 400, 2); FastLED.delay(50);}
  FROM(0,0,06.000)   {CD77_chase_one_color_symet(CRGB::DarkBlue, 800, 6); FastLED.delay(50);}
  FROM(0,0,12.000)   {CD77_chase_array_color_symet(400,800,2); FastLED.delay(50);}
  FROM(0,0,20.000)   {random16_add_entropy(random(65535)); CD77_chase_one_color_unsymet(CRGB::Yellow,200,800,3); FastLED.delay(50);}
  FROM(0,0,26.000)   {random16_add_entropy(random(65535)); CD77_chase_array_color_unsymet(200,800,400, 2); FastLED.delay(50);}
  FROM(0,0,32.000)   {random16_add_entropy(random(65535));  EVERY_N_MILLIS(750){dotnumber = random16(3,6);};  CD77_chase_array_color_unsymet(200,800,400, dotnumber); FastLED.delay(50);}
  FROM(0,0,40.000)   {currentPalette = CRGBPalette16(CRGB::Blue, CRGB::Blue, CRGB::Red, CRGB::Red); CD77_chase_PAL_symet( 5, 400, 4 );FastLED.delay(50);}
  FROM(0,0,50.000)   {random16_add_entropy(random(65535)); currentPalette =  bhw1_28_gp; CD77_chase_PAL_unsymet(5, 200,800,4); FastLED.delay(50);}
  AT(0,0,60.000)     {RestartPerformance(); }
}

void Performance_police_lights_sketch(){
  FROM(0,0,0.010)    {cd77_police_lights_one(0, 2, 50);} // Note: cd77_police_lights_one(color array used, number of segments (dots), wait) - generates moving dots
  FROM(0,0,5.000)    {cd77_police_lights_all(0, 2, 50);} // Note: cd77_police_lights_all(color array used, number of segments, wait) - generates moving segments
  FROM(0,0,10.000)   {cd77_police_lights_one(1, 3, 50);}
  FROM(0,0,15.000)   {cd77_police_lights_all(1, 3, 50);}
  FROM(0,0,20.000)   {cd77_police_lights_one(0, 4, 50);}
  FROM(0,0,25.000)   {cd77_police_lights_all(0, 4, 50);}  
  FROM(0,0,30.000)   {cd77_police_lights_one(1, 6, 50);} 
  FROM(0,0,35.000)   {cd77_police_lights_all(1, 6, 50);}
  FROM(0,0,40.000)   {cd77_police_lights_one(2, 5, 50);}
  FROM(0,0,45.000)   {cd77_police_lights_all(2, 5, 50);}
  FROM(0,0,50.000)   {cd77_police_lights_one_palette(1,48,4,50);currentPalette = CRGBPalette16( CRGB::Grey, CRGB::Blue, CRGB::Aqua,  CRGB::White);  currentBlending = LINEARBLEND;} //note: cd77_police_lights_all_palette( colorIndex,  deltacolorIndex, number of segments,  wait )
  FROM(0,0,55.000)   {cd77_police_lights_all_palette(1,48,4,50);currentPalette = CRGBPalette16( CRGB::Grey, CRGB::Blue, CRGB::Aqua,  CRGB::White);  currentBlending = LINEARBLEND;} //note: cd77_police_lights_one_palette( colorIndex,  deltacolorIndex, number of segments,  wait )
  AT(0,1,00.000)     {RestartPerformance(); } 

}

void Performance_flicker()
{
  FROM(0,0,00.000)   {CD77_flicker(CRGB::OrangeRed, 5, 30); }
  FROM(0,0,03.000)   {CD77_flicker(CRGB::Purple, 5, 30);}
  FROM(0,0,06.000)   {CD77_flicker(CRGB::Green, 5, 30);}
  FROM(0,0,09.000)   {CD77_flicker(CRGB::OrangeRed, 5, 30); }
  FROM(0,0,12.000)   {CD77_flicker(CRGB::Purple, 5, 30);}
  FROM(0,0,15.000)   {CD77_flicker(CRGB::Green, 5, 30);}
    FROM(0,0,18.000)   {FastLED.clear();FastLED.show();}
  AT(0,0,18.200)     {RestartPerformance(); }
  
}

void Performance_DemoReel100()
{
  FROM(0,0,00.000)   {gCurrentPatternNumberdr100=0;}
  FROM(0,0,00.200)   {gPatternsdr100[gCurrentPatternNumberdr100]();  FastLED.show(); FastLED.delay(1000/FRAMES_PER_SECOND);  EVERY_N_MILLISECONDS( 5 ) { ghuedr100++; };   EVERY_N_SECONDS(12) { nextPatterndr100(); };  } 
  FROM(0,5,00.000)   {FastLED.clear();FastLED.show();}
  AT(0,5,00.200)     {RestartPerformance(); }
  }



#endif
