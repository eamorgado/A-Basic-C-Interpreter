/*******************************************************************************
| Program: An Implementation of a C interper                                   |
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
        case'e':
            if(strncmp(line+1,"screver",7)==0){
                //Escrever
                line=line+sizeof("screver");

                OP(I)=PRINT;
                KIND(SELEM(I))=KIND(TELEM(I))=EMPTY;
                KIND(FELEM(I))=STRING;
                STRING(FELEM(I))=line;
                addProcess(I,Program);
                //printf("PC:%s\n",STRING(FELEM(I(PC(Program))))); 
                return;     
            }
        break;
        case 'l':
            if(strncmp(line+1,"er",2)==0){
                //ler
                line+=sizeof("er");;
                OP(I)=READ;
                KIND(SELEM(I))=KIND(TELEM(I))=EMPTY;
                KIND(FELEM(I))=STRING;

                while(!isalnum(*line))
                    ++line;

                int i=0;
                while(isalnum(*line)){
                    ++line; i++;
                }
                *line='\0';
                line-=i;                

                STRING(FELEM(I))=line;
                addProcess(I,Program);
                //printf("PC:%s\n",STRING(FELEM(I(PC(Program)))));
                return;  
            }
            else if(strncmp(line+1,"abel",4)==0){
                //Label
                line+=sizeof("abel");;
                OP(I)=LABEL;
                KIND(SELEM(I))=KIND(TELEM(I))=EMPTY;
                
                while(!isalnum(*line))
                    ++line;

                int i=0;
                while(isalnum(*line)){
                    ++line; i++;
                }
                *line='\0';
                line-=i;  

                STRING(FELEM(I))=line;
                addProcess(I,Program);
                //printf("PC:%s\n",STRING(FELEM(I(PC(Program)))));
                return;  
            }
        break;
        case 'i':
            if(strncmp(line+1,"f",1)==0){
                //if
                char c[256];
                char *v; int i=0;

                line+=sizeof("f");;
                //printf("L1:%s|\n",line);
                while(!isalnum(*line)) ++line;
                //printf("L2:%s|\n",line);
                while(isalnum(*line)){
                    c[i++]=*line;
                    ++line;
                }
                c[i]='\0'; 
                //printf("C:%s|\n",c);               
                v=(char*)malloc(i+1);
                    if(!v){
                        printf("Error allocating for if\n");
                        error(is_file,F);
                    }
                strcpy(v,c);
                //printf("V:%s|\n",v);
                while(!isalnum(*line)) ++line;
                //printf("L3:%s|\n",line);
                line+=sizeof("goto");
                //printf("L4:%s|\n",line);
                while(!isalnum(*line)) ++line;
                //printf("L5:%s|\n",line);
                i=0;
                while(isalnum(*line)){
                    ++line; i++;
                }
                *line='\0';
                line-=i; 
                //printf("L6:%s|\n",line);
                OP(I)=IF_I;
                KIND(TELEM(I))=EMPTY;
                KIND(FELEM(I))=KIND(SELEM(I))=STRING;
                STRING(FELEM(I))=v;
                STRING(SELEM(I))=line;
                addProcess(I,Program);
                //printf("PC Cond:%s|\nPc Label:%s|\n",STRING(FELEM(I(PC(Program)))),STRING(SELEM(I(PC(Program)))));
                return;      
            }
        break;
        case 'g':
            if(strncmp(line+1,"oto",3)==0){
                //goto
                //printf("L1:%s|\n",line);
                line+=sizeof("oto");
                //printf("L2:%s|\n",line);
                while(!isalnum(*line)) ++line;
                //printf("L3:%s|\n",line);
                int i=0;
                while(isalnum(*line)){
                    ++line; i++;
                }
                *line='\0';
                line-=i;
                //printf("L4:%s|\n",line);
                OP(I)=GOTO_I;
                KIND(SELEM(I))=KIND(TELEM(I))=EMPTY;
                KIND(FELEM(I))=STRING;
                STRING(FELEM(I))=line;
                addProcess(I,Program);
                //printf("PC:%s\n",STRING(FELEM(I(PC(Program)))));
                return;
            }
        break;
        case 'q':
            if(strncmp(line+1,"uit",3)==0){
                printf("Bye\n");
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
                        error(is_file,F);
                    }
                    shellFile(fp);
                }
                printf("File Does Not exist\n");
                error(is_file,F);
            }
        break;
    }
    //It can only be = or {+=,-=,*=,/=};
    char c[256];
    char* v;
    int i=0;
    while(!isalnum(*line)) ++line;
    //printf("L1:%s|\n",line);
    while(isalnum(*line))
        c[i++]=*line++;
    c[i]='\0';
    //printf("L2:%s|\n",line);
    //printf("C:%s|\n",c);
    v=(char*)malloc(i+1);
        if(!v){
            printf("Error Allocating for Var in Expression\n");
            error(is_file,F);
        }
    strcpy(v,c);
    //printf("V:%s|\n",v);
    
    while(*line==' ')++line;
    //printf("L3:%s|\n",line);
    switch (*line){
        case '=':
            line++;
            OP(I)=ATRIB;
            //printf("A1:%s|\n",line);
            while(*line==' ') ++line;
            //printf("A2:%s|\n",line);

            KIND(TELEM(I))=EMPTY;
            KIND(FELEM(I))=KIND(SELEM(I))=STRING;
            STRING(FELEM(I))=v;
            STRING(SELEM(I))=line;
            addProcess(I,Program);
            //printf("PC_Var-A:%s|\nPC_Exp-A:%s|\n",STRING(FELEM(I(PC(Program)))),STRING(SELEM(I(PC(Program)))));
            return;
        break;
        case '+': OP(I)=ADD; break;
        case '-': OP(I)=SUB; break;
        case '*': OP(I)=MUL; break;
        case '/': OP(I)=DIV; break;
        case '%': OP(I)=MOD; break;
        default:
            printf("Invalid Format\n");
            error(is_file,F);
        break;
    }
    if(*++line=='='){
        line++;
        //printf("L4:%s|\n",line);
        while(*line==' ')++line;
        //printf("L5:%s|\n",line);
        KIND(FELEM(I))=KIND(SELEM(I))=KIND(TELEM(I))=STRING;
        STRING(FELEM(I))=STRING(SELEM(I))=v;
        STRING(TELEM(I))=line;
        addProcess(I,Program);
        /*switch(OP(I)){
            case ADD: printf("Add\n"); break;
            case SUB: printf("Sub\n"); break;
            case MUL: printf("Mul\n"); break;
            case DIV: printf("Div\n"); break;
        }
        printf("PC_Var:%s|\nPC_Var2:%s|\nPC_Exp:%s|\n",STRING(FELEM(I(PC(Program)))),STRING(SELEM(I(PC(Program)))),STRING(TELEM(I(PC(Program)))));
        */return;
    }
    printf("Invalid Format\n");
    error(is_file,F);
}
int execute(int loop,int is_file,FILE* F){
    //printf("Instruction:%d\n",OP(I((PC(Program)))));
    if(loop==1){        
        int brek=execute(0,is_file,F);
        if(brek==1 && NEXTP(PC(Program))!=NULL){
            //execute(0);
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
            //printf("R:%d|\nV:%s|\n",contains(Vars,"k"),STRING(FELEM(I)));                
            printf("%d\n",parseFormula(STRING(FELEM(I)),Vars));
            //PC(Program)=NEXTP(PC(Program));
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
            do{
                c=getchar();
            }while(c==' ' && c!='\n');
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
            //printf("%s\n",new);
            //strcpy(var,STRING(FELEM(I)));
            //printf("%s\n",STRING(FELEM(I)));
            if(contains(Vars,STRING(FELEM(I)))==0){
                e=(Elem*)malloc(sizeof(Elem));
                if(!e){
                    printf("Unable to read\n");
                    error(is_file,F);
                }
                PKIND(e)=STRING;
                PSTRING(e)=new;
                put(Vars,STRING(FELEM(I)),e);
                //printf("R:%d|\n",contains(Vars,STRING(FELEM(I))));
                return 1;
            }
            old=getHash(Vars,STRING(FELEM(I)));
            result=parseFormula(new,Vars);
            PKIND(old)=INT_CONST;
            PVAL(old)=result;
            //printf("RN:%d|\n",contains(Vars,STRING(FELEM(I))));
            //PC(Program)=NEXTP(PC(Program));
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
                //printf("R:%d|\n",contains(Vars,STRING(FELEM(I))));
                return 1;
            }
            old=getHash(Vars,STRING(FELEM(I)));
            result=parseFormula(STRING(SELEM(I)),Vars);
            PKIND(old)=INT_CONST;
            PVAL(old)=result;
            PC(Program)=NEXTP(PC(Program));
            return 1;
        break;
        case ADD:
            if(contains(Vars,STRING(FELEM(I)))==0){
                printf("Var not initilised\n");
                error(is_file,F);
            }
            old=getHash(Vars,STRING(FELEM(I)));
            result=parseFormula(STRING(FELEM(I)),Vars);
            //printf("Re:%d\n",result);
            result+=parseFormula(STRING(TELEM(I)),Vars);
            //printf("Re:%d\n",result);            
            PKIND(old)=INT_CONST;
            PVAL(old)=result;
            //PC(Program)=NEXTP(PC(Program));
            return 1;
        break;
        case SUB:
            if(contains(Vars,STRING(FELEM(I)))==0){
                printf("Var not initilised\n");
                error(is_file,F);
            }
            old=getHash(Vars,STRING(FELEM(I)));
            result=parseFormula(STRING(FELEM(I)),Vars);
            //printf("Re:%d\n",result);
            result-=parseFormula(STRING(TELEM(I)),Vars);
            //printf("Re:%d\n",result);            
            PKIND(old)=INT_CONST;
            PVAL(old)=result;
            return 1;
        break;
        case DIV:
            if(contains(Vars,STRING(FELEM(I)))==0){
                printf("Var not initilised\n");
                error(is_file,F);
            }
            old=getHash(Vars,STRING(FELEM(I)));
            result=parseFormula(STRING(FELEM(I)),Vars);
            //printf("Re:%d\n",result);
            result/=parseFormula(STRING(TELEM(I)),Vars);
            //printf("Re:%d\n",result);            
            PKIND(old)=INT_CONST;
            PVAL(old)=result;
            return 1;
        break;
        case MUL:
            if(contains(Vars,STRING(FELEM(I)))==0){
                printf("Var not initilised\n");
                error(is_file,F);
            }
            old=getHash(Vars,STRING(FELEM(I)));
            result=parseFormula(STRING(FELEM(I)),Vars);
            //printf("Re:%d\n",result);
            result*=parseFormula(STRING(TELEM(I)),Vars);
            //printf("Re:%d\n",result);            
            PKIND(old)=INT_CONST;
            PVAL(old)=result;
            return 1;
        break;
        case MOD:
            if(contains(Vars,STRING(FELEM(I)))==0){
                printf("Var not initilised\n");
                error(is_file,F);
            }
            old=getHash(Vars,STRING(FELEM(I)));
            result=parseFormula(STRING(FELEM(I)),Vars);
            //printf("Re:%d\n",result);
            result%=parseFormula(STRING(TELEM(I)),Vars);
            //printf("Re:%d\n",result);            
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
            if(containsLabel(Labels,STRING(FELEM(I)))==0){
                printf("Label doesn't exist\n");
                error(is_file,F);
            }
            pcGoto(getLabelHash(Labels,STRING(FELEM(I))),Program);
            execute(1,is_file,F);
            return 1;
        break;
        case IF_I:
            if(containsLabel(Labels,STRING(SELEM(I)))==0){
                printf("Label doesn't exist\n");
                error(is_file,F);
            }
            if(contains(Vars,STRING(FELEM(I)))==0){
                printf("Var not initilised\n");
                error(is_file,F);
            }
            if(parseFormula(STRING(FELEM(I)),Vars)==0){
                return 1;
            }
            else{
                pcGoto(getLabelHash(Labels,STRING(SELEM(I))),Program);
                execute(1,is_file,F); 
                return 1;
            }
            return 0;
        break;    
    }    
}
