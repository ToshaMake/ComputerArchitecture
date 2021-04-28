#include "cpu.h"

int ALU(int command, int operand)
{
    int val = sc_accumGet();
    int comm, oper;
    sc_commandDecode(val, &comm, &oper);

    switch (command)
    {
    case 30:
        oper += operand;
        sc_commandEncode(comm, oper, &val);
        sc_accumSet(val);
        return 0;
    case 31:
        oper -= operand;
        sc_commandEncode(comm, oper, &val);
        sc_accumSet(val);
        return 0;
    case 32:
        oper /= operand;
        sc_commandEncode(comm, oper, &val);
        sc_accumSet(val);
        return 0;
    case 33:
        oper *= operand;
        sc_commandEncode(comm, oper, &val);
        sc_accumSet(val);
        return 0;
    case 66:
        // oper /= operand;
        // sc_commandEncode(comm, oper, &val);
        // sc_accumSet(val);
        return 0;
    default:
        break;
    }
    return -1;
}
int CU()
{
    int value, command, operand;
    sc_memoryGet(sc_counterGet(), &value);
    if (sc_commandDecode(value, &command, &operand) != 0)
    {
        sc_regSet(CLOCKIGNORE, 1);
        return -1;
    }
    if ((command >= 30 && command <= 33) || command == 66)
    {
        ALU(command, operand);
    }
    else
    {
    }
    raise(SIGALRM);
    return 0;
}