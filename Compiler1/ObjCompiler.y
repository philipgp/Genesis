%{
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "Compiler.h"
#define YY_NO_UNISTD_H 1
extern int yylex();
//#define YYLEX_PARAM &yylval, &yylloc
extern FILE *yyin;
char basePath[255];

void yyerror(const char *str)
{
 fprintf(stderr,"error:Lineno:%d\n",iLineNo+1);
 //fprintf(stderr,"error:Lineno:%d\n",yyget_lineno());
 
}



int yywrap()
{
      return 1;
}
%}

%union 
{
int SymId;
struct Optab *optabs;
};

%token <SymId> INTEGER ID STRING DATATYPE ASMStatement DEREFERENCE CompilerRequest STRINGLITERAL
%token <optabs> MemberReference
%token WS AND_OP OR_OP LTE_OP GTE_OP IMPORT_KW NTE_OP ISE_OP IF_KW INTERRUPT_KW THN_KW EIF_KW STATEMENT_DELIM ELSE_KW TASK_KW ELSIF_KW WHILE_KW LOOP_KW ENDLOOP_KW LFT_SQ_BKT_OP RYT_SQ_BKT_OP FUNCTION_KW RETURNS_KW RETURN_KW COMMA_OP BREAK_LOOP_KW CONTINUE_LOOP_KW DATATYPE_KW WORKER_KW LFT_SIMP_BKT_OP RYT_SIMP_BKT_OP DEFINE_KW OBJECTTYPE_KW NEW_KW RYT_CRLY_BKT_OP LFT_CRLY_BKT_OP END_DEFINE_KW MINUS_OP MODULUS_OP IN_KW OUT_KW OPERATION_KW OPERATOR_KW 
%type <optabs> FunctionDeclaration
%type <optabs> ArrayAndMemberRef
%type <SymId> DefineObjectName
%type <SymId> DefineWorkerName
%type<SymId> ReturnsStatement
%type <optabs> AsmStatement
%type <optabs> FunctionBody
%type <optabs> Statement_Block
%type <optabs> Or_Logic_Expr
%type <optabs> And_Logic_Expr;
%type <optabs> Comp_Expr Relat_Expr;
%type <optabs> AddSub_Arith_Expr;
%type <optabs> MulDiv_Arith_Expr;
%type <optabs> Exp_Arith_Expr
%type <optabs> Assignment_Statement;
%type <optabs> Statement;
%type <optabs> If_Statement;
%type <optabs> Else_If_Statement;
%type <optabs> While_Statement;
%type <optabs> Declare_Statement;
%type <optabs> Declare_ID_List;
%type <optabs> DeclareID;
%type <optabs> DeclareSubscriptList;
%type <optabs> ExprID;
%type <optabs> ArrayReference
%type <optabs> FormalParameterList
%type <optabs> FunctionCall
%type <optabs> FunctionCallStatement
%type <optabs> CompilerRequestStatement
%type <optabs> ActualParameterList
%type <optabs> BreakStatement
%type <optabs> ContinueStatement;
%type <optabs> Datatype_Declaration
%type <optabs> Declare_Block
%type <optabs> FunctionBlock
%type <optabs> ObjectDefineBlock
%type <optabs> TaskBlock
%type <optabs> TaskDeclaration
%type <optabs> Program
%type <optabs> WorkerDefineBlock
%type <optabs> Forward_Declaration
%type <optabs> Objects
%type <optabs> NewStatement
%type <optabs> ServiceParameter
%type <optabs> AddressOfExpr
%type <optabs> DereferenceExpr
%type <optabs> Forward_Declaration_Block
%type <optabs> ObjectWithGlobals
%type <optabs> DatatypeOperations
%type <optabs> Datatype_Body_Block
%type <optabs> Datatype_Declare_Block
%type <optabs> Operator_Declaration
%%

Program :Forward_Declaration_Block Objects{$$=$2;} 
         | Forward_Declaration_Block WorkerDefineBlock{$$=$2;} 
         | WorkerDefineBlock{$$=$1;}
         | Objects{$$=$1;}
         | Objects Forward_Declaration_Block WorkerDefineBlock{$$=$2;}
         | Objects WorkerDefineBlock{}
         | Forward_Declaration_Block Objects WorkerDefineBlock{}


WorkerDefineBlock:DefineWorkerName Declare_Block TaskBlock END_DEFINE_KW{} 
                  |DefineWorkerName TaskBlock END_DEFINE_KW{}
Objects:Objects ObjectWithGlobals{$$=NULL;}
       |ObjectWithGlobals{$$=NULL;}
