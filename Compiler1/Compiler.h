
#define DEBUG_ASSEMBLYCOMMENTS 1
#define DEBUG_REGISTER_OPTIMIZATION 2
#define DEBUG_SHOW_OPTAB 4
#define DEBUG_SHOW_SYMTAB 8
#define DEBUG_SHOW_CLASSMEMBERS 16
#define DEBUG (DEBUG_ASSEMBLYCOMMENTS)
#define CHECK_DEBUG_ENABLED(val) (DEBUG/val) &1
#define MaxTableLen 40	
#define ARRAYSIZE 30
#define KW_SIZE 26
#define LEN 30
#define MaxOperators 43
#define MAXSymbols 400
#define OperatorTabLen 44
#define SIZE 40
#define MaxOutputAsmStatement 230
#define MaxOperatorLen 18
#define MAX_OBJECTS 30
#define MAX_LABEL_LEN 40
#define MAX_SYM_LEN 50
#define MAX_ASM_STATEMENT_LENGTH 120
#define MAX_LITERAL_LEN 80
#define MAX_STRUCT_LEN 20 
#define MAX_VARIABLE_LEN 40
#define MAX_FUNCTION_NAME_LEN 40
#define MAX_FUNCTION_LABEL_LEN MAX_FUNCTION_NAME_LEN+30



#include<string.h>
#include "stdio.h"
#include "stdlib.h"
#include "main.h"
#include "SymbolTable.h"
#include "literals.h"
#include "datatypetable.h"
#include "structure.h"
#include "x86Registers.h"
#include "object.h"
#include "worker.h"
#include "ObjCompiler.tab.h"

int iLineNo=-1;
int iHeapSize=1024;
char *LpszOutputFileName=NULL;
struct opasm
    {
    char *szLabel;
    char szAsmStatement[MAX_ASM_STATEMENT_LENGTH];
    }OutputAsm[MaxOutputAsmStatement];
  
  enum CompileOptions
  {
	  eGenesis,
	  eWindows,
	  eUnitTest
  };



struct Operand
    {
    int IsValid,IsRegister,IsImmediate,HasIndex,IsReference,IsMemoryAddress,IsIndirectAddress,IsLiteral,IsLabel;
    int Register,MemoryAddress,SymTabPos,IndexRegister,ImmediateValue,SegmentRegister;
	char szLabel[30];
    };


enum blockType
    {
    Object,
    Function,
    Global
    }BlockType;


int iCompileOption=eWindows;

FILE *fpOutputFile=NULL;
char szCompileOption[3][15]={"Genesis","Windows","UnitTest"};
char sz386OpCode[20][20]={"mov ","add ","sub ","movzx ","movsx ","mul ","imul ","div ","idiv ","push ","cmp ","or ","and "};
enum x86opcode{mov,add,sub,movzx,movsx,mul,imul,Div,idiv,push,cmp,or,and}x86OpCode;
char szCurrentWorker[MAX_CLASS_NAME_LEN];
int TempLitCount=0;
int MaxStackSize=300;
  
  int iStructTableCount=0;
int LabelCount=0;

int iOutputAsmCount=0;
Optab *prog_start=NULL,*Func_Start,*current,*previous=NULL,*block_start=NULL,*ID_Node_Current=NULL,*ID_Node_Start=NULL,*ID_Node_Previous=NULL,*Last_Statement_Block;
    int nOperation;
    char OperatorTab[OperatorTabLen][MaxOperatorLen]={{"+"},{"-"},{"*"},{"/"},{"="},{"||"},{"&&"},{"^"},{"<="},{">="},{"=="},{"!="},{"<"},{">"},{"JNE_JNXT"},{"JMP"},{"JMP_JNXT"},{"BRK_LOOP"},{"PUSH_FUN_PAR"},{"CALL"},{"CONT_LOOP"},{"ASM"},{"DEREFERENCE"},{"JG"},{"JL"},{"JA"},{"JB"},{"JGE"},{"JAE"},{"JBE"},{"JLE"},{"JE"},{"JNE"},{"cast"},{"comp"},{"ClearRegs"},{"%LockRegister"},{"%UnLockRegister"},{"Return"},{"%"},{"SetEBX"},{"UnSetEBX"},{"Lit2Ptr"}};


struct Func_Table
    {
    int ReturnType;
    char Func_Name[32];
    struct Optab* ParamList,*m_LpStatementBlock;
    }FunctionTable[20];


struct FuncDetails
    {
    int iReturnDataType;
    char FunctionName[MAX_FUNCTION_NAME_LEN];
	char szClassName[MAX_CLASS_NAME_LEN];
	char szFunctionLabel[MAX_FUNCTION_LABEL_LEN];
    int AddressStart,AddressEnd;
	int iType;
    }FunctionDetails;







char KW_Name[KW_SIZE][LEN]={{"If"},{"EndIf"},{"Then"},{"Else"},{"Elseif"},{"WHILE"},{"LOOP"},{"EndLoop"},{"Function"},{"Returns"},{"return"},{"Break"},{"Continue"},{"Datatype"},{"Define"},{"ObjectType"},{"EndDefine"},{"Mod"},{"Task"},{"Worker"},{"Import"},{"Interrupt"},{"new"},{"IN"},{"Operation"},{"Operator"}};
int KW_ID[KW_SIZE]={IF_KW,EIF_KW,THN_KW,ELSE_KW,{ELSIF_KW},{WHILE_KW},{LOOP_KW},{ENDLOOP_KW},{FUNCTION_KW},{RETURNS_KW},{RETURN_KW},{BREAK_LOOP_KW},{CONTINUE_LOOP_KW},{DATATYPE_KW},{DEFINE_KW},{OBJECTTYPE_KW},{END_DEFINE_KW},{MODULUS_OP},{TASK_KW},{WORKER_KW},{IMPORT_KW},{INTERRUPT_KW},{NEW_KW},{IN_KW},{OPERATION_KW},{OPERATOR_KW}};
    int TempCount=0;

    
	FILE **Lpyyin;
int FunctionTableCount=0;

void LockRegister(int RegisterId);
int IsValidSymbol(int iSymTab);
void WriteToFile(char *LpszFileName);
int GetSymbolRegister(int iSymId);
void UnLockRegister(int RegisterId);
int IsConst(int SymId);
void initDataTypeTable();
void  setDataTypeSize(int DataType,int Size);
int IsSigned(int SymTabPos);
int CompareSize(int Operand1SymTabPos,int Operand2SymTabPos);
int GetExtendedRegister(int SourceRegister,int Size);    
int GetDataTypeId(char * LpszDataType);
int VariableIsStruct(Optab * Current);
int DataTypeIsStruct(int iDataType);
int GetPointerTarget(int iSymId);
//struct OMProperty *GetOMProperty(char *LpszClassName,char *LpszPropertyName);
int GetSymbolId(char *LpszSymName);

int SetCurrentClassName(int iSymId);

    int IsLiteral(int SymId);
    int IsPrimitive(int SymTabPos);
	void AddPropertyToCurrentClass(char *LpszPropertyName,int iDataType);
	void AddPropertyToWorker(char *LpszPropertyName,int iDataType);
void AddDataType(char * LpszDataTypeName,int iDataTypeSize,Optab *LpDataMembers,Optab *Functions);
//int AddFunctionTable(int RtrnType,char *FuncName,Optab * Parameters);
Optab* AddAsm(char *ASM);
int GetStructIndex(char *LpszStructName);
int SearchFunctionTable(char *FuncName);
int GetDataType(int SymTabPos);
void SetDataType(int SymTabPos,int Datatype);
struct ArrayDimension * GetDimension(int SymTabPos);
int GetDataTypeSize(int Pos);
int CalculateDataTypeSize(Optab *LpMembers);
void SetDimension(int SymTabPos,Optab * DimenSion);
Optab* MakeFunctionCallNoParam(int FunctionID);
int GetSymTabPos(char *LpszIdentifier);
char * GetDataTypeName(int DatatypeId);
int CalculateMemberOffset(char *LpszParent,char *LpszMember);
Optab* ProcessMemberCall(char *LpszIdentifier);
void MakeReturnsStatement(int iDataType);
int IsMemberCall(char *LpszIdentifier);

void DisplaySymTab();
int SearchDataTypeTable(char *Datatype);
struct ClassDefinition * GetClassInformation(char *LpszClassName);
void SetPointerTarget(int SymId,int DataTypeTabLoc);
int SearchKWTable(char *ID1);
int AddSymbol(char *SYMBOL);
void SetStorage(int iSymId,int iStorageType);
Optab* GenerateTempVariable();
Optab* MakeOperationDeclaration(int RtrnDataType,int FunctionNameSymTabPos,Optab * ParamList,Optab *StatementBlock);
//char * GetSymbolName(int SYMID);
void AssignLabel(Optab* Current,Optab * Target);
int ProcessJumpStatement(Optab *current,struct FunctionDetails functiondetails);
void DisplayFunctionTable();
void DisplayOptab();
int IsStruct(int SymId);
void ParseFile(char *LpszFileLocation);
int GetOperatorId(char OPERATOR[LEN]);
struct OMFunction * AddFunctionTable(int RtrnType,char *FuncName,Optab * Parameters,Optab *StatementBlock);
void AddDataType(char * LpszDataTypeName,int iDataTypeSize,Optab *LpDataMembers,Optab *Functions);
char * GenerateTempLabel();
Optab *MakeStructDeclaration(int iStructNameID,Optab *Members);
Optab *MakeForwardDeclaration(int iSymId);
Optab * MakeNode(int data);
void InitNewBlock();
void TermOldBlock();
Optab* MakeDeclareIDSubscript(Optab* Identifier,Optab* Subscript);
int IsPointer(Optab * LpCurrent);
int IsPointer(Optab * LpCurrent);
Optab* MakeDeclareStatement(int Datatype,Optab* ID_List);
Optab* MakeFunctionDeclaration(int RtrnDataType,int FunctionNameSymTabPos,Optab * ParamList,struct Optab *StatementBlock);
Optab * MakeSimpleNode();
Optab * DeleteNode(struct Optab * Node);
void BackPatch(Optab * Current,Optab* PatchAddr);
void BackPatchWhileLoop(Optab * Current,Optab* BreakPatchAddr,Optab * ContinuePatchAddress);
Optab * ConcatSubscriptNode(Optab *Node1,Optab * Node2);
Optab * ConcatNode(Optab *Node1,Optab * Node2);
struct OMProperty * AddPropertyToClass(char * LpszClassName,Optab *LpDataBlock);
int GetLowerRegister(int RegisterId);
int GetResult(Optab* BlockStart);
void SetTempVariableInfo(Optab * LpTempVariable,Optab * LpOperand1,Optab * LpOperand2);
Optab * AddOperation(Optab * RESULT,int OPERATOR,Optab * OPERAND1,Optab * OPERAND2);
Optab *GetLastNodeAddr(Optab *Block_Start);
Optab* MakeElseIf(Optab *Condition ,Optab *Statement);
Optab* MakeElseIfElse(Optab *Condition ,Optab *ElseIfStatement,Optab *ElseStatement);
Optab* MakeIfElseIf(Optab *Condition,Optab *Statement,Optab *IfElseIfStatement);
Optab* MakeElseIfElseIf(Optab *Condition,Optab *IfStatement,Optab* ElseIfStatement);
Optab* MakeAssignment(Optab* LHS ,Optab * RHS);
Optab * MakeWhile(Optab *Condition ,Optab *Statement);
Optab * MakeIfThen(Optab *Condition ,Optab *Statement);
Optab* MakeStatementBlock(Optab * Statement1,Optab * Statement2);
Optab* MakeIfThenElse(Optab* Condition,Optab* TrueStatement,Optab * FalseStatement);
char * Getx86RegisterName(int RegisterId);
int GetOperatorId(char OPERATOR[LEN]);
Optab * MakeSingleExprSubscript(int Identifier,Optab * CurrentSubscriptExpr);
struct ArrayDimension * GetCurrentDimension(int Identifier,int count);
Optab * MakeExprSubscript(Optab * PreviousSubscriptExpr,Optab * CurrentSubscriptExpr);
Optab* MakeFunctionCallSingleParam(int FunctionID,Optab* Parameter);
Optab* MakeFunctionCallAddParam(Optab *FirstExpression, Optab * SecondExpression);
Optab * MakeFunctionCallAddFirstParam(Optab *FirstParam);
Optab * MakeFunctionCallMultipleParam(int FunctionID,Optab * Parameters,Optab *LastParameter);
Optab *MakeReturnStatement(Optab *LpExprId);
char * GetOperatorName(int OPERATORID);
Optab *MakeObjectDefinition(int iIdentifier,Optab * DataBlock,Optab *FunctionBlock);
void DeleteSymbol(int Index);
int GetDatatype(char *LpszVariable);
void Generatex86Instruction(int Opcode,int Operand1,int Operand1_Index,int Operand2,int Operand2_Index,char *LpszInstructionBuf);
void Generate_x86ASM_Function(Optab *Function_Start);
int GetStorage(int Index);

void AssignAddressObjectMember();
void initOutputFile(char *LpszFileLocation);
void closeOutputFile();
int IsRegisterLocked(int iRegId);
int IsLiteral(int SymId)
    {
    if((GetDataType(SymId)==GetDataTypeId("_int_ltrl_8"))||(GetDataType(SymId)==GetDataTypeId("_int_ltrl_16"))||(GetDataType(SymId)==GetDataTypeId("_int_ltrl_32"))||((GetDataType(SymId)==GetDataTypeId("int_imm"))))
        return 1;
    return 0; //return 2 for string literal
    }
 
 
 


void initOutputFile(char *LpszFileLocation)
{
	fpOutputFile=fopen(LpszFileLocation,"w");
	LpszOutputFileName=LpszFileLocation;
	if(fpOutputFile==NULL)
	{
		printf("Error Opening %s in Write mode",LpszFileLocation);
		exit(-1);
	}
	else
	{
		if(iCompileOption==eWindows)
	  {
		  fprintf(fpOutputFile,"global _main\n extern _printf \nsegment .text\n_main:push EBP \nmov EBP,Data\n add EBP,%d\n",MaxStackSize*2);
		  fprintf(fpOutputFile,"mov  EBX,ObjectData\n");
		  fprintf(fpOutputFile,"push EBX \nmov dword EBX,heap\npush EBP\nmov EBP,ESP \nsub EBP,0x4 \ncall heapobj_init \npop EBP\npop EBX\n");
		//fprintf(fpOutputFile,"push EBX\nmov EBX,heap\nadd EDI,0x1\n push EBP\nmov EBP,ESP\nsub EBP,0x4\ncall heapobj_init\npop EBP\npop EBX\n");	  
		fprintf(fpOutputFile,"call ");
		if(strcmp(szCurrentWorker,"")==0)
			fprintf(fpOutputFile,"__main\n");
		else
		{
			fprintf(fpOutputFile,szCurrentWorker);
			fprintf(fpOutputFile,"_main\n");
		}
		fprintf(fpOutputFile,"pop EBP\nret\n");
	  }
	  else if(iCompileOption==eUnitTest)
	  {
		  //fprintf(fpOutputFile,"push EBX\nmov EBX,heap\nadd EDI,0x1\n push EBP\nmov EBP,ESP\nsub EBP,0x4\ncall heapobj_init\npop EBP\npop EBX\n");	  
		  fprintf(fpOutputFile,"extern ExitProcess\nextern OpenFile\nextern WriteFile\nextern CloseHandle\nimport ExitProcess kernel32.dll\nimport OpenFile kernel32.dll\nimport WriteFile kernel32.dll\nimport CloseHandle kernel32.dll ");
fprintf(fpOutputFile,"\nsection .text use32\n..start:\n mov dword [ESPOrg],ESP\nmov EBP,ESP\nsub EBP,0x4\ncall Obj1_start\npush eax\ncall [ExitProcess]\n");
fprintf(fpOutputFile,"fprint_int_win:\n mov dword [EBPSave],EBP\n mov dword [ESPSave],ESP\nmov dword ESP,[ESPOrg]\nenter 148, 0 \nmov CX,1000\nmov EDI,hexstr\nconv_loop:\ncwd\nidiv cx\nadd al,0x30\nmov byte[edi],al\ninc edi\nskip_label:\nmov ax,cx\nidiv byte [divid]\ncmp al,0\n");
fprintf(fpOutputFile,"jz returnhex\ncbw\nmov cx,ax\nmov ax,dx\njmp conv_loop\nreturnhex:\nlea ebx, [ebp-148]\npush dword 1 | 0x1000\npush ebx\npush dword filename\ncall [OpenFile]\nmov dword [ebp-4], eax");
fprintf(fpOutputFile,"\nlea ebx, [ebp-8]\npush dword 0\npush ebx\nmov EAX,EDI\nsub EAX,hexstr\npush dword EAX\npush dword hexstr\npush dword [ebp-4]\ncall [WriteFile]\npush dword [ebp-4]\ncall [CloseHandle]\nmov dword EBP,[EBPSave]\nmov dword ESP,[ESPSave]\nret\n	");
	  }
	  else
	  {
		  fprintf(fpOutputFile,"[BITS 16]\n[ORG 0x7C00]\n");
		  fprintf(fpOutputFile,"xor ax, ax\nmov ds, ax\nmov ss, ax \nmov es,ax\n");
		  fprintf(fpOutputFile,"mov ah,02h\nmov al,21; no of sectors\nmov ch,0\nmov cl,2\nmov dh,0\nmov dl,0\nmov bx,heapobj_init\nint 13h\n");
		  fprintf(fpOutputFile,"mov EBP,Data\nadd EBP,%d\nmov ESP,EBP\nmov  EBX,ObjectData\n",MaxStackSize*2);
		  fprintf(fpOutputFile,"push EBX \nmov dword EBX,heap\npush EBP\nmov EBP,ESP \nsub EBP,0x4 \ncall heapobj_init \npop EBP\npop EBX\n");	  
		  fprintf(fpOutputFile,"call __main\n hang:jmp hang\n");
		  fprintf(fpOutputFile,"times 510-($-$$) db 0\ndb 0x55 \ndb 0xAA\n");
	  }
	}
}
void closeOutputFile()
{
    char szFileName[80];
	int i;
	if(fpOutputFile!=NULL)
	{
		if(iCompileOption==eWindows)
		fprintf(fpOutputFile,"segment .data\n");
		for(i=0;i<MAXSymbols;i++)
	  {
		  if(GetScope(i)==GlobalScope)
		  {
			  fprintf(fpOutputFile,"%s resb %d\n",GetSymbolName(i),GetDatatypeSize(i));
		  }

	  }
		if(iCompileOption==eWindows)
            fprintf(fpOutputFile,"heapspace resb %d \nObjectData resb 100\nData resb %d\nhex_format db 'Value=%%x\',13,10,0 \nint_format db 'Value=%%d\',13,10,0\nstring_format  db \'String Value=%%s',13,10,0 \n uint_format db \'Value=%%d\',13,10,0",iHeapSize,MaxStackSize*2);
	  else if(iCompileOption==eUnitTest)
	  {
          char *LpszFileName;
         LpszFileName=strrchr(LpszOutputFileName,'\\' );
         LpszFileName++;
         
         
         strcpy(szFileName,LpszFileName);
         szFileName[strlen(LpszFileName)-3]='\0';
         strcat(szFileName,"out");
		  fprintf(fpOutputFile,"section .data\n Data resb 260\nfilename db \'");
              fprintf(fpOutputFile,"%s",szFileName);
          fprintf(fpOutputFile,"\',0\n hexstr resb 10\nESPSave resb 4\nESPOrg resb 4\nEBPSave resb 4\ndivid db 10\n");
	  }
	  else
	  {
		 // fprintf(fpOutputFile,"Data resb 100\ntimes 510-($-$$) db 0\ndb 0x55\ndb 0xAA\nISR resb 100\n ObjectData resb 300\ntimes 1024-($-$$) db 0");
		   fprintf(fpOutputFile,"Data resb %d\nheapspace resb %d \nISR resb 180\nObjectData resb 300\ntimes 368640-($-$$) db 0",MaxStackSize*2,iHeapSize);
	  }
	  fprintf(fpOutputFile,"\n");
	  
		fclose(fpOutputFile);
	}
	else
		printf("Error cannot close output file.. NULL");

}

void ProcessPreDefs()
{

}
Optab *MakeForwardDeclaration(int iSymId)
{
	
	AddDataType(GetSymbolName(iSymId),-1,-1,-1);
	DeleteSymbol(iSymId);
	return NULL;
}
Optab* MakeSimpleDataNode(int Result,int Operator,int Operand1,int Operand2)
      {
      current=(Optab *)malloc(sizeof(struct optab));
      current->instr_addr=NULL;
      current->Result=Result;
      current->Operator=Operator;
      current->Operand1=Operand1;
      current->Operand2=Operand2;
      current->Label[0]='\0';
      strcpy(current->Result_c,GetSymbolName(Result));
      strcpy(current->Operand1_c,GetSymbolName(Operand1));
      strcpy(current->Operand2_c,GetSymbolName(Operand2));
      strcpy(current->Operator_c,GetOperatorName(Operator));
      current->TargetLabel[0]='\0';
      current->AsmPointer=NULL;
      current->subscript=NULL;
      current->SubscriptIndex=-1;
      current->ArrayIndex=-1;
      current->next=current;
      current->previous=current;
      return current;
      }
Optab *MakeReturnStatement(Optab *LpExprId)
{
	Optab *ReturnNode;
	ReturnNode=MakeNode(-1);
	ReturnNode->Operator=GetOperatorId("return");
	if(LpExprId!=NULL)
	ReturnNode->Operand1=GetResult(LpExprId);
	else
		ReturnNode->Operand1=-1;

	strcpy(ReturnNode->Operator_c,"return");
	if(LpExprId!=NULL)
	strcpy(ReturnNode->Operand1_c,GetSymbolName(ReturnNode->Operand1));
	return ConcatNode(LpExprId,ReturnNode);
}
Optab * MakeGlobalVariable(Optab *LpDeclareBlock)
{
    
    Optab *LpCurrent,*LpStart;
    LpStart=LpDeclareBlock;
    LpCurrent=LpStart;
    while(1)
    {
        SetSymbolScope(LpCurrent->Result,GlobalScope);
        LpCurrent=LpCurrent->next;
        if(LpCurrent==LpStart)
            break;
    }

}
Optab *MakeNewStatment(Optab *LpClassName)
{
int j;
j=5; 
}
Optab *MakeStringLiteral(int SymId)
{
    Optab *Lit2PtrNode,*NILOperand,*StrTempVar,*LitNode,*PtrTempVar,*SetStringParam1;
    Optab * SetStringParam2,*SetStringFunctionCall;
    char szFunctionName[MAX_VARIABLE_LEN+20],szLenBuffer[10];
    int symId,litSymId,bSwitchFuncStart;
	bSwitchFuncStart=0;
	if(Func_Start==NULL)
		bSwitchFuncStart=1;

    StrTempVar = GenerateTempVariable();
    SetDataType(StrTempVar->Result,GetDataTypeId("String"));
    NILOperand=MakeSimpleNode();
    LitNode=MakeNode(SymId);
    
    PtrTempVar=GenerateTempVariable();
    SetDataType(PtrTempVar->Result,GetDataTypeId("Pointer"));
    Lit2PtrNode=AddOperation(PtrTempVar,GetOperatorId("Lit2Ptr"),LitNode,NILOperand);
    SetStringParam1=MakeFunctionCallAddFirstParam(Lit2PtrNode);
    itoa(strlen(GetLiteralValue(SymId,0)),szLenBuffer,10);
    litSymId=AddLiteral(szLenBuffer,0);
    SetStringParam2=MakeNode(litSymId);
    strcpy(szFunctionName,GetSymbolName(StrTempVar->Result));
    strcat(szFunctionName,".SetString");
    symId=AddSymbol(szFunctionName);
    SetStringFunctionCall=MakeFunctionCallMultipleParam(symId,SetStringParam1,SetStringParam2);
    //PtrTempVar=SetStringFunctionCall->previous->previous; //setting Temp variable as a result in the last Node
	//PtrTempVar->Result=StrTempVar->Result; //because only then the next statement will take this temp variable as result else it will take ""
	PtrTempVar=MakeNode(StrTempVar->Result);
	PtrTempVar->Operator=GetOperatorId("DEREFERENCE");
	SetStringFunctionCall=ConcatNode(SetStringFunctionCall,PtrTempVar);
	if(bSwitchFuncStart==1)
		Func_Start=SetStringFunctionCall;

    return SetStringFunctionCall;
    
}

Optab* GenerateCompilerRequest(char *LpszParam)
    {
   Optab *LpCurrent;
    char szRequest[20];
    int iOperatorId,iEnd,iCount;
    iCount=0;
    while(*LpszParam!='(')
        {
        szRequest[iCount++]=*LpszParam;
        LpszParam++;
        }
    szRequest[iCount]='\0';
    LpCurrent=MakeSimpleNode();
    iOperatorId=GetOperatorId(szRequest);

    LpszParam[strlen(LpszParam)-2]='\0';
    LpszParam++;
    if(iOperatorId==GetOperatorId("%LockRegister"))
        {
        LpCurrent->Operator=GetOperatorId("%LockRegister");
        LpCurrent->Operand1=GetRegisterID(LpszParam);
        }
    if(iOperatorId==GetOperatorId("%UnLockRegister"))
        {
        LpCurrent->Operator=GetOperatorId("%UnLockRegister");
        LpCurrent->Operand1=GetRegisterID(LpszParam);
        }

        return LpCurrent;
    }
    


char *GetImmediateValue(int Value,int Size)
    {
     int i=0;
    char szTemp[MAX_SYM_LEN];
    szTemp[0]='\0';
    itoa(Value,szTemp,16);
    if(Value>=0)
        return szTemp;
    else
        {
        int iLen;
        iLen=strlen(szTemp);
        if(Size==byte)
            {
            if(iLen>2)
                {
                return szTemp+iLen-2;
                }
            else
                return szTemp;
            }
        if(Size==word)
            {
            if(iLen>4)
                {
                return szTemp+iLen-4;
                }
            else
                return szTemp;
            }
        if(Size==dword)
            {
            if(iLen>2)
                {
                return szTemp+iLen-8;
                }
            else
                return szTemp;
            }
        }
    /*if((format==GetDataTypeId("uint8"))||(format==GetDataTypeId("uint16")||(format==GetDataTypeId("uint32"))||(format==GetDataTypeId("void"))))
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
    */
    }
void AssignAddressObjectMember()
    {
    int index=0,Address=0;

    while(index!=SymCount)
        {
        if(SymTab[index].m_StorageType!=NONEStorage)// Local storage has to be changed to local scope. else struct members wont disappear from symtab
            {
            if(SymTab[index].m_StorageType==PointerStorage)
                {
                SymTab[index].SymbolAddress=Address;
                Address=Address+4;
                }
            else
                {
                SymTab[index].SymbolAddress=Address;
                Address=Address+GetDatatypeSize(index);
                }
            }
        index++;
        }

    }



	
	void AddPropertyToWorker(char *LpszPropertyName,int iDataType,struct ArrayDimension *LpDimension)
	{
		struct OMProperty *LpPropertyList,*LpPropCurrent;
	  int iDataTypeSize,DataType;
	  LpPropertyList=LpCurrentClass->m_LpMemberVar;
	  LpPropCurrent=(struct OMProperty*)malloc(sizeof(struct OMProperty));
	  LpPropCurrent->m_LpNext=NULL;
	  if(LpDimension==NULL)
	  LpPropCurrent->m_LpDimension=NULL;
	  else
		  LpPropCurrent->m_LpDimension=LpDimension;
	  strcpy(LpPropCurrent->m_szPropertyName,LpszPropertyName);
	  LpPropCurrent->m_iDataType=iDataType;
	  
	  if(LpPropertyList!=NULL)
	  {
		  while(1)
		  {
			if(strcmp(LpPropertyList->m_szPropertyName,LpszPropertyName)==0)
			{
			  ErrorHandler(ERROR,"Duplicate Property");
			}	
			if(LpPropertyList->m_LpNext!=NULL)
				LpPropertyList=LpPropertyList->m_LpNext;
			else
				break;
		  }
		  LpPropertyList->m_LpNext=LpPropCurrent;
		  
	  }
	  else
	  {
		  LpCurrentClass->m_LpMemberVar=LpPropCurrent;
		 
	  }
	  //iDataTypeSize=LpPropCurrent->m_iOffsetAddress+GetDataTypeSize(LpPropCurrent->m_iDataType);
	  DataType=GetDataTypeId(szCurrentClass);
	  iDataTypeSize=GetDataTypeSize(DataType)+GetDataTypeSize(LpPropCurrent->m_iDataType);
	  setDataTypeSize(DataType,iDataTypeSize);
	}
