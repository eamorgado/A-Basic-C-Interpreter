/*******************************************************************************
| Program: Basic UserShell defenition                                          |
| Author: Eduardo Morgado                                                      |
| Last Updated: 18/3/2019                                                      |
*******************************************************************************/
#ifndef STRUCTURES_H
#define STRUCTURES_H

/*------------------------------------------------------------------------------
|                            Macro Defenition                                  |
------------------------------------------------------------------------------*/
#define OP(I) ((I)->op)                                    //I is an instruction
#define VAL(E) ((E).contents.val)                        //E is an Elem
#define STRING(E) ((E).contents.name)
#define KIND(E) ((E).kind)                                 //E is an Elem
#define FELEM(I) ((I)->first)                              //I is an Instruction
#define SELEM(I) ((I)->second)                             //P is an Instruction
#define TELEM(I) ((I)->third)                              //P is an Instruction
#define PVAL(E) ((E)->contents.val)                        //E is an Elem
#define PSTRING(E) ((E)->contents.name)
#define PKIND(E) ((E)->kind)                                 //E is an Elem




/*------------------------------------------------------------------------------
|                            Structure Defenition                              |
------------------------------------------------------------------------------*/
    /*
     * Consider a Structure to be an Instruction (Struct Instr)
     * That structure is defined by the type of operation it represents
     *     as the elements that make it
     * If the operation kind of the instr, we know that it represents the value
     *    of its first variable (first is type String and content name), where
     *    the second element represents its true value(can be string or int),
     *    the third element is empty
     * An Element can be defined as its type(EMPTY,..) and the values it stores
     */
/*Type of Operation defenition------------------------------------------------*/
    typedef enum{
        ATRIB,ADD,SUB,MUL,DIV,IF_I,PRINT,READ,GOTO_I,LABEL,OPEN,MOD
       //0     1   2   3   4    5   6      7    8      9    10   11
    }OpKind;
/*Type of valid elements defenition-------------------------------------------*/
    typedef enum{
        EMPTY,INT_CONST,STRING
        //0     1       2
    }ElemKind;
/*Singular Element Defenition-------------------------------------------------*/
    typedef struct{
        ElemKind kind;
        union{
            int val;
            char *name;
        }contents;
    }Elem, *PElem;
/*Instruction Defenition------------------------------------------------------*/
    typedef struct{
        //defines (OpKind,first,second,third)
            /* Ex:
             *    p=p+2;
             *     -> (ADD,p,p,2);
             *    first: STRING; (name==p)
             *    second:STRING; (name==p)
             *    third: INT_CONST; (val=2)
             */
        OpKind op;
        Elem first,second,third;
    }Instr,*PInstr;
#endif
