segment .data
	;guardamos posicion pila
segment .bss
	pila resd 1
	;declaracion de variables sin inicializar
	;
segment .text
	global main
	;habilitar funciones de alfalib
	extern scan_int, scan_boolean
	extern print_int, print_boolean, print_string, print_blank, print_endofline
main:
	mov dword [pila], esp
	push dword 6
	push dword 5
	pop dword eax
	pop dword ebx
	add eax, ebx
	mov ecx, 0
	cmp eax, 10
	jle fin_if_0
	mov ecx, 1
fin_if_0:
	push dword ecx
	call print_int
	add esp, 4
	call print_endofline
	push dword 5
	push dword 3
	pop dword eax
	pop dword ebx
	add eax, ebx
	mov ecx, 0
	cmp eax, 10
	jle fin_if_1
	mov ecx, 1
fin_if_1:
	push dword ecx
	call print_int
	add esp, 4
	call print_endofline
	push dword 5
	push dword 3
	pop dword ebx
	pop dword eax
	sub eax, ebx
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	push dword 2
	push dword 7
	pop dword ebx
	pop dword eax
	imul ebx
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	mov dword esp, [pila]
	ret
