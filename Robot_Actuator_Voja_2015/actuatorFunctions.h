#ifndef ACTUATORFUNCTIONS_H_
#define ACTUATORFUNCTIONS_H_

#include "can.h"

void knockDownTheClapperboards(unsigned char side);
void colectThePopcorn(unsigned char side);
void action(canMsg msg);

#endif