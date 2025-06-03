FILES=./build/start.o ./build/pearos.o
INCLUDES=

all: ${FILES}
	i686-elf-ld -m elf_i386 -relocatable ${FILES} -o ./stdlib.elf

./build/start.o: ./src/start.asm
	nasm -f elf ./src/start.asm -o ./build/start.o


./build/pearos.o: ./src/pearos.asm
	nasm -f elf ./src/pearos.asm -o ./build/pearos.o

clean:
	rm -rf ${FILES}
	rm ./stdlib.elf