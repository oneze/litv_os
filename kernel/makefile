kernel: start.o main.o print.o main32.o
	ld -melf_i386 --oformat=binary -Tlinker.ld -o $@ $^
	cp kernel ../text

main.o: main.c
	gcc -m32 -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

print.o: print.c
	gcc -m32 -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

main32.o: main32.c
	gcc -m32 -nostdlib -nodefaultlibs -nostartfiles -c -o $@ $<

start.o: start.asm
	nasm -f elf -o $@ $<

clean:
	rm -f *.o kernel

disas: kernel
	ndisasm -b32 kernel
