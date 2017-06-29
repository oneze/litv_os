[BITS 16]
    	org 0x7c00
    	mov ax, 0
    	mov ds, ax
    	mov ss, ax

      mov cx, 80*25
      mov bx, 0h
      mov ax, 0xb800
      mov es, ax
cycle:
      mov [es:bx], byte ' '
      mov [es:bx+1], byte 7
      add bx, 2
      dec cx
      cmp cx, 0
      jne cycle

    	;mov ah, 00h		;Очистить экран, установить видеорежим
    	;mov al, 0eh		;Номер видеорежима (640x200 16 цветов)
    	;int 10h

	mov ah, 02h		;Читать секторы
  mov dl, 80h		;Номер диска
	mov dh, 0		;Номер головки
	mov ch, 0		;Номер дорожки
	mov cl, 2		;Номер сектора >1
	mov al, 4		;Число считываемых секторов >0
	mov bx, 0h 		;Записываем в es:bx адрес
	mov es, bx		;буфера считывания
	mov bx, 8000h		;200h:0h, сразу после загрузочного блока
	int 13h


	jmp 0x0:0x8000
;    	mov ax, es		;Записываем адрес
;	mov ds, ax		;буфера считывания
;	mov si, bx		;в ds:si для lodsb
;	mov bl, 0ch             ;Устанавливаем цвет текста
;	xor ax, ax

;ch_loop:
;   	lodsb                 	;Загружаем очередной символ в al
;   	test al, al
;    	jz hang
;    	mov ah, 0x0E          	;Выводим al в режиме телетайпа
;    	int 0x10
;    	jmp ch_loop

hang:
    	jmp hang

    	msg db 'Hello, world!', 13, 10, 0
    	;msglen equ $ - msg

    	times (510 - ($ - $$)) db 0x90
    	db 0x55, 0xaa
