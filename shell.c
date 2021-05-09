#include "shell.h"

// int sign[100];

// static struct Cell
// {
//     int posRow;
//     int posCol;
// } currCell;

struct sigaction act;

static inline void setDefaultColor()
{
    mt_setbgcolor(White);
    mt_setfgcolor(Black);
}

//void inputMemory(int address);
void inputAccumulator();
void inputCounter();
void iterCounter();
void repaintCell();
void reset();
void sigHandler(int signo)
{
    int clockFlag;
    sc_regGet(CLOCKIGNORE, &clockFlag);
    if (clockFlag)
        return;
    if (signo == SIGALRM)
    {
        CU();
        iterCounter();
        drawInstructionCounter(1);
        drawMemory();
        drawBigCell();
        drawFlags();
        drawAccumulator();
        mt_gotoXY(1, 25);
    }
    else if (signo == SIGUSR1)
    {
        reset();
    }
}
void stepCU()
{
    CU();
    iterCounter();
    drawInstructionCounter(1);
    drawMemory();
    drawBigCell();
    mt_gotoXY(1, 25);
}

void repaintCell()
{
    fillContext();
    drawMemory();
    drawFlags();
    drawKeys();
    drawAccumulator();
    drawOperation(currCell.posRow * 10 + currCell.posCol);
    drawInstructionCounter();
    drawBigCell();
}

void reset()
{
    sc_regInit();
    sc_regSet(8, 1);
    sc_memoryInit();
    sc_accumSet(0);
    repaintCell();
}
int shell()
{
    sc_regInit();
    sc_memoryInit();
    currCell.posCol = 0;
    currCell.posRow = 0;

    act.sa_handler = &sigHandler;
    act.sa_flags = SA_RESTART;
    sigemptyset(&act.sa_mask);
    sc_regSet(CLOCKIGNORE, 1);

    sigaction(SIGALRM, &act, NULL);
    sigaction(SIGUSR1, &act, NULL);

    struct itimerval nval;
    nval.it_interval.tv_sec = 0;
    nval.it_interval.tv_usec = 500;
    nval.it_value.tv_sec = 0;
    nval.it_value.tv_usec = 2;

    setitimer(ITIMER_REAL, &nval, NULL);

    setDefaultColor();
    rk_mytermregime(0, 0, 0, 0, 1);
    mt_clrscr();

    repaintCell();

    mt_gotoXY(1, 25);
    int key;
    while (1)
    {
        rk_readkey(&key);
        switch (key)
        {
        case KEY_right:
        {
            if (currCell.posCol < 9)
            {
                currCell.posCol++;
                int a = sc_counterGet();
                a += 1;
                sc_counterSet(a);
                repaintCell();
            }
            break;
        }
        case KEY_down:
        {
            if (currCell.posRow < 9)
            {
                currCell.posRow++;
                int a = sc_counterGet();
                a += 10;
                sc_counterSet(a);
                repaintCell();
            }
            break;
        }
        case KEY_left:
        {
            if (currCell.posCol > 0)
            {
                currCell.posCol--;
                int a = sc_counterGet();
                a -= 1;
                sc_counterSet(a);
                repaintCell();
            }
            break;
        }
        case KEY_up:
        {
            if (currCell.posRow > 0)
            {
                currCell.posRow--;
                int a = sc_counterGet();
                a -= 10;
                sc_counterSet(a);
                repaintCell();
            }
            break;
        }
        case KEY_q:
        {
            sc_regSet(CLOCKIGNORE, 0);
            rk_mytermregime(1, 0, 0, 1, 1);
            exit(0);
            break;
        }
        case KEY_i:
        {
            sc_regSet(CLOCKIGNORE, 0);
            raise(SIGUSR1);
            sc_regSet(CLOCKIGNORE, 1);
            break;
        }
        case KEY_s:
        {
            mt_gotoXY(1, 25);
            rk_mytermregime(1, 0, 0, 1, 1);
            printf("file name:\n");
            char fileName[250];
            scanf("%s", fileName);
            getchar();
            rk_mytermregime(0, 0, 0, 0, 1);
            sc_memorySave(fileName);
            repaintCell();
            break;
        }
        case KEY_l:
        {
            mt_gotoXY(1, 25);
            rk_mytermregime(1, 0, 0, 1, 1);
            printf("file name:\n");
            char fileName[250];
            scanf("%s", fileName);
            getchar();
            rk_mytermregime(0, 0, 0, 0, 1);
            sc_memoryLoad(fileName);
            repaintCell();
            break;
        }
        case KEY_enter:
        {
            int value;
            sc_regGet(CLOCKIGNORE, &value);
            sc_regSet(CLOCKIGNORE, 1);
            mt_gotoXY(1, 25);
            inputMemory(sc_counterGet());
            getchar();
            if (!value)
                sc_regSet(CLOCKIGNORE, 0);
            repaintCell();
            break;
        }
        case KEY_f5:
        {
            mt_gotoXY(1, 25);
            inputAccumulator();
            getchar();
            repaintCell();
            break;
        }
        case KEY_f6:
        {
            mt_gotoXY(1, 25);
            inputCounter();
            getchar();
            repaintCell();
            break;
        }
        case KEY_r:
        {
            sc_regSet(CLOCKIGNORE, 0);
            //repaintCell();
            break;
        }
        case KEY_t:
        {
            stepCU();
            //repaintCell();
            break;
        }
        case KEY_other:
            break;
        }
    }
}

