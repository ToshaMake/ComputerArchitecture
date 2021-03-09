#include "shell.h"
#include "command.h"
#include "bigchars.h"
#include "readkey.h"
#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

static struct Cell{
    int posRow;
    int posCol;
} currCell;

static inline void setDefaultColor()
{
    mt_setbgcolor(White);
    mt_setfgcolor(Black);
}

void repaintCell()
{
    fillContext();
    drawMemory();
    drawFlags();
    drawKeys();
    drawAccumulator();
    drawOperation();
    drawInstructionCounter();
    drawBigCell();
}

void inputMemory();
void inputAccumulator();
void inputCounter();

int shell() {
    currCell.posCol = 0;
    currCell.posRow = 0;

    setDefaultColor();
    rk_mytermregime(0, 0, 0, 0, 1);
    mt_clrscr();

    fillContext();
    drawMemory();
    drawFlags();
    drawKeys();
    drawAccumulator();
    drawOperation();
    drawInstructionCounter();
    drawBigCell();

    mt_gotoXY(1, 25);
    int key;
    while (1) {
        rk_readkey(&key);

        switch (key) {
        case KEY_right: {
            if (currCell.posCol < 9) {
                currCell.posCol++;
                repaintCell();
            }
            break;
        }
        case KEY_down: {
            if (currCell.posRow < 9) {
                currCell.posRow++;
                repaintCell();
            }
            break;
        }
        case KEY_left: {
            if (currCell.posCol > 0) {
                currCell.posCol--;
                repaintCell();
            }
            break;
        }
        case KEY_up: {
            if (currCell.posRow > 0) {
                currCell.posRow--;
                repaintCell();
            }
            break;
        }
        case KEY_q: {
            rk_mytermregime(1, 0, 0, 1, 1);
            exit(0);
            break;
        }
        case KEY_i: {
            sc_memoryLoad("reset.bin");
            repaintCell();
            break;
        }
        case KEY_s: {
            mt_gotoXY(1, 25);
            printf("file name:\n");
            char fileName[250];
            scanf("%s", fileName);
            sc_memorySave(fileName);
            repaintCell();
            break;
        }
        case KEY_l: {
            mt_gotoXY(1, 25);
            printf("file name:\n");
            char fileName[250];
            scanf("%s", fileName);
            sc_memoryLoad(fileName);
            repaintCell();
            break;
        }
        case KEY_enter: {
            mt_gotoXY(1, 25);
            inputMemory();
            getchar();
            repaintCell();
            break;
        }
        case KEY_f5: {
            mt_gotoXY(1, 25);
            inputAccumulator();
            getchar();
            drawAccumulator();
            break;

        }
        case KEY_f6: {
            mt_gotoXY(1, 25);
            inputCounter();
            getchar();
            drawInstructionCounter();
            break;
        }
        case KEY_other:
            break;
        }
    }

}

void fillContext(){
    int height, width;
    mt_getscreensize(&height, &width);

    mt_gotoXY(0, 0);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++)
            putchar(' ');
        putchar('\n');
    }
}

void drawOperation(){
    int offsetCol = 63;
    int offsetRow = 7;

    bc_box(offsetCol, offsetRow, 20, 3);
    mt_gotoXY(5 + offsetCol, offsetRow);
    printf(" Operation ");
    mt_gotoXY(7 + offsetCol ,offsetRow + 1);
    printf("+00 : 00");
}

void printFlagReg() {
    int val;
    char printBuff[5] = { ' ', ' ', ' ', ' ', ' ' };

    sc_regGet(OVERFLOW, &val);
    if (val)
        printBuff[0] = 'O';
    sc_regGet(ZEROERROR, &val);
    if (val)
        printBuff[1] = 'Z';
    sc_regGet(OUTMEMORY, &val);
    if (val)
        printBuff[2] = 'S';
    sc_regGet(CLOCKIGNORE, &val);
    if (val)
        printBuff[3] = 'C';
    sc_regGet(COMMANDERROR, &val);
    if (val)
        printBuff[4] = 'I';

    for (int i = 0; i < 5; i++) {
        putchar(printBuff[i]);
        putchar(' ');
    }
}

