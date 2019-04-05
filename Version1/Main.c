/*******************************************************************************
| Program: Main Implementation of a C interper                                 |
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

int main(int argc, char const *argv[]){
    if(argc==2){
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