void fillContext()
{
    int height, width;
    mt_getscreensize(&height, &width);

    mt_gotoXY(0, 0);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            putchar(' ');
        putchar('\n');
    }
}

void printFlagReg()
{
    int val;
    char printBuff[5] = {' ', ' ', ' ', ' ', ' '};

    sc_regGet(OVERFLOW, &val);
    if (val)
        printBuff[0] = 'P';
    sc_regGet(ZEROERROR, &val);
    if (val)
        printBuff[1] = 'O';
    sc_regGet(OUTMEMORY, &val);
    if (val)
        printBuff[2] = 'M';
    sc_regGet(CLOCKIGNORE, &val);
    if (val)
        printBuff[3] = 'T';
    sc_regGet(COMMANDERROR, &val);
    if (val)
        printBuff[4] = 'E';

    for (int i = 0; i < 5; i++)
    {
        putchar(printBuff[i]);
        putchar(' ');
    }
}

void drawFlags()
{
    int offsetCol = 63;
    int offsetRow = 10;
    bc_box(offsetCol, offsetRow, 20, 3);
    mt_gotoXY(offsetCol + 6, offsetRow);
    printf(" Flags ");
    mt_gotoXY(offsetCol + 7, 1 + offsetRow);
    printFlagReg();
}

static void getMemBuffCom(char buff[6], int const command, int const operand)
{
    sprintf(buff, "+%02X%02X", command, operand);
}
static void getCounterBuffCom(char buff[6], int value)
{
    sprintf(buff, "+%04d", value);
}
static void getOperationBuffCom(char buff[8], int command, int operand)
{
    sprintf(buff, "+%02d:%03d", command, operand);
}
static void getMemBuffNum(char buff[6], int const value)
{
    sprintf(buff, "-%04X", value);
}
static void getCounterBuffNum(char buff[6], int value)
{
    sprintf(buff, "-%04d", value);
}
static void getOperationBuffNum(char buff[8], int const value)
{
    sprintf(buff, "-%04d", value);
}
static void getAccumulatorBuffPlus(char buff[8], int value)
{

    sprintf(buff, "+%04d", value);
}
static void getAccumulatorBuffMinus(char buff[8], int value)
{
    sprintf(buff, "-%04d", value);
}

void wrong_str_memory(char buff[6])
{
    sprintf(buff, "+0000");
}

void wrong_str_operation(char buff[7])
{
    buff[0] = '-';
    for (int i = 1; i < 6; i++)
        buff[i] = '0';
    buff[3] = ':';
    buff[6] = '\0';
}

void drawOperation(int index)
{
    int memValue;
    int command;
    int operand;
    int retval;
    int offsetCol = 63;
    int offsetRow = 7;
    char buff[8];

    bc_box(offsetCol, offsetRow, 20, 3);
    mt_gotoXY(5 + offsetCol, offsetRow);
    printf(" Operation ");
    mt_gotoXY(7 + offsetCol, offsetRow + 1);
    retval = sc_memoryGet(index, &memValue);
    if (retval != 0)
    {
        wrong_str_operation(buff);
        printf("%s", buff);
    }
    if (memValue < 32768)
    {
        retval = sc_commandDecode(memValue, &command, &operand);
        if (retval != 0)
        {
            wrong_str_operation(buff);
            printf("%s", buff);
        }
        getOperationBuffCom(buff, command, operand);
    }
    else
    {
        memValue -= 32768;
        getOperationBuffNum(buff, memValue);
    }

    printf("%s", buff);
}

