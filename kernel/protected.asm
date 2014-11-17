[BITS 16]

global enter_protected_mode
extern main32

enter_protected_mode:
	lgdt [esp+8] 
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp 0x8:.protected_mode
.protected_mode:
	o32 call main32
