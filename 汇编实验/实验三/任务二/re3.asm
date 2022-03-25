.386
.model flat, c
option casemap:none
extrn printf: near
extrn scanf: near
extrn strncmp: near
public FUNC1
public FUNC2
public FUNC3
public FUNC4
public FUNC5

includelib  user32.lib
includelib  kernel32.lib

goodStruct struct
	good_name	DB	10 dup(0)
	good_len	DB	0
	good_sale	DW	10
	good_in_price	DW	?
	good_out_price	DW	?
	good_all_count	DW	?
	good_sale_count	DW	?
	good_recommand	DW	?
	good_sort		DW	1
goodStruct ends

.DATA	 
	N		EQU	30 					;number

	numOfBag	EQU		1000

	ga1		goodStruct	<'PEN', 3, 10, 35, 56, 70, 25, ?>
	ga2		goodStruct	<'BOOK', 4, 9, 12, 30, 25, 5, ?>
	goodStruct	N-2	dup(<'EARASER', 3, 7, 35, 56, 70, 25, ?>)

	checkname	DB	'Tell me what you want:','0'
    in_name db 15 dup(0)
	notFound	DB	'NOT FOUND!TRY AGAIN!', 0ah, 0dh, '0'
	ui_query_failed DB 'NOT FOUND!TRY AGAIN!', '0'
	outenter	DB	0ah, 0dh, 0

    errorInputMsg DB ' Error!', 0ah, 0dh, 0

    io_1 db 'NAME: ',0
	io_2 db 'SALE: ',0
	io_3 db 'IN_PRICE: ',0
	io_4 db 'OUT_PRICE: ',0
	io_5 db 'ALL_ACCOUNT: ',0
	io_6 db 'SALE_ACCOUNT: ',0
	io_7 db 'COMMOND: ',0
	io_8 db 'good_sort is: ',0

    BUF1 db 10, ?, 10 dup(0)
	bufF2T10 db 12 dup(0)
	DAT DW 0AH
	SIGN DB ?
	fmt db '%10s',0
	formatout db "%hd", 10, 0 ;
	formatin db "%hd",0
	putc db ">>",0
.STACK	200

.CODE	

gets macro of:req
    push ebx
    lea ebx, of
	push ebx
	push dword ptr offset formatin 
	call scanf
	add  esp, 8
	pop ebx
endm

puts macro of:req
    push dword ptr offset of 
	call printf
	add  esp, 4 
endm

puts_no macro of:req
    push dword ptr  of 
	call printf
	add  esp, 4 
endm

putchar macro 
	puts putc
endm

puts_nu macro of:req
	push bx
    mov bx, word ptr of
	push bx
	push dword ptr offset formatout 
	call printf
	add  esp, 6 
	pop bx
endm

CRLF macro
	puts outenter
endm

scmp macro one:req, anthor:req
	push dword ptr 8
    push dword ptr one
	push dword ptr offset anthor
	call strncmp
	add esp, 12
endm

; esi good addr
outone proc near
	push eax
	push ebx
	push dx

	mov dx, 16
L6:
	puts io_1
	lea ebx, [esi].good_name
	puts_no ebx
	CRLF
	puts io_2
	puts_nu [esi].good_sale
	puts io_3
	puts_nu [esi].good_in_price
	puts io_4
	puts_nu [esi].good_out_price
	puts io_5
	puts_nu [esi].good_all_count
	puts io_6
	puts_nu [esi].good_sale_count
	puts io_7
	puts_nu [esi].good_recommand
	puts io_8
	puts_nu [esi].good_sort
	
	pop dx
	pop ebx
	pop eax
	ret
outone endp

FUNC1 PROC near
que:
	puts checkname
	push dword ptr offset in_name
	push dword ptr offset fmt
	call scanf
	add esp, 8
	lea esi, ga1
	mov bp, N
query_loop:
	lea ebx, [esi].good_name
	scmp ebx, in_name
	cmp eax, 0
	jz query_find
	add esi, sizeof goodStruct
	dec bp
	jnz query_loop
query_not_find:
	puts ui_query_failed
	jmp que	
query_find:
	call outone
	ret
FUNC1 ENDP

;di good addr
FUNC2 proc 
cha_que:
	puts checkname
	push dword ptr offset in_name
	push dword ptr offset fmt
	call scanf
	add esp, 8
	lea esi, ga1
	mov bp, N
cha_query_loop:
	lea ebx, [esi].good_name
	scmp ebx, in_name
	cmp eax, 0
	jz cha_query_find
	add esi, sizeof goodStruct
	dec bp
	jnz cha_query_loop
cha_query_not_find:
	puts ui_query_failed
	jmp cha_que	
cha_query_find:
	puts io_2
	puts_nu [esi].good_sale
	putchar
	gets [esi].good_sale
	puts io_3
	puts_nu [esi].good_in_price
	putchar
	gets [esi].good_in_price
	puts io_4
	puts_nu [esi].good_out_price
	putchar
	gets [esi].good_out_price
	puts io_5
	puts_nu [esi].good_all_count
	putchar
	gets [esi].good_all_count
	ret
FUNC2 endp

FUNC3 proc
	mov bp, N ;bp is iterator
	mov esi, offset ga1 ;si is commodity

calc_pro:
	mov ax, [esi].good_in_price
	mov bx, 1280
	xor dx,dx
	MUL bx

	mov bx, [esi].good_out_price
	mov cx, [esi].good_sale
	imul bx, cx
	div bx
	mov cx, ax

	mov ax, [esi].good_sale_count
	sal ax, 6
	
	mov bx, [esi].good_all_count
	xor dx, dx
	div bx
	add ax, cx
	mov word ptr[esi].good_recommand, ax

	add esi, sizeof goodStruct
	dec bp 
	jnz calc_pro
	ret
FUNC3 endp

;ax good sum, si good addr
FUNC4 proc 
	push ebx
	push cx
	push dx
	mov ax, N
	mov esi, offset ga1 ;si is commodity
	jmp L3
L4:	
	dec ax
	add esi, sizeof goodStruct
	cmp ax, 1
	je exit
L3:
	mov dx, [esi].good_recommand
	mov ebx, esi
	mov cx, ax
L5:	
	add ebx, sizeof goodStruct
	dec cx
	cmp dx, [ebx].good_recommand
	ja	L1 
	jb	L2
next:   
	cmp cx, 1
	je L4
	jmp L5
L1:	
	inc [ebx].good_sort
	jmp next
L2:
	inc [esi].good_sort
	jmp next
exit:
	pop dx
	pop cx
	pop ebx
	ret
FUNC4 endp

;;ax good sum, si good addr
FUNC5 proc
	mov ax, N
	mov esi, offset ga1 ;si is commodity
L7:
	call outone
	add esi, sizeof goodStruct
	dec ax
	jne L7
	ret
FUNC5 endp

END
