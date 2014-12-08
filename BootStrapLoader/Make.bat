cls
cd ..
call SetEnv.bat
cd BootStrapLoader
echo ON
nasm -w+orphan-labels BootStrapLoader.asm -o OVM\BootLoader.img
nasm -w+orphan-labels BootStrapLoader.asm -o  bin\BootLoader