struct OMFunction * AddFunctionTable(int RtrnType,char *FuncName,Optab * Parameters,Optab *StatementBlock)
    {
	struct OMFunction * LpCurrentFunction;
	struct SDataTypeList *LpFPStart;
	struct SDataTypeList *LpFPCurrent,*LpFPPrevious;
	int iDataType;
	struct Optab* ParamStart;
	LpCurrentFunction=malloc(sizeof(struct OMFunction));
	LpCurrentFunction->m_LpNext=NULL;
	LpCurrentFunction->iReturnType=RtrnType;
	strcpy(LpCurrentFunction->m_szFunctionName,FuncName);
	strcpy(LpCurrentFunction->m_szFunctionLabel,szCurrentClass);
	strcat(LpCurrentFunction->m_szFunctionLabel,"_");
	strcat(LpCurrentFunction->m_szFunctionLabel,FuncName);
	LpFPPrevious=NULL;
	LpFPStart=NULL;

	//struct optab ParamStart;
	if(Parameters!=NULL)
	{
		ParamStart=Parameters;
	do
	{		
	LpFPCurrent=malloc(sizeof(struct SDataTypeList));
	LpFPCurrent->m_LpNext=NULL;
	iDataType=GetDataType(Parameters->Result);
	LpFPCurrent->m_iDataType=iDataType;
	if(LpFPStart==NULL)
		{
		LpFPStart=LpFPCurrent;
		}
	else
	LpFPPrevious->m_LpNext=LpFPCurrent;
	LpFPPrevious=LpFPCurrent;
	Parameters=Parameters->next;
	}while((Parameters!=ParamStart));
	LpCurrentFunction->m_LpFormalParameter=LpFPStart;
	}
	else
	{
		LpCurrentFunction->m_LpFormalParameter=NULL;
	}
	
	AddFunctionToClass(szCurrentClass,LpCurrentFunction);
    //FunctionTable[FunctionTableCount].ReturnType=RtrnType;
    //strcpy(FunctionTable[FunctionTableCount].Func_Name,FuncName);
    //FunctionTable[FunctionTableCount].ParamList=Parameters;
    //FunctionTable[FunctionTableCount].m_LpStatementBlock=StatementBlock;
    //FunctionTableCount++;
    return LpCurrentFunction;
    }



	
	/*
	Following function compares the datatype of literal with a datatype to see if they are compatable
	it checks whether  the literal can be passed to that dataType
	*/
	int CheckLiteralCompatability(int LiteralSymTabPos,int iDataType)
	{
	char *LpszLiteralDataType;
		LpszLiteralDataType=GetDataTypeName(GetDataType(LiteralSymTabPos));
		if(strcmp(LpszLiteralDataType,"_int_ltrl_8")==0)
		{
		if(iDataType==GetDataTypeId("int8"))
		return TRUE;
		if(iDataType==GetDataTypeId("int16"))
		return TRUE;
		if(iDataType==GetDataTypeId("int32"))
		return TRUE;
		}
		else if(strcmp(LpszLiteralDataType,"_int_ltrl_16")==0)
		{
		if(iDataType==GetDataTypeId("int16"))
		return TRUE;
		if(iDataType==GetDataTypeId("int32"))
		return TRUE;
		}
		else if(strcmp(LpszLiteralDataType,"_int_ltrl_32")==0)
		{
		if(iDataType==GetDataTypeId("int32"))
		return TRUE;
		}
		return FALSE;
	
	}
void initDataTypeTable()
    {
    int i=0;
    for(i=0;i<LEN;i++)
        {
        SymTab[i].NodePtr=NULL;
        }
    //BlockType=Global;
    CurrentScope=GlobalScope;
    AddDataType("void",0,NULL,NULL);
    AddDataType("int8",1,NULL,NULL);
	AddDataType("uint8",1,NULL,NULL);
    AddDataType("int_imm",4,NULL,NULL);
    AddDataType("_int_ltrl_8",1,NULL,NULL); //integer literal
    AddDataType("_int_ltrl_16",2,NULL,NULL);
    AddDataType("_int_ltrl_32",4,NULL,NULL);
    AddDataType("_string_ltrl",1,NULL,NULL);
    //AddDataType("uint8",1,NULL,NULL);																																																																										Q	1,NULL,NULL);
    AddDataType("int16",2,NULL,NULL);
    AddDataType("uint16",2,NULL,NULL);
    AddDataType("int32",4,NULL,NULL);
    AddDataType("uint32",4,NULL,NULL);
    AddDataType("int64",8,NULL,NULL);
    AddDataType("uint8",1,NULL,NULL);
    AddDataType("char",2,NULL,NULL);
    AddDataType("AddressOf",4,NULL,NULL);
    AddDataType("Pointer",4,NULL,NULL);
    
    }

  

Optab* AddAsm(char *ASM)
    {
    Optab * AsmNode;
    char *LpszASM;
	AsmNode=MakeNode(-1);
	LpszASM=AddNewString(ASM);
    LpszASM[strlen(LpszASM)-1]='\0';
    LpszASM=LpszASM+5;
    AsmNode->AsmPointer=LpszASM;
    AsmNode->Operator=GetOperatorId("ASM");
    return AsmNode;
    }
 


void SetTempVariableInfo(Optab * LpTempVariable,Optab * LpOperand1,Optab * LpOperand2)
    {
    char szTempSym[MAX_SYM_LEN];
    int TempVariable,Operand1,Operand2;
    Optab *LastNode;
    int OrginalSymbol,iCompare;
    TempVariable=LpTempVariable->Result;
    if(LpOperand1!=NULL)
    Operand1=GetLastNodeAddr(LpOperand1)->Result;
    else 
        Operand1=-1;
    if(LpOperand2!=NULL)
    Operand2=GetLastNodeAddr(LpOperand2)->Result;
    else
        Operand2=-1;
    
    if((GetDataType(Operand1)==GetDataTypeId("AddressOf"))||(GetDataType(Operand2)==GetDataTypeId("AddressOf")))
        {
        SetDataType(TempVariable,GetDataTypeId("Pointer"));
        }
    
    else if((IsReference(Operand1)||IsReference(Operand2)))
        {
        iCompare=CompareSize(Operand1,Operand2);
        if(iCompare==0)
            {
            if(IsReference(Operand1))
                {
                strcpy(szTempSym,GetSymbolName(Operand1));
                SetDataType(TempVariable,SymTab[GetSymbolId(szTempSym)].PointerTarget);
                }
            else
                {
                strcpy(szTempSym,GetSymbolName(Operand2));
                SetDataType(TempVariable,SymTab[GetSymbolId(szTempSym)].PointerTarget);
                }
            }
        else
            {
            if(IsReference(iCompare))
                {
                strcpy(szTempSym,GetSymbolName(iCompare));
                SetDataType(TempVariable,SymTab[GetSymbolId(szTempSym)].PointerTarget);
                }
            else
                SetDataType(TempVariable,SymTab[iCompare].DataType);
                
            }
        }
    else if((GetDataType(Operand1)==GetDataTypeId("Pointer"))||(GetDataType(Operand2)==GetDataTypeId("Pointer")))
        {
        SetDataType(TempVariable,GetDataTypeId("Pointer"));
        }
    else if((GetDataType(Operand1)==GetDataTypeId("_int_ltrl_8"))||(GetDataType(Operand1)==GetDataTypeId("_int_ltrl_16"))||(GetDataType(Operand1)==GetDataTypeId("_int_ltrl_32")))
        {
        if((GetDataType(Operand2)==GetDataTypeId("_int_ltrl_8"))||(GetDataType(Operand2)==GetDataTypeId("_int_ltrl_16"))||(GetDataType(Operand2)==GetDataTypeId("_int_ltrl_32"))||(GetDataType(Operand2)==GetDataTypeId("void")))
            {
            if((GetDataType(Operand1)==GetDataTypeId("_int_ltrl_8")))
                SetDataType(TempVariable,GetDataTypeId("int8"));
            else if((GetDataType(Operand1)==GetDataTypeId("_int_ltrl_16")))
                SetDataType(TempVariable,GetDataTypeId("int16"));
            else if((GetDataType(Operand1)==GetDataTypeId("_int_ltrl_32")))
                SetDataType(TempVariable,GetDataTypeId("int32"));

            }
        else
        SetDataType(TempVariable,GetDataType(Operand2));
        }
    else
        {
        iCompare=CompareSize(Operand1,Operand2);
        if(iCompare==0)
            {
            SetDataType(TempVariable,SymTab[Operand1].DataType);
            }
        else
            {
            if(IsReference(iCompare))
                SetDataType(TempVariable,SymTab[iCompare].PointerTarget);
            else
                {
                SetDataType(TempVariable,SymTab[iCompare].DataType);
                }
            
            }
        }


    
    
   
   // SetDataType(TempVariable,GetDataType(Operand1));
    //SetStorage(TempVariable,TempStorage);
   
    }


int CompareSize(int Operand1SymTabPos,int Operand2SymTabPos) //returns Positive value if bot operand is of same size else returns a negative indicating the biggest Size
    {
    int Operand1Size,Operand2Size;
    char szTempSym[MAX_SYM_LEN];
    if(Operand1SymTabPos==-1)
        return 0;
    if(Operand2SymTabPos==-1)
        return 0;
    Operand1Size=GetDataTypeSize(GetDataType(Operand1SymTabPos));
    Operand2Size=GetDataTypeSize(GetDataType(Operand2SymTabPos));
    
    if(IsReference(Operand1SymTabPos))
        {
        strcpy(szTempSym,GetSymbolName(Operand1SymTabPos));
        Operand1Size=GetDataTypeSize(SymTab[GetSymbolId(szTempSym)].PointerTarget);
        }
    if(IsReference(Operand2SymTabPos))
        {
        strcpy(szTempSym,GetSymbolName(Operand2SymTabPos));
        Operand2Size=GetDataTypeSize(SymTab[GetSymbolId(szTempSym)].PointerTarget);
        }
    if(IsLiteral(Operand1SymTabPos))
        {
        int iLiteralValue;
        char szTemp[20];
        strcpy(szTemp,GetLiteralValue(Operand1SymTabPos,0));
        iLiteralValue=atoi(szTemp);
        if(IsSigned(Operand2SymTabPos))
            {
            if((iLiteralValue>-128)&&(iLiteralValue<127))
                Operand1Size=1;
            else if((iLiteralValue>-32768)&&(iLiteralValue<32767))
                Operand1Size=2;
            else if((iLiteralValue<-32768)||(iLiteralValue>32767))
                Operand1Size=4;
            }
        else
            {
            if(iLiteralValue<255)
                Operand1Size=1;
            else if(iLiteralValue<65536)
                Operand1Size=2;
            else Operand1Size=4;

            
            }
        }
    if(IsLiteral(Operand2SymTabPos))
        {
        int iLiteralValue;
        char szTemp[20];
        strcpy(szTemp,GetLiteralValue(Operand2SymTabPos,0));
        iLiteralValue=atoi(szTemp);
        if(IsSigned(Operand1SymTabPos))
            {
            if((iLiteralValue>-128)&&(iLiteralValue<127))
                Operand2Size=1;
            else if((iLiteralValue>-32768)&&(iLiteralValue<32767))
                Operand2Size=2;
            else if((iLiteralValue<-32768)||(iLiteralValue>32767))
                Operand2Size=4;
            }
        else
            {
            if(iLiteralValue<255)
                Operand2Size=1;
            else if(iLiteralValue<65536)
                Operand2Size=2;
            else Operand2Size=4;

            
            }
        }
    
    if(Operand1Size==Operand2Size)
        {
        return 0;
        }
    else if(Operand1Size>Operand2Size)
        {
        return Operand1SymTabPos;
        }
    else 
        return Operand2SymTabPos;
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



int CalculateMemberOffset(char *LpszParent,char *LpszMember)
    {
    int iDataType,iSize,iSymId;
    Optab * LpMember;
	struct StructDecMember *LpMemCurrent;
	int i,found;
    iSize=0;
	found=0;
	i=GetStructIndex(LpszParent);
	if(i!=-1)
	{
		LpMemCurrent=StructTable[i].m_LpStart;
		found=0;
		while(LpMemCurrent!=NULL)
		{
			if(strcmp(LpMemCurrent->m_szSymbolName,LpszMember)==0)
			{
				found=1;
				break;
			}
			iSize=iSize+GetDataTypeSize(LpMemCurrent->m_iDataType);
			LpMemCurrent=LpMemCurrent->m_LpNext;
		}
		if(found==1)
		{
			
			return iSize;
		}
		else
		{
			ErrorHandler(ERROR,"Struct Member Not Found");
		}
	}
	else
	{
		ErrorHandler(ERROR,"Struct Not Found");
	}
    /*iSymId=GetSymTabPos(LpszParent);
    iDataType=GetDataType(iSymId);
    iSymId=GetSymTabPos(LpszMember);
    LpMember=DataTypeTable[iDataType].m_LpDataMembers;
    if(LpMember==NULL)
        return GetDataTypeSize(iDataType);
    while(LpMember->Result!=iSymId)
        {
        iDataType=GetDataType(LpMember->Result);
        iSize=iSize+GetDataTypeSize(iDataType);
        LpMember=LpMember->next;
        }
    return iSize;
	*/
	return -1;
    }
int GetDatatype(char *LpszVariable)
    {
    int SymId,index,flag,HasMember,DataType;
    char szParent[32],szChild[32];
    char *LpszOrginalSymbol;
    LpszOrginalSymbol=LpszVariable;
    flag=0;
    for(index=0;index<SymCount;index++)
        {
        if(strcmp(SymTab[index].Symbol,LpszVariable)==0)
            {
            flag=1;
            break;
            
            }
        }
    
        HasMember=IsMemberCall(LpszVariable);
        
        if(HasMember>0)
            {
            while(HasMember!=0)
                   {
                   LpszVariable=LpszVariable+HasMember+1;
                   HasMember=IsMemberCall(LpszVariable);
                   }
            flag=0;
            for(index=0;index<SymCount;index++)
                {
                 if(strcmp(SymTab[index].Symbol,LpszVariable)==0)
                     {
                      flag=1;
                      break;
                     }
            }
        
            if(flag==1)
            return SymTab[index].DataType;
            else
                {
                    
                printf("Datatype of %s Not Found",LpszOrginalSymbol);
                //catch Exceptions 
                }
            }
        
        
    if(flag==1)
            return SymTab[index].DataType;
	else
    {
        DataType= GetPropertyDataType(szCurrentClass,LpszVariable);
        if(DataType!=-1)
            return DataType;
        else
        return -1;
    }
    
        
    }
/*

*/
Optab * AddToDeclareBlock(Optab * DeclareBlock,Optab *DeclareStatement)
{
	Optab *LpCurrent,*LpStart,*LpTemp;
	LpStart=DeclareStatement;
	LpCurrent=NULL;
	if(CurrentScope==ObjectScope)
	{
		LpCurrent=DeclareStatement;
		while(1)
		{
			AddPropertyToCurrentClass(GetSymbolName(LpCurrent->Result),GetDataType(LpCurrent->Result),SymTab[LpCurrent->Result].LpDimension);
			LpTemp=LpCurrent;
			LpCurrent=LpCurrent->next;
			DeleteSymbol(LpTemp->Result);
			if(LpCurrent==LpStart)
				break;
		}
		
	}
	else if(CurrentScope==eWorkerScope)
	{
		LpCurrent=DeclareStatement;
		MakeGlobalVariable(LpCurrent);
		
	}

	else //if(CurrentScope==eStructScope)
	{
		return ConcatSubscriptNode(DeclareBlock,DeclareStatement);
	}
}
Optab * MakeINparameter(int iDataType,int iParameter,int iAlias)
{
  return NULL;	
}
Optab * MakeOUTparameter(int iDataType,int iParameter,int iAlias)
{
	return NULL;
}
Optab *MakeArrayAndMemberRef(Optab *ArrayRef,int Identifier)
{
	int TargetDataType;
	char  szTempText[60];
	Optab *LastNode,*ProcessedNode;
	  
	  LastNode=GetLastNodeAddr(ArrayRef);
	  TargetDataType=GetPointerTarget(LastNode->Result);
	  SetPointerTarget(LastNode->Operand1,TargetDataType);

	  strcpy(szTempText,GetSymbolName(LastNode->Operand1));
	  strcat(szTempText,".");
	  strcat(szTempText,GetSymbolName(Identifier));
ProcessedNode=ProcessMemberCall(szTempText);
return ConcatNode(ArrayRef,ProcessedNode);
}
 Optab* ProcessMemberCall(char *LpszIdentifier)
    {
    char szParent[32],szChild[32],szParent_Temp[32],szSymBuf[8],szDereferenceTemp[32];
    Optab * Result,*TempResult,*Operand1,*Operand2;
    char *LpszOrginalSymbol;
	char *LpszParentDataTypeName;
    int iMembers,iSize,iSymId,iDataType,IsStructVar,iOffset,bFlag,iStructDataType;
    iSize=0;
	
    LpszOrginalSymbol=LpszIdentifier;
    iMembers=IsMemberCall(LpszIdentifier);
    strncpy(szParent_Temp+1,LpszIdentifier,iMembers);
        szParent_Temp[iMembers+1]='\0';
        szParent_Temp[0]='&';
		iSymId=GetSymbolId(szParent_Temp+1);
		if(GetDataType(iSymId)==GetDataTypeId("Pointer"))
		{
			iStructDataType=GetPointerTarget(iSymId);
			bFlag=GetStructIndex(GetDataTypeName(iStructDataType));
			if(bFlag!=-1)
				IsStructVar=1;
			else
				IsStructVar=0;

		}
		else
		{
			IsStructVar=IsStruct(GetSymbolId(szParent_Temp+1));
		}
    while(iMembers!=0)
        {
        strncpy(szParent,LpszIdentifier,iMembers);
        szParent[iMembers]='\0';
        LpszIdentifier=LpszIdentifier+iMembers+1;
        iMembers=IsMemberCall(LpszIdentifier);
		
		if(GetDataType(iSymId)==GetDataTypeId("Pointer"))
		{
LpszParentDataTypeName=GetDataTypeName(GetPointerTarget(GetSymbolId(szParent)));
		}
		else
			LpszParentDataTypeName=GetDataTypeName(GetDatatype(szParent));

        if(iMembers)
            {
            strncpy(szChild,LpszIdentifier,iMembers);
            szChild[iMembers]='\0';
			if(IsStructVar)
			{
				iSize=iSize+CalculateMemberOffset(LpszParentDataTypeName,szChild);
			}
			else
			{
				iOffset=GetPropertyOffsetAddress(LpszParentDataTypeName,szChild);
				if(iOffset==FALSE)
				{
					iSymId=GetSymbolId(LpszOrginalSymbol);
					
					return MakeNode(iSymId);
				}
				else
					iSize=iSize+iOffset;
			}
            }
        else
            {
            strncpy(szChild,LpszIdentifier,iMembers);
            szChild[iMembers]='\0';
            if(IsStructVar)
			{
				iSize=iSize+CalculateMemberOffset(LpszParentDataTypeName,LpszIdentifier);
			}
			else
			{
				iOffset=GetPropertyOffsetAddress(LpszParentDataTypeName,LpszIdentifier);
				if(iOffset<=-1)
					return NULL;
				else
					iSize=iSize+iOffset;
			}
            }   
        }
	if(GetDataType(iSymId)==GetDataTypeId("Pointer"))
	{
		Operand1=MakeNode(AddSymbol(szParent_Temp+1));
		Operand2=MakeNode(AddLiteral(itoa(iSize,szSymBuf,16),0));
	}
	else
	{
		Operand1=MakeNode(AddSymbol(szParent_Temp));
		SetDataType(Operand1->Result,GetDataTypeId("AddressOf"));
		Operand2=MakeNode(AddLiteral(itoa(iSize,szSymBuf,16),0));
	}

    SetStorage(Operand2->Result,LocalStorage);
    TempResult=GenerateTempVariable();
	if(IsStructVar)
		iDataType=GetDataType_StructMember(LpszParentDataTypeName,LpszIdentifier); //getting datatType of the innermost element
	else
       iDataType=GetPropertyDataType(LpszParentDataTypeName,LpszIdentifier);
    
    SetTempVariableInfo(TempResult,Operand1,Operand2);
    Result=AddOperation(TempResult,GetOperatorId("+"),Operand1,Operand2);
    
    SetStorage(TempResult->Result,PointerStorage);
    strcpy(szDereferenceTemp+1,GetSymbolName(TempResult->Result));
    szDereferenceTemp[0]='@';
    iSymId=AddSymbol(szDereferenceTemp);
    SetPointerTarget(iSymId,iDataType);
    SetStorage(iSymId,NONEStorage);
    SetDataType(iSymId,GetDataType(GetSymTabPos(LpszIdentifier)));
    TempResult=MakeNode(iSymId);
    Operand2=MakeNode(-1);
    Result=AddOperation(TempResult,GetOperatorId("DEREFERENCE"),Result,Operand2);
//    SetTempVariableInfo(TempResult,Operand1,NULL);
    return Result;

    }
 Optab *MakeDereferenceOperation(int iDataType,int iSymId)
 {
 
 char szSymbol[MAX_SYM_LEN+1];
 Optab * LpCurrentNode,*Result,*Operand2,*TempResult,*TempVariable;
 strcpy(szSymbol,"@");
 
 strcat(szSymbol,GetSymbolName(iSymId));
 Result=MakeNode(iSymId);
 iSymId=AddSymbol(szSymbol);
  
 TempResult=MakeNode(iSymId);
 SetPointerTarget(iSymId,iDataType);
    Operand2=MakeNode(-1);
    Result=AddOperation(TempResult,GetOperatorId("DEREFERENCE"),Result,Operand2);
 return Result;
 }
int IsMemberCall(char *LpszIdentifier)
    {
    unsigned int i;
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
	 struct ArrayDimension *LpDim;
     if(iCompileOption==eUnitTest)
         return;
    printf("-------------SymbolTable---------------\nSymbolName DataType    \t BlockNumber Scope SymbolAddress PointerTarget");
    for(i=0;i<SymCount;i++)
        {
            if(!IsValidSymbol(i))
                continue;
        printf("\n%s\t\t%s\t\t%d\t\t%d\t\t%d %s",SymTab[i].Symbol,DataTypeTable[SymTab[i].DataType].m_szDataTypeName,SymTab[i].BlockNumber,SymTab[i].m_Scope,SymTab[i].SymbolAddress,DataTypeTable[SymTab[i].PointerTarget].m_szDataTypeName);
        
        LpDim=GetDimension(i);
        
        while(LpDim!=NULL)
            {
				printf(" %d",LpDim->iDimension);
				LpDim=LpDim->LpNext;
            }
        
        }
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
			
            else if(KW_ID[i]==ELSE_KW)
                {
                TermOldBlock();
                InitNewBlock();
                }
            else if((KW_ID[i]==EIF_KW))
                {
                TermOldBlock();
                }
            else if((KW_ID[i]==ELSIF_KW))
                {
                TermOldBlock();
                InitNewBlock();
                }
            else if((KW_ID[i]==LOOP_KW))
                {
                InitNewBlock();
                }
			else if((KW_ID[i]==TASK_KW))
                {
					TermOldBlock();
					CurrentScope=LocalScope;
                InitNewBlock();
                }
            else if((KW_ID[i]==DATATYPE_KW))
                {
                InitNewBlock();
				//CurrentScope=eStructScope;
                }
            
            else if((KW_ID[i]==FUNCTION_KW))
                {
                if(CurrentScope==ObjectScope)
                    {
                    //AssignAddressObjectMember();
                    }
                CurrentScope=LocalScope;
                InitNewBlock();
                }
			else if((KW_ID[i]==INTERRUPT_KW))
                {
                
                CurrentScope=LocalScope;
                InitNewBlock();
                }
            else if((KW_ID[i]==OBJECTTYPE_KW))
                {
                CurrentScope=ObjectScope;
                InitNewBlock();
                }
			else if((KW_ID[i]==TASK_KW))
                {
                CurrentScope=LocalScope;
                InitNewBlock();
                }
			else if((KW_ID[i]==WORKER_KW))
                {
                CurrentScope=eWorkerScope;
                InitNewBlock();
                }
			else if((KW_ID[i]==END_DEFINE_KW))
                {
                CurrentScope=GlobalScope;
                InitNewBlock();
                }

            return KW_ID[i];
            }
        }
    return -1;
    }
	
	int GetPropertyDataType(char *LpszClassName,char *LpszPropertyName)
	{
	struct ClassDefinition *LpClassDefn;
	struct OMProperty *LpProperty;
	int iDataType;
	LpProperty=NULL;
	LpClassDefn=NULL;
	//iOffset=0;
	
	LpClassDefn=GetClassInformation(LpszClassName);
	if(LpClassDefn!=NULL)
	LpProperty=LpClassDefn->m_LpMemberVar;
	else
		return FALSE;
		while(LpProperty!=NULL)
	{
		if(strcmp(LpProperty->m_szPropertyName,LpszPropertyName)==0)
				return LpProperty->m_iDataType;
		LpProperty=LpProperty->m_LpNext;
	  
		

	}
		return -1;
	}
int GetPropertyOffsetAddress(char *LpszClassName,char *LpszPropertyName)
{
	struct ClassDefinition *LpClassDefn;
	struct OMProperty *LpProperty;
	int iOffset;
	LpProperty=NULL;
	LpClassDefn=NULL;
	iOffset=0;
	
	LpClassDefn=GetClassInformation(LpszClassName);
	if(LpClassDefn!=NULL)
	LpProperty=LpClassDefn->m_LpMemberVar;
	else
		return -1;
	while(LpProperty!=NULL)
	{
		if(strcmp(LpProperty->m_szPropertyName,LpszPropertyName)==0)
				break;
		if(LpProperty->m_LpDimension==NULL)
		iOffset=iOffset+GetDataTypeSize(LpProperty->m_iDataType);
		else
		{
			int arrSize;

			struct ArrayDimension *LpCurrentDim;
			arrSize=1;
			LpCurrentDim=LpProperty->m_LpDimension;
			while(LpCurrentDim!=NULL)
			{
				arrSize=arrSize*LpCurrentDim->iDimension;
				LpCurrentDim=LpCurrentDim->LpNext;
			}
			iOffset=iOffset+GetDataTypeSize(LpProperty->m_iDataType)*arrSize;
		}
		LpProperty=LpProperty->m_LpNext;
	  
		

	}
	if(LpProperty==NULL)
	{
		ErrorHandler(INFO,"No Such Property");
		return -1;
	}
	return iOffset;
}
 
 void SetStorage(int iSymId,int iStorageType)
     {
     SymTab[iSymId].m_StorageType=iStorageType;
     SymTab[iSymId].m_Scope=CurrentScope;
     }
 char *GenerateTempLiteralName()
     {
     char no[10];
     char TempLit[LEN];
     int sym;
     itoa(TempLitCount,no,10);
     strcpy(TempLit,"L");
     strcat(TempLit,no);
     TempLitCount++;
     return TempLit;
     }
 Optab * MakeNegativeLiteral(int  LiteralOperand)
     {
     int iValue,SymId;
     char szValue[12];
     strcpy(szValue,GetLiteralValue(LiteralOperand,0));
     iValue=atoi(szValue);
     iValue=iValue*-1;
     itoa(iValue,szValue,10);
     SymId=AddLiteral(szValue,0);
     return MakeNode(SymId);
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
     SetStorage(sym,TempStorage);
     return MakeNode(sym);
     }
 

 void AssignLabel(Optab* Current,Optab * Target)
     {
     char *label; 
     if(strlen(Current->TargetLabel)!=0)
         return;
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
 int ProcessJumpStatement(Optab *current,struct FuncDetails *funcdetails)
     {
     char label[20]; 
     Optab * JumpTarget,*LpPrevious;
         LpPrevious=current->previous;
     
      if(current->Operator==GetOperatorId("JMP"))
         {
         JumpTarget=current->instr_addr;
         AssignLabel(current,JumpTarget);
         return 1;
         }
        if(current->Operator==GetOperatorId("JNE"))
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
		 if(JumpTarget->Operator==GetOperatorId("ClearRegs"))
		 {
			 while((JumpTarget!=Func_Start)&&(JumpTarget->Operator==GetOperatorId("ClearRegs")))
				 JumpTarget=JumpTarget->next;
		 }
		 if(JumpTarget==Func_Start)
		 {
			 strcpy(current->TargetLabel,"Epilogue_");
			 strcat(current->TargetLabel,funcdetails->szFunctionLabel);
		 }
		 else
         AssignLabel(current,JumpTarget);
         return 1;
         }
           else if(current->Operator==GetOperatorId("JNE_JNXT"))
         {   
         JumpTarget=current->instr_addr;
         JumpTarget=JumpTarget->next;
		 if(JumpTarget->Operator==GetOperatorId("ClearRegs"))
		 {
			 while((JumpTarget!=Func_Start)&&(JumpTarget->Operator==GetOperatorId("ClearRegs")))
				 JumpTarget=JumpTarget->next;
		 }
		 if (JumpTarget==Func_Start)
		 {
    			 strcpy(current->TargetLabel,"Epilogue_");
			 strcat(current->TargetLabel,funcdetails->szFunctionLabel);
		 }
		 
		 else
			 AssignLabel(current,JumpTarget);
         current->Operator=GetOperatorId("JNE");
         
         return 1;
         }
          else if((current->Operator==GetOperatorId("JL"))||(current->Operator==GetOperatorId("JG"))||(current->Operator==GetOperatorId("JBE"))||(current->Operator==GetOperatorId("JZ"))||(current->Operator==GetOperatorId("JA"))||(current->Operator==GetOperatorId("JB"))||((current->Operator==GetOperatorId("JNE")))||(current->Operator==GetOperatorId("JLE"))||(current->Operator==GetOperatorId("JE")))
              return 1;
     return 0;
     }
 
 
 void DisplayOptab()
        {
       /* char Instruction[100];
        Optab * current;
        int IsJump;
        current=Func_Start;
        if(current==NULL)
            return;
        while(1)
            {
            Instruction[0]='\0';
            if(current->Operator==GetOperatorId("ASM"))
                {
                printf("%s",current->AsmPointer);
                current=current->next;
            if(current==Func_Start)
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
            if(current==Func_Start)
                break;
            }*/
        }

