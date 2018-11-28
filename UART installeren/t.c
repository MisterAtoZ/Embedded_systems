/************* t.c file of C2.5 **************/
int v[] = {1,2,3,4,5,6,7,8,9,10}; // data array
int sum;
#include "uart.c" // UART driver code file
#include "gpio.c"
int main()
{
	gpio_init();
	set_GPIO_ALT0(&gpio[14]);
	set_GPIO_ALT0(&gpio[15]);
	
	int i;
	char string[64];
	//UART *up;
	//uart_init(); // initialize UARTs
	//up = &uart[0]; // test UART0
	uprints("Enter lines from serial terminal 0\n\r");
	while(1)
	{
		ugets(string);
		uprints(" ");
		uprints(string);
		uprints("\n\r");
		if (strcmp(string, "end")==0)
			break;
	}
	
	uprints("Compute sum of array:\n\r");
	sum = 0;
	for (i=0; i<10; i++) sum += v[i];
	uprints("sum = ");
	uputc((sum/10)+'0'); uputc((sum%10)+'0');
	uprints("\n\rEND OF RUN\n\r");
}