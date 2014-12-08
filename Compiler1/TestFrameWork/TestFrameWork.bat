set GENESIS_HOME=D:\Genesis
set folder_name=%GENESIS_HOME%\SRC\Compiler\TestFrameWork
set %PATH%=%GENESIS_HOME%\SRC\Compiler\Compiler\Debug;%GENESIS_HOME%\SOFTWARES\NASM;%PATH%
set src_folder_name= %folder_name%\SRC
set asm_folder_name=%src_folder_name%\ASM\
set nasm=%GENESIS_HOME%\SOFTWARE\NASM\nasm.exe
set compiler=%GENESIS_HOME%\SRC\Compiler\Compiler\Debug\Compiler.exe
echo start > %folder_name%\result.txt
set  /a count=0

for  %%f in (%src_folder_name%\*.*) do (
 
 %Compiler% -o %asm_folder_name%%%~nf.asm -i %%f
           %nasm% -fobj %asm_folder_name%%%~nf.asm
           %GENESIS_HOME%\Software\alink\alink.exe -oPE %asm_folder_name%%%~nf.obj
         %asm_folder_name%%%~nf.exe
         start /d %asm_folder_name% %%~nf.exe
echo %%~nf
           fc /b %asm_folder_name%%%~nf.out %folder_name%\ExpectedOutput\%%~nf.out > nul
           if errorlevel 1 (
    echo %%f >> %folder_name%\result.txt
) else (
    echo same
)

      )
