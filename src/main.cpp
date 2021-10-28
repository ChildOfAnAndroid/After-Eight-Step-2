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
  int ledAState = LOW;

//CONTROL VOLTAGE
  const int eightStepCV = A4;
  const int afterEightCV = A5;

//TEMPO POTENTIOMETER
  const int tempoControl = A6;
  int tempoReadout = 0;
  int tempo = 0;
  long rememberTime = 0;

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
  pinMode(potsA,INPUT); //PITCH
  pinMode(potsB,INPUT); //PROBABILITY

//LEDs
  pinMode(ledAPins, OUTPUT);
  digitalWrite (ledAPins, ledAState);
  pinMode(ledBPins, OUTPUT);

//CONTROL VOLTAGE
  pinMode(eightStepCV, OUTPUT);
  pinMode(afterEightCV, OUTPUT);
}

void loop() {
// put your main code here, to run repeatedly:

//READING POTENTIOMETER INPUTS
  PORTB=0b00000000; //Data flow - X0 (first step on both rows)
  int step1A = analogRead(potsA); //read data from X0 potsA 1st step
  int step1APitch = map(step1A, 0, 1023, 50, 80); //Convert to MIDI values
  int step1B = analogRead(potsB); //read data from X0 potsB 1st step

  PORTB=0b00000001;  //Data flow - X1 (second step)
  int step2A = analogRead(potsA); //read data from X1 potsA 2nd step
  int step2APitch = map(step2A, 0, 1023, 50, 80); //Convert to MIDI values
  int step2B = analogRead(potsB); //read data from X1 potsB 2nd step

//SETTING TEMPO
  //Want to use input of tempo potentiometer to scale how long it takes to 
  //jump between steps

  int tempoReadout = analogRead(tempoControl); //reads potentiometer
  int tempo = map(tempoReadout, 0, 1023, 20, 260); //makes value of potentiometer smaller
  int tempoInMilliseconds = (60000/tempo); //Converts BPM to milliseconds

//8 STEP OUTPUT (LEDs & CV)
  if ((millis() - rememberTime) >= tempoInMilliseconds){

    PORTB=0b00000000; //Data flow - X0 (1st step)

    if (ledAState == LOW){
      digitalWrite(ledAPins, HIGH); //1st step, 1st row of LEDs, turns on
      analogWrite(eightStepCV, step1APitch); //Sends correct control voltage (1v per octave) to CV Out Jack
      //Step 1A Pitch is currently set in MIDI, will have to change this
    }
    else (ledAState == HIGH){
      digitalWrite(ledAPins, LOW); //1st step, 1st row of LEDs, turns off
      analogWrite(eightStepCV, LOW); //Removes any control voltage
    }

    PORTB=0b00000001; //Data flow - X1 (2nd step)

    if (ledAState == LOW){
      digitalWrite(ledAPins, HIGH); //2st step, 1st row of LEDs, turns on
      analogWrite(eightStepCV, step2APitch); //Sends CV of second steps pitch to CV out jack
    }
    else (ledAState == HIGH){
      digitalWrite(ledAPins, LOW); //2st step, 1st row of LEDs, turns off
      analogWrite(eightStepCV, LOW);
    }

    rememberTime = millis(); //makes 'rememberTime' the current time 
  }

//MARKOV CHAIN PROCESSING


//AFTER 8 STEP OUTPUT (LEDs)


//AFTER 8 STEP OUTPUT (CV)


}