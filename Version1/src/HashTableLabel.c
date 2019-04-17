/*******************************************************************************
| Program: An Implementation of a HashTable for Labels                         |
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 3/4/2019                                                   FCUP|
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LinkedListProgramSequence.h"
#include "LinkedListLabel.h"
#include "HashTableLabel.h"

#define INIT_SIZE 100                                           //Size of table


HashTableLabel* createLabelsTable(){
    /*
     * Allocates the memory for the array of lists and initializes/creates them
     *      all, sets the size of the list to INIT_SIZE
     * Returns the created table
     * Note: for a future improvement we could give this function the desired 
     *      size of the table and do HLSIZE(table)=input_size, allowing for
     *      diferent size tables depending of the user
     */
    HashTableLabel* table=(HashTableLabel*)malloc(sizeof(HashTableLabel));
    if(!table){
        printf("Error allocating memory to HashTableLabel\n"); 
        exit(0);
    }

    HLSIZE(table)=INIT_SIZE;
    HLELEMS(table)=0;
    HLENTRIES(table)=malloc(INIT_SIZE*sizeof(HLENTRIES(table)));
    if(!HLENTRIES(table)){
        printf("Error allocating memory to LabelEntries\n"); 
        exit(0);
    }
    //creates all the lists in the array
    for(int i=0;i<INIT_SIZE;i++){
        HLENTRIES(table)[i]=createLabels();
    }return table;
}
unsigned int hashLabel(char* varname){
    /*
     * Given a label name, produces the index of the list that might contain the
     *      label, the higher the size of the table we consider, the less
     *      colisions we might encounter
     * Retuns the computed index 
     */
    int i=sizeof(varname)/sizeof(char*);
    int k=0;
    while(*varname!='\0'){
        k+=*(varname++)*pow(31,i--);
    }
    k%=INIT_SIZE;
    return k;
}
int containsLabel(HashTableLabel* table,char* name){
    /*
     * Given a table and a label name, checks if the label is in the table, for
     *      that, it first gets the index of the list that might contain it and
     *      searches the list for the label O(n) for n=size_list
     * If the list cointains the label, returns 1 otherwise 0 
     */
    unsigned int position=hashLabel(name);
    return (getLabel(name,HLENTRIES(table)[position])==NULL ? 0 : 1);
}
void putLabel(HashTableLabel* table,char* name,Process* p){
    /*
     * Given a table of labels, a potential new label and its pointing process
     *      we first check if the label(name) already exists in the table if not
     *      then we add/append the label in the list O(1) for is addFirst 
     */
    unsigned int position=hashLabel(name);
    HLELEMS(table)++;
    addLabel(name,p,HLENTRIES(table)[position]);
    return;
}
Process* getLabelHash(HashTableLabel* table,char* name){
    /*
     * Given a table and a potential label name, we return the process of the 
     *      label if it exists
     * As an improvement we could only return the getLabel, the contains is 
     *      a getlabel with int output
     */
    unsigned int position=hashLabel(name);
    if(containsLabel(table,name)==0){
        printf("Unable to access Label: Does not exist\n");
        exit(0);
    }
    return getLabel(name,HLENTRIES(table)[position]);
}
void freeLabelTable(HashTableLabel* table){
    /*
     * Given a table to delete, we transverse the array, freeing all the lists
     *      from memory, in the end the table itself is removed from memory; 
     */
    for(int i=0;i<HLSIZE(table);i++){
        freeLabelList(HLENTRIES(table)[i]);
    }
    free(table);
}
