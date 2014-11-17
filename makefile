disk: bootblock disk.img text
	dd if=bootblock of=disk.img bs=512 count=1 conv=notrunc
	dd if=text of=disk.img bs=512 count=2 seek=1 conv=notrunc

bootblock: bootblock.asm
	nasm -f bin -o bootblock bootblock.asm

disk.img:
	dd if=/dev/zero of=disk.img bs=1M count=1

clean:
	rm -f disk.img bootblock *~ *.o

ndis:
	ndisasm -b16 bootblock

run: bochs.txt
	bochs -qf bochs.txt