char * GenerateTempLabel()
     {
     char no[10];
     char Temp[LEN];
     itoa(LabelCount,no,10);
     strcpy(Temp,"LABEL");
     strcat(Temp,no);
     LabelCount++;
     return Temp;
     }
   char * GetOperatorName(int OPERATORID)
    {
    return OperatorTab[OPERATORID];
    }
   struct ClassDefinition * AddNewClass(char *LpszClassName)
   {
	   int i,found;
	   found=0;
	   for(i=0;i<iClassCount;i++)
	   {
		   if(strcmp(ClassDefn[i].m_szClassName,LpszClassName)==0)
		   {
			   found=1;
		   }
	   }
	   if(found==0)
	   {
		   if(iClassCount==MAX_CLASS_COUNT)
		   {
			   ErrorHandler(ERROR,"Maximum Class Count Reached");
		   }
		   else
		   {
			strcpy(ClassDefn[iClassCount].m_szClassName,LpszClassName);
			ClassDefn[iClassCount].m_LpMemberFun=NULL;
			ClassDefn[iClassCount++].m_LpMemberVar=NULL;
			return &ClassDefn[iClassCount-1];
		   }
	   }
   }
  int SetWorkerName(int iSymId)
  {
	  strcpy(szCurrentWorker,GetSymbolName(iSymId));
	  DeleteSymbol(iSymId);
	  return -1;
  }
   int SetCurrentClassName(int iSymId)
   {
	   
	   strcpy(szCurrentClass,GetSymbolName(iSymId));
	   LpCurrentClass=AddNewClass(szCurrentClass);
	   AddDataType(szCurrentClass,0,NULL,NULL);
	   DeleteSymbol(iSymId);
	   return -1;
   }
   

   Optab *MakeStructDeclaration(int iStructNameID, Optab *Members)
       {
       int iDataTypeSize,iTotalSize;
       Optab *LpCurrent,*LpStart;
	   struct StructDecMember  *LpMemStart,*LpMemCurrent,*LpMemPrev;
	   char *LpszStructName;
       LpCurrent=Members;
	   iTotalSize=0;
	   
       LpStart=Members;
	   LpMemStart=NULL;
	   LpMemCurrent=NULL;
	   LpMemPrev=NULL;
       while(1)
       {
		   LpMemCurrent=(struct StructDecMember *)malloc(sizeof(struct StructDecMember));
		   LpMemCurrent->m_LpNext=NULL;
		   strcpy(LpMemCurrent->m_szSymbolName,GetSymbolName(LpCurrent->Result));
		   LpMemCurrent->m_iDataType=GetDataType(LpCurrent->Result);
		   
		   if(LpMemStart==NULL)
		   {
			   LpMemStart=LpMemCurrent;
			   
		   }
		   else
		   {
			   
			   LpMemPrev->m_LpNext=LpMemCurrent;
		   }
		   iDataTypeSize=GetDataTypeSize(LpMemCurrent->m_iDataType);
			   iTotalSize=iTotalSize+iDataTypeSize;
		   LpMemPrev=LpMemCurrent;
           DeleteSymbol(LpCurrent->Result);
           LpCurrent=LpCurrent->next;
           if(LpCurrent==LpStart)
               break;
           }
       
	   
	   LpszStructName=GetSymbolName(iStructNameID);
       AddDataType(LpszStructName,iTotalSize,Members,NULL);
	   //TODO: check iStructCount<MAX_STRUCT_LEN
	   strcpy(StructTable[iStructCount].m_szStructName,LpszStructName);
	   StructTable[iStructCount++].m_LpStart=LpMemStart;
	   DeleteSymbol(iStructNameID);
       return NULL;
       }
  Optab * MakeNode(int iSymbolId)
       {
       Optab* ID_Node;
       if(iSymbolId!=-1)
           if(SymTab[iSymbolId].NodePtr!=NULL)
		   {
			   ID_Node=SymTab[iSymbolId].NodePtr;
			   if(ID_Node==ID_Node->next)
			   return SymTab[iSymbolId].NodePtr;
		   }
       ID_Node=MakeSimpleNode();
       strcpy(ID_Node->Result_c,GetSymbolName(iSymbolId));
       ID_Node->Result=iSymbolId;
       SymTab[iSymbolId].NodePtr=ID_Node;
       return ID_Node;
      }
  void InitNewBlock()
      {
    
      Block_Number++;
      block_start=NULL;
      }
  void TermOldBlock()
      {
      Block_Number--;
            }

  Optab* MakeDeclareIDSubscript(Optab* Identifier,Optab* Subscript)
      {
      Identifier->subscript=Subscript;
      return Identifier;
      }
  int IsPointer(Optab * LpCurrent)
      {
      char * LpszSymName=GetSymbolName(LpCurrent->Result);
      if(LpszSymName[0]=='@')
          return 1;
      else
      return 0;
      }
  Optab * MakeInterruptDeclaration()
  {

  }
  Optab* MakeDeclareStatement(int Datatype,Optab* ID_List)
      {
      Optab *Current,*Start;
      Current=Start=ID_List;
      while(1)
          {
          if(DataTypeIsStruct(Datatype))
              {
              if(IsPointer(Current))
                  {
                  SetDataType(Current->Result,Datatype);
                  SetStorage(Current->Result,PointerStorage);
                  }
              else
                  {
                  SetDataType(Current->Result,Datatype);
                  SetStorage(Current->Result,StructStorage);
              
                  }
              }
          else if(IsPointer(Current))
              {
              SetDataType(Current->Result,Datatype);
              SetStorage(Current->Result,PointerStorage);
              }
          else
              {
              SetDataType(Current->Result,Datatype);
              if(GetStorage(Current->Result)==NONEStorage)
                  {
                  if(CurrentScope==LocalScope)
                      {
                      SetStorage(Current->Result,LocalStorage);

                      }
                  else
                      {
                      SetStorage(Current->Result,ObjectDataMember);
                      }
                  }
              //SetStorage(Current->Result,LocalStorage);
              }

          
          if(Current->subscript!=NULL)
              {
              
              SetDimension(Current->Result,Current->subscript);
              }
          Current=Current->next;
          if(Current==Start)
                break;
          }
      return ID_List;
      }
  
  void  setDataTypeSize(int DataType,int Size)
  {
	  DataTypeTable[DataType].m_iDataTypeSize=Size;
  }
  void AddPropertyToCurrentClass(char *LpszPropertyName,int iDataType,struct ArrayDimension *LpDimension)
  {
	  struct OMProperty *LpPropertyList,*LpPropCurrent;
	  int iDataTypeSize,DataType;
	  LpPropertyList=LpCurrentClass->m_LpMemberVar;
	  LpPropCurrent=(struct OMProperty*)malloc(sizeof(struct OMProperty));
	  LpPropCurrent->m_LpNext=NULL;
	  if(LpDimension==NULL)
	  LpPropCurrent->m_LpDimension=NULL;
	  else
		  LpPropCurrent->m_LpDimension=LpDimension;
	  strcpy(LpPropCurrent->m_szPropertyName,LpszPropertyName);
	  LpPropCurrent->m_iDataType=iDataType;
	  
	  if(LpPropertyList!=NULL)
	  {
		  while(1)
		  {
			if(strcmp(LpPropertyList->m_szPropertyName,LpszPropertyName)==0)
			{
			  ErrorHandler(ERROR,"Duplicate Property");
			}	
			if(LpPropertyList->m_LpNext!=NULL)
				LpPropertyList=LpPropertyList->m_LpNext;
			else
				break;
		  }
		  LpPropertyList->m_LpNext=LpPropCurrent;
		  
	  }
	  else
	  {
		  LpCurrentClass->m_LpMemberVar=LpPropCurrent;
		 
	  }
	  //iDataTypeSize=LpPropCurrent->m_iOffsetAddress+GetDataTypeSize(LpPropCurrent->m_iDataType);
	  DataType=GetDataTypeId(szCurrentClass);
	  if(LpDimension==NULL)
	  iDataTypeSize=GetDataTypeSize(DataType)+GetDataTypeSize(LpPropCurrent->m_iDataType);
	  else
	  {
		  int arrSize;
		  struct  ArrayDimension *LpCurrentDim;
		  arrSize=1;
		  LpCurrentDim=LpDimension;
		  while(LpCurrentDim!=NULL)
		  {
			  arrSize=arrSize*LpCurrentDim->iDimension;
			  LpCurrentDim=LpDimension->LpNext;
		  }
		  iDataTypeSize=GetDataTypeSize(DataType)+GetDataTypeSize(LpPropCurrent->m_iDataType)*arrSize;

	  }
	  setDataTypeSize(DataType,iDataTypeSize);
  }
void MakeReturnsStatement(int iDataType)
{
	int iSymTabPos;
	iSymTabPos=-1;
		/*if(!IsPrimitive(iDataType))
		{
			iSymTabPos=AddSymbol("_Address_ReturnValue"); // creates a pointer variable which stores the Address of a Non Primitive value which is returned from callee
			SetDataType(iSymTabPos,GetDataTypeId("Pointer"));
			SetStorage(iSymTabPos,PointerStorage);
		}*/
}
struct OMProperty *GetOMProperty(char *LpszClassName,char *LpszPropertyName)
	{
		struct ClassDefinition *LpClassDefn;
	struct OMProperty *LpProperty;
	int iDataType;
	LpProperty=NULL;
	LpClassDefn=NULL;
	//iOffset=0;
	
	LpClassDefn=GetClassInformation(LpszClassName);
	if(LpClassDefn!=NULL)
	LpProperty=LpClassDefn->m_LpMemberVar;
	else
		return NULL;
		while(LpProperty!=NULL)
	{
		if(strcmp(LpProperty->m_szPropertyName,LpszPropertyName)==0)
				return LpProperty;
		LpProperty=LpProperty->m_LpNext;
	  
		

	}
	}
  

Optab *MakeTaskDeclaration(int FunctionNameSymTabPos,Optab *LpFormalParam,Optab *StatementBlock)
{
	int IsFormalParam,SymId;
	char *LpszTaskName;
	int index,Address=0;
	
	index=1; //0 index is TaskName
	IsFormalParam=true;
	LockRegister(EBX);
	LockRegister(bh);
	LockRegister(bl);
	LockRegister(bx);
	 // will add parameters to ask afetr sometime
	for(;index<SymCount;index++)
        {
if(GetScope(index)!=GlobalScope)
        if(SymTab[index].m_StorageType!=NONEStorage)// Local storage has to be changed to local scope. else struct members wont disappear from symtab
            {
            if(SymTab[index].m_StorageType==PointerStorage)
                {
                Address=Address+4;
                SymTab[index].SymbolAddress=Address;
            
                }
            else
                {
                Address=Address+GetDatatypeSize(index);
            SymTab[index].SymbolAddress=Address;
            
                }
            }
        
	}
	LpszTaskName=GetSymbolName(FunctionNameSymTabPos);
	FunctionDetails.AddressEnd=Address;
    FunctionDetails.iReturnDataType=-1;
	strcpy(FunctionDetails.szClassName,szCurrentWorker);
	if(strcmp(LpszTaskName,"start")==0)
	{
		strcpy(FunctionDetails.szFunctionLabel,"__main");
		strcpy(FunctionDetails.FunctionName,"main");
	}
	else
	{
		strcpy(FunctionDetails.szFunctionLabel,szCurrentWorker);
		strcat(FunctionDetails.szFunctionLabel,"_");
		strcat(FunctionDetails.szFunctionLabel,LpszTaskName);
		strcpy(FunctionDetails.FunctionName,LpszTaskName);
	}
	
	#if (CHECK_DEBUG_ENABLED(DEBUG_SHOW_SYMTAB)) 
	printf(" SymTab for function ' %s '\n",GetSymbolName(FunctionNameSymTabPos));
    DisplaySymTab(); 
	#endif
	#if (CHECK_DEBUG_ENABLED(DEBUG_SHOW_OPTAB)) 
	printf(" OPTAB for function ' %s '\n",GetSymbolName(FunctionNameSymTabPos));
	#endif
    Generate_x86ASM_Function(Func_Start,FunctionDetails);
    WriteStringLiterals();
        for(index=0;index<SymCount;index++)
            {
				if(SymTab[index].m_Scope==LocalScope)
				{
					DeleteSymbol(index);
					SymCount--;
				}
		     }
            DisplayOptab();
            Func_Start=NULL;
//SymCount=0;


LitCount=0;

}
Optab* MakeOperationDeclaration(int RtrnDataType,int FunctionNameSymTabPos,Optab * ParamList,Optab *StatementBlock){
	int i=0;
	i=22;
}
Optab* MakeFunctionDeclaration(int RtrnDataType,int FunctionNameSymTabPos,Optab * ParamList,Optab *StatementBlock,int eType)
    {
    int iFunctionIndex,index,Address=0;
    int IsFormalParam,SymId;
	int  GlobalSymCount;
	struct OMFunction *LpCurrentFunction;
    IsFormalParam=true;
	LpCurrentFunction=NULL;
    
	if(eType==FUNCTION_KW)
    LpCurrentFunction=AddFunctionTable(RtrnDataType,GetSymbolName(FunctionNameSymTabPos),ParamList,StatementBlock);
    LockRegister(EBX);
	LockRegister(bh);
	LockRegister(bl);
	LockRegister(bx);
    index=1; //index 0 is functionname
    //while(SymTab[index].m_Scope!=LocalScope)
      //  index++;
    //index++; //skipping the function name which is the first entry in symtab as Localscope
	if(ParamList!=NULL)
	{
		if(index!=ParamList->Result)
         IsFormalParam=false;
	}
	else
	{
		IsFormalParam=false;
	}

    while(IsFormalParam==true)
        {
        if(SymTab[index].m_StorageType!=NONEStorage)// Local storage has to be changed to local scope. else struct members wont disappear from symtab
            {
				if(GetScope(index)==GlobalScope)
					continue;
            if(SymTab[index].m_StorageType==PointerStorage)
                {
            Address=Address+4;
                SymTab[index].SymbolAddress=Address;
            
                }
            else
                {
                Address=Address+GetDatatypeSize(index);
            SymTab[index].SymbolAddress=Address;
            
                }
            }
 index++;
 ParamList=ParamList->next;
 if(index!=ParamList->Result)
        IsFormalParam=false;
        }
    
	   
    for(;index<SymCount;index++)
        {
if(GetScope(index)==GlobalScope)
					continue;
        if(SymTab[index].m_StorageType!=NONEStorage)// Local storage has to be changed to local scope. else struct members wont disappear from symtab
            {
            if(SymTab[index].m_StorageType==PointerStorage)
                {
            Address=Address+4;
                SymTab[index].SymbolAddress=Address;
            
                }
            else
                {
                Address=Address+GetDatatypeSize(index);
            SymTab[index].SymbolAddress=Address;
            
                }
            }
        
        }
	if(MaxStackSize<Address)
MaxStackSize=Address;
	Address+=4;  // offset added to address an issue(issue 15 in TODO doc)
    FunctionDetails.AddressEnd=Address;
    FunctionDetails.iReturnDataType=RtrnDataType;
	FunctionDetails.iType=eType;
	strcpy(FunctionDetails.szClassName,szCurrentClass);
	if(eType==FUNCTION_KW)
	{
	strcpy(FunctionDetails.szFunctionLabel,LpCurrentFunction->m_szFunctionLabel);
	strcpy(FunctionDetails.FunctionName,LpCurrentFunction->m_szFunctionName);
	}
	else
	{
		strcpy(FunctionDetails.szFunctionLabel,GetSymbolName(FunctionNameSymTabPos));
		strcpy(FunctionDetails.FunctionName,GetSymbolName(FunctionNameSymTabPos));
	}
	
	
    #if (CHECK_DEBUG_ENABLED(DEBUG_SHOW_SYMTAB))
	printf("\n--------- SymTab for function ' %s '-----------\n",GetSymbolName(FunctionNameSymTabPos));
    DisplaySymTab();
	#endif
	#if (CHECK_DEBUG_ENABLED(DEBUG_SHOW_OPTAB))
	printf("------------ OPTAB for function ' %s '------------\n",GetSymbolName(FunctionNameSymTabPos));
	#endif
    Generate_x86ASM_Function(StatementBlock,FunctionDetails);
    WriteStringLiterals();
	GlobalSymCount=0;
        for(index=0;index<SymCount;index++)
            {
                if(GetScope(index)!=GlobalScope)
				{
					DeleteSymbol(index);
					
				}
				else
					GlobalSymCount++;
		     }
            DisplayOptab();
            Func_Start=NULL;
SymCount=GlobalSymCount;

LitCount=0;
//TempLitCount=0;
//TODO: delete the NodePtr of all local Variables by looping and finding out.
            
return NULL;
    }
  Optab* MakeSimpleNode()
      {
      current=(Optab *)malloc(sizeof(struct optab));
      current->instr_addr=NULL;
      current->Result=-1;
      current->Operator=-1;
      current->Operand1=-1;
      current->Operand2=-1;
      current->Label[0]='\0';
      current->Result_c[0]='\0';
      current->Operand1_c[0]='\0';
      current->Operand2_c[0]='\0';
      current->Operator_c[0]='\0';
      current->TargetLabel[0]='\0';
      current->AsmPointer=NULL;
      current->subscript=NULL;
      current->SubscriptIndex=-1;
      current->ArrayIndex=-1;
      current->next=current;
      current->previous=current;
      return current;
      }
  Optab * DeleteNode( Optab * Node)
      {
      
      Optab* Previous,*Next;
      Previous=Node->previous;
      if(Previous==Node)
          {
          prog_start=NULL;
          return NULL;
          }
      
      Next=Node->next;
      if(Node==prog_start)
          prog_start=Next;
      Previous->next=Next;
      Next->previous=Previous;
      return Previous;
      }
  void BackPatch(Optab * Current,Optab* PatchAddr)
     {
     Optab* Start=Current;
     while(1)
         {
         if((Current->Operator==GetOperatorId("JMP_JNXT"))&&(strlen(Current->TargetLabel)==0)&&(Current->instr_addr==NULL))
             {
             Current->instr_addr=PatchAddr;
             }
         else if((Current->Operator==GetOperatorId("BRK_L"))&&(strlen(Current->TargetLabel)==0))
             {
             Current->Operator=GetOperatorId("JMP_JNXT");
             strcpy(Current->Operator_c,GetOperatorName(Current->Operator));
             Current->instr_addr=PatchAddr;
             }
         Current=Current->next;
         if(Current==Start)
             break;
         }
     }
  void BackPatchWhileLoop(Optab * Current,Optab* BreakPatchAddr,Optab * ContinuePatchAddress)
     {
      Optab* Start=Current;
     while(1)
         {
         
         if((Current->Operator==GetOperatorId("BRK_LOOP"))&&(strlen(Current->TargetLabel)==0))
             {
             Current->Operator=GetOperatorId("JMP_JNXT");
             strcpy(Current->Operator_c,GetOperatorName(Current->Operator));
             Current->instr_addr=BreakPatchAddr;
             }
         else if((Current->Operator==GetOperatorId("CONT_LOOP"))&&(strlen(Current->TargetLabel)==0))
             {
             Current->Operator=GetOperatorId("JMP");
             strcpy(Current->Operator_c,GetOperatorName(Current->Operator));
             AssignLabel(Current,ContinuePatchAddress);
             Current->instr_addr=ContinuePatchAddress;
             }
         Current=Current->next;
         if(Current==Start)
             break;
         }
     }
  Optab * ConcatSubscriptNode(Optab *Node1,Optab * Node2)
      {
      Optab* Node1_Last,*Node2_Last;
	  if(Node1==NULL)
		  return Node2;
	  if(Node2==NULL)
		  return Node1;
      Node1_Last=Node1->previous;
      Node2_Last=Node2->previous;
      Node1_Last->next=Node2;
      Node2->previous=Node1_Last;
      Node2_Last->next=Node1;
      Node1->previous=Node2_Last;
      return Node1;
      }
   Optab * ConcatNode(Optab *Node1,Optab * Node2)
      {
      Optab * Node1_Last,*Node2_Last;
      if(Node1==NULL)
          return Node2;
      if(Node2==NULL)
          return Node1;
      if(Node2->Operator==-1) //have to include code to check if both are ID Nodes..
          return Node1;
      if(Node1->Operator==-1)
          return Node2;
      
      Node1_Last=Node1->previous;
      Node2_Last=Node2->previous;
      Node1_Last->next=Node2;
      Node2->previous=Node1_Last;
      Node2_Last->next=Node1;
      Node1->previous=Node2_Last;
      return Node1;
      }
  int GetResult(Optab* BlockStart)
      {
      Optab* Temp;
      if(BlockStart->Operator==-1)
          {
          return BlockStart->Result;
          }
      if(BlockStart==BlockStart->next)
          return BlockStart->Result;
      Temp=BlockStart->previous;
	  if((Temp->Operator==GetOperatorId("UnSetEBX"))||(Temp->Operator==GetOperatorId("SetEBX")))
		  Temp=Temp->previous;
      return Temp->Result;
      }
  Optab *PerformCast(int Operand,int DestinationDataType)
      {
      Optab *LpCastOperation,*LpTempResult;
      LpTempResult=GenerateTempVariable();
      SetDataType(LpTempResult->Result,DestinationDataType);
      LpCastOperation=MakeSimpleNode();
      LpCastOperation->Result=LpTempResult->Result;
      LpCastOperation->Operator=GetOperatorId("cast");
      LpCastOperation->Operand1=Operand;
      LpCastOperation->Operand2=DestinationDataType;
      strcpy(LpCastOperation->Result_c,GetSymbolName(LpCastOperation->Result));
      strcpy(LpCastOperation->Operand1_c,GetSymbolName(LpCastOperation->Operand1));
      strcpy(LpCastOperation->Operand2_c,GetDataTypeName(LpCastOperation->Operand2));
      strcpy(LpCastOperation->Operator_c,GetOperatorName(LpCastOperation->Operator));
      return LpCastOperation;
      }
  void IncrementLineCount()
  {
	  iLineNo++;
  }
 Optab * AddOperation(Optab * RESULT,int OPERATOR,Optab * OPERAND1,Optab * OPERAND2)
        {
         Optab* Temp,*Current;
         int Operand1,Operand2,Result;
        Current=MakeSimpleNode();
        if(Func_Start==NULL)
            Func_Start=current;
        if(block_start==NULL)
            {
            block_start=current;
            }
        Operand1=GetResult(OPERAND1);
        Operand2=GetResult(OPERAND2);
        Result=GetResult(RESULT);
        if(((IsLiteral(Operand1))&&(IsLiteral(Operand2))))
            {
            int iOperand1,iOperand2,iOperandResult,iSymId;
            char szOperand[15];
            strcpy(szOperand,GetLiteralValue(Operand1,0));
            iOperand1=atoi(szOperand);
            strcpy(szOperand,GetLiteralValue(Operand2,0));
            iOperand2=atoi(szOperand);
            if(OPERATOR==GetOperatorId("-"))
                {
                iOperandResult=iOperand1-iOperand2;
                }
            else if(OPERATOR==GetOperatorId("+"))
                {
                iOperandResult=iOperand1+iOperand2;
                }
            else if(OPERATOR==GetOperatorId("*"))
                {
                iOperandResult=iOperand1*iOperand2;
                }
            else if(OPERATOR==GetOperatorId("/"))
                {
                iOperandResult=iOperand1/iOperand2;
                }
            else if(OPERATOR==GetOperatorId("^"))
                {
                int i;
                    i=iOperand2;
                    iOperandResult=1;
                    while(i>0)
                        {
                        iOperandResult=iOperandResult*iOperand1;
                        i--;
                        }
                }
            itoa(iOperandResult,szOperand,10);

            iSymId=AddLiteral(szOperand,0);

            Current->Result=GetResult(RESULT);
            Current->Operator=GetOperatorId("=");
            Current->Operand1=iSymId;
            Current->Operand2=-1;
            }
        else
            {
            
            
         /*   if(IsLiteral(Operand1))
                {
                if((GetDataType(Operand2)==GetDataTypeId("int8")))
                    SetDataType(Operand1,GetDataTypeId("_int_ltrl_8"));
                else if((GetDataType(Operand2)==GetDataTypeId("int16")))
                    SetDataType(Operand1,GetDataTypeId("_int_ltrl_16"));
                else if((GetDataType(Operand2)==GetDataTypeId("int32"))||(GetDataType(Operand2)==GetDataTypeId("Pointer"))||(GetDataType(Operand2)==GetDataTypeId("AddressOf")))
                    SetDataType(Operand1,GetDataTypeId("_int_ltrl_32"));
                }
            else if(IsLiteral(Operand2))
                {
                if((GetDataType(Operand1)==GetDataTypeId("int8")))
                    SetDataType(Operand2,GetDataTypeId("_int_ltrl_8"));
                else if((GetDataType(Operand1)==GetDataTypeId("int16")))
                    SetDataType(Operand2,GetDataTypeId("_int_ltrl_16"));
                else if((GetDataType(Operand1)==GetDataTypeId("int32"))||(GetDataType(Operand1)==GetDataTypeId("Pointer"))||(GetDataType(Operand1)==GetDataTypeId("AddressOf")))
                    SetDataType(Operand2,GetDataTypeId("_int_ltrl_32"));
                }
                */
            if((!IsLiteral(Operand1))&&(!IsLiteral(Operand2)))// Nothing to be done in cases where only one is literal.
                {
                int iCompareSize;
                Optab *TempNode;
            iCompareSize=CompareSize(Operand1,Operand2);
            if(iCompareSize==Operand1)
                {
                int Operand1DataType;
                Operand1DataType=GetDataType(Operand1);
                if(Operand1DataType==GetDataTypeId("AddressOf"))
                    Operand1DataType=GetDataTypeId("Pointer");
                TempNode=PerformCast(Operand2,Operand1DataType);
                Operand2=GetResult(TempNode);
                OPERAND2=ConcatNode(OPERAND2,TempNode);
                
                //OPERAND2=TempNode; have to check why i added this code
                }
            else if(iCompareSize==Operand2)
                {
                int Operand2DataType;
                Operand2DataType=GetDataType(Operand2);
                if(Operand2DataType==GetDataTypeId("AddressOf"))
                    Operand2DataType=GetDataTypeId("Pointer");
                TempNode=PerformCast(Operand1,Operand2DataType);
                Operand1=GetResult(TempNode);
                OPERAND1=ConcatNode(OPERAND1,TempNode);
                
                //OPERAND1=TempNode;
                }
                }
            
        Current->Result=Result;
        Current->Operator=OPERATOR;
        Current->Operand1=Operand1;
        Current->Operand2=Operand2;
            }
            if(OPERATOR==GetOperatorId("<"))
                {
                Optab *Temp1,*Temp2,*Temp3,*Temp4;
                char szLabelTrue[MAX_LABEL_LEN];
                Current->Operand1=Operand1;
                Current->Operand2=Operand2;
                Current->Operator=GetOperatorId("comp");
                SetDataType(Result,GetDataTypeId("int8"));
                Current->Result=-1;
                Temp1=MakeSimpleNode();
                Temp2=MakeSimpleNode();
                Temp3=MakeSimpleNode();
                Temp4=MakeSimpleNode();
                Temp1->Result=-1;
                if(IsSigned(Operand1))
                Temp1->Operator=GetOperatorId("JL");
                else
                    Temp1->Operator=GetOperatorId("JB");
                AssignLabel(Temp1,Temp4);
                Temp2->Result=Result;
                Temp2->Operator=GetOperatorId("=");
                Temp2->Operand1=AddLiteral("0",0);
                
                Temp3->Operator=GetOperatorId("JMP_JNXT");
                Temp3->instr_addr=Temp4;
                Temp4->Result=Result;
                Temp4->Operator=GetOperatorId("=");
                Temp4->Operand1=AddLiteral("1",0);
                ConcatNode(Current,Temp1);
                ConcatNode(Current,Temp2);
                ConcatNode(Current,Temp3);
                ConcatNode(Current,Temp4);

                }
            else if(OPERATOR==GetOperatorId(">"))
                {
                Optab *Temp1,*Temp2,*Temp3,*Temp4;
                char szLabelTrue[MAX_LABEL_LEN];
                Current->Operand1=Operand1;
                Current->Operand2=Operand2;
                Current->Operator=GetOperatorId("comp");
                
                SetDataType(Result,GetDataTypeId("int8"));
                Temp1=MakeSimpleNode();
                Temp2=MakeSimpleNode();
                Temp3=MakeSimpleNode();
                Temp4=MakeSimpleNode();
                Temp1->Result=-1;
                if(IsSigned(Operand1))
                Temp1->Operator=GetOperatorId("JG");
                else
                    Temp1->Operator=GetOperatorId("JA");
                AssignLabel(Temp1,Temp4);
                Temp2->Result=Result;
                Temp2->Operator=GetOperatorId("=");
                Temp2->Operand1=AddLiteral("0",0);
                
                Temp3->Operator=GetOperatorId("JMP_JNXT");
                Temp3->instr_addr=Temp4;
                Temp4->Result=Result;
                Temp4->Operator=GetOperatorId("=");
                Temp4->Operand1=AddLiteral("1",0);
                ConcatNode(Current,Temp1);
                ConcatNode(Current,Temp2);
                ConcatNode(Current,Temp3);
                ConcatNode(Current,Temp4);

                }
            else if(OPERATOR==GetOperatorId("=="))
                {
                Optab *Temp1,*Temp2,*Temp3,*Temp4;
                char szLabelTrue[MAX_LABEL_LEN];
                Current->Operand1=Operand1;
                Current->Operand2=Operand2;
                SetDataType(Result,GetDataTypeId("int8"));
                Current->Operator=GetOperatorId("comp");
                Current->Result=-1;
                Temp1=MakeSimpleNode();
                Temp2=MakeSimpleNode();
                Temp3=MakeSimpleNode();
                Temp4=MakeSimpleNode();
                Temp1->Result=-1;
                    Temp1->Operator=GetOperatorId("JE");
                AssignLabel(Temp1,Temp4);
                Temp2->Result=Result;
                Temp2->Operator=GetOperatorId("=");
                Temp2->Operand1=AddLiteral("0",0);
                
                Temp3->Operator=GetOperatorId("JMP_JNXT");
                Temp3->instr_addr=Temp4;
                Temp4->Result=Result;
                Temp4->Operator=GetOperatorId("=");
                Temp4->Operand1=AddLiteral("1",0);
                ConcatNode(Current,Temp1);
                ConcatNode(Current,Temp2);
                ConcatNode(Current,Temp3);
                ConcatNode(Current,Temp4);

                }
            else if(OPERATOR==GetOperatorId("!="))
                {
                Optab *Temp1,*Temp2,*Temp3,*Temp4;
                char szLabelTrue[MAX_LABEL_LEN];
                Current->Operand1=Operand1;
                SetDataType(Result,GetDataTypeId("int8"));
                Current->Operand2=Operand2;
                Current->Operator=GetOperatorId("comp");
                Current->Result=-1;
                Temp1=MakeSimpleNode();
                Temp2=MakeSimpleNode();
                Temp3=MakeSimpleNode();
                Temp4=MakeSimpleNode();
                Temp1->Result=-1;
                
                Temp1->Operator=GetOperatorId("JNE");
                
                AssignLabel(Temp1,Temp4);
                Temp2->Result=Result;
                Temp2->Operator=GetOperatorId("=");
                Temp2->Operand1=AddLiteral("0",0);
                
                Temp3->Operator=GetOperatorId("JMP_JNXT");
                Temp3->instr_addr=Temp4;
                Temp4->Result=Result;
                Temp4->Operator=GetOperatorId("=");
                Temp4->Operand1=AddLiteral("1",0);
                ConcatNode(Current,Temp1);
                ConcatNode(Current,Temp2);
                ConcatNode(Current,Temp3);
                ConcatNode(Current,Temp4);

                }
            if(OPERATOR==GetOperatorId("<="))
                {
                Optab *Temp1,*Temp2,*Temp3,*Temp4;
                char szLabelTrue[MAX_LABEL_LEN];
                Current->Operand1=Operand1;
                SetDataType(Result,GetDataTypeId("int8"));
                Current->Operand2=Operand2;
                Current->Operator=GetOperatorId("comp");
                Current->Result=-1;
                Temp1=MakeSimpleNode();
                Temp2=MakeSimpleNode();
                Temp3=MakeSimpleNode();
                Temp4=MakeSimpleNode();
                Temp1->Result=-1;
                if(IsSigned(Operand1))
                   Temp1->Operator=GetOperatorId("JLE");
                else
                    Temp1->Operator=GetOperatorId("JBE");
                AssignLabel(Temp1,Temp4);
                Temp2->Result=Result;
                Temp2->Operator=GetOperatorId("=");
                Temp2->Operand1=AddLiteral("0",0);
                
                Temp3->Operator=GetOperatorId("JMP_JNXT");
                Temp3->instr_addr=Temp4;
                Temp4->Result=Result;
                Temp4->Operator=GetOperatorId("=");
                Temp4->Operand1=AddLiteral("1",0);
                ConcatNode(Current,Temp1);
                ConcatNode(Current,Temp2);
                ConcatNode(Current,Temp3);
                ConcatNode(Current,Temp4);

                }
            else if(OPERATOR==GetOperatorId(">="))
                {
                Optab *Temp1,*Temp2,*Temp3,*Temp4;
                char szLabelTrue[MAX_LABEL_LEN];
                Current->Operand1=Operand1;
                Current->Operand2=Operand2;
                SetDataType(Result,GetDataTypeId("int8"));
                Current->Operator=GetOperatorId("comp");
                Current->Result=-1;
                Temp1=MakeSimpleNode();
                Temp2=MakeSimpleNode();
                Temp3=MakeSimpleNode();
                Temp4=MakeSimpleNode();
                Temp1->Result=-1;
                if(IsSigned(Operand1))
                Temp1->Operator=GetOperatorId("JGE");
                else
                    Temp1->Operator=GetOperatorId("JAE");
                AssignLabel(Temp1,Temp4);
                Temp2->Result=Result;
                Temp2->Operator=GetOperatorId("=");
                Temp2->Operand1=AddLiteral("0",0);
                
                Temp3->Operator=GetOperatorId("JMP_JNXT");
                Temp3->instr_addr=Temp4;
                Temp4->Result=Result;
                Temp4->Operator=GetOperatorId("=");
                Temp4->Operand1=AddLiteral("1",0);
                ConcatNode(Current,Temp1);
                ConcatNode(Current,Temp2);
                ConcatNode(Current,Temp3);
                ConcatNode(Current,Temp4);

                }
        //Temp info storage start
        strcpy(Current->Result_c,GetSymbolName(Current->Result));
        strcpy(Current->Operand1_c,GetSymbolName(Current->Operand1));
        strcpy(Current->Operand2_c,GetSymbolName(Current->Operand2));
        strcpy(Current->Operator_c,GetOperatorName(Current->Operator));
        //temp info storgae end
        
        Temp=ConcatNode(OPERAND1,OPERAND2);
        Temp=ConcatNode(Temp,Current);
        return Temp;
        }
         
