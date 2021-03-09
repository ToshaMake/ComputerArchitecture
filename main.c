#include "command.h"
#include "bigchars.h"
#include "readkey.h"
#include "shell.h"
int main() {


    //int test;
    //sc_memoryInit();
    //sc_regInit();
    //int commandMy=0;
    //int command, operand;
    //int result = sc_commandEncode(75, 100, &commandMy);
    //int result2 = sc_commandDecode(commandMy, &command, &operand);
    //printf("True result encode = %d\n%d\n%d\n%d\n%d\n", result, commandMy, result2, command, operand); // 0= true, 1 - false
    //result = sc_commandEncode(12, 128, &commandMy);
    //printf("False result encode = %d\n", result);
    //result = sc_memorySet(50, commandMy);
    //printf("True Memory result = %d\n", result);
    ////result = sc_memorySet(101, commandMy);
    //// printf("False memory result = %d", result);

    //int test;
    //sc_memoryInit();
    //sc_regInit();
    //int commandMy=0;
    //int command, operand;
    //int result = sc_commandEncode(75, 100, &commandMy);
    //int result2 = sc_commandDecode(commandMy, &command, &operand);
    //printf("True result encode = %d\n%d\n%d\n%d\n%d\n", result, commandMy, result2, command, operand);
    //sc_printReg();
    //result = sc_commandEncode(8, 128, &commandMy);
    //printf("False result encode = %d\n", result);
    //result = sc_memorySet(50, commandMy);
    //printf("True Memory result = %d\n", result);
    //result = sc_memorySet(101, commandMy);
    // printf("False memory result = %d", result);


    //sc_memorySave("file.bin");
    //sc_memoryInit();
    //sc_memoryLoad("file.bin");

	//sc_memorySet(200, 20);
    //result = sc_memoryGet(0, &commandMy);
    //printf("%d\n", result);
    //sc_printReg();


    //result = sc_memoryGet(0, &commandMy);
    //printf("%d\n", result);
    //mt_clrscr();
    //mt_gotoXY(9,5);
    //mt_setfgcolor(Red);
    //printf("ANTON RUDENKO");
    //mt_gotoXY(7, 6);
    //mt_setbgcolor(White);
    //mt_setfgcolor(Green);
    //printf("IV-922");
    //mt_gotoXY(1, 10);
    //mt_setbgcolor(Black);
    //mt_setfgcolor(White);
    //int x, y;
    //mt_getscreensize(&x, &y);
    //printf("%d\n%d\n", x, y);
    //bc_printA("aaaaaaaaaa");
    //bc_box(10, 5, 8, 8);
    //int fd = open("fil.bin", O_CREAT | O_RDWR | O_TRUNC);
    //int a[2] = { 2115508224, 1579134 };
    //int d[2];
    //int b;
    //int flag;
    //bc_setbigcharpos(a, 0, 0, 1);
    //bc_bigcharwrite(fd, a, 2);
    //int ff = open("fil.bin", O_RDONLY);
    //flag = bc_bigcharread(ff, d, 2, &b);
    //bc_printbigchar(a, 1, 1, Red, Black);
    //bc_getbigcharpos(a, 1, 0, &b);
    //printf("%d\n%d\n", d[0], d[1]); 
    //printf("%d", b);
    //rk_readkey(&b);
    //rk_mytermsave();
    //rk_mytermregime(0, 0, 0, 0, 1);
    //rk_mytermrestore();
    //printf("%d", b);
    //mt_clrscr();
    //bc_box(10, 5, 8, 8);
    shell();
	return 0;
}
