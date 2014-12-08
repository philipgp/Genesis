cls
cd ..
call SetEnv.bat
cd Keyboard
echo ON
nasm -w+orphan-labels KeyBoardSample.asm -o OVM\KeyBoard.img
nasm -w+orphan-labels KeyBoardSample.asm -o  bin\KeyBoard