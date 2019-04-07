/*******************************************************************************
| Program: An Implementation of the interpreter for Interactie mode            |
| Last Updated: 4/4/2019       FCUP       Copyright (c) 2019, Eduardo Morgado  |
********************************************************************************
|   The program functionality:                                                 |
|       ->This mode is the default, if the program is executed without giving a|
|           text file the program will work by user input there you can also   |
|           open a file and change the instruction                             |
*******************************************************************************/
#include "CInterpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


char* readInteractive(){
    char aux[100],c,*l;
    int i=0;
    do{
        c=getchar();
    }while(!isalnum(c));
    if(c==';' || c=='\0'){
        printf("Ended\n");
        error(0,NULL);
    }
    do{
        aux[i++]=c;
        c=getchar();
    }while(c!=';' && c!='\0');
    aux[i]='\0';
    l=(char*)malloc(i+1);
    if(!l){
        printf("Error reading\n");
        error(0,NULL);
    }
    strcpy(l,aux);
    return l;
}
void shellInteractive(){
    /*
     * Open Function, initiates the REPL 
     */
    createMem();    
    int status=1;
    do{
        printf("C>");
        parser(readInteractive(),0,NULL);
        status=execute(0,0,NULL);
    }while(status==1);
    printf("Error occured in execution\n");
    error(0,NULL);
}