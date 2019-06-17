/*
PURPOSE: The regular Tone Library does not allow for simultaneous tones. 
This library uses two digital pins both connected to the same speaker, 
to produce DTMF tones for touch-tone phone dialing. If placed near the microphone 
end of a handset, the speaker can dial a phone number when the momentary button is pushed.
URL:  https://playground.arduino.cc/Main/DTMF/
*/
/* DTMF encoder (Dual Tone Generator) for a Phone Dialer
 *  Created by David Dubins, May 13th, 2016.
 *  Released into the public domain.
 *
 * SETUP:
 * - Connect Pins 15 and 13 to the + speaker terminal, each through their own 240 Ohm resistor
 * - Connect a 4.7 uF capacitor between the + and - terminals of the speaker
 * - Connect speaker GND to NodeMCU GND
 */
 
#ifndef DTMF_SOUND_EFFECTS_H
#define DTMF_SOUND_EFFECTS_H

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void DTMFSetup();
void playDTMF(uint8_t digit, uint8_t duration);
void dialNumber(uint8_t number[],uint8_t len);
void dialOneNumber();

#ifdef __cplusplus
} // extern "C"
#endif

#endif
