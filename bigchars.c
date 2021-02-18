#include "bigchars.h"

int bc_printA(char* str)
{
	printf("\E(0%s\E(B", str);
	return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
	int x, y, i;
	mt_clrscr();
	mt_getscreensize(&y, &x);
	if ((x1 < 0) || (y1 < 0) || (x1+x2 > x) || (y1+y2 > y) || (x2 < 2) || (y2 < 2))
		return -1;
	mt_gotoXY(x1, y1);
	bc_printA(BORDER_TL);
	for (i = 0; i < x2 - 2; i++)
		bc_printA(BORDER_HO);
	bc_printA(BORDER_TR);
	for (i = 1 ; i < y2-1; i++)
	{
		mt_gotoXY(x1, y1+i);
		bc_printA(BORDER_VE);
		mt_gotoXY(x1+x2-1, y1+i);
		bc_printA(BORDER_VE);
	}
	mt_gotoXY(x1, y1+y2-1);
	bc_printA(BORDER_BL);
	for (i = 0; i < x2 - 2; i++)
		bc_printA(BORDER_HO);
	bc_printA(BORDER_BR);
	printf("\n");
	return 0;
}

int bc_printbigchar(int* big, int x, int y, colors fg, colors bg)
{
	int x1, y1, i, j;
	mt_clrscr();
	mt_getscreensize(&y1, &x1);
	if ((x < 0) || (y < 0) || (x + 8 > x1) || (y + 8 > y1))
		return -1;
	mt_setfgcolor(fg);
	mt_setbgcolor(bg);
	mt_gotoXY(x, y);
	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if ((big[i / 4] >> ((i % 4) * 8 + j -1) & 1))
				bc_printA(BORDER_RE);
			else
				printf(" ");
			mt_gotoXY(x + j, y + i);
		}
	}
	mt_setfgcolor(White);
	mt_setbgcolor(Black);
	return 0;
}

int bc_setbigcharpos(int* big, int x, int y, int value)
{
	if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0) || (value > 1))
		return -1;
	if (value == 0)
		big[y/4] &= ~(1 << (8 * (y % 4) + x));
	else
		big[y/4] |= 1 << (8 * (y % 4) + x);

	return 0;

}

int bc_getbigcharpos(int* big, int x, int y, int* value)
{
	if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
		return -1;
	*value = big[y / 4] >> 8 * (y % 4) + x;
	return 0;
}

int bc_bigcharwrite(int fd, int* big, int count)
{
	int	flag = write(fd, big, count * sizeof(int));
	if (flag == -1)
		return -1;
	//printf("%d", flag);
	return 0;
}

int bc_bigcharread(int fd, int* big, int need_count, int* count)
{
	int flag = read(fd, big, need_count * sizeof(int));
	if (flag == -1)
		return -1;
	*count = flag / (sizeof(int) * 2);
	//printf("%d", flag);
	return 0;
}
