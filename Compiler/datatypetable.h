
#ifndef DATATYPETABLE_H
#define DATATYPETABLE_H 
#define MAX_DATATYPE_COUNT 40
#define DataType_SIZE 30
#include "SymbolTable.h"
struct DatatypeTable
    {
    char m_szDataTypeName[DataType_SIZE];//[DataType_SIZE][MaxTableLen]={{"void"},{"int8"},{"int16"},{"int32"},{"int64"},{"char"}};
    int m_iDataTypeSize;//[MaxTableLen]={0,1,2,3,4,5,2};
    //struct Optab * m_LpDataMembers,*m_FunctionMembers;
    }DataTypeTable[MAX_DATATYPE_COUNT];
int DataTypeCount=0;
struct SDataTypeList
{
int m_iDataType;
struct SDataTypeList *m_LpNext;
};

#include "optab.h"
#include "string.h"

/*-------------------------------------------------------------------------------*
 * AddDataType() adds a new DataType.											 *
 * LpszDataTypeName- Name of DataType(eg int8)                                   *
 * iDataTypeSize   - Size of DataType(eg 1)                                      *
 *-------------------------------------------------------------------------------*/
void AddDataType(char * LpszDataTypeName,int iDataTypeSize,Optab *LpDataMembers,Optab *Functions)
    {
    strcpy(DataTypeTable[DataTypeCount].m_szDataTypeName,LpszDataTypeName);
    DataTypeTable[DataTypeCount].m_iDataTypeSize=iDataTypeSize;
    DataTypeCount++;
	if(DataTypeCount==MAX_DATATYPE_COUNT)
		ErrorHandler(ERROR,"MAXIMUM DataType count reached");
    }
int SearchDataTypeTable(char *Datatype)
    {
    int i;
    for(i=0;i<DataTypeCount;i++)
        {
        if(strcmpi(DataTypeTable[i].m_szDataTypeName,Datatype)==0)
            {
            return i;
            }
        }
    return -1;
    }
/*-------------------------------------------------------------------------------*
 * GetDataTypeId() Gets index of DataTypeName in DataTypeTable					 *
 * LpszDataType- Name of DataType(eg int8)                                       *
 *-------------------------------------------------------------------------------*/
int GetDataTypeId(char * LpszDataType)
    {
    int i;
    for(i=0;i<DataTypeCount;i++)
        {
        if(strcmpi(DataTypeTable[i].m_szDataTypeName,LpszDataType)==0)
            {
            return i;
            }
        }
    return -1;
    }
/*-------------------------------------------------------------------------------*
 * GetDatatypeSize() Gets DataTypeSize of a DataType							 *
 * SymTabPos- DataType ID							                             *
 *-------------------------------------------------------------------------------*/
int GetDataTypeSize(int DataTypeTablePos)
    {
    return DataTypeTable[DataTypeTablePos].m_iDataTypeSize;
    }
/*-------------------------------------------------------------------------------*
 * GetDataTypeName() Gets name of the Datatype in DataTypeTable					 *
 * DatatypeId- index of DataTypee in DataTypetable                               *
 *-------------------------------------------------------------------------------*/
char * GetDataTypeName(int DatatypeId)
    {
		if(DatatypeId!=-1)
    return DataTypeTable[DatatypeId].m_szDataTypeName;
		else return NULL;
    }
/*-------------------------------------------------------------------------------*
 * GetDatatypeSize() Gets DataTypeSize of a variable							 *
 * SymTabPos- SymTabPos								                             *
 *-------------------------------------------------------------------------------*/
int GetDatatypeSize(int SymTabPos)
    {
    struct ArrayDimension * LpDimensionStart,*LpDimensionCurrent;
    int iValue,iLength;
    char szLiteralValue[20];
    iValue=1;
    if(IsReference(SymTabPos)) // if it is a reference variable, get the original variable size
        {
        char szTemp[MAX_SYM_LEN];
        int iOrginalSymId;
        strcpy(szTemp,GetSymbolName(SymTabPos));
        iOrginalSymId=GetSymbolId(szTemp+1);
        return DataTypeTable[SymTab[iOrginalSymId].PointerTarget].m_iDataTypeSize;
        }
	if(SymTab[SymTabPos].LpDimension!=NULL)
        {
			LpDimensionStart=SymTab[SymTabPos].LpDimension;
        LpDimensionCurrent=LpDimensionStart;
		iValue=DataTypeTable[GetDataType(SymTabPos)].m_iDataTypeSize;
        while(1)
        {
            iLength=LpDimensionCurrent->iDimension;
            iValue=iValue*iLength;
			LpDimensionCurrent=LpDimensionCurrent->LpNext;
            if(LpDimensionCurrent==NULL)
                break;
            }
        return iValue;
        }
    else
        return DataTypeTable[GetDataType(SymTabPos)].m_iDataTypeSize;


    }
#endif