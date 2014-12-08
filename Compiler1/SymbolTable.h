#ifndef SYMTAB_H
#define SYMTAB_H
#include "optab.h"
#include "literals.h"
#include "main.h"
#define MAX_CLASS_NAME_LEN 30
char szCurrentClass[MAX_CLASS_NAME_LEN];
enum Scope
{
    LocalScope,
    ObjectScope,
    eStructScope,
    eWorkerScope,
    GlobalScope,
    NoScope
} CurrentScope;
enum StorageType
    {
    LocalStorage,
    StructMember,
    StructStorage,
    PointerStorage,
    NONEStorage,
    TempStorage,
    ObjectDataMember
    };
struct ArrayDimension
{
    int iDimension; //current Dimension eg: in a[2][3] . 2 is stored here and pointer to 3 is in LpNext
    struct ArrayDimension *LpNext; //pointer to next value
};
struct symtab
{
    char Symbol[MAX_SYM_LEN]; //Variable Name
    struct ArrayDimension *LpDimension;//Points to array Index [3][4]
    int SymbolAddress; // Offset address from EBP.
    int DataType,BlockNumber; // Blocknumber shows the nesting levels
    Optab *NodePtr; //Points to Optab entry for a ID.stores MakeNode(ID)
    int m_StorageType; //NONEStorage,LocalStorage.Used to assign no address to Invalid SymTab entries
    enum Scope m_Scope; //Scope LocalScope,ObjectScope,GlobalScope
    int PointerTarget; // Points to the correct DataType location in Datatype
} SymTab[MAXSymbols];

int SymCount=0; // Symbol Count
int Block_Number=0;
int AddSymbol(char *SYMBOL)
        {
        int i,iOffset;
		int sc,iDataType;
		struct OMProperty *LpCurrentProp;
		sc=CurrentScope;
		iDataType=0;
		if(SymCount>=MAXSymbols-10)
		{
			ErrorHandler(ERROR,"MAXIMUM Symbols reached...AddSymbol()");
			exit(0);
		}
		for(i=0;i<SymCount;i++)
            {
            if(strcmp(SymTab[i].Symbol,SYMBOL)==0)
                {
                if(SymTab[i].BlockNumber<=Block_Number)
                    return i;
                }
            }
		iOffset=GetPropertyOffsetAddress(szCurrentClass,SYMBOL);
		if(iOffset>-1)
		{
			sc=ObjectScope;
			iDataType=GetPropertyDataType(szCurrentClass,SYMBOL);

		}
		
        if(SymCount==MAXSymbols-1)
            {
            for(i=0;i<SymCount;i++)
                {
                if(strcmp(SymTab[i].Symbol,"")==0)
                    {
                    strcpy(SymTab[i].Symbol,SYMBOL);
        SymTab[i].BlockNumber=Block_Number;
        SymTab[i].m_Scope=sc;
		SymTab[i].SymbolAddress=iOffset;
		SymTab[i].DataType=iDataType;

return i;
                    }
                } //catch error of Exceeding MAXSymbols

            }
        else
            {
        strcpy(SymTab[SymCount].Symbol,SYMBOL);
        SymTab[SymCount].BlockNumber=Block_Number;
        SymTab[SymCount].m_Scope=sc;
        SymTab[SymCount].NodePtr=NULL;
		SymTab[SymCount].DataType=iDataType;
        SymTab[SymCount].m_StorageType=NONEStorage;
		SymTab[SymCount].SymbolAddress=iOffset;
		SymTab[SymCount].LpDimension=NULL;
        SymCount++;
        return SymCount-1;
            }
		
       }
char * GetSymbolName(int SYMID)
{
    char *Sym;
    if(SYMID==-1)
        return "";
    Sym=SymTab[SYMID].Symbol;
    return Sym;
}
/*-------------------------------------------------------------------------------*
 * SetDataType() Set DataType of variable in DataTypeTable						 *
 * SymTabPos - Position of symbol on Symtab										 *
 * Datatype  - DataType Position of symbol on DataTypeTable						 *
 *-------------------------------------------------------------------------------*/
void SetDataType(int SymTabPos,int Datatype)
    {
    SymTab[SymTabPos].DataType=Datatype; 
    }
