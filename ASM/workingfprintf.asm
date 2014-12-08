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
ret
fprint_int_win:
 enter 148, 0 
 mov CX,1000
 mov EDI,hexstr
 mov ESI,10
 conv_loop:
 CWD
 idiv cx
 ;jz skip_label
 add al,0x30
 mov byte[EDI],al
 inc EDI
 skip_label:
 mov ax,cx
 idiv byte [divid]
 cmp al,0
 jz return
 cbw
 mov cx,ax 
 mov ax,dx
 jmp conv_loop

return: 
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
call [CloseHandle]
push dword [ebp-4]
leave
ret
	Obj1_start:
sub ESP,0x1
;	g	12	=	
mov byte ah,0xc
mov byte [EBP-0x1],ah
;		fprint_int_win	CALL	g
mov dword [ESPSave],ESP
mov dword ESP,[ESPOrg]
mov EAX,0x2F0
call fprint_int_win
mov dword ESP,[ESPSave]
;writing Epilogue for function
Epilogue_obj1_start:add ESP,0x1
push dword 0
call [ExitProcess]
ret 
section .data
 Data resb 260
filename db 'out6.txt',0
 hexstr resb 10
ESPSave resb 4
 ESPOrg resb 4
EBPSave resb 4
divid db 10