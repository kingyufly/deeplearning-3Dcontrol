#ifndef _GPIO_H
#define _GPIO_H

#include "sys.h"

#define X PGout(13)
#define Y PGout(14)
#define Z PGout(15)
#define X_D PGout(3)
#define Y_D PGout(4)
#define Z_D PGout(5)
#define X_L1 PGin(0)
#define Y_L1 PGin(1)
#define Z_L1 PGin(2)
#define X_L2 PGin(6)
#define Y_L2 PGin(7)
#define Z_L2 PGin(8)

void Input_Init(void);
void Output_Init(void);

#endif
