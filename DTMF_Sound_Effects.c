#include <stdint.h>
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define tone1Pin                  13 // aka GPIO13, D7 also works.
#define tone2Pin                  15 // aka GPIO15, D8 also works.
#define DTMF_TONE_DURATION_MS         200
#define DTMF_PAUSE_DURATION_MS         150

// frequencies adopted from: https://en.wikipedia.org/wiki/Dual-tone_multi-frequency_signaling
int DTMF[14][2]={
  {941,1336}, // frequencies for touch tone 0
  {697,1209}, // frequencies for touch tone 1
  {697,1336}, // frequencies for touch tone 2
  {697,1477}, // frequencies for touch tone 3
  {770,1209}, // frequencies for touch tone 4
  {770,1336}, // frequencies for touch tone 5
  {770,1477}, // frequencies for touch tone 6
  {852,1209}, // frequencies for touch tone 7
  {852,1336}, // frequencies for touch tone 8
  {852,1477}, // frequencies for touch tone 9
  {941,1209}, // frequencies for touch tone * (10)
  {941,1477}, // frequencies for touch tone # (11)
  {0,0},      // pause (12)
  {350,440}   // Dial tone (13)
};

void DTMFSetup(){
  pinMode(tone1Pin,OUTPUT); // Output for Tone 1
  pinMode(tone2Pin,OUTPUT); // Output for Tone 2
}

void playDTMF(uint8_t digit, uint8_t duration){
  bool tone1state=false;
  bool tone2state=false;
  int tone1delay=(500000/DTMF[digit][0])-10; // calculate delay (in microseconds) for tone 1 (half of the period of one cycle). 10 is a fudge factor to raise the frequency due to sluggish timing.
  int tone2delay=(500000/DTMF[digit][1])-10; // calculate delay (in microseconds) for tone 2 (half of the period of one cycle). 10 is a fudge factor to raise the frequency due to sluggish timing.
  unsigned long tone1timer=micros();
  unsigned long tone2timer=micros();
  unsigned long timer=millis(); // for timing duration of a single tone
  if(digit==12){
    delay(duration); // delay if digit is 12
  } 
  else {
    while(millis()-timer<duration){
      if(micros()-tone1timer>tone1delay){
        tone1timer=micros(); // reset the timer
        tone1state=!tone1state; // toggle tone1state
        digitalWrite(tone1Pin, tone1state);
      }
      if(micros()-tone2timer>tone2delay){
        tone2timer=micros(); // reset the timer
        tone2state=!tone2state; // toggle tone2state
        digitalWrite(tone2Pin, tone2state);
      }
      yield(); // To allow time for the Wifi functions of the NodeMCU/ESP8266 to run.
    }
      digitalWrite(tone1Pin,LOW);
      digitalWrite(tone2Pin,LOW);
  }
}

void dialNumber(uint8_t number[],uint8_t len){
  for(int i=0;i<len;i++){
    playDTMF(number[i], 100);  // 100 msec duration of tone
    delay(100); // 100 msec pause between tones
  }
}

void dialOneNumber(){
  playDTMF(13, DTMF_TONE_DURATION_MS); // Dial tone
  playDTMF(12, DTMF_PAUSE_DURATION_MS); // pause off
}
