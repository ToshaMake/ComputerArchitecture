#ifndef BIGCHARS_H
#define BIGCHARS_H

#include "term.h"
#include <fcntl.h>
//#include <io.h>
#include <errno.h>

#define BORDER_RE "a"
#define BORDER_BR "j"
#define BORDER_BL "m"
#define BORDER_TR "k"
#define BORDER_TL "l"
#define BORDER_VE "x"
#define BORDER_HO "q"


int bc_printA(char* str);

int bc_box(int x1, int y1, int x2, int y2);

int bc_printbigchar(int* big, int x, int y, colors fg, colors bg);

int bc_setbigcharpos(int* big, int x, int y, int value);

int bc_getbigcharpos(int* big, int x, int y, int* value);

int bc_bigcharwrite(int fd, int* big, int count);

int bc_bigcharread(int fd, int* big, int need_count, int* count);


#endif
