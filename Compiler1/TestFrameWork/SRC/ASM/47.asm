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
sub ESP,0x6
;	i	8	=	
mov byte ah,0x8
mov byte [EBP-0x1],ah
;	p	&i	=	
mov EDI,EBP
sub EDI,0x1
mov dword EAX,EDI
mov dword [EBP-0x6],EAX
;	@p	p	DEREFERENCE	
;	j	@p	=	
mov dword ESI,[EBP-0x6]
mov byte ah,[ESI]
mov byte [EBP-0x2],ah
;		fprint_int_win	CALL	j
mov byte al,[EBP-0x2]
movsx EAX,al
call fprint_int_win
;writing Epilogue for function
Epilogue_Obj1_start:
add ESP,0x6

ret 
section .data
 Data resb 260
filename db '47.out',0
 hexstr resb 10
ESPSave resb 4
ESPOrg resb 4
EBPSave resb 4
divid db 10