static void drawMemIndex(int index)
{
    int memValue;
    int command;
    int operand;
    int retval;
    char buff[6];

    retval = sc_memoryGet(index, &memValue);
    if (retval != 0)
    {
        wrong_str_memory(buff);
        printf("%s", buff);
    }
    if (memValue < 32768)
    {
        retval = sc_commandDecode(memValue, &command, &operand);
        if (retval != 0)
        {
            wrong_str_memory(buff);
            printf("%s", buff);
        }
        getMemBuffCom(buff, command, operand);
    }
    else
    {
        getMemBuffNum(buff, memValue - 32768);
    }
    printf("%s", buff);
}

void drawMemory()
{
    bc_box(1, 1, 62, 12);
    mt_gotoXY(26, 1);
    printf(" Memory ");

    for (int row = 0; row < 10; row++)
    {
        for (int col = 0; col < 10; col++)
        {
            mt_gotoXY((col * 6) + 2, row + 2);
            drawMemIndex(row * 10 + col);
            putchar(' ');
        }
    }
    mt_gotoXY((currCell.posCol * 6) + 2, currCell.posRow + 2);
    mt_setbgcolor(Black);
    mt_setfgcolor(White);
    drawMemIndex(currCell.posRow * 10 + currCell.posCol);
    setDefaultColor();
}

void drawKeys()
{
    int offsetCol = 47;
    int offsetRow = 13;
    bc_box(offsetCol, offsetRow, 36, 10);
    mt_gotoXY(offsetCol + 1, offsetRow);
    printf(" Keys:");
    mt_gotoXY(offsetCol + 1, offsetRow + 1);
    printf("q - quit");
    mt_gotoXY(offsetCol + 1, offsetRow + 2);
    printf("l - load");
    mt_gotoXY(offsetCol + 1, offsetRow + 3);
    printf("s - save");
    mt_gotoXY(offsetCol + 1, offsetRow + 4);
    printf("r - run");
    mt_gotoXY(offsetCol + 1, offsetRow + 5);
    printf("t - step");
    mt_gotoXY(offsetCol + 1, offsetRow + 6);
    printf("i - reset");
    mt_gotoXY(offsetCol + 1, offsetRow + 7);
    printf("F5 - accumulator");
    mt_gotoXY(offsetCol + 1, offsetRow + 8);
    printf("F6 - instructionCounter");
}

void drawAccumulator()
{
    int offsetCol = 63;
    int val = sc_accumGet();
    int comm, operand;
    char buff[6];

    bc_box(offsetCol, 1, 20, 3);
    mt_gotoXY(offsetCol + 4, 1);
    printf(" accumulator ");
    mt_gotoXY(offsetCol + 7, 2);
    if (val >= 0)
        getAccumulatorBuffPlus(buff, val);
    else
    {
        val = val * -1;
        getAccumulatorBuffMinus(buff, val);
    }

    printf("%s", buff);
}

void drawInstructionCounter(int full)
{
    const int offsetCol = 63;
    const int offsetRow = 4;
    int val = sc_counterGet();
    char buff[6];
    if (full)
    {
        bc_box(offsetCol, offsetRow, 20, 3);
        mt_gotoXY(offsetCol + 1, offsetRow);
        printf("intructionCounter ");
        mt_gotoXY(offsetCol + 7, 1 + offsetRow);
    }
    getCounterBuffCom(buff, val);
    printf("%s", buff);
    mt_gotoXY(1, 25);
}

void get_zero(int value[2])
{
    value[0] = 1717976064;
    value[1] = 3958374;
}

void get_one(int value[2])
{
    value[0] = 1010315264;
    value[1] = 3158064;
}

void get_two(int value[2])
{
    value[0] = 1010842624;
    value[1] = 8258050;
}

void get_three(int value[2])
{
    value[0] = 2120252928;
    value[1] = 8282238;
}

void get_four(int value[2])
{
    value[0] = 2120640000;
    value[1] = 6316158;
}

void get_five(int value[2])
{
    value[0] = 1040350720;
    value[1] = 4079680;
}

