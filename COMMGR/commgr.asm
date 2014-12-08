[BITS 16]
[ORG 0x7C00]
xor ax, ax
mov ds, ax
mov ss, ax 
mov es,ax
mov ah,02h
mov al,21; no of sectors
mov ch,0
mov cl,2
mov dh,0
mov dl,0
mov bx,heapobj_init
int 13h
mov EBP,Data
add EBP,600
mov ESP,EBP
mov  EBX,ObjectData
push EBX 
mov dword EBX,heap
push EBP
mov EBP,ESP 
sub EBP,0x4 
call heapobj_init 
pop EBP
pop EBX
call __main
 hang:jmp hang
times 510-($-$$) db 0
db 0x55 
db 0xAA
heapobj_init:
sub ESP,0x20
;	HEADERSIZE	6	=	
mov byte ah,0x6
mov byte [EBX+0x4],ah
;			ASM	
;mov EDX,heapspace
mov EDX,heapspace
mov EAX,EBP
sub EAX,0x12
mov dword EAX,EAX
mov dword  [EAX],EDX
;	T0	&StartBlock	+	0
mov ECX,EBP
sub ECX,0x6
mov dword EAX,ECX
add EAX,0x0
mov dword [EBP-0x17],EAX
;	@T0	T0	DEREFERENCE	
;	@T0	1024	=	
mov word ax,0x400
mov dword ECX,[EBP-0x17]
mov word [ECX],ax
;	T1	&StartBlock	+	2
mov ESI,EBP
sub ESI,0x6
mov dword ECX,ESI
add ECX,0x2
mov dword [EBP-0x1c],ECX
;	@T1	T1	DEREFERENCE	
;	@T1	0	=	
mov dword ESI,0x0
mov dword EDI,[EBP-0x1c]
mov dword [EDI],ESI
;	@LpStart	LpStart	DEREFERENCE	
;	@LpStart	StartBlock	=	
mov dword EAX,[EBP-0x12]
mov dword EDI,EAX
mov EAX,EBP
sub EAX,0x6
mov dword ESI,EAX
mov dword ECX,0x1
LABEL0:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,4
 add EDI,4
LOOP LABEL0
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
;	m_LpStart	LpStart	=	
mov dword EAX,[EBP-0x12]
mov dword [EBX+0x0],EAX
;writing Epilogue for function
Epilogue_heapobj_init:
add ESP,0x20
ret 

heapobj_AllocateMemory:
sub ESP,0x40
;	iSize	0	=	
mov word ax,0x0
mov word [EBP-0x16],ax
;	LpAddress	0	=	
mov dword ECX,0x0
mov dword [EBP-0xe],ECX
;	LpCurrent	m_LpStart	=	
mov dword EAX,[EBX+0x0]
mov dword [EBP-0xa],EAX
;LABEL3		LpCurrent	comp	0
LABEL3: cmp EAX,0x0
;	JNE LABEL1
jne LABEL1
;	T2	0	=	
mov byte ah,0x0
mov byte [EBP-0x17],ah
;	JMP LABEL5
jmp LABEL5
;LABEL1	T2	1	=	
LABEL1: mov byte ah,0x1
mov byte [EBP-0x17],ah
;			ClearRegs	
;LABEL5		T2	comp	1
LABEL5: mov byte ah,[EBP-0x17]
cmp ah,0x1
;	JNE LABEL6
jne LABEL6
;	@LpCurrent	LpCurrent	DEREFERENCE	
;	CurrentBlock	@LpCurrent	=	
mov EAX,EBP
sub EAX,0x14
mov dword EDI,EAX
mov dword EAX,[EBP-0xa]
mov dword ESI,EAX
mov dword ECX,0x1
LABEL7:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,4
 add EDI,4
