;
; Input	MD5   :	542EE6516410709A1421141501F03760
; Input	CRC32 :	C1AC4CCB

; File Name   :	C:\Users\eric\Downloads\r0pbaby_542ee6516410709a1421141501f03760
; Format      :	ELF64 for x86-64 (Shared object)
; Interpreter '/lib64/ld-linux-x86-64.so.2'
; Needed Library 'libdl.so.2'
; Needed Library 'libc.so.6'
;

		.686p
		.mmx
		.model flat
.intel_syntax noprefix

; ===========================================================================

; Segment type:	Pure code
; Segment permissions: Read/Execute
_init		segment	dword public 'CODE' use64
		assume cs:_init
		;org 940h
		assume es:nothing, ss:nothing, ds:_data, fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================


		public _init_proc
_init_proc	proc near		; CODE XREF: sub_EC0+2Ep
		sub	rsp, 8
		mov	rax, cs:__gmon_start___ptr
		test	rax, rax
		jz	short loc_955
		call	___gmon_start__

loc_955:				; CODE XREF: _init_proc+Ej
		add	rsp, 8
		retn
_init_proc	endp

_init		ends

; ===========================================================================

; Segment type:	Pure code
; Segment permissions: Read/Execute
_plt		segment	para public 'CODE' use64
		assume cs:_plt
		;org 960h
		assume es:nothing, ss:nothing, ds:_data, fs:nothing, gs:nothing
		dq 2 dup(?)
; [00000006 BYTES: COLLAPSED FUNCTION _puts. PRESS KEYPAD CTRL-"+" TO EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION _alarm. PRESS KEYPAD CTRL-"+" TO EXPAND]
		dw ?
		dq ?

; =============== S U B	R O U T	I N E =======================================

; Attributes: thunk

___libc_start_main proc	near		; CODE XREF: start+24p
		jmp	cs:off_202028
___libc_start_main endp

; ---------------------------------------------------------------------------
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION _signal. PRESS KEYPAD CTRL-"+" TO	EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION ___gmon_start__. PRESS KEYPAD CTRL-"+" TO	EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION _strtol. PRESS KEYPAD CTRL-"+" TO	EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION _memcpy. PRESS KEYPAD CTRL-"+" TO	EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION _dlopen. PRESS KEYPAD CTRL-"+" TO	EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION __IO_getc. PRESS KEYPAD CTRL-"+" TO EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION _dlclose.	PRESS KEYPAD CTRL-"+" TO EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION ___printf_chk. PRESS KEYPAD CTRL-"+" TO EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION _setvbuf.	PRESS KEYPAD CTRL-"+" TO EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION _exit. PRESS KEYPAD CTRL-"+" TO EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION _dlsym. PRESS KEYPAD CTRL-"+" TO EXPAND]
		dw ?
		dq ?
; [00000006 BYTES: COLLAPSED FUNCTION ___cxa_finalize. PRESS KEYPAD CTRL-"+" TO	EXPAND]
		dw ?
		dq ?
_plt		ends

; ===========================================================================

; Segment type:	Pure code
; Segment permissions: Read/Execute
_text		segment	para public 'CODE' use64
		assume cs:_text
		;org 0A60h
		assume es:nothing, ss:nothing, ds:_data, fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================

; Attributes: noreturn

		public start
start		proc near
		xor	ebp, ebp
		mov	r9, rdx
		pop	rsi
		mov	rdx, rsp
		and	rsp, 0FFFFFFFFFFFFFFF0h
		push	rax
		push	rsp
		lea	r8, nullsub_1
		lea	rcx, sub_EC0
		lea	rdi, sub_C46
		call	___libc_start_main
		hlt
start		endp

; ---------------------------------------------------------------------------
		align 10h

; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_A90		proc near		; CODE XREF: sub_B00:loc_B23p
		lea	rax, unk_2020A7
		lea	rdi, _edata
		push	rbp
		sub	rax, rdi
		mov	rbp, rsp
		cmp	rax, 0Eh
		ja	short loc_AAD

loc_AAB:				; CODE XREF: sub_A90+27j
		pop	rbp
		retn
; ---------------------------------------------------------------------------

loc_AAD:				; CODE XREF: sub_A90+19j
		mov	rax, cs:_ITM_deregisterTMCloneTable_ptr
		test	rax, rax
		jz	short loc_AAB
		pop	rbp
		jmp	rax
