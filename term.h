#ifndef TERM_H
#define TERM_H

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

typedef enum {
	White = 7,
	Black = 0,
	Red = 1,
	Green = 2,
	Yellow = 3,
	Blue = 4,
	Magenta = 5,
	Cyan = 6
}colors;

typedef struct {
	unsigned short row;
	unsigned short col;
	unsigned short xpixel;
	unsigned short ypixel;
}winsize;

int mt_clrscr(void);
int mt_gotoXY(int x, int y);
int mt_getscreensize(int* rows, int* cols);
int mt_setfgcolor(colors color);
int mt_setbgcolor(colors color);

#endif