LOOP LABEL7
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
;	T3	&CurrentBlock	+	0
mov ECX,EBP
sub ECX,0x14
mov dword EAX,ECX
add EAX,0x0
mov dword [EBP-0x1c],EAX
;	@T3	T3	DEREFERENCE	
;	iSize	@T3	=	
mov dword ESI,[EBP-0x1c]
mov word ax,[ESI]
mov word [EBP-0x16],ax
;	T4	iSize	comp	requiredSize
mov word cx,[EBP-0x2]
cmp ax,cx
;	JG LABEL2
jg LABEL2
;	T4	0	=	
mov byte ah,0x0
mov byte [EBP-0x1d],ah
;	JMP LABEL8
jmp LABEL8
;LABEL2	T4	1	=	
LABEL2: mov byte ah,0x1
mov byte [EBP-0x1d],ah
;			ClearRegs	
;LABEL8		T4	comp	1
LABEL8: mov byte ah,[EBP-0x1d]
cmp ah,0x1
;	JNE LABEL9
jne LABEL9
;	JMP LABEL6
jmp LABEL6
;			ClearRegs	
;LABEL9	T5	&CurrentBlock	+	2
LABEL9: mov ECX,EBP
sub ECX,0x14
mov dword EAX,ECX
add EAX,0x2
mov dword [EBP-0x22],EAX
;	@T5	T5	DEREFERENCE	
;	LpCurrent	@T5	=	
mov dword ESI,[EBP-0x22]
mov dword ECX,[ESI]
mov dword [EBP-0xa],ECX
;	JMP LABEL3
jmp LABEL3
;			ClearRegs	
;LABEL6		LpCurrent	comp	0
LABEL6: mov dword EAX,[EBP-0xa]
cmp EAX,0x0
;	JNE LABEL4
jne LABEL4
;	T6	0	=	
mov byte ah,0x0
mov byte [EBP-0x23],ah
;	JMP LABEL10
jmp LABEL10
;LABEL4	T6	1	=	
LABEL4: mov byte ah,0x1
mov byte [EBP-0x23],ah
;			ClearRegs	
;LABEL10		T6	comp	1
LABEL10: mov byte ah,[EBP-0x23]
cmp ah,0x1
;	JNE LABEL11
jne LABEL11
;	T8	HEADERSIZE	cast	int16
mov byte ah,[EBX+0x4]
movsx cx,ah
mov word [EBP-0x2b],cx
;	T7	iSize	+	T8
mov word ax,[EBP-0x16]
mov word cx,[EBP-0x2b]
add ax,cx
mov word [EBP-0x29],ax
;	T9	T7	-	requiredSize
mov word dx,[EBP-0x2]
sub ax,dx
mov word [EBP-0x2d],ax
;	T10	T9	cast	int32
mov word cx,[EBP-0x2d]
movsx EDX,cx
mov dword [EBP-0x31],EDX
;	offset	T10	=	
mov dword ECX,[EBP-0x31]
mov dword [EBP-0x27],ECX
;	T11	LpCurrent	+	offset
mov dword EDX,[EBP-0xa]
add EDX,ECX
mov dword [EBP-0x35],EDX
;	LpAddress	T11	=	
mov dword [EBP-0xe],EDX
;	T12	&CurrentBlock	+	0
mov ESI,EBP
sub ESI,0x14
mov dword ECX,ESI
add ECX,0x0
mov dword [EBP-0x3a],ECX
;	@T12	T12	DEREFERENCE	
;	T13	iSize	-	requiredSize
mov word dx,[EBP-0x16]
mov word cx,[EBP-0x2]
sub dx,cx
mov word [EBP-0x3c],dx
;	@T12	T13	=	
mov dword ESI,[EBP-0x3a]
mov word [ESI],dx
;	@LpCurrent	LpCurrent	DEREFERENCE	
;	@LpCurrent	CurrentBlock	=	
mov dword EDX,[EBP-0xa]
mov dword EDI,EDX
mov EDX,EBP
sub EDX,0x14
mov dword ESI,EDX
mov dword ECX,0x1
LABEL12:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,4
 add EDI,4
LOOP LABEL12
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
;			ClearRegs	
;LABEL11	iSize	0	=	
LABEL11: mov word ax,0x0
mov word [EBP-0x16],ax
;		LpAddress	Return	
mov dword EAX,[EBP-0xe]
jmp Epilogue_heapobj_AllocateMemory
;writing Epilogue for function
Epilogue_heapobj_AllocateMemory:
add ESP,0x40
ret 

heapobj_FreeMemory:
sub ESP,0x1e
;	T14	&currentBlock	+	0
mov ECX,EBP
sub ECX,0xc
mov dword EAX,ECX
add EAX,0x0
mov dword [EBP-0x11],EAX
;	@T14	T14	DEREFERENCE	
;	T16	HEADERSIZE	cast	int16
mov byte ah,[EBX+0x4]
movsx cx,ah
mov word [EBP-0x15],cx
;	T15	iSize	-	T16
mov word ax,[EBP-0x6]
mov word cx,[EBP-0x15]
sub ax,cx
mov word [EBP-0x13],ax
;	@T14	T15	=	
mov dword ECX,[EBP-0x11]
mov word [ECX],ax
;	T17	&currentBlock	+	2
mov EDX,EBP
sub EDX,0xc
mov dword ECX,EDX
add ECX,0x2
mov dword [EBP-0x1a],ECX
;	@T17	T17	DEREFERENCE	
;	@T17	m_LpStart	=	
mov dword EDX,[EBX+0x0]
mov dword ESI,[EBP-0x1a]
mov dword [ESI],EDX
;	@p	p	DEREFERENCE	
;	@p	currentBlock	=	
mov dword EDX,[EBP-0x4]
mov dword EDI,EDX
mov EDX,EBP
sub EDX,0xc
mov dword ESI,EDX
mov dword ECX,0x1
LABEL13:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,4
 add EDI,4
LOOP LABEL13
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
;	m_LpStart	p	=	
mov dword EAX,[EBP-0x4]
mov dword [EBX+0x0],EAX
;writing Epilogue for function
Epilogue_heapobj_FreeMemory:
add ESP,0x1e
ret 