sub_A90		endp

; ---------------------------------------------------------------------------
		align 20h
; START	OF FUNCTION CHUNK FOR sub_B40

loc_AC0:				; CODE XREF: sub_B40+24j
					; sub_B40:loc_B70j
		lea	rax, _edata
		lea	rdi, _edata
		push	rbp
		sub	rax, rdi
		mov	rbp, rsp
		sar	rax, 3
		mov	rdx, rax
		shr	rdx, 3Fh
		add	rax, rdx
		sar	rax, 1
		jnz	short loc_AEA

loc_AE8:				; CODE XREF: sub_B40-4Cj
		pop	rbp
		retn
; ---------------------------------------------------------------------------

loc_AEA:				; CODE XREF: sub_B40-5Aj
		mov	rdx, cs:_ITM_registerTMCloneTable_ptr
		test	rdx, rdx
		jz	short loc_AE8
		pop	rbp
		mov	rsi, rax
		jmp	rdx
; END OF FUNCTION CHUNK	FOR sub_B40
; ---------------------------------------------------------------------------
		align 20h

; =============== S U B	R O U T	I N E =======================================


sub_B00		proc near		; DATA XREF: .fini_array:off_201DD8o
		cmp	cs:_edata, 0
		jnz	short locret_B30
		cmp	cs:__cxa_finalize_ptr, 0
		push	rbp
		mov	rbp, rsp
		jz	short loc_B23
		mov	rdi, cs:off_202098
		call	___cxa_finalize

loc_B23:				; CODE XREF: sub_B00+15j
		call	sub_A90
		pop	rbp
		mov	cs:_edata, 1

locret_B30:				; CODE XREF: sub_B00+7j
		rep retn
sub_B00		endp

; ---------------------------------------------------------------------------
		align 20h

; =============== S U B	R O U T	I N E =======================================


sub_B40		proc near		; DATA XREF: .init_array:off_201DD0o

; FUNCTION CHUNK AT 0000000000000AC0 SIZE 0000003C BYTES

		cmp	cs:qword_201DE0, 0
		jz	short loc_B70
		mov	rax, cs:_Jv_RegisterClasses_ptr
		test	rax, rax
		jz	short loc_B70
		push	rbp
		lea	rdi, qword_201DE0
		mov	rbp, rsp
		call	rax ; _Jv_RegisterClasses
		pop	rbp
		jmp	loc_AC0
; ---------------------------------------------------------------------------
		align 10h

loc_B70:				; CODE XREF: sub_B40+8j sub_B40+14j
		jmp	loc_AC0
sub_B40		endp

; ---------------------------------------------------------------------------
		align 20h

; =============== S U B	R O U T	I N E =======================================

; Attributes: noreturn

; void handler(int)
handler		proc near		; DATA XREF: sub_C46+32o
		sub	rsp, 8
		lea	rdi, s		; "Connection timeout, closing."
		call	_puts
		mov	edi, 1		; status
		call	_exit
handler		endp


; =============== S U B	R O U T	I N E =======================================


sub_B9A		proc near		; CODE XREF: sub_C46+91p sub_C46+12Fp	...
		push	r14
		push	r13
		push	r12
		push	rbp
		push	rbx
		mov	r12, rdi
		sub	rsi, 1
		mov	r14, rsi
		jz	short loc_BE3
		mov	ebx, 0
		mov	ebp, 0
		mov	r13, cs:stdin_ptr

loc_BBF:				; CODE XREF: sub_B9A+45j
		mov	rdi, [r13+0]	; fp
		call	__IO_getc
		cmp	eax, 0FFFFFFFFh
		jz	short loc_BE6
		cmp	eax, 0Ah
		jz	short loc_BE6
		add	ebp, 1
		mov	[r12+rbx], al
		movsxd	rbx, ebp
		cmp	rbx, r14
		jb	short loc_BBF
		jmp	short loc_BE6
; ---------------------------------------------------------------------------

loc_BE3:				; CODE XREF: sub_B9A+12j
		mov	rbx, rsi

loc_BE6:				; CODE XREF: sub_B9A+31j sub_B9A+36j ...
		mov	byte ptr [r12+rbx], 0
		mov	rax, rbx
		pop	rbx
		pop	rbp
		pop	r12
		pop	r13
		pop	r14
		retn
sub_B9A		endp


; =============== S U B	R O U T	I N E =======================================


