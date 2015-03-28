#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "actuatorFunctions.h"
#include "control.h"
#include "uart.h"
#include "can.h"

int main(void)
{
	DDRE |= (1 << PINE4);
	PORTE &= (~(1 << PINE4));
	AX_UART_Init();
	CAN_Init();
	
	_delay_ms(1000);

	canMsg message;
	
    while(1)
    {
       CAN_read(&message);
	   
	   action(message);  
    }
}