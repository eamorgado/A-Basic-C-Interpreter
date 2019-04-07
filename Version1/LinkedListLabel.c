/*******************************************************************************
| Program: An Implementation of a LinkedList For Label-------------------------|
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 3/4/2019                                                   FCUP|
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"
#include "LinkedListProgramSequence.h"
#include "LinkedListLabel.h"


/*------------------------------------------------------------------------------
|                           Functions Implementation                           |
------------------------------------------------------------------------------*/
int sizeLabelList(LabelList* L){
    //Given a list, returns the size of the list
    return SLABEL(L);
}
LabelList* createLabels(){
    /*
     * Allocates memory to store the list and initializes the pointers
     * returns the list created
     */
    LabelList* L=(LabelList*)malloc(sizeof(LabelList));
    if(!L){
        printf("Error creating LabelList\n"); 
        exit(0);
    }
    FLABEL(L)=NULL;
    SLABEL(L)=0;
    return L;
}
Process* getLabel(char* name,LabelList* L){
    /*
     * Given a list and a string, it iterates through the list in search of 
     *  a node with the name equal to the string
     * Return the node/process if it finds the node otherwise returns NULL
     */
    if(sizeLabelList(L)==0) return NULL;
    LabelNode* curr=FLABEL(L);
    while(curr!=NULL && strcmp(LNAME(curr),name)!=0)
        curr=LNEXT(curr);
    return (curr==NULL ? NULL : HEADER(curr));    
}
LabelNode* addLabel(char* name,Process* p,LabelList* L){
    /*
     * Given a list of Labels and a process to add and the new label name
     *  it creates the new LabelNode (allocates and initializes)
     *  and appends it to the head of the list O(1);
     *  returns the new label 
     */
    LabelNode* l =(LabelNode*)malloc(sizeof(LabelNode));
    if(!l){
        printf("Error creating label\n");
            exit(0);
    }
    LNAME(l)=name; HEADER(l)=p; LNEXT(l)=FLABEL(L);
    FLABEL(L)=l;
    SLABEL(L)++;
    return l;
}
void freeLabelList(LabelList* L){
    /*
     * Given a list of labels, it will free all its nodes from memory
     *      using recursion (freeLabel) 
     * Once all is done, if frees the list itself from memory
     */
    if(sizeLabelList(L)==0){
        free(L);
        return;
    }
    LabelNode* l=FLABEL(L);
    freeLabel(NULL,l);
    free(L);
}
void freeLabel(LabelNode* label_parent,LabelNode* label){
    if(LNEXT(label)==NULL){
        //Reached end of list
        free(LNAME(label));
        LNEXT(label_parent)=NULL;
    }
    freeLabel(label,LNEXT(label));
}
