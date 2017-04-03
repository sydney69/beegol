#include "parser.h"

//probably change this so that the ORG address can be
//set by the user passing the required address in 
//through a parameter

void begin(void)
{
	fprintf(outFile,"INCLUDE \"acornconstants.asm\"\n");
	fprintf(outFile,"ORG &2000\n");
	fprintf(outFile,".start\n");
}
