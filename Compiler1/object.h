#ifndef OBJECT_H
#define OBJECT_H 

#define MAX_CLASS_COUNT 20
#include "datatypetable.h"

typedef struct OMFunction
{
	char m_szFunctionName[MAX_FUNCTION_NAME_LEN],m_szFunctionLabel[MAX_FUNCTION_LABEL_LEN];
	int iReturnType;
	struct SDataTypeList *m_LpFormalParameter;
	struct OMFunction *m_LpNext;
}omFunction;
struct ClassDefinition
{
	char m_szClassName[MAX_CLASS_NAME_LEN];
	struct OMProperty *m_LpMemberVar;
	struct OMFunction *m_LpMemberFun;
}ClassDefn[MAX_CLASS_COUNT];
struct ClassDefinition * LpCurrentClass;

int iClassCount=0;
//
/*-------------------------------------------------------------------------------*
 * GetClassInformation() Gets the Class Structure from Class Array				 *
 * LpszClassName- ClassName						                                 *
 *-------------------------------------------------------------------------------*/
struct ClassDefinition * GetClassInformation(char *LpszClassName)
  {
	  int i;
	  int found;
	  found=0;
	  if(strcmp(LpszClassName,szCurrentClass)==0)
	  return LpCurrentClass;
	  for(i=0;i<iClassCount;i++) // iterating throught the class array looking for ClassName
	  {
		  if(strcmp(ClassDefn[i].m_szClassName,LpszClassName)==0)
		  {
			  found=1;
		  break;
		  }
	  }
	  if(found==1)
	  {
		  return &ClassDefn[i];
	  }
	  else
	  {
		  ErrorHandler(INFO,"Class Not Found");
		  return NULL;
	  }
  }

/*-------------------------------------------------------------------------------*
 * DisplayClassFunctions() Prints Class Member Functions						 *
 * LpszClassName- ClassName						                                 *
 *-------------------------------------------------------------------------------*/
void DisplayClassFunctions(char *LpszClassName)
     {
		 #if (CHECK_DEBUG_ENABLED(DEBUG_SHOW_CLASSMEMBERS))
     int i;
     struct ClassDefinition *LpClassDefn;
	 struct OMFunction * LpFunction;
	 struct SDataTypeList *LpFormalParams;
	 LpClassDefn=GetClassInformation(LpszClassName);
     
      if(LpClassDefn==NULL)
	 {
		 ErrorHandler(ERROR,"No Such Class.");
		 return;
	 }
	 else
	 {
		 LpFunction=LpClassDefn->m_LpMemberFun;
		 
		 printf("\n-------------Class Functions(%s)---------------\nReturnType FunctionName Function Label Paramteres\n",LpszClassName);
   
	
		
		while(LpFunction!=NULL)
		{
			
			printf("%s\t\t%s\t%s\t",GetDataTypeName(LpFunction->iReturnType),LpFunction->m_szFunctionName,LpFunction->m_szFunctionLabel);

			LpFormalParams=LpFunction->m_LpFormalParameter;
			while(LpFormalParams!=NULL)
			{
				printf("%s\t",GetDataTypeName(LpFormalParams->m_iDataType));
				LpFormalParams=LpFormalParams->m_LpNext;
			}
			printf("\n");
			LpFunction=LpFunction->m_LpNext;
		}

	 }
#endif
     }
/*-------------------------------------------------------------------------------*
 * DisplayClassMembers() Prints Class Member variables							 *
 * LpszClassName- ClassName						                                 *
 *-------------------------------------------------------------------------------*/
void DisplayClassMembers(char *LpszClassName)
 {
	 #if (CHECK_DEBUG_ENABLED(DEBUG_SHOW_CLASSMEMBERS))
	 struct OMProperty *LpProperty;
	 struct ClassDefinition *LpClassDefn;
	 LpClassDefn=GetClassInformation(LpszClassName);
	 if(LpClassDefn==NULL)
	 {
		 ErrorHandler(ERROR,"No Such Class.");
		 return;
	 }
	 else
	 {
		 LpProperty=LpClassDefn->m_LpMemberVar;
		 
		 printf("----------------------Class Members(%s)-------------------\nSymbolName DataType\n",LpszClassName);
		 while(LpProperty!=NULL)
		 {
			 printf("%s\t\t%s\n",LpProperty->m_szPropertyName,GetDataTypeName(LpProperty->m_iDataType));
			 LpProperty=LpProperty->m_LpNext;
		 }
	 }
#endif
 }
