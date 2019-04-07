/*******************************************************************************
| Program: An Implementation of a LinkedLis For A Variable Elemenr             |
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 3/4/2019                                                   FCUP|
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structures.h"
#include "LinkedListsHashVar.h"

/*------------------------------------------------------------------------------
|                           Functions Implementation                           |
------------------------------------------------------------------------------*/
VarList* createVarList(){
    /*
     * Allocates the space in memory for the list and initializes first
     * Returns the new lists
     */
    VarList* l=(VarList*)malloc(sizeof(VarList));
    if(!l){
        printf("Error at creating ListVar\n"); 
        exit(0);
    }
    FIRST(l)=NULL;
    return l;
}
int size(VarList* l){
    //Given a list, returns its size
    return SIZEVARS(l);
}
int isEmpty(VarList* l){
    return (FIRST(l)==NULL ? 1 : 0);
}
Elem* getNodeVar(char* name,VarList* l){
    /*
     * Given a variable name and the list containing it, iterates through it to
     *      find the variable, returns the element of the variable/its value
     *      if found otherwise retuns NULL O(n) for n=size_list 
     */
    if(isEmpty(l)==1) return NULL;
    VarNode* n=FIRST(l);
    while(n!=NULL && strcmp(NAME(n),name)!=0)
        n=NEXT(n);
    return (n==NULL ? NULL : ELEM(n));
}
VarList* addFirst(char* name, Elem* elem,VarList* l){
    /*
     * Given a lists of variables, a variable name and its value(elem)
     *     appends it to the head of the list (if it exists) 
     * Returns the new created VarNode O(n), this can be reduced to O(1) if
     *     in the implementation of HashTableVar we perform the contains outside
     */
    if(getNodeVar(name,l)!=NULL){
        printf("Unable to create variable: Already exists or list empty\n");
        exit(0);
    }
    VarNode* n = (VarNode*)malloc(sizeof(VarNode));
        if(!n){
            printf("Error allocating memmory to node\n"); 
            exit(0);
        }
    NAME(n)=name; ELEM(n)=elem; NEXT(n)=FIRST(l);
    FIRST(l)=n;
    SIZEVARS(l)++;
    return l;
}
VarList* addLast(char* name, Elem* elem, VarList* l){
    /*
     * Given a list of vars, a var name and its value, if the var doesn't occur 
     *      in the list, appends it to the tail of the end of the list
     * Returns the new VarNode 
     */
    if(isEmpty(l)==1){
        addFirst(name,elem,l);
        return l;
    }
    if(getNodeVar(name,l)!=NULL) return NULL;
    if(size(l)==1){
        VarNode* n = (VarNode*)malloc(sizeof(VarNode));
            if(!n){
                printf("Error allocating memmory to node\n"); 
                exit(0);
            }
        NAME(n)=name; ELEM(n)=elem; NEXT(n)=FIRST(l);
        FIRST(l)=n;
        SIZEVARS(l)++;
        return l;
    }
    VarNode* curr=FIRST(l);
    while(NEXT(NEXT(curr))!=NULL){
        curr=NEXT(curr);
    }
    VarNode*  n= (VarNode*)malloc(sizeof(VarNode));
        if(!n){
            printf("Error allocating memmory to node\n"); 
            exit(0);
        }
    NAME(n)=name; ELEM(n)=elem; NEXT(n)=NULL;
    NEXT(curr)=n;
    SIZEVARS(l)++;
    return l;    
}
void printVarNode(VarList* l){
    if(isEmpty(l)==1){
        printf("[]\n");
        return;
    }
    VarNode* n=FIRST(l);
    printf("[");
    while(n!=NULL){
        if(NEXT(n)==NULL)
            printf("%s", NAME(n));
        else
            printf("%s, ",NAME(n));
        n=NEXT(n);
    }
    printf("]\n");
    return;
}
void freeList(VarList* l){
    /*
     * Given a list, it will free its nodes from memory using recursion
     *      (freeNodes) at the end it frees the list from memory 
     */
    if(isEmpty(l)){
        free(l); 
        return;
    }
    VarNode* n=FIRST(l);
    freeNodes(NULL,n);
    free(l);
}
void freeNodes(VarNode* parent,VarNode* n){
    if(NEXT(n)==NULL){
        free(NAME(n));
        free(ELEM(n));
        NEXT(parent)=NULL;
        return;
    }
    freeNodes(n,NEXT(n));
}