/*******************************************************************************
| Program: An Implementation of a C interper                                   |
| Last Updated: 4/4/2019       FCUP       Copyright (c) 2019, Eduardo Morgado  |
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
#include "ParserExpression.h"
#include "Structures.h"
#include "LinkedListProgramSequence.h"
#include "HashTableVar.h"
#include "HashTableLabel.h"
#include "ShellFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>


HashTableLabel* Labels;
HashTableVar* Vars;
ProcessGroup* Program;


void createMem(){
    Labels=createLabelsTable();
    Vars=createVars();
    Program=createProgramQueue();
}
void freeMem(){
    freeTable(Vars);
    freeLabelTable(Labels);
    endExecution(Program);
}
void error(int is_file,FILE* F){
    if(is_file==1){
        fclose(F);
    }
    freeMem();
    exit(0);
}

void parser(char* line,int is_file,FILE* F){
    Instr* I=(Instr*)malloc(sizeof(Instr));
    if(!I){
        printf("Error allocating Instruction\n");
        error(is_file,F);
    }
    switch(*line){//Tests for Read/write/goto/if/label/quit/open
        case'p':
            if(strncmp(line+1,"rint",4)==0){
                //Escrever
                line=line+sizeof("rint");

                OP(I)=PRINT;
                KIND(SELEM(I))=KIND(TELEM(I))=EMPTY;
                KIND(FELEM(I))=STRING;
                STRING(FELEM(I))=line;
                addProcess(I,Program);
                return;     
            }
        break;
        case 'r':
            if(strncmp(line+1,"ead",3)==0){
                //ler
                line+=sizeof("ead");;
                OP(I)=READ;
                KIND(SELEM(I))=KIND(TELEM(I))=EMPTY;
                KIND(FELEM(I))=STRING;

                while(!isalnum(*line)) ++line;

                int i=0;
                while(isalnum(*line)){++line; i++;}
                *line='\0';
                line-=i;                

                STRING(FELEM(I))=line;
                addProcess(I,Program);
                return;  
            }
        break;
        case 'l':
            if(strncmp(line+1,"abel",4)==0){
                //Label
                line+=sizeof("abel");;
                OP(I)=LABEL;
                KIND(SELEM(I))=KIND(TELEM(I))=EMPTY;
                
                while(!isalnum(*line)) ++line;

                int i=0;
                while(isalnum(*line)){ ++line; i++;}

                *line='\0';
                line-=i;  

                STRING(FELEM(I))=line;
                addProcess(I,Program);
                return;  
            }
        break;
        case 'i':
            if(strncmp(line+1,"f",1)==0){
                //if
                char c[256];
                char *v; int i=0;

                line+=sizeof("f");;
                while(!isalnum(*line)) ++line;
                while(isalnum(*line)){
                    c[i++]=*line;
                    ++line;
                }
                c[i]='\0'; 
                v=(char*)malloc(i+1);
                    if(!v){
                        printf("Error allocating for if\n");
                        free(line);
                        error(is_file,F);
                    }
                strcpy(v,c);
                while(!isalnum(*line)) ++line;
                line+=sizeof("goto");

                while(!isalnum(*line)) ++line;
                i=0;
                while(isalnum(*line)){++line; i++;}

                *line='\0';
                line-=i; 
                OP(I)=IF_I;
                KIND(TELEM(I))=EMPTY;
                KIND(FELEM(I))=KIND(SELEM(I))=STRING;
                //(IF_I,label,var,EMPTY)
                STRING(FELEM(I))=line; 
                STRING(SELEM(I))=v;
                addProcess(I,Program);
                return;      
            }
        break;
        case 'g':
            if(strncmp(line+1,"oto",3)==0){
                //goto
                line+=sizeof("oto");

                while(!isalnum(*line)) ++line;
                int i=0;
                while(isalnum(*line)){++line; i++;}

                *line='\0';
                line-=i;
                OP(I)=GOTO_I;
                KIND(SELEM(I))=KIND(TELEM(I))=EMPTY;
                KIND(FELEM(I))=STRING;
                STRING(FELEM(I))=line;
                addProcess(I,Program);
                return;
            }
        break;
        case 'q':
            if(strncmp(line+1,"uit",3)==0){
                printf("Bye\n");
                free(line);
                error(is_file,F);
            }
        break;
        case 'o':
            if(strncmp(line+1,"pen",3)==0){
                line+=sizeof("pen");
                while(!isalnum(*line)) ++line;

                if(access(line,F_OK)!=-1){
                    FILE* fp=fopen(line,"r");
                    if(fp==NULL){
                        printf("Error While Opening %s\n",line);
                        free(line);
                        error(is_file,F);
                    }
                    shellFile(fp);
                }
                printf("File Does Not exist\n");
                free(line);
                error(is_file,F);
            }
        break;
    }
    //It can only be = or {+=,-=,*=,/=};
    char c[256];
    char* v;
    int i=0;

    while(!isalnum(*line)) ++line;
    while(isalnum(*line))  c[i++]=*line++;
    c[i]='\0';
    
    v=(char*)malloc(i+1);
        if(!v){
            printf("Error Allocating for Var in Expression\n");
            free(line);
            error(is_file,F);
        }
    strcpy(v,c);
    
    while(*line==' ')++line;
    switch (*line){
        case '=':
            line++;
            OP(I)=ATRIB;
            while(*line==' ') ++line;
            
            KIND(TELEM(I))=EMPTY;
            KIND(FELEM(I))=KIND(SELEM(I))=STRING;
            STRING(FELEM(I))=v;
            STRING(SELEM(I))=line;
            addProcess(I,Program);
            return;
        break;
        case '+': OP(I)=ADD; break;
        case '-': OP(I)=SUB; break;
        case '*': OP(I)=MUL; break;
        case '/': OP(I)=DIV; break;
        case '%': OP(I)=MOD; break;
        default:
            printf("Invalid Format\n");
            free(line);
            error(is_file,F);
        break;
    }
    if(*++line!='='){
        printf("Invalid Format\n");
        free(line);
        error(is_file,F);
    }
    line++;
    while(*line==' ')++line;
    
    KIND(FELEM(I))=KIND(SELEM(I))=KIND(TELEM(I))=STRING;
    STRING(FELEM(I))=STRING(SELEM(I))=v;
    STRING(TELEM(I))=line;
    addProcess(I,Program);
    return;
}
int execute(int loop,int is_file,FILE* F){
    if(loop==1){        
        int brek=execute(0,is_file,F);
        if(brek==1 && NEXTP(PC(Program))!=NULL){
            PC(Program)=NEXTP(PC(Program));
            execute(1,is_file,F);
        }        
        return 1;
    }
    Process* P=PC(Program);
    Instr* I=I(P);
    Elem *e,*old;
    int result;
    switch (OP(I)){
        case PRINT:
            printf("%d\n",parseFormula(STRING(FELEM(I)),Vars));
            return 1;
        break;
        case READ:
            if(is_file==1){
                printf("Can't read from File\n");
                error(is_file,F);
            }
            getchar();
            printf("Enter Value:");
            char *new,*var;
            char c,aux[256];
            do{ c=getchar(); }while(c==' ' && c!='\n');
            if(c=='\n'){
                printf("Not a value %c|\n",c);
                return execute(0,0,F);
            }
            int i=0;
            do{
                aux[i++]=c;
                c=getchar();
            }while(c!='\n');
            aux[i]='\0';
            new=(char*)malloc(i+1);
            if(!new){
                printf("Error reading value\n");
                error(is_file,F);
            }
            strcpy(new,aux);            
            if(contains(Vars,STRING(FELEM(I)))==0){
                e=(Elem*)malloc(sizeof(Elem));
                if(!e){
                    printf("Unable to read\n");
                    error(is_file,F);
                }
                PKIND(e)=STRING;
                PSTRING(e)=new;
                put(Vars,STRING(FELEM(I)),e);
                return 1;
            }
            old=getHash(Vars,STRING(FELEM(I)));
            result=parseFormula(new,Vars);
            PKIND(old)=INT_CONST;
            PVAL(old)=result;
            return 1;
        break;
        case ATRIB:
            if(contains(Vars,STRING(FELEM(I)))==0){
                e=(Elem*)malloc(sizeof(Elem));
                if(!e){
                    printf("Unable to read\n");
                    error(is_file,F);
                }
                PKIND(e)=STRING;
                PSTRING(e)=STRING(SELEM(I));
                put(Vars,STRING(FELEM(I)),e);
                return 1;
            }
            old=getHash(Vars,STRING(FELEM(I)));
            result=parseFormula(STRING(SELEM(I)),Vars);
            PKIND(old)=INT_CONST;
            PVAL(old)=result;
            return 1;
        break;
        case LABEL:
            if(containsLabel(Labels,STRING(FELEM(I)))==1){
                return 1;
            }
            putLabel(Labels,STRING(FELEM(I)),PC(Program));
            return 1;
        break;
        case GOTO_I:
        case IF_I:
            if(containsLabel(Labels,STRING(FELEM(I)))==0){
                printf("Label doesn't exist\n");
                return 1;
            }
            if(OP(I)==IF_I){
                if(contains(Vars,STRING(SELEM(I)))==0){
                    printf("Var not initilised\n");
                    error(is_file,F);
                }
                if((KIND(SELEM(I))==INT_CONST? VAL(SELEM(I)) : parseFormula(STRING(SELEM(I)),Vars))==0)
                    return 1;
            }
            pcGoto(getLabelHash(Labels,STRING(FELEM(I))),Program);
            execute(1,is_file,F);
            return 1;
        break;  
    }

    if(contains(Vars,STRING(FELEM(I)))==0){
                printf("Var not initilised\n");
                error(is_file,F);
    }
    old=getHash(Vars,STRING(FELEM(I)));
    //printf((PKIND(old)==INT_CONST? "Yes\n" : "No\n"));
    result=( PKIND(old)==INT_CONST? PVAL(old) : parseFormula(STRING(FELEM(I)),Vars) );
    switch(OP(I)){
        case ADD: result+=parseFormula(STRING(TELEM(I)),Vars); break;
        case SUB: result-=parseFormula(STRING(TELEM(I)),Vars); break;
        case MUL: result*=parseFormula(STRING(TELEM(I)),Vars); break;
        case DIV: result/=parseFormula(STRING(TELEM(I)),Vars); break;
        case MOD: result%=parseFormula(STRING(TELEM(I)),Vars); break;
    }
    PKIND(old)=INT_CONST;
    PVAL(old)=result; 
    return 1;   
}
