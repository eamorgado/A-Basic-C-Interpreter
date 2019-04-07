/*******************************************************************************
| Program: A Conceptual defenition of a HashTable for Labels                   |
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 3/4/2019                                                   FCUP|
********************************************************************************
|   Representation:                                                            |
|       ->A Hashtable of labels is an array of lists of labels, as such,our    |
|           hashtable will be the allocated array+its size                     |
*******************************************************************************/
#include "LinkedListProgramSequence.h"
#include "LinkedListLabel.h"

#ifndef HASHTABLE_LABEL_H
#define HASHTABLE_LABEL_H


/*------------------------------------------------------------------------------
|                          Macro Defenition                                    |
------------------------------------------------------------------------------*/
#define HLSIZE(T) ((T)->size)
#define HLELEMS(T) ((T)->elements)
#define HLENTRIES(T) ((T)->table)


/*------------------------------------------------------------------------------
HashTable defenition
------------------------------------------------------------------------------*/
typedef struct hashtableLabel{
    int size;
    int elements;
    LabelList** table;
}HashTableLabel;


/*------------------------------------------------------------------------------
HashTable Functions
------------------------------------------------------------------------------*/
HashTableLabel* createLabelsTable();
unsigned int hashLabel(char*);
int containsLabel(HashTableLabel*,char*);
void putLabel(HashTableLabel*,char*,Process*);
Process* getLabelHash(HashTableLabel*,char*);
void freeLabelTable(HashTableLabel*);

#endif