#ifndef SMTAB_H
#define SYMTAB_H 
#define LEN 30
#define MaxTableLen 40
#define DataType_SIZE 16
#define ARRAYSIZE 30
#define KW_SIZE 14
#include<string.h>
#include "optab.h"
#include "ObjCompiler.tab.h"
#include "stdio.h"
#include "stdlib.h"
//int IsMemberCall(char *LpszIdentifier);

struct DatatypeTable
    {
    char m_szDataTypeName[DataType_SIZE];//[DataType_SIZE][MaxTableLen]={{"void"},{"int8"},{"int16"},{"int32"},{"int64"},{"char"}};
    int m_iDataTypeSize;//[MaxTableLen]={0,1,2,3,4,5,2};
    
    struct Optab * m_LpMembers;
    }DataTypeTable[MaxTableLen];

struct Func_Table
    {
    int ReturnType;
    char Func_Name[32];
    struct Optab* ParamList;
    }FunctionTable[20];

char Symbol[ARRAYSIZE][LEN];
struct Optab *Dimension[LEN];
int DataType[LEN],BlockNumber[LEN],m_iStorageType[LEN];
char KW_Name[KW_SIZE][LEN]={{"If"},{"EndIf"},{"Then"},{"Else"},{"Elseif"},{"WHILE"},{"LOOP"},{"EndLoop"},{"Function"},{"Returns"},{"Return"},{"Break"},{"Continue"},{"Struct"}};
int KW_ID[KW_SIZE]={IF_KW,EIF_KW,THN_KW,ELSE_KW,{ELSIF_KW},{WHILE_KW},{LOOP_KW},{ENDLOOP_KW},{FUNCTION_KW},{RETURNS_KW},{RETURN_KW},{BREAK_LOOP_KW},{CONTINUE_LOOP_KW},{STRUCT_KW}};
    int SymCount=0,TempCount=0;
    
    int DataTypeCount=0;
int FunctionTableCount=0;
 
void initDataTypeTable()
    {
    AddDataType("void",0,NULL);
    AddDataType("int8",1,NULL);
    AddDataType("int16",2,NULL);
    AddDataType("int32",4,NULL);
    AddDataType("int64",8,NULL);
    AddDataType("char",2,NULL);
    }
int VariableIsStruct(Optab * Current)
      {
      int iDataType;
      iDataType=GetDataType(Current->Result);
      if(DataTypeTable[iDataType].m_LpMembers!=NULL)
          return 1;
      else
          return 0;
      }
  int DataTypeIsStruct(int iDataType)
      {
      if(DataTypeTable[iDataType].m_LpMembers!=NULL)
          return 1;
      else
          return 0;
      }
void AddDataType(char * LpszDataTypeName,int iDataTypeSize,Optab *LpMembers)
    {
    strcpy(DataTypeTable[DataTypeCount].m_szDataTypeName,LpszDataTypeName);
    DataTypeTable[DataTypeCount].m_iDataTypeSize=iDataTypeSize;
    DataTypeTable[DataTypeCount].m_LpMembers=LpMembers;
    DataTypeCount++;
    }


int AddFunctionTable(int RtrnType,char *FuncName,Optab * Parameters)
    {
    FunctionTable[FunctionTableCount].ReturnType=RtrnType;
    strcpy(FunctionTable[FunctionTableCount].Func_Name,FuncName);
    FunctionTable[FunctionTableCount].ParamList=Parameters;
    FunctionTableCount++;
    return FunctionTableCount;
    }
Optab* AddAsm(char *ASM)
    {
    Optab * AsmNode;
    AsmNode=MakeNode(-1);
    ASM[strlen(ASM)-1]='\0';
    ASM=ASM+5;
    AsmNode->AsmPointer=ASM;
    AsmNode->Operator=GetOperatorId("ASM");
    return AsmNode;
    }
 int SearchFunctionTable(char *FuncName)
     {
     int i;
     for(i=0;i<FunctionTableCount;i++)
         {
         if(strcmp(FuncName,FunctionTable[i].Func_Name)==0)
             {
             return i;
             }
         }
     return -1;
    }

int GetDataType(int SymTabPos)
    {
    return DataType[SymTabPos];
    }
void SetDataType(int SymTabPos,int Datatype)
    {
    DataType[SymTabPos]=Datatype;
    
    }
Optab * GetDimension(int SymTabPos)
    {
    return Dimension[SymTabPos];
    }
int GetDataTypeSize(int Pos)
    {
    return DataTypeTable[Pos].m_iDataTypeSize;
    }
int CalculateDataTypeSize(Optab *LpMembers)
    {
    Optab * LpCurrent,*LpStart;
    int iDataType,iSize;
    LpCurrent=LpStart=LpMembers;
    iSize=0;
    while(1)
        {
        iDataType=GetDataType(LpCurrent->Result);
        iSize=iSize+GetDataTypeSize(iDataType);
        LpCurrent=LpCurrent->next;
        if(LpCurrent==LpStart)
            break;
        }
    return iSize;
    }
