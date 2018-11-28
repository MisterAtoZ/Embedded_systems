#include "gpio.c"

void main()
{
	//First initialize:
	gpio_init();
	volatile unsigned int i;
	//Next set all GPIO-pins as output:
	set_GPIO_output(&gpio[21]);
	
	while (1)
	{
		

		set_pin(&gpio[21]);

		volatile unsigned int tim;
		for(tim = 0; tim < 500000; tim++);
	

		clear_pin(&gpio[21]);

		//Delay again
		for(tim = 0; tim < 500000; tim++);
	
	}	
}

