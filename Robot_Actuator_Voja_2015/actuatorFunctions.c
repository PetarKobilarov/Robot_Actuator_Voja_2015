#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "actuatorFunctions.h"
#include "control.h"
#include "uart.h"
#include "can.h"

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

void action(canMsg msg)
{
	unsigned char command = msg.data[0];
	unsigned char side = msg.data[1];
	
	switch(command)
	{
		case 'A':
			knockDownTheClapperboards(side);
				break;
				
		case 'B':
			colectThePopcorn(side);
				break;
	}
}