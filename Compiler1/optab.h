#ifndef OPTAB_H
#define OPTAB_H 
#include "main.h"
struct optab
    {
    int Result,Operator,Operand1,Operand2,SubscriptIndex,ArrayIndex;
    char Result_c[MAX_SYM_LEN],Operator_c[MaxOperatorLen],Operand1_c[MAX_SYM_LEN],Operand2_c[MAX_SYM_LEN];
    char *PlainInstr,Label[MaxLabelLen],TargetLabel[MaxLabelLen],*AsmPointer;
    struct optab *previous,*next,*subscript,*instr_addr;
    };
typedef struct optab Optab;
#endif