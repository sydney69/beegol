#include "parser.h"

//label command - for use with goto

void label(char argument[255])
{
	fprintf(outFile,".%s\n",argument);
}