void SetDimension(int SymTabPos,Optab * DimenSion)
    {
    Dimension[SymTabPos]=DimenSion;
    }
int GetSymTabPos(char *LpszIdentifier)
    {
    int i;
    for(i=0;i<SymCount;i++)
        {
        if(strcmp(Symbol[i],LpszIdentifier)==0)
            {
            return i;
            }
        }
    return -1;
    }
char * GetDataTypeName(int DatatypeId)
    {
    return DataTypeTable[DatatypeId].m_szDataTypeName;
    }

int CalculateMemberOffset(char *LpszParent,char *LpszMember)
    {
    int iDataType,iSize,iSymId;
    Optab * LpMember;
    iSize=0;
    iSymId=GetSymTabPos(LpszParent);
    iDataType=GetDataType(iSymId);
    iSymId=GetSymTabPos(LpszMember);
    LpMember=DataTypeTable[iDataType].m_LpMembers;
    if(LpMember==NULL)
        return GetDataTypeSize(iDataType);
    while(LpMember->Result!=iSymId)
        {
        iDataType=GetDataType(LpMember->Result);
        iSize=iSize+GetDataTypeSize(iDataType);
        LpMember=LpMember->next;
        }
    return iSize;
    }
 Optab* ProcessMemberCall(char *LpszIdentifier)
    {
    char szParent[32],szChild[32],szParent_Temp[32],szSymBuf[8],szDereferenceTemp[32];
    Optab * Result,*TempResult,*Operand1,*Operand2;
    int iMembers,iSize,iSymId;
    iSize=0;
    iMembers=IsMemberCall(LpszIdentifier);
    strncpy(szParent_Temp+1,LpszIdentifier,iMembers);
        szParent_Temp[iMembers+1]='\0';
        szParent_Temp[0]='&';
    while(iMembers!=0)
        {
        strncpy(szParent,LpszIdentifier,iMembers);
        szParent[iMembers]='\0';
        LpszIdentifier=LpszIdentifier+iMembers+1;
        iMembers=IsMemberCall(LpszIdentifier);
        if(iMembers)
            {
            strncpy(szChild,LpszIdentifier,iMembers);
            szChild[iMembers]='\0';
            iSize=iSize+CalculateMemberOffset(szParent,szChild);
            }
        else
            {
            strncpy(szChild,LpszIdentifier,iMembers);
            szChild[iMembers]='\0';
            iSize=iSize+CalculateMemberOffset(szParent,LpszIdentifier);
            }   
        }
    Operand1=MakeNode(AddSymbol(szParent_Temp));
    Operand2=MakeNode(AddSymbol(itoa(iSize,szSymBuf,10)));
    TempResult=GenerateTempVariable();
    Result=AddOperation(TempResult,GetOperatorId("+"),Operand1,Operand2);
    strcpy(szDereferenceTemp+1,GetSymbolName(TempResult->Result));
    szDereferenceTemp[0]='@';
    iSymId=AddSymbol(szDereferenceTemp);
    SetDataType(iSymId,GetDataType(GetSymTabPos(LpszIdentifier)));
    TempResult=MakeNode(iSymId);
    Operand2=MakeNode(-1);
    Result=AddOperation(TempResult,GetOperatorId("DEREFERENCE"),Result,Operand2);
    return Result;

    }
int IsMemberCall(char *LpszIdentifier)
    {
    int i;
    for(i=0;i<strlen(LpszIdentifier);i++)
        {
        if(LpszIdentifier[i]=='.')
            return i;
        }
    return 0;
    }
