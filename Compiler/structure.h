#ifndef STRUCT_H
#define STRUCT_H 
int iStructCount=0;
struct StructDecMember
{
	char m_szSymbolName[MAX_VARIABLE_LEN];
	int m_iDataType;
	struct StructDecMember *m_LpNext;
};
struct StructDec
{
	char m_szStructName[MAX_VARIABLE_LEN];
	struct StructDecMember *m_LpStart;
}StructTable[MAX_STRUCT_LEN];
/*-------------------------------------------------------------------------------*
 * VariableIsStruct() Checks whether a symbol is struct							 *
 * Current- Optab entry 							                             *
 *-------------------------------------------------------------------------------*/
int VariableIsStruct(Optab * Current)
      {
      int iDataType,i;
      iDataType=GetDataType(Current->Result);
	  i=GetStructIndex(GetDataTypeName(iDataType));
      if(i!=-1)
          return 1;
      else
          return 0;
      }
/*-------------------------------------------------------------------------------*
 * IsStruct() Checks whether a symbol is struct									 *
 * SymId- SymID          							                             *
 *-------------------------------------------------------------------------------*/
int IsStruct(int SymId)
      {
      int iDataType,i;
      iDataType=GetDataType(SymId);
      if(iDataType==-1)
	  {
		  ErrorHandler(ERROR,"Invalid DataType passed to IsStruct()");
		  return 0;
	  }
      i=GetStructIndex(GetDataTypeName(iDataType));
      if(i!=-1)
          return 1;
      else
          return 0;
      }
int GetStructIndex(char *LpszStructName)
{
	int i;
	for(i=0;i<iStructCount;i++)
	{
		if(strcmp(StructTable[i].m_szStructName,LpszStructName)==0)
		{
		return i;
		}
		
	}
	return -1;
}
/*-------------------------------------------------------------------------------*
 * DataTypeIsStruct() Checks whether a particular datatype is struct			 *
 * iDataType- DataType     							                             *
 *-------------------------------------------------------------------------------*/
  int DataTypeIsStruct(int iDataType)
      {
		  int i;
      i=GetStructIndex(GetDataTypeName(iDataType)); // see if that datatype is added to struct tables.
      if(i!=-1)
          return 1;
      else
          return 0;

      }
/*-------------------------------------------------------------------------------*
 * GetDataType_StructMember() Gets DataType of a struct member          		 *
 * LpszStructName- Name of the structure			                             *
 * LpszMemberName- Name of the Variable			                             *
 *-------------------------------------------------------------------------------*/
  int GetDataType_StructMember(char *LpszStructName,char *LpszMemberName)
{
	int i,j;
	int found;
	char szErrorMessage[100];
	struct StructDecMember *LpMemCurrent;
	found=1;
	i=GetStructIndex(LpszStructName);
	if(i!=-1)
	{
		LpMemCurrent=StructTable[i].m_LpStart;
		found=0;
		while(LpMemCurrent!=NULL)
		{
			if(strcmp(LpMemCurrent->m_szSymbolName,LpszMemberName)==0)
			{
				found=1;
				break;
			}
			
			LpMemCurrent=LpMemCurrent->m_LpNext;
		}
		if(found==1)
		{
			
			return LpMemCurrent->m_iDataType;
		}
		else
		{
			strcpy(szErrorMessage,"Struct member:");
			strcat(szErrorMessage,LpszMemberName);
			strcat(szErrorMessage," not found int struct:");
			strcat(szErrorMessage,LpszStructName);
			
			ErrorHandler(ERROR,szErrorMessage);
		}
	}
	else

	{
		strcpy(szErrorMessage,"Struct :");
			strcat(szErrorMessage,LpszStructName);
			strcat(szErrorMessage,"not found! ");
			
		ErrorHandler(ERROR,szErrorMessage);
	}

}
#endif