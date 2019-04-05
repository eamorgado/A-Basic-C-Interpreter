/*******************************************************************************
| Program: An Implementation of a C interper for interactive                   |
| Last Updated: 4/4/2019                                                       |
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
#ifndef SHELL_INTERACTIVE_H
#define SHELL_INTERACTIVE_H

void shellInteractive();
char* readInteractive();

#endif