void DisplaySymTab()
    {
    int i;
     Optab * Temp,*Start;
    printf("-------------SymbolTable---------------\nSymbolName DataType BlockNumber StorageType");
    for(i=0;i<SymCount;i++)
        {
        printf("\n%s\t\t%s\t%d\t%d",Symbol[i],DataTypeTable[DataType[i]].m_szDataTypeName,BlockNumber[i],m_iStorageType[i]);
        
        Temp=GetDimension(i);
        Start=Temp;
        if(Temp==NULL)
            continue;
        while(1)
            {
            printf(" %s",Symbol[Temp->Result]);
            Temp=Temp->next;
            if(Temp==Start)
                break;
            }
        
        }
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
int SearchKWTable(char *ID1)
    {
    int i;
    for(i=0;i<KW_SIZE;i++)
        {
        if(strcmpi(KW_Name[i],ID1)==0)
            {
            
            if((KW_ID[i]==THN_KW))
                {
                
                InitNewBlock();
                }

            if(KW_ID[i]==ELSE_KW)
                {
                TermOldBlock();
                InitNewBlock();
                }
            if((KW_ID[i]==EIF_KW))
                {
                TermOldBlock();
                }
            if((KW_ID[i]==ELSIF_KW))
                {
                TermOldBlock();
                InitNewBlock();
                }
            if((KW_ID[i]==LOOP_KW))
                {
                InitNewBlock();
                }
            if((KW_ID[i]==STRUCT_KW))
                {
                InitNewBlock();
                }

            return KW_ID[i];
            }
        }
    return -1;
    }
 int AddSymbol(char *SYMBOL)
        {
        int i;
        for(i=0;i<SymCount;i++)
            {
            if(strcmp(Symbol[i],SYMBOL)==0)
                {
                if(BlockNumber[i]==Block_Number)
                    return i;
                }
            }
        strcpy(Symbol[SymCount],SYMBOL);
        BlockNumber[SymCount]=Block_Number;
        SymCount++;
        return SymCount-1;
        }
 void SetStorage(int iSymId,int iStorageType)
     {
     m_iStorageType[iSymId]=iStorageType;
     }
 Optab* GenerateTempVariable()
     {
     char no[10];
     char Temp[LEN];
     int sym;
     itoa(TempCount,no,10);
     strcpy(Temp,"T");
     strcat(Temp,no);
     TempCount++;
     sym=AddSymbol(Temp);
     SetStorage(sym,-1);
     return MakeNode(sym);
     }
 char * GetSymbolName(int SYMID)
     {
     char *Sym;
     if(SYMID==-1)
         return "";
     Sym=Symbol[SYMID];
     return Sym;
     }

 void AssignLabel(Optab* Current,Optab * Target)
     {
     char *label; 
     if(strlen(Target->Label)==0)
         {
         label=GenerateTempLabel();
         strcpy(Current->TargetLabel,label);
         strcpy(Target->Label,label);
         }
     else
         {
         strcpy(Current->TargetLabel,Target->Label);
         }
     }
 int ProcessJumpStatement(Optab *current)
     {
     char label[20]; 
     Optab * JumpTarget;
         
     if(current->Operator==GetOperatorId("JLT_JNXT"))
         {
         
         JumpTarget=(current->instr_addr);
         JumpTarget=JumpTarget->next;
         current->Operator=GetOperatorId("JLT");
         AssignLabel(current,JumpTarget);
         return 1;
         }
     else if(current->Operator==GetOperatorId("JMP"))
         {
         JumpTarget=current->instr_addr;
         AssignLabel(current,JumpTarget);
         return 1;
         }
     else if(current->Operator==GetOperatorId("JLT"))
         {
         
         JumpTarget=current->instr_addr;
         AssignLabel(current,JumpTarget);
         return 1;
         }
          else if(current->Operator==GetOperatorId("JMP_JNXT"))
         {   
         JumpTarget=current->instr_addr;
         JumpTarget=JumpTarget->next;
         current->Operator=GetOperatorId("JMP");
         AssignLabel(current,JumpTarget);
         return 1;
         }
     return 0;
     }
 void DisplayFunctionTable()
     {
     int i;
     Optab *Temp,*Start;
     printf("\n-------------Functions---------------\nReturnType FunctionName Paramteres\n");

     for(i=0;i<FunctionTableCount;i++)
         {
         printf("%s\t\t%s\t",GetDataTypeName(FunctionTable[i].ReturnType),FunctionTable[i].Func_Name);
Temp=FunctionTable[i].ParamList;
        Start=Temp;
        if(Temp==NULL)
            continue;
        while(1)
            {
            printf(" %s",Symbol[Temp->Result]);
            Temp=Temp->next;
            if(Temp==Start)
                break;
            }
         }

     }
 void DisplayOptab()
        {
        char Instruction[100];
        Optab * current;
        int IsJump;
        current=prog_start;
        if(current==NULL)
            return;
        while(1)
            {
            Instruction[0]='\0';
            if(current->Operator==GetOperatorId("ASM"))
                {
                printf("%s",current->AsmPointer);
                current=current->next;
            if(current==prog_start)
                break;
                continue;
                }
            IsJump=ProcessJumpStatement(current);
            if(IsJump==1)
                {
                strcat(Instruction,"\t");
                strcat(Instruction,GetOperatorName(current->Operator));
                strcat(Instruction,"\t");
                strcat(Instruction,current->TargetLabel);
                }
            else
                {
                if(strlen(current->Label)!=0)
                    {
                    strcat(Instruction,current->Label);
                    strcat(Instruction,"\t");
                    }
                else
                    {
                    strcat(Instruction,"\t");
                    }
                strcat(Instruction,GetSymbolName(current->Result));
                strcat(Instruction,"\t");
                strcat(Instruction,GetSymbolName(current->Operand1));
                strcat(Instruction,"\t");
                strcat(Instruction,GetOperatorName(current->Operator));
                strcat(Instruction,"\t");
                strcat(Instruction,GetSymbolName(current->Operand2));
                
                }
            printf("%s\n",Instruction);
            current=current->next;
            if(current==prog_start)
                break;
            }
        }

#endif