ObjectWithGlobals:ObjectDefineBlock{$$=NULL;}
                  |ObjectDefineBlock Declare_Block{$$=MakeGlobalVariable($2);}

ObjectDefineBlock: DefineObjectName Declare_Block FunctionBlock END_DEFINE_KW{TermOldBlock();$$=MakeObjectDefinition($1,$2,$3);}
                  |DefineObjectName FunctionBlock END_DEFINE_KW{TermOldBlock();$$=MakeObjectDefinition($1,NULL,$2);}
                  |DefineObjectName Declare_Block END_DEFINE_KW{TermOldBlock();$$=MakeObjectDefinition($1,$2,NULL);}

FunctionBlock:FunctionBlock FunctionDeclaration{$$=ConcatSubscriptNode($1,$2);}
             |FunctionDeclaration{$$=$1;};

TaskBlock: TaskBlock TaskDeclaration{}|TaskDeclaration{}

TaskDeclaration: TASK_KW ID LFT_SIMP_BKT_OP RYT_SIMP_BKT_OP FunctionBody{TermOldBlock();$$=MakeTaskDeclaration($2,NULL,$5);}
                |TASK_KW ID LFT_SIMP_BKT_OP FormalParameterList RYT_SIMP_BKT_OP FunctionBody{TermOldBlock();$$=MakeTaskDeclaration($2,$4,$6);}

                

FunctionDeclaration: FUNCTION_KW ID LFT_SIMP_BKT_OP FormalParameterList RYT_SIMP_BKT_OP FunctionBody{TermOldBlock();$$=MakeFunctionDeclaration(0,$2,$4,$6,FUNCTION_KW);} 
                   | FUNCTION_KW ID LFT_SIMP_BKT_OP FormalParameterList RYT_SIMP_BKT_OP ReturnsStatement FunctionBody{TermOldBlock();$$=MakeFunctionDeclaration($6,$2,$4,$7,FUNCTION_KW);}
				   |FUNCTION_KW ID LFT_SIMP_BKT_OP RYT_SIMP_BKT_OP FunctionBody{TermOldBlock();$$=MakeFunctionDeclaration(0,$2,NULL,$5,FUNCTION_KW);} 
				   | FUNCTION_KW ID LFT_SIMP_BKT_OP  RYT_SIMP_BKT_OP ReturnsStatement FunctionBody{TermOldBlock();$$=MakeFunctionDeclaration($5,$2,NULL,$6,FUNCTION_KW);}
		  |INTERRUPT_KW ID LFT_SIMP_BKT_OP RYT_SIMP_BKT_OP FunctionBody{TermOldBlock();$$=MakeFunctionDeclaration(0,$2,NULL,$5,INTERRUPT_KW);}

FunctionBody:LFT_CRLY_BKT_OP Statement_Block RYT_CRLY_BKT_OP {$$=$2;}


Statement_Block:Statement_Block Statement{$$=MakeStatementBlock($1,$2);}
                |Statement{$$=$1;};

Statement:Assignment_Statement{$$=$1;}
         |If_Statement{$$=$1;}
          |While_Statement{$$=$1;}
          |FunctionCallStatement{$$=$1;} 
          |Declare_Statement{$$=$1;} 
          |BreakStatement{$$=$1;}
          |ContinueStatement{$$=$1;}
          |AsmStatement{$$=$1;}
          |Datatype_Declaration{$$=$1;}
          |CompilerRequestStatement{$$=$1;}
          |RETURN_KW AddSub_Arith_Expr ';'{$$=MakeReturnStatement($2);}
          |ServiceParameter{$$=$1;}
          |RETURN_KW';'{$$=MakeReturnStatement(NULL);}

Forward_Declaration_Block:Forward_Declaration{$$=$1;}
                          |Forward_Declaration_Block Forward_Declaration {$$=$1;}
Forward_Declaration:IMPORT_KW ID {$$=MakeForwardDeclaration($2);}
                   |Datatype_Declaration{$$=$1;}
          




ServiceParameter:IN_KW DATATYPE ID ID ';'{$$=MakeINparameter($2,$3,$4);}
                 |OUT_KW DATATYPE ID ID ';'{$$=MakeOUTparameter($2,$3,$4);}

CompilerRequestStatement:CompilerRequest{$$=$1;}

AsmStatement:ASMStatement{$$=$1;}

ReturnsStatement: RETURNS_KW DATATYPE{MakeReturnsStatement($2);$$=$2;}

