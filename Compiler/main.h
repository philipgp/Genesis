#ifndef MAIN_H
#define MAIN_H 
#define MaxLabelLen 40 
#define false 0
#define FALSE -1
#define TRUE 1
#define FALSE 0
#define true 1
#define Nil -1
#define NIL -1
typedef struct OMProperty
{
	char m_szPropertyName[MAX_VARIABLE_LEN];
	int m_iDataType;
	struct ArrayDimension *m_LpDimension;
	struct OMProperty *m_LpNext;
};
struct OMProperty *GetOMProperty(char *LpszClassName,char *LpszPropertyName);
void SetDataType(int SymTabPos,int Datatype);
char *AddNewString(char *LpszValue);
char * GetSymbolName(int SYMID);
void AddOutputASM(char * LpszLabel,char *LpszInstruction);
void SetSymbolScope(int SymId,int Scope);

#include "errorhandler.h"
#endif