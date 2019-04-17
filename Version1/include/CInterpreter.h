/*******************************************************************************
| Program: An Implementation of a C interper                                   |
| Last Updated: 4/4/2019       FCUP       Copyright (c) 2019, Eduardo Morgado  |
********************************************************************************
|   The program functionality:                                                 |
|       ->The program will be able to implement a small programming language   |
|       ->In memory we will keep 2 HashTables and 1 LinkedList. The HashTables |
|           will be [char*,Elem] and [char*,Instr] respectively, the first one |
|           will serve as a storage for the program variables, the second a    |
|           storage for labels were Instr is a pointer to the LinkedList of    |
|           instructions.                                                      |
|       ->The program will be able to both read interactivley or by loading a  |
|           file.                                                              |
*******************************************************************************/
#include "ParserExpression.h"
#include "Structures.h"
#include "LinkedListProgramSequence.h"
#include "HashTableVar.h"
#include "HashTableLabel.h"
#include <stdio.h>

#ifndef C_INTERPRETER_H
#define C_INTERPRETER_H

/*------------------------------------------------------------------------------
Mem Vars
------------------------------------------------------------------------------*/
HashTableLabel* Labels;
HashTableVar* Vars;
ProcessGroup* Program;


/*------------------------------------------------------------------------------
Interpreter Functions
------------------------------------------------------------------------------*/
void error();
void freeMem();
void createMem();
void parser(char*,int,FILE*);
int execute(int,int,FILE*);  

#endif