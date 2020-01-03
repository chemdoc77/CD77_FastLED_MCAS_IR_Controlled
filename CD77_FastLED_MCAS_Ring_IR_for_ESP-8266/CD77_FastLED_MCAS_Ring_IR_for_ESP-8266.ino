//FastLED MCAS Ring Sketch Ir Controlled by Chemdoc77 For ESP-8266 MCU
//MCAS = Multiple Complex Animations Sketch


/*
  **************** NOTE ********************
You may have to push a button on the IR controller a couple of times
to change to another sketchin the MCAS sketch.  This is due to the setting interrupts in 
FastLED to zero.  

****** This is set up for Wemos D1 Mini Pro *************

See line 22 and line 65 if you use another ESP-8266 MCU

***** Look at the READ_ME.h tab for further explanation of this sketch. ***

*/

#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>

#define LED_PIN D6 

#define CHIPSET NEOPIXEL 
#define NUM_LEDS 24

uint16_t BRIGHTNESS = 60;
CRGB leds[NUM_LEDS];
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

//Time Performance code

uint32_t gTimeCodeBase = 0;
uint32_t gTimeCode = 0;
uint32_t gLastTimeCodeDoneAt = 0;
uint32_t gLastTimeCodeDoneFrom = 0;
uint32_t gTimeCodeBase_sub = 0;
uint32_t gTimeCode_SECONDS=0;
uint32_t mysec =0;
//===========================================

//DemoReel100 Code

uint8_t gCurrentPatternNumberdr100 = 0; // Index number of which pattern is current
uint8_t ghuedr100 = 0; // rotating "base color" used by many of the patterns

//====================================

#include "CD77_func1.h"
#include "Chase.h" 
#include "CD77_police_lights.h"
#include "cd77_meteor.h"
#include "CD77_Fade_To_Diff_Colors.h"
#include "Flicker.h"
#include "DemoReel100.h"
#include "Time_performance.h"

//***********************

// IR Stuff

#include <IRremoteESP8266.h> //#include <IRremote.h>
#include <IRrecv.h>
#include <IRutils.h>
int RECV_PIN = D3;

IRrecv irrecv(RECV_PIN);

decode_results results;

int IR_value =0;
int last_value = 0;
 int sw_value = 16724175; // modified 20190528

//=================
  
void setup() {

delay(1000); // sanity delay
 
 irrecv.enableIRIn(); // Start the receiver IR STUFF
Serial.begin(115200);//comment out if you are not using print messages
FastLED.addLeds<CHIPSET, LED_PIN>(leds, NUM_LEDS);// for NeoPixels
//FastLED.addLeds<CHIPSET, LED_PIN, GRB>(leds, NUM_LEDS);// for WS2812b
//FastLED.addLeds<CHIPSET, LED_PIN, RBG>(leds, NUM_LEDS);// for WS2811
FastLED.setBrightness( BRIGHTNESS );
FastLED.setMaxPowerInVoltsAndMilliamps(5,1500);  //set to 5 volts 1.5 amps
 set_max_power_indicator_LED(13);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
  
//Time Performance code
  RestartPerformance();
}

//============================================
void loop() {
//Time Performance code
  gTimeCode = millis() - gTimeCodeBase;  


// IR Stuff ===============
 if (irrecv.decode(&results)) {
   // Serial.println(results.value);
    irrecv.resume(); // Receive the next value


if (results.value!= -1){

 IR_value = results.value;
 last_value = IR_value;
 sw_value=last_value;
  Serial.println("IR_value");
  Serial.println(IR_value);
Serial.println("sw_value");
  Serial.println(sw_value);
    }
else {
last_value;
sw_value=last_value;
   }
 fill_solid( leds, NUM_LEDS, CRGB::Black); FastLED.show();
 RestartPerformance();
delay(100);
  }
  
  
     switch (sw_value) {

       // For the 44 colored button IR Controller
       case 16724175:   Serial.println("start case y1");       Performance_red_white_dot(); break;     //DIY1 button 
       case 16756815:   Serial.println("start case Y2");       Performance_green_yellow_dot();  break;    //DIY2 button                
       case 16740495:   Serial.println("start case Y3");       Performance_red_blue_line();  break;    //DIY3 button 
       case 16716015:   Serial.println("start case Y4");       Performance_chase(); break; //DIY4 button           
       case 16748655:   Serial.println("start case Y5");       Performance_police_lights_sketch();  break;   //DIY5 button  
       case 16732335:   Serial.println("start case Y6");       meteorShower();  break;   //DIY6 button
       case 16720095:   Serial.println("start case Jump 3");   CD77_Slow_Fade_Pal(15, 10);  break; //Jump 3 button
       case 16752735:   Serial.println("start case Jump7");    Performance_flicker();  break;   //jump7 button  
       case 16736415:   Serial.println("start case fade7");    Performance_DemoReel100();  break;   //fade 7 button
       case 16718565:   Serial.println("start case red r");    BRIGHTNESS = 30;  FastLED.setBrightness( BRIGHTNESS ); Performance_green_yellow_dot(); break;   //red rbutton
       case 16751205:   Serial.println("start case green g");  BRIGHTNESS = 60;  FastLED.setBrightness( BRIGHTNESS ); Performance_green_yellow_dot(); break;   //green g"button
       case 16720605:   Serial.println("start case white w");  BRIGHTNESS = 160;  FastLED.setBrightness( BRIGHTNESS ); Performance_green_yellow_dot(); break;   //white w button



       // For the AdaFruit Mini Remote Control

       case 16582903:   Serial.println("start case button 1");     Performance_red_white_dot(); break;     // button 1
       case 16615543:   Serial.println("start case button 2");     Performance_green_yellow_dot();  break;    //button 2               
       case 16599223:   Serial.println("start case button 3");     Performance_red_blue_line();  break;    // button 3
       case 16591063:   Serial.println("start case button 4");     Performance_chase(); break; // button 4          
       case 16623703:   Serial.println("start case button 5");     Performance_police_lights_sketch();  break;  // button 5 
       case 16607383:   Serial.println("start case button 6");     meteorShower();  break;   // button 6
       case 16586983:   Serial.println("start case button 7");     CD77_Slow_Fade_Pal(15, 10);  break; //button 7
       case 16619623:   Serial.println("start case button 8");     Performance_DemoReel100();   break;   // button 8           
       case 16603303:   Serial.println("start case button 9");     Performance_flicker();  break;   // button 9 
       case 16580863:   Serial.println("start case vol-");         BRIGHTNESS = 30;  FastLED.setBrightness( BRIGHTNESS ); Performance_green_yellow_dot(); break;   //red rbutton
       case 16613503:   Serial.println("start case red >||");      BRIGHTNESS = 60;  FastLED.setBrightness( BRIGHTNESS ); Performance_green_yellow_dot(); break;   //green g"button
       case 16597183:   Serial.println("start case vol+");         BRIGHTNESS = 160;  FastLED.setBrightness( BRIGHTNESS ); Performance_green_yellow_dot(); break;   //white w button


   }  
}
