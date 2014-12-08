global _main
 extern _printf 
segment .text
_main:push EBP 
mov EBP,Data
 add EBP,0xFF
 call wk1_main
pop EBP
ret
wk1_main:
sub ESP,0x1
mov byte ah,0x5
mov byte [EBP-0x1],ah
mov byte al,[EBP-0x1]
movsx EAX,al
push EAX
push dword int_format
 call _printf
 pop EAX
pop EAX
Epilogue__main:
add ESP,0x1

ret 
segment .data
 Data resb 260 
int_format db 'Value=%d',0
 string_format  db 'String Value=%s',0 
 uint_format db 'Value=%d',0