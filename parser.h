#include <string.h>
#include <stdio.h>

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

extern FILE *outFile;			//the output file
extern FILE *subFile;			//the subroutine file


struct numeric byte(char argument[]);
struct numeric word(char argument[]);
struct txt string(char argument[]);
void begin(void);
void rem(char line[]);
void mode(char argument[255]);
void label(char argument[255]);
void gotolabel(char argument[255]);
void end(int NumbersIndex,struct numeric numbers[],int StringsIndex,struct txt strings[]);
void printliteral(int stringsIndex,struct txt strings[],char argument[255],char **subroutines);