void drawFlags(){
    int offsetCol = 63;
    int offsetRow = 10;
    bc_box(offsetCol, offsetRow, 20, 3);
    mt_gotoXY(offsetCol+6, offsetRow);
    printf(" Flags ");
    mt_gotoXY(offsetCol + 7, 1 + offsetRow);
    printFlagReg();
}

static void getMemBuff(char buff[6], int const command, int const operand)
{
    buff[0] = '+';
    buff[1] = command / 10 + 0x30;
    buff[2] = command % 10 + 0x30;
    buff[3] = operand / 10 + 0x30;
    buff[4] = operand % 10 + 0x30;
    buff[5] = '\0';
}

void wrong_str_memory(char buff[6]) {
    buff[0] = '-';
    for (int i = 1; i < 5; i++)
        buff[i] = '0';
    buff[5] = '\0';
}

static void drawMemIndex(int index) {
    int memValue;
    int command;
    int operand;
    int retval;
    char buff[6];

    retval = sc_memoryGet(index, &memValue);
    if (retval != 0) {
        wrong_str_memory(buff);
        printf("%s", buff);
    }

    retval = sc_commandDecode(memValue, &command, &operand);
    if (retval != 0) {
        wrong_str_memory(buff);
        printf("%s", buff);
    }
    getMemBuff(buff, command, operand);
    printf("%s", buff);
}

void drawMemory() {
    bc_box(1, 1, 62, 12);
    mt_gotoXY(26, 1);
    printf(" Memory ");

    for (int row = 0; row < 10; row++) {
        for (int col = 0; col < 10; col++) {
            mt_gotoXY((col *6) + 2, row + 2);
            drawMemIndex(row * 10 + col);
            putchar(' ');
        }
    }
    mt_gotoXY((currCell.posCol * 6) + 2, currCell.posRow + 2);
    mt_setbgcolor(Black);
    mt_setfgcolor(White);
    drawMemIndex(currCell.posRow * 10 + currCell.posCol);
    setDefaultColor();
    //putchar(' ');
}

void drawKeys() {
    int offsetCol = 47;
    int offsetRow = 13;
    bc_box(offsetCol, offsetRow, 36, 10);
    mt_gotoXY(offsetCol+1, offsetRow);
    printf(" Keys:");
    mt_gotoXY(offsetCol + 1, offsetRow + 1);
    printf("q - quit");
    mt_gotoXY(offsetCol+1, offsetRow+2);
    printf("l - load");
    mt_gotoXY(offsetCol+1, offsetRow+3);
    printf("s - save");
    mt_gotoXY(offsetCol+1, offsetRow+4);
    printf("r - run");
    mt_gotoXY(offsetCol+1, offsetRow+5);
    printf("t - step");
    mt_gotoXY(offsetCol+1, offsetRow+6);
    printf("i - reset");
    mt_gotoXY(offsetCol+1, offsetRow+7);
    printf("F5 - accumulator");
    mt_gotoXY(offsetCol+1, offsetRow+8);
    printf("F6 - instructionCounter");
}

void drawAccumulator() {
    int offsetCol = 63;
    int val = sc_accumGet();
    int comm, operand;
    char buff[6];

    sc_commandDecode(val, &comm, &operand);

    bc_box(offsetCol, 1, 20, 3);
    mt_gotoXY(offsetCol+4, 1);
    printf(" accumulator ");
    mt_gotoXY(offsetCol+7, 2);

    getMemBuff(buff, comm, operand);

    printf("%s", buff);
}

void drawInstructionCounter() {
    const int offsetCol = 63;
    const int offsetRow = 4;
    int val = sc_counterGet();
    int comm, operand;
    char buff[6];

    sc_commandDecode(val, &comm, &operand);

    bc_box(offsetCol, offsetRow, 20, 3);
    mt_gotoXY(offsetCol+1, offsetRow);
    printf("intructionCounter ");
    mt_gotoXY(offsetCol + 7, 1 + offsetRow);

    getMemBuff(buff, comm, operand);

    printf("%s", buff);
}

void get_zero(int value[2]) {
    value[0] = 1717976064;
    value[1] = 3958374;
}

void get_one(int value[2]) {
    value[0] = 1010315264;
    value[1] = 3158064;
}

