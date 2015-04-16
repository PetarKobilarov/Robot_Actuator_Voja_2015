#ifndef ACTUATORFUNCTIONS_H_
#define ACTUATORFUNCTIONS_H_

#include "can.h"

void knockDownTheClapperboards(unsigned char side);
void colectThePopcorn(unsigned char side);
void leftDiafram(unsigned char state);
void rightDiafram(unsigned char state);
void liftMove(unsigned char state);
void action(canMsg msg);

#endif