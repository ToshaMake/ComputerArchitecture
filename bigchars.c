#include "bigchars.h"

int bc_printA(char* str)
{
	printf("\E(0%s\E(B", str);
	return 0;
}

int bc_box(int x1, int y1, int x2, int y2)
{
	int x, y, i;
	mt_getscreensize(&y, &x);
	if ((x1 < 0) || (y1 < 0) || (x2 > x) || (y2 > y) || (x2 - x1 < 2) || (y2 - y1 < 2))
		return -1;
	mt_gotoXY(x1, y1);
	bc_printA(BORDER_TL);
	for (i = x1 + 1; i < x2; i++)
		bc_printA(BORDER_HO);
	bc_printA(BORDER_TR);
	for (i = y1 + 1; i < y2; i++)
	{
		mt_gotoXY(x1, i);
		bc_printA(BORDER_VE);
		mt_gotoXY(x2, i);
		bc_printA(BORDER_VE);
	}
	mt_gotoXY(x1, y2);
	bc_printA(BORDER_BL);
	for (i = x1 + 1; i < x2; i++)
		bc_printA(BORDER_HO);
	bc_printA(BORDER_BR);
	return 0;
}