Optab *GetLastNodeAddr(Optab *Block_Start)
     {
     Optab* LastNode;
     LastNode=Block_Start->previous;
     return LastNode;
     }
Optab* MakeElseIf(Optab *Condition ,Optab *Statement)
    {
    Optab *JUMP,*Temp,*Comp,*ClearRegs;
    JUMP=MakeSimpleNode();
    Comp=MakeSimpleNode();
    ClearRegs=MakeSimpleNode();
     ClearRegs->Operator=GetOperatorId("ClearRegs");
     ConcatNode(Statement,ClearRegs);
    Comp->Operator=GetOperatorId("comp");
    Comp->Operand1=GetResult(Condition);
    Comp->Operand2=AddLiteral("1",0);
    JUMP->instr_addr=GetLastNodeAddr(Statement);
    JUMP->Operator=GetOperatorId("JNE_JNXT"); 
    Temp=ConcatNode(Condition,Comp);
    Temp=ConcatNode(Temp,JUMP);
    Temp=ConcatNode(Temp,Statement);
    return Temp;
    }
Optab* MakeElseIfElse(Optab *Condition ,Optab *ElseIfStatement,Optab *ElseStatement)
    {
    Optab *JUMP1,*Temp,*JUMP2,*Comp,*ClearRegs,*ClearRegs2;
     JUMP1=MakeSimpleNode();
     JUMP1->Operator=GetOperatorId("JNE");
     JUMP1->instr_addr=ElseStatement;
     JUMP2=MakeSimpleNode();
     ClearRegs=MakeSimpleNode();
     ClearRegs->Operator=GetOperatorId("ClearRegs");
     ConcatNode(ElseIfStatement,ClearRegs);
     ClearRegs2=MakeSimpleNode();
     ClearRegs2->Operator=GetOperatorId("ClearRegs");
     ConcatNode(ElseStatement,ClearRegs2);
     Comp=MakeSimpleNode();
    Comp->Operator=GetOperatorId("comp");
    Comp->Operand1=GetResult(Condition);
    Comp->Operand2=AddLiteral("1",0);
     JUMP2->Operator=GetOperatorId("JMP_JNXT");
     Temp=ConcatNode(Condition,Comp);
     Temp=ConcatNode(Temp,JUMP1);
     Temp=ConcatNode(Temp,ElseIfStatement);
     Temp=ConcatNode(Temp,JUMP2);
     Temp=ConcatNode(Temp,ElseStatement);
     return Temp;
    }
Optab * MakeAddressOf(int iSymId)
{
	
	char symbolAddr[MAX_SYM_LEN+1];
	Optab * LpAddressNode;
	strcpy(symbolAddr,"&");
      strcat(symbolAddr,GetSymbolName(iSymId));
	  iSymId=AddSymbol(symbolAddr);
      SetDataType(iSymId,GetDataTypeId("AddressOf"));
      LpAddressNode=MakeNode(iSymId);
	  return LpAddressNode;
}
 Optab* MakeIfElseIf(Optab *Condition,Optab *Statement,Optab *IfElseIfStatement)
    {
    Optab *JUMP1,*JUMP2,*Temp,*Comp,*ClearRegs,*TestTemp,*ClearRegs2;
     JUMP1=MakeSimpleNode();
     TestTemp=Condition->previous->previous;
     JUMP1->instr_addr=IfElseIfStatement;
     JUMP1->Operator=GetOperatorId("JNE");
     JUMP2=MakeSimpleNode();
     Comp=MakeSimpleNode();
     ClearRegs=MakeSimpleNode();
     ClearRegs->Operator=GetOperatorId("ClearRegs");
	 ClearRegs2=MakeSimpleNode();
     ClearRegs2->Operator=GetOperatorId("ClearRegs");
     ConcatNode(Statement,ClearRegs);
    Comp->Operator=GetOperatorId("comp");
    Comp->Operand1=GetResult(Condition);
    Comp->Operand2=AddLiteral("1",0);
     JUMP2->Operator=GetOperatorId("JMP_JNXT");
	 Condition=ConcatNode(Condition,ClearRegs2);
     Temp=ConcatNode(Condition,Comp);
     Temp=ConcatNode(Temp,JUMP1);
     Temp=ConcatNode(Temp,Statement);
     Temp=ConcatNode(Temp,JUMP2);
     Temp=ConcatNode(Temp,IfElseIfStatement);
     BackPatch(Temp,Temp->previous);
     return Temp;
    }
 Optab* MakeElseIfElseIf(Optab *Condition,Optab *IfStatement,Optab* ElseIfStatement)
    {
     Optab *JUMP1,*JUMP2,*Temp,*Comp;
    JUMP1=MakeSimpleNode();
    JUMP1->Operator=GetOperatorId("JNE");
    JUMP1->instr_addr=ElseIfStatement;
    JUMP2=MakeSimpleNode();
    Comp=MakeSimpleNode();
    Comp->Operator=GetOperatorId("comp");
    Comp->Operand1=GetResult(Condition);
    Comp->Operand2=AddLiteral("1",0);
    JUMP2->Operator=GetOperatorId("JMP_JNXT");
    Temp=ConcatNode(Condition,Comp);
    Temp=ConcatNode(Temp,JUMP1);
    Temp=ConcatNode(Temp,IfStatement);
    Temp=ConcatNode(Temp,JUMP2);
    Temp=ConcatNode(Temp,ElseIfStatement);
    return Temp;
    }
 Optab* MakeAssignment(Optab* LHS ,Optab * RHS)
     {
     Optab *Result,*Operand;
     //=MakeNode(-1);
     Result=AddOperation(LHS,GetOperatorId("="),LHS,RHS);
     Operand=GetLastNodeAddr(Result);
     Operand->Operand1=Operand->Operand2; // Exchanging Operand1 and Operand2 coz in above addoperation we gave LHS as Operand1 instead of RHS
     Operand->Operand2=-1;
     
     strcpy(Operand->Operand1_c,Operand->Operand2_c);
     strcpy(Operand->Operand2_c,"");
     return Result;
     }
  Optab * MakeWhile(Optab *Condition ,Optab *Statement)
     {
     Optab *JUMP1,*Temp,*JUMP2,*Comp,*ClearRegs,*ClearRegs2;
     
     JUMP1=MakeSimpleNode();
     ClearRegs2=MakeSimpleNode();
     ClearRegs=MakeSimpleNode();
     JUMP2=MakeSimpleNode();
     JUMP1->instr_addr=ClearRegs;
     
     JUMP1->Operator=GetOperatorId("JNE_JNXT");
     JUMP2->instr_addr=Condition;
     JUMP2->Operator=GetOperatorId("JMP");
     AssignLabel(JUMP2,Condition);
     
     ClearRegs->Operator=GetOperatorId("ClearRegs");
     ClearRegs2->Operator=GetOperatorId("ClearRegs");
     
     Comp=MakeSimpleNode();
    Comp->Operator=GetOperatorId("comp");
    Comp->Operand1=GetResult(Condition);
    Comp->Operand2=AddLiteral("1",0);

     Temp=ConcatNode(Condition,ClearRegs2);
    Temp=ConcatNode(Temp,Comp);
     Temp=ConcatNode(Temp,JUMP1);
     Temp=ConcatNode(Temp,Statement);
     Temp=ConcatNode(Temp,JUMP2);
     Temp=ConcatNode(Temp,ClearRegs);
     BackPatchWhileLoop(Temp,GetLastNodeAddr(Temp),Temp);
     return Temp;
     }
  Optab * MakeIfThen(Optab *Condition ,Optab *Statement)
     {
     Optab *JUMP,*Temp,*Comp,*ClearRegs,*PreConditionClearReg2;
	 int conditionValue;
     JUMP=MakeSimpleNode();
     ClearRegs=MakeSimpleNode();
	 Comp=MakeSimpleNode();
	 
    
	 PreConditionClearReg2=MakeSimpleNode();
	 PreConditionClearReg2->Operator=GetOperatorId("ClearRegs");
     ClearRegs->Operator=GetOperatorId("ClearRegs");
	 conditionValue=GetResult(Condition);
	 Condition=ConcatNode(Condition,PreConditionClearReg2);
     ConcatNode(Statement,ClearRegs);
     JUMP->instr_addr=GetLastNodeAddr(Statement);
     JUMP->Operator=GetOperatorId("JNE_JNXT");
     
     Comp->Operator=GetOperatorId("comp");
	 
    Comp->Operand1=conditionValue;
    Comp->Operand2=AddLiteral("1",0);
     Temp=ConcatNode(Condition,Comp);
     Temp=ConcatNode(Temp,JUMP);
     Temp=ConcatNode(Temp,Statement);
     
     return Temp;
     }
   Optab* MakeStatementBlock(Optab * Statement1,Optab * Statement2)
      {
       Optab *Result;
      Result=ConcatNode(Statement1,Statement2);
      Last_Statement_Block=Result;
      return Result;
      }
   
  Optab* MakeIfThenElse(Optab* Condition,Optab* TrueStatement,Optab * FalseStatement)
      {
      Optab* JUMP1,*JUMP2,*Temp,*Comp,*ClearRegs,*ClearRegs2,*ClearRegs3;
     JUMP1=MakeSimpleNode();
     ClearRegs=MakeSimpleNode();
     ClearRegs->Operator=GetOperatorId("ClearRegs");
	 ClearRegs3=MakeSimpleNode();
     ClearRegs3->Operator=GetOperatorId("ClearRegs");
     ClearRegs2=MakeSimpleNode();
     ClearRegs2->Operator=GetOperatorId("ClearRegs");
     ConcatNode(TrueStatement,ClearRegs);
     ConcatNode(FalseStatement,ClearRegs2);
     JUMP1->Operator=GetOperatorId("JNE");
     JUMP1->instr_addr=FalseStatement;
     JUMP2=MakeSimpleNode();
     Comp=MakeSimpleNode();
     
    Comp->Operator=GetOperatorId("comp");
    Comp->Operand1=GetResult(Condition);
    Comp->Operand2=AddLiteral("1",0);
     JUMP2->Operator=GetOperatorId("JMP_JNXT");
     JUMP2->instr_addr=GetLastNodeAddr(FalseStatement);
	 Condition=ConcatNode(Condition,ClearRegs3);
     Temp=ConcatNode(Condition,Comp);
     Temp=ConcatNode(Temp,JUMP1);
     Temp=ConcatNode(Temp,TrueStatement);
     Temp=ConcatNode(Temp,JUMP2);
     Temp=ConcatNode(Temp,FalseStatement);
     
     return Temp;
      }

int GetOperatorId(char OPERATOR[LEN])
    {
    int i=0;
    for(i=0;i<OperatorTabLen;i++)
        {
        if(strcmpi(OperatorTab[i],OPERATOR)==0)
            return i;
        }
    return -1;
    }
int IsReference(int SymId)
    {
    char firstchar;
    firstchar=SymTab[SymId].Symbol[0];
    if(firstchar=='@')
        return 1;
    else
    return 0;
    }
