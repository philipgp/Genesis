org 0x7C00
xor ax, ax
mov ds, ax
mov ss, ax 
mov es,ax
mov EBP,Data
add EBP,100
mov EBX,Data2
mov ESP,EBP
 jmp KeyBoard_start
KeyBoard_init:
sub ESP,0x8
;	T0	&ScanCode	+	144
mov ECX,EBX
add ECX,0x1
mov dword EAX,ECX
add EAX,0x90
mov dword [EBP-0x4],EAX
;	@T0	T0	DEREFERENCE	
;	@T0	113	=	
mov byte ah,0x71
mov dword ECX,[EBP-0x4]
mov byte [ECX],ah
;	T1	&ScanCode	+	16
mov ECX,EBX
add ECX,0x1
mov dword EAX,ECX
add EAX,0x10
mov dword [EBP-0x8],EAX
;	@T1	T1	DEREFERENCE	
;	@T1	113	=	
mov byte ah,0x71
mov dword ECX,[EBP-0x8]
mov byte [ECX],ah
;writing Epilogue for function
Epilogue_KeyBoard_init:add ESP,0x8
ret 
KeyBoard_HandleInput:
pusha
mov dword EAX,ESP
mov dword EBX,EBP
mov EBP,ISR
add EBP,80
mov ESP,EBP
push EAX
push EBX
;pusha
;pusha
mov EBX,Data2
cli
.spin:
   in  al, 0x64
   and al, 0x01
   jz  .spin
in al,0x60
pusha
mov byte al,'a'
mov ah,0x0E
int 0x10
 popa
mov al, 0x20
out 0x20, al
;popa
pop EBP
pop ESP

popa

sti
iret

KeyBoard_start:
sub ESP,0x1
;		KeyBoard_init	CALL	

;			ASM	
;cli
cli
;mov word[es:(9*4)], KeyBoard_HandleInput
mov word[es:(9*4)], KeyBoard_HandleInput
; mov word[es:(9*4)+2], 0
 mov word[es:(9*4)+2], 0
; sti
 sti
; jmp $
 jmp $
;	h	67	=	
mov byte ah,0x43
mov byte [EBP-0x1],ah
;writing Epilogue for function
Epilogue_KeyBoard_start:add ESP,0x1
ret 
Data resb 100

times 510-($-$$) db 0
db 0x55
db 0xAA
Data2 resb 300
ISR resb 100
times 1024-($-$$) db 0