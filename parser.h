#include <string.h>

struct numeric
{
	char name[20];
	int type;// 0 = byte, 1 = word (not implemented yet!)
	int value;
};

struct txt
{
	char name[20];
	char value[255];
};


struct numeric byte(char argument[]);
struct numeric word(char argument[]);
struct txt string(char argument[]);
void begin(void);
