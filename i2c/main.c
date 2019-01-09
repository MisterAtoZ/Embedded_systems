/********************************************************************
Main file inspired by the armc-013.c file from the Raspberry-Pi Bare
Metal Tutorials by Brian Sidebotham and modified to implement an
interrupt-driven device driver for the Raspberry Pi 1 Model b+.
********************************************************************/

#include "rpi-interrupts.h" // other exception handlers
#include "rpi-gpio.h"
#include "rpi-uart.h"
#include "rpi-i2c.h"
#include "acceleroSensor.h"
#include "stdio.h"

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
	gpio_init();
	set_GPIO_alterfunc(&gpio[14], 4); //Set TX Pin
	set_GPIO_alterfunc(&gpio[15], 4); //Set RX Pin

	set_GPIO_pullup(&gpio[2]);
	set_GPIO_pullup(&gpio[3]);

	set_GPIO_alterfunc(&gpio[2], 4); //Set SDA Pin
	set_GPIO_alterfunc(&gpio[3], 4); //Set SCL Pin

	/* Enable the timer interrupt IRQ */
    RPI_GetIrqController()->Enable_IRQs_2 = RPI_IRQ_2_ARM_UART_IRQ;

	/* Initialize uart and allow uart to send interrupts */
	uart_init();				// initialize UARTs

	/* Enable interrupts */
	_unlock();
	//uprintf("after unlock\r\n");
	//Initialize I2C
	i2c_init();

	uprintf("\n\r\nSTARTING... \n\r");

	acceleroSensor_setup();

	char line[128];
	while(1){
		uprintf("Begin while loop \n");
		acceleroSensor_values();
		delay_ms(1000);
		/*uprintf("Enter a line from UARTS\n\r");
		ugets(&uart, line);
		uprintf("%s\n", line);*/
	}
}