/*
Function for array
*/
  Optab * MakeSingleExprSubscript(int Identifier,Optab * CurrentSubscriptExpr)
      {
       Optab * Temp,*Result,*TempResult;
       Optab * Operand1,*Operand2,*SizeCalcNode,*TempVar2,*TempOp1,*TempOp2;
      char symbolAddr[20],szDereferenceTemp[MAX_SYM_LEN],szLen[10];
      int SymTabPos,DataType;
      Operand2=NULL;
      strcpy(symbolAddr,"&");
      strcat(symbolAddr,GetSymbolName(Identifier));
      SymTabPos=AddSymbol(symbolAddr);
      Operand1=MakeNode(SymTabPos);
      SetDataType(Operand1->Result,GetDataTypeId("AddressOf"));
      
      Temp=MakeNode(SymTabPos);
      TempResult=GenerateTempVariable();
      
      SetDataType(TempResult->Result,GetDataTypeId("Pointer"));
	  SizeCalcNode=MakeSimpleNode();
	  TempVar2=GenerateTempVariable();
	  SetDataType(TempVar2->Result,GetDataTypeId("int8"));
	  SizeCalcNode->Result=TempVar2->Result;
	  SizeCalcNode->Operator=GetOperatorId("*");
	  DataType=GetDataType(Identifier);
	  itoa(GetDataTypeSize(DataType),szLen,10);
	  TempOp1=MakeNode(AddLiteral(szLen,0));
	  
SizeCalcNode=AddOperation(TempVar2,GetOperatorId("*"),TempOp1,CurrentSubscriptExpr);

	  Result=AddOperation(TempResult,GetOperatorId("+"),Operand1,SizeCalcNode);
      Temp=GetLastNodeAddr(Result);
      Temp->ArrayIndex=Identifier;
      Temp->SubscriptIndex=1;
      strcpy(szDereferenceTemp+1,GetSymbolName(TempResult->Result));
      szDereferenceTemp[0]='@';
      SymTabPos=AddSymbol(szDereferenceTemp);
      SetPointerTarget(SymTabPos,GetDataType(Identifier));
      SetStorage(SymTabPos,NONEStorage);
      TempResult=MakeNode(SymTabPos);
      Operand2=MakeNode(-1);
      Result=AddOperation(TempResult,GetOperatorId("DEREFERENCE"),Result,Operand2);
      
      return Result;
      }
  Optab * ObjectArray_FunctionCall(Optab * ArrayRef,int iFunctionID,Optab * Parameter,Optab *ParamList)
  {
	  int TargetDataType;
	  int iSymbol;
	  char szTempText[30];
	  Optab *LastNode,*FunctionCall;
	  
	  LastNode=GetLastNodeAddr(ArrayRef);
	  TargetDataType=GetPointerTarget(LastNode->Result);
	  SetPointerTarget(LastNode->Operand1,TargetDataType);

	  strcpy(szTempText,GetSymbolName(LastNode->Operand1));
	  strcat(szTempText,".");
	  strcat(szTempText,GetSymbolName(iFunctionID));
	  iSymbol=AddSymbol(szTempText);
	  if(Parameter==NULL)
	  {
		  FunctionCall=MakeFunctionCallNoParam(iSymbol);
	  }
	  else 
	  {
		  if(ParamList==NULL)
		  FunctionCall=MakeFunctionCallSingleParam(iSymbol,Parameter);
		  else
			  FunctionCall=MakeFunctionCallMultipleParam(iSymbol,ParamList,Parameter);

	  }
	  return ConcatNode(ArrayRef,FunctionCall);
	  

  }
  struct ArrayDimension * GetCurrentDimension(int Identifier,int count)
      {
      struct ArrayDimension* Temp;
      int Result,i;
      Result=1;
      Temp=GetDimension(Identifier);
      for(i=0;i<count-1;i++)
          {
			  Temp=Temp->LpNext;
	      
          }
	  return Temp;
      
      }
  Optab * MakeExprSubscript(Optab * PreviousSubscriptExpr,Optab * CurrentSubscriptExpr)
      {
      int CurrentIndex,PreviousResult,counter,ArrayIndex,SymTabPos,ID_Address_Symtab,iPreviousResult,iPointerTarget;
      char  CharTemp[20],szDereferenceTemp[MAX_SYM_LEN];

      Optab* Temp1,*Temp2,*Temp,*TempResult2,*TempResult,*ID_Address,*Result,*Operand2,*CurrentDim;
struct ArrayDimension *LpCurrentDimension;
     int iSymTabPos_CurrentDimension;
      
      Temp1=GetLastNodeAddr(PreviousSubscriptExpr);
      Temp1=DeleteNode(Temp1);
      PreviousResult=Temp1->Operand2;
      iPreviousResult=Temp1->Result;
      iPointerTarget=SymTab[iPreviousResult].PointerTarget;
      ID_Address_Symtab=Temp1->Operand1;
      ID_Address=MakeNode(ID_Address_Symtab);
      ArrayIndex=Temp1->ArrayIndex;
      CurrentIndex=Temp1->SubscriptIndex+1;
      LpCurrentDimension=GetCurrentDimension(ArrayIndex,CurrentIndex);
	  itoa(LpCurrentDimension->iDimension,CharTemp,10);
	  iSymTabPos_CurrentDimension=AddLiteral(CharTemp,0);
	  CurrentDim=MakeNode(iSymTabPos_CurrentDimension);
      Temp1=DeleteNode(Temp1);
      if(Temp1==NULL)
          {
          PreviousSubscriptExpr=MakeNode(PreviousResult);
          }
      SymTabPos=AddLiteral("1",0);
      SetDataType(SymTabPos,GetDataTypeId("_int_ltrl_8"));
      Temp=MakeNode(SymTabPos);
      TempResult=GenerateTempVariable();
      SetTempVariableInfo(TempResult,PreviousSubscriptExpr,Temp);
      Result=AddOperation(TempResult,GetOperatorId("-"),PreviousSubscriptExpr,Temp);
      
      TempResult=GenerateTempVariable();
      SetTempVariableInfo(TempResult,Result,CurrentDim);
      Temp=AddOperation(TempResult,GetOperatorId("*"),Result,CurrentDim);
      
      TempResult=GenerateTempVariable();
      SetTempVariableInfo(TempResult,Temp,CurrentSubscriptExpr);
      Result=AddOperation(TempResult,GetOperatorId("+"),Temp,CurrentSubscriptExpr);
      
      TempResult=GenerateTempVariable();
      SetTempVariableInfo(TempResult,ID_Address,Result);
      Temp=AddOperation(TempResult,GetOperatorId("+"),ID_Address,Result);
      
      
      Temp1=GetLastNodeAddr(Temp);
      Temp1->ArrayIndex=ArrayIndex;
      Temp1->SubscriptIndex=CurrentIndex;
      strcpy(szDereferenceTemp+1,GetSymbolName(TempResult->Result));
    szDereferenceTemp[0]='@';
    SymTabPos=AddSymbol(szDereferenceTemp);
    SetPointerTarget(SymTabPos,iPointerTarget);
    SetStorage(SymTabPos,NONEStorage);
    TempResult=MakeNode(SymTabPos);
    Operand2=MakeSimpleNode();
    Result=AddOperation(TempResult,GetOperatorId("DEREFERENCE"),Result,Operand2);
      return Result;
      /*Result=GetRangeMultipliedID(ArrayIndex,CurrentIndex);
      SymTabPos=AddSymbol(itoa(Result,CharTemp,10));
      Temp1=MakeNode(SymTabPos);
      Temp2=MakeNode(PreviousResult);
      
      TempResult=GenerateTempVariable();
      Temp=AddOperation(TempResult,GetOperatorId("*"),CurrentSubscriptExpr,Temp1);
      TempResult2=GenerateTempVariable();
      TempResult=AddOperation(TempResult2,GetOperatorId("+"),Temp,Temp2);
      Temp1=GetLastNodeAddr(TempResult);
      Temp1->ArrayIndex=ArrayIndex;
      Temp1->SubscriptIndex=CurrentIndex;
      Temp=ConcatNode(PreviousSubscriptExpr,TempResult);
      return Temp;
      */

      }
  
  struct OMFunction * GetFunctionInformation(char *LpszClassName,char *LpszFunctionName,Optab *ActualParameters)
  {
	  struct ClassDefinition *LpClassDefn;
	  struct OMFunction *LpCurrentFunction;
	  Optab *ActualParamStart;
	  struct SDataTypeList *LpCurrentFormalParam;
	  int iDataType_FormalParam,iDataType_ActualParam,found;
	  LpCurrentFunction=NULL;
	  found=0;
	  ActualParamStart=ActualParameters;
	  LpClassDefn=NULL;
	  LpClassDefn=GetClassInformation(LpszClassName);
	  if(LpClassDefn!=NULL)
		  LpCurrentFunction=LpClassDefn->m_LpMemberFun;
	  while(LpCurrentFunction!=NULL) // have to check for Function overloading
	  {
		  if(strcmp(LpCurrentFunction->m_szFunctionName,LpszFunctionName)==0)
		  {
			  LpCurrentFormalParam=LpCurrentFunction->m_LpFormalParameter;
			  while(1)
			  {
				  
				  if((LpCurrentFormalParam==NULL)&&(ActualParameters!=ActualParamStart))
					  break;
				  if((LpCurrentFormalParam==NULL)&&(ActualParameters==NULL))
				  {
					  found=1;
					  break;
				  }
				  iDataType_FormalParam=LpCurrentFormalParam->m_iDataType;
				  while(ActualParameters->Operator!=GetOperatorId("PUSH_FUN_PAR"))
				  {
					  ActualParameters=ActualParameters->next;
				  }
				  if(IsLiteral(ActualParameters->Operand1))
				  {
					  if(CheckLiteralCompatability(ActualParameters->Operand1,iDataType_FormalParam)==0)
					  {
                          
						  break;
					  }
                      else
                      {
                          if((GetDataType(ActualParameters->Operand1)==GetDataTypeId("_int_ltrl_8"))
                              &&(iDataType_FormalParam==GetDataTypeId("int16")))
                          {
                              SetDataType(ActualParameters->Operand1,GetDataTypeId("_int_ltrl_16"));

                          }
                          else if((GetDataType(ActualParameters->Operand1)==GetDataTypeId("_int_ltrl_16"))
                              &&(iDataType_FormalParam==GetDataTypeId("int32")))
                          {
                              SetDataType(ActualParameters->Operand1,GetDataTypeId("_int_ltrl_32"));

                          }
                          else if((GetDataType(ActualParameters->Operand1)==GetDataTypeId("_int_ltrl_8"))
                              &&(iDataType_FormalParam==GetDataTypeId("int32")))
                          {
                              SetDataType(ActualParameters->Operand1,GetDataTypeId("_int_ltrl_32"));

                          }
                      }
				  }
				  else
				  {
					  iDataType_ActualParam=GetDataType(ActualParameters->Operand1);
					  if(iDataType_ActualParam!=iDataType_FormalParam)
						break;
				  }
				  LpCurrentFormalParam=LpCurrentFormalParam->m_LpNext;
				  ActualParameters=ActualParameters->next;
				  if((ActualParameters==ActualParamStart)&&(LpCurrentFormalParam!=NULL))
					  break;
				  if((ActualParameters==ActualParamStart)&&(LpCurrentFormalParam==NULL))
				  {
					  found=1;
					  break;
				  }
			  }
			  if(found==1)
				  return LpCurrentFunction;
			  
		  }
		  LpCurrentFunction=LpCurrentFunction->m_LpNext;
	  }
	  return NULL;
		  
  }
  Optab* MakeFunctionCallSingleParam(int FunctionID, Optab* Parameter)
      {
      Optab * Operand2,*Result,*FunctionName,*FunctionResult,*TempResult,*SetEBX,*UnSetEBX,*ActualParam;
      char  FunctionResultName[50],szObjectNameBuf[MAX_SYM_LEN],szErrMsg[40];
	  char *LpszFunctionName,*LpszDataType;
	  struct OMFunction *LpCurrentFunction;
      int SymId,FunctionTableId,iMember;
	  szObjectNameBuf[0]='\0';
	  LpszFunctionName=GetSymbolName(FunctionID);
	  TempResult=MakeNode(-1);
	  
	  if(strcmp(LpszFunctionName,"print_int_win")==0)
	  {
		  Result=MakeNode(-1);
		  Result->Operand1=GetSymbolId("print_int_win");
		  Result->Operator=GetOperatorId("CALL");
		  Result->Operand2=GetResult(Parameter);
		  return ConcatNode(Parameter,Result);
	  }
      if(strcmp(LpszFunctionName,"print_addr_win")==0)
	  {
		  Result=MakeNode(-1);
		  Result->Operand1=GetSymbolId("print_addr_win");
		  Result->Operator=GetOperatorId("CALL");
		  Result->Operand2=GetResult(Parameter);
		  return ConcatNode(Parameter,Result);
	  }
	  if(strcmp(LpszFunctionName,"fprint_int_win")==0)
	  {
		  Result=MakeNode(-1);
		  Result->Operand1=GetSymbolId("fprint_int_win");
		  Result->Operator=GetOperatorId("CALL");
		  Result->Operand2=GetResult(Parameter);
		  return ConcatNode(Parameter,Result);
	  }
	  if(strcmp(LpszFunctionName,"print_ascii_os")==0)
	  {
		  Result=MakeNode(-1);
		  Result->Operand1=GetSymbolId("print_ascii_os");
		  Result->Operator=GetOperatorId("CALL");
		  Result->Operand2=GetResult(Parameter);
		  return ConcatNode(Parameter,Result);
	  }
      if(strcmp(LpszFunctionName,"print_str_win")==0)
	  {
		  Result=MakeNode(-1);
		  Result->Operand1=GetSymbolId("print_str_win");
		  Result->Operator=GetOperatorId("CALL");
		  Result->Operand2=GetResult(Parameter);
		  return ConcatNode(Parameter,Result);
	  }
	  ActualParam=MakeSimpleDataNode(-1,GetOperatorId("PUSH_FUN_PAR"),GetResult(Parameter),-1);
	  iMember=IsMemberCall(LpszFunctionName);
      if(iMember<=0)
	  {
		  LpCurrentFunction=GetFunctionInformation(szCurrentClass,LpszFunctionName,ActualParam);
	  }
	  else
	  {
		  strncpy(szObjectNameBuf,LpszFunctionName,iMember);
		  szObjectNameBuf[iMember]='\0';
		  LpszDataType=GetDataTypeName(GetDatatype(szObjectNameBuf));
		  if(strcmp(LpszDataType,"Pointer")==0)
		  {
			 LpszDataType= GetDataTypeName(GetPointerTarget(GetSymbolId(szObjectNameBuf)));
		  }
		  LpCurrentFunction=GetFunctionInformation(LpszDataType,LpszFunctionName+iMember+1,ActualParam);
	  }
	  if(LpCurrentFunction==NULL)
	  {
	  strcpy(szErrMsg,"Function:");
	  strcat(szErrMsg,LpszFunctionName);
	  strcat(szErrMsg," not found");
	  ErrorHandler(ERROR,szErrMsg);
	  }
	  //FunctionTableId=SearchFunctionTable(GetSymbolName(FunctionID));
	  if(LpCurrentFunction->iReturnType!=0)
          {
      strcpy(FunctionResultName,"_Result.");
	  strcat(FunctionResultName,LpCurrentFunction->m_szFunctionLabel);
      SymId=AddSymbol(FunctionResultName);
	  SetDataType(SymId,LpCurrentFunction->iReturnType);
	  SetStorage(SymId,LocalStorage);
      TempResult=MakeNode(SymId);
	  }
      
      if(LpCurrentFunction!=NULL)
		FunctionName=MakeNode(AddSymbol(LpCurrentFunction->m_szFunctionLabel));
	  
      Result=MakeNode(-1);
	  if(iMember>0)
	  SetEBX=MakeSimpleDataNode(-1,GetOperatorId("SetEBX"),GetSymbolId(szObjectNameBuf),-1);
      if(Func_Start==NULL)
          Func_Start=SetEBX;
	  Result=MakeNode(-1);
	  Operand2=MakeNode(-1);
	  
      Result=ConcatNode(Parameter,ActualParam);
	  if(iMember>0)
	  Result=ConcatNode(SetEBX,Result);
      FunctionResult=AddOperation(TempResult,GetOperatorId("CALL"),FunctionName,Operand2);
	  if(iMember>0)
	  {
		  UnSetEBX=MakeSimpleDataNode(-1,GetOperatorId("UnSetEBX"),-1,-1);
		  FunctionResult=ConcatNode(FunctionResult,UnSetEBX);
	  }
      Result=ConcatNode(Result,FunctionResult);
      if(Func_Start==NULL)
          Func_Start=Result;
      return Result;
      }
  
  Optab* MakeFunctionCallAddParam(Optab *FirstExpression,  Optab * SecondExpression)
      {
      Optab * Operand2,*Result;
      Operand2=MakeNode(-1);
      Result=MakeNode(-1);
      Result=AddOperation(Result,GetOperatorId("PUSH_FUN_PAR"),SecondExpression,Operand2);
      Result=ConcatNode(FirstExpression,Result);
      return Result;
      }
  Optab * MakeFunctionCallAddFirstParam(Optab *FirstParam)
      {
      Optab * Operand2,*Result;
      Operand2=MakeNode(-1);
      Result=MakeNode(-1);
      Result=AddOperation(Result,GetOperatorId("PUSH_FUN_PAR"),FirstParam,Operand2);

      return Result;
      }
  Optab* MakeFunctionCallNoParam(int FunctionID)
  {
	  Optab * Operand2,*Result,*FunctionName,*FunctionResult,*TempResult,*SetEBX,*UnSetEBX,*ActualParam;
      char  FunctionResultName[50],szObjectNameBuf[MAX_SYM_LEN],szErrMsg[40];
	  char *LpszFunctionName,*LpszDataType;
	  struct OMFunction *LpCurrentFunction;
      int SymId,FunctionTableId,iMember;
	  szObjectNameBuf[0]='\0';
	  ActualParam=NULL;
	  LpszFunctionName=GetSymbolName(FunctionID);
	  TempResult=MakeNode(-1);
	  iMember=IsMemberCall(LpszFunctionName);
      if(iMember<=0)
	  {
		  LpCurrentFunction=GetFunctionInformation(szCurrentClass,LpszFunctionName,ActualParam);
	  }
	  else
	  {
		  strncpy(szObjectNameBuf,LpszFunctionName,iMember);
		  szObjectNameBuf[iMember]='\0';
		  LpszDataType=GetDataTypeName(GetDatatype(szObjectNameBuf));
		  if(strcmp(LpszDataType,"Pointer")==0)
		  {
			 LpszDataType= GetDataTypeName(GetPointerTarget(GetSymbolId(szObjectNameBuf)));
		  }
		  LpCurrentFunction=GetFunctionInformation(LpszDataType,LpszFunctionName+iMember+1,ActualParam);
	  }
	  //FunctionTableId=SearchFunctionTable(GetSymbolName(FunctionID));
	  if(LpCurrentFunction==NULL)
	  {
	  strcpy(szErrMsg,"Function:");
	  strcat(szErrMsg,LpszFunctionName);
	  strcat(szErrMsg," not found");
	  ErrorHandler(ERROR,szErrMsg);
	  }
	  if(LpCurrentFunction==NULL)
	  {

	  }
	  if(LpCurrentFunction->iReturnType!=0)
          {
      strcpy(FunctionResultName,"_Result.");
	  strcat(FunctionResultName,LpCurrentFunction->m_szFunctionLabel);
      SymId=AddSymbol(FunctionResultName);
	  SetDataType(SymId,LpCurrentFunction->iReturnType);
	  SetStorage(SymId,LocalStorage);
      TempResult=MakeNode(SymId);
	  }
      
      if(LpCurrentFunction!=NULL)
		FunctionName=MakeNode(AddSymbol(LpCurrentFunction->m_szFunctionLabel));
	  
      Result=MakeNode(-1);
	  if(iMember>0)
	  SetEBX=MakeSimpleDataNode(-1,GetOperatorId("SetEBX"),GetSymbolId(szObjectNameBuf),-1);
      if(Func_Start==NULL)
          Func_Start=SetEBX;
	  Result=MakeNode(-1);
	  Operand2=MakeNode(-1);
	  if(iMember>0)
	  Result=SetEBX;
      FunctionResult=AddOperation(TempResult,GetOperatorId("CALL"),FunctionName,Operand2);
	  if(iMember>0)
	  {
		  UnSetEBX=MakeSimpleDataNode(-1,GetOperatorId("UnSetEBX"),-1,-1);
		  FunctionResult=ConcatNode(FunctionResult,UnSetEBX);
	  }
      Result=ConcatNode(Result,FunctionResult);
      
      return Result;
  }
  Optab* MakeFunctionCallMultipleParam(int FunctionID,Optab * Parameters,Optab *LastParameter)
      {
      Optab * Result,*FunctionResult,*FunctionName,*Operand2,*TempResult,*SetEBX,*UnSetEBX;
      char  FunctionResultName[MAX_FUNCTION_LABEL_LEN+8],*LpszFunctionName,szObjectNameBuf[MAX_VARIABLE_LEN],*LpszDataType;
	  struct OMFunction *LpCurrentFunction;
      int SymId,FunctionTableId,iMember;
      szObjectNameBuf[0]='\0';
	  TempResult=MakeSimpleNode();
	  Result=MakeFunctionCallAddParam(Parameters,LastParameter);
	  LpszFunctionName=GetSymbolName(FunctionID);
	  iMember=IsMemberCall(LpszFunctionName);

      if(iMember<=0)
	  {
		  LpCurrentFunction=GetFunctionInformation(szCurrentClass,LpszFunctionName,Result);
	  }
	  else
	  {
		  strncpy(szObjectNameBuf,LpszFunctionName,iMember);
		  szObjectNameBuf[iMember]='\0';
		  LpszDataType=GetDataTypeName(GetDatatype(szObjectNameBuf));
		  if(strcmp(LpszDataType,"Pointer")==0)
		  {
			 LpszDataType= GetDataTypeName(GetPointerTarget(GetSymbolId(szObjectNameBuf)));
		  }
		  LpCurrentFunction=GetFunctionInformation(LpszDataType,LpszFunctionName+iMember+1,Result);
	  }
      
      if(LpCurrentFunction!=NULL)
		FunctionName=MakeNode(AddSymbol(LpCurrentFunction->m_szFunctionLabel));
	  
      
	  if(LpCurrentFunction->iReturnType!=0)
          {
			  strcpy(FunctionResultName,"_Result.");
			strcat(FunctionResultName,LpCurrentFunction->m_szFunctionLabel);
		SymId=AddSymbol(FunctionResultName);
		TempResult=MakeNode(SymId);
            SetDataType(SymId,LpCurrentFunction->iReturnType);
			SetStorage(SymId,LocalStorage);
          }
      
      
      if(iMember>0)
		  SetEBX=MakeSimpleDataNode(-1,GetOperatorId("SetEBX"),GetSymbolId(szObjectNameBuf),-1);
	  
	  if(iMember>0)
	  Result=ConcatNode(SetEBX,Result);
	  Operand2=MakeNode(-1);
      FunctionResult=AddOperation(TempResult,GetOperatorId("CALL"),FunctionName,Operand2);
	  if(iMember>0)
	  {
		  UnSetEBX=MakeSimpleDataNode(-1,GetOperatorId("UnSetEBX"),-1,-1);
		  FunctionResult=ConcatNode(FunctionResult,UnSetEBX);
	  }
      return ConcatNode(Result,FunctionResult);
      }
  void AddOutputASM(char * LpszLabel,char *LpszInstruction)
      {
      
		  //strcpy(OutputAsm[iOutputAsmCount].szAsmStatement,LpszInstruction);
      //OutputAsm[iOutputAsmCount].szLabel=LpszLabel;
      /*
      if(LpszLabel!=NULL)
          {
          strcpy(OutputAsm[iOutputAsmCount].szLabel,LpszLabel);
          if(strlen(LpszLabel)>1)
          strcat(OutputAsm[iOutputAsmCount].szLabel,":");
          LpszLabel=NULL;
          }
      else
          strcpy(OutputAsm[iOutputAsmCount].szLabel,"");

      */
	  
  //    iOutputAsmCount++;
	  if ((LpszLabel==NULL)||((strlen(LpszLabel)==0)))
          fprintf(fpOutputFile,"%s",LpszInstruction);
          else
              fprintf(fpOutputFile,"%s: %s",LpszLabel,LpszInstruction);
	  if(iOutputAsmCount>=MaxOutputAsmStatement)
	  {

		  ErrorHandler(ERROR,"Maximum Number of ASM statements reached..");
		  return;
	  }
      }
  
  int IsConst(int SymId)
      {
      if(SymTab[SymId].DataType==GetDataTypeId("_int_ltrl"))
          return 1;
      return 0;
      }
  
  
  
  
  
  int Chosex86Register(int iCurrent)
      {
      char szAsmInstruction[100],*LpszLabel=NULL,szTempItoaBuf[15],szTempSymbol[MAX_SYM_LEN];
      enum i386Register regs;
      int index,found,iSize,iOrginalSymbol;
	  int lowestRank;
	  lowestRank=30000;
      index=-1;
      found=0;
      if(IsReference(iCurrent))
    {
    
    iSize=GetDataTypeSize(SymTab[iCurrent].PointerTarget);
    iSize=iSize*8;
    }
      else  if((GetDataType(iCurrent)==GetDataTypeId("uint8"))||(GetDataType(iCurrent)==GetDataTypeId("int8"))||(GetDataType(iCurrent)==GetDataTypeId("_int_ltrl_8")))
          iSize=8;
      else if((GetDataType(iCurrent)==GetDataTypeId("uint16"))||(GetDataType(iCurrent)==GetDataTypeId("int16"))||(GetDataType(iCurrent)==GetDataTypeId("char"))||(GetDataType(iCurrent)==GetDataTypeId("_int_ltrl_16")))
          iSize=16;
      else if((GetDataType(iCurrent)==GetDataTypeId("uint32"))||(GetDataType(iCurrent)==GetDataTypeId("int32"))||(GetDataType(iCurrent)==GetDataTypeId("_int_ltrl_32"))||(GetDataType(iCurrent)==GetDataTypeId("AddressOf"))||(GetDataType(iCurrent)==GetDataTypeId("Pointer")))
          iSize=32;

if(iSize==8)
          {
			  
			 // lowestRank=x86RegSet[ah].Rank;
          for(regs=ah;regs<=dl;regs++)
              {
              
              if(x86RegSet[regs].locked==false)
                  {
                  
                  	  if(lowestRank>x86RegSet[regs].Rank)
					  {
						  index=regs;
						  lowestRank=x86RegSet[regs].Rank;
					  }
                  }
              if(x86RegSet[regs].Register==iCurrent)
			  {
				#if (CHECK_DEBUG_ENABLED(DEBUG_REGISTER_OPTIMIZATION))
				  printf("\n---Register Optimization carried out for Register:%s for Value:%s---\n",Getx86RegisterName(regs),GetSymbolName(iCurrent));
				#endif
				  return -regs;
			  }
                  
              }
          return index;
          }
      if(iSize==16)
          {
			  
//			  lowestRank=x86RegSet[ax].Rank;
          for(regs=ax;regs<=dx;regs++)
              {
              
              if(x86RegSet[regs].locked==false)
                  {
					  if(lowestRank>x86RegSet[regs].Rank)
					  {
lowestRank=x86RegSet[regs].Rank;
						  index=regs;
					  }
                  
                  }
              if(x86RegSet[regs].Register==iCurrent)
			  {
				 #if (CHECK_DEBUG_ENABLED(DEBUG_REGISTER_OPTIMIZATION))
				  printf("\n---Register Optimization carried out for Register:%s for Value:%s---\n",Getx86RegisterName(regs),GetSymbolName(iCurrent));
				#endif
				  return -regs;
			  }
              }
          return index;
          }
      if(iSize==32)
          {
			   
			  //lowestRank=x86RegSet[EAX].Rank;
          for(regs=EAX;regs<=EDX;regs++)
              {
              
              if(x86RegSet[regs].locked==false)
                  {
                  if(lowestRank>x86RegSet[regs].Rank)
				  {lowestRank=x86RegSet[regs].Rank;
					  index=regs;
				  }
                  }
              if(x86RegSet[regs].Register==iCurrent)
			  {
				  #if (CHECK_DEBUG_ENABLED(DEBUG_REGISTER_OPTIMIZATION))
				  printf("\n---Register Optimization carried out for Register:%s for Value:%s---\n",Getx86RegisterName(regs),GetSymbolName(iCurrent));
				#endif
				  return -regs;
			  }
              }
          }
	  if(index==-1)
		  ErrorHandler(ERROR,"No available register to store data");
      return index;
      }
   struct Operand SetMemoryOperand(int SymTabPos)
       {
       struct Operand MemoryOperand;
       char szTempSymbolBuf[MAX_SYM_LEN];
       int OrginalSymbol;
       MemoryOperand.IsValid=true;
       MemoryOperand.IsImmediate=0;
       MemoryOperand.ImmediateValue=0;
       MemoryOperand.IsIndirectAddress=false;
       MemoryOperand.SymTabPos=SymTabPos;
       MemoryOperand.SegmentRegister=NoRegister;
	   MemoryOperand.IsRegister=0;
       MemoryOperand.IsLabel=0;
       MemoryOperand.Register=-1;
	   
       if(GetDataType(SymTabPos)==GetDataTypeId("AddressOf"))
           {
           MemoryOperand.IsMemoryAddress=true;
           MemoryOperand.IsIndirectAddress=false;
           strcpy(szTempSymbolBuf,GetSymbolName(SymTabPos));
           OrginalSymbol=GetSymbolId(szTempSymbolBuf+1);
           if (GetScope(OrginalSymbol)==LocalScope)
               {
               MemoryOperand.IndexRegister=EBP;
               MemoryOperand.HasIndex=true;
               }
		   else if (GetScope(OrginalSymbol)==GlobalScope)
               {
				   MemoryOperand.IsLabel=true;
               strcpy(MemoryOperand.szLabel,GetSymbolName(SymTabPos)+1);
			   MemoryOperand.IsMemoryAddress=false;
			   MemoryOperand.IsReference=false;
               }
		   else
		   {
			   MemoryOperand.IndexRegister=EBX;
			   MemoryOperand.HasIndex=true;
		   }
           MemoryOperand.MemoryAddress=GetSymbolAddress(OrginalSymbol);
           MemoryOperand.IsReference=false;
           MemoryOperand.IsLiteral=false;
           }
       else if(IsReference(SymTabPos))
           {
           MemoryOperand.IsIndirectAddress=true;
           strcpy(szTempSymbolBuf,GetSymbolName(SymTabPos));
           OrginalSymbol=GetSymbolId(szTempSymbolBuf+1);
           MemoryOperand.SymTabPos=OrginalSymbol;
           if (GetScope(OrginalSymbol)==LocalScope)
               {
               MemoryOperand.IndexRegister=EBP;
               MemoryOperand.HasIndex=true;
               }
		   else if (GetScope(OrginalSymbol)==ObjectScope)
                {
					MemoryOperand.HasIndex=true;
                MemoryOperand.IndexRegister=EBX;
                /*MemoryOperand.SegmentRegister=ds;
                MemoryOperand.HasIndex=false;*/
                }
           MemoryOperand.IsReference=true;
           MemoryOperand.IsImmediate=false;
           MemoryOperand.IsMemoryAddress=false;
           MemoryOperand.IsLiteral=false;
           }
       else if(IsLiteral(SymTabPos))
           {
           char szTemp[10];
           MemoryOperand.IsLiteral=true;
           MemoryOperand.IsImmediate=true;
           strcpy(szTemp,GetLiteralValue(SymTabPos,0));
           MemoryOperand.ImmediateValue=atoi(szTemp);
           MemoryOperand.SymTabPos=SymTabPos;
           MemoryOperand.IsIndirectAddress=false;
           MemoryOperand.IsMemoryAddress=false;
           MemoryOperand.IsReference=false;
           
           }
       else if(GetDataType(SymTabPos)==GetDataTypeId("int_imm"))
           {
           MemoryOperand.IsImmediate=true;
           MemoryOperand.ImmediateValue=atoi(GetSymbolName(SymTabPos));
           MemoryOperand.IsMemoryAddress=false;
           MemoryOperand.IsIndirectAddress=false;
           MemoryOperand.IsReference=false;
           MemoryOperand.HasIndex=0;
           }
	   else if(GetScope(SymTabPos)==GlobalScope)
	   {
		   MemoryOperand.IsLabel=1;
		   MemoryOperand.IsReference=true;
		   strcpy(MemoryOperand.szLabel,GetSymbolName(SymTabPos));
	   }
       else
           {
            MemoryOperand.IsMemoryAddress=true;
            MemoryOperand.IsIndirectAddress=false;
            MemoryOperand.IsReference=true;
            MemoryOperand.IsLiteral=false;
            MemoryOperand.MemoryAddress=GetSymbolAddress(SymTabPos);
            if (GetScope(SymTabPos)==LocalScope)
                {
                MemoryOperand.HasIndex=true;
                MemoryOperand.IndexRegister=EBP;
                }
            else if (GetScope(SymTabPos)==ObjectScope)
                {
					MemoryOperand.HasIndex=true;
                MemoryOperand.IndexRegister=EBX;
                /*MemoryOperand.SegmentRegister=ds;
                MemoryOperand.HasIndex=false;*/
                }
           }
       
       
       return MemoryOperand;
       }
   struct Operand SetRegisterOperand(int RegisterVal)
       {
       struct Operand RegisterOperand;
       RegisterOperand.IsValid=true;
       RegisterOperand.IsRegister=1;
       RegisterOperand.IsMemoryAddress=false;
       RegisterOperand.IsImmediate=0;
       RegisterOperand.IsIndirectAddress=false;
       RegisterOperand.IsLiteral=false;
       RegisterOperand.IsIndirectAddress=false;
       RegisterOperand.Register=RegisterVal;
       RegisterOperand.HasIndex=0;
       RegisterOperand.IsReference=false;
       
       return RegisterOperand;
       }
   /*struct Operand SetImmediateOperand(int Value)
       {
       struct Operand ImmediateOperand;
       ImmediateOperand.IsImmediate=true;
       ImmediateOperand.ImmediateValue=Value;
       ImmediateOperand.IsMemoryAddress=false;
       ImmediateOperand.IsIndirectAddress=false;
       ImmediateOperand.IsMemory=false;
       ImmediateOperand.IsReference=false;
       ImmediateOperand.IsRegister=0;
       ImmediateOperand.HasIndex=0;
       return ImmediateOperand;
       }*/
  void Generatex86Instruction(int Opcode,enum memorysize Size,struct Operand Operand1,struct Operand Operand2,char *LpszInstructionBuf)
      {
      char SymbolAddress[8],szRegisterName[7];
      char szTempBuf[10];
      int iSymbolAddress,RegisterId1,RegisterId2;
      
      RegisterId1=-1;
      RegisterId2=-1;
      strcpy(LpszInstructionBuf,"");
	  if(Operand2.IsLabel==true)
	  {
		  strcpy(LpszInstructionBuf,"mov ");
		  strcat(LpszInstructionBuf,memorysize_s[Size]);
		  strcat(LpszInstructionBuf,Getx86RegisterName(Operand1.Register));
		  strcat(LpszInstructionBuf,",");
		  if(Operand2.IsReference==true)
			  strcat(LpszInstructionBuf,"[");
		  strcat(LpszInstructionBuf,Operand2.szLabel);
		  if(Operand2.IsReference==true)
			  strcat(LpszInstructionBuf,"]");
		  strcat(LpszInstructionBuf,"\n");
return;

	  }
      if(Operand1.IsValid==true)
      if(Operand1.IsIndirectAddress==true)
          {
          int IsRef;
          RegisterId1=GetRegister(32);
          SetRegister(RegisterId2,-1,1);
          strcpy(LpszInstructionBuf,"mov dword ");
          strcat(LpszInstructionBuf,Getx86RegisterName(RegisterId1));
          strcat(LpszInstructionBuf,",");
          //SetRegister(RegisterId1,-1,1);
          strcat(LpszInstructionBuf,"[");
          if(Operand1.SegmentRegister!=NoRegister)
              {
              strcat(LpszInstructionBuf,Getx86RegisterName(Operand1.SegmentRegister));
              strcat(LpszInstructionBuf,":");
              }
          if(Operand1.HasIndex==true)
              {
              strcat(LpszInstructionBuf,Getx86RegisterName(Operand1.IndexRegister));
			  if(Operand1.IndexRegister==EBP)
				strcat(LpszInstructionBuf,"-");
			  else if(Operand1.IndexRegister==EBX)
				strcat(LpszInstructionBuf,"+");
              }
          if(Operand1.IsRegister==true)
              {
              strcat(LpszInstructionBuf,Getx86RegisterName(Operand1.Register));
              }
          else
              {
              strcat(LpszInstructionBuf,"0x");
              iSymbolAddress=GetSymbolAddress(Operand1.SymTabPos);
              itoa(iSymbolAddress,SymbolAddress,16);
              strcat(LpszInstructionBuf,SymbolAddress);
              }
          strcat(LpszInstructionBuf,"]\n");
          IsRef=Operand1.IsReference;
          Operand1=SetRegisterOperand(RegisterId1);
          if(IsRef==true)
          Operand1.IsReference=true;
          
          }
if(Operand2.IsValid==true)
      if(Operand2.IsIndirectAddress==true)
          {
          int IsRef;
		  if(!IsRegisterLocked(ESI))
			  RegisterId2=ESI;
		  else
          RegisterId2=GetRegister(32);
          SetRegister(RegisterId2,-1,0);
          strcpy(LpszInstructionBuf,"mov dword ");
          strcat(LpszInstructionBuf,Getx86RegisterName(RegisterId2));
          strcat(LpszInstructionBuf,",");
          SetRegister(RegisterId2,-1,1);
          strcat(LpszInstructionBuf,"[");
          if(Operand2.SegmentRegister!=NoRegister)
              {
              strcat(LpszInstructionBuf,Getx86RegisterName(Operand2.SegmentRegister));
              strcat(LpszInstructionBuf,":");
              }
          if(Operand2.HasIndex==true)
              {
              strcat(LpszInstructionBuf,Getx86RegisterName(Operand2.IndexRegister));
			  if(Operand2.IndexRegister==EBP)
				strcat(LpszInstructionBuf,"-");
			  else if(Operand2.IndexRegister==EBX)
				strcat(LpszInstructionBuf,"+");
                            }
          if(Operand2.IsRegister==true)
              {
              strcat(LpszInstructionBuf,Getx86RegisterName(Operand2.Register));
              }
          else
              {
              strcat(LpszInstructionBuf,"0x");
              iSymbolAddress=GetSymbolAddress(Operand2.SymTabPos);
              itoa(iSymbolAddress,SymbolAddress,16);
              strcat(LpszInstructionBuf,SymbolAddress);
              }
          strcat(LpszInstructionBuf,"]\n");
          IsRef=Operand2.IsReference;
          Operand2=SetRegisterOperand(RegisterId2);
          if(IsRef==true)
          Operand2.IsReference=true;
          
          }
      if(Operand1.IsValid==true)
      if(Operand1.IsMemoryAddress==true)
          {
          if(Operand1.IsReference==false)
              {
              strcat(LpszInstructionBuf,"mov dword ");
			  if(!IsRegisterLocked(EDI))
				  RegisterId1=EDI;
			  else
              RegisterId1=GetRegister(32);
              SetRegister(RegisterId1,-1,0);
              strcat(LpszInstructionBuf,Getx86RegisterName(RegisterId1));
              strcat(LpszInstructionBuf,",0x");
              strcat(LpszInstructionBuf,itoa(Operand1.MemoryAddress,SymbolAddress,16));
              strcat(LpszInstructionBuf,"\n");
              if(Operand1.HasIndex==true)
                  {
                  strcat(LpszInstructionBuf,"add ");
                  strcat(LpszInstructionBuf,Getx86RegisterName(RegisterId1));
                  strcat(LpszInstructionBuf,",");
                  strcat(LpszInstructionBuf,Getx86RegisterName(Operand1.IndexRegister));
                  strcat(LpszInstructionBuf,"\n");
                  }
              Operand1=SetRegisterOperand(RegisterId1);
          Operand1.IsReference=false;
              }
          
          }

      if(Operand2.IsValid==true)
      if(Operand2.IsMemoryAddress==true)
          {
          if(Operand2.IsReference==false)
              {
              RegisterId1=GetRegister(32);
              SetRegister(RegisterId1,-1,0);
              if(Operand2.HasIndex==true)
                  {
                  strcat(LpszInstructionBuf,"mov ");
                  strcat(LpszInstructionBuf,Getx86RegisterName(RegisterId1));
                  strcat(LpszInstructionBuf,",");
                  strcat(LpszInstructionBuf,Getx86RegisterName(Operand2.IndexRegister)); // have to check this once more
                  strcat(LpszInstructionBuf,"\n");
				  if(Operand2.IndexRegister==EBP)
                  strcat(LpszInstructionBuf,"sub ");
				  else if(Operand2.IndexRegister==EBX)
					  strcat(LpszInstructionBuf,"add ");
              strcat(LpszInstructionBuf,Getx86RegisterName(RegisterId1));
              strcat(LpszInstructionBuf,",0x");
              strcat(LpszInstructionBuf,itoa(Operand2.MemoryAddress,SymbolAddress,16));
              strcat(LpszInstructionBuf,"\n");
                  }
              else
                  {
              strcat(LpszInstructionBuf,"mov dword ");
              strcat(LpszInstructionBuf,Getx86RegisterName(RegisterId1));
              strcat(LpszInstructionBuf,",0x");
              strcat(LpszInstructionBuf,itoa(Operand2.MemoryAddress,SymbolAddress,16));
              strcat(LpszInstructionBuf,"\n");
                  }
              Operand2=SetRegisterOperand(RegisterId1);
          Operand2.IsReference=false;
              }
          
          }
      //    strcpy(LpszInstructionBuf,sz386OpCode[Opcode]);
      

      if(Operand1.IsValid==true)
          {
      if(Operand1.IsRegister==true)
          {
          strcat(LpszInstructionBuf,sz386OpCode[Opcode]);
      
      strcat(LpszInstructionBuf,memorysize_s[Size]);
          if(Operand1.IsReference==true)
              strcat(LpszInstructionBuf,"[");
          strcat(LpszInstructionBuf,Getx86RegisterName(Operand1.Register));
          
          if(Operand1.IsReference==true)
              strcat(LpszInstructionBuf,"]");
          }
      else if(Operand1.IsImmediate==true)
               {
               int Offset,len;
               Offset=0;
                   strcat(LpszInstructionBuf,sz386OpCode[Opcode]);
               strcat(LpszInstructionBuf,"0x");
               
               strcat(LpszInstructionBuf,GetImmediateValue(Operand1.ImmediateValue,Size));
               

               }
      else if(Operand1.IsLiteral==true)
          {
          strcat(LpszInstructionBuf,sz386OpCode[Opcode]);
      strcat(LpszInstructionBuf,memorysize_s[Size]);
          if(Operand1.IsReference==true)
          strcat(LpszInstructionBuf," [");
              strcat(LpszInstructionBuf,GetLiteralName(Operand1.SymTabPos));
              if(Operand1.IsReference==true)
              strcat(LpszInstructionBuf,"]");
          }
      else if(Operand1.IsMemoryAddress==true)
          {
          strcat(LpszInstructionBuf,sz386OpCode[Opcode]);
      
      strcat(LpszInstructionBuf,memorysize_s[Size]);
          itoa(Operand1.MemoryAddress,SymbolAddress,16); //isreference is already checked above so no need to check again
          
          strcat(LpszInstructionBuf,"[");
          if(Operand1.SegmentRegister!=NoRegister)
              {
              strcat(LpszInstructionBuf,Getx86RegisterName(Operand1.SegmentRegister));
              strcat(LpszInstructionBuf,":");
              }
          if(Operand1.HasIndex==true)
              {
              strcat(LpszInstructionBuf,Getx86RegisterName(Operand1.IndexRegister));
			  if(Operand1.IndexRegister==EBP)
				strcat(LpszInstructionBuf,"-");
              else if(Operand1.IndexRegister==EBX)
				strcat(LpszInstructionBuf,"+");
              }
              strcat(LpszInstructionBuf,"0x");
          strcat(LpszInstructionBuf,SymbolAddress);
          strcat(LpszInstructionBuf,"]");
	  }
	  else  if(Operand1.IsLabel==true)
	  {
		  strcat(LpszInstructionBuf,sz386OpCode[Opcode]);
      
      strcat(LpszInstructionBuf,memorysize_s[Size]);
	  strcat(LpszInstructionBuf,"[");
	  strcat(LpszInstructionBuf,Operand1.szLabel);
	  strcat(LpszInstructionBuf,"]");

	  }

	  }

//Operand1 ends here
if(Operand2.IsValid==true)
    {
           if(Operand2.IsRegister==true)
          {
          
          strcat(LpszInstructionBuf,",");
          if(Operand2.IsReference==true)
              strcat(LpszInstructionBuf,"[");
          strcat(LpszInstructionBuf,Getx86RegisterName(Operand2.Register));
          if(Operand2.IsReference==true)
              strcat(LpszInstructionBuf,"]");
          
          }
           else if(Operand2.IsImmediate==true)
               {
               int Offset,len;
               Offset=0;
               strcat(LpszInstructionBuf,",0x");
               strcat(LpszInstructionBuf,GetImmediateValue(Operand2.ImmediateValue,Size));
               
               }
           else if(Operand2.IsLiteral==true)
               {
               strcat(LpszInstructionBuf,",");
               if(Operand2.IsReference==true)
              strcat(LpszInstructionBuf,"[");
              strcat(LpszInstructionBuf,GetLiteralName(Operand2.SymTabPos));
              if(Operand2.IsReference==true)
              strcat(LpszInstructionBuf,"]");   
              
               }
           else if(Operand2.IsMemoryAddress==true)
          {
          strcat(LpszInstructionBuf,",");
          itoa(Operand2.MemoryAddress,SymbolAddress,16);
          
              strcat(LpszInstructionBuf,"[");
              if(Operand2.SegmentRegister!=NoRegister)
                {
              strcat(LpszInstructionBuf,Getx86RegisterName(Operand2.SegmentRegister));
              strcat(LpszInstructionBuf,":");
              }
              
      if(Operand2.HasIndex!=0)
              {
              strcat(LpszInstructionBuf,Getx86RegisterName(Operand2.IndexRegister));
              if(Operand2.IndexRegister==EBP)
				strcat(LpszInstructionBuf,"-");
			  else if(Operand2.IndexRegister==EBX)
				strcat(LpszInstructionBuf,"+");
              }
          strcat(LpszInstructionBuf,"0x");
          strcat(LpszInstructionBuf,SymbolAddress);
          
              strcat(LpszInstructionBuf,"]");
          
          }
    } 
           
         strcat(LpszInstructionBuf,"\n");
         if(RegisterId1!=-1) 
             UnLockRegister(RegisterId1);
         if(RegisterId2!=-1) 
             UnLockRegister(RegisterId2);
    
      }
  
  char *AddNewString(char *LpszValue)
  {
	  char *LpszBuffer;
	  int iLen;
	  iLen=strlen(LpszValue);
	  LpszBuffer=(char *)malloc(iLen);
	  strcpy(LpszBuffer,LpszValue);
	  return LpszBuffer;
  }
  void WriteToFile(char *LpszFileName)
      {
      int index,i;
      
  iCompileOption=eWindows;
	  
      //fprintf(OutputFile,"global _main\nsegment .text\n_main:push EBP \nmov EBP,Data\n add EBP,0xFF\n call _start\n pop EBP\nret\n");
      for(index=0;index<iOutputAsmCount;index++)
          {
          
          }
      
     /* for(index=0;index<LitCount;index++)
          {
          char szTempAsm[70],szTempLitValue[70];
          int SymValue,SymLen;
          strcpy(szTempAsm,GetSymbolName(LitTab[index].m_iSymId));
          strcpy(szTempLitValue,GetLiteralValue(LitTab[index].m_iSymId,int8));
          SymValue=atoi(szTempLitValue);
          itoa(SymValue,szTempLitValue,16);
          //strcpy(szTempLitValue,GetSymbolName(LitTab[index].m_iSymId));
          SymLen=strlen(szTempLitValue);
          if(GetDataType((LitTab[index].m_iSymId))==GetDataTypeId("_int_ltrl_8"))
              {
              strcat(szTempAsm," db 0x");
              if(SymLen>=2)
              strcat(szTempAsm,szTempLitValue+SymLen-2);
              else
                  strcat(szTempAsm,szTempLitValue);
              }
          else if(GetDataType((LitTab[index].m_iSymId))==GetDataTypeId("_int_ltrl_16"))
              {
              strcat(szTempAsm," dw 0x");
              if(SymLen>=4)
              strcat(szTempAsm,szTempLitValue+SymLen-4);
              else
                  strcat(szTempAsm,szTempLitValue);
              }
          if(GetDataType((LitTab[index].m_iSymId))==GetDataTypeId("_int_ltrl_32"))
              {
              strcat(szTempAsm," dd 0x");
              if(SymLen>=2)
              strcat(szTempAsm,szTempLitValue+SymLen-4);
              else
                  strcat(szTempAsm,szTempLitValue);
              }
          
          
          fprintf(OutputFile,"%s\n",szTempAsm);
          }*/
	  
      //fprintf(OutputFile," Data resb 100 \nint_format db 'Value=%%d\',0\n string_format  db \'String Value=%%s',0 \n uint_format db \'Value=%%d\',0\ntimes 510-($-$$) db 0 \n db 0x55\n db 0xAA\n times 1024-($-$$) db 0");

      }