sub_BF7		proc near		; CODE XREF: sub_C46:loc_CCAp
		sub	rsp, 8
		lea	rdi, a1GetLibcAddres ; "1) Get libc address"
		call	_puts
		lea	rdi, a2GetAddressOfA ; "2) Get address of a libc function"
		call	_puts
		lea	rdi, a3NomNomR0pBuff ; "3) Nom nom r0p buffer to stack"
		call	_puts
		lea	rdi, a4Exit	; "4) Exit"
		call	_puts
		lea	rsi, aEnterSymbol+0Ch
		mov	edi, 1
		mov	eax, 0
		call	___printf_chk
		add	rsp, 8
		retn
sub_BF7		endp


; =============== S U B	R O U T	I N E =======================================

; Attributes: bp-based frame

sub_C46		proc near		; DATA XREF: start+1Do

handle		= qword	ptr -448h
nptr		= byte ptr -440h

		push	rbp
		mov	rbp, rsp
		push	r15
		push	r14
		push	r13
		push	r12
		push	rbx
		sub	rsp, 428h
		mov	ecx, 0		; n
		mov	edx, 2		; modes
		mov	esi, 0		; buf
		mov	rax, cs:stdout_ptr
		mov	rdi, [rax]	; stream
		call	_setvbuf
		lea	rsi, handler	; handler
		mov	edi, 0Eh	; sig
		call	_signal
		mov	edi, 3Ch	; seconds
		call	_alarm
		lea	rdi, aWelcomeToAnEas ; "\nWelcome to an	easy Return Oriented Pr"...
		call	_puts
		lea	rdi, aMenu	; "Menu:"
		call	_puts
		mov	esi, 1		; mode
		lea	rdi, file	; "libc.so.6"
		call	_dlopen
		mov	[rbp+handle], rax
		lea	rbx, [rbp+nptr]

loc_CCA:				; CODE XREF: sub_C46+10Cj sub_C46+145j ...
		call	sub_BF7
		mov	esi, 400h
		mov	rdi, rbx
		call	sub_B9A
		test	rax, rax
		jnz	short loc_CF2
		lea	rdi, aBadChoice_ ; "Bad	choice."
		call	_puts
		jmp	loc_E9D
; ---------------------------------------------------------------------------

loc_CF2:				; CODE XREF: sub_C46+99j
		mov	edx, 0Ah	; base
		mov	esi, 0		; endptr
		mov	rdi, rbx	; nptr
		call	_strtol
		cmp	eax, 2
		jz	short loc_D57
		cmp	eax, 2
		jg	short loc_D18
		cmp	eax, 1
		jz	short loc_D35
		jmp	loc_E69
; ---------------------------------------------------------------------------

loc_D18:				; CODE XREF: sub_C46+C6j
		cmp	eax, 3
		nop	dword ptr [rax+rax+00h]
		jz	loc_DC0
		cmp	eax, 4
		jz	loc_E7A
		nop
		jmp	loc_E69
; ---------------------------------------------------------------------------

loc_D35:				; CODE XREF: sub_C46+CBj
		mov	rdx, [rbp+handle]
		lea	rsi, aLibc_so_60x016 ; "libc.so.6: 0x%016llX\n"
		mov	edi, 1
		mov	eax, 0
		call	___printf_chk
		jmp	loc_CCA
; ---------------------------------------------------------------------------

loc_D57:				; CODE XREF: sub_C46+C1j
		lea	rsi, aEnterSymbol ; "Enter symbol: "
		mov	edi, 1
		mov	eax, 0
		call	___printf_chk
		mov	esi, 40h
		mov	rdi, rbx
		call	sub_B9A
		test	rax, rax
		jnz	short loc_D90
		lea	rdi, aBadSymbol_ ; "Bad	symbol."
		call	_puts
		jmp	loc_CCA
; ---------------------------------------------------------------------------

loc_D90:				; CODE XREF: sub_C46+137j
		mov	rsi, rbx	; name
		mov	rdi, [rbp+handle] ; handle
		call	_dlsym
		mov	rcx, rax
		mov	rdx, rbx
		lea	rsi, aSymbolS0x016ll ; "Symbol %s: 0x%016llX\n"
		mov	edi, 1
		mov	eax, 0
		call	___printf_chk
		jmp	loc_CCA
; ---------------------------------------------------------------------------

