SET  CYGWIN_BIN=C:\cygwin\bin
set SRC_LOC=C:\Genesis\SRC\Compiler
copy %SRC_LOC%\ObjCompiler.y %CYGWIN_BIN%
cd %CYGWIN_BIN%
C:
%CYGWIN_BIN%\bison -d ObjCompiler.y
%CYGWIN_BIN%\flex  %SRC_LOC%\ObjCompiler.l
echo OFF
copy ObjCompiler.tab.c %SRC_LOC%\ObjCompiler.tab.c
copy ObjCompiler.tab.h %SRC_LOC%\ObjCompiler.tab.h
copy lex.yy.c %SRC_LOC%\lex.yy.c
C:
cd %SRC_LOC%\