# BEEGOL - BEEb Game Oriented Language</p>

### Purpose

Simple language compiler to produce beebasm compatible assembler source file for use in writing games for the BBC Micro 

### How?
It will work by reading each line from the source file and translating it into 6502 assembler.

Numeric variable declarations will be added to a variable table. String varaibles and constants will be added to a string table. When a command is read the corresponding code will be written to the output file. Any subroutines needed will be added to the subroutines file which will be included in the output file. The variable and string tables will then be written to the output file.

Usage: beegol file

Rules:
* the beegol source file must end in .bgl
* only 1 command per line
* all lines must end with a ;
* commands and arguments must be seperated by 1 space
* arguments must contain no spaces
* arithemtic must use the 'let' command
* all commands must be entered in lower case
* maximum of 255 (256?) variables
* maximum line length of 500 characters
* maximum string length of 255 characters
* all byte/word variables are initialised to 0 on creation
* all string variables initialised to "" on creation.

