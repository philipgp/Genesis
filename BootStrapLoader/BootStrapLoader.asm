[ORG 0x7c00]      ; add to offsets
   xor ax, ax    ; make it zero
   mov ds, ax   ; DS=0
   mov ss, ax   ; stack starts at 0
   mov sp, 0x9c00   ; 200h past code start
 
   mov ax, 0xb800   ; text video memory
   mov es, ax
 lgdt [gdtinfo]   ; load gdt register
 mov  eax, cr0   ; switch to pmode by
   or al,1         ; set pmode bit
   mov  cr0, eax
 mov  bx, 0x08   ; select descriptor 1
   mov  ds, bx   ; 8h = 1000b
   mov si, msg   ; show text string
   call sprint
 
   mov ax, 0xb800   ; look at video mem
   mov gs, ax
   mov bx, 0x0000   ; 'W'=57 attrib=0F
   mov ax, [gs:bx]
 
   mov  word [reg16], ax ;look at register
   call printreg16
 
hang:
   jmp hang
 
;----------------------
dochar:   call cprint         ; print one character
sprint:   lodsb      ; string char to AL
   cmp al, 0
   jne dochar   ; else, we're done
   add byte [ypos], 1   ;down one row
   mov byte [xpos], 0   ;back to left
   ret
 
cprint:   mov ah, 0x0F   ; attrib = white on black
   mov cx, ax    ; save char/attribute
   movzx ax, byte [ypos]
   mov dx, 160   ; 2 bytes (char/attrib)
   mul dx      ; for 80 columns
   movzx bx, byte [xpos]
   shl bx, 1    ; times 2 to skip attrib
 
   mov di, 0        ; start of video memory
   add di, ax      ; add y offset
   add di, bx      ; add x offset
 
   mov ax, cx        ; restore char/attribute
   stosw              ; write char/attribute
   add byte [xpos], 1  ; advance to right
 
   ret
 
;------------------------------------
 
printreg16:
   mov di, outstr16
   mov ax, [reg16]
   mov si, hexstr
   mov cx, 4   ;four places
hexloop:
   rol ax, 4   ;leftmost will
   mov bx, ax   ; become
   and bx, 0x0f   ; rightmost
   mov bl, [si + bx];index into hexstr
   mov [di], bl
   inc di
   dec cx
   jnz hexloop
 
   mov si, outstr16
   call sprint
 
   ret
 
;------------------------------------
 
xpos   db 0
ypos   db 0
hexstr   db '0123456789ABCDEF'
outstr16   db '0000', 0  ;register value string
reg16   dw    0  ; pass values to printreg16
msg   db "Booting Genesis..", 0
gdtinfo:
   dw gdt_end - gdt - 1   ;last byte in table
   dd gdt         ;start of table
 
gdt        dd 0,0  ; entry 0 is always unused
flatdesc    db 0xff, 0xff, 0, 0, 0, 10010010b, 11001111b, 0
gdt_end:
times 510-($-$$) db 0
db 0x55
db 0xAA
times 1024-($-$$) db 0
;==================================