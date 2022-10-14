/*
  MIT License
  
  Copyright (c) 2021 Ferrari Roberto
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/
#include "Arduino.h"
#include "oneButtonSwitch.h"

oneButtonSwitch::oneButtonSwitch(int pinButton, double pinHoldMOSFET)
{
    _pinButton = pinButton;
    _pinHoldMOSFET = pinHoldMOSFET;
    pinMode(_pinButton, INPUT_PULLUP);
    pinMode(_pinHoldMOSFET, OUTPUT);
    digitalWrite(_pinHoldMOSFET, HIGH);
}

oneButtonSwitch::oneButtonSwitch(int pinButton, double pinHoldMOSFET, long milliseconds)
{
	_pinButton = pinButton;
    _pinHoldMOSFET = pinHoldMOSFET;
    pinMode(_pinButton, INPUT_PULLUP);
    pinMode(_pinHoldMOSFET, OUTPUT);
    digitalWrite(_pinHoldMOSFET, HIGH);
	_milliseconds = milliseconds;
}
	
oneButtonSwitch::oneButtonSwitch()
{

}

//---- De-bouncing function for all buttons----//
boolean oneButtonSwitch::debounce(boolean last, int pin)
{
  boolean current = digitalRead(pin);
    if (last != current)
    {
      delay(5);
      current = digitalRead(pin);
    }
  return current;
}

void oneButtonSwitch::oneButtonSwitchLOOP()
{
 powerbutton = debounce(last_powerbutton, _pinButton);
	
 if(_milliseconds < 1){
  if(MOSFET_hold == false){
   if (last_powerbutton == LOW && powerbutton == HIGH){
     MOSFET_hold = true;
   }else{}
  last_powerbutton = powerbutton;
   }else{
    if (last_powerbutton == LOW && powerbutton == HIGH){
      digitalWrite(_pinHoldMOSFET, LOW);
    }else{}
  last_powerbutton = powerbutton;
  }
 }else{
  if(MOSFET_hold == false){
   if (last_powerbutton == LOW && powerbutton == HIGH){
    MOSFET_hold = true;
   }else{}
    last_powerbutton = powerbutton;
   }else{
   if (last_powerbutton == HIGH && powerbutton == LOW){
     pressedTime = millis();
   }else if(last_powerbutton == LOW && powerbutton == HIGH){
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;	
     if( pressDuration < _milliseconds ){
       //Serial.println("A short press is detected");
      }
     if( pressDuration > _milliseconds ){
       //Serial.println("A long press is detected");
	   digitalWrite(_pinHoldMOSFET, LOW);
      }
   }
  last_powerbutton = powerbutton;
  }
 }
}