/*******************************************************************************
| Program: A Conceptual defenition of a HashTable for Variables                |
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 3/4/2019                                                   FCUP|
********************************************************************************
|   Representation:                                                            |
|       ->A HashTable of vars is and array of lists of variables, as such our  |
|           table will be the allocated array of lists + its size              |
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