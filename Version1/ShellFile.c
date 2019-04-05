/*******************************************************************************
| Program: An Implementation of a C interper from file                         |
| Last Updated: 4/4/2019                                                       |
********************************************************************************
|   The program functionality:                                                 |
|       ->The program will be able to implement a small programming language   |
|       ->In memory we will keep 2 HashTables and 1 LinkedList. The HashTables |
|           will be [char*,Elem] and [char*,Instr] respectively, the first one |
|           will serve as a storage for the program variables, the second a    |
|           storage for labels were Instr is a pointer to the LinkedList of    |
|           instructions.                                                      |
|       ->The program will be able to both read interactivley or by loading a  |
|           file.                                                              |
*******************************************************************************/
#include "CInterpreter.h"
#include "ShellFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char* readFile(FILE* F){
    char aux[100],c,*l;
    int i=0;
    do{
        c=fgetc(F);
    }while(!isalnum(c));
    if(c==';' || c=='\0'){
        printf("Ended\n");
        error(1,F);
    }
    do{
        aux[i++]=c;
        c=fgetc(F);
    }while(c!=';' && c!='\0');
    aux[i]='\0';
    l=(char*)malloc(i+1);
    if(!l){
        printf("Error reading\n");
        error(1,F);
    }
    strcpy(l,aux);
    return l;
}
void shellFile(FILE* F){
    createMem();    
    int status=1;
    do{
        parser(readFile(F),1,F);
        status=execute(0,1,F);
    }while(status==1);
    printf("Error occured in execution\n");
    error(1,F);
}