void get_two(int value[2]) {
    value[0] = 1010842624;
    value[1] = 8258050;
}

void get_three(int value[2]) {
    value[0] = 2120252928;
    value[1] = 8282238;
}

void get_four(int value[2]) {
    value[0] = 2120640000;
    value[1] = 6316158;
}

void get_five(int value[2]) {
    value[0] = 1040350720;
    value[1] = 4079680;
}

void get_six(int value[2]) {
    value[0] = 35789824;
    value[1] = 1974814;
}

void get_seven(int value[2]) {
    value[0] = 811630080;
    value[1] = 396312;
}

void get_eight(int value[2]) {
    value[0] = 1013332992;
    value[1] = 3958374;
}

void get_nine(int value[2]) {
    value[0] = 2087074816;
    value[1] = 3956832;
}

void get_plus(int value[2]) {
    value[0] = 2115508224;
    value[1] = 1579134;
}
void get_minus(int value[2]) {
    value[0] = 2113929216;
    value[1] = 126;
}

void choiseBigVal(int val, int retVal[2])
{
    switch (val) {
    case 0:
        get_zero(retVal);
        return;
    case 1:
        get_one(retVal);
        return;
    case 2:
        get_two(retVal);
        return;
    case 3:
        get_three(retVal);
        return;
    case 4:
        get_four(retVal);
        return;
    case 5:
        get_five(retVal);
        return;
    case 6:
        get_six(retVal);
        return;
    case 7:
        get_seven(retVal);
        return;
    case 8:
        get_eight(retVal);
        return;
    case 9:
        get_nine(retVal);
        return;
    }
}

void drawBigCell() {
    int memVal, command, operand;
    int offsetRow = 13;
    int offsetCol = 1;
    int valueChar[2];
    bc_box(offsetCol, offsetRow, 46, 10);
    sc_memoryGet(currCell.posRow * 10 + currCell.posCol, &memVal);
    if (sc_commandDecode(memVal, &command, &operand) != 0) {
        command = 0;
        operand = 0;
        get_minus(valueChar);
        bc_printbigchar(valueChar, offsetCol+1, offsetRow+1, Black, White);
        offsetCol += 9;
        get_zero(valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
        offsetCol += 9;
        get_zero(valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
        offsetCol += 9;
        get_zero(valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
        offsetCol += 9;
        get_zero(valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
    }
    else {
        get_plus(valueChar);
        bc_printbigchar(valueChar, offsetCol+1, offsetRow + 1, Black, White);        
        offsetCol += 9;
        choiseBigVal(command / 10, valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);       
        offsetCol += 9;
        choiseBigVal(command % 10, valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);      
        offsetCol += 9;
        choiseBigVal(operand / 10, valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);    
        offsetCol += 9;
        choiseBigVal(operand % 10, valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
    }
    mt_gotoXY(1, 25);
}
void inputMemory()
{
    printf("Input value:\n");
    rk_mytermregime(0, 0, 0, 1, 1);
    int command, operand, result;
    scanf("%2d%2d", &command, &operand);
    int retval = sc_commandEncode(command, operand, &result);
    if (retval != 0)
        printf("Input error");
    else
        sc_memorySet((currCell.posRow * 10 + currCell.posCol), result);

    rk_mytermregime(0, 0, 0, 0, 1);
}
void inputAccumulator()
{
    printf("Input value:\n");
    rk_mytermregime(0, 0, 0, 1, 0);
    int command, operand, result;
    scanf("%2d%2d", &command, &operand);
    int retval = sc_commandEncode(command, operand, &result);
    if (retval != 0) {
        printf("Input error");
        rk_mytermregime(0, 0, 0, 0, 1);;
    }
    sc_accumSet(result);
    rk_mytermregime(0, 0, 0, 0, 1);
}

void inputCounter()
{
    printf("Input value:\n");
    rk_mytermregime(0, 0, 0, 1, 0);
    int command, operand, result;
    scanf("%2d%2d", &command, &operand);
    int retval = sc_commandEncode(command, operand, &result);
    if (retval != 0 || (command == 0)) {
        printf("Input error");
        rk_mytermregime(0, 0, 0, 0, 1);;
    }
    sc_counterSet(result);
    rk_mytermregime(0, 0, 0, 0, 1);
}