void get_six(int value[2])
{
    value[0] = 35789824;
    value[1] = 1974814;
}

void get_seven(int value[2])
{
    value[0] = 811630080;
    value[1] = 396312;
}

void get_eight(int value[2])
{
    value[0] = 1013332992;
    value[1] = 3958374;
}

void get_nine(int value[2])
{
    value[0] = 2087074816;
    value[1] = 3956832;
}

void get_plus(int value[2])
{
    value[0] = 2115508224;
    value[1] = 1579134;
}
void get_minus(int value[2])
{
    value[0] = 2113929216;
    value[1] = 126;
}
void get_a(int value[2])
{
    value[0] = 2118269952;
    value[1] = 4342338;
}
void get_b(int value[2])
{
    value[0] = 1044528640;
    value[1] = 4080194;
}
void get_c(int value[2])
{
    value[0] = 37895168;
    value[1] = 3949058;
}
void get_e(int value[2])
{
    value[0] = 2114092544;
    value[1] = 8258050;
}
void get_d(int value[2])
{
    value[0] = 1111637504;
    value[1] = 4080194;
}
void get_f(int value[2])
{
    value[0] = 33717760;
    value[1] = 131646;
}

void choiseBigVal(int val, int retVal[2])
{
    switch (val)
    {
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
    case 10:
        get_a(retVal);
        return;
    case 11:
        get_b(retVal);
        return;
    case 12:
        get_c(retVal);
        return;
    case 13:
        get_d(retVal);
        return;
    case 14:
        get_e(retVal);
        return;
    case 15:
        get_f(retVal);
        return;
    }
}

void drawBigCell()
{
    int memValue, command, operand;
    int offsetRow = 13;
    int offsetCol = 1;
    int valueChar[2];
    bc_box(offsetCol, offsetRow, 46, 10);
    sc_memoryGet(currCell.posRow * 10 + currCell.posCol, &memValue);
    if (memValue >= 32768)
    {
        memValue -= 32768;
        int val1, val2, val3, val4;
        val4 = memValue % 16;
        memValue = memValue / 16;
        val3 = memValue % 16;
        memValue = memValue / 16;
        val2 = memValue % 16;
        memValue = memValue / 16;
        val1 = memValue % 16;
        get_minus(valueChar);
        bc_printbigchar(valueChar, offsetCol + 1, offsetRow + 1, Black, White);
        offsetCol += 9;
        choiseBigVal(val1, valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
        offsetCol += 9;
        choiseBigVal(val2, valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
        offsetCol += 9;
        choiseBigVal(val3, valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
        offsetCol += 9;
        choiseBigVal(val4, valueChar);
        bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
    }
    else
    {
        if (sc_commandDecode(memValue, &command, &operand) == 0)
        {
            get_plus(valueChar);
            bc_printbigchar(valueChar, offsetCol + 1, offsetRow + 1, Black, White);
            offsetCol += 9;
            choiseBigVal(command / 16, valueChar);
            bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
            offsetCol += 9;
            choiseBigVal(command % 16, valueChar);
            bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
            offsetCol += 9;
            choiseBigVal(operand / 16, valueChar);
            bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
            offsetCol += 9;
            choiseBigVal(operand % 16, valueChar);
            bc_printbigchar(valueChar, offsetCol, offsetRow + 1, Black, White);
        }
    }
    mt_gotoXY(1, 25);
}

void inputAccumulator()
{
    printf("Input value:\n");
    rk_mytermregime(1, 0, 0, 1, 1);
    int result;
    scanf("%5d", &result);
    sc_accumSet(result);
    rk_mytermregime(0, 0, 0, 0, 1);
}

void inputCounter()
{
    printf("Input value:\n");
    rk_mytermregime(1, 0, 0, 1, 0);
    int val;
    scanf("%2d", &val);
    sc_counterSet(val);
    currCell.posCol = val % 10;
    currCell.posRow = val / 10;
    rk_mytermregime(0, 0, 0, 0, 1);
}
void iterCounter()
{
    int val1, val2, a;
    sc_regGet(COMMANDERROR, &val1);
    sc_regGet(CLOCKIGNORE, &val2);
    a = sc_counterGet();
    if (!(val2 && val1))
        a++;
    if (a == 100)
        a = 0;
    sc_counterSet(a);
    currCell.posCol = a % 10;
    currCell.posRow = a / 10;
}