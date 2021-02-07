#ifndef COMMAND_H
#define COMMAND_H

#include "memory.h"

#define FIRSTCODE 10
#define LASTCODE  76

int sc_commandEncode(int command, int operand, int* value);

int sc_commandDecode(int value, int* command, int* operand);

#endif