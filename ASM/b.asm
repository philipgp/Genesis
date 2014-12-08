Define ObjectType KeyBoard
int8 CurKey;
int8 m_bShiftPressed;
int8 m_iScanCode[255];
Function init()
{
m_bShiftPressed=0;
_asm{
mov EAX,&m_iScanCode
inc EAX
inc EAX
mov byte [EAX],'1'
inc EAX
mov byte [EAX],'2'
inc EAX
mov byte [EAX],'3'
inc EAX
mov byte [EAX],'4'
inc EAX
mov byte [EAX],'5'
inc EAX
mov byte [EAX],'6'
inc EAX
mov byte [EAX],'7'
inc EAX
mov byte [EAX],'8'
inc EAX
mov byte [EAX],'9'
inc EAX
mov byte [EAX],'0'
inc EAX
mov byte [EAX],'-'
inc EAX
mov byte [EAX],'='
inc EAX
inc EAX
inc EAX
mov byte [EAX],'q'
inc EAX
mov byte [EAX],'w'
inc EAX
mov byte [EAX],'e'
inc EAX
mov byte [EAX],'r'
inc EAX
mov byte [EAX],'t'
inc EAX
mov byte [EAX],'y'
inc EAX
mov byte [EAX],'u'
inc EAX
mov byte [EAX],'i'
inc EAX
mov byte [EAX],'o'
inc EAX
mov byte [EAX],'p'
inc EAX
mov byte [EAX],'['
inc EAX
mov byte [EAX],']'
inc EAX
inc EAX
inc EAX
mov byte [EAX],'a'
inc EAX
mov byte [EAX],'s'
inc EAX
mov byte [EAX],'d'
inc EAX
mov byte [EAX],'f'
inc EAX
mov byte [EAX],'g'
inc EAX
mov byte [EAX],'h'
inc EAX
mov byte [EAX],'j'
inc EAX
mov byte [EAX],'k'
inc EAX
mov byte [EAX],'l'
inc EAX
mov byte [EAX],';'
inc EAX
mov byte [EAX],'\''
inc EAX
mov byte [EAX],'`'
}
m_bShiftPressed=0;
}
Interrupt HandleInput()
{
uint8 CurScanCode;
int8 m;
%LockRegister(EAX);
_asm{
spin:
in  al, 0x64
and al, 0x01
jz  spin
in al,0x60
mov byte @CurScanCode,al
}
%UnLockRegister(EAX);
if (CurScanCode==42)  Then
m_bShiftPressed=1;
Elseif(CurScanCode==170) Then
m_bShiftPressed=0;
else
CurKey=m_iScanCode[CurScanCode];
if (m_bShiftPressed==1) Then
CurKey=CurKey-32;
EndIf
m=2;
If(CurScanCode<127) Then
print_ascii_os(CurKey);
EndIf
EndIf
m=2;
_asm{
mov al, 0x20
out 0x20, al
}
}
Function start()
{
int8 h;
init();
_asm{
cli
mov word[es:(9*4)], KeyBoard_HandleInput
mov word[es:(9*4)+2], 0
sti
jmp $
}
h=67;
}
EndDefine
