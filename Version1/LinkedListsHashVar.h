/*******************************************************************************
| Program: A Conceptual defenition of a LinkedList------For A Variable Elemenrt|
| Author: Eduardo Morgado                                                      |
| Last Updated: 3/4/2019                                                       |
********************************************************************************
|   Representation:                                                            |
|       ->Node is defined by:                                                  |
|           -The desired value to store, in this case the variable name        |
|           -The element that stores, can be an integer or a char              |
|           -A pointer to the next node in the list                            |
|   The list will contain an empty node, first, that points to the very first  |
|       node in the list.                                                      |
*******************************************************************************/
#include "Structures.h"

#ifndef LISTS_HASHVAR_H
#define LISTS_HASHVAR_H

/*------------------------------------------------------------------------------
|                            Macro Defenition                                  |
------------------------------------------------------------------------------*/
#define NAME(N) ((N)->name)
#define ELEM(N) ((N)->elem)
#define NEXT(N) ((N)->next)

#define FIRST(L) ((L)->first)
#define SIZEVARS(L) ((L)->size)

/*------------------------------------------------------------------------------
|                           Node Defenition                                    |
------------------------------------------------------------------------------*/
typedef struct varnode{
    char* name;
    Elem* elem;
    struct varnode* next;
}VarNode;


/*------------------------------------------------------------------------------
|                           List Defenition                                    |
------------------------------------------------------------------------------*/
typedef struct varlist{
    VarNode* first;
    int size;
}VarList;


/*------------------------------------------------------------------------------
|                           List Functions                                     |
------------------------------------------------------------------------------*/
VarList* createVarList();
int size(VarList*);
int isEmpty(VarList*);
Elem* getNodeVar(char*,VarList*);
VarList* addFirst(char*,Elem*,VarList*);
VarList* addLast(char*,Elem*,VarList*);
void printVarNode(VarList*);

/*------------------------------Free------------------------------------------*/
void freeList(VarList*);
void freeNodes(VarNode*,VarNode*);

#endif