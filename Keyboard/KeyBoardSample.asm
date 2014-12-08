use16
 org 0x7C00
 mov al, 13h
            mov ah, 0
            int 10h
 ;Disable interrupts
 cli
 
 ;set DS to 0
 xor  ax, ax
 mov es,ax
 push ax
 pop  ds
 
 ;The IRQ1 (keyboard) is mapped on interrupt 9 by default
 ;Now we write the address of the handler in the Interrupt descriptor table (IDT)
 mov word[es:(9*4)  ], keyboard_handler    ;Offset
 mov word[es:(9*4)+2], 0                   ;Segment
 
 ;Enable interrupts
 sti
 
 jmp $
 
 ;This handler gets called each time a IRQ1 is triggered by the keyboard
 keyboard_handler:
   pusha
 
   ;Apparently spinning until the byte is ready is necessary on some older machines.
 .spin:
   in  al, 0x64
   and al, 0x01
   jz  .spin
 
   ;read scancode
   in  al, 0x60
 
   ;Here you can do with the scancode whatever you like.
   ;For example converting it to another keyboard layout or test for special keys and trigger a reboot
 
   call write_byte_as_hex
   mov  al, '|'
   call bios.write_char
 
   ;Now we tell the first PIC that the IRQ is handled
   mov al, 0x20
   out 0x20, al
 
   popa
 iret
 
 
 ;Input: al = char
 bios.write_char:
   pusha
   mov  ah, 0x0E
   int  0x10
   popa
 ret
 
 hex_chars: db '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
 
 ;This is a small function to write a value on the screen
 ;Input: al = byte
 write_byte_as_hex:
   pusha
   and  ax, 0xFF
   push ax
   mov  bx, ax
   shr  bx, 4
   mov  al, [hex_chars+bx]
   call bios.write_char
   pop  bx
   and  bx, 0xF
   mov  al, [hex_chars+bx]
   call bios.write_char
   popa
 ret
 
 times 510-($-$$) db 0
 dw 0xAA55