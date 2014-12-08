%{
#include <stdlib.h>
#include <stdio.h>
#include "ObjCompiler.tab.h"

int yywrap();
void yyerror(char*);
extern YYSTYPE yylval;
extern FILE *yyin;
//extern int iLineNo;
    
%}

%%
"_asm{"[\./`~\\\;\"\'\*\+\-\=\_\:\[\]a-zA-Z0-9, \'()\n@&_$]*"}" {yylval.optabs=AddAsm(yytext);return ASMStatement;}
"%"[a-zA-Z0-9()\n%&]*";" {yylval.optabs=GenerateCompilerRequest(yytext);return CompilerRequest;}
"\/\*"[a-zA-Z0-9()  \,:!@#$%^&*()-+;.]*"\*\/" {}
"[" {return LFT_SQ_BKT_OP;} 
"]" {return RYT_SQ_BKT_OP;} 
"(" {return LFT_SIMP_BKT_OP;}
")" {return RYT_SIMP_BKT_OP;}
[0-9]+ {;yylval.SymId=AddLiteral(yytext,0);;return INTEGER;}
[a-zA-Z][a-zA-Z.0-9_]* {int KW,DT,IsMember;struct Optab * MemReference;KW=SearchKWTable(yytext);if(KW!=-1)return KW;DT=SearchDataTypeTable(yytext);if(DT!=-1) { yylval.SymId=DT;return DATATYPE;}if(IsMember=IsMemberCall(yytext)){MemReference=ProcessMemberCall(yytext);if(MemReference!=NULL){ yylval.optabs=MemReference; return MemberReference;}else{yylval.SymId=AddSymbol(yytext);return ID;}}else{yylval.SymId=AddSymbol(yytext);return ID;}}
"&&" {return AND_OP;}
"==" {return ISE_OP;}
"||" {return OR_OP;}
"<=" {return LTE_OP;}
">=" {return GTE_OP;}
"!=" {return NTE_OP;}
"," {return COMMA_OP;}
"{" {return LFT_CRLY_BKT_OP;}
"}" {return RYT_CRLY_BKT_OP;}
"-" {return MINUS_OP;}
"\""[a-zA-Z0-9 \,:!@#$%^&*()-+;.]*"\""  {char *LpszStringLit;yytext[strlen(yytext)-1]='\0';LpszStringLit=AddNewString(yytext+1);yylval.SymId=AddLiteral(LpszStringLit,1);return STRINGLITERAL;}
[+*/=|&^<>!;@.] {return *yytext;}
"\n" {IncrementLineCount();}

%%