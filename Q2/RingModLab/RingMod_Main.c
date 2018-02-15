// Ring modulator lab template.

// Must include for sine sinf(x) function.
#include <math.h>

// Must include for DSK functionality.
#include "dsk6713_aic23.h"
#include "dsk6713_led.h"
#include "dsk6713_dip.h"

Uint32 fs=DSK6713_AIC23_FREQ_44KHZ;		// Set codec sampling rate to 44100.

// Defines **************************************************.
// Add your own... Frequency of LED blinking, Carrier waveform (sine), Length of sine-table, etc.
// For example: #define SAMPLE_RATE 44100				// Sample rate of AIC23 codec.
// #define ...

#define SAMPLE_RATE 44100
#define PI 3.14159265358979
#define freq_led 2 // Led Blink Frequency (Hz)
#define freq_dip1 100 // Sine Wave Frequency (Hz)
#define LEFT  0
#define RIGHT 1

int ledtime = 0; 
int sinetime = 0;
int loadtime = 0;
int sine_tab[SAMPLE_RATE / freq_dip1];

// Sine lookup table ****************************************. 
// <<<<YOU MUST HAVE ONE>>>>
// <type> g_sine_table[<length>];

// Flags for program functionality **************************.
// 0 for off, >0 for on...
// For example: short g_input_line_in = 0;				// Line-in vs. Modulator source.
// etc.

// Interrupt service routine, called on audio codec sample 
// clock trigger.
// **********************************************************.
interrupt void c_int11()         		
{
   // The majority of your code should go in this function.

   // 32bit audio IO. 16 bits per channel, highword|lowword.
   int   in_sample;
   int   out_sample;
   short sample_data;
   
   // Define more variables here. ***************************.

   // Get the state of the DIP switches. ********************.

   // Update your counters for the sine lookup table, LED. **.

   // Handle the LED toggling. ******************************.
   if(ledtime/(SAMPLE_RATE/(2*freq_led)) % 2 == 0)
   {
   		DSK6713_LED_on(0);
   }
   else if(ledtime/(SAMPLE_RATE/(2*freq_led)) % 2 == 1)
   {
   		DSK6713_LED_off(0);
   }
   if(ledtime >= 44000) ledtime = 0;
   else ++ledtime;
 
   in_sample   =  input_sample();
   //sample_data =  (0xFFFF & in_sample);
   
   // DIP switches
   
   if(DSK6713_DIP_get(0) == 0) // Justify whether process the input
   {
   		sample_data = (0xFFFF & (in_sample >> 16)); // Acquire Right Channel of Line in
   		if(DSK6713_DIP_get(2) == 0) // multiply sine
   		{
			sample_data = sample_data * (0xFFFF & sine_tab[loadtime]);
			loadtime++;
			if (loadtime >= SAMPLE_RATE / freq_dip1) loadtime = 0;
		}
   		else
   		{
   			loadtime = 0;
   		}
   }
   else
   {
   		sample_data = (0xFFFF & sine_tab[sinetime]);
   		if(DSK6713_DIP_get(2) == 0) // multiply sine
   		{
			sample_data = sample_data * sample_data;
		}
   		if(DSK6713_DIP_get(1) == 0) // Frequency x2
   		{
   			sinetime+=2;
   		}
   		else
   		{
   			sinetime++;
   		}
 	 	if (sinetime >= SAMPLE_RATE / freq_dip1) sinetime = 0;
   }
   
   // Do your processing and program functionality here. ****.

   //out_sample = (0x0000FFFF & sample_data) | 
   // 	        (0xFFFF0000 & (sample_data << 16));

   if(DSK6713_DIP_get(3) == 0) // Change Phase of right channel
   {
   		out_sample = (0x0000FFFF & sample_data) | 
    	        (0xFFFF0000 & (-sample_data << 16));
   }
   else
   {
   		out_sample = (0x0000FFFF & sample_data) | 
    	        (0xFFFF0000 & (sample_data << 16));
   } 

   output_sample(out_sample);//AIC23_data.uint
   
   return;
}

void gen_sine_table()
{
	
	// Generate your sine lookup table here. ****************.
	// Be aware of the data type you use to hold the data.
	// Get sine data using the sinf(x) function, x is in radians.
	short i = 0;
	for(i = 0; i < SAMPLE_RATE / freq_dip1; i++)
	{
		sine_tab[i] = 100 * sin(2 * PI * freq_dip1 * i / SAMPLE_RATE);
	}
}

void main()
{
  // Generate sine lookup table.
  gen_sine_table();

  // Init DSK, codec, McBSP.
  comm_intr();
  DSK6713_LED_init();
  DSK6713_DIP_init();                  

  // Init DSK functionality. ********************************.
  // Call the init functions for the LEDs and DIPs 
  while(1); // Inf. loop. Interrupt-driven at this point.
}
