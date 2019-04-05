/*******************************************************************************
| Program: A Conceptual defenition of a HashTable for Variables----------------|
| Author: Eduardo Morgado                                                      |
| Last Updated: 3/4/2019                                                       |
********************************************************************************
|   This class is supported by the LinkedListsHashVar                          |
*******************************************************************************/
#include "LinkedListsHashVar.h"

#ifndef HASHTABLE_VAR_H
#define HASHTABLE_VAR_H


/*------------------------------------------------------------------------------
|                          Macro Defenition                                    |
------------------------------------------------------------------------------*/
#define SIZE(T) ((T)->size)
#define ELEMS(T) ((T)->elements)
#define ENTRIES(T) ((T)->table)


/*------------------------------------------------------------------------------
HashTable defenition
------------------------------------------------------------------------------*/
typedef struct hashtableVar{
    int size; //size of the hashtable
    int elements;
    VarList **table;
}HashTableVar;


/*------------------------------------------------------------------------------
HashTable Functions
------------------------------------------------------------------------------*/
HashTableVar* createVars();
unsigned int hash(char*);
int contains(HashTableVar*,char*);
void put(HashTableVar*,char*,Elem*);
Elem* getHash(HashTableVar*,char*);
int replace(HashTableVar*,char*,Elem*);
void printVarTable(HashTableVar*);
void freeTable(HashTableVar*);

#endif