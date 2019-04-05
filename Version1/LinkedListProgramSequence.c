/*******************************************************************************
| Program: An Implementation of a LinkedList------For A Program Sequence-------|
| Author: Eduardo Morgado                                                      |
| Last Updated: 3/4/2019                                                       |
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"
#include "LinkedListProgramSequence.h"


/*------------------------------------------------------------------------------
|                           Functions Implementation                           |
------------------------------------------------------------------------------*/
ProcessGroup* createProgramQueue(){
    ProcessGroup* P=(ProcessGroup*)malloc(sizeof(ProcessGroup));
    if(!P){
        printf("Error creating Program\n"); 
        exit(0);
    }
    START(P)=NULL;
    END(P)=NULL;
    PC(P)=NULL;
    SIZEPROGRAM(P)=0;
    return P;
}
Process* addProcess(Instr* inst,ProcessGroup* P){
    Process* p = (Process*)malloc(sizeof(Process));
            if(!p){
                printf("Error creating process\n"); 
                exit(0);
            }
    I(p)=inst; NEXTP(p)=NULL;
    if(sizeProgram(P)==0){
        START(P)=p;
        END(P)=p;
        SIZEPROGRAM(P)++;
        pcGoto(p,P);
        return p;
    }
    /*if(sizeProgram(P)==1){
        Process* p = (Process*)malloc(sizeof(Process));
            if(!p){
                printf("Error creating process\n"); 
                exit(0);
            }
        I(p)=inst; NEXTP(p)=NULL;
        START(P)=p;
        SIZEPROGRAM(P)++;
        pcGoto(p,P);
        return p;
    }
    Process* curr=START(P);
    while(NEXTP(NEXTP(curr))!=NULL){
        curr=NEXTP(curr);
    }
    Process* p = (Process*)malloc(sizeof(Process));
        if(!p){
            printf("Error creating process\n");
            exit(0);
        }
    I(p)=inst; NEXTP(p)=NULL;
    NEXTP(curr)=p;
    SIZEPROGRAM(P)++;*/
    Process* last=END(P);
    NEXTP(last)=p;
    END(P)=p;
    SIZEPROGRAM(P)++;
    pcGoto(p,P);
    return p;
}
void nextProcess(ProcessGroup* P){
    PC(P)=NEXTP(PC(P));
}
void pcGoto(Process* p,ProcessGroup* P){
    PC(P)=p;
}
int sizeProgram(ProcessGroup* P){
    return SIZEPROGRAM(P);
}
void endExecution(ProcessGroup* P){
    if(sizeProgram(P)==0){
        free(P); 
        return;
    }
    Process* n=START(P);
    endProcess(NULL,n);
    free(P);
}
void endProcess(Process* parent_process,Process* process){
    if(NEXTP(process)==NULL){
        free(I(process));
        NEXTP(parent_process)=NULL;
        return;
    }
    endProcess(process,NEXTP(process));
}
void printProcesses(ProcessGroup* P){

}