loc_DC0:				; CODE XREF: sub_C46+DAj
		lea	rsi, aEnterBytesToSe ; "Enter bytes to send (max 1024):	"
		mov	edi, 1
		mov	eax, 0
		call	___printf_chk
		mov	esi, 400h
		mov	rdi, rbx
		call	sub_B9A
		mov	edx, 0Ah	; base
		mov	esi, 0		; endptr
		mov	rdi, rbx	; nptr
		call	_strtol
		movsxd	r14, eax
		lea	rax, [r14-1]
		cmp	rax, 3FFh
		ja	short loc_E58
		test	r14, r14
		jz	short loc_E3F
		mov	r13d, 0
		mov	r12d, 0
		mov	r15, cs:stdin_ptr

loc_E1C:				; CODE XREF: sub_C46+1F5j
		mov	rdi, [r15]	; fp
		call	__IO_getc
		cmp	eax, 0FFFFFFFFh
		jz	short loc_E94
		mov	[rbp+r12+nptr],	al
		add	r13d, 1
		movsxd	r12, r13d
		cmp	r14, r12
		ja	short loc_E1C
		jmp	short loc_E45
; ---------------------------------------------------------------------------

loc_E3F:				; CODE XREF: sub_C46+1C1j
		mov	r12d, 0

loc_E45:				; CODE XREF: sub_C46+1F7j sub_C46+255j
		mov	rdx, r12	; n
		mov	rsi, rbx	; src
		mov	rdi, rbp	; dest
		call	_memcpy
		jmp	loc_CCA
; ---------------------------------------------------------------------------

loc_E58:				; CODE XREF: sub_C46+1BCj
		lea	rdi, aInvalidAmount_ ; "Invalid	amount."
		call	_puts
		jmp	loc_CCA
; ---------------------------------------------------------------------------

loc_E69:				; CODE XREF: sub_C46+CDj sub_C46+EAj
		lea	rdi, aBadChoice_ ; "Bad	choice."
		call	_puts
		jmp	loc_CCA
; ---------------------------------------------------------------------------

loc_E7A:				; CODE XREF: sub_C46+E3j
		mov	rdi, [rbp+handle] ; handle
		call	_dlclose
		lea	rdi, aExiting_	; "Exiting."
		call	_puts
		jmp	short loc_E9D
; ---------------------------------------------------------------------------

loc_E94:				; CODE XREF: sub_C46+1E1j
		lea	r12d, [r13+1]
		movsxd	r12, r12d
		jmp	short loc_E45
; ---------------------------------------------------------------------------

loc_E9D:				; CODE XREF: sub_C46+A7j sub_C46+24Cj
		mov	eax, 0
		add	rsp, 428h
		pop	rbx
		pop	r12
		pop	r13
		pop	r14
		pop	r15
		pop	rbp
		retn
sub_C46		endp

; ---------------------------------------------------------------------------
		align 20h

; =============== S U B	R O U T	I N E =======================================


sub_EC0		proc near		; DATA XREF: start+16o
		push	r15
		mov	r15d, edi
		push	r14
		mov	r14, rsi
		push	r13
		mov	r13, rdx
		push	r12
		lea	r12, off_201DD0
		push	rbp
		lea	rbp, off_201DD8
		push	rbx
		sub	rbp, r12
		xor	ebx, ebx
		sar	rbp, 3
		sub	rsp, 8
		call	_init_proc
		test	rbp, rbp
		jz	short loc_F16
		nop	dword ptr [rax+rax+00000000h]

loc_F00:				; CODE XREF: sub_EC0+54j
		mov	rdx, r13
		mov	rsi, r14
		mov	edi, r15d
		call	qword ptr [r12+rbx*8]
		add	rbx, 1
		cmp	rbx, rbp
		jnz	short loc_F00

loc_F16:				; CODE XREF: sub_EC0+36j
		add	rsp, 8
		pop	rbx
		pop	rbp
		pop	r12
		pop	r13
		pop	r14
		pop	r15
		retn
sub_EC0		endp

; ---------------------------------------------------------------------------
		align 10h
; [00000002 BYTES: COLLAPSED FUNCTION nullsub_1. PRESS KEYPAD CTRL-"+" TO EXPAND]
; ===========================================================================

; Segment type:	Pure code
; Segment permissions: Read/Execute
_fini		segment	dword public 'CODE' use64
		assume cs:_fini
		;org 0F34h
		assume es:nothing, ss:nothing, ds:_data, fs:nothing, gs:nothing

; =============== S U B	R O U T	I N E =======================================


		public _term_proc
