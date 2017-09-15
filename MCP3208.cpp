/*
  MCP3208.h - library to operate the MCP3204/08 ADC

  USAGE
       MCP3208 adc(9); // instantiate an MCP3208 object using chip-select pin 9
       adc.begin(); 
       word value = adc.convert(B0000); // read the voltage on channel 0 
   
   NOTES
       * SPI.begin() must be called in setup() before attempting to use the convert() method.
       * The maximum frequency for the MCP3204/08 series is 2MHz. You must set the clock divider yourself
         in the sketch's setup(). For a 16MHz Arduino clock, it is recommended to call
         SPI.setClockDivider(SPI_CLOCK_DIV16), which yields a 1MHz clock.
       * SPI mode may be CPOL==CPHA==1 or CPOL==CPHA==0 (i.e., SPI_DATAMODE3 or SPI_DATAMODE0)
*/

#include "Arduino.h"
#include "SPI.h"

#include "MCP3208.h"

//MCP3208::MC3208(){}

void MCP3208::begin(int pin){
    _pin = pin;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, HIGH);
}

word MCP3208::convert(byte address, int type){
/*
  convert() - read an analog value and convert it to digital

  ARGUMENTS
      (byte) address - Channel to read. 0 to 7
      (int)  type    - may be SINGLE_ENDED or DIFFERENTIAL

  RETURNS
      word - output value from MCP3208 device

  NOTES
      
 */

    byte data[3];
    word value = 0;

    int i;
    
    SPI.setBitOrder(MSBFIRST);
    SPI.setDataMode(SPI_MODE0); // just pick a convention and stick to it...

    // The bit pattern is:
    // 0000_01(SNG/DIFF)(D2) (D1)(D0)XX_XXXX XXXX_XXXX; the 2nd and 3rd transfers back data we care about.
    
    byte cb[3];
    
    cb[0] = 0x04;
    cb[0] |= bitRead(type, 0) << 1; // single or differential? 
    cb[0] |= bitRead(address, 2);   // pull the 2nd bit from address and chain it to the command
    cb[1] = address << 6; // last 6 bits are dontcares      
    cb[2] = 0x00; // dontcares
    

    digitalWrite(_pin, LOW);
    for (i = 0; i < 3; i++){
        data[i] = SPI.transfer(cb[i]);
    }
    digitalWrite(_pin, HIGH);
        
    // Mask the top 4 bits of data[1], since they're unknowns/nulls
    data[1] &= 0x0F;

    value  = data[1] << 8;
    value |= data[2];

    return(value);
}
