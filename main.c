#include "command.h"

int main() {

    int test;
    sc_memoryInit();
    sc_regInit();
    int commandMy=0;
    int command, operand;
    int result = sc_commandEncode(75, 100, &commandMy);
    int result2 = sc_commandDecode(commandMy, &command, &operand);
    printf("True result encode = %d\n%d\n%d\n%d\n%d\n", result, commandMy, result2, command, operand);
    sc_printReg();
    //result = sc_commandEncode(8, 128, &commandMy);
    //printf("False result encode = %d\n", result);
    result = sc_memorySet(50, commandMy);
    printf("True Memory result = %d\n", result);
    //result = sc_memorySet(101, commandMy);
    // printf("False memory result = %d", result);

    //sc_memorySave("file.bin");
    //sc_memoryInit();
    //sc_memoryLoad("file.bin");
	sc_memorySet(200, 20);
    result = sc_memoryGet(0, &commandMy);
    printf("%d\n", result);
    sc_printReg();

	return 0;
}
