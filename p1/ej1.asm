segment .data
	err_div0 db "Error: dividing by 0",0
	err_ioutrange db"Error: index out of bounds",0
segment .bss
	__esp resd 1
	_x resd 1
	_y resd 1
	_z resd 1
segment .text
	global main
	extern scan_int, print_int, scan_float, print_float, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
	extern alfa_malloc, alfa_free, ld_float
main:
	mov dword [__esp], dword esp
	mov dword eax, 8
	push dword eax
	pop dword eax
	mov dword [_x], eax
	push dword _y
	call scan_int
	add esp, 4
	mov dword eax, _x
	push dword eax
	mov dword eax, _y
	push dword eax
	pop dword eax
	mov dword eax, [eax]
	pop dword ebx
	mov dword ebx, [ebx]
	add eax, ebx
	push dword eax
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	jmp endofcode
etiq_div0:
	push dword err_div0
	call print_string
	add esp, 4
	call print_endofline
etiq_ibounds:
	push dword err_ioutrange
	call print_string
	add esp, 4
	call print_endofline
endofcode:
	mov dword esp, [__esp]
	ret
