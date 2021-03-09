#include "register.h"

int flag;
int accumReg = 0;
int counterReg = 0;

int sc_regInit()
{
	flag = 0;
	return 0;
}
void sc_regNULL() {
    flag = 0;
}
int sc_regSet(int reg, int value)
{
    if (reg > 16 || reg < 1) 
        return -1;
    if (value = 0)
        flag = flag & ~reg;
    else if (value = 1)
        flag = flag | reg;
    else return -2;

	return 0;
}

int sc_regGet(int reg, int* value)
{
    if (reg > 16 || reg < 1)
        return -1;
    if ((flag & ~reg) == 0)
        *value = 0;
    else 
        *value = 1;
	return 0;
}

void sc_printReg(){
	printf("%d", flag);
}

void sc_accumSet(int val)
{
    accumReg = val;
}

int sc_accumGet()
{
    return accumReg;
}

void sc_counterSet(int val)
{
    counterReg = val;
}

int sc_counterGet()
{
    return counterReg;
}