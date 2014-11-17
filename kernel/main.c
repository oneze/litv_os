asm(".code16gcc");
typedef unsigned long uint32_t;
typedef unsigned int uint16_t;
typedef unsigned long long gdt_entry_t;

gdt_entry_t gdt[4];

typedef struct gdt_descriptor_t {
	uint32_t base;
	uint32_t limit;
	uint16_t flag;
} gdt_descriptor_t;

typedef struct __attribute__ ((__packed__)) gdt_reg {
	uint16_t size;
	uint32_t offset;
} gdt_reg;

void make_gdt_entry(const gdt_descriptor_t* descriptor, gdt_entry_t* entry)
{
	*entry  =(descriptor->limit	&0x000F0000);	//19:16 limit bits
	*entry |=(descriptor->flag << 8)&0x00F0FF00;	//set flags fields
	*entry |=(descriptor->base <<16)&0x000000FF;	//23:16 base bits
	*entry |= descriptor->base	&0xFF000000;	//31:24 base bits

	*entry <<= 32;

	*entry |= descriptor->base <<16;		//15:0 base bits
	*entry |= descriptor->limit	&0x0000FFFF;	//15:0 limit bits
}

const int GDT_ENTRIES_NUM = 3;

gdt_descriptor_t gdt_structs[] = {
	{0,0,0},
	{0x0, 0x3FF, 0x409A},
	{0x400, 0x7FF, 0x4092},
	{0xC00, 0x7FF, 0x4096}
};

void main32();

int main() {
	gdt_reg gdt_register;
	int i;
	for (i = 0; i < GDT_ENTRIES_NUM; ++i) {
		make_gdt_entry(gdt_structs + i, gdt + i);
	}

	//LOAD GDT HERE
	gdt_register.size = GDT_ENTRIES_NUM;
	gdt_register.offset = (uint16_t)gdt;
	enter_protected_mode(&gdt_register);
	/*asm volatile (" \
		lgdt %0; \
		movl %cr0, %eax; \
		orl $1, %eax; \
		movl %eax, %cr0; \
		jmpf 0x8:.next; \
	.next: \
		.code16; \
		call main32;"
	:
	: "p" (&gdt_register));*/
	return 0;
} 
