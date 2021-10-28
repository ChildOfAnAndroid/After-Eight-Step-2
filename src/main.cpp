#include <Arduino.h>

/* INITIAL NOTES

After Eight Step 2.0

Charis Cat // Child of an Android 2021

--

I am re-writing the After Eight Step to work independently of Max, so that 
it works without being plugged in and is also 100% free. 

I am also adding CV control to enable use of the after eight step in my 
DIY modular synth setup. 

I am removing the screen and some other elements as they didn't add anything,
allowing room for the CV gates.

*/

//INITIALISE PINS

//POTENTIOMETERS (multiplexed)
  const int potsA = A0;
  const int potsB = A1;
  const int inhibitMux = 7; //Turns off all Multiplexers (un-needed??)

//LEDs (multiplexed)
  const int ledAPins = A2;
  const int ledBPins = A3;

//CONTROL VOLTAGE
  const int eightStepCV = A4;
  const int afterEightCV = A5;

//REMOVED COMPONENTS (for my ref)

//ROTARY ENCODER (pins 2, 3, and 4)
//I want to remove this, perhaps could replace it with a 3 way switch????
//It largely controlled moving between settings without using Max

//GREEN BUTTON (pin A4)
//It does nothing

//LCD SCREEN (pins 5, 6, 11, 12, and 13)
//Takes up a lot of pins and doesn't really work

void setup() {
// put your setup code here, to run once:

//POTENTIOMETERS
  pinMode(inhibitMux,OUTPUT);
  digitalWrite(inhibitMux,LOW);
  DDRB = 0b00000111;  //PORT 8,9,10 as output
  PORTB = 0b00000000; //PORT 8,9,10 set to low
  pinMode(potsA,INPUT);
  pinMode(potsB,INPUT);

//LEDs
  pinMode(ledAPins, OUTPUT);
  pinMode(ledBPins, OUTPUT);

//CONTROL VOLTAGE
  pinMode(eightStepCV, OUTPUT);
  pinMode(afterEightCV, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

//READING POTENTIOMETER INPUTS

//8 STEP OUTPUT (LEDs)

//8 STEP OUTPUT (CV)

//MARKOV CHAIN PROCESSING

//AFTER 8 STEP OUTPUT (LEDs)

//AFTER 8 STEP OUTPUT (CV)

}