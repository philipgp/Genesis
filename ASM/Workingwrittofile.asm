;; Define the externs. 
extern MessageBoxA 
extern ExitProcess 
extern OpenFile 
extern ReadFile 
extern WriteFile 
extern CloseHandle 
extern GetFileSize 

;; Construct our symbol import table. 
import MessageBoxA user32.dll 
import ExitProcess kernel32.dll 
import OpenFile kernel32.dll 
import ReadFile kernel32.dll 
import WriteFile kernel32.dll 
import CloseHandle kernel32.dll 
import GetFileSize kernel32.dll 

;; This goes into the code section; use 32-bit code. 
section .text use32 
;; This is where the program should start running. 
..start: 

;; Call the main() function. 
call main 

;; Exit, returning whatever main() returned. 
push eax 
call [ExitProcess] 

main: 
	enter 148, 0 
	lea ebx, [ebp-148]                ;; The address of the OFSTRUCT structure. 
	push dword 1 | 0x1000             ;; OF_WRITE | OF_CREATE 
	push ebx 
	push dword filename1 
	call [OpenFile] 
	mov dword [ebp-4], eax            ;; Save the file handle. 
	lea ebx, [ebp-8]                  ;; The number of bytes written will be saved there. 
	push dword 0 
	push ebx 
	push dword 0x1         ;; Size of the message. 
	push dword mymsg                    ;; The address of the message. 
	push dword [ebp-4]                ;; The handle to use for writing to file. 
	call [WriteFile]  
	push dword [ebp-4]                ;; The file handle. 
	call [CloseHandle] 
	leave
ret 

section .data 

filename1                                    db "FileIncbin.txt", 0 
mymsg db 0x67
