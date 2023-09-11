#include "STD_TYPES.h"
#include "7SEG_Private.h"
#include "DIO_Interface.h"
#include "7SEG_Interface.h"
#include <avr/delay.h>

// Create array to represent numbers to be displayed in 7 segment
static u8 Numbers[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};

// Function to display a number in 7 segment
void SEG_VoidDisplaySeg(u8 Number)
{
	// Set DDR of segment port as output
	DIO_VoidSetPortDirection(SEG_PORT, 1);

	// Display the number in the
	DIO_VoidSetPortValue(SEG_PORT, Number);
}

// Function to count numbers in 7 segment and indicate count with leds
void SEG_VoidCountSeg(void)
{
	// Initialize Data Direction Register (DDR) for portc
	DIO_VoidSetPortDirection(SEG_PORT, 0b11111111);

	// Initialize Data Direction Register (DDR) for portd
	DIO_VoidSetPortDirection(LED_PORT, 0b11111111);

	// Initialize a variable to hold leds states
	u8 led = 0b00000000;

	// Program loop
	while(1)
	{
		// Loop and display values from n1 to n2 in 7 segement
		for(int i=0; i<=9; i++)
		{
			// Display nimber in the 7 segment
			DIO_VoidSetPortValue(SEG_PORT, Numbers[i]);

			// turn on leds
			DIO_VoidSetPortValue(LED_PORT, led);
			if(i<=8)
			{
				led |= (1 << i);
			}
			else
			{
				DIO_VoidSetPortValue(LED_PORT, 0);
			}
			_delay_ms(1000);
		}

		// Reset led counter
		led = 0x0;
	}
}
