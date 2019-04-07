/*******************************************************************************
| Program: A Conceptual defenition of a LinkedList For Label                   |
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 3/4/2019                                                   FCUP|
********************************************************************************
|   Representation:                                                            |
|       ->We will consider a list of Labels to be of type LabelList where we   |
|           store the pointer to the head of the list (the first node)         |
|       ->Node is defined by the name of the label that it stores in order to  |
|               locate it in the label memory(HashTableLabel), plus the        |
|               the execution process to where it points to, that way we can   |
|               manipulate the program counter to our list of instructions     |
*******************************************************************************/
#include "Structures.h"
#include "LinkedListProgramSequence.h"

#ifndef LISTS_LABEL_H
#define LISTS_LABEL_H

/*------------------------------------------------------------------------------
|                          Macro Defenition                                    |
------------------------------------------------------------------------------*/
#define LNAME(N) ((N)->name)
#define HEADER(N) ((N)->header)
#define LNEXT(N) ((N)->next)

#define FLABEL(L) ((L)->first)
#define SLABEL(L) ((L)->labels)

/*------------------------------------------------------------------------------
|                           Node Defenition                                    |
------------------------------------------------------------------------------*/
typedef struct labelnode{
    char* name;
    Process* header;
    struct labelnode* next;
}LabelNode;


/*------------------------------------------------------------------------------
|                           List Defenition                                    |
------------------------------------------------------------------------------*/
typedef struct labellist{
    LabelNode* first;
    int labels;
}LabelList;


/*------------------------------------------------------------------------------
|                           Labels Functions                                   |
------------------------------------------------------------------------------*/
int sizeLabelList(LabelList*);
LabelList* createLabels();
Process* getLabel(char*,LabelList*);
LabelNode* addLabel(char*,Process*,LabelList*);
void freeLabelList(LabelList*);
void freeLabel(LabelNode*,LabelNode*);

#endif
