#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "actuatorFunctions.h"
#include "control.h"
#include "uart.h"
#include "can.h"
#include "system.h"

#define ACTIVATE	1
#define DEACTIVATE	-1
#define CLOSE		2

void knockDownTheClapperboards(signed char side, signed char state)
{
	if(state == ACTIVATE)
	{
		if(side == 1)
		{
			AX_SetAngle(60, 240, 1, AX_SERVO1);//izbaci udaraljku sa desne strane
		}else
		{
			AX_SetAngle(160, 180, 1, AX_SERVO3);//izbaci udaraljku sa leve strane
		}
	}else
	{
		if(side == 1)
		{
			AX_SetAngle(160, 240, 1, AX_SERVO1);//uvuce udaraljku sa desne strane
		}else
		{
			AX_SetAngle(60, 180, 1, AX_SERVO3);//uvuce udaraljku sa leve strane
		}
	}
	
}//END OF knockDownTheClapperboards

void colectThePopcorn(signed char side, signed char state)
{
	if(state == ACTIVATE)
	{
		if(side == 1)
		{
			AX_SetAngle(300, 240, 1, AX_SERVO2);//otvori ruku za uzimanje kokica sa desne strane
		}else
		{
			AX_SetAngle(60, 240, 1, AX_SERVO4);//otvori ruku za uzimanje kokica sa leve strane
		}
	}else if(state == DEACTIVATE)
	{
		if(side == 1)
		{
			AX_SetAngle(280, 240, 1, AX_SERVO2);//zatvori ruku za uzimanje kokica sa desne strane
		}else
		{
			AX_SetAngle(100, 240, 1, AX_SERVO4);//zatvori ruku za uzimanje kokica sa leve strane
		}
	}else if(state == CLOSE)
	{
		if(side == 1)
		{
			AX_SetAngle(240, 240, 1, AX_SERVO2);//zatvori ruku za uzimanje kokica sa desne strane do kraja
			
		}else
		{
			AX_SetAngle(120, 240, 1, AX_SERVO4);//zatvori ruku za uzimanje kokica sa leve strane do kraja
		}
		
	}

}//END OF colectThePopcorn

void rightDiafram(signed char state)
{
	DDRE |= (1 << PINE4);
	
	if(state == ACTIVATE)
	{
		PORTE |= (1 << PINE4);
	}else
	{
		PORTE &= ~(1 << PINE4);
	}
	
}//END OF rightDiafram

void leftDiafram(signed char state)
{
	DDRE |= (1 << PINE5);
	
	if(state == ACTIVATE)
	{
		PORTE |= (1 << PINE5);
	}else
	{
		PORTE &= ~(1 << PINE5);
	}

}//END OF leftDiafram

void liftStates(signed char state)
{

	GPIO_OutputSet(chipSelect);
	GPIO_OutputSet(INA1);
	GPIO_OutputSet(PWM);
	GPIO_OutputReset(INB1);
	
	if(state == ACTIVATE)
	{
		GPIO_OutputSet(PWM);
	}else
	{
		GPIO_OutputReset(PWM);
	}
	
}//END OF liftMove

void action(canMsg msg)
{
	unsigned char command = msg.data[0];
	unsigned char side, state;
	
	switch(command)
	{
		case 'A':
		side = msg.data[1];
		state = msg.data[2];
		knockDownTheClapperboards(side, state);
		break;
		
		case 'B':
		side = msg.data[1];
		state = msg.data[2];
		colectThePopcorn(side, state);
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
		liftStates(state);
		break;
	}
}