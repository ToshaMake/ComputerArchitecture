#ifndef SHELL_H
#define SHELL_H

#include "command.h"
#include "bigchars.h"
#include "readkey.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

int shell();

void drawMemory();
void drawAccumulator();
void drawInstructionCounter();
void drawOperation();
void drawFlags();
void drawKeys();
void drawBigCell();
void fillContext();
//void fillRow(int row);

#endif