While_Statement:WHILE_KW Or_Logic_Expr LOOP_KW Statement_Block ENDLOOP_KW{$$=MakeWhile($2,$4);}

If_Statement:IF_KW Or_Logic_Expr THN_KW Statement_Block EIF_KW{$$=MakeIfThen($2,$4);}
             |IF_KW Or_Logic_Expr THN_KW Statement_Block ELSE_KW Statement_Block EIF_KW{$$=MakeIfThenElse($2,$4,$6);}
             |IF_KW Or_Logic_Expr THN_KW Statement_Block Else_If_Statement EIF_KW{$$=MakeIfElseIf($2,$4,$5);}

Else_If_Statement:ELSIF_KW Or_Logic_Expr THN_KW Statement_Block ELSE_KW Statement_Block {$$=MakeElseIfElse($2,$4,$6);}
                  | ELSIF_KW Or_Logic_Expr THN_KW Statement_Block Else_If_Statement{$$=MakeElseIfElseIf($2,$4,$5);}
                  | ELSIF_KW Or_Logic_Expr THN_KW Statement_Block{$$=MakeElseIf($2,$4);}

Assignment_Statement:ExprID'='Or_Logic_Expr ';'{$$=MakeAssignment($1,$3);} 


Datatype_Declaration:DEFINE_KW DATATYPE_KW ID LFT_CRLY_BKT_OP Declare_Block RYT_CRLY_BKT_OP {TermOldBlock();$$=MakeStructDeclaration($3,$5);}
                    |DEFINE_KW DATATYPE_KW ID LFT_CRLY_BKT_OP Declare_Block Datatype_Body_Block RYT_CRLY_BKT_OP {TermOldBlock();$$=MakeStructDeclaration($3,$5);}

Datatype_Body_Block:Datatype_Body_Block DatatypeOperations{$$=ConcatSubscriptNode($1,$2);}
             |DatatypeOperations{$$=$1;};
DatatypeOperations: OPERATION_KW ID LFT_SIMP_BKT_OP Datatype_Declare_Block RYT_SIMP_BKT_OP ReturnsStatement FunctionBody{TermOldBlock();$$=MakeOperationDeclaration($6,$2,$4,$7);}
				   | OPERATION_KW ID LFT_SIMP_BKT_OP  RYT_SIMP_BKT_OP ReturnsStatement FunctionBody{TermOldBlock();$$=MakeOperationDeclaration($5,$2,NULL,$6);}
			 



Declare_Block:Declare_Block Declare_Statement{$$=AddToDeclareBlock($1,$2);}
              |Declare_Statement{$$=AddToDeclareBlock(NULL,$1);}



Declare_Statement:DATATYPE Declare_ID_List';'{$$=MakeDeclareStatement($1,$2);}

Datatype_Declare_Block:DATATYPE ID COMMA_OP Operator_Declaration COMMA_OP DATATYPE ID COMMA_OP {$$=$2;}

Or_Logic_Expr:Or_Logic_Expr OR_OP  And_Logic_Expr{Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("||"),$1,$3);}
              |And_Logic_Expr{$$=$1;}

And_Logic_Expr:And_Logic_Expr AND_OP Comp_Expr{struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("&&"),$1,$3);}
               |Comp_Expr{$$=$1;}

Comp_Expr:Comp_Expr ISE_OP Relat_Expr{struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("=="),$1,$3);}
          |Comp_Expr NTE_OP Relat_Expr{struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("!="),$1,$3);}
          |Relat_Expr{$$=$1;};

Relat_Expr:Relat_Expr '<' AddSub_Arith_Expr{struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("<"),$1,$3);}
           |Relat_Expr '>' AddSub_Arith_Expr{struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId(">"),$1,$3);}
           |Relat_Expr LTE_OP AddSub_Arith_Expr{struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("<="),$1,$3);}
           |Relat_Expr GTE_OP AddSub_Arith_Expr{struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId(">="),$1,$3);}
           |AddSub_Arith_Expr{$$=$1;}

AddSub_Arith_Expr:AddSub_Arith_Expr '+' MulDiv_Arith_Expr {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("+"),$1,$3);}
                 | AddSub_Arith_Expr MINUS_OP MulDiv_Arith_Expr {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("-"),$1,$3);}
                 | MulDiv_Arith_Expr { $$ = $1;}

MulDiv_Arith_Expr:MulDiv_Arith_Expr '*' Exp_Arith_Expr {struct  Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("*"),$1,$3);}
                  | MulDiv_Arith_Expr '/' Exp_Arith_Expr {struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("/"),$1,$3);}
                  |MulDiv_Arith_Expr MODULUS_OP Exp_Arith_Expr{struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("%"),$1,$3);}
                  | Exp_Arith_Expr { $$ = $1; }

