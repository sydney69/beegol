#include "parser.h"

//mode command - set screenmode
void mode(char argument[255])
{
	fprintf(outFile,"lda #$16\n");
	fprintf(outFile,"jsr oswrch\n");
	fprintf(outFile,"lda #%s\n",argument);
	fprintf(outFile,"jsr oswrch\n");
}
