nasm -f win64 out.asm -o binaries/out.obj
ld binaries/out.obj -e _start -o binaries/out.exe -lkernel32
./binaries/out.exe