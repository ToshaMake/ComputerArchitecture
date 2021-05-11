#include "cpu.h"

void inputMemory(int address)
{
    printf("Input sign:\n");
    rk_mytermregime(1, 0, 0, 1, 1);
    scanf("%d", &sign[address]);
    if (sign[currCell.posRow * 10 + currCell.posCol] > 1)
    {
        rk_mytermregime(0, 0, 0, 0, 1);
        return;
    }
    printf("Input value:\n");
    if (!sign[address])
    {
        int command, operand, result;
        scanf("%2d%4d", &command, &operand);
        int retval = sc_commandEncode(command, operand, &result);
        if (retval != 0)
            printf("Input error");
        else
            sc_memorySet(address, result);
    }
    else
    {
        int result;
        scanf("%4d", &result);
        sc_memorySet(address, result + 32768);
    }
    rk_mytermregime(0, 0, 0, 0, 1);
    getchar();
    mt_gotoXY(1, 23);
    for (int i = 23; i < 27; i++)
    {
        for (int j = 1; j < 30; j++)
            putchar(' ');
        putchar('\n');
    }
    mt_gotoXY(1, 23);
}
void outMemory(int address)
{
    mt_gotoXY(1, 23);
    printf("Value:\n");
    int val;
    sc_memoryGet(address, &val);
    printf("%04d", val - 32768);
}
void loadAccum(int address)
{
    int val;
    sc_memoryGet(address, &val);
    sc_accumSet(val - 32768);
}

void storeAccum(int address)
{
    int val = sc_accumGet() + 32768;
    sign[address] = 1;
    sc_memorySet(address, val);
}

int ALU(int command, int operand)
{
    int val1, val2;
    int value = sc_accumGet();
    switch (command)
    {
    case 30:
        if (operand >= SIZE)
            return -1;
        sc_memoryGet(operand, &val1);
        value += (val1 - 32768);
        sc_accumSet(value);
        return 0;
    case 31:
        if (operand >= SIZE)
            return -1;
        sc_memoryGet(operand, &val1);
        value -= (val1 - 32768);
        sc_accumSet(value);
        return 0;
    case 32:
        if (operand >= SIZE)
            return -1;
        sc_memoryGet(operand, &val1);
        value /= (val1 - 32768);
        sc_accumSet(value);
        return 0;
    case 33:
        if (operand >= SIZE)
            return -1;
        sc_memoryGet(operand, &val1);
        value *= (val1 - 32768);
        sc_accumSet(value);
        return 0;
    case 66:
        if ((operand >= SIZE) && (value >= SIZE))
            return -1;
        sc_memoryGet(operand, &val1);
        sc_memoryGet(value, &val2);
        val1 -= 32768;
        val2 -= 32768;
        val1 -= val2;
        sc_accumSet(val1);
        return 0;
    default:
        return -1;
    }
    return -1;
}

int CU()
{
    int value, command, operand;
    sc_memoryGet(sc_counterGet(), &value);
    sc_commandDecode(value, &command, &operand);
    if ((!command) || (!operand))
    {
        sc_regSet(CLOCKIGNORE, 1);
        sc_regSet(COMMANDERROR, 1);
        return -1;
    }
    if ((command >= 30 && command <= 33) || command == 66)
    {
        ALU(command, operand);
    }
    else
    {
        switch (command)
        {
        case 10:
            if (operand >= SIZE)
                return -1;
            inputMemory(operand);
            return 0;
        case 11:
            if (operand >= SIZE)
                return -1;
            outMemory(operand);
            return 0;
        case 20:
            if (operand >= SIZE)
                return -1;
            loadAccum(operand);
            return 0;
        case 21:
            if (operand >= SIZE)
                return -1;
            storeAccum(operand);
            return 0;
        case 40:
            if (operand >= SIZE)
                return -1;
            sc_counterSet(operand - 1);
            return 0;
        case 41:
            if (operand >= SIZE)
                return -1;
            value = sc_accumGet();
            if (value < 0)
                sc_counterSet(operand - 1);
            return 0;
        case 42:
            if (operand >= SIZE)
                return -1;
            value = sc_accumGet();
            if (value == 0)
                sc_counterSet(operand - 1);
            return 0;
        case 43:
            sc_regSet(CLOCKIGNORE, 1);
            return 0;
        default:
            return -1;
        }
    }
    return 0;
}