String_init:
sub ESP,0x4
;	m_iLength	0	=	
mov word ax,0x0
mov word [EBX+0x4],ax
;	m_szStringData	0	=	
mov dword EAX,0x0
mov dword [EBX+0x0],EAX
;writing Epilogue for function
Epilogue_String_init:
add ESP,0x4
ret 

String_getDataPointer:
sub ESP,0x4
;		m_szStringData	Return	
mov dword EAX,[EBX+0x0]
jmp Epilogue_String_getDataPointer
;writing Epilogue for function
Epilogue_String_getDataPointer:
add ESP,0x4
ret 

String_SetLength:
sub ESP,0xa
;		heap	SetEBX	
push EBX
mov dword EBX,heap
;		iLen	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov EAX,EBP
sub EAX,0x2
mov dword ESI,EAX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;	_Result.heapobj_AllocateMemory	heapobj_AllocateMemory	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call heapobj_AllocateMemory
pop EBP
mov dword [EBP-0x6],EAX
;			UnSetEBX	
pop EBX
;	m_szStringData	_Result.heapobj_AllocateMemory	=	
mov dword EAX,[EBP-0x6]
mov dword [EBX+0x0],EAX
;writing Epilogue for function
Epilogue_String_SetLength:
add ESP,0xa
ret 

String_copyBytes:
sub ESP,0xe
;			%LockRegister	
;			%LockRegister	
;			ASM	
;mov ESI,@charPointer
mov dword EAX,[EBP-0x8]
mov ESI,EAX
;mov EDI,@LpszDestPointer
mov dword EAX,[EBP-0x4]
mov EDI,EAX
;mov CX,@length
mov word ax,[EBP-0xa]
mov CX,ax
;movzx ECX,cx
movzx ECX,cx
L: mov byte ah,[ESI]
mov byte[EDI],ah
inc ESI
inc EDI
LOOP L
;			%UnLockRegister	
;			%UnLockRegister	
;writing Epilogue for function
Epilogue_String_copyBytes:
add ESP,0xe
ret 

String_IsEqualTo:
sub ESP,0x20
;	srcLen	m_iLength	=	
mov word ax,[EBX+0x4]
mov word [EBP-0xf],ax
;	T18	&st	+	4
mov ECX,EBP
sub ECX,0x8
mov dword EAX,ECX
add EAX,0x4
mov dword [EBP-0x16],EAX
;	@T18	T18	DEREFERENCE	
;	destLen	@T18	=	
mov dword ESI,[EBP-0x16]
mov word cx,[ESI]
mov word [EBP-0x11],cx
;		srcLen	comp	destLen
mov word dx,[EBP-0xf]
cmp dx,cx
;	JNE LABEL14
jne LABEL14
;	T19	0	=	
mov byte ah,0x0
mov byte [EBP-0x17],ah
;	JMP LABEL15
jmp LABEL15
;LABEL14	T19	1	=	
LABEL14: mov byte ah,0x1
mov byte [EBP-0x17],ah
;			ClearRegs	
;LABEL15		T19	comp	1
LABEL15: mov byte ah,[EBP-0x17]
cmp ah,0x1
;	JNE LABEL16
jne LABEL16
;	bFlag	0	=	
mov byte ah,0x0
mov byte [EBP-0xd],ah
;		bFlag	Return	
mov byte al,[EBP-0xd]
jmp Epilogue_String_IsEqualTo
;			ClearRegs	
;LABEL16	T20	&st	+	0
LABEL16: mov ECX,EBP
sub ECX,0x8
mov dword EAX,ECX
add EAX,0x0
mov dword [EBP-0x1c],EAX
;	@T20	T20	DEREFERENCE	
;	destCharpointer	@T20	=	
mov dword ESI,[EBP-0x1c]
mov dword ECX,[ESI]
mov dword [EBP-0xc],ECX
;		srcLen	%LockRegister	
;		destLen	%LockRegister	
;		destCharpointer	%LockRegister	
;		bFlag	%LockRegister	
;			ASM	
;mov esi,@m_szStringData
mov dword EAX,[EBX+0x0]
mov esi,EAX
;movzx ecx,@m_iLength
mov word ax,[EBX+0x4]
movzx ecx,ax
;mov edi,@destCharpointer
mov dword EAX,[EBP-0xc]
mov edi,EAX
;COMPLOOP: mov byte dl,[esi]
COMPLOOP: mov byte dl,[esi]
mov byte dh,[edi]
cmp dh,dl
jne NOTEQUAL
inc esi
inc edi
LOOP COMPLOOP
EQUAL:
mov dl,0x1
jmp DONE
NOTEQUAL: 
mov dl,0x0
DONE: mov EAX,EBP
sub EAX,0xd
mov dword EAX,EAX
 mov byte  [EAX],dl
;		srcLen	%UnLockRegister	
;		destCharpointer	%UnLockRegister	
;		bFlag	%UnLockRegister	
;		destLen	%UnLockRegister	
;		bFlag	Return	
mov byte al,[EBP-0xd]
jmp Epilogue_String_IsEqualTo
;writing Epilogue for function
Epilogue_String_IsEqualTo:
add ESP,0x20
ret 