Exp_Arith_Expr:ExprID '^' Exp_Arith_Expr{struct Optab * TempResult;TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$1,$3);$$=AddOperation(TempResult,GetOperatorId("^"),$1,$3);}
               |ExprID{$$=$1;} 


Declare_ID_List:DeclareID COMMA_OP Declare_ID_List{$$=ConcatSubscriptNode($1,$3);}
                |DeclareID{$$=$1;}

DeclareID:ID DeclareSubscriptList{struct Optab * ID_Node=MakeNode($1);$$=MakeDeclareIDSubscript(ID_Node,$2);}|ID{$$=MakeNode($1);}


DeclareSubscriptList:LFT_SQ_BKT_OP INTEGER RYT_SQ_BKT_OP{$$=MakeNode($2);}
                     |DeclareSubscriptList LFT_SQ_BKT_OP INTEGER RYT_SQ_BKT_OP {struct Optab * Subscript;Subscript=MakeNode($3);$$=ConcatSubscriptNode($1,Subscript);}




FunctionCallStatement:FunctionCall ';'{$$=$1;}


FunctionCall: ID LFT_SIMP_BKT_OP ActualParameterList AddSub_Arith_Expr RYT_SIMP_BKT_OP {$$=MakeFunctionCallMultipleParam($1,$3,$4);}
            | ID LFT_SIMP_BKT_OP AddSub_Arith_Expr RYT_SIMP_BKT_OP{$$=MakeFunctionCallSingleParam($1,$3);}
            |ID LFT_SIMP_BKT_OP RYT_SIMP_BKT_OP{$$=MakeFunctionCallNoParam($1);}
            |ArrayReference'.' ID LFT_SIMP_BKT_OP RYT_SIMP_BKT_OP{Optab *Nl=NULL;$$=ObjectArray_FunctionCall($1,$3,NULL,NULL);}
            |ArrayReference'.' ID LFT_SIMP_BKT_OP AddSub_Arith_Expr RYT_SIMP_BKT_OP{$$=ObjectArray_FunctionCall($1,$3,$5,NULL);}
  |ArrayReference'.' ID LFT_SIMP_BKT_OP ActualParameterList AddSub_Arith_Expr RYT_SIMP_BKT_OP{$$=ObjectArray_FunctionCall($1,$3,$6,$5);}



FormalParameterList:DATATYPE ID{$$=MakeDeclareStatement($1,MakeNode($2));}
                    |FormalParameterList COMMA_OP DATATYPE ID{struct Optab * ID_Node=MakeDeclareStatement($3,MakeNode($4));$$=ConcatSubscriptNode($1,ID_Node);}

ExprID:ID{$$=MakeNode($1);}
        |MINUS_OP ID{int SymIdOperand2;struct Optab *Operand2,*Operand1,*TempResult;Operand1=MakeNode($2);SymIdOperand2=AddSymbol("-1");Operand2=MakeNode(SymIdOperand2);TempResult=GenerateTempVariable();SetTempVariableInfo(TempResult,$2,NULL);$$=AddOperation(TempResult,GetOperatorId("*"),Operand1,Operand2);}
        |INTEGER{$$=MakeNode($1);}
        |MINUS_OP INTEGER{$$=MakeNegativeLiteral($2);}
        |ArrayReference{$$=$1;}
        |FunctionCall{$$=$1;}
        |MemberReference{$$=$1;}
        |LFT_SIMP_BKT_OP Or_Logic_Expr RYT_SIMP_BKT_OP{$$=$2;}
        |NewStatement{$$=$1;}
        |AddressOfExpr{$$=$1;}
        |DereferenceExpr{$$=$1;}
        |STRINGLITERAL{$$=MakeStringLiteral($1);}
         |ArrayAndMemberRef{$$=$1;}

Operator_Declaration:OPERATOR_KW '+'{}


ArrayAndMemberRef : ArrayReference '.' ID{$$=MakeArrayAndMemberRef($1,$3);}
AddressOfExpr: '&' ID {$$=MakeAddressOf($2);}
NewStatement:NEW_KW FunctionCall{$$=MakeNewStatment($2);}

DereferenceExpr:'@'LFT_SIMP_BKT_OP DATATYPE RYT_SIMP_BKT_OP ID{$$=MakeDereferenceOperation($3,$5);}
DefineObjectName:DEFINE_KW OBJECTTYPE_KW ID{$$=SetCurrentClassName($3);}