int GetPointerTarget(int iSymId)
{
    return SymTab[iSymId].PointerTarget;
}
/*-------------------------------------------------------------------------------*
 * IsPrimitive() checks whether a particular symbol is Primitive(int8,int16,in32)*
 * Storage can be optimized for such functions                                   *
 *-------------------------------------------------------------------------------*/
int IsPrimitive(int SymTabPos)
{
    int iDataType;
    if(IsReference(SymTabPos))
    {
        iDataType=SymTab[SymTabPos].PointerTarget;
    }
    else
        iDataType=GetDataType(SymTabPos);
    if((iDataType==GetDataTypeId("int8"))||(iDataType==GetDataTypeId("int16"))||(iDataType==GetDataTypeId("int32"))||(iDataType==GetDataTypeId("uint8"))||(iDataType==GetDataTypeId("uint16"))||(iDataType==GetDataTypeId("uint32"))||(iDataType==GetDataTypeId("char"))||(iDataType==GetDataTypeId("Pointer"))||(iDataType==GetDataTypeId("int_imm"))||(iDataType==GetDataTypeId("_int_ltrl_8"))||(iDataType==GetDataTypeId("_int_ltrl_16"))||(iDataType==GetDataTypeId("_int_ltrl_32"))||(iDataType==GetDataTypeId("AddressOf")))
        return 1;
    else
        return 0;

}
/*-------------------------------------------------------------------------------*
 * GetSymbolId() Gets the SYMTAB position of Symbol								 *
 * LpszSymName- Symbol Name					                                     *
 * returns- Symbol ID						                                     *
 *-------------------------------------------------------------------------------*/
int GetSymbolId(char *LpszSymName)
    {
    int i,SymId;
    for(i=0;i<SymCount;i++)
        {
        if(strcmp(SymTab[i].Symbol,LpszSymName)==0)
            return i;
        }
    i=GetPropertyDataType(szCurrentClass,LpszSymName);

    if(i!=-1)
    {
        SymId=AddSymbol(LpszSymName);
        SetDataType(SymId,i);
        SymTab[SymId].m_Scope=ObjectScope;
        

    }

    return -1;
    }
void SetDimension(int SymTabPos,Optab * DimenSion)
    {
	struct ArrayDimension *LpCurrent,*LpStart,*LpPrevious;
	char szLen[5];
	Optab *LpOptabCurrent,*LpOptabStart;
	LpCurrent=NULL;
	LpStart=NULL;
	LpPrevious=NULL;
	LpOptabStart=DimenSion;
	LpOptabCurrent=LpOptabStart;
	if(LpOptabStart==NULL)
		return;
	while(1)
	{
		LpCurrent=(struct ArrayDimension*)malloc(sizeof(struct ArrayDimension));
		LpCurrent->LpNext=NULL;
		strcpy(szLen,GetLiteralValue(LpOptabCurrent->Result,0));
		LpCurrent->iDimension=atoi(szLen);
		if(LpStart==NULL)
		{
			LpStart=LpCurrent;
			LpPrevious=LpCurrent;
		}
		else
		{
			LpPrevious->LpNext=LpCurrent;
			LpPrevious=LpCurrent;
		}
		LpOptabCurrent=LpOptabCurrent->next;
		if(LpOptabCurrent==LpOptabStart)
			break;
	}

	SymTab[SymTabPos].LpDimension=LpStart;
    }
/*-------------------------------------------------------------------------------*
 * GetSymTabPos() Searches the SYMTAB for a particular Variable Name	     	 *
 * LpszIdentifier- Symbol name					                                 *
 * returns- Symbol ID								                             *
 *-------------------------------------------------------------------------------*/
int GetSymTabPos(char *LpszIdentifier)
    {
    int i;
    for(i=0;i<SymCount;i++)
        {
        if(strcmp(SymTab[i].Symbol,LpszIdentifier)==0)
            {
            return i;
            }
        }
    return -1;
    }
/*-------------------------------------------------------------------------------*
 * IsSigned() Checks whether a symbol is signed or unsigned.	     			 *
 * SymTabPos- Symbol ID					                                         *
 * returns- boolean value whether it is signed or not                            *
 *-------------------------------------------------------------------------------*/