String_ConcatInteger:
sub ESP,0x27
;	isrcLength	10	=	
mov word ax,0xa
mov word [EBP-0x6],ax
;	T21	isrcLength	+	m_iLength
mov word cx,[EBX+0x4]
add ax,cx
mov word [EBP-0x16],ax
;	iresultLength	T21	=	
mov word [EBP-0x8],ax
;	LpszOriginal	m_szStringData	=	
mov dword EAX,[EBX+0x0]
mov dword [EBP-0x10],EAX
;		heap	SetEBX	
push EBX
mov dword EBX,heap
;		iresultLength	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov ECX,EBP
sub ECX,0x8
mov dword ESI,ECX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;	_Result.heapobj_AllocateMemory	heapobj_AllocateMemory	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call heapobj_AllocateMemory
pop EBP
mov dword [EBP-0x1a],EAX
;			UnSetEBX	
pop EBX
;	m_szStringData	_Result.heapobj_AllocateMemory	=	
mov dword EAX,[EBP-0x1a]
mov dword [EBX+0x0],EAX
;		LpszOriginal	comp	0
mov dword ECX,[EBP-0x10]
cmp ECX,0x0
;	JNE LABEL17
jne LABEL17
;	T22	0	=	
mov byte ah,0x0
mov byte [EBP-0x1b],ah
;	JMP LABEL18
jmp LABEL18
;LABEL17	T22	1	=	
LABEL17: mov byte ah,0x1
mov byte [EBP-0x1b],ah
;			ClearRegs	
;LABEL18		T22	comp	1
LABEL18: mov byte ah,[EBP-0x1b]
cmp ah,0x1
;	JNE LABEL19
jne LABEL19
;		m_szStringData	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov EAX,EBX
add EAX,0x0
mov dword ESI,EAX
sub EDI,0x4
mov dword ECX,0x1
LABEL20:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL20
sub EDI,0x4
;		LpszOriginal	PUSH_FUN_PAR	
mov EAX,EBP
sub EAX,0x10
mov dword ESI,EAX
sub EDI,0x4
mov dword ECX,0x1
LABEL21:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL21
sub EDI,0x4
;		m_iLength	PUSH_FUN_PAR	
mov EAX,EBX
add EAX,0x4
mov dword ESI,EAX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;		String_copyBytes	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call String_copyBytes
pop EBP
mov ECX,EBP
sub ECX,0x0
mov dword EDI,ECX
mov dword ESI,EAX
;			ClearRegs	
;LABEL19	T24	m_iLength	cast	Pointer
LABEL19: mov word ax,[EBX+0x4]
movsx ECX,ax
mov dword [EBP-0x23],ECX
;	T23	m_szStringData	+	T24
mov dword EAX,[EBX+0x0]
mov dword ECX,[EBP-0x23]
add EAX,ECX
mov dword [EBP-0x1f],EAX
;	LpTarget	T23	=	
mov dword [EBP-0x14],EAX
;		LpszSource	%LockRegister	
;		isrcLength	%LockRegister	
;		iresultLength	%LockRegister	
;		LpszOriginal	%LockRegister	
;			ASM	
;xor edi,edi
xor edi,edi
mov dword EAX,[EBP-0x14]
mov  edi,EAX
;mov eax,@intValue
mov dword EAX,[EBP-0x4]
mov eax,EAX
;mov ecx,1000000000
mov ecx,1000000000
mov edx,0x0
cmp eax,0x7FFFFFFF
jb conv_loop_int
mov byte [edi],'-'
inc edi
neg eax
conv_loop_int:
cmp eax,0x0
je divAndADD_int
cmp  eax,ecx
jge divAndADD_int
idiv  ecx
jmp skip_add_int
divAndADD_int:idiv  ecx
add al,48
mov byte [edi],al
inc edi
skip_add_int:mov esi,edx
mov eax,ecx
mov edx,0x0
mov  ecx,10
div ecx
cmp eax,0x0
jz stop_int
mov ecx,eax
mov eax,esi
mov edx,0x0
jmp conv_loop_int
stop_int:
mov eax,esi
mov byte [edi],al
inc edi
mov dword EAX,[EBX+0x0]
mov esi,EAX
;sub edi,esi
sub edi,esi
mov EAX,EBX
add EAX,0x4
mov dword EAX,EAX
mov  [EAX],sp
;		LpszSource	%UnLockRegister	
;		isrcLength	%UnLockRegister	
;		iresultLength	%UnLockRegister	
;		LpszOriginal	%UnLockRegister	
;writing Epilogue for function
Epilogue_String_ConcatInteger:
add ESP,0x27
ret 

