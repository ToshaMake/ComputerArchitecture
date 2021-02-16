#include "term.h"
#ifndef BIGCHARS_H
#define BIGCHARS_H


#define BORDER_RE "a"
#define BORDER_BR "j"
#define BORDER_BL "m"
#define BORDER_TR "k"
#define BORDER_TL "l"
#define BORDER_VE "x"
#define BORDER_HO "q"


int bc_printA(char* str);

int bc_box(int x1, int y1, int x2, int y2);


#endif
