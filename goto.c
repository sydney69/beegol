#include "parser.h"

//goto command - jump to a label
void gotolabel(char argument[255])	
{
	fprintf(outFile,"jmp %s\n",argument);
}
		