DefineWorkerName:DEFINE_KW WORKER_KW ID{$$=SetWorkerName($3);}

BreakStatement:BREAK_LOOP_KW ';'{struct Optab  * Operand1,*Operand2,*TempResult; Operand1=MakeNode(-1);Operand2=MakeNode(-1);TempResult=MakeNode(-1);$$=AddOperation(TempResult,GetOperatorId("BRK_LOOP"),Operand1,Operand2);}


ContinueStatement:CONTINUE_LOOP_KW ';'{struct Optab  * Operand1,*Operand2,*TempResult; Operand1=MakeNode(-1);Operand2=MakeNode(-1);TempResult=MakeNode(-1);$$=AddOperation(TempResult,GetOperatorId("CONT_LOOP"),Operand1,Operand2);}

ActualParameterList: AddSub_Arith_Expr COMMA_OP{$$=MakeFunctionCallAddFirstParam($1);}|ActualParameterList AddSub_Arith_Expr COMMA_OP{$$=MakeFunctionCallAddParam($1,$2);}  




ArrayReference:ID LFT_SQ_BKT_OP AddSub_Arith_Expr RYT_SQ_BKT_OP{$$=MakeSingleExprSubscript($1,$3);}
              |ArrayReference LFT_SQ_BKT_OP AddSub_Arith_Expr RYT_SQ_BKT_OP{$$=MakeExprSubscript($1,$3);}


              
%%

void ParseFile(char *LpszFileLocation)
{
FILE *fp,*fpsave;
printf("ParseFile:%s",LpszFileLocation);
fp=fopen(LpszFileLocation,"r");
if(fp==NULL)
{
printf("error opening file\n");
getch();
}
else
yyin=fp;
/*yydebug=1;*/
do
{
yyparse();
}while(!feof(yyin));
fclose(yyin);
}
void ProcessFile(char *LpszFileLocation)
{
char szFileName[255];
char szImportDec[8],szImportVal[32];
char *LpszFolder;
FILE *fp;
fp=NULL;
iLineNo=0;
LpszFolder=strrchr(LpszFileLocation,'\\');
if(LpszFolder!=NULL)
{
strncpy(basePath,LpszFileLocation,LpszFolder-LpszFileLocation+1);
}

if(strchr(LpszFileLocation,'\\')==NULL)
	{
		strcpy(szFileName,basePath);
		strcat(szFileName,LpszFileLocation);
		LpszFileLocation=szFileName;
	}
fp=fopen(LpszFileLocation,"r");
if(fp==NULL)
{
printf("error opening file %s\n",LpszFileLocation);
getch();
}
else
{
	while(1)
	{
fscanf(fp,"%s%s",&szImportDec,&szImportVal);
if(strcmp(szImportDec,"Import")==0)
{
//szImportVal[strlen(szImportVal)-1]='\0';
ProcessFile(szImportVal);
}
else
{
fclose(fp);
ParseFile(LpszFileLocation);
break;
}
	}
}

}
int main(int argc,char *argv[])
{
int i;
yyin=NULL;
basePath[0]='\0';
initDataTypeTable();

if(argc>2)
{
for(i=1;i<argc;i++)
{
if(argv[i][0]=='-')
{
if(argv[i][1]=='i')
{
ProcessFile(argv[++i]);
}
else if(argv[i][1]=='o')
{
initOutputFile(argv[++i]);
ProcessFile("C:\\Genesis\\SRC\\Compiler\\Compiler\\\Debug\\heapobject");
ProcessFile("C:\\Genesis\\SRC\\Compiler\\Compiler\\\Debug\\String.txt");
ProcessFile("C:\\Genesis\\SRC\\Compiler\\Compiler\\\Debug\\DisplayObj");

}
else if(argv[i][1]=='c')
{
++i;
if(argv[i][0]=='G')
iCompileOption = eGenesis;
else if(argv[i][0]=='W')
iCompileOption = eWindows;
else if(argv[i][0]=='U')
iCompileOption = eUnitTest;
}
}

}
}
printf("Compile Mode:%s",szCompileOption[iCompileOption]);
closeOutputFile();
//ParseFile("C:\\Users\\pgpanick\\Desktop\\DUMP\\Genesis\\SRC\\Compiler\\Compiler\\Debug\\input.txt");
//WriteToFile("C:\\Users\\pgpanick\\AppData\\Local\\nasm\\Compilerout.asm");
if(iCompileOption!=eUnitTest)
getch();
return 0;
}
