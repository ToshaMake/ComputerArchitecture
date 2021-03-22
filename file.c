#include "hard.h"
#include <stdlib.h>
int main(){
    tCHS* chs = malloc(20);
    tLBA* lba = malloc(32);
    tLARGE* large = malloc(24);
    tIDECHS* idechs = malloc(28);

    int h;
    int s;
    int c;
    int sectionSize;
    int diskSize;
    int choose;
    int freeSpace = 1;
    char active;
    int size = 11;
 
	int tableMas[size][size];
   
    printf("Input geometry\n");
    printf("C: ");
    scanf("%d", &c);
    printf("H: ");
    scanf("%d", &h);
    printf("S: ");
    scanf("%d", &s);
    //printf("Input disk size: ");
    //scanf("%d", &diskSize);
    printf("Free space: ");
    scanf("%d", &freeSpace);
    printf("Input section size: ");
    scanf("%d", &sectionSize);
    
    printf("Тип:\n");
    printf("1 - CHS 2- LARGE 3 - IDECHS\n");
    scanf("%d", &choose);
    
        switch(choose){
		case 1:
			chs -> c = c;
			chs -> h = h;
			chs -> s = s;
			break;
		case 2:
			large -> c = c;
			large -> h = h;
			large -> s = s;
			break;
		case 3:
			idechs -> c = c;
			idechs -> h = h;
			idechs -> s = s;
			break;
		default:
			printf("Wrong choose");
			return 0;
		}
	printf("Free space: %d\n", freeSpace - sectionSize);

	printf("Set section as active (y/n):\n");
	scanf("%c", &active);
	mas[0][0] = active;
	mas[0][1] = 0;
	mas[0][2] = 0;
	mas[0][3] = 1;
	
    while ( (freeSpace -= sectionSize)> 0){
		
	printf("Input section size\n");
    scanf("%d", &sectionSize);	
	printf("Set section as active (y/n):\n");
	scanf("%c", &active);
	printf("Free space: %d\n", freeSpace - sectionSize);
	}	
	printf("Active | CSH start | Type | CHS finish | LBA start | Size\n");

}
