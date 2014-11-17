kernel: start.o protected.o main.o main32.o
	ld -melf_i386 --oformat=binary -Tlinker.ld -o $@ $^

main.o: main.c
	gcc -m32 -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

main32.o: main32.c
	gcc -m32 -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

protected.o: protected.asm main32.o
	nasm -f elf -o $@ $<

start.o: start.asm
	nasm -f elf -o $@ $<

clean:
	rm -f main.o start.o protected.o kernel

disas: kernel
	ndisasm -b32 kernel