_term_proc	proc near
		sub	rsp, 8
		add	rsp, 8
		retn
_term_proc	endp

_fini		ends

; ===========================================================================

; Segment type:	Pure data
; Segment permissions: Read
; Segment alignment 'qword' can not be represented in assembly
_rodata		segment	para public 'CONST' use64
		assume cs:_rodata
		;org 0F40h
		db    1
		db    0
		db    2
		db    0
; char s[]
s		db 'Connection timeout, closing.',0 ; DATA XREF: handler+4o
; char a1GetLibcAddres[]
a1GetLibcAddres	db '1) Get libc address',0 ; DATA XREF: sub_BF7+4o
; char a4Exit[]
a4Exit		db '4) Exit',0          ; DATA XREF: sub_BF7+28o
; char aMenu[]
aMenu		db 'Menu:',0            ; DATA XREF: sub_C46+59o
; char file[]
file		db 'libc.so.6',0        ; DATA XREF: sub_C46+6Ao
; char aBadChoice_[]
aBadChoice_	db 'Bad choice.',0      ; DATA XREF: sub_C46+9Bo
					; sub_C46:loc_E69o
aLibc_so_60x016	db 'libc.so.6: 0x%016llX',0Ah,0 ; DATA XREF: sub_C46+F6o
aEnterSymbol	db 'Enter symbol: ',0   ; DATA XREF: sub_C46:loc_D57o
					; sub_BF7+34o
; char aBadSymbol_[]
aBadSymbol_	db 'Bad symbol.',0      ; DATA XREF: sub_C46+139o
aSymbolS0x016ll	db 'Symbol %s: 0x%016llX',0Ah,0 ; DATA XREF: sub_C46+15Fo
; char aInvalidAmount_[]
aInvalidAmount_	db 'Invalid amount.',0  ; DATA XREF: sub_C46:loc_E58o
; char aExiting_[]
aExiting_	db 'Exiting.',0         ; DATA XREF: sub_C46+240o
		align 20h
; char a2GetAddressOfA[]
a2GetAddressOfA	db '2) Get address of a libc function',0 ; DATA XREF: sub_BF7+10o
		align 8
; char a3NomNomR0pBuff[]
a3NomNomR0pBuff	db '3) Nom nom r0p buffer to stack',0 ; DATA XREF: sub_BF7+1Co
		align 8
; char aWelcomeToAnEas[]
aWelcomeToAnEas	db 0Ah			; DATA XREF: sub_C46+4Do
		db 'Welcome to an easy Return Oriented Programming challenge...',0
		align 8
aEnterBytesToSe	db 'Enter bytes to send (max 1024): ',0 ; DATA XREF: sub_C46:loc_DC0o
		align 10h
_rodata		ends

; ===========================================================================

