del obj\*.o
nasm -f elf -o obj\boot.o boot.asm
i586-elf-gcc -m32 -I include -I hal -o obj\main.o -c main.c
del bin\*.bin
i586-elf-ld -m elf_i386 -T link.ld -o bin\kernel.bin obj\boot.o obj\main.o
cd boot
del Boot.img
cd ..
imgtool\GrubImgTool.exe -i bin -o boot/Boot.img
bochsrc.bxrc