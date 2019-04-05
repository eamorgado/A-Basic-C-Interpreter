/*******************************************************************************
| Program: A Conceptual defenition of a LinkedList------For The Instructions---|
| Author: Eduardo Morgado                                                      |
| Last Updated: 3/4/2019                                                       |
********************************************************************************
|   Representation:                                                            |
|       ->Node is defined by the Instruction that it stores                    |
|   The list will contain an empty node, first, that points to the very first  |
|       node in the list and a node called pc that is the program counter for  |
|       this program                                                           |
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
void printProcesses(ProcessGroup*);
void endExecution(ProcessGroup*);
void endProcess(Process*,Process*);



#endif