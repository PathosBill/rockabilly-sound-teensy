// "That Rockabilly Sound" II- rewritten for Teensy
// 


/* To-Do 
 *  add physical controls
 *  convert to raw read
 *  sound design delay
 *  verify sync
 */

///////////////////////////////////
// code from Teensy Audio design tool
///////////////////////////////////

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=152,169
AudioPlaySdWav           playSdWav2;     //xy=153,208
AudioPlaySdWav           playSdWav4;     //xy=153,290
AudioPlaySdWav           playSdWav3;     //xy=155,249
AudioEffectDelay         delay1;         //xy=352,96
AudioMixer4              mixer1;         //xy=354,207
AudioMixer4              mixer2;         //xy=502,226
AudioOutputPT8211        pt8211_1;       //xy=659,236
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 0, delay1, 0);
AudioConnection          patchCord3(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord4(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord5(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord6(delay1, 0, mixer2, 1);
AudioConnection          patchCord7(mixer1, 0, mixer2, 0);
AudioConnection          patchCord8(mixer2, 0, pt8211_1, 0);
AudioConnection          patchCord9(mixer2, 0, pt8211_1, 1);
// GUItool: end automatically generated code


// define SD card

// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

// Init Stuff
void setup() {
  Serial.begin(9600);
  AudioMemory(8);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  // initialize settings
  pinMode(13, OUTPUT); // LED on pin 13
  mixer1.gain(0, 0.25);
  mixer1.gain(1, 0.25);
  mixer1.gain(2, 0.25);
  mixer1.gain(3, 0.25);
  mixer2.gain(0, 0.5);
  mixer2.gain(1, 0.5);
  delay(1000);
}

// PLAYBACK 
void loop() {
  if (playSdWav1.isPlaying() == false) {
    Serial.println("Start playing 1");
    playSdWav1.play("SDTEST2.WAV");
    delay(10); // wait for library to parse WAV info
  }
  if (playSdWav2.isPlaying() == false) {
    Serial.println("Start playing 2");
    playSdWav2.play("SDTEST3.WAV");
    delay(10); // wait for library to parse WAV info
  }
  if (playSdWav3.isPlaying() == false) {
    Serial.println("Start playing 3");
    playSdWav3.play("SDTEST1.WAV");
    delay(10); // wait for library to parse WAV info
  }
  if (playSdWav4.isPlaying() == false) {
    Serial.println("Start playing 4");
    playSdWav4.play("SDTEST4.WAV");
    delay(10); // wait for library to parse WAV info
  }
  
  // CONTROL
  int knobA = analogRead(A10); // knob read @ 10 bits 0 to 1023
  float rawGain = ( (float)knobA / 1023.0);
  float mappedGain = rawGain * 0.25;
  Serial.print( "knob 1 = "); // log to serial monitor
  Serial.print(mappedGain);
  Serial.print("\n");
  mixer1.gain(0, mappedGain); // control mixer gain with knob

  int knobB = analogRead(A11); // knob read @ 10 bits 0 to 1023
  rawGain = ( (float)knobB / 1023.0);
  mappedGain = rawGain * 0.25;
  Serial.print( "knob 2 = "); // log to serial monitor
  Serial.print(mappedGain);
  Serial.print("\n");
  mixer1.gain(1, mappedGain); // control mixer gain with knob

  int knobC = analogRead(A12); // knob read @ 10 bits 0 to 1023
  rawGain = ( (float)knobC / 1023.0);
  mappedGain = rawGain * 0.25;
  Serial.print( "knob 3 = "); // log to serial monitor
  Serial.print(mappedGain);
  Serial.print("\n");
  mixer1.gain(2 , mappedGain); // control mixer gain with knob

  int knobD = analogRead(A13); // knob read @ 10 bits 0 to 1023
  rawGain = ( (float)knobD / 1023.0);
  mappedGain = rawGain * 0.25;
  Serial.print( "knob 4 = "); // log to serial monitor
  Serial.print(mappedGain);
  Serial.print("\n");
  mixer1.gain(3 , mappedGain); // control mixer gain with knob

  int knobE = analogRead(A14); // knob read @ 10 bits 0 to 1023
  rawGain = ( (float)knobE / 1023.0);
  mappedGain = rawGain * 0.5;
  Serial.print( "knob 5 = "); // log to serial monitor
  Serial.print(mappedGain);
  Serial.print("\n");
  mixer2.gain(1 , mappedGain); // control mixer gain with knob


  
  
  
  /*
  int knob = analogRead(A3);  // knob = 0 to 1023
  float gain1 = (float)knob / 1023.0;
  float gain2 = 1.0 - gain1;
  mixer1.gain(0, gain1);
  mixer1.gain(1, gain2);
  mixer2.gain(0, gain1);
  mixer2.gain(1, gain2);
  */
}
