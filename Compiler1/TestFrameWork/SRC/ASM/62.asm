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
 call Obj1_start
push eax
call [ExitProcess]
fprint_int_win:
 mov dword [EBPSave],EBP
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
leave
ret
	obj2_setI:
sub ESP,0x0
;	i	9	=	
mov byte ah,0x9
mov byte [EBX+0x0],ah
;writing Epilogue for function
Epilogue_obj2_setI:
add ESP,0x0

ret 
obj2_printI:
sub ESP,0x0
;		fprint_int_win	CALL	i
mov dword [ESPSave],ESP
mov dword ESP,[ESPOrg]
mov byte al,[EBX+0x0]
movsx EAX,al
call fprint_int_win
mov dword ESP,[ESPSave]
;writing Epilogue for function
Epilogue_obj2_printI:
add ESP,0x0

ret 
obj1_main:
sub ESP,0x1
;		o	SetEBX	
push EBX
mov EDI,EBP
sub EDI,0x1
mov dword EBX,EDI
;		obj2_setI	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call obj2_setI
pop EBP
mov EDI,EBP
sub EDI,0x0
mov dword EDI,EDI
mov dword ESI,EAX
;			UnSetEBX	
pop EBX
;		o	SetEBX	
push EBX
mov EDI,EBP
sub EDI,0x1
mov dword EBX,EDI
;		obj2_printI	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call obj2_printI
pop EBP
mov EDI,EBP
sub EDI,0x0
mov dword EDI,EDI
mov dword ESI,EAX
;			UnSetEBX	
pop EBX
;writing Epilogue for function
Epilogue__main:
add ESP,0x1

ret 
section .data
 Data resb 260
filename db '62.out',0
 hexstr resb 10
ESPSave resb 4
ESPOrg resb 4
EBPSave resb 4
divid db 10
