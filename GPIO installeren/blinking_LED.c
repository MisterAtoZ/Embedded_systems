#include "gpio.c"

void main()
{
	//First initialize:
	gpio_init();
	volatile unsigned int i;
	//Next set all GPIO-pins as output:
	for(i = 0;i<28;i++){
	set_GPIO_output(&gpio[i]);
	}
	
	while (1)
	{
		
		for(i = 0;i<28;i++){
			set_pin(&gpio[i]);
		}

		volatile unsigned int tim;
		for(tim = 0; tim < 500000; tim++);
	

		for(i = 0;i<28;i++){
			clear_pin(&gpio[i]);
		}

		//Delay again
		for(tim = 0; tim < 500000; tim++);
	
	}	
}

