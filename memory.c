#include "memory.h"

#define SIZE 100
#define MIN 0

int memory[SIZE];

int sc_memoryInit()
{
    for (int i = 0; i < SIZE; i++)
        memory[i] = 0;
	return 0;
}

int sc_memorySet(int address, int value)
{
    if (address > SIZE || address < MIN) {
        sc_regSet(OUTMEMORY, 1); // out of memory
        return 1;
    }
    memory[address] = value;
    return 0;
}

int sc_memoryGet(int address, int* value)
{
    if (address > SIZE || address < MIN) {
        sc_regSet(OUTMEMORY, 1); // out of memory 
        return 1;
    }
    *value = memory[address];
    return 0;
}

int sc_memorySave(char* filename)
{
    FILE* file = fopen(filename, "wb");
    if (file == NULL)
        return -1;
    int flag = fwrite(memory, sizeof(int), SIZE, file);
    if (!flag)
        return -1;
    fclose(file);
    return 0;
}

int sc_memoryLoad(char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
        return -1;
    int flag = fread(memory, sizeof(int), SIZE, file);
    if (!flag)
        return -1;
    fclose(file);
    return 0;
}