String_SetString:
sub ESP,0xf
;		charPointer	comp	0
mov dword EAX,[EBP-0x4]
cmp EAX,0x0
;	JE LABEL22
je LABEL22
;	T25	0	=	
mov byte ah,0x0
mov byte [EBP-0x7],ah
;	JMP LABEL23
jmp LABEL23
;LABEL22	T25	1	=	
LABEL22: mov byte ah,0x1
mov byte [EBP-0x7],ah
;			ClearRegs	
;LABEL23		T25	comp	1
LABEL23: mov byte ah,[EBP-0x7]
cmp ah,0x1
;	JNE LABEL24
jne LABEL24
;	m_szStringData	0	=	
mov dword EAX,0x0
mov dword [EBX+0x0],EAX
;	m_iLength	0	=	
mov word ax,0x0
mov word [EBX+0x4],ax
;			Return	
jmp Epilogue_String_SetString
;			ClearRegs	
;LABEL24		heap	SetEBX	
LABEL24: push EBX
mov dword EBX,heap
;		length	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov EAX,EBP
sub EAX,0x6
mov dword ESI,EAX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;	_Result.heapobj_AllocateMemory	heapobj_AllocateMemory	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call heapobj_AllocateMemory
pop EBP
mov dword [EBP-0xb],EAX
;			UnSetEBX	
pop EBX
;	m_szStringData	_Result.heapobj_AllocateMemory	=	
mov dword EAX,[EBP-0xb]
mov dword [EBX+0x0],EAX
;		m_szStringData	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov ECX,EBX
add ECX,0x0
mov dword ESI,ECX
sub EDI,0x4
mov dword ECX,0x1
LABEL25:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL25
sub EDI,0x4
;		charPointer	PUSH_FUN_PAR	
mov ECX,EBP
sub ECX,0x4
mov dword ESI,ECX
sub EDI,0x4
mov dword ECX,0x1
LABEL26:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL26
sub EDI,0x4
;		length	PUSH_FUN_PAR	
mov ECX,EBP
sub ECX,0x6
mov dword ESI,ECX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;		String_copyBytes	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call String_copyBytes
pop EBP
mov ECX,EBP
sub ECX,0x0
mov dword EDI,ECX
mov dword ESI,EAX
;	m_iLength	length	=	
mov word ax,[EBP-0x6]
mov word [EBX+0x4],ax
;writing Epilogue for function
Epilogue_String_SetString:
add ESP,0xf
ret 

String_CopyString:
sub ESP,0x20
;	T26	&st	+	4
mov ECX,EBP
sub ECX,0x8
mov dword EAX,ECX
add EAX,0x4
mov dword [EBP-0x13],EAX
;	@T26	T26	DEREFERENCE	
;	iLength	@T26	=	
mov dword ESI,[EBP-0x13]
mov word cx,[ESI]
mov word [EBP-0xa],cx
;	T27	&st	+	0
mov EDX,EBP
sub EDX,0x8
mov dword ECX,EDX
add ECX,0x0
mov dword [EBP-0x18],ECX
;	@T27	T27	DEREFERENCE	
;	LpszSource	@T27	=	
mov dword ESI,[EBP-0x18]
mov dword EDX,[ESI]
mov dword [EBP-0xe],EDX
;		heap	SetEBX	
push EBX
mov dword EBX,heap
;		iLength	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov EDX,EBP
sub EDX,0xa
mov dword ESI,EDX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;	_Result.heapobj_AllocateMemory	heapobj_AllocateMemory	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call heapobj_AllocateMemory
pop EBP
mov dword [EBP-0x1c],EAX
;			UnSetEBX	
pop EBX
;	m_szStringData	_Result.heapobj_AllocateMemory	=	
mov dword EAX,[EBP-0x1c]
mov dword [EBX+0x0],EAX
;		m_szStringData	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov ECX,EBX
add ECX,0x0
mov dword ESI,ECX
sub EDI,0x4
mov dword ECX,0x1
LABEL27:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL27
sub EDI,0x4
;		LpszSource	PUSH_FUN_PAR	
mov ECX,EBP
sub ECX,0xe
mov dword ESI,ECX
sub EDI,0x4
mov dword ECX,0x1
LABEL28:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL28
sub EDI,0x4
;		iLength	PUSH_FUN_PAR	
mov ECX,EBP
sub ECX,0xa
mov dword ESI,ECX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;		String_copyBytes	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call String_copyBytes
pop EBP
mov ECX,EBP
sub ECX,0x0
mov dword EDI,ECX
mov dword ESI,EAX
;	m_iLength	iLength	=	
mov word ax,[EBP-0xa]
mov word [EBX+0x4],ax
;writing Epilogue for function
Epilogue_String_CopyString:
add ESP,0x20
ret 

