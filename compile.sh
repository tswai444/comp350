
gcc -o loadFile loadFile.c

# Compile kernel
nasm -f asm kernel.asm -o kernel.o # (or as86 depending on your environment setup)
bcc -ansi -c -o kernel.o kernel.c
as86 kernel.asm -u -3 -o kernel_asm.o
ld86 -d -o kernel kernel.o kernel_asm.o

# Compile shell
bcc -ansi -c -o shell.o shell.c
as86 userlib.asm -u -3 -o userlib.o
ld86 -d -o shell shell.o userlib.o

# Compile test programs (tstpr1 and tstpr2)
bcc -ansi -c -o tstpr1.o tstpr1.c
as86 userlib.o userlib.asm # or link with userlib.o
ld86 -d -o tstpr1 tstpr1.o userlib.o

bcc -ansi -c -o tstpr2.o tstpr2.c
ld86 -d -o tstpr2 tstpr2.o userlib.o

# Copy files onto disk image using loadFile
./loadFile kernel
./loadFile shell
./loadFile message.txt
./loadFile tstpr1
./loadFile tstpr2