org 0x7C00
xor ax, ax
mov ds, ax
mov ss, ax 
mov es,ax

 start:
	  in  al, 64h					; \It would be good
	  and al, 02h	;Test if command buffer is empty |to put this in a
	  jnz start					 ;/macro...

	  mov al, 0xee
	  out 60h, al	;Write outputport

    ;wait:
	  in  al, 60h
	  cmp al,0xee	;Test if command came through
	  jnz ends
	 ; jnz wait
  
	  ends:
	  mov al,0xab
	  out 0x64,al
	  in al,0x64
	  cmp al,0
	  jnz ends2
	  
	  mov al,'a'
	mov ah,0x0e
  int 0x10
	  
	   mov al,'a'
  mov ah,0x0e
  int 0x10
	  ends2:
	  mov al,'b'
  mov ah,0x0e
  int 0x10
times 510-($-$$) db 0
db 0x55
db 0xAA

times 1024-($-$$) db 0