String_ConcatString:
sub ESP,0x38
;	T28	&st	+	4
mov ECX,EBP
sub ECX,0x8
mov dword EAX,ECX
add EAX,0x4
mov dword [EBP-0x1d],EAX
;	@T28	T28	DEREFERENCE	
;	isrcLength	@T28	=	
mov dword ESI,[EBP-0x1d]
mov word cx,[ESI]
mov word [EBP-0xa],cx
;	T29	&st	+	0
mov EDX,EBP
sub EDX,0x8
mov dword ECX,EDX
add ECX,0x0
mov dword [EBP-0x22],ECX
;	@T29	T29	DEREFERENCE	
;	LpszSource	@T29	=	
mov dword ESI,[EBP-0x22]
mov dword EDX,[ESI]
mov dword [EBP-0x10],EDX
;	T30	isrcLength	+	m_iLength
mov word dx,[EBP-0xa]
mov word ax,[EBX+0x4]
add dx,ax
mov word [EBP-0x24],dx
;	iresultLength	T30	=	
mov word [EBP-0xc],dx
;	LpszOriginal	m_szStringData	=	
mov dword EDX,[EBX+0x0]
mov dword [EBP-0x14],EDX
;		heap	SetEBX	
push EBX
mov dword EBX,heap
;	T31	iresultLength	+	1
mov word cx,[EBP-0xc]
add cx,0x1
mov word [EBP-0x26],cx
;		T31	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov EAX,EBP
sub EAX,0x26
mov dword ESI,EAX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;	_Result.heapobj_AllocateMemory	heapobj_AllocateMemory	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call heapobj_AllocateMemory
pop EBP
mov dword [EBP-0x2a],EAX
;			UnSetEBX	
pop EBX
;	m_szStringData	_Result.heapobj_AllocateMemory	=	
mov dword EAX,[EBP-0x2a]
mov dword [EBX+0x0],EAX
;		LpszOriginal	comp	0
mov dword ECX,[EBP-0x14]
cmp ECX,0x0
;	JNE LABEL29
jne LABEL29
;	T32	0	=	
mov byte ah,0x0
mov byte [EBP-0x2b],ah
;	JMP LABEL31
jmp LABEL31
;LABEL29	T32	1	=	
LABEL29: mov byte ah,0x1
mov byte [EBP-0x2b],ah
;			ClearRegs	
;LABEL31		T32	comp	1
LABEL31: mov byte ah,[EBP-0x2b]
cmp ah,0x1
;	JNE LABEL32
jne LABEL32
;		m_szStringData	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov EAX,EBX
add EAX,0x0
mov dword ESI,EAX
sub EDI,0x4
mov dword ECX,0x1
LABEL33:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL33
sub EDI,0x4
;		LpszOriginal	PUSH_FUN_PAR	
mov EAX,EBP
sub EAX,0x14
mov dword ESI,EAX
sub EDI,0x4
mov dword ECX,0x1
LABEL34:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL34
sub EDI,0x4
;		m_iLength	PUSH_FUN_PAR	
mov EAX,EBX
add EAX,0x4
mov dword ESI,EAX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;		String_copyBytes	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call String_copyBytes
pop EBP
mov ECX,EBP
sub ECX,0x0
mov dword EDI,ECX
mov dword ESI,EAX
;			ClearRegs	
;LABEL32	T34	m_iLength	cast	Pointer
LABEL32: mov word ax,[EBX+0x4]
movsx ECX,ax
mov dword [EBP-0x33],ECX
;	T33	m_szStringData	+	T34
mov dword EAX,[EBX+0x0]
mov dword ECX,[EBP-0x33]
add EAX,ECX
mov dword [EBP-0x2f],EAX
;	LpTarget	T33	=	
mov dword [EBP-0x18],EAX
;		LpszSource	comp	0
mov dword EDX,[EBP-0x10]
cmp EDX,0x0
;	JNE LABEL30
jne LABEL30
;	T35	0	=	
mov byte ah,0x0
mov byte [EBP-0x34],ah
;	JMP LABEL35
jmp LABEL35
;LABEL30	T35	1	=	
LABEL30: mov byte ah,0x1
mov byte [EBP-0x34],ah
;			ClearRegs	
;LABEL35		T35	comp	1
LABEL35: mov byte ah,[EBP-0x34]
cmp ah,0x1
;	JNE LABEL36
jne LABEL36
;		LpTarget	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov EAX,EBP
sub EAX,0x18
mov dword ESI,EAX
sub EDI,0x4
mov dword ECX,0x1
LABEL37:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL37
sub EDI,0x4
;		LpszSource	PUSH_FUN_PAR	
mov EAX,EBP
sub EAX,0x10
mov dword ESI,EAX
sub EDI,0x4
mov dword ECX,0x1
LABEL38:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL38
sub EDI,0x4
;		isrcLength	PUSH_FUN_PAR	
mov EAX,EBP
sub EAX,0xa
mov dword ESI,EAX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;		String_copyBytes	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call String_copyBytes
pop EBP
mov ECX,EBP
sub ECX,0x0
mov dword EDI,ECX
mov dword ESI,EAX
;			ClearRegs	
;LABEL36	m_iLength	iresultLength	=	
LABEL36: mov word ax,[EBP-0xc]
mov word [EBX+0x4],ax
;writing Epilogue for function
Epilogue_String_ConcatString:
add ESP,0x38
ret 

