org 0x7C00
xor ax, ax
mov ds, ax
mov ss, ax 
mov es,ax
mov EBP,Data
add EBP,100
mov ESP,EBP
 mov EBX,ObjectData
jmp KeyBoard_start
KeyBoard_init:
sub ESP,0x2
mov byte ah,0x0
mov byte [EBX+0x1],ah
mov EAX,EBX
add EAX,0x2
mov dword EAX,EAX
mov EAX,EAX
add EAX,16
mov byte [EAX],113
inc EAX
mov byte [EAX],119
inc EAX
mov byte [EAX],101
mov byte ah,0x0
mov byte [EBX+0x1],ah
Epilogue_KeyBoard_init:
add ESP,0x2

ret 
KeyBoard_HandleInput:
cli
pushad
mov dword EAX,ESP
mov dword EBX,EBP
mov EBP,ISR
add EBP,80
mov ESP,EBP
push EAX
push EBX
sub EBP,0x9
mov ESP,EBP
mov EBX,ObjectData
sub ESP,0xf
spin:
in  al, 0x64
and al, 0x01
jz  spin
in al,0x60
mov ECX,EBP
sub ECX,0x1
mov dword ECX,ECX
mov byte [ECX],al
mov byte ah,[EBP-0x1]
cmp ah,0x2a
je LABEL0
mov byte ah,0x0
mov byte [EBP-0x3],ah
jmp LABEL4
LABEL0: mov byte ah,0x1
mov byte [EBP-0x3],ah
LABEL4: cmp ah,0x1
jne LABEL5
mov byte ah,0x1
mov byte [EBX+0x1],ah
jmp LABEL6
LABEL5: mov byte ah,[EBP-0x1]
cmp ah,0xaa
je LABEL1
mov byte ah,0x0
mov byte [EBP-0x4],ah
jmp LABEL7
LABEL1: mov byte ah,0x1
mov byte [EBP-0x4],ah
LABEL7: cmp ah,0x1
jne LABEL8
mov byte ah,0x0
mov byte [EBX+0x1],ah
jmp LABEL6
LABEL8: mov byte ah,[EBP-0x1]
movzx ECX,ah
mov dword [EBP-0xc],ECX
mov EDX,EBX
add EDX,0x2
mov dword ECX,EDX
mov dword EDX,[EBP-0xc]
add ECX,EDX
mov dword [EBP-0x8],ECX
mov ECX,EBX
add ECX,0x0
mov dword EDI,ECX
mov dword ECX,[EBP-0x8]
mov dword ESI,ECX
mov byte ah,[ESI]
 mov byte [EDI],ah 
mov byte al,[EBX+0x1]
cmp al,0x1
je LABEL2
mov byte al,0x0
mov byte [EBP-0xd],al
jmp LABEL9
LABEL2: mov byte al,0x1
mov byte [EBP-0xd],al
LABEL9: cmp al,0x1
jne LABEL10
mov byte al,[EBX+0x0]
sub al,0x20
mov byte [EBP-0xe],al
mov byte [EBX+0x0],al
LABEL10: mov byte ah,0x2
mov byte [EBP-0x2],ah
mov byte ah,[EBP-0x1]
cmp ah,0x7f
mov byte ah,0x0
mov byte [EBP-0xf],ah
jmp LABEL11
LABEL3: mov byte ah,0x1
mov byte [EBP-0xf],ah
LABEL11: cmp ah,0x1
jne LABEL12
mov byte al,[EBX+0x0]
pusha
mov ah,0x0E
int 0x10
popa
LABEL6: mov byte ah,0x2
mov byte [EBP-0x2],ah
mov al, 0x20
out 0x20, al
Epilogue_HandleInput:
add ESP,0xf
add EBP,0x9
inc ESP
pop EBP
pop ESP
popad

sti
iret
KeyBoard_start:
sub ESP,0x1
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call KeyBoard_init
pop EBP
mov EAX,EBP
sub EAX,0x0
mov dword EDI,EAX
mov dword ESI,EAX
cli
mov word[es:(9*4)], KeyBoard_HandleInput
mov word[es:(9*4)+2], 0
sti
jmp $
mov byte ah,0x43
mov byte [EBP-0x1],ah
Epilogue_KeyBoard_start:
add ESP,0x1

ret 

times 510-($-$$) db 0
db 0x55
db 0xAA
ISR resb 100
Data resb 100
 ObjectData resb 300
times 1024-($-$$) db 0