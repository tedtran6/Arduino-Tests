#include <CapacitiveSensor.h>
CapacitiveSensor   im = CapacitiveSensor(12, A1);

CapacitiveSensor  first = CapacitiveSensor(2, 3);
CapacitiveSensor  second = CapacitiveSensor(4, 5);
CapacitiveSensor  third = CapacitiveSensor(7, 6);
CapacitiveSensor  fourth = CapacitiveSensor(8, 9);

int led1 = 10;
int led2 = 19;
int led3 = 18;
int led4 = 17;

int on = 0x90;
int off = 0x80;

int gv = 0x40; //generic velocity

int pitch1;
int pitch2;
int pitch3;
int pitch4;

boolean currentIm = LOW;
boolean lastIm = LOW;

int currentPot = 0;
int lastPot = 0;

boolean currentState1 = LOW;    //for each sensor
boolean lastState1 = LOW;
boolean currentState2 = LOW;
boolean lastState2 = LOW;
boolean currentState3 = LOW;
boolean lastState3 = LOW;
boolean currentState4 = LOW;
boolean lastState4 = LOW;

void setup() {
  Serial.begin(115200);
  pinMode(10, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
}

void loop() {
  
  //for the volume pot
//  currentPot = analogRead(0);
// if(currentPot = lastPot);
//  {
//    MIDImessage(176, 1, currentPot/8);
//    lastPot = currentPot;
//  }
  
  //This is for changing the note types of the four keys
  //This changes an LED so we can know when a change has been made
  if(analogRead(A2) > 767){   //1023 / 4 approx 255 or so, intervals of that. 
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    pitch1 = 48;
    pitch2 = 49;
    pitch3 = 50;
    pitch4 = 51;
  }
  else if(analogRead(A2) > 551){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    pitch1 = 44;
    pitch2 = 45;
    pitch3 = 46;
    pitch4 = 47;
  }
  else if(analogRead(A2) > 256){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    pitch1 = 40;
    pitch2 = 41;
    pitch3 = 42;
    pitch4 = 43;
  }
  else{
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    pitch1 = 36;
    pitch2 = 37;
    pitch3 = 38;
    pitch4 = 39;
  }

  if(analogRead(A2) < 5){
    im.reset_CS_AutoCal();
    first.reset_CS_AutoCal();
    second.reset_CS_AutoCal();
    third.reset_CS_AutoCal();
    fourth.reset_CS_AutoCal();
    MIDIButton(0x90, 60, 0x40);
  }
  
  long valueIm = im.capacitiveSensor(2);
    
  long valueFirst = first.capacitiveSensor(30);
  long valueSecond = second.capacitiveSensor(30);
  long valueThird = third.capacitiveSensor(30);
  long valueFourth = fourth.capacitiveSensor(30);

  //This is for debugging
  //Serial.print(valueIm); Serial.print("\t");  Serial.print(valueOk); Serial.print("\t \t");  Serial.print(valueFirst); Serial.print("\t");  Serial.print(valueSecond);
  //Serial.print("\t");  Serial.print(valueThird); Serial.print("\t");  Serial.println(valueFourth);

  if(valueIm > 2000){
    currentIm = HIGH;
  }
  else
    currentIm = LOW;
    
  //to change the off an off states of the booleans---
  if(valueFirst > 70){
    currentState1 = HIGH; 
  }
  else
    currentState1 = LOW;
    
  if(valueSecond > 70){
    currentState2 = HIGH;
  }
  else
    currentState2 = LOW;
    
  if(valueThird > 70){
    currentState3 = HIGH;
  }
  else
    currentState3 = LOW;
    
  if(valueFourth > 70){
    currentState4 = HIGH;
  }
  else
    currentState4 = LOW;
  //END-------------------------------------------------
  //im
  if(lastIm == LOW && currentIm == HIGH)
   {
    MIDIButton(on, 55, gv);
    lastIm = HIGH;
   }
   if(currentIm== LOW && lastIm == HIGH)
   {
    MIDIButton(off, 55, gv);
    lastIm = LOW;
   }
  //to send the actual data to hairless midi------------
   if(lastState1 == LOW && currentState1 == HIGH)  //if the pervious state was low and now it's high, send the ON message
   {
    MIDIButton(on, pitch1, gv);
    lastState1 = HIGH;
   }
   if(currentState1 == LOW && lastState1 == HIGH) //if the previous state was high and now it's low, send the OFF message
   {
    MIDIButton(off, pitch1, gv); //right here accidentally made it all for the second state
    lastState1 = LOW;
   }
  
   if(lastState2 == LOW && currentState2 == HIGH)
   {
    MIDIButton(on, pitch2, gv);
    lastState2 = HIGH;
   }
   if(currentState2 == LOW && lastState2 == HIGH)
   {
    MIDIButton(off, pitch2, gv);
    lastState2 = LOW;
   }

   if(lastState3 == LOW && currentState3 == HIGH)
   {
    MIDIButton(on, pitch3, gv);
    lastState3 = HIGH;
   }
   if(currentState3 == LOW && lastState3 == HIGH)
   {
    MIDIButton(off, pitch3, gv);
    lastState3 = LOW;
   }

   if(lastState4 == LOW && currentState4 == HIGH)
   {
    MIDIButton(on, pitch4, gv);
    lastState4 = HIGH;
   }
   if(currentState4 == LOW && lastState4 == HIGH)
   {
    MIDIButton(off, pitch4, gv);
    lastState4 = LOW;
   }

}
void MIDIButton(int command, int pitch, int velocity)
  {
     Serial.write(command);
     Serial.write(pitch);
     Serial.write(velocity);
  }

void MIDImessage(byte command, byte data1, byte data2) //pass values out through standard Midi Command
{
   Serial.write(command);
   Serial.write(data1);
   Serial.write(data2);
}

