#include <stdio.h>

#ifndef REGISTER_H
#define REGISTER_H

#define OVERFLOW 0b00000001 // overflow occured in action
#define ZEROERROR 0b00000010 // division by 0
#define OUTMEMORY 0b00000100 // out of memory
#define CLOCKIGNORE 0b00001000 // ignore impulse
#define COMMANDERROR 0b00010000 // wrong command

int sc_regInit();
int sc_regSet(int reg, int value);
int sc_regGet(int reg, int* value);
void sc_printReg();
void sc_accumSet(int val);
int sc_accumGet();
void sc_counterSet(int val);
int sc_counterGet();
#endif
