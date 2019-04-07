/*******************************************************************************
| Program: Conceptual Defition of an Instruction                               |
| Author: Eduardo Morgado                                                      |
| Last Updated: 18/3/2019                                                  FCUP|
*******************************************************************************/
#ifndef STRUCTURES_H
#define STRUCTURES_H

/*------------------------------------------------------------------------------
|                            Macro Defenition                                  |
------------------------------------------------------------------------------*/
#define OP(I) ((I)->op)                                    //I is an instruction
#define VAL(E) ((E).contents.val)                          //E is an Elem
#define STRING(E) ((E).contents.name)                      //E is an Elem
#define KIND(E) ((E).kind)                                 //E is an Elem
#define FELEM(I) ((I)->first)                              //I is an Instruction
#define SELEM(I) ((I)->second)                             //P is an Instruction
#define TELEM(I) ((I)->third)                              //P is an Instruction
//ForPointers
#define PVAL(E) ((E)->contents.val)                     //E is a pointer to Elem
#define PSTRING(E) ((E)->contents.name)                 //E is a pointer to Elem
#define PKIND(E) ((E)->kind)                            //E is a pointer to Elem




/*------------------------------------------------------------------------------
|                            Structure Defenition                              |
------------------------------------------------------------------------------*/
    /*
     * Consider a Structure to be an Instruction (Struct Instr)
     * That structure is defined by 4 values, the first value will be the      
     *      type of instruction/operation kind and thus allow us to deduce the
     *      other values ex:
     *          i=0; 
     *              op=ATRIB
     *              first.kind=STRING|first.contents.name=i
     *              second.kind=INT_CONST|second.contents.val=0
     *              third.kind=EMPTY
     */
/*Type of Operation defenition------------------------------------------------*/
    typedef enum{
        ATRIB,ADD,SUB,MUL,DIV,IF_I,PRINT,READ,GOTO_I,LABEL,OPEN,MOD
    }OpKind;
/*Type of valid elements defenition-------------------------------------------*/
    typedef enum{
        EMPTY,INT_CONST,STRING
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
        OpKind op;
        Elem first,second,third;
    }Instr,*PInstr;
#endif
