kernel: start.o main.o main32.o
	ld -melf_i386 --oformat=binary -Tlinker.ld -o $@ $^
	cp kernel ../text

main.o: main.c
	gcc -m32 -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

main32.o: main32.c
	gcc -m32 -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

start.o: start.asm
	nasm -f elf -o $@ $<

clean:
	rm -f main.o start.o protected.o kernel

disas: kernel
	ndisasm -b32 kernel
