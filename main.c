//commands start at line 148

//begin work on let.

/******************************************************************
Program: BEEGOL - BEEb Game Oriented Language
Purpose
	Simple language compiler to produce beebasm compatible 
	assembler source file for use in writing games for the
	BBC Micro 
How?
	It will work by reading each line from the source file 
	and translating it into 6502 assembler.

	Numeric variable declarations will be added to a variable
	table. String varaibles and constants will be added to a 
	string table. When a command is read the corresponding 
	code will be written to the output file. Any subroutines
	needed will be added to the subroutines file which will be
	included in the output file. The variable and string tables
	will then be written to the output file.

Usage: beegol file

	* only 1 command per line
	* all lines must end with a ;
	* each command must be followed by 1 space
	* arguments must contain no spaces
	* arithemtic must use the 'let' command
	* all commands must be entered in lower case
	* maximum of 255 (256?) variables
	* maximum line length of 500 characters
	* maximum string length of 255 characters
	* all byte/word variables are initialised to 0 on creation

******************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include "parser.h"

char* changesuffix(char file[], char suffix[]);
void checkValidFilename(char file[]);
FILE *openInputFile(char file[]);
char *getTerm(char line[], int position);
void errorQuit(int lineno,char *text);

FILE *inFile;			//the input file
FILE *outFile;			//the output file
FILE *subFile;			//the subroutine file


int main(int argc, char *argv[])
{
	int lineNumber = 0;	// counter to track line number
	int i = 0;	//general variable for use in loops
	char line[500];	//line read from a file
	char INFILENAME[20];	//the input filename
	char OUTFILENAME[20];	//the outout filename
	char SUBFILENAME[25];	//the subroutine filename

	char command[20];		//string extracted from input file
	char argument[30];		//string extracted from input file
	int found;				//command found so no error
	int phase;              //(0) - declaration or (1) - code
	int subfound;

	///////////////////////////////////////////////////////////////////

	// array of strings to record which commands have been added to the 
	// subroutine file. 255 entries - 20 chars long should be enough for now.
	char subroutines[255][20];

	struct numeric numbers[255];
	struct txt strings[255];
	int numbersIndex;
	int stringsIndex;
	
	

///////////////////////////////////////////////////////////////////

	if(argc == 1) 		
	{	
		printf("BEEGOL - BEEb Game Oriented Language\n\n");
		printf("Usage: beegol <filename>\n");	
		exit(0);	//exit program sucessfully
	}

/////////////////////////////////////////////////////////////////////////
// File setup
	
	strcpy(INFILENAME,argv[1]);				//copy 1st argument into INFILENAME
	checkValidFilename(INFILENAME); 			//check filename is in format name.bgl
	inFile = openInputFile(INFILENAME);			//open file for reading
	strcpy(OUTFILENAME,changesuffix(INFILENAME,".asm"));	//name asm file
	strcpy(SUBFILENAME,changesuffix(INFILENAME,".sub"));	//name subfile
	outFile = fopen(OUTFILENAME,"w");			//open asm file
	subFile = fopen(SUBFILENAME,"w");			//open sub file
	
	for(i=0;i<256;i++)
	{	
		strcpy(numbers[i].name,"");
		numbers[i].type = 0;
		numbers[i].value=0;
		
		strcpy(strings[i].name,"");
		strcpy(strings[i].value,"");
	
		strcpy(subroutines[i],"");
		
	}


////////////////////////////////////////////////////////////////////////////////	
//	parser


	phase = 0;
	lineNumber = 0;
	numbersIndex = 0;
	stringsIndex = 0;

	
		
	while ( fgets(line,255,inFile)!= NULL) 
	{
		i=0;
		found = 0;
		subfound = 0;
		lineNumber++;	

		//get command
		strcpy(command,getTerm(line,i));
		i = i+strlen(command)+1;
		printf("\ncommand = %s",command);	
		
		if (line[strlen(command)] != ';')
		{
			//get argument
			strcpy(argument,getTerm(line,i));
			i = i+strlen(argument)+1;
			printf("\nargument = %s",argument);
		}
		else
		{
			printf("\nNo argument");
		}
			
	

//byte command

		if(strcmp(command,"byte") == 0)
		{
			found = 1;
			numbers[numbersIndex]=byte(argument);
			numbersIndex++;
			
		}

//word command - declares a variable of type word

		if(strcmp(command,"word") == 0)
		{
			found = 1;
			numbers[numbersIndex]=word(argument);
			numbersIndex++;
		}

// string command - declares a variable of type string

		if(strcmp(command,"string") == 0)
		{
			found = 1;				
			strings[stringsIndex]=string(argument);	//possible conflict with strings.h here
			stringsIndex++;
		}

//begin command - marks end of variable declarations

		if(strcmp(command,"begin") == 0)
		{
			found = 1;
			begin();
		}


//rem command - remark - comments added to output file as comment
		if(strcmp(command,"rem") == 0)
		{
			found = 1;
			rem(line);
		}

//mode command - set screenmode

		if(strcmp(command,"mode") == 0)
		{
			found = 1;
			mode(argument);
		}

//label command - for use with goto

		if(strcmp(command,"label") == 0)
		{
			found = 1;
			label(argument);
		}

//goto command - jump to a label

		if(strcmp(command,"goto") == 0)
		{
			found = 1;
			gotolabel(argument);
		}

//end command - marks end of program

		if(strcmp(command,"end") == 0)
		{
			found = 1;
			end(numbersIndex,numbers,stringsIndex,strings);
		}


//print command - print string/variable to screen		

		if(strcmp(command,"print") == 0)
		{
			found = 1;
			
			//get real argument as get term only returns chars upto 1st space
			for(i=6;i<(strlen(line)-2);i++)
			{
				argument[i-6]=line[i];
			}
			argument[i-7] = '\0';
			
//there are 5 (maybe more?) possibilities here:	
	// ( 1 ) string literal  : "blah blah blah";
	
			if(argument[0]=='"')
			{
				printliteral(stringsIndex,strings,argument,subroutines);
			}
		
	// ( 2 ) string variable :
	// ( 3 ) byte variable   : <byte> or <byte> <+-/*> <byte> etc
	// ( 4 ) word variable   : <word> or <word> <+-/*> <word> etc
	// ( 5 ) nothing         : ;

		}


		//command not recognised
		
		if(!found)
		{	
			//errorQuit(inFile,outFile,lineNumber,"Unknown command");
			errorQuit(lineNumber,"Unknown command");
		}

	}
	
////////////////////////////////////////////////////////////////////////////////	
	
	//close input file
	fclose( inFile );
	fclose( outFile );	
	fclose(subFile);
	return 0;
}


//////////////////////////////////////////////////////////////////////////////

FILE *openInputFile(char file[20])
{
	FILE *inputFile;
	inputFile = fopen(file,"r");
	//if file does not open succesfully then exit program
	if(inputFile==0)
	{	
		printf("Error opening file - does it exist?\n");
		exit(-1);				//exit program unsucessfully
	}
	return inputFile;
}


void checkValidFilename(char file[20])
{
	int length = 0;			//used in string manipulations
	char suffix[5];			//used to test input file suffix is .bgl	

	length = strlen(file);	//get length of filename
	
	//if filename is < 5 then it can't be a valid filename as
	//the shortest valid filename is 5 characters eg a.bgl
	if(length<5)
	{	
		printf("Invalid filename\n");
		exit(-1);			//exit program unsucessfully
	}
	
	//copy last 4 chars of filename (suffix) to suffix string
	for(int i=0;i<5;i++)
	{
		suffix[i] = file[length-4+i];
	}
	
	//compare suffix string to ".bgl", exit if not the same
	if(strcmp(suffix,".bgl"))
	{
		printf("Filename must have .bgl suffix\n");
		exit(-1);				//exit program unsucessfully
	}	
}


char* changesuffix(char file[20], char suffix[5])
{
	static char returnstring[20];
	int i = 0;
	
//	strcpy(returnstring,"");
	while(file[i] != '.')
	{
			returnstring[i] = file[i];
			i++;
	}

	for(int loop=0;loop<5;loop++)
	{
		returnstring[i]=suffix[loop];
		i++;
	}

//	strcat(returnstring,suffix);
	returnstring[i+4] = '\0';
	
	return returnstring;
}

char *getTerm(char line[255],int position)
{
	static char term[255];
	int i=0;
	
	strcpy(term,"");
	while(line[position] != ' ' && line[position] != ';')
	{
		term[i] = line[position];
		i++;
		position++;
	}		
	term[i] = '\0';
	return term;
}

void errorQuit(int lineno, char *text)
{
	printf("\n\nLine %d : Error - %s\n",lineno,text);
	fclose( inFile );
	fclose( outFile );	
	fclose( subFile );
	exit (-1);
}
