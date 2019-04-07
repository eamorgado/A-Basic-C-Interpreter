/*******************************************************************************
| Program: Main function for the CInterpreter mode                             |
| Last Updated: 4/4/2019       FCUP       Copyright (c) 2019, Eduardo Morgado  |
********************************************************************************
|   The program functionality:                                                 |
|       ->Checks if the program was executed giving a file, if so, opens it and|
|           opens the ShellFile mode other wise, goes to the ShellInteractive  |
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "ShellFile.h"
#include "ShellInteractive.h"

int main(int argc, char const *argv[]){
    if(argc==2){
        printf("File.%s|\n",argv[1]);
        FILE* F;
        if(access(argv[1],F_OK)!=-1){
            F=fopen(argv[1],"r");
            if(F==NULL){
                printf("Error While Opening %s\n",argv[1]);
                exit(0);
            }
            shellFile(F);
        }else{
            printf("File Doesn't Exist\n");
            exit(0);
        }
    }else{
        shellInteractive();
    }
    return 0;
}
