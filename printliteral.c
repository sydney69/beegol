#include "parser.h"


void printliteral(int stringsIndex,struct txt strings[],char argument[255],char *subroutines[])
{
	
	char buf[10];
	int tempcounter = 0;
	int subfound = 0;
			
	// look at ../code/6502/print/main.asm
	//add string literal to strings table and name it string<stringsIndex>
						
	sprintf(buf,"string%d",stringsIndex);			
	strcpy(strings[stringsIndex].name,buf);
	strcpy(strings[stringsIndex].value,argument);
	stringsIndex++;
				
	//set printvector to string<x> and call printstring subroutine
	fprintf(outFile,"lda #LO(%s)\n",buf);
	fprintf(outFile,"sta printvector\n");
	fprintf(outFile,"lda #HI(%s)\n",buf);
	fprintf(outFile,"sta printvector+1\n");
	fprintf(outFile,"ldy #0\n");
	fprintf(outFile,"jsr printstring\n");
				
	//add printstring subroutine if it has not been added to sub file	
	while(!strcmp(subroutines[tempcounter],""))
	{
		if(strcmp(subroutines[tempcounter],"printstring")==0)
		{
			subfound=1;
		}
		tempcounter++;
	}
	if(subfound == 0)
	{
		fprintf(subFile,"\n\n.printstring\n");
		fprintf(subFile,"lda (printvector),y\n");
		fprintf(subFile,"beq printend\n");
		fprintf(subFile,"jsr osasci\n");
		fprintf(subFile,"iny\n");
		fprintf(subFile,"bne printstring\n");
		fprintf(subFile,".printend\n");
		fprintf(subFile,"rts\n");
	}
	subfound=0;
}



