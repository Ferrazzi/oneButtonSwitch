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

/* 
 *  Arduino ON/OFF power momentary push button switch
 */
  
#ifndef oneButtonSwitch_h
#define oneButtonSwitch_h

#include "Arduino.h"

class oneButtonSwitch {
  public:  
    
    /*
    * Constructor
    * @param pinButton, pin number where momentary push button switch connect
    * @param pinHoldMOSFET, pin number hold power MOSFET ON - pinMode(pinHoldMOSFET, OUTPUT); digitalWrite(pinHoldMOSFET, HIGH); - when is LOW arduino power OFF
    */
    oneButtonSwitch(int pinButton, double pinHoldMOSFET);

    /*
    * Constructor
    * @param pinButton, pin number where momentary push button switch connect
    * @param pinHoldMOSFET, pin number hold power MOSFET ON - pinMode(pinHoldMOSFET, OUTPUT); digitalWrite(pinHoldMOSFET, HIGH); - when is LOW arduino power OFF
    * @param milliseconds, sets milliseconds from pressing power switch to switching off   
    */
	oneButtonSwitch(int pinButton, double pinHoldMOSFET, long milliseconds);

    /*
    * Constructor
    * Put oneButtonSwitchLOOP(); in loop void to activate off function with power switch button
    */
    void oneButtonSwitchLOOP();
    
    /*
    * Constructor
    */
    oneButtonSwitch();    
       
  private:
    int     _pinButton;        // pinButton moentarz push button switch
    int     _pinHoldMOSFET;      // pinHoldMOSFET hold MOSFET ON
    bool    MOSFET_hold = false;
	long    _milliseconds = 0;
	unsigned long pressedTime  = 0;
    unsigned long releasedTime = 0;
    boolean powerbutton = LOW;          
    boolean last_powerbutton = LOW;
    boolean debounce(boolean last, int pin);
};

#endif
