void main32()
{
	asm volatile ("\
		movw $0x10, %ax; \
		movw %ax, %ds; \
		movw %ax, %ss; \ 
	");
	while(1){};
}
