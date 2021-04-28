#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <stdlib.h>
#include "register.h"
#include "command.h"
#include "memory.h"
#include <signal.h>
#include <sys/time.h>

int ALU(int command, int operand);
int CU();

#endif