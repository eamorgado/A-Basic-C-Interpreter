/*******************************************************************************
| Program: An Implementation of the interpreter for File mode                  |
| Last Updated: 4/4/2019       FCUP       Copyright (c) 2019, Eduardo Morgado  |
********************************************************************************
|   The program functionality:                                                 |
|       ->Works almost like the interactive mode except it will read from file |
*******************************************************************************/
#include "CInterpreter.h"
#include "ShellFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char* readFile(FILE* F){
    /*
     * Reades from the file and allocates the instruction in memory
     */
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
    /*
     * The open function, executes the REPL, the functions createMem, error, 
     *      parser and execute are the general CInterpreter. 
     */
    createMem();    
    int status=1;
    do{
        parser(readFile(F),1,F);
        status=execute(0,1,F);
    }while(status==1);
    printf("Error occured in execution\n");
    error(1,F);
}