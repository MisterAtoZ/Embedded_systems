/******** uart.c file of C2.5 : UART Driver Code ********/
/*** bytes offsets of UART registers from char *base ***/

#define UART_BASE 0x20201000
#define UDR 0x00
#define UFR 0x18
#define TXFF 0x20
#define RXFE 0x10
#define BUSY 0x08
#define RXFF 0x40
#define TXFE 0x80

volatile char * base = (char *) UART_BASE;

/*
Legende:
UDR = Data register: for read/write chars
UFR = Status of UART port, contains:

	7 	6 	 5 	  4    3   2 1 0
| TXFE RXFF TXFF RXFE BUSY - - - |

Legend for flags:
TXFE = Tx buffer empty
TXFF = Tx buffer full
RXFE = Rx buffer empty
RXFF = Rx buffer full
BUSY = device busy
*/

int ugetc() // input a char from UART pointed by up
{
	while (*(base+UFR) & RXFE); // loop if UFR is REFE:
	//Loop als de waarde die op het adres base+UFR staat AND RXFE 1 is,
	//dus feitelijk als op adres base+UFR de waarde RXFE staat, en er dus niks staat
	//dat je kan lezen in de Rx buffer
	return *(base+UDR); // return a char in UDR
	//Returnt de waarde die nu ontvangen is
}

int uputc(char c) // output a char to UART pointed by up
{
	//Deze code zegt:
	//wacht tot de Tx buffer leeg is,
	//Daarna verstuur je iets
	while (*(base+UFR) & TXFF); // loop if UFR is TXFF
	
	*(base+UDR) = c; // write char to data register
}

int ugets(char *s) // input a string of chars
{
	while ((*s = ugetc()) != '\r') 
	//De '\r' is de "carriage return" of "enter"
	{
		uputc(*s);
		s++;
	}
	*s = 0;
}

int uprints(char *s) // output a string of chars
{
	while (*s)
	uputc(*s++);
}

/*
int uart_init() // UART initialization function
{
	int i; UART *up;
	for (i=0; i<4; i++) // uart0 to uart2 are adjacent
	{
		up = &uart[i];
		up->base = (char *)(0x20200100 + i*0x1000);
		up->n = i;
	}
	uart[3].base = (char *)(0x10009000); // uart3 at 0x10009000
}
*/

/*
typedef volatile struct uart{
	char *base; // base address; as char *
	int n; // uart number 0-3
	}UART;
UART uart[4]; // 4 UART structures
*/