#ifndef SHELL_H
#define SHELL_H

#include "cpu.h"
#include "bigchars.h"
#include "readkey.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int shell();

void drawMemory();
void drawAccumulator();
void drawInstructionCounter();
void drawOperation();
void drawFlags();
void drawKeys();
void drawBigCell();
void fillContext();

#endif
