printreg32:
pushad
mov dword eax,[regvalue]
mov cx,0x8
mov si, hexstr
hexloop:
rol eax, 4   ;leftmost will
mov ebx, eax   ; become
and ebx, 0x0f   ; rightmost
mov bl,[si+bx]
xchg eax,ebx
pusha
mov ah,0xE
int 0x10
popa
xchg eax,ebx
dec cx
jnz hexloop
pusha
mov al,' '
mov ah,0xE
int 0x10
popa
popad
ret

hexstr   db '0123456789ABCDEF'
regvalue db 0000