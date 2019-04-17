/*******************************************************************************
| Program: An Implementation of the interpreter for File mode                  |
| Last Updated: 4/4/2019       FCUP       Copyright (c) 2019, Eduardo Morgado  |
********************************************************************************
|   The program functionality:                                                 |
|       ->Works almost like the interactive mode except it will read from file |
*******************************************************************************/
#include <stdio.h>
#ifndef SHELL_FILE_H
#define SHELL_FILE_H

char* readFile(FILE*);
void shellFile(FILE*);

#endif