String_ConcatByteArray:
sub ESP,0x28
;	T36	length	+	m_iLength
mov word cx,[EBP-0x6]
mov word dx,[EBX+0x4]
add cx,dx
mov word [EBP-0x14],cx
;	iresultLength	T36	=	
mov word [EBP-0xa],cx
;	LpszOriginal	m_szStringData	=	
mov dword EAX,[EBX+0x0]
mov dword [EBP-0xe],EAX
;		heap	SetEBX	
push EBX
mov dword EBX,heap
;	T37	iresultLength	+	1
add cx,0x1
mov word [EBP-0x16],cx
;		T37	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov ECX,EBP
sub ECX,0x16
mov dword ESI,ECX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;	_Result.heapobj_AllocateMemory	heapobj_AllocateMemory	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call heapobj_AllocateMemory
pop EBP
mov dword [EBP-0x1a],EAX
;			UnSetEBX	
pop EBX
;	m_szStringData	_Result.heapobj_AllocateMemory	=	
mov dword EAX,[EBP-0x1a]
mov dword [EBX+0x0],EAX
;		LpszOriginal	comp	0
mov dword ECX,[EBP-0xe]
cmp ECX,0x0
;	JNE LABEL39
jne LABEL39
;	T38	0	=	
mov byte ah,0x0
mov byte [EBP-0x1b],ah
;	JMP LABEL41
jmp LABEL41
;LABEL39	T38	1	=	
LABEL39: mov byte ah,0x1
mov byte [EBP-0x1b],ah
;			ClearRegs	
;LABEL41		T38	comp	1
LABEL41: mov byte ah,[EBP-0x1b]
cmp ah,0x1
;	JNE LABEL42
jne LABEL42
;		m_szStringData	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov EAX,EBX
add EAX,0x0
mov dword ESI,EAX
sub EDI,0x4
mov dword ECX,0x1
LABEL43:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL43
sub EDI,0x4
;		LpszOriginal	PUSH_FUN_PAR	
mov EAX,EBP
sub EAX,0xe
mov dword ESI,EAX
sub EDI,0x4
mov dword ECX,0x1
LABEL44:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL44
sub EDI,0x4
;		m_iLength	PUSH_FUN_PAR	
mov EAX,EBX
add EAX,0x4
mov dword ESI,EAX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;		String_copyBytes	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call String_copyBytes
pop EBP
mov ECX,EBP
sub ECX,0x0
mov dword EDI,ECX
mov dword ESI,EAX
;			ClearRegs	
;LABEL42	T40	m_iLength	cast	Pointer
LABEL42: mov word ax,[EBX+0x4]
movsx ECX,ax
mov dword [EBP-0x23],ECX
;	T39	m_szStringData	+	T40
mov dword EAX,[EBX+0x0]
mov dword ECX,[EBP-0x23]
add EAX,ECX
mov dword [EBP-0x1f],EAX
;	LpTarget	T39	=	
mov dword [EBP-0x12],EAX
;		bytePointer	comp	0
mov dword EDX,[EBP-0x4]
cmp EDX,0x0
;	JNE LABEL40
jne LABEL40
;	T41	0	=	
mov byte ah,0x0
mov byte [EBP-0x24],ah
;	JMP LABEL45
jmp LABEL45
;LABEL40	T41	1	=	
LABEL40: mov byte ah,0x1
mov byte [EBP-0x24],ah
;			ClearRegs	
;LABEL45		T41	comp	1
LABEL45: mov byte ah,[EBP-0x24]
cmp ah,0x1
;	JNE LABEL46
jne LABEL46
;		LpTarget	PUSH_FUN_PAR	
mov EDI,ESP
 sub EDI,0x8
mov EAX,EBP
sub EAX,0x12
mov dword ESI,EAX
sub EDI,0x4
mov dword ECX,0x1
LABEL47:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL47
sub EDI,0x4
;		bytePointer	PUSH_FUN_PAR	
mov EAX,EBP
sub EAX,0x4
mov dword ESI,EAX
sub EDI,0x4
mov dword ECX,0x1
LABEL48:  mov dword EAX,[ESI]
mov dword [EDI],EAX
 add ESI,0x4
 add EDI,0x4
LOOP LABEL48
sub EDI,0x4
;		length	PUSH_FUN_PAR	
mov EAX,EBP
sub EAX,0x6
mov dword ESI,EAX
sub EDI,0x2
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
mov byte ah,[ESI]
 mov byte [EDI],ah 
 inc ESI 
 inc EDI
sub EDI,0x2
;		String_copyBytes	CALL	
add EDI,0x1
sub EDI,0x0
push EBP
 mov EBP,ESP
 sub EBP,0x4
call String_copyBytes
pop EBP
mov ECX,EBP
sub ECX,0x0
mov dword EDI,ECX
mov dword ESI,EAX
;			ClearRegs	
;LABEL46	m_iLength	iresultLength	=	
LABEL46: mov word ax,[EBP-0xa]
mov word [EBX+0x4],ax
;writing Epilogue for function
Epilogue_String_ConcatByteArray:
add ESP,0x28
ret 

String_getLength:
sub ESP,0x4
;		m_iLength	Return	
mov word ax,[EBX+0x4]
jmp Epilogue_String_getLength
;writing Epilogue for function
Epilogue_String_getLength:
add ESP,0x4
ret 

