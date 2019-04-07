/*******************************************************************************
| Program: Implementation of Descendent Parser for expressions                 |
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 4/4/2019                                                   FCUP|
*******************************************************************************/
#include "Structures.h"
#include "HashTableVar.h"
#include "LinkedListsHashVar.h"
#include "ParserExpression.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* exp;

int parseNumber(){
    int number=0;
    while(*exp>='0'&&*exp<='9'){
        number*=10;
        number+= *exp-'0';
        ++exp;
    }
    return number;
}
int parseVar(HashTableVar* table){
    char var[256]; int i=0;
    while(isalpha(*exp) && *exp!='\0'){
        var[i]=*exp;
        ++exp;
        i++;
    }
    var[i]='\0';
    //printf("ParserVar:%s|\n",var);
    Elem* e=getHash(table,var);
    if(PKIND(e)==EMPTY){
        printf("Unexpected error: Var %s does not exist or not initialised\n",var);
        exit(0);
    }
    if(PKIND(e)==INT_CONST){
        return PVAL(e);
    }
    else if(PKIND(e)==STRING){
        //printf("ParseVar:%s|\nParserVarString:%s|\n",var,PSTRING(e));
        char* tmp=exp;
        int r=parseFormula(PSTRING(e),table);
        exp=tmp;
        return r;
    }
    printf("Var of Wrong Type\n");
    exit(0);
}
int parseFactor(HashTableVar* table){
    if(*exp>='0'&& *exp<='9'){
        return parseNumber();
    }
    else if(isalpha(*exp)){
        return parseVar(table);
    }
    else if(*exp=='('){
        ++exp;
        int sum;
        if(*exp=='-'){
            ++exp;
            sum=parseSum(-1,table);
        }
        else sum=parseSum(1,table);
        ++exp;
        return sum;
    }
    else if(*exp=='-' && isalnum(*(exp-1))==0){
        ++exp;
        int sum=parseSum(-1,table);
        return sum;
    }
    else if(*exp==' ' || *exp=='\n' || *exp=='\t'){
        ++exp;
        return parseFactor(table);
    }
    else{
        printf("Expected digit or var but found %c\n",*exp);
        exit(0);
    }
}
int parseFormula(char* x,HashTableVar* table){
    //Main Caller
    exp=x;
    int result=parseSum(1,table);
    if(*exp=='\0') return result;
    return 0;
}
int parseProduct(HashTableVar* table){
    int right=parseFactor(table);
    while(*exp=='*' || *exp=='/' || *exp=='%'){
        char c=*exp;
        ++exp;
        int left=parseFactor(table);
        if(c=='*') right*=left;
        else if(c=='/') right/=left;
        else if(c=='%') right%=left;
    }
    return right;
}
int parseSum(int s,HashTableVar* table){
    int right=s*parseProduct(table);
    while(*exp=='+'||*exp=='-'){
        char c=*exp;
        ++exp;
        int left=parseProduct(table);
        if(c=='+') right+=left;
        else if(c=='-') right-=left;
    }
    return right;
}