#include "parser.h"

struct numeric word(char argument[255])
{
	struct numeric number;
	
	strcpy(number.name,argument);
	number.type = 0;
	number.value = 0;

	return number;
}
