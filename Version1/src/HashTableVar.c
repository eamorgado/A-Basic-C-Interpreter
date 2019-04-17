/*******************************************************************************
| Program: An Implementation of a HashTable for Variables                      |
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 3/4/2019                                                   FCUP|
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "LinkedListsHashVar.h"
#include "HashTableVar.h"

#define INIT_SIZE 100


HashTableVar* createVars(){
    /*
     * We allocate the space in memory for the table array and initialise every
     *      list in every index in the end we return the new table  
     */
    HashTableVar* table=(HashTableVar*)malloc(sizeof(HashTableVar));
    if(!table){
        printf("Error allocating memory to HashTableVar\n"); 
        exit(0);
    }

    SIZE(table)=INIT_SIZE;
    ELEMS(table)=0;
    ENTRIES(table)=malloc(INIT_SIZE*sizeof(ENTRIES(table)));
    if(!ENTRIES(table)){
        printf("Error allocating memory to Entries\n"); 
        exit(0);
    }
    
    for(int i=0;i<INIT_SIZE;i++){
        ENTRIES(table)[i]=createVarList();
    }return table;
}
unsigned int hash(char* varname){
    /*
     * Given a potential var name, we calculate its hash value and return it 
     */
    int i=sizeof(varname)/sizeof(char*);
    int k=0;
    while(*varname!='\0'){
        k+=*(varname++)*pow(31,i--);
    }
    k%=INIT_SIZE;
    return k;
}
int contains(HashTableVar* table,char* name){
    /*
     * Given a table and a potential var, we calculate the index/hash of the 
     *      list that might contain it and then perform a list search
     * If the list does contain the variable, then we return 1 otherwise 0 
     */
    unsigned int position=hash(name);
    return (getNodeVar(name,ENTRIES(table)[position])==NULL ? 0 : 1);
}
void put(HashTableVar* table,char* name,Elem* elem){
    /*
     * Given a table of vars and the new var values and name, we append it to
     *      the head of the list in the var hash index
     */
    unsigned int position=hash(name);
    ELEMS(table)++;
    addFirst(name,elem,ENTRIES(table)[position]);
    return;
}
Elem* getHash(HashTableVar* table,char* name){
    /*
     * Given a table of vars and a potential var name, we first calculate
     *      the index of the list that might contain it, if it does then the 
     *      var value/element is returned
     */
    unsigned int position=hash(name);
    if(contains(table,name)==0){
        printf("Unable to access variable: Does not exist\n");
        exit(0);
    }
    return getNodeVar(name,ENTRIES(table)[position]);   
}
int replace(HashTableVar* table, char* name, Elem* elem){
    /*
     * Given a table and an existing variable, its value will be replaced by
     *      the given one 
     */
    unsigned int position=hash(name);
    Elem* e=getNodeVar(name,ENTRIES(table)[position]);
    if(!e){
        printf("Unable to change variable: Does not exist\n");
        exit(0);
    }
    e=elem;
    return 1;
}
void printVarTable(HashTableVar* table){
    for(int i=0;i<SIZE(table);i++){
        printf("%d:",i);
        printVarNode(ENTRIES(table)[i]);
    }
}
void freeTable(HashTableVar* table){
    for(int i=0;i<SIZE(table);i++){
        freeList(ENTRIES(table)[i]);
    }
    free(table);
}

