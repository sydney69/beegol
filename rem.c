#include "parser.h"

//rem command - remark - comments added to output file as comment

void rem(char line[500])
{
	line[0] = '\\';
	line[1] = '\\';
	line[2] = ' ';
	fprintf(outFile,"%s",line);
}
