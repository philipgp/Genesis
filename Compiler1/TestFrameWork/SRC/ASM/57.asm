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
sub ESP,0x37
;	T0	&st1	+	8
mov EDI,EBP
sub EDI,0xa
mov dword EAX,EDI
add EAX,0x8
mov dword [EBP-0x19],EAX
;	@T0	T0	DEREFERENCE	
;	@T0	8	=	
mov byte ah,0x8
mov dword EDI,[EBP-0x19]
mov byte [EDI],ah
;	T1	&st1	+	9
mov EDI,EBP
sub EDI,0xa
mov dword EAX,EDI
add EAX,0x9
mov dword [EBP-0x1e],EAX
;	@T1	T1	DEREFERENCE	
;	@T1	18	=	
mov byte ah,0x12
mov dword EDI,[EBP-0x1e]
mov byte [EDI],ah
;	T2	&st1	+	4
mov EDI,EBP
sub EDI,0xa
mov dword EAX,EDI
add EAX,0x4
mov dword [EBP-0x23],EAX
;	@T2	T2	DEREFERENCE	
;	@T2	18	=	
mov dword EDI,0x12
mov dword ESI,[EBP-0x23]
mov dword [ESI],EDI
;	T3	&st1	+	0
mov EDI,EBP
sub EDI,0xa
mov dword EAX,EDI
add EAX,0x0
mov dword [EBP-0x28],EAX
;	@T3	T3	DEREFERENCE	
;	@T3	19	=	
mov word ax,0x13
mov dword EDI,[EBP-0x28]
mov word [EDI],ax
;	T4	&st2	+	0
mov EDI,EBP
sub EDI,0x14
mov dword EAX,EDI
add EAX,0x0
mov dword [EBP-0x2d],EAX
;	@T4	T4	DEREFERENCE	
;	T5	&st1	+	0
mov EDI,EBP
sub EDI,0xa
mov dword EAX,EDI
add EAX,0x0
mov dword [EBP-0x32],EAX
;	@T5	T5	DEREFERENCE	
;	@T4	@T5	=	
mov dword ESI,[EBP-0x32]
mov word ax,[ESI]
mov dword EDI,[EBP-0x2d]
mov word [EDI],ax
;	T6	&st2	+	0
mov EDI,EBP
sub EDI,0x14
mov dword EAX,EDI
add EAX,0x0
mov dword [EBP-0x37],EAX
;	@T6	T6	DEREFERENCE	
;		fprint_int_win	CALL	@T6
mov dword ESI,[EBP-0x37]
mov word ax,[ESI]
movzx EAX,ax
call fprint_int_win
;writing Epilogue for function
Epilogue_Obj1_start:
add ESP,0x37

ret 
section .data
 Data resb 260
filename db '57.out',0
 hexstr resb 10
ESPSave resb 4
ESPOrg resb 4
EBPSave resb 4
divid db 10

