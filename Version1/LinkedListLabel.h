/*******************************************************************************
| Program: A Conceptual defenition of a LinkedList------For Label -------------|
| Author: Eduardo Morgado                                                      |
| Last Updated: 3/4/2019                                                       |
********************************************************************************
|   Representation:                                                            |
|       ->Node is defined by the name of the label that it stores, plus the    |
|               the execution process to where it points to                    |
|   The list will contain an empty node, first, that points to the very first  |
|       node in the list                                                       |
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
