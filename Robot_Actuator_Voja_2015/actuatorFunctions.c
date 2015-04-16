#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "actuatorFunctions.h"
#include "control.h"
#include "uart.h"
#include "can.h"

#define ACTIVATE	1
#define DEACTIVATE	-1

void knockDownTheClapperboards(unsigned char side)
{
	if(side == 1)
	{
		AX_SetAngle(60, 180, 1, AX_SERVO1);//izbaci udaraljku sa desne strane
			_delay_ms(1000);
		AX_SetAngle(160, 180, 1, AX_SERVO1);//uvuce udaraljku sa desne strane
			_delay_ms(1000);
		
	}else
	{
		AX_SetAngle(160, 180, 1, AX_SERVO3);//izbaci udaraljku sa leve strane
			_delay_ms(1000);
		AX_SetAngle(60, 180, 1, AX_SERVO3);//uvuce udaraljku sa leve strane
			_delay_ms(1000);
		
	}
}//END OF knockDownTheClapperboards

void colectThePopcorn(unsigned char side)
{
	if(side == 1)
	{
		AX_SetAngle(60, 180, 1, AX_SERVO2);//otvori ruku za uzimanje kokica sa desne strane
		_delay_ms(1000);
		AX_SetAngle(160, 180, 1, AX_SERVO2);//zatvori ruku za uzimanje kokica sa desne strane
		_delay_ms(1000);	
		
	}else
	{
		AX_SetAngle(60, 180, 1, AX_SERVO4);//otvori ruku za uzimanje kokica sa leve strane
		_delay_ms(1000);
		AX_SetAngle(160, 180, 1, AX_SERVO4);//zatvori ruku za uzimanje kokica sa leve strane
		_delay_ms(1000);
	}
}//END OF colectThePopcorn

void rightDiafram(unsigned char state)
{
	DDRE |= (1 << PINE4);
	
	if (state == ACTIVATE)
	{
		PORTE |= (1 << PINE4);
	}else
	{
		PORTE &= ~(1 << PINE4);
	}
	
}//END OF valveOnOff

void leftDiafram(unsigned char state)
{
	DDRE |= (1 << PINE5);
	
	if (state == ACTIVATE)
	{
		PORTE |= (1 << PINE5);
	}else
	{
		PORTE &= ~(1 << PINE5);
	}
	
}//END OF valveTwoOnOff

void liftMove(unsigned char state)
{
	DDRF |= (1 << PINF7);//CS1
	DDRF |= (1 << PINF6);//INA1
	DDRF |= (0 << PINF5);//INB1
	DDRE |= (1 << PINE3);//PWM1
	
	if (state == ACTIVATE)
	{
		PORTE |= (1 << PINE3);
	} 
	else
	{
		PORTE &= ~(1 << PINE3);
		
	}
		
}//END OF liftOnOff

void action(canMsg msg)
{
	unsigned char command = msg.data[0];
	unsigned char side, state;
	
	switch(command)
	{
		case 'A':
			side = msg.data[1];
			knockDownTheClapperboards(side);
				break;
				
		case 'B':
			side = msg.data[1];
			colectThePopcorn(side);
				break;
				
		case 'C':
			state = msg.data[1];
			leftDiafram(state);
				break;
				
		case 'D':
			state = msg.data[1];
			rightDiafram(state);
				break;
				
		case 'E':
			state = msg.data[1];
			liftMove(state);
				break;
	}
}