; Segment type:	Pure data
; Segment permissions: Read
_eh_frame_hdr	segment	dword public 'CONST' use64
		assume cs:_eh_frame_hdr
		;org 10B0h
		db    1
		db  1Bh
		db    3
		db  3Bh	; ;
		db  4Ch	; L
		db    0
		db    0
		db    0
		db    8
		db    0
		db    0
		db    0
		db 0B0h	; °
		db 0F8h	; ø
		db 0FFh
		db 0FFh
		db  98h	; ˜
		db    0
		db    0
		db    0
		db 0B0h	; °
		db 0F9h	; ù
		db 0FFh
		db 0FFh
		db  68h	; h
		db    0
		db    0
		db    0
		db 0D0h	; Ð
		db 0FAh	; ú
		db 0FFh
		db 0FFh
		db 0C0h	; À
		db    0
		db    0
		db    0
		db 0EAh	; ê
		db 0FAh	; ú
		db 0FFh
		db 0FFh
		db 0D8h	; Ø
		db    0
		db    0
		db    0
		db  47h	; G
		db 0FBh	; û
		db 0FFh
		db 0FFh
		db  18h
		db    1
		db    0
		db    0
		db  96h	; –
		db 0FBh	; û
		db 0FFh
		db 0FFh
		db  30h	; 0
		db    1
		db    0
		db    0
		db  10h
		db 0FEh	; þ
		db 0FFh
		db 0FFh
		db  60h	; `
		db    1
		db    0
		db    0
		db  80h	; €
		db 0FEh	; þ
		db 0FFh
		db 0FFh
		db 0A8h	; ¨
		db    1
		db    0
		db    0
_eh_frame_hdr	ends

; ===========================================================================

; Segment type:	Pure data
; Segment permissions: Read
; Segment alignment 'qword' can not be represented in assembly
_eh_frame	segment	para public 'CONST' use64
		assume cs:_eh_frame
		;org 1100h
		db  14h
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    1
		db  7Ah	; z
		db  52h	; R
		db    0
		db    1
		db  78h	; x
		db  10h
		db    1
		db  1Bh
		db  0Ch
		db    7
		db    8
		db  90h	; 
		db    1
		db    7
		db  10h
		db  14h
		db    0
		db    0
		db    0
		db  1Ch
		db    0
		db    0
		db    0
		db  40h	; @
		db 0F9h	; ù
		db 0FFh
		db 0FFh
		db  2Ah	; *
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db  14h
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    1
		db  7Ah	; z
		db  52h	; R
		db    0
		db    1
		db  78h	; x
		db  10h
		db    1
		db  1Bh
		db  0Ch
		db    7
		db    8
		db  90h	; 
		db    1
		db    0
		db    0
		db  24h	; $
		db    0
		db    0
		db    0
		db  1Ch
		db    0
		db    0
		db    0
		db  10h
		db 0F8h	; ø
		db 0FFh
		db 0FFh
		db    0
		db    1
		db    0
		db    0
		db    0
		db  0Eh
		db  10h
		db  46h	; F
		db  0Eh
		db  18h
		db  4Ah	; J
		db  0Fh
		db  0Bh
		db  77h	; w
		db    8
		db  80h	; €
		db    0
		db  3Fh	; ?
		db  1Ah
		db  3Bh	; ;
		db  2Ah	; *
		db  33h	; 3
		db  24h	; $
		db  22h	; "
		db    0
		db    0
		db    0
		db    0
		db  14h
		db    0
		db    0
		db    0
		db  44h	; D
		db    0
		db    0
		db    0
		db    8
		db 0FAh	; ú
		db 0FFh
		db 0FFh
		db  1Ah
		db    0
		db    0
		db    0
		db    0
		db  44h	; D
		db  0Eh
		db  10h
		db    0
		db    0
		db    0
		db    0
		db  3Ch	; <
		db    0
		db    0
		db    0
		db  5Ch	; \
		db    0
		db    0
		db    0
		db  0Ah
		db 0FAh	; ú
		db 0FFh
		db 0FFh
		db  5Dh	; ]
		db    0
		db    0
		db    0
		db    0
		db  42h	; B
		db  0Eh
		db  10h
		db  8Eh	; Ž
		db    2
		db  42h	; B
		db  0Eh
		db  18h
		db  8Dh	; 
		db    3
		db  42h	; B
		db  0Eh
		db  20h
		db  8Ch	; Œ
		db    4
		db  41h	; A
		db  0Eh
		db  28h	; (
		db  86h	; †
		db    5
		db  41h	; A
		db  0Eh
		db  30h	; 0
		db  83h	; ƒ
		db    6
		db    2
		db  4Dh	; M
		db  0Eh
		db  28h	; (
		db  41h	; A
		db  0Eh
		db  20h
		db  42h	; B
		db  0Eh
		db  18h
		db  42h	; B
		db  0Eh
		db  10h
		db  42h	; B
		db  0Eh
		db    8
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db  14h
		db    0
		db    0
		db    0
		db  9Ch	; œ
		db    0
		db    0
		db    0
		db  27h	; '
		db 0FAh	; ú
		db 0FFh
		db 0FFh
		db  4Fh	; O
		db    0
		db    0
		db    0
		db    0
		db  44h	; D
		db  0Eh
		db  10h
		db    2
		db  4Ah	; J
		db  0Eh
		db    8
		db  2Ch	; ,
		db    0
		db    0
		db    0
		db 0B4h	; ´
		db    0
		db    0
		db    0
		db  5Eh	; ^
		db 0FAh	; ú
		db 0FFh
		db 0FFh
		db  6Eh	; n
		db    2
		db    0
		db    0
		db    0
		db  41h	; A
		db  0Eh
		db  10h
		db  86h	; †
		db    2
		db  43h	; C
		db  0Dh
		db    6
		db  50h	; P
		db  8Fh	; 
		db    3
		db  8Eh	; Ž
		db    4
		db  8Dh	; 
		db    5
		db  8Ch	; Œ
		db    6
		db  83h	; ƒ
		db    7
		db    3
		db  59h	; Y
		db    2
		db  0Ch
		db    7
		db    8
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db  44h	; D
		db    0
		db    0
		db    0
		db 0E4h	; ä
		db    0
		db    0
		db    0
		db 0A8h	; ¨
		db 0FCh	; ü
		db 0FFh
		db 0FFh
		db  65h	; e
		db    0
		db    0
		db    0
		db    0
		db  42h	; B
		db  0Eh
		db  10h
		db  8Fh	; 
		db    2
		db  45h	; E
		db  0Eh
		db  18h
		db  8Eh	; Ž
		db    3
		db  45h	; E
		db  0Eh
		db  20h
		db  8Dh	; 
		db    4
		db  45h	; E
		db  0Eh
		db  28h	; (
		db  8Ch	; Œ
		db    5
		db  48h	; H
		db  0Eh
		db  30h	; 0
		db  86h	; †
		db    6
		db  48h	; H
		db  0Eh
		db  38h	; 8
		db  83h	; ƒ
		db    7
		db  4Dh	; M
		db  0Eh
		db  40h	; @
		db  6Ch	; l
		db  0Eh
		db  38h	; 8
		db  41h	; A
		db  0Eh
		db  30h	; 0
		db  41h	; A
		db  0Eh
		db  28h	; (
		db  42h	; B
		db  0Eh
		db  20h
		db  42h	; B
		db  0Eh
		db  18h
		db  42h	; B
		db  0Eh
		db  10h
		db  42h	; B
		db  0Eh
		db    8
		db    0
		db  14h
		db    0
		db    0
		db    0
		db  2Ch	; ,
		db    1
		db    0
		db    0
		db 0D0h	; Ð
		db 0FCh	; ü
		db 0FFh
		db 0FFh
		db    2
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
_eh_frame	ends

; ===========================================================================

; Segment type:	Pure data
; Segment permissions: Read/Write
; Segment alignment 'qword' can not be represented in assembly
_init_array	segment	para public 'DATA' use64
		assume cs:_init_array
		;org 201DD0h
off_201DD0	dq offset sub_B40	; DATA XREF: sub_EC0+11o
_init_array	ends

; ===========================================================================

; Segment type:	Pure data
; Segment permissions: Read/Write
; Segment alignment 'qword' can not be represented in assembly
_fini_array	segment	para public 'DATA' use64
		assume cs:_fini_array
		;org 201DD8h
off_201DD8	dq offset sub_B00	; DATA XREF: sub_EC0+19o
_fini_array	ends

; ===========================================================================

; Segment type:	Pure data
; Segment permissions: Read/Write
; Segment alignment 'qword' can not be represented in assembly
_jcr		segment	para public 'DATA' use64
		assume cs:_jcr
		;org 201DE0h
qword_201DE0	dq 0			; DATA XREF: sub_B40r sub_B40+17o
_jcr		ends

; ===========================================================================

; Segment type:	Pure data
; Segment permissions: Read/Write
; Segment alignment 'qword' can not be represented in assembly
_got		segment	para public 'DATA' use64
		assume cs:_got
		;org 201FC8h
_ITM_deregisterTMCloneTable_ptr	dq offset _ITM_deregisterTMCloneTable
					; DATA XREF: sub_A90:loc_AADr
stdout_ptr	dq offset stdout	; DATA XREF: sub_C46+23r
stdin_ptr	dq offset stdin		; DATA XREF: sub_B9A+1Er sub_C46+1CFr
__gmon_start___ptr dq offset __gmon_start__ ; DATA XREF: _init_proc+4r
_Jv_RegisterClasses_ptr	dq offset _Jv_RegisterClasses ;	DATA XREF: sub_B40+Ar
_ITM_registerTMCloneTable_ptr dq offset	_ITM_registerTMCloneTable
					; DATA XREF: sub_B40:loc_AEAr
__cxa_finalize_ptr dq offset __cxa_finalize ; DATA XREF: sub_B00+9r
_got		ends

; ===========================================================================

; Segment type:	Pure data
; Segment permissions: Read/Write
; Segment alignment 'qword' can not be represented in assembly
_got_plt	segment	para public 'DATA' use64
		assume cs:_got_plt
		;org 202000h
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
off_202018	dq offset puts		; DATA XREF: _putsr
off_202020	dq offset alarm		; DATA XREF: _alarmr
off_202028	dq offset __libc_start_main ; DATA XREF: ___libc_start_mainr
off_202030	dq offset signal	; DATA XREF: _signalr
off_202038	dq offset __gmon_start__ ; DATA	XREF: ___gmon_start__r
off_202040	dq offset strtol	; DATA XREF: _strtolr
off_202048	dq offset memcpy	; DATA XREF: _memcpyr
off_202050	dq offset dlopen	; DATA XREF: _dlopenr
off_202058	dq offset _IO_getc	; DATA XREF: __IO_getcr
off_202060	dq offset dlclose	; DATA XREF: _dlcloser
off_202068	dq offset __printf_chk	; DATA XREF: ___printf_chkr
off_202070	dq offset setvbuf	; DATA XREF: _setvbufr
off_202078	dq offset exit		; DATA XREF: _exitr
off_202080	dq offset dlsym		; DATA XREF: _dlsymr
off_202088	dq offset __cxa_finalize ; DATA	XREF: ___cxa_finalizer
_got_plt	ends

; ===========================================================================

; Segment type:	Pure data
; Segment permissions: Read/Write
; Segment alignment 'qword' can not be represented in assembly
_data		segment	para public 'DATA' use64
		assume cs:_data
		;org 202090h
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
		db    0
off_202098	dq offset off_202098	; DATA XREF: sub_B00+17r
					; .data:off_202098o
_data		ends

; ===========================================================================

; Segment type:	Uninitialized
; Segment permissions: Read/Write
_bss		segment	byte public 'BSS' use64
		assume cs:_bss
		;org 2020A0h
		assume es:nothing, ss:nothing, ds:_data, fs:nothing, gs:nothing
		public _edata
_edata		db ?			; DATA XREF: sub_A90+7o
					; sub_B40:loc_AC0o ...
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
		db    ?	;
unk_2020A7	db    ?	;		; DATA XREF: sub_A90o
_bss		ends

; ===========================================================================

; Segment type:	Externs
; extern
; struct _IO_FILE *stdout
		extrn stdout		; DATA XREF: .got:stdout_ptro
; int puts(const char *s)
		extrn puts:near		; DATA XREF: .got.plt:off_202018o
; struct _IO_FILE *stdin
		extrn stdin		; DATA XREF: .got:stdin_ptro
; unsigned int alarm(unsigned int seconds)
		extrn alarm:near	; DATA XREF: .got.plt:off_202020o
		extrn __libc_start_main:near ; DATA XREF: .got.plt:off_202028o
; __sighandler_t signal(int sig, __sighandler_t	handler)
		extrn signal:near	; DATA XREF: .got.plt:off_202030o
; __int32 strtol(const char *nptr, char	**endptr, int base)
		extrn strtol:near	; DATA XREF: .got.plt:off_202040o
; void *memcpy(void *dest, const void *src, size_t n)
		extrn memcpy:near	; DATA XREF: .got.plt:off_202048o
; void *dlopen(const char *file, int mode)
		extrn dlopen:near	; DATA XREF: .got.plt:off_202050o
; int IO_getc(_IO_FILE *fp)
		extrn _IO_getc:near	; DATA XREF: .got.plt:off_202058o
; int dlclose(void *handle)
		extrn dlclose:near	; DATA XREF: .got.plt:off_202060o
		extrn __printf_chk:near	; DATA XREF: .got.plt:off_202068o
; int setvbuf(FILE *stream, char *buf, int modes, size_t n)
		extrn setvbuf:near	; DATA XREF: .got.plt:off_202070o
; void exit(int	status)
		extrn exit:near		; DATA XREF: .got.plt:off_202078o
; void *dlsym(void *handle, const char *name)
		extrn dlsym:near	; DATA XREF: .got.plt:off_202080o
		extrn __cxa_finalize:near ; weak ; DATA	XREF: .got:__cxa_finalize_ptro
					; .got.plt:off_202088o
		extrn _ITM_deregisterTMCloneTable ; weak
					; DATA XREF: .got:_ITM_deregisterTMCloneTable_ptro
		extrn __gmon_start__ ; weak ; DATA XREF: .got:__gmon_start___ptro
					; .got.plt:off_202038o
		extrn _Jv_RegisterClasses:near ; weak ;	CODE XREF: sub_B40+21p
					; DATA XREF: .got:_Jv_RegisterClasses_ptro
		extrn _ITM_registerTMCloneTable	; weak
					; DATA XREF: .got:_ITM_registerTMCloneTable_ptro


		end start
