// pin 18 is CD   (SD Card CD)
// pin 17 is CS2  (SD Card CS)
// pin 16 is CS1  (MCP3208)


#include <SPI.h>
String serialout;

//================================================
// START OF MCP3208
//================================================
#include "MCP3208.h"
#define arr_len(x) (sizeof(x)/sizeof(*x))
#define NUM_ADC_CHANNELS 8
#define CONVERT_12BIT_TO_VOLTS 0.001221001221001 // 5/(2^12)
#define ADC_CS 16
double CHANNEL_COUNT_OFFSET[NUM_ADC_CHANNELS] = {0, 0, 0, 0, 0, 0, 0, 0}; // Channels 0..7
MCP3208 inputAdc;
int inputCounts[NUM_ADC_CHANNELS];
int filteredCounts[NUM_ADC_CHANNELS];
double filteredVoltage[NUM_ADC_CHANNELS];
word outputCounts[NUM_ADC_CHANNELS];
double offset[NUM_ADC_CHANNELS];
int i;
//================================================
//end of MCP3208 Setup
//================================================

long sequence = 0;

void setup() {

 for (i = 0; i < NUM_ADC_CHANNELS; i++){
        CHANNEL_COUNT_OFFSET[i];
    }

SPI.begin();
SPI.setClockDivider(SPI_CLOCK_DIV16);

//====================================
// Initialize MCP3208
inputAdc.begin(ADC_CS);
//====================================


Serial.begin(57600);



}

void loop() {

//========================================
// MCP3208 reading
//========================================
 // Read all ADC channels
    for (i = 0; i < NUM_ADC_CHANNELS; i++){
    
    // Read the value from the ADC
    inputCounts[i] = inputAdc.convert((byte) i, SINGLE_ENDED);
    
    filteredCounts[i] = inputCounts[i];
  
    // The input voltage (0-5) ranges from 0-4095 (12 bit system). Convert the value to its correct voltage.
    filteredVoltage[i] = filteredCounts[i] * CONVERT_12BIT_TO_VOLTS;
   }


//==========================================
//sequence
//==========================================

sequence = sequence +1;
  if (sequence >= 2147483645){
    sequence = 0;
  }



//=======================================
// MCP3208 Serial out
//=======================================

serialout = '0';

for (i = 0; i < NUM_ADC_CHANNELS; i++){
  serialout += filteredCounts[i];
  serialout += ',';
}
Serial.print(sequence);
Serial.println(serialout);

//delay(100);
//=======================================
}
