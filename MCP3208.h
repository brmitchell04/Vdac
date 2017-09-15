/*
  MCP3208.h - library to operate the MCP3204/08 DAC

  Created by: Clayton Chu
              clayton.n.chu@boeing.com
*/


#ifndef MCP3208_h
#define NCP3208_h

#include "Arduino.h"

#define ADC0 B0000
#define ADC1 B0001
#define ADC2 B0010
#define ADC3 B0011
#define ADC4 B0100
#define ADC5 B0101
#define ADC6 B0110
#define ADC7 B0111

#define SINGLE_ENDED 1
#define DIFFERENTIAL 0

class MCP3208{
    public:
    //MCP3208();
        void begin(int pin);
        word convert(byte address, int type);
        
    protected:
        int _pin;
};

#endif
