#include "term.h"

int mt_clrscr(void)
{
	printf("\E[H\E[J");
	return 0;
}

int mt_gotoXY(int x, int y)
{
	int rows, cols;
	mt_getscreensize(&rows, &cols);
	if (!((y < rows) && (x < cols) && (x >= 0) && (y >= 0)))
		return -1;
	else {
		printf("\E[%d;%dH", y, x);
		return 0;
	}
}

int mt_getscreensize(int* rows, int* cols)
{
	winsize ws;
	if (!ioctl(1, TIOCGWINSZ, &ws)) {
		*rows = ws.row;
		*cols = ws.col;
	}
	else
		return -1;
	return 0;
}
int mt_setfgcolor(colors color)
{
	printf("\E[3%dm", color);
	return 0;
}
int mt_setbgcolor(colors color)
{
	printf("\E[4%dm", color);
	return 0;
}
