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
sub ESP,0x13
;	T0	&st1	+	0
mov EDI,EBP
sub EDI,0x2
mov dword EAX,EDI
add EAX,0x0
mov dword [EBP-0x9],EAX
;	@T0	T0	DEREFERENCE	
;	@T0	8	=	
mov byte ah,0x8
mov dword EDI,[EBP-0x9]
mov byte [EDI],ah
;	T1	&st1	+	1
mov EDI,EBP
sub EDI,0x2
mov dword EAX,EDI
add EAX,0x1
mov dword [EBP-0xe],EAX
;	@T1	T1	DEREFERENCE	
;	@T1	18	=	
mov byte ah,0x12
mov dword EDI,[EBP-0xe]
mov byte [EDI],ah
;	st2	st1	=	
mov EDX,EBP
sub EDX,0x4
mov dword EDI,EDX
mov EDX,EBP
sub EDX,0x2
mov dword ESI,EDX
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
;	T2	&st2	+	1
mov EDI,EBP
sub EDI,0x4
mov dword EAX,EDI
add EAX,0x1
mov dword [EBP-0x13],EAX
;	@T2	T2	DEREFERENCE	
;		fprint_int_win	CALL	@T2
mov dword ESI,[EBP-0x13]
mov byte al,[ESI]
movzx EAX,ax
call fprint_int_win
;writing Epilogue for function
Epilogue_Obj1_start:
add ESP,0x13

ret 
section .data
 Data resb 260
filename db '50.out',0
 hexstr resb 10
ESPSave resb 4
ESPOrg resb 4
EBPSave resb 4
divid db 10

