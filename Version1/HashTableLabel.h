/*******************************************************************************
| Program: A Conceptual defenition of a HashTable for Labels-------------------|
| Author: Eduardo Morgado                                                      |
| Last Updated: 3/4/2019                                                       |
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
void printLabelTable(HashTableLabel*);
void freeLabelTable(HashTableLabel*);

#endif