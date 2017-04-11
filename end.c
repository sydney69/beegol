#include "parser.h"

//end command - marks end of program
	
void end(int numbersIndex,struct numeric numbers[],int stringsIndex,struct txt strings[])	
{
	int i;
	//copy variables table to output file
	for(i=0;i<numbersIndex;i++)
	{
		fprintf(outFile,".%s ",numbers[i].name);
	
		if(numbers[i].type == 0) 
		{
			fprintf(outFile,"equb ");
		}
		else
		{
			fprintf(outFile,"equw ");
		}
		
		fprintf(outFile,"%d\n",numbers[i].value);
	}
	fprintf(outFile,"\n");
	
			
	//copy strings table to output file
		
	for(i=0;i<stringsIndex;i++)
	{
		fprintf(outFile,".%s ",strings[i].name);
		fprintf(outFile,"equs ");
		fprintf(outFile,"%s\n",strings[i].value);
		fprintf(outFile,"equb 0\n");
		
	}

	fprintf(outFile,"\n");
	
	fprintf(outFile,".end\n");
	fprintf(outFile,"SAVE \"MAIN\",start,end\n");
			
}
