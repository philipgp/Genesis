#ifndef LITERAL_H
#define LITERAL_H 
#define MaxLiteral 250

#define LIT_INT 0
#define LIT_STR 1
#include "SymbolTable.h"
struct littab
    {
    int m_iSymId,m_Type;
    char* m_LpszLiteralValue;
    int m_iSymbolAddress;
    }LitTab[MaxLiteral];
int LitCount=0;
char *GenerateTempLiteralName();
int AddLiteral(char * LpszValue,int iType) //0 for Integer and 1 for string
    {
    char szTempLiteralName[LEN];
    int SymId;
    int iValue;
    if(LitCount>=MaxLiteral)
		ErrorHandler(ERROR,"maximum Literals reached");
	strcpy(szTempLiteralName,GenerateTempLiteralName());
    SymId=AddSymbol(szTempLiteralName);
	
	    if(iType==0)
        {
        iValue=atoi(LpszValue);
		LpszValue=AddNewString(LpszValue);
        if((iValue>-127)&&(iValue<128))
            {
            SetDataType(SymId,GetDataTypeId("_int_ltrl_8"));
            }
        else if((iValue>-32767)&&(iValue<32767))
            {
            SetDataType(SymId,GetDataTypeId("_int_ltrl_16"));
            }
        else
            {
            SetDataType(SymId,GetDataTypeId("_int_ltrl_32"));
            }
        }
    LitTab[LitCount].m_iSymId=SymId;
    LitTab[LitCount].m_Type=iType;
    LitTab[LitCount].m_LpszLiteralValue=LpszValue;
    LitCount++;
    return SymId;
    

    }

char *GetLiteralValue(int SymId,int format)
    {
    int i=0;
    char szTemp[MAX_SYM_LEN];
    szTemp[0]='\0';
    for(i=0;i<LitCount;i++)
        {
        if(LitTab[i].m_iSymId==SymId)
            {
            strcpy(szTemp,LitTab[i].m_LpszLiteralValue);
            break;
            }
        }
    if((format==GetDataTypeId("uint8"))||(format==GetDataTypeId("uint16")||(format==GetDataTypeId("uint32"))||(format==GetDataTypeId("void"))))
        return szTemp;
    else
        {
        int iLen,iOffset;
        iLen=strlen(szTemp);
        if(format==GetDataTypeId("int8"))
            {
            if(iLen>2)
                {
                return szTemp+iLen-2;
                }
            else
                return szTemp;
            }
        if(format==GetDataTypeId("int16"))
            {
            if(iLen>2)
                {
                return szTemp+iLen-4;
                }
            else
                return szTemp;
            }
        if(format==GetDataTypeId("int32"))
            {
            if(iLen>2)
                {
                return szTemp+iLen-2;
                }
            else
                return szTemp;
            }
        }
    return NULL;
    }
void WriteStringLiterals()
{
    int iCount=0,symId,iLen;
    char *LpszLiteralName,*LpszLiteralValue,*LpszString;

    for(;iCount<LitCount;iCount++)
    {
        if(LitTab[iCount].m_Type==LIT_STR)
        {
            symId=LitTab[iCount].m_iSymId;
            LpszLiteralName=GetSymbolName(symId);
            LpszLiteralValue=GetLiteralValue(symId,0);
            iLen=strlen(LpszLiteralName)+strlen(LpszLiteralValue)+8;
            LpszString=(char *)malloc(iLen+2); //+2  for ',0'
            strcpy(LpszString,LpszLiteralName);
            strcat(LpszString," db \'");
            
            strcat(LpszString,GetLiteralValue(symId,0));
            strcat(LpszString,"\',0\n");
            AddOutputASM("",LpszString);
            free(LpszString);
        }
    }
}
int GetLiteralSize(int SymId,int Signed)
    {
    int i=0;
    int iValue;
    char szTemp[MAX_SYM_LEN];
    szTemp[0]='\0';
    for(i=0;i<LitCount;i++)
        {
        if(LitTab[i].m_iSymId==SymId)
            {
            strcpy(szTemp,LitTab[i].m_LpszLiteralValue);
            break;
            }
        }
    iValue=atoi(szTemp);
    if(Signed==true)
        {
        if((iValue>-128)&&(iValue<128))
            return 1;
        else if((iValue>-32768)&&(iValue<32767))
        return 2;
        else
            return 4;
        }
    else
        {
        if(iValue<255)
            return 1;
        else if(iValue<65536)
            return 2;
        else
            return 4;
        

        }
    }
#endif