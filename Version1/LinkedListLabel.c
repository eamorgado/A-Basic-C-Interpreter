/*******************************************************************************
| Program: An Implementation of a LinkedList------For Label--------------------|
| Author: Eduardo Morgado                                                      |
| Last Updated: 3/4/2019                                                       |
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
    return SLABEL(L);
}
LabelList* createLabels(){
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
    if(sizeLabelList(L)==0) return NULL;
    LabelNode* curr=FLABEL(L);
    while(curr!=NULL && strcmp(LNAME(curr),name)!=0)
        curr=LNEXT(curr);
    return (curr==NULL ? NULL : HEADER(curr));    
}
LabelNode* addLabel(char* name,Process* p,LabelList* L){
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
        free(LNAME(label));
        LNEXT(label_parent)=NULL;
    }freeLabel(label,LNEXT(label));
}
