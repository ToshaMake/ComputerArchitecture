#include "command.h"


int sc_commandEncode(int command, int operand, int* value)
{
    if ((command < 10) || (command > 11 && command < 20)
        || (command > 21 && command < 30)
        || (command > 33 && command < 40)
        || (command > 43 && command < 51)
        || (command > 76)) {
        sc_regSet(COMMANDERROR, 1);
        return -1;
    }
    if (operand > 127 || operand < 0) {
        return -2;
    }
    *value = (command << 7) | operand;
    return 0;
}

int sc_commandDecode(int value, int* command, int* operand)
{
    if (value >> 14 != 0) {
        sc_regSet(COMMANDERROR, 1);
        return 1;
    }
    *command = value >> 7;
    *operand = value & 0x7F;
	return 0;
}
