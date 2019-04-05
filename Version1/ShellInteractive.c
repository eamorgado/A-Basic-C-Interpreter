/*******************************************************************************
| Program: An Implementation of a C interper for interactive                   |
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