#include "register.h"

int flag;

int sc_regInit()
{
	flag = 0;
	return 0;
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