Display_init:
sub ESP,0x4
;	m_iCursorPos	0	=	
mov word ax,0x0
mov word [EBX+0x0],ax
;writing Epilogue for function
Epilogue_Display_init:
add ESP,0x4
ret 

Display_PrintInteger:
sub ESP,0x8
;			%LockRegister	
;			%LockRegister	
;			%LockRegister	
;			%LockRegister	
;			ASM	
;mov ax,0xB800
mov ax,0xB800
mov gs,ax
mov  edi,0x0
mov word ax,[EBX+0x0]
mov  di,ax
;mov eax,@intValue
mov dword EAX,[EBP-0x4]
mov eax,EAX
;mov ecx,1000000000
mov ecx,1000000000
mov edx,0x0
cmp eax,0x7FFFFFFF
jb conv_loop
mov byte [gs:edi],'-'
add edi,0x2
neg eax
conv_loop:
cmp eax,0x0
je divAndPrint
cmp  eax,ecx
jge divAndPrint
idiv  ecx
jmp skip_print
divAndPrint:idiv  ecx
add al,48
mov byte [gs:edi],al
add edi,0x2
skip_print:mov esi,edx
mov eax,ecx
mov edx,0x0
mov  ecx,10
div ecx
cmp eax,0x0
jz stop
mov ecx,eax
mov eax,esi
mov edx,0x0
jmp conv_loop
stop:
mov eax,esi
mov byte [gs:edi],al
add edi,0x2
mov EAX,EBX
add EAX,0x0
mov dword EAX,EAX
mov  [EAX],sp
;		m_iCursorPos	%UnLockRegister	
;			%UnLockRegister	
;			%UnLockRegister	
;			%UnLockRegister	
;writing Epilogue for function
Epilogue_Display_PrintInteger:
add ESP,0x8
ret 

Display_PrintString:
sub ESP,0x1d
;	T42	&strValue	+	0
mov ECX,EBP
sub ECX,0x8
mov dword EAX,ECX
add EAX,0x0
mov dword [EBP-0x13],EAX
;	@T42	T42	DEREFERENCE	
;	strAddr	@T42	=	
mov dword ESI,[EBP-0x13]
mov dword ECX,[ESI]
mov dword [EBP-0xe],ECX
;		strAddr	comp	0
cmp ECX,0x0
;	JE LABEL49
je LABEL49
;	T43	0	=	
mov byte ah,0x0
mov byte [EBP-0x14],ah
;	JMP LABEL50
jmp LABEL50
;LABEL49	T43	1	=	
LABEL49: mov byte ah,0x1
mov byte [EBP-0x14],ah
;			ClearRegs	
;LABEL50		T43	comp	1
LABEL50: mov byte ah,[EBP-0x14]
cmp ah,0x1
;	JNE LABEL51
jne LABEL51
;			Return	
jmp Epilogue_Display_PrintString
;			ClearRegs	
;LABEL51	T44	&strValue	+	4
LABEL51: mov ECX,EBP
sub ECX,0x8
mov dword EAX,ECX
add EAX,0x4
mov dword [EBP-0x19],EAX
;	@T44	T44	DEREFERENCE	
;	strLen	@T44	=	
mov dword ESI,[EBP-0x19]
mov word ax,[ESI]
mov word [EBP-0xa],ax
;		&strValue	%LockRegister	
;		0	%LockRegister	
;		strLen	%LockRegister	
;			ASM	
;xor ecx,ecx
xor ecx,ecx
mov ax,0xB800
mov gs,ax
mov  edi,0x0
mov word ax,[EBX+0x0]
mov  di,ax
;mov cx,@strLen
mov word ax,[EBP-0xa]
mov cx,ax
;mov esi,@strAddr
mov dword EAX,[EBP-0xe]
mov esi,EAX
;.print_loop: 
.print_loop: 
mov byte  al,[esi]
mov byte [gs:edi],al
add edi,0x2
inc esi
LOOP .print_loop
add edi,0x2
mov EAX,EBX
add EAX,0x0
mov dword EAX,EAX
mov  [EAX],sp
;		&strValue	%UnLockRegister	
;		0	%UnLockRegister	
;		strLen	%UnLockRegister	
;writing Epilogue for function
Epilogue_Display_PrintString:
add ESP,0x1d
ret 

__main:
sub ESP,0x1
;	i	9	=	
mov byte ah,0x9
mov byte [EBP-0x1],ah
;writing Epilogue for function
Epilogue___main:
add ESP,0x1
main_hang: jmp main_hang
ret 

commgr_GetSome:
sub ESP,0x2
;	i	12	=	
mov word ax,0xc
mov word [EBP-0x2],ax
;writing Epilogue for function
Epilogue_commgr_GetSome:
add ESP,0x2
ret 

heap resb 5
displayObject resb 2
Data resb 600
heapspace resb 1024 
ISR resb 180
ObjectData resb 300
times 368640-($-$$) db 0