void Generate_x86ASM_Function(Optab *Function_Start,struct FuncDetails FunctionDetails)
    {
    char Instruction[100],szAssemblyComment[100],*LpszLabel,szAsmInstruction[100],*LpszInstruction;
        Optab * current,*LpPrevious;
        int IsJump;
        char szTempLen[8];
        current=Function_Start;
        if(current==NULL)
            return;
        printf("\n");
        
        
		strcpy(szAsmInstruction,FunctionDetails.szFunctionLabel);
		//strcat(szAsmInstruction,"_");
        //strcat(szAsmInstruction,FunctionDetails.FunctionName);
        strcat(szAsmInstruction,":\n");
       /* AddOutputASM(szAsmInstruction,"\nmov ESP,EBP\n");
        strcpy(szAsmInstruction,"add ESP,0x");
        itoa(FunctionDetails.AddressEnd,szTempLen,16);
        strcat(szAsmInstruction,szTempLen);
        strcat(szAsmInstruction,"\n");*/
        AddOutputASM("",szAsmInstruction); // writing function name
		if(FunctionDetails.iType==INTERRUPT_KW)
		{
			AddOutputASM("","cli\npushad\nmov dword EAX,ESP\n");
			AddOutputASM("","mov dword EBX,EBP\nmov EBP,ISR\nadd EBP,180\n");
			AddOutputASM("","mov ESP,EBP\npush EAX\npush EBX\n");
			AddOutputASM("","sub EBP,0x9\nmov ESP,EBP\nmov EBX,ObjectData\n");
		}
        strcpy(szAsmInstruction,"sub ESP,0x");
        itoa(FunctionDetails.AddressEnd,szTempLen,16);
        strcat(szAsmInstruction,szTempLen);
        strcat(szAsmInstruction,"\n");
        AddOutputASM("",szAsmInstruction); //writing the EBP Size required.
        while(1)
            {
            szAssemblyComment[0]=';'; // 
            szAssemblyComment[1]='\0';
            Instruction[0]='\0';
            LpszLabel=NULL;
            
            IsJump=ProcessJumpStatement(current,&FunctionDetails);
            if(IsJump==1)
                {
                strcat(Instruction,"\t");
                strcat(Instruction,GetOperatorName(current->Operator));
                strcat(Instruction," ");
                strcat(Instruction,current->TargetLabel); 
				strcat(szAssemblyComment,current->Label);
                strcat(szAssemblyComment,Instruction); 
                strcat(szAssemblyComment,"\n");
				#if(CHECK_DEBUG_ENABLED(DEBUG_ASSEMBLYCOMMENTS))
                AddOutputASM("",szAssemblyComment);
				#endif
                if(current->Operator==GetOperatorId("JE"))
                    {
                    strcpy(szAsmInstruction,"je ");
                    strcat(szAsmInstruction,current->TargetLabel);
                    strcat(szAsmInstruction,"\n");
                    AddOutputASM(current->Label,szAsmInstruction);
                    }
                if(current->Operator==GetOperatorId("JNE"))
                    {
                    strcpy(szAsmInstruction,"jne ");
                    strcat(szAsmInstruction,current->TargetLabel);
                    strcat(szAsmInstruction,"\n");
                    AddOutputASM(current->Label,szAsmInstruction);
                    }
                if(current->Operator==GetOperatorId("JMP"))
                    {
                    strcpy(szAsmInstruction,"jmp ");
                    strcat(szAsmInstruction,current->TargetLabel);
                    strcat(szAsmInstruction,"\n");
                    AddOutputASM(current->Label,szAsmInstruction);
                    }
                if(current->Operator==GetOperatorId("JG"))
                    {
                    strcpy(szAsmInstruction,"jg ");
                    strcat(szAsmInstruction,current->TargetLabel);
                    strcat(szAsmInstruction,"\n");
                    AddOutputASM(current->Label,szAsmInstruction);
                    }
                if(current->Operator==GetOperatorId("JL"))
                    {
                    strcpy(szAsmInstruction,"jl ");
                    strcat(szAsmInstruction,current->TargetLabel);
                    strcat(szAsmInstruction,"\n");
                    AddOutputASM(current->Label,szAsmInstruction);
                    }
                if(current->Operator==GetOperatorId("JLE"))
                    {
                    strcpy(szAsmInstruction,"jle ");
                    strcat(szAsmInstruction,current->TargetLabel);
                    strcat(szAsmInstruction,"\n");
                    AddOutputASM(current->Label,szAsmInstruction);
                    }
				if(current->Operator==GetOperatorId("JA"))
                    {
                    strcpy(szAsmInstruction,"ja ");
                    strcat(szAsmInstruction,current->TargetLabel);
                    strcat(szAsmInstruction,"\n");
                    AddOutputASM(current->Label,szAsmInstruction);
                    }
				if(current->Operator==GetOperatorId("JB"))
                    {
                    strcpy(szAsmInstruction,"jb ");
                    strcat(szAsmInstruction,current->TargetLabel);
                    strcat(szAsmInstruction,"\n");
                    AddOutputASM(current->Label,szAsmInstruction);
                    }
                if(current->Operator==GetOperatorId("JBE"))
                    {
                    strcpy(szAsmInstruction,"jbe ");
                    strcat(szAsmInstruction,current->TargetLabel);
                    strcat(szAsmInstruction,"\n");
                    AddOutputASM(current->Label,szAsmInstruction);
                    }
				ClearRegs();
                }
            else
                {
                LpszLabel=current->Label;
                if(strlen(current->Label)!=0)
                    {
                    
                    strcat(Instruction,LpszLabel);
                    strcat(Instruction,"\t");
                    }
                else
                    {
                    strcat(Instruction,"\t");
                    }
                
                strcat(Instruction,GetSymbolName(current->Result));
                strcat(Instruction,"\t");
                if(IsLiteral(current->Operand1))
                    strcat(Instruction,GetLiteralValue(current->Operand1,0));
                else
                strcat(Instruction,GetSymbolName(current->Operand1));
                strcat(Instruction,"\t");
                
                strcat(Instruction,GetOperatorName(current->Operator));
                strcat(Instruction,"\t");
				SetNextRegisterRank(current,Function_Start);
				if(current->Operator==GetOperatorId("cast"))
				{
					strcat(Instruction,GetDataTypeName(current->Operand2));
				}
				else
				{
					if(IsLiteral(current->Operand2))
						strcat(Instruction,GetLiteralValue(current->Operand2,0));
					else
					{
						strcat(Instruction,GetSymbolName(current->Operand2));
					}
				}
                
                strcat(szAssemblyComment,Instruction);
                strcat(szAssemblyComment,"\n");
				#if(CHECK_DEBUG_ENABLED(DEBUG_ASSEMBLYCOMMENTS))
                AddOutputASM("",szAssemblyComment);
				#endif
                if(current->Operator==GetOperatorId("-"))
                    {
                    int reg1,reg2,OpCodeOperand1,OpCodeOperand2,Size,reg_result;
                    struct Operand Operand1,Operand2,Result;
                    struct Operand Register1,Register2,Register3;
                    char szTempSymbolBuf[MAX_SYM_LEN];
                    OpCodeOperand1=mov;
                    OpCodeOperand2=mov;     
                    Size=CompareSize(current->Operand1,current->Operand2);
                    Operand1=SetMemoryOperand(current->Operand1);
                  //  if(Operand1.IsImmediate==false) 
                       // {
                         reg1=Chosex86Register(current->Operand1);
                         if(reg1>=0)
                             {
                              Register1=SetRegisterOperand(reg1);
                              SetRegister(reg1,current->Operand1,1);
                              if(Operand1.IsLiteral==true)
                                Operand1.IsReference=false;
                              Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                              AddOutputASM(LpszLabel,szAsmInstruction);
                              Operand1=Register1;
                             }
                         else
                             {
                             int iLength,OpCode,reg1_save;
                             struct Operand RegisterTemp;
                             reg1=reg1*-1;
                             Operand1=SetRegisterOperand(reg1);
                             SetRegister(reg1,current->Operand1,1);
                             }
                   //     }

                    Operand2=SetMemoryOperand(current->Operand2);
                    if(Operand2.IsImmediate==false)
                            {
                    reg2=Chosex86Register(current->Operand2);
                    if(reg2>=0)
                        {
                        SetRegister(reg2,current->Operand2,1);
                        Register2=SetRegisterOperand(reg2);
                        
                        if(Operand2.IsLiteral==true)
                            Operand2.IsReference=true;
                        
                    Generatex86Instruction(mov,GetRegisterWordSize(reg2),Register2,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Operand2=Register2;
                        }
                    else
                        {
                        int iLength,OpCode,reg2_save;
                        struct Operand RegisterTemp;
                        reg2=reg2*-1;
                        Operand2=SetRegisterOperand(reg2);
                        SetRegister(reg2,current->Operand2,1); 
                        }
                     }
                    Generatex86Instruction(sub,none,Operand1,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Result=SetMemoryOperand(current->Result);
                    Generatex86Instruction(mov,GetRegisterWordSize(reg1),Result,Operand1,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
					reg_result=GetSymbolRegister(Result.SymTabPos);
					if(reg_result!=-1)
						SetRegister(reg_result,-1,0);
                    UnLockRegister(reg2);
                    if(Register1.IsRegister==true)
                        {
                    SetRegister(Register1.Register,current->Result,0);
                    UnLockRegister(reg1);
                        }
                    }
                if(current->Operator==GetOperatorId("+"))
                    {
                    int reg1,reg2,OpCodeOperand1,OpCodeOperand2,Size,reg_result;
                    struct Operand Operand1,Operand2,Result,EAXRegister,EBPRegister,Operand3;
                    struct Operand Register1,Register2,Register3;
                    char szTempSymbolBuf[MAX_SYM_LEN];
                    OpCodeOperand1=mov;
                    OpCodeOperand2=mov;
                    reg1=-1;
                    reg2=-1;
                    Register1.IsValid=false;
                    Register2.IsValid=false;
                   
                        
                        Size=CompareSize(current->Operand1,current->Operand2);
                        
                       
                   
                    
                    Operand1=SetMemoryOperand(current->Operand1);
                    if(Operand1.IsImmediate==false) 
                           {
                           reg1=Chosex86Register(current->Operand1);
                    if(reg1>=0)
                        
                        {
                        Register1=SetRegisterOperand(reg1);
                        
                        SetRegister(reg1,current->Operand1,1);
                        
                        if(Operand1.IsLiteral==true)
                            Operand1.IsReference=false;
                       
                    Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    Operand1=Register1;
                           
                            
                   
                    
                        }
                    else
                        {
                        int iLength,OpCode,reg1_save;
                        struct Operand RegisterTemp;
                        reg1=reg1*-1;
                        Operand1=SetRegisterOperand(reg1);
                        SetRegister(reg1,current->Operand1,1);
                       
                        }
                        
                        }
                    Operand2=SetMemoryOperand(current->Operand2);
                    if(Operand2.IsImmediate==false)
                            {
                    reg2=Chosex86Register(current->Operand2);
                    if(reg2>=0)
                        {
                        SetRegister(reg2,current->Operand2,1);
                        Register2=SetRegisterOperand(reg2);
                        
                        if(Operand2.IsLiteral==true)
                            Operand2.IsReference=true;
                        
                    Generatex86Instruction(mov,GetRegisterWordSize(reg2),Register2,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Operand2=Register2;
                            
                    /*if(Size==current->Operand1)
                        {
                        int reg2_save;
                        reg2_save=reg2;
                         reg2=GetRegister(GetDataTypeSize(GetDataType(current->Operand1))*8);
                         UnLockRegister(reg2_save);
                         Register3=SetRegisterOperand(reg2);
                         SetRegister(reg2,-1,1);
                         if(IsSigned(current->Operand2))
                             OpCodeOperand2=movsx;
                         else
                             OpCodeOperand2=movzx;
                         Generatex86Instruction(OpCodeOperand2,none,Register3,Register2,szAsmInstruction);
                         AddOutputASM(LpszLabel,szAsmInstruction);
                         Register2=Register3;
                        }*/
                        }
                    else
                        {
                        
                        int iLength,OpCode,reg2_save;
                        struct Operand RegisterTemp;
                        reg2=reg2*-1;
                        Operand2=SetRegisterOperand(reg2);
                        SetRegister(reg2,current->Operand2,1);
                       /* if(Size==current->Operand1)
                            {
                            if(IsReference(current->Operand1))
                                iLength=GetDataTypeSize(SymTab[current->Operand1].PointerTarget);
                            else
                            iLength=GetDataTypeSize(GetDataType(current->Operand1));
                            
                            reg2_save=reg2;
                            reg2=GetRegister(iLength*8);
                            RegisterTemp=SetRegisterOperand(reg2);
                            if(IsSigned(current->Operand1))
                             OpCode=movsx;
                            else
                             OpCode=movzx;
                            Generatex86Instruction(OpCode,none,RegisterTemp,Register2,szAsmInstruction);
                            AddOutputASM("",szAsmInstruction);
                            SetRegister(reg2,-1,1);
                            UnLockRegister(reg2_save);
                            Register2=RegisterTemp;
                            }
                     */
                        
                        }
                     }
                    if(Operand1.IsImmediate==true)
                        {
                        Operand3=Operand1;
                        Operand1=Operand2;
                        Operand2=Operand3;
                        }
                    Generatex86Instruction(add,none,Operand1,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Result=SetMemoryOperand(current->Result);
                    Generatex86Instruction(mov,GetRegisterWordSize(reg1),Result,Operand1,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    reg_result=GetSymbolRegister(Result.SymTabPos);
					if(reg_result!=-1)
						SetRegister(reg_result,-1,0);
                    if(Operand2.IsRegister==true)
                        {
                    UnLockRegister(Operand2.Register);
                        }
                    if(Operand1.IsRegister==true)
                        {
                        UnLockRegister(Operand1.Register);
                        SetRegister(Operand1.Register,current->Result,0);
                        }
                    }
                if(current->Operator==GetOperatorId("="))
                    {
                    struct Operand Operand1,Operand2,Result,Register1,Register2;
                    int reg1;
                    char szLengthBuffer[6],szTempLabel[MAX_LABEL_LEN];
                        int iLength,iCount,iModulus; 
                  
                            char szTempBufResult[32],szTempBufOperand[32];
                            int iSymIdResult,iSymIdOperand,iSymbolAddress,iCompareSize,reg_result;
                            if(IsPrimitive(current->Operand1))
                                {
                                int iRegWordSize;
                                iCompareSize=CompareSize(current->Operand1,current->Result);
                               if(IsLiteral(current->Operand1))
                                   {
                                       if(!IsReference(current->Result))
                                   reg1=GetRegister(8*GetDatatypeSize(current->Result));
                                       else
                                           reg1=GetRegister(8*GetDataTypeSize(GetPointerTarget(current->Result)));

                                   
                                   }
                               else
                                    reg1=Chosex86Register(current->Operand1);
                                    if(reg1>=0)
                                        {
                                    iRegWordSize=GetRegisterWordSize(reg1);
                                    SetRegister(reg1,current->Operand1,1); 
                                    Register1=SetRegisterOperand(reg1);
                                    Operand1=SetMemoryOperand(current->Operand1);
									//Operand1.IsReference=true;
                                    Generatex86Instruction(mov,iRegWordSize,Register1,Operand1,szAsmInstruction);
                                    AddOutputASM(LpszLabel,szAsmInstruction);
                                        }
                                    else
                                        {
                                        reg1=reg1*-1;
                                        SetRegister(reg1,current->Operand1,1); 
                                        Register1=SetRegisterOperand(reg1);
                                        }
                                    Result=SetMemoryOperand(current->Result);
                                    Generatex86Instruction(mov,GetRegisterWordSize(Register1.Register),Result,Register1,szAsmInstruction);
                                    AddOutputASM("",szAsmInstruction);
                                    UnLockRegister(reg1);
                                    SetRegister(reg1,current->Result,0);
                                  
									//reg_result=GetSymbolRegister(Result.SymTabPos);
									//if(reg_result!=-1)
									//	SetRegister(reg_result,-1,0);
                                }  
                                
                            else
                                {
                            Register1=SetRegisterOperand(EDI);
                            Register2=SetRegisterOperand(ESI);
                          
                            LockRegister(EDI);
                            LockRegister(ESI);
                            
                            Result=SetMemoryOperand(current->Result);
                            Result.IsReference=false; // one dummy operation performed  . moving data to intermediate register instead of destination
                            Generatex86Instruction(mov,dword,Register1,Result,szAsmInstruction);
                            AddOutputASM("",szAsmInstruction);
                            Operand1=SetMemoryOperand(current->Operand1);
                            Operand1.IsReference=false;
                            Generatex86Instruction(mov,dword,Register2,Operand1,szAsmInstruction);
                            AddOutputASM("",szAsmInstruction);
                            if(IsReference(current->Operand1))
                                iLength=DataTypeTable[SymTab[current->Operand1].PointerTarget].m_iDataTypeSize;
                            else
                                iLength=DataTypeTable[GetDataType(current->Operand1)].m_iDataTypeSize;
                            iCount=iLength/4;
                            iModulus=iLength%4;
                            if(iCount!=0)
                                    {
                            UnLockRegister(ECX);
                            itoa(iCount,szLengthBuffer,16); //unlock ECX
                            strcpy(szAsmInstruction,"mov dword ECX,0x");
                            strcat(szAsmInstruction,szLengthBuffer);
                            strcat(szAsmInstruction,"\n");
                            AddOutputASM("",szAsmInstruction);
                            strcpy(szTempLabel,GenerateTempLabel());
                            
                            AddOutputASM(szTempLabel," mov dword EAX,[ESI]\n");
                            AddOutputASM("","mov dword [EDI],EAX\n add ESI,4\n add EDI,4\n");
                            strcpy(szAsmInstruction,"LOOP ");
                            strcat(szAsmInstruction,szTempLabel);
                            strcat(szAsmInstruction,"\n");
                            AddOutputASM("",szAsmInstruction);
                                }
                        /*    }
                        else if(IsReference(current->Result))
                            {
                            char szTempBuf[32];
                            int iSymId,iSymbolAddress,IndexRegister,HasIndex;
                            Register2=SetRegisterOperand(EDI);
                            Result=SetMemoryOperand(current->Result);
                            Result.IsReference=false;
                            Generatex86Instruction(mov,dword,Register2,Result,szAsmInstruction);
                            AddOutputASM("",szAsmInstruction);
                            if(IsLiteral(current->Operand1))
                                {
                                strcpy(szAsmInstruction,"mov dword ESI,");
                                strcat(szAsmInstruction,GetLiteralName(current->Operand1));
                                strcat(szAsmInstruction,"\n");
                                AddOutputASM("",szAsmInstruction);
                                }
                            else
                                {
                            Register1=SetRegisterOperand(ESI);
                            Operand1=SetMemoryOperand(current->Operand1);
                            Operand1.IsReference=false;
                            
                            IndexRegister=Operand1.IndexRegister;
                            
                            Generatex86Instruction(mov,dword,Register1,Operand1,szAsmInstruction);
                            AddOutputASM("",szAsmInstruction);
                                }
                            
                            iLength=DataTypeTable[GetDataType(current->Operand1)].m_iDataTypeSize;

                            }
                        else if(IsReference(current->Operand1)) //only one operand can be Reference for the timebeing
                            {
                            char szTempBuf[32];
                            int iSymId,iSymbolAddress,iHasIndex;
                            //strcpy(szTempBuf,SymTab[current->Operand1].Symbol);
                            //iSymId=GetSymTabPos(szTempBuf+1);
                            Operand1=SetMemoryOperand(current->Operand1);
                            Operand1.IsReference=false;
                            Register1=SetRegisterOperand(ESI);
                            Generatex86Instruction(mov,dword,Register1,Operand1,szAsmInstruction);
                            AddOutputASM("",szAsmInstruction);
                            Register2=SetRegisterOperand(EDI);
                            Result=SetMemoryOperand(current->Result);
                            Result.IsReference=false;
                            iHasIndex=Result.HasIndex;
                            Result.HasIndex=false;
                            Generatex86Instruction(mov,dword,Register2,Result,szAsmInstruction);
                            AddOutputASM("",szAsmInstruction);
                            
                            iLength=DataTypeTable[GetDataType(current->Operand1)].m_iDataTypeSize;
                            }
                            iCount=iLength/4;
                            iModulus=iLength%4;
                            if(iCount!=0)
                                {
                            UnLockRegister(ECX);
                            itoa(iCount,szLengthBuffer,16); //unlock ECX
                            strcpy(szAsmInstruction,"mov dword ECX,0x");
                            strcat(szAsmInstruction,szLengthBuffer);
                            strcat(szAsmInstruction,"\n");
                            AddOutputASM("",szAsmInstruction);
                            strcpy(szTempLabel,GenerateTempLabel());
                            
                            AddOutputASM(szTempLabel,": mov dword EAX,[ESI]");
                            AddOutputASM("","mov dword [EDI],EAX\n add ESI,4\n add EDI,4\n");
                            strcpy(szAsmInstruction,"LOOP ");
                            strcat(szAsmInstruction,szTempLabel);
                            strcat(szAsmInstruction,"\n");
                            AddOutputASM("",szAsmInstruction);
                                }
                                */
                            
                            if(iModulus==3)
                                {
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n");
                                
                                }
                            if(iModulus==2)
                                {
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n");
                                
                                }
                            if(iModulus==1)
                                {
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n");
                                }
                            
                        }
                       /* else
                            {
                            int iRetValue,reg1;
                            reg1=Chosex86Register(current->Operand1);
                            
                            /*if(iRetValue=IsLiteral(current->Operand1))
                                {
                                if(iRetValue==1)
                                    {
                                    if(reg1<0)
                                        reg1=reg1*-1;
                                    
                                    strcpy(szAsmInstruction,"mov ");
                                    strcat(szAsmInstruction,memorysize_s[GetRegisterWordSize(reg1)]);
                                    strcat(szAsmInstruction,Getx86RegisterName(reg1));
                                    strcat(szAsmInstruction,",[");
                                    strcat(szAsmInstruction,GetLiteralName(current->Operand1));
                                    strcat(szAsmInstruction,"]\n");
                                    AddOutputASM("",szAsmInstruction);
                                    SetRegister(reg1,current->Operand1,1);
                                    Register1=SetRegisterOperand(reg1);
                                
                                    }
                                else if(iRetValue==2) //string literal
                                    {
                                    }
                                }
                            else
                                {
                    */
                /*    if(reg1>0)
                        {
                        Register1=SetRegisterOperand(reg1);
                        Operand1=SetMemoryOperand(current->Operand1);
                        if(Operand1.IsLiteral==true)
                            Operand1.IsReference=true;
                    Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    SetRegister(reg1,current->Operand1,1);
                        }
                    else
                        {
                        reg1=reg1*-1;
                        SetRegister(reg1,current->Operand1,1);
                        Register1=SetRegisterOperand(reg1);
                        }
                                
                                
                            Result=SetMemoryOperand(current->Result);
                    Generatex86Instruction(mov,GetRegisterWordSize(reg1),Result,Register1,szAsmInstruction);
                    SetRegister(reg1,current->Result,0);
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    UnLockRegister(reg1);
                        
                       // }
                    
                    */
                            //}
                        UnLockRegister(EDI);
                        UnLockRegister(ESI);
                            }

                            if(current->Operator==GetOperatorId("Lit2Ptr"))
                            {
                                int rSourceReg,rDestReg;
                                struct Operand TempVar,RegOperand,DestReg;
                                char szLenBuffer[10];
                                rSourceReg=GetRegister(32);
                                SetRegister(rSourceReg,-1,1);
                                rDestReg=GetRegister(32);
                                SetRegister(rDestReg,-1,1);
                                strcpy(szAsmInstruction,"mov ");
                                strcat(szAsmInstruction,Getx86RegisterName(rSourceReg));
                                strcat(szAsmInstruction,",");
                                strcat(szAsmInstruction,GetLiteralName(current->Operand1));
                                strcat(szAsmInstruction,"\n");
                                AddOutputASM(LpszLabel,szAsmInstruction);
                                LpszLabel=NULL;
                                TempVar=SetMemoryOperand(current->Result);
                                
                                RegOperand=SetRegisterOperand(rSourceReg);
                                DestReg=SetRegisterOperand(rDestReg);
                                TempVar.IsReference=false;
                                Generatex86Instruction(mov,GetRegisterWordSize(rSourceReg),DestReg,TempVar,szAsmInstruction);
                                AddOutputASM(LpszLabel,szAsmInstruction);
                                DestReg.IsReference=true;
                                Generatex86Instruction(mov,GetRegisterWordSize(rSourceReg),DestReg,RegOperand,szAsmInstruction);
                                AddOutputASM(LpszLabel,szAsmInstruction);

                                /*rSourceReg=GetRegister(32);
                                SetRegister(rSourceReg,-1,1);
                                rDestReg=GetRegister(32);
                                SetRegister(rDestReg,-1,1);
                                strcpy(szAsmInstruction,"mov ");
                                strcat(szAsmInstruction,Getx86RegisterName(rSourceReg));
                                strcat(szAsmInstruction,",");
                                strcat(szAsmInstruction,GetLiteralName(current->Operand1));
                                strcat(szAsmInstruction,"\n");
                                AddOutputASM(LpszLabel,szAsmInstruction);
                                LpszLabel=NULL;
                                TempVar=SetMemoryOperand(current->Result);
                                
                                RegOperand=SetRegisterOperand(rSourceReg);
                                DestReg=SetRegisterOperand(rDestReg);
                                TempVar.IsReference=false;
                                Generatex86Instruction(mov,GetRegisterWordSize(rSourceReg),DestReg,TempVar,szAsmInstruction);
                                AddOutputASM(LpszLabel,szAsmInstruction);
                                DestReg.IsReference=true;
                                Generatex86Instruction(mov,GetRegisterWordSize(rSourceReg),DestReg,RegOperand,szAsmInstruction);
                                AddOutputASM(LpszLabel,szAsmInstruction);
                                strcpy(szAsmInstruction,"add ");
                                strcat(szAsmInstruction,Getx86RegisterName(rDestReg));
                                strcat(szAsmInstruction,",04x\n");
                                AddOutputASM(LpszLabel,szAsmInstruction);
                                strcpy(szAsmInstruction,"mov byte[");
                                strcat(szAsmInstruction,Getx86RegisterName(rDestReg));
                                strcat(szAsmInstruction,"],0x");
                                itoa(strlen(GetLiteralValue(current->Operand1,0)),szLenBuffer,16);
                                
                                    strcat(szAsmInstruction,szLenBuffer);
                                    strcat(szAsmInstruction,"\n");
                                AddOutputASM(LpszLabel,szAsmInstruction);
*/
                                UnLockRegister(rSourceReg);
                                UnLockRegister(rDestReg);


                                




                                
                            }
                if(current->Operator==GetOperatorId("*"))
                    {
                    int reg1,reg2,OpCodeOperand1,OpCodeOperand2,Size,OpCodeOperand,reg_result,temp;
                    struct Operand Operand1,Operand2,Operand3,Result;
                    struct Operand Register1,Register2,Register3;
                    char szTempSymbolBuf[MAX_SYM_LEN];
					if((IsLiteral(current->Operand1))&&(!IsLiteral(current->Operand2)))
					{
					temp=current->Operand1;
					current->Operand1=current->Operand2;
					current->Operand2=temp;
					}
                    OpCodeOperand1=mov;
                    OpCodeOperand2=mov;     
                    Size=CompareSize(current->Operand1,current->Operand2);
                    Operand1=SetMemoryOperand(current->Operand1);
                    Operand2=SetMemoryOperand(current->Operand2);
					
                    Result=SetMemoryOperand(current->Result);
                    if((GetDatatypeSize(current->Operand1)==1)||(!IsSigned(current->Operand1)))
                        {
                        if(GetDatatypeSize(current->Operand1)==1)
                            reg1=al;
                        else
                            reg1=ax;
                        UnLockRegister(reg1);
                        SetRegister(EAX,-1,1);
                        Register1=SetRegisterOperand(reg1);
                        reg2=Chosex86Register(current->Operand2);
                        Register2=SetRegisterOperand(reg2);
                        Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                        AddOutputASM(LpszLabel,szAsmInstruction);
                        Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register2,Operand2,szAsmInstruction);
                        AddOutputASM(LpszLabel,szAsmInstruction);
                        if(IsSigned(current->Operand1))
                            OpCodeOperand1=imul;
                        else
                            OpCodeOperand1=mul;
                        Operand2.IsValid=false;
                        Generatex86Instruction(OpCodeOperand1,none,Register2,Operand2,szAsmInstruction);
                        AddOutputASM(LpszLabel,szAsmInstruction);
                        
                        Generatex86Instruction(mov,GetRegisterWordSize(reg1),Result,Register1,szAsmInstruction);
                        AddOutputASM(LpszLabel,szAsmInstruction);
                        UnLockRegister(reg1);

                        UnLockRegister(reg2);
                        }
                    else
                        {
                    
                    Operand1.IsImmediate=false;
                         reg1=Chosex86Register(current->Operand1);
                         if(reg1>=0)
                             {
                              Register1=SetRegisterOperand(reg1);
                              SetRegister(reg1,current->Operand1,1);
                              if(Operand1.IsLiteral==true)
                                Operand1.IsReference=false;
                              Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                              AddOutputASM(LpszLabel,szAsmInstruction);
                              Operand1=Register1;
                             }
                         else
                             {
                             int iLength,OpCode,reg1_save;
                             struct Operand RegisterTemp;
                             reg1=reg1*-1;
                             Operand1=SetRegisterOperand(reg1);
                             SetRegister(reg1,current->Operand1,1);
                             }
                        
                    
                    if(Operand2.IsImmediate==false)
                            {
                    reg2=Chosex86Register(current->Operand2);
                    if(reg2>=0)
                        {
                        SetRegister(reg2,current->Operand2,1);
                        Register2=SetRegisterOperand(reg2);
                        
                        if(Operand2.IsLiteral==true)
                            Operand2.IsReference=true;
                        
                    Generatex86Instruction(mov,GetRegisterWordSize(reg2),Register2,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Operand2=Register2;
                        }
                    else
                        {
                        int iLength,OpCode,reg2_save;
                        struct Operand RegisterTemp;
                        reg2=reg2*-1;
                        Operand2=SetRegisterOperand(reg2);
                        SetRegister(reg2,current->Operand2,1); 
                        }
                     }
                    
                    if(Operand1.IsImmediate==true)
                        {
                        Operand3=Operand1;
                        Operand1=Operand2;
                        Operand2=Operand3;
                        }
                    Generatex86Instruction(imul,none,Operand1,Operand2,szAsmInstruction);
                    
                        
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    
                    Generatex86Instruction(mov,GetRegisterWordSize(reg1),Result,Operand1,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    
                        
                    reg_result=GetSymbolRegister(Result.SymTabPos);
					if(reg_result!=-1)
						SetRegister(reg_result,-1,0);
                    if(Operand1.IsRegister==true)
                        {
                        SetRegister(Operand1.Register,current->Result,0);
                        UnLockRegister(Operand1.Register);
                        }
                        
                    if((reg2>0)&&(reg2<25))
                        {
                        UnLockRegister(reg2);
                        }
                        }
                    }
                if(current->Operator==GetOperatorId("/"))
                    {
                    int reg1,reg2,OpCodeOperand1,OpCodeOperand2,Size,OpCodeOperand,reg_result;
                    struct Operand Operand1,Operand2,Result;
                    struct Operand Register1,Register2,Register3;
                    char szTempSymbolBuf[MAX_SYM_LEN],szConvertInstruction[5];
                    OpCodeOperand1=mov;
                    OpCodeOperand2=mov;     
                    //Size=CompareSize(current->Operand1,current->Operand2);
                    UnLockRegister(EAX);
                    Operand1=SetMemoryOperand(current->Operand1);
                   reg1=-1;
                   reg2=-1;
                   if(Operand1.IsImmediate==true)
                       {
                      if((GetDataType(current->Operand2)==GetDataTypeId("int8"))||(GetDataType(current->Operand2)==GetDataTypeId("uint8")))
                        {
                        strcpy(szConvertInstruction,"CBW\n");
                        reg1=al;
                        }
                    else if((GetDataType(current->Operand2)==GetDataTypeId("int16"))||(GetDataType(current->Operand2)==GetDataTypeId("uint16")))
                        {
                        strcpy(szConvertInstruction,"CWD\n");
                        UnLockRegister(dx);
                        reg1=ax;
                        }
                    else if((GetDataType(current->Operand2)==GetDataTypeId("int32"))||(GetDataType(current->Operand2)==GetDataTypeId("uint32")))
                        {
                        strcpy(szConvertInstruction,"CDQ\n");
                        reg1=EAX;
                        UnLockRegister(EDX);
                        }
                       }
                    if((GetDataType(current->Operand1)==GetDataTypeId("int8"))||(GetDataType(current->Operand1)==GetDataTypeId("uint8")))
                        {
                        strcpy(szConvertInstruction,"CBW\n");
                        reg1=al;
                        }
                    else if((GetDataType(current->Operand1)==GetDataTypeId("int16"))||(GetDataType(current->Operand1)==GetDataTypeId("uint16")))
                        {
                        strcpy(szConvertInstruction,"CWD\n");
                        UnLockRegister(dx);
                        reg1=ax;
                        }
                    else if((GetDataType(current->Operand1)==GetDataTypeId("int32"))||(GetDataType(current->Operand1)==GetDataTypeId("uint32")))
                        {
                        strcpy(szConvertInstruction,"CDQ\n");
                        reg1=EAX;
                        UnLockRegister(EDX);
                        }
                    
                              Register1=SetRegisterOperand(reg1);
                              SetRegister(EAX,current->Operand1,1);
                              
                              Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                              AddOutputASM(LpszLabel,szAsmInstruction);

                         
                         AddOutputASM(LpszLabel,szConvertInstruction);
                     //   }
                    Operand2=SetMemoryOperand(current->Operand2);
                    
                    //reg2=Chosex86Register(current->Operand2);
					reg2=GetRegister(GetDatatypeSize(current->Operand1)*8);
                    if(reg2>=0)
                        {
                        SetRegister(reg2,current->Operand2,1);
                        Register2=SetRegisterOperand(reg2);
                        
                        if(Operand2.IsLiteral==true)
                            Operand2.IsReference=true;
                        
                    Generatex86Instruction(mov,GetRegisterWordSize(reg2),Register2,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Operand2=Register2;
                        }
                    else
                        {
                        int iLength,OpCode,reg2_save;
                        struct Operand RegisterTemp;
                        reg2=reg2*-1;
                        Operand2=SetRegisterOperand(reg2);
                        SetRegister(reg2,current->Operand2,1); 
                        }
                     
                    if(IsSigned(current->Operand1))
                        OpCodeOperand=idiv;
                    else
                    OpCodeOperand=Div;
                    Operand1.IsValid=false;

                    Generatex86Instruction(OpCodeOperand,none,Operand2,Operand1,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    Result=SetMemoryOperand(current->Result);
                    Generatex86Instruction(mov,GetRegisterWordSize(Register1.Register),Result,Register1,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
					reg_result=GetSymbolRegister(Result.SymTabPos);
					if(reg_result!=-1)
						SetRegister(reg_result,-1,0);
                    UnLockRegister(reg1);
                    UnLockRegister(reg2);
                    SetRegister(reg1,current->Result,0);
                    }
                if(current->Operator==GetOperatorId("%"))
                    {
                    int reg1,reg2,OpCodeOperand1,OpCodeOperand2,Size,OpCodeOperand,reg_rem,reg_result;
                    struct Operand Operand1,Operand2,Result;
                    struct Operand Register1,Register2,Register3,RegisterRemainder;
                    char szTempSymbolBuf[MAX_SYM_LEN],szConvertInstruction[5];
                    OpCodeOperand1=mov;
                    OpCodeOperand2=mov;     
                    //Size=CompareSize(current->Operand1,current->Operand2);
                    UnLockRegister(EAX);
                    Operand1=SetMemoryOperand(current->Operand1);
                   reg1=-1;
                   reg2=-1;
                   if(Operand1.IsImmediate==true)
                       {
                      if((GetDataType(current->Operand2)==GetDataTypeId("int8"))||(GetDataType(current->Operand2)==GetDataTypeId("uint8")))
                        {
                        strcpy(szConvertInstruction,"CBW\n");
                        reg1=al;
                        reg_rem=ah;
                        }
                    else if((GetDataType(current->Operand2)==GetDataTypeId("int16"))||(GetDataType(current->Operand2)==GetDataTypeId("uint16")))
                        {
                        strcpy(szConvertInstruction,"CWD\n");
                        UnLockRegister(dx);
                        reg1=ax;
                        reg_rem=dx;
                        }
                    else if((GetDataType(current->Operand2)==GetDataTypeId("int32"))||(GetDataType(current->Operand2)==GetDataTypeId("uint32")))
                        {
                        strcpy(szConvertInstruction,"CDQ\n");
                        reg1=EAX;
                        UnLockRegister(EDX);
                        reg_rem=EDX;
                        }
                       }
                    if((GetDataType(current->Operand1)==GetDataTypeId("int8"))||(GetDataType(current->Operand1)==GetDataTypeId("uint8")))
                        {
                        strcpy(szConvertInstruction,"CBW\n");
                        reg1=al;
                        reg_rem=ah;
                        }
                    else if((GetDataType(current->Operand1)==GetDataTypeId("int16"))||(GetDataType(current->Operand1)==GetDataTypeId("uint16")))
                        {
                        strcpy(szConvertInstruction,"CWD\n");
                        UnLockRegister(dx);
                        reg1=ax;
                        reg_rem=dx;
                        }
                    else if((GetDataType(current->Operand1)==GetDataTypeId("int32"))||(GetDataType(current->Operand1)==GetDataTypeId("uint32")))
                        {
                        strcpy(szConvertInstruction,"CDQ\n");
                        reg1=EAX;
                        UnLockRegister(EDX);
                        reg_rem=EDX;
                        }
                    
                              Register1=SetRegisterOperand(reg1);
                              SetRegister(EAX,current->Operand1,1);
                              
                              Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                              AddOutputASM(LpszLabel,szAsmInstruction);

                         
                         AddOutputASM(LpszLabel,szConvertInstruction);
                     //   }
                    Operand2=SetMemoryOperand(current->Operand2);
                    RegisterRemainder=SetRegisterOperand(reg_rem);
                    reg2=Chosex86Register(current->Operand2);
                    if(reg2>=0)
                        {
                        SetRegister(reg2,current->Operand2,1);
                        Register2=SetRegisterOperand(reg2);
                        
                        if(Operand2.IsLiteral==true)
                            Operand2.IsReference=true;
                        
                    Generatex86Instruction(mov,GetRegisterWordSize(reg2),Register2,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Operand2=Register2;
                        }
                    else
                        {
                        int iLength,OpCode,reg2_save;
                        struct Operand RegisterTemp;
                        reg2=reg2*-1;
                        Operand2=SetRegisterOperand(reg2);
                        SetRegister(reg2,current->Operand2,1); 
                        }
                     
                    if(IsSigned(current->Operand1))
                        OpCodeOperand=idiv;
                    else
                    OpCodeOperand=Div;
                    Operand1.IsValid=false;

                    Generatex86Instruction(OpCodeOperand,none,Operand2,Operand1,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    Result=SetMemoryOperand(current->Result);
                    Generatex86Instruction(mov,GetRegisterWordSize(RegisterRemainder.Register),Result,RegisterRemainder,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
					reg_result=GetSymbolRegister(Result.SymTabPos);
					if(reg_result!=-1)
						SetRegister(reg_result,-1,0);
                    UnLockRegister(reg1);
                    UnLockRegister(reg2);
                    SetRegister(reg_rem,current->Result,0);
                    }
					if(current->Operator==GetOperatorId("SetEBX"))
					{
						struct Operand Operand1,EBXRegister;
						EBXRegister=SetRegisterOperand(EBX);
						Operand1=SetMemoryOperand(current->Operand1);
						strcpy(szAsmInstruction,"push EBX\n");
						AddOutputASM(LpszLabel,szAsmInstruction);
                       LpszLabel=NULL;
						if(!IsReference(current->Operand1))
							Operand1.IsReference=false;
						if(GetDataType(current->Operand1)==GetDataTypeId("Pointer"))
							Operand1.IsReference=true;

						Generatex86Instruction(mov,dword,EBXRegister,Operand1,szAsmInstruction);
                        AddOutputASM(LpszLabel,szAsmInstruction);
						
					}
					if(current->Operator==GetOperatorId("UnSetEBX"))
					{
						
						strcpy(szAsmInstruction,"pop EBX\n");
						AddOutputASM(LpszLabel,szAsmInstruction);
					}
                if(current->Operator==GetOperatorId("^"))
                    {
                    int reg1,reg2,reg3,OpCodeOperand1,OpCodeOperand2,Size,OpCodeOperand,reg_result;
                    struct Operand Operand1,Operand2,Operand3,Result;
                    struct Operand Register1,Register2,Register3;
                    char szTempSymbolBuf[MAX_SYM_LEN],szTempLabel[MAX_LABEL_LEN];
                    OpCodeOperand1=mov;
                    OpCodeOperand2=mov;     
                    Size=CompareSize(current->Operand1,current->Operand2);
                    Operand1=SetMemoryOperand(current->Operand1);
                         reg1=Chosex86Register(current->Operand1);
                         if(reg1>=0)
                             {
                              Register1=SetRegisterOperand(reg1);
                              SetRegister(reg1,current->Operand1,1);
                              if(Operand1.IsLiteral==true)
                                Operand1.IsReference=false;
                              Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                              AddOutputASM(LpszLabel,szAsmInstruction);
                              Operand1=Register1;
                             }
                         else
                             {
                             int iLength,OpCode,reg1_save;
                             struct Operand RegisterTemp;
                             reg1=reg1*-1;
                             Operand1=SetRegisterOperand(reg1);
                             SetRegister(reg1,current->Operand1,1);
                             }
                    if((reg1>=ah)&&(reg1<=dl))
                        {
                        int reg1_save;
                        if(IsSigned(current->Operand1))
                            OpCodeOperand1=movsx;
                        else
                            OpCodeOperand1=movzx;
                        reg1_save=reg1;
                        reg1=GetRegister(16);
                        Register1=SetRegisterOperand(reg1);
                        SetRegister(reg1,-1,1);
                        Generatex86Instruction(OpCodeOperand1,none,Register1,Operand1,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Operand1=Register1;
                    UnLockRegister(reg1_save);
                        }
                    Operand2=SetMemoryOperand(current->Operand2);
                    
                    reg2=Chosex86Register(current->Operand2);
                    if(reg2>=0)
                        {
                        SetRegister(reg2,current->Operand2,1);
                        Register2=SetRegisterOperand(reg2);
                        
                        if(Operand2.IsLiteral==true)
                            Operand2.IsReference=true;
                        
                    Generatex86Instruction(mov,GetRegisterWordSize(reg2),Register2,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Operand2=Register2;
                        }
                    else
                        {
                        int iLength,OpCode,reg2_save;
                        struct Operand RegisterTemp;
                        reg2=reg2*-1;
                        Operand2=SetRegisterOperand(reg2);
                        SetRegister(reg2,current->Operand2,1); 
                        }
                     

                    if(IsSigned(current->Operand2))
                        OpCodeOperand2=movsx;
                    else
                    OpCodeOperand2=movzx;
                    SetRegister(ECX,-1,1);
                    Operand3=SetRegisterOperand(ECX);
                    Generatex86Instruction(OpCodeOperand2,none,Operand3,Operand2,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    if(IsSigned(current->Operand1))
                        OpCodeOperand=imul;
                    else
                    OpCodeOperand=mul;
                    
                    reg3=GetRegister(GetRegisterSize(Operand1.Register)*8);
                    Register3=SetRegisterOperand(reg3);
                    SetRegister(reg3,-1,1);
                    strcpy(szAsmInstruction,"mov ");
                    strcat(szAsmInstruction,Getx86RegisterName(reg3));
                    strcat(szAsmInstruction,",0x1\n" );
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    strcpy(szTempLabel,GenerateTempLabel());
                    AddOutputASM(szTempLabel,"");
                    Generatex86Instruction(OpCodeOperand,none,Register3,Operand1,szAsmInstruction);    
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    strcpy(szAsmInstruction,"loop ");
                    strcat(szAsmInstruction,szTempLabel);
                    strcat(szAsmInstruction,"\n");
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    Result=SetMemoryOperand(current->Result);
                    Generatex86Instruction(mov,GetRegisterWordSize(reg1),Result,Register3,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    
                    reg_result=GetSymbolRegister(Result.SymTabPos);
					if(reg_result!=-1)
						SetRegister(reg_result,-1,0);
                    
                    if(Operand1.IsRegister==true)
                        {
                        SetRegister(Operand1.Register,current->Result,0);
                        UnLockRegister(Operand1.Register);
                        }
                        
                    if((reg2>0)&&(reg2<25))
                        {
                        UnLockRegister(reg2);
                        }
                    
                    }
                if(current->Operator==GetOperatorId("CALL"))
                    {
                    Optab * Parameters;
					struct Operand RegisterOperand,Operand1,Register1;

                    if(strcmp(SymTab[current->Operand1].Symbol,"print_int_win")==0)
                        {
                        char szTempLenBuf[6];
                        int Param;
						
                        //Parameters=current->Operand2;
                        Param=current->Operand2;
                        
                                                        if((GetDataType(Param)==GetDataTypeId("int32"))||(GetDataType(Param)==GetDataTypeId("uint32")))
                        {
							if(IsReference(Param))
							{
								RegisterOperand=SetRegisterOperand(EAX);
								Operand1=SetMemoryOperand(Param);
								Generatex86Instruction(mov,dword,RegisterOperand,Operand1,szAsmInstruction);
								AddOutputASM(LpszLabel,szAsmInstruction);
								strcpy(szAsmInstruction,"push ");
								strcat(szAsmInstruction,Getx86RegisterName(RegisterOperand.Register));
							}
							else
							{
                        strcpy(szAsmInstruction,"push dword [EBP-0x");
                        itoa(GetSymbolAddress(Param),szTempLenBuf,16);
                        strcat(szAsmInstruction,szTempLenBuf);
                        strcat(szAsmInstruction,"]\n");
                        AddOutputASM("",szAsmInstruction);    
							}
                        }
                         else if((GetDataType(Param)==GetDataTypeId("int16"))||(GetDataType(Param)==GetDataTypeId("uint16")))
                        {
							
								RegisterOperand=SetRegisterOperand(ax);
								Operand1=SetMemoryOperand(Param);
								Generatex86Instruction(mov,word,RegisterOperand,Operand1,szAsmInstruction);
								AddOutputASM(LpszLabel,szAsmInstruction);
							
							
                        if(IsSigned(Param))
                        strcpy(szAsmInstruction,"movsx EAX,ax\npush EAX\n");
                        else
                            strcpy(szAsmInstruction,"movzx EAX,ax\npush EAX\n");
                        AddOutputASM("",szAsmInstruction);
                        
                        }
                         else if((GetDataType(Param)==GetDataTypeId("int8"))||(GetDataType(Param)==GetDataTypeId("uint8")))
                        {
							if(IsReference(Param))
							{
								RegisterOperand=SetRegisterOperand(al);
								Operand1=SetMemoryOperand(Param);
								Generatex86Instruction(mov,byte,RegisterOperand,Operand1,szAsmInstruction);
								AddOutputASM(LpszLabel,szAsmInstruction);
							}
							else
							{
								RegisterOperand=SetRegisterOperand(al);
								Operand1=SetMemoryOperand(Param);
								Generatex86Instruction(mov,byte,RegisterOperand,Operand1,szAsmInstruction);

						AddOutputASM(LpszLabel,szAsmInstruction);
							}
                        if(IsSigned(Param))
                        strcpy(szAsmInstruction,"movsx EAX,al\npush EAX\n");
                        else
                            strcpy(szAsmInstruction,"movzx EAX,al\npush EAX\n");
                        AddOutputASM("",szAsmInstruction);
                        }
                            
                            
					if(IsSigned(Param))	
					AddOutputASM("","push dword int_format\n call _printf\n pop EAX\npop EAX\n");
                        else
                            AddOutputASM("","push dword uint_format\n call _printf\n pop EAX\npop EAX\n");

                         //cirrect for literal and unsigned integer
                        
                        
                        }
                    else if(strcmp(SymTab[current->Operand1].Symbol,"print_addr_win")==0)
                        {
                            int reg1;
                            
                            Register1=SetRegisterOperand(EAX);
                            LockRegister(EAX);
                            Operand1=SetMemoryOperand(current->Operand2);

								Generatex86Instruction(mov,dword,Register1,Operand1,szAsmInstruction);
                                AddOutputASM(LpszLabel,szAsmInstruction);
                        AddOutputASM("","push EAX \npush dword hex_format\n call _printf\n pop EAX \n pop EAX\n");
                        UnLockRegister(EAX);
                        }

                    else if(strcmp(GetSymbolName(current->Operand1),"print_str_win")==0)
                        {
                            int reg1;
                            
                            Register1=SetRegisterOperand(EAX);
                            LockRegister(EAX);
                            Operand1=SetMemoryOperand(current->Operand2);

								Generatex86Instruction(mov,dword,Register1,Operand1,szAsmInstruction);
                                AddOutputASM(LpszLabel,szAsmInstruction);
                        AddOutputASM("","push EAX\npush dword string_format\n call _printf\n pop EAX\npop EAX\n");
                        UnLockRegister(EAX);
                        }
					else if(strcmp(SymTab[current->Operand1].Symbol,"fprint_int_win")==0)
					{
						int Param;
						Param=current->Operand2;
						//AddOutputASM("","mov dword [ESPSave],ESP\nmov dword ESP,[ESPOrg]\n");
						if ((GetDataType(Param)==GetDataTypeId("int8"))||(GetDataType(Param)==GetDataTypeId("uint8")))
						RegisterOperand=SetRegisterOperand(al);
						else
							RegisterOperand=SetRegisterOperand(ax);
								Operand1=SetMemoryOperand(Param);
								Generatex86Instruction(mov,GetRegisterSize(RegisterOperand.Register),RegisterOperand,Operand1,szAsmInstruction);

						AddOutputASM(LpszLabel,szAsmInstruction);
						if(IsSigned(Param))
							if ((GetDataType(Param)==GetDataTypeId("int8")))
								strcpy(szAsmInstruction,"movsx EAX,al\n");
							else
								strcpy(szAsmInstruction,"movsx EAX,ax\n");
                        else
							if ((GetDataType(Param)==GetDataTypeId("uint8")))
								strcpy(szAsmInstruction,"movzx EAX,al\n");
							else
								strcpy(szAsmInstruction,"movzx EAX,ax\n");
                        AddOutputASM("",szAsmInstruction);
						AddOutputASM("","call fprint_int_win\n");
						SetRegister(EDI,-1,0);
					}
                    else if(strcmp(GetSymbolName(current->Operand1),"print_ascii_os")==0)
                        {
                        struct Operand alRegister,character,Register1;
                        int reg1;
                        //AddOutputASM("","pusha\n");
                        Register1=SetRegisterOperand(al);
                        character=SetMemoryOperand(current->Operand2);
                        SetRegister(al,current->Operand2,1);
                        Generatex86Instruction(mov,byte,Register1,character,szAsmInstruction);
                        AddOutputASM("",szAsmInstruction);
                        AddOutputASM("","pusha\nmov ah,0x0E\n");
                        AddOutputASM("","int 0x10\npopa\n");
                        UnLockRegister(al);
                        }
                    else
                        {
                        int iReturnDataType,iReturnSize,iCount,iLength,iModulus,SymId,FunctionID,iMemberCall;
                        char szLengthBuf[8],szTempReturnName[MAX_SYM_LEN],szTempLabel[MAX_LABEL_LEN],szClassName[MAX_SYM_LEN];
						char *LpszFunctionName,szFunctionName[MAX_SYM_LEN];
                        struct Operand Operand1,EDIRegister,ESIRegister,Operand2;
						iReturnSize=0;
                        LpszFunctionName=GetSymbolName(current->Operand1);
						iMemberCall=IsMemberCall(LpszFunctionName);
						if(iMemberCall==0)
						{
							strcpy(szClassName,szCurrentClass);
							strcpy(szFunctionName,LpszFunctionName);
						}
						else
						{
							strncpy(szClassName,LpszFunctionName,iMemberCall);
							strcpy(szFunctionName,LpszFunctionName+iMemberCall);
						}

                        strcpy(szAsmInstruction,"add EDI,0x1\nsub EDI,0x"); //Adding Location to set the return Datatype,Future  i am looking for multiple return values
                        itoa(iReturnSize,szLengthBuf,16);
                        strcat(szAsmInstruction,szLengthBuf);
                        strcat(szAsmInstruction,"\n");
                        AddOutputASM(LpszLabel,szAsmInstruction);
                        
                        if(LpszLabel!=NULL)
                            LpszLabel=NULL;
                        
                        strcpy(szAsmInstruction,"push EBP\n mov EBP,ESP\n sub EBP,0x4\ncall ");
                        //strcpy(szTempFuncName,SymTab[current->Operand1].Symbol);
                        /*for(i=0;i<FunctionCount;i++)
                            {
                            if((FunctionTable[i].Func_Name,szTempFuncName)==0)
                                break; //need error routine for missing functions
                            }*/
                        strcat(szAsmInstruction,LpszFunctionName);
                        strcat(szAsmInstruction,"\n");
                        AddOutputASM(LpszLabel,szAsmInstruction);
                        AddOutputASM(LpszLabel,"pop EBP\n");
                        
                        
                       
                        SymId=current->Result;
                        Operand2=SetMemoryOperand(SymId);
						if(IsPrimitive(SymId))
						{
							int reg;
							if((GetDataType(SymId)==GetDataTypeId("int8"))||((GetDataType(SymId)==GetDataTypeId("uint8")))||(GetDataType(SymId)==GetDataTypeId("char")))
							 reg=al;
							else if((GetDataType(SymId)==GetDataTypeId("int16"))||((GetDataType(SymId)==GetDataTypeId("uint16"))))
							 reg=ax;
							else
							 reg=EAX;
							Register1=SetRegisterOperand(reg);
							Generatex86Instruction(mov,GetRegisterWordSize(reg),Operand2,Register1,szAsmInstruction);
							AddOutputASM(LpszLabel,szAsmInstruction);
						}
						else
						{
							Operand2.IsReference=false;
							EDIRegister=SetRegisterOperand(EDI);
							ESIRegister=SetRegisterOperand(ESI);
							LockRegister(EAX);
							Generatex86Instruction(mov,dword,EDIRegister,Operand2,szAsmInstruction);
							AddOutputASM(LpszLabel,szAsmInstruction);
							Register1=SetRegisterOperand(EAX);
							Generatex86Instruction(mov,dword,ESIRegister,Register1,szAsmInstruction);
							AddOutputASM(LpszLabel,szAsmInstruction);
							iLength=DataTypeTable[GetDataType(current->Result)].m_iDataTypeSize;
                            iCount=iLength/4;
                            iModulus=iLength%4;
                            if(iCount!=0)
                                    {
                            UnLockRegister(ECX);
                            itoa(iCount,szLengthBuf,16); //unlock ECX
                            strcpy(szAsmInstruction,"mov dword ECX,0x");
                            strcat(szAsmInstruction,szLengthBuf);
                            strcat(szAsmInstruction,"\n");
                            AddOutputASM("",szAsmInstruction);
                            strcpy(szTempLabel,GenerateTempLabel());
                            
                            AddOutputASM(szTempLabel,"mov dword EAX,[ESI]\n");
                            AddOutputASM("","mov dword [EDI],EAX\n add ESI,4\n add EDI,4\n");
                            strcpy(szAsmInstruction,"LOOP ");
                            strcat(szAsmInstruction,szTempLabel);
                            strcat(szAsmInstruction,"\n");
                            AddOutputASM("",szAsmInstruction);
                                }
                            if(iModulus==3)
                                {
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n");
                                
                                }
                            if(iModulus==2)
                                {
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n");
                                
                                }
                            if(iModulus==1)
                                {
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n");
                                }
						}
                        
                        
                        
                        
                        }
						//SetRegister(ESI,-1,0);
						ClearRegs();
                    }
                if(current->Operator==GetOperatorId("PUSH_FUN_PAR"))
                    {     
                    
                     Optab *LpPrevious,*LpNext;
                     char szLengthBuffer[8],szLengthBuffer2[8],szTempLabel[MAX_LABEL_LEN];
                     struct Operand Operand1,Register2;
                     int iLength,iModulus,iCount,iSize;
					 
                     LpPrevious=current->previous;
                     LpNext=current->next;
                     SetRegister(EDI,-1,1);
                     szLengthBuffer2[0]='\0';
					 LockRegister(ESI);
                     if(LpPrevious->Operator!=GetOperatorId("PUSH_FUN_PAR"))
                         {
                         strcpy(szAsmInstruction,"mov EDI,ESP\n sub EDI,0x8\n"); //8 for EBP and return address 
                         AddOutputASM(LpszLabel,szAsmInstruction);
                         }
                     
                     Operand1=SetMemoryOperand(current->Operand1);
                     
					 if(IsLiteral(current->Operand1))
					 {
						 iSize=GetDatatypeSize(current->Operand1);
						 itoa(iSize,szLengthBuffer,16);
						 strcpy(szAsmInstruction,"sub EDI,0x");
						 strcat(szAsmInstruction,szLengthBuffer);
						 strcat(szAsmInstruction,"\n");
						 AddOutputASM(LpszLabel,szAsmInstruction);
						 Register2=SetRegisterOperand(EDI);
						 Register2.IsReference=true;
						 Generatex86Instruction(mov,iSize,Register2,Operand1,szAsmInstruction);
						 AddOutputASM(LpszLabel,szAsmInstruction);
						 AddOutputASM(LpszLabel,"dec EDI");
					 }
					 else
					 {
						 Register2=SetRegisterOperand(ESI);
						 Operand1.IsReference=false;
						 

					 
                     Generatex86Instruction(mov,dword,Register2,Operand1,szAsmInstruction);
                            AddOutputASM(LpszLabel,szAsmInstruction);
                            
                     if(IsReference(current->Operand1))
                                iLength=DataTypeTable[SymTab[current->Operand1].PointerTarget].m_iDataTypeSize;
                            else
                                iLength=DataTypeTable[GetDataType(current->Operand1)].m_iDataTypeSize;
                      iCount=iLength/4;
                            iModulus=iLength%4;
							
                     
							 itoa(iLength,szLengthBuffer2,16);
							 
                          
						  
						  
							 strcpy(szAsmInstruction,"sub EDI,0x");
                          
                          strcat(szAsmInstruction,szLengthBuffer2);
                          strcat(szAsmInstruction,"\n");
                          AddOutputASM(LpszLabel,szAsmInstruction);
                        
                            
                            if(iCount!=0)
                                    {

                            UnLockRegister(ECX);
                            itoa(iCount,szLengthBuffer,16); //unlock ECX
                            strcpy(szAsmInstruction,"mov dword ECX,0x");
                            strcat(szAsmInstruction,szLengthBuffer);
                            strcat(szAsmInstruction,"\n");
                            AddOutputASM("",szAsmInstruction);
                            strcpy(szTempLabel,GenerateTempLabel());
                            
                            AddOutputASM(szTempLabel," mov dword EAX,[ESI]\n");
                            AddOutputASM("","mov dword [EDI],EAX\n add ESI,0x4\n add EDI,0x4\n");
                            strcpy(szAsmInstruction,"LOOP ");
                            strcat(szAsmInstruction,szTempLabel);
                            strcat(szAsmInstruction,"\n");
                            AddOutputASM("",szAsmInstruction);
                                }
                            if(iModulus==3)
                                {
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                
                                }
                            if(iModulus==2)
                                {
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                
                                }
                            if(iModulus==1)
                                {
                                AddOutputASM("","mov byte ah,[ESI]\n mov byte [EDI],ah \n inc ESI \n inc EDI\n");
                                }
							 strcpy(szAsmInstruction,"sub EDI,0x");
                          
                          strcat(szAsmInstruction,szLengthBuffer2);
                          strcat(szAsmInstruction,"\n");
                          AddOutputASM(LpszLabel,szAsmInstruction);
					 
                         }
					 SetRegister(EDI,-1,1);
					 UnLockRegister(ESI);
                    }
                if(current->Operator==GetOperatorId("cast"))
                    {
						int Param,reg_result;
						char *LpszSymbolName;
						
						
                    
                        int reg1,reg2,OpCode,iCompareSize;
                        struct Operand Register1,Operand1,Register2,Result;
						Param=current->Operand1;
                        reg1=Chosex86Register(Param);
                        Operand1=SetMemoryOperand(Param);
						Operand1.IsReference=true;
                        if(reg1>0)
                            {
                            Register1=SetRegisterOperand(reg1);
                            SetRegister(reg1,Param,1);
                            Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                            AddOutputASM(LpszLabel,szAsmInstruction);
							LpszLabel=NULL;
                            }
                        else
                            {
                            reg1=reg1*-1;
                            Register1=SetRegisterOperand(reg1);
                            SetRegister(reg1,current->Operand1,1);
                            }
                        reg2=GetRegister(GetDatatypeSize(current->Result)*8);
                        Register2=SetRegisterOperand(reg2);
                        iCompareSize=CompareSize(current->Result,current->Operand1);
                            if(iCompareSize==current->Result)
                                {
                                if(IsSigned(Param))
                                    OpCode=movsx;
                                else
                                    OpCode=movzx;
                                Generatex86Instruction(OpCode,none,Register2,Register1,szAsmInstruction);
                                AddOutputASM(LpszLabel,szAsmInstruction);
								LpszLabel=NULL;
                                }
                            else
                                {
                                int reg3;
                                struct Operand Register3;
                                reg3=GetLowerRegister(reg1);
                                Register3=SetRegisterOperand(reg3);
                                Generatex86Instruction(mov,none,Register2,Register3,szAsmInstruction);
                                AddOutputASM(LpszLabel,szAsmInstruction);
								LpszLabel=NULL;
                                }
                            Result=SetMemoryOperand(current->Result);
                            Generatex86Instruction(mov,GetRegisterWordSize(Register2.Register),Result,Register2,szAsmInstruction);
                                AddOutputASM("",szAsmInstruction);
						/*		reg_result=GetSymbolRegister(Result.SymTabPos);
						if(reg_result!=-1)
						SetRegister(reg_result,-1,0);*/
                        UnLockRegister(reg2);
						UnLockRegister(reg1);
					
                    }
                if(current->Operator==GetOperatorId("return"))
                    {     
                    
                     Optab *LpPrevious,*LpNext;
                     char szLengthBuffer[8],szTempLabel[MAX_LABEL_LEN];
                     struct Operand Operand1,Register2,RegisterEDI,Operand2,Register_org;
                     int iLength,iModulus,iCount,SymId,reg,reg_org;
					 if(current->Operand1==-1)
					 {
						 
					 }
                     else if(IsPrimitive(current->Operand1))
					 {
						 if((GetDataType(current->Operand1)==GetDataTypeId("int8"))||((GetDataType(current->Operand1)==GetDataTypeId("uint8")))||(GetDataType(current->Operand1)==GetDataTypeId("char")))
							 reg=al;
						 else if((GetDataType(current->Operand1)==GetDataTypeId("int16"))||((GetDataType(current->Operand1)==GetDataTypeId("uint16"))))
							 reg=ax;
						 else
							 reg=EAX;
						 SetRegister(EAX,-1,0);
						 reg_org=Chosex86Register(current->Operand1);
						 Register2=SetRegisterOperand(reg);
						 if(reg_org>=0)
						 {
							 Operand1=SetMemoryOperand(current->Operand1);
							 Generatex86Instruction(mov,GetRegisterWordSize(reg),Register2,Operand1,szAsmInstruction);
							 AddOutputASM(LpszLabel,szAsmInstruction);
						 }
						 else
						 {
							 Register_org=SetRegisterOperand(reg_org*-1);
							 Generatex86Instruction(mov,GetRegisterWordSize(reg),Register2,Register_org,szAsmInstruction);
							 AddOutputASM(LpszLabel,szAsmInstruction);
						 }
						 LpszLabel=NULL;
					 }
					 else
					 {
						 Register2=SetRegisterOperand(EAX);
						 Operand1=SetMemoryOperand(current->Operand1);
						 Operand1.IsReference=false;
						 Generatex86Instruction(mov,GetRegisterWordSize(reg),Register2,Operand1,szAsmInstruction);
					     AddOutputASM(LpszLabel,szAsmInstruction);
						 LpszLabel=NULL;

					 }
					 strcpy(szAsmInstruction,"jmp ");
					 strcat(szAsmInstruction,"Epilogue_");
					 strcat(szAsmInstruction,FunctionDetails.szFunctionLabel);
					 strcat(szAsmInstruction,"\n");
					 AddOutputASM(LpszLabel,szAsmInstruction);
                                             
                    }
                if(current->Operator==GetOperatorId("comp"))
                    {
                    int reg1,reg2,OpCodeOperand1,OpCodeOperand2,Size,reg_result;
                    struct Operand Operand1,Operand2,Result;
                    struct Operand Register1,Register2,Register3;
                    char szTempSymbolBuf[MAX_SYM_LEN];
                    OpCodeOperand1=mov;
                    OpCodeOperand2=mov;     
                    Size=CompareSize(current->Operand1,current->Operand2);
                    Operand1=SetMemoryOperand(current->Operand1);
                    if(Operand1.IsImmediate==false) 
                        {
                         reg1=Chosex86Register(current->Operand1);
                         if(reg1>=0)
                             {
                              Register1=SetRegisterOperand(reg1);
                              SetRegister(reg1,current->Operand1,1);
                              if(Operand1.IsLiteral==true)
                                Operand1.IsReference=false;
                              Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                              AddOutputASM(LpszLabel,szAsmInstruction);
                              if(LpszLabel!=NULL)
                                  LpszLabel=NULL;
                              Operand1=Register1;
                             }
                         else
                             {
                             int iLength,OpCode,reg1_save;
                             struct Operand RegisterTemp;
                             reg1=reg1*-1;
                             Operand1=SetRegisterOperand(reg1);
                             SetRegister(reg1,current->Operand1,1);
                             }
                        }
                    Operand2=SetMemoryOperand(current->Operand2);
                    if(Operand2.IsImmediate==false)
                            {
                    reg2=Chosex86Register(current->Operand2);
                    if(reg2>=0)
                        {
                        SetRegister(reg2,current->Operand2,1);
                        Register2=SetRegisterOperand(reg2);
                        
                        if(Operand2.IsLiteral==true)
                            Operand2.IsReference=true;
                        
                    Generatex86Instruction(mov,GetRegisterWordSize(reg2),Register2,Operand2,szAsmInstruction);
                    if(LpszLabel!=NULL)
                                  LpszLabel=NULL;
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    Operand2=Register2;
                        }
                    else
                        {
                        int iLength,OpCode,reg2_save;
                        struct Operand RegisterTemp;
                        reg2=reg2*-1;
                        Operand2=SetRegisterOperand(reg2);
                        SetRegister(reg2,current->Operand2,1); 
                        }
                     }
                    Generatex86Instruction(cmp,none,Operand1,Operand2,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    if(LpszLabel!=NULL)
                                  LpszLabel=NULL;
                    if(Operand1.IsRegister==true)
                        {
                        UnLockRegister(Operand1.Register);
                        }
                    if(Operand2.IsRegister==true)
                        {
                        UnLockRegister(Operand2.Register);
                        }
                    }
                if(current->Operator==GetOperatorId("ClearRegs"))
                    {
                    int i;
                    i=0;
                    for(i=0;i<=dl;i++)
                        {
							if((i!=EBX)&&(i!=bx)&&(i!=bh)&&(i!=bl))
							{
                        x86RegSet[i].Register=-1;
                        x86RegSet[i].locked=false;
						x86RegSet[i].Rank=0;
							}
                        }
                    }
                if(current->Operator==GetOperatorId("||"))
                    {
                    int reg1,reg2,OpCodeOperand1,OpCodeOperand2,Size,reg_result;
                    struct Operand Operand1,Operand2,Result;
                    struct Operand Register1,Register2,Register3;
                    char szTempSymbolBuf[MAX_SYM_LEN];
                    OpCodeOperand1=mov;
                    OpCodeOperand2=mov;     
                    Size=CompareSize(current->Operand1,current->Operand2);
                    Operand1=SetMemoryOperand(current->Operand1);
                    if(Operand1.IsImmediate==false) 
                        {
                         reg1=Chosex86Register(current->Operand1);
                         if(reg1>=0)
                             {
                              Register1=SetRegisterOperand(reg1);
                              SetRegister(reg1,current->Operand1,1);
                              if(Operand1.IsLiteral==true)
                                Operand1.IsReference=false;
                              Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                              AddOutputASM(LpszLabel,szAsmInstruction);
							  LpszLabel="";
                              Operand1=Register1;
                             }
                         else
                             {
                             int iLength,OpCode,reg1_save;
                             struct Operand RegisterTemp;
                             reg1=reg1*-1;
                             Operand1=SetRegisterOperand(reg1);
                             SetRegister(reg1,current->Operand1,1);
                             }
                        }
                    Operand2=SetMemoryOperand(current->Operand2);
                    if(Operand2.IsImmediate==false)
                            {
                    reg2=Chosex86Register(current->Operand2);
                    if(reg2>=0)
                        {
                        SetRegister(reg2,current->Operand2,1);
                        Register2=SetRegisterOperand(reg2);
                        
                        if(Operand2.IsLiteral==true)
                            Operand2.IsReference=true;
                        
                    Generatex86Instruction(mov,GetRegisterWordSize(reg2),Register2,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Operand2=Register2;
                        }
                    else
                        {
                        int iLength,OpCode,reg2_save;
                        struct Operand RegisterTemp;
                        reg2=reg2*-1;
                        Operand2=SetRegisterOperand(reg2);
                        SetRegister(reg2,current->Operand2,1); 
                        }
                     }
                    Generatex86Instruction(or,none,Operand1,Operand2,szAsmInstruction);
                    AddOutputASM(LpszLabel,szAsmInstruction);
                    Result=SetMemoryOperand(current->Result);
                    Generatex86Instruction(mov,GetRegisterWordSize(reg1),Result,Operand1,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    reg_result=GetSymbolRegister(Result.SymTabPos);
					if(reg_result!=-1)
						SetRegister(reg_result,-1,0);
                    UnLockRegister(reg2);
                    if(Register1.IsRegister==true)
                        {
                    SetRegister(Register1.Register,current->Result,0);
                    UnLockRegister(reg1);
                        }
                    }
                if(current->Operator==GetOperatorId("&&"))
                    {
                    int reg1,reg2,OpCodeOperand1,OpCodeOperand2,Size,reg_result;
                    struct Operand Operand1,Operand2,Result;
                    struct Operand Register1,Register2,Register3;
                    char szTempSymbolBuf[MAX_SYM_LEN];
                    OpCodeOperand1=mov;
                    OpCodeOperand2=mov;     
                    Size=CompareSize(current->Operand1,current->Operand2);
                    Operand1=SetMemoryOperand(current->Operand1);
                    if(Operand1.IsImmediate==false) 
                        {
                         reg1=Chosex86Register(current->Operand1);
                         if(reg1>=0)
                             {
                              Register1=SetRegisterOperand(reg1);
                              SetRegister(reg1,current->Operand1,1);
                              if(Operand1.IsLiteral==true)
                                Operand1.IsReference=false;
                              Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                              AddOutputASM(LpszLabel,szAsmInstruction);
                              Operand1=Register1;
                             }
                         else
                             {
                             int iLength,OpCode,reg1_save;
                             struct Operand RegisterTemp;
                             reg1=reg1*-1;
                             Operand1=SetRegisterOperand(reg1);
                             SetRegister(reg1,current->Operand1,1);
                             }
                        }
                    Operand2=SetMemoryOperand(current->Operand2);
                    if(Operand2.IsImmediate==false)
                            {
                    reg2=Chosex86Register(current->Operand2);
                    if(reg2>=0)
                        {
                        SetRegister(reg2,current->Operand2,1);
                        Register2=SetRegisterOperand(reg2);
                        
                        if(Operand2.IsLiteral==true)
                            Operand2.IsReference=true;
                        
                    Generatex86Instruction(mov,GetRegisterWordSize(reg2),Register2,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Operand2=Register2;
                        }
                    else
                        {
                        int iLength,OpCode,reg2_save;
                        struct Operand RegisterTemp;
                        reg2=reg2*-1;
                        Operand2=SetRegisterOperand(reg2);
                        SetRegister(reg2,current->Operand2,1); 
                        }
                     }
                    Generatex86Instruction(and,none,Operand1,Operand2,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    Result=SetMemoryOperand(current->Result);
                    Generatex86Instruction(mov,GetRegisterWordSize(reg1),Result,Operand1,szAsmInstruction);
                    AddOutputASM("",szAsmInstruction);
                    reg_result=GetSymbolRegister(Result.SymTabPos);
					if(reg_result!=-1)
						SetRegister(reg_result,-1,0);
                    UnLockRegister(reg2);
                    if(Register1.IsRegister==true)
                        {
                    SetRegister(Register1.Register,current->Result,0);
                    UnLockRegister(reg1);
                        }
                    }
                if(current->Operator==GetOperatorId("ASM"))
                    {
                    char *LpCurrent,szTemp[90],*LpszRegisterName,cCurrent,*LpszCLine,*LpszVar,*LpszComma,szVar[MAX_SYM_LEN],szRegister[6];
                    int Count,flag;
					int iLineCount;
					char szComment[90];
					char szLabel[MAX_LABEL_LEN];
					int iSymId;

                    struct Operand Operand1,Register1;
					iLineCount=0;
                    LpCurrent=current->AsmPointer+1;
                    LpszCLine=strchr(LpCurrent,'\n');
					LpCurrent[LpszCLine-LpCurrent]='\0';
					LpszCLine++;
					ClearRegs();
					strcpy(szComment,";");
					strcat(szComment,LpCurrent);
					strcat(szComment,"\n");
					#if(CHECK_DEBUG_ENABLED(DEBUG_ASSEMBLYCOMMENTS))
					AddOutputASM(LpszLabel,szComment);
					#endif
					while(LpszCLine!=NULL)
					{
						
						flag=0;
						LpszVar=NULL;
						LpszComma=NULL;
						iSymId=-1;
						LpszLabel=NULL;
						LpszVar=strchr(LpCurrent,'&');
						if(LpszVar!=NULL)
							flag=1;
						if(flag==0)
						{
							LpszVar=strchr(LpCurrent,'@');
							if(LpszVar!=NULL)
								flag=1;
						}
						if(flag==1)
						{
							int reg1;
							char *LpszLABEL;
							LpszLABEL=strchr(LpCurrent,':');
							if(LpszLABEL!=NULL)
							{
								strncpy(szLabel,LpCurrent,LpszLABEL-LpCurrent);
								szLabel[LpszLABEL-LpCurrent]='\0';
								LpCurrent=LpszLABEL+1;
								LpszLabel=szLabel;
							}
							LpszComma=strchr(LpszVar,',');
							if(LpszComma!=NULL)
							{
								strcpy(szRegister,LpszComma+1);
								strncpy(szVar,LpszVar,LpszComma-LpszVar);
								szVar[LpszComma-LpszVar]='\0';
								iSymId=GetSymbolId(szVar+1);
								if(iSymId==-1) // This symbol is not in SYMTAB. add it to symtab(it means it is a object property)
								{
									iSymId=AddSymbol(szVar+1);
								}
								
							}
							else
							{
								iSymId=GetSymbolId(LpszVar+1);
								if(iSymId==-1)
								{
									iSymId=AddSymbol(LpszVar+1);
								}
								
							}
							strncpy(szTemp,LpCurrent,LpszVar-LpCurrent);
							szTemp[LpszVar-LpCurrent]='\0';
							Operand1=SetMemoryOperand(iSymId);
							
							
							
							
							if(LpszComma==NULL) //moving data from variable to register
							{
								if(LpszVar[0]=='@')
								{
									reg1=Chosex86Register(iSymId);
									if(reg1<0)
										reg1=reg1*-1;
								}
								else
								{
									Operand1.IsReference=false;
								 reg1=GetRegister(32);
								}
							
								Register1=SetRegisterOperand(reg1);
								Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                                AddOutputASM(LpszLabel,szAsmInstruction);
								strcat(szTemp,Getx86RegisterName(reg1));
								strcat(szTemp,"\n");
								AddOutputASM("",szTemp);
								
							}
							else
							{ //moving data from register to variable
								int iRegUsed;
								iRegUsed=GetRegisterID(szRegister);
								LockRegister(iRegUsed);
								reg1=GetRegister(32);
								Register1=SetRegisterOperand(reg1);
								Operand1.IsReference=false;
								Generatex86Instruction(mov,GetRegisterWordSize(reg1),Register1,Operand1,szAsmInstruction);
                                AddOutputASM(LpszLabel,szAsmInstruction);
								strcat(szTemp,memorysize_s[GetRegisterWordSize(iRegUsed)]);
								strcat(szTemp," [");
								strcat(szTemp,Getx86RegisterName(reg1));
								strcat(szTemp,"],");
								strcat(szTemp,Getx86RegisterName(iRegUsed));
								strcat(szTemp,"\n");
								AddOutputASM("",szTemp);
							}
							
							

						}
						else
						{
							strcpy(szTemp,LpCurrent);
							strcat(szTemp,"\n");
							AddOutputASM("",szTemp);
						}
						iLineCount++;
						LpCurrent=LpszCLine;
						if(strlen(LpszCLine)==0)
							break;
						LpszCLine=strchr(LpCurrent+1,'\n');
						if(LpszCLine!=NULL)
						{
							LpCurrent[LpszCLine-LpCurrent]='\0';
							LpszCLine++;
							strcpy(szComment,";");
							strcat(szComment,LpCurrent);
							strcat(szComment,"\n");
							#if(CHECK_DEBUG_ENABLED(DEBUG_ASSEMBLYCOMMENTS))
							if(flag==1)
							AddOutputASM("",szComment);
							#endif
						}
						//LpszCLine++;
					}
					iLineNo=iLineNo/2+iLineCount+2;
                    }
                if(current->Operator==GetOperatorId("%LockRegister"))
                    {
                    SetRegister(current->Operand1,-2,1);
                }
                if(current->Operator==GetOperatorId("%UnLockRegister"))
                    {
                    UnLockRegister(current->Operand1);
                }
                }
				#if CHECK_DEBUG_ENABLED(DEBUG_SHOW_OPTAB)
    printf("%s\n",Instruction);
	#endif
            
            LpPrevious=current;
			SetCurrentRegisterRank(current);
            current=current->next;
            if(current==Function_Start)
                {
                struct Operand RegisterEBP,Operand1,Operand2,RegisterESP;
                int SymId;
				#if(CHECK_DEBUG_ENABLED(DEBUG_ASSEMBLYCOMMENTS))
                AddOutputASM("",";writing Epilogue for function\n");
				#endif
				strcpy(szAsmInstruction,"Epilogue_");
				strcat(szAsmInstruction,FunctionDetails.szFunctionLabel);
				strcat(szAsmInstruction,":\n");
				strcat(szAsmInstruction,"add ESP,0x");
                strcat(szAsmInstruction,szTempLen);
				strcat(szAsmInstruction,"\n");
				AddOutputASM("",szAsmInstruction);
				if(strcmp(FunctionDetails.FunctionName,"main")==0)
				{
					AddOutputASM("main_hang","jmp main_hang\n");
				}
				if(FunctionDetails.iType==INTERRUPT_KW)
				{
				
				AddOutputASM("","add EBP,0x9\ninc ESP\n");
				}
				
				if(FunctionDetails.iType==INTERRUPT_KW)
				{
					AddOutputASM("","pop EBP\npop ESP\npopad\n");
				}
                
				if(iCompileOption==eUnitTest)
				{
					if(strcmp(FunctionDetails.FunctionName,"start")==0)
					strcpy(szAsmInstruction,"\npush dword 0\ncall [ExitProcess]");
				}
				if(FunctionDetails.iType==INTERRUPT_KW)
				{
					strcpy(szAsmInstruction,"\nsti\niret\n");
				}
				else
				{
                strcpy(szAsmInstruction,"ret \n\n");
				}
                AddOutputASM("",szAsmInstruction);
                break;
                }
            }
            

	}