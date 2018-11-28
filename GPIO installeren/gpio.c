/*****gpio.c*****/
#include "defines.h"
volatile unsigned int* gpio_reg;
typedef volatile struct gpio{
	int sel;
	int bit;
	int set;
	int clr;
	int gpio_bit;
}GPIO;
GPIO gpio[27];
void gpio_init(){
	gpio_reg = (unsigned int*)GPIO_BASE;
	int i;
	int tiental;
	GPIO *gp;
	for(i = 0; i<=27;i++){
		gp = &gpio[i];
		gp->bit = (i%10)*3;
		gp->set = GPIO_GPSET0;
		gp->clr = GPIO_GPCLR0;
		gp->gpio_bit = i;
		tiental = i/10;
		switch (tiental){
			case 0:
			gp->sel = GPIO_GPFSEL0;
			break;
			case 1:
			gp->sel = GPIO_GPFSEL1;
			break;
			case 2:
			gp->sel = GPIO_GPFSEL2;
			break;
		default: break;
		}
	}
}
void set_GPIO_output(GPIO *up){
	gpio_reg[up->sel] |= (1 << up->bit);
}

void set_pin(GPIO *up){
	gpio_reg[up->set] = (1 << up->gpio_bit);
}

void clear_pin(GPIO *up) {
	gpio_reg[up->clr] = (1 << up->gpio_bit);
}