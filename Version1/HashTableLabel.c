/*******************************************************************************
| Program: An Implementation of a HashTable for Labels-------------------------|
| Author: Eduardo Morgado                                                      |
| Last Updated: 3/4/2019                                                       |
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LinkedListProgramSequence.h"
#include "LinkedListLabel.h"
#include "HashTableLabel.h"

#define INIT_SIZE 100

HashTableLabel* createLabelsTable(){
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
    
    for(int i=0;i<INIT_SIZE;i++){
        HLENTRIES(table)[i]=createLabels();
    }return table;
}
unsigned int hashLabel(char* varname){
    int i=sizeof(varname)/sizeof(char*);
    int k=0;
    while(*varname!='\0'){
        k+=*(varname++)*pow(31,i--);
    }
    k%=INIT_SIZE;
    return k;
}
int containsLabel(HashTableLabel* table,char* name){
    unsigned int position=hashLabel(name);
    return (getLabel(name,HLENTRIES(table)[position])==NULL ? 0 : 1);
}
void putLabel(HashTableLabel* table,char* name,Process* p){
    unsigned int position=hashLabel(name);
    HLELEMS(table)++;
    addLabel(name,p,HLENTRIES(table)[position]);
    return;
}
Process* getLabelHash(HashTableLabel* table,char* name){
    unsigned int position=hashLabel(name);
    if(containsLabel(table,name)==0){
        printf("Unable to access Label: Does not exist\n");
        exit(0);
    }
    return getLabel(name,HLENTRIES(table)[position]);
}
//void printLabelTable(HashTableLabel*);
void freeLabelTable(HashTableLabel* table){
    for(int i=0;i<HLSIZE(table);i++){
        freeLabelList(HLENTRIES(table)[i]);
    }
    free(table);
}
