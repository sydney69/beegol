#include "parser.h"

void begin(void)
{
	fprintf(outFile,"INCLUDE \"acornconstants.asm\"\n");
	fprintf(outFile,"ORG &2000\n");
	fprintf(outFile,".start\n");
)