/*-------------------------------------------------------------------------------*
 * AddFunctionToClass() Add a Function as a member to the class					 *
 * LpszClassName- ClassName						                                 *
 * LpCurrentFunction- Function Structure		                                 *
 *-------------------------------------------------------------------------------*/
void AddFunctionToClass(char *LpszClassName,struct OMFunction *LpCurrentFunction)
	{

	int i;
	struct OMFunction * LpCFunction,*LpPFunction;
	int found=0;
	struct ClassDefinition *LpCDefn=NULL;
	
		LpCDefn=GetClassInformation(LpszClassName); // Used to get the class Object from the CLASS ARRAY
	
	if(LpCDefn!=NULL)
		{
		LpCFunction=LpCDefn->m_LpMemberFun;
		if(LpCFunction==NULL)
			{
			LpCDefn->m_LpMemberFun=LpCurrentFunction;
			}
		else
			{
			while(LpCFunction!=NULL)
				{
				LpPFunction=LpCFunction;
				LpCFunction=LpCFunction->m_LpNext;
				}
			LpPFunction->m_LpNext=LpCurrentFunction;	
			}
		}
	}
Optab *MakeObjectDefinition(int iIdentifier,Optab * DataBlock,Optab *FunctionBlock)
    {
    int iDataTypeSize; 
	struct OMProperty * PropertyBlock;
	char *LpszClassName;

	LpszClassName=GetSymbolName(iIdentifier);
	DisplayClassFunctions(szCurrentClass);
	DisplayClassMembers(szCurrentClass);
       
       return NULL;
    }

/*-------------------------------------------------------------------------------*
 * AddPropertyToClass() Add a Property as a member to the class					 *
 * LpszClassName- ClassName						                                 *
 * LpDataBlock- List of variables				                                 *
 *-------------------------------------------------------------------------------*/
struct OMProperty * AddPropertyToClass(char * LpszClassName,Optab *LpDataBlock)
	{
	Optab * LpMemberStart,*LpMemberCurrent;
	struct OMProperty *LpPropCurrent,*LpPropStart,*LpPropPrev;
	int i;
	int found=0;
	struct ClassDefinition *LpCDefn=NULL;
	int iSize;
	iSize=0;
	LpPropStart=NULL;
	LpPropPrev=NULL;
	LpPropCurrent=NULL;
	LpMemberStart=LpDataBlock;
	LpMemberCurrent=LpDataBlock;
	do
	{
		LpPropCurrent=(struct OMProperty*)malloc(sizeof(struct OMProperty));
		LpPropCurrent->m_LpNext=NULL;
		strcpy(LpPropCurrent->m_szPropertyName,GetSymbolName(LpMemberCurrent->Result));
		LpPropCurrent->m_iDataType=GetDataType(LpMemberCurrent->Result);
		if(LpPropStart==NULL)
		{
			LpPropStart=LpPropCurrent;
		}
		else
		{
			iSize=GetDataTypeSize(LpPropPrev->m_iDataType);
			LpPropPrev->m_LpNext=LpPropCurrent;
		}
		LpPropPrev=LpPropCurrent;
		DeleteSymbol(LpMemberCurrent->Result);
		//TODO: delete the Optab for corresponding entry
		LpMemberCurrent=LpMemberCurrent->next;
	}while(LpMemberCurrent!=LpMemberStart);
	
	
		LpCDefn=GetClassInformation(LpszClassName); //Getting Class Object from Class Table
	
	LpCDefn->m_LpMemberVar=LpPropStart;
	return LpPropStart;
	}
#endif