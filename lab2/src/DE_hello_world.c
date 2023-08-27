#include <sys/alt_stdio.h>
#include <stdio.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"

int main()
{
	int switch_datain;
	alt_putstr("Hello from Nios II!\n");
	alt_putstr("When you press Push Button 0,1 the switching on of the LEDs is done by software\n");
	alt_putstr("But, Switching on/off of LED 2 by SW 2 is done by hardware\n");
	/* Event loop never exits. Read the PB, display on the LED */

	while (1)
	{
		//Gets the data from the pb, recall that a 0 means the button is pressed
		switch_datain = ~IORD_ALTERA_AVALON_PIO_DATA(BUTTON_BASE);
		//Mask the bits so the leftmost LEDs are off (we only care about LED3-0)
		switch_datain &= (0b0000000011);
		//Send the data to the LED
		IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE,switch_datain);

	}
	return 0;
}
