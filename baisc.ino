#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <synth_simple_drum.h>

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum2;          //xy=399,244
AudioSynthSimpleDrum     drum3;          //xy=424,310
AudioSynthSimpleDrum     drum1;          //xy=431,197
AudioSynthSimpleDrum     drum4;          //xy=464,374
AudioMixer4              mixer1;         //xy=737,265
AudioOutputI2S           i2s1;           //xy=979,214
AudioConnection          patchCord1(drum2, 0, mixer1, 1);
AudioConnection          patchCord2(drum3, 0, mixer1, 2);
AudioConnection          patchCord3(drum1, 0, mixer1, 0);
AudioConnection          patchCord4(drum4, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=930,518
// GUItool: end automatically generated code

//static uint32_t next;

int pinTouch[] = {33, 32, 17, 16, 25};
bool released[] = {true, true, true, true, true};

unsigned long clock;
unsigned long tempo;
unsigned long bps;
unsigned long held;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  // audio library init
  AudioMemory(15);

  //next = millis() + 1000;

  AudioNoInterrupts();

  drum1.frequency(60);
  drum1.length(1500);
  drum1.secondMix(0.0);
  drum1.pitchMod(0.55);

  drum2.frequency(60);
  drum2.length(300);
  drum2.secondMix(0.0);
  drum2.pitchMod(1.0);

  drum3.frequency(550);
  drum3.length(400);
  drum3.secondMix(1.0);
  drum3.pitchMod(0.5);

  drum4.frequency(1200);
  drum4.length(150);
  drum4.secondMix(0.0);
  drum4.pitchMod(0.0);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  AudioInterrupts();

  clock = millis();
  tempo = 60;
  bps = 60000 / tempo;
}

void touchCheck()
{

  if (touchRead(pinTouch[0]) > 2000 && released[0])
  {
    drum1.noteOn();
    released[0] = false;
  }
  if (touchRead(pinTouch[0]) <= 2000)
  {
    released[0] = true;
  }


  if (touchRead(pinTouch[1]) > 2000 && released[1])
  {
    drum2.noteOn();
    released[1] = false;

  }
  if (touchRead(pinTouch[1]) <= 2000)
  {
    released[1] = true;
  }


  if (touchRead(pinTouch[2]) > 2000 && released[2])
  {
    drum3.noteOn();
    released[2] = false;

  }
  if (touchRead(pinTouch[2]) <= 2000)
  {
    released[2] = true;
  }


  if (touchRead(pinTouch[3]) > 2000 && released[3])
  {
    drum4.noteOn();
    released[3] = false;


  }
  if (touchRead(pinTouch[3]) <= 2000 )
  {
    released[3] = true;
  }

  if (touchRead(pinTouch[4]) > 2000 && released[4])
  {
    held = millis();
    released[4] = false;

  }
  if (touchRead(pinTouch[4]) <= 2000 && !released[4])
  {
    int dif = millis() - held;
    dif = constrain(dif, 300, 1000);
    bps = dif;
    
    Serial.println(dif);
    released[4] = true;
  

  }


}


void loop() {
  touchCheck();

  if (millis() - clock > bps) {
    clock = millis();
    drum1.noteOn();
  }

}
