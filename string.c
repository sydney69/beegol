#include "parser.h"


struct txt string(char argument [255])
{
	struct txt string;
	
	strcpy(string.name,argument);
	strcpy(string.value,"");

	return string;
}



