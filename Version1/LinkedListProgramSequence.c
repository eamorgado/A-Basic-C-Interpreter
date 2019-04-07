/*******************************************************************************
| Program: An Implementation defenition of a LinkedList For The Instructions   |
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 3/4/2019                                                   FCUP|
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
    /*
     * We allocate space in memory and initialise the poiters and return the 
     *  list of process 
     */
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
    /*
     * Given the lists of processes and an instruction, we append the process to
     *      the end of the list, the operation is O(1) because we store the 
     *      pointer to the end of the list
     * We then  return the new process created 
     */
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
    Process* last=END(P);
    NEXTP(last)=p;
    END(P)=p;
    SIZEPROGRAM(P)++;
    pcGoto(p,P);
    return p;
}
void nextProcess(ProcessGroup* P){
    //skip the PC to the next process 
    PC(P)=NEXTP(PC(P));
}
void pcGoto(Process* p,ProcessGroup* P){
    //Point the pc to the given process, used for the labels
    PC(P)=p;
}
int sizeProgram(ProcessGroup* P){
    return SIZEPROGRAM(P);
}
void endExecution(ProcessGroup* P){
    //Frees the list from memory and all its processes, recursion
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
