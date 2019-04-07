/*******************************************************************************
| Program: A Conceptual defenition of a LinkedList For The Instructions        |
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 3/4/2019                                                   FCUP|
********************************************************************************
|   Representation:                                                            |
|       ->We will consider a list of Instructions to be of type ProcessGroup   |
|               where we store the first instruction/process in the list, the  |
|               last process in order to ease the addition and the pc/program  |
|               counter that points to the current/next executing process      |
|       ->Node is defined by the process to execute and a pointer to the next  |
|               instruction                                                    |
*******************************************************************************/
#include "Structures.h"

#ifndef LISTS_PROGRAM_H
#define LISTS_PROGRAM_H


/*------------------------------------------------------------------------------
|                           Macro Defenition                                   |
------------------------------------------------------------------------------*/
#define I(N) ((N)->instruction)
#define NEXTP(N) ((N)->next)

#define START(S) ((S)->first)
#define END(S) ((S)->last)
#define PC(S) ((S)->pc)
#define SIZEPROGRAM(S) ((P)->instructions)


/*------------------------------------------------------------------------------
|                           Node Defenition                                    |
------------------------------------------------------------------------------*/
typedef struct process{
    Instr* instruction;
    struct process* next;
}Process;


/*------------------------------------------------------------------------------
|                           List Defenition                                    |
------------------------------------------------------------------------------*/
typedef struct processgroup{
    Process* first;
    Process* last;
    Process* pc;
    int instructions;
}ProcessGroup;


/*------------------------------------------------------------------------------
|                           Sequence Functions                                 |
------------------------------------------------------------------------------*/
ProcessGroup* createProgramQueue();
Process* addProcess(Instr*,ProcessGroup*);
void nextProcess(ProcessGroup*);
void pcGoto(Process*,ProcessGroup*);
int sizeProgram(ProcessGroup*);
void endExecution(ProcessGroup*);
void endProcess(Process*,Process*);



#endif