int IsSigned(int SymTabPos)
{
    int iOrginalSymbol;
    int DataType;
    char szSym[MAX_SYM_LEN];
    if(IsReference(SymTabPos))
    {
        strcpy(szSym,GetSymbolName(SymTabPos));
        iOrginalSymbol=GetSymbolId(szSym+1);
        DataType=SymTab[iOrginalSymbol].PointerTarget;
    }
    else
    {
        DataType=GetDataType(SymTabPos);
    }
    if((DataType==GetDataTypeId("int8"))||(DataType==GetDataTypeId("int16"))||(DataType==GetDataTypeId("int32"))||(DataType==GetDataTypeId("_int_ltrl_8"))||(DataType==GetDataTypeId("_int_ltrl_16"))||(DataType==GetDataTypeId("_int_ltrl_32")))
        return 1;
    else
        return 0;

}

/*-------------------------------------------------------------------------------*
 * DeleteSymbol() Delete a symbol from Symtab									 *
 * SymTabPos - Position of symbol on Symtab										 *
 * Datatype  - DataType Position of symbol on DataTypeTable						 *
 *-------------------------------------------------------------------------------*/
void DeleteSymbol(int Index)
      {
      if(Index==-1)
	  {
		  ErrorHandler(WARNING,"Trying to delete Symbol of SymId -1");
		  return;
	  }
      SymTab[Index].NodePtr=NULL;
      SymTab[Index].m_StorageType=NONEStorage;
	  SymTab[Index].BlockNumber=0;
	  SymTab[Index].DataType=0;
      SymTab[Index].LpDimension=NULL;
	  SymTab[Index].m_Scope=LocalScope;
      SymTab[Index].Symbol[0]='\0';  //have to delete the optab entry for this.
	  if(Index==SymCount-1)
	  {
		  SymCount--;
	  }
      }
/*-------------------------------------------------------------------------------*
 * GetDataType() Gets the DataTypeId of Symbol,if reference,                     *
 * the original one is took														 *
 * SymTabPos - Position of symbol on Symtab										 *
 *-------------------------------------------------------------------------------*/
int GetDataType(int SymTabPos)
    {
    char szTempSym[MAX_SYM_LEN];
    int iOrginalSymbol;
    if(SymTabPos==-1)
        return -1;
   
    if(IsReference(SymTabPos))
        {
        strcpy(szTempSym,GetSymbolName(SymTabPos));
        return SymTab[GetSymbolId(szTempSym)].PointerTarget;
        }
    return SymTab[SymTabPos].DataType;
    }

int GetStorage(int Index)
    {
    return SymTab[Index].m_StorageType;
    }
int IsValidSymbol(int iSymTab)
{
    if(SymTab[iSymTab].Symbol[0]=='\0')
return 0;
else 
return 1;
}
void SetSymbolScope(int SymId,int Scope)
{
    SymTab[SymId].m_Scope=Scope;
}

char *GetLiteralName(int SymId)
    {
    return SymTab[SymId].Symbol;
    }
void SetPointerTarget(int SymId,int DataTypeTabLoc)
    {
    SymTab[SymId].PointerTarget=DataTypeTabLoc;
    }

int GetScope(int SymId)
    {
    return SymTab[SymId].m_Scope;
    }

/*-------------------------------------------------------------------------------*
 * GetDimension() Gets the Dimension of an array variable                        *
 * SymTabPos - Position of symbol on Symtab										 *
 *-------------------------------------------------------------------------------*/
struct ArrayDimension * GetDimension(int SymTabPos)
    {
		struct OMProperty *LpProperty;
		char *LpszPropertyName;
        if(!IsValidSymbol(SymTabPos))
            return NULL;
		if(GetScope(SymTabPos)==LocalScope)
		return SymTab[SymTabPos].LpDimension;
		if(GetScope(SymTabPos)==eWorkerScope)
		return SymTab[SymTabPos].LpDimension;
		else if(GetScope(SymTabPos)==GlobalScope)
			return SymTab[SymTabPos].LpDimension;
		else if(GetScope(SymTabPos)==ObjectScope)
		{
			LpszPropertyName=GetSymbolName(SymTabPos);
			LpProperty=GetOMProperty(szCurrentClass,LpszPropertyName);
			if(LpProperty!=NULL)
			{
				return LpProperty->m_LpDimension;
			}
			else
			{
				ErrorHandler(ERROR,"No Such Property..");
			}
		}

    }
int GetSymbolAddress(int SymId)
      {
      return SymTab[SymId].SymbolAddress;
      }
#endif