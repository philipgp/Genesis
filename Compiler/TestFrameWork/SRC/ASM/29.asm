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
 mov dword ESP,[ESPOrg]
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
leave
ret
	Obj1_start:
sub ESP,0xe
;	j	7	=	
mov word ax,0x7
mov word [EBP-0x2],ax
;	k	48	=	
mov word ax,0x30
mov word [EBP-0x4],ax
;	T0	j	+	k
mov word ax,[EBP-0x2]
mov word cx,[EBP-0x4]
add ax,cx
mov word [EBP-0xa],ax
;	T1	T0	cast	int32
mov word ax,[EBP-0xa]
movsx EDI,ax
mov dword [EBP-0xe],EDI
;	m	T1	=	
mov dword EAX,[EBP-0xe]
mov dword [EBP-0x8],EAX
;		fprint_int_win	CALL	m
mov word ax,[EBP-0x8]
movsx EAX,ax
call fprint_int_win
;writing Epilogue for function
Epilogue_Obj1_start:
add ESP,0xe

ret 
section .data
 Data resb 260
filename db '29.out',0
 hexstr resb 10
ESPSave resb 4
ESPOrg resb 4
EBPSave resb 4
divid db 10

