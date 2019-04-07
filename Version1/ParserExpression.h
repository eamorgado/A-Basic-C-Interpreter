/*******************************************************************************
| Program: Descendent Parser for arithmetic expressions                        |
| Author: Eduardo Morgado                 Copyright (c) 2019, Eduardo Morgado  |
| Last Updated: 4/4/2019                                                   FCUP|
*******************************************************************************/
#include "Structures.h"
#include "HashTableVar.h"
#include "LinkedListsHashVar.h"

#ifdef PARSER_EXPRESSIONS_H
#define PARSER_EXPRESSIONS_H

    int parseNumber();
    int parseVar(HashTableVar*);
    int parseFactor(HashTableVar*);
    int parseFormula(char*,HashTableVar*);
    int parseProduct(HashTableVar*);
    int parseSum(int,HashTableVar*);
    
#endif