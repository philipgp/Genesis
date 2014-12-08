extern ExitProcess
extern OpenFile
extern WriteFile
extern CloseHandle
import ExitProcess kernel32.dll
import OpenFile kernel32.dll
import WriteFile kernel32.dll
import CloseHandle kernel32.dll 
section .text use32
..start:
 mov dword [ESPOrg],ESP
mov EBP,ESP
sub EBP,0x4
call Obj1_start
push eax
call [ExitProcess]
fprint_int_win:
 mov dword [EBPSave],EBP
 mov dword [ESPSave],ESP
enter 148, 0 
mov CX,1000
mov EDI,hexstr
conv_loop:
cwd
idiv cx
add al,0x30
mov byte[edi],al
inc edi
skip_label:
mov ax,cx
idiv byte [divid]
cmp al,0
jz returnhex
cbw
mov cx,ax
mov ax,dx
jmp conv_loop
returnhex:
lea ebx, [ebp-148]
push dword 1 | 0x1000
push ebx
push dword filename
call [OpenFile]
mov dword [ebp-4], eax
lea ebx, [ebp-8]
push dword 0
push ebx
mov EAX,EDI
sub EAX,hexstr
push dword EAX
push dword hexstr
push dword [ebp-4]
call [WriteFile]
push dword [ebp-4]
call [CloseHandle]
mov dword EBP,[EBPSave]
mov dword ESP,[ESPSave]
ret
	Obj1_start:
sub ESP,0x4
;	k	6	=	
mov byte ah,0x6
mov byte [EBP-0x1],ah
;	m	9	=	
mov byte ah,0x9
mov byte [EBP-0x2],ah
;	T0	k	comp	8
mov byte ah,[EBP-0x1]
cmp ah,0x8
;	JA LABEL0
ja LABEL0
;	T0	0	=	
mov byte ah,0x0
mov byte [EBP-0x3],ah
;	JMP LABEL2
jmp LABEL2
;LABEL0	T0	1	=	
LABEL0: mov byte ah,0x1
mov byte [EBP-0x3],ah
;LABEL2		T0	comp	1
LABEL2: cmp ah,0x1
;	JNE LABEL3
jne LABEL3
;		fprint_int_win	CALL	k
mov byte al,[EBP-0x1]
movzx EAX,al
call fprint_int_win
;			ClearRegs	
;	JMP LABEL4
jmp LABEL4
;LABEL3		k	comp	6
LABEL3: mov byte ah,[EBP-0x1]
cmp ah,0x6
;	JE LABEL1
je LABEL1
;	T1	0	=	
mov byte ah,0x0
mov byte [EBP-0x4],ah
;	JMP LABEL5
jmp LABEL5
;LABEL1	T1	1	=	
LABEL1: mov byte ah,0x1
mov byte [EBP-0x4],ah
;LABEL5		T1	comp	1
LABEL5: cmp ah,0x1
;	JNE LABEL4
jne LABEL4
;	m	9	=	
mov byte ah,0x9
mov byte [EBP-0x2],ah
;		fprint_int_win	CALL	m
mov byte al,[EBP-0x2]
movzx EAX,al
call fprint_int_win
;			ClearRegs	
;LABEL4	k	7	=	
LABEL4: mov byte ah,0x7
mov byte [EBP-0x1],ah
;writing Epilogue for function
Epilogue_Obj1_start:
add ESP,0x4

ret 
section .data
 Data resb 260
filename db '45.out',0
 hexstr resb 10
ESPSave resb 4
ESPOrg resb 4
EBPSave resb 4
divid db 10

