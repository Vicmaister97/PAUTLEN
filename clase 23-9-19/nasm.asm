segment .data
	;guardamos posicion pila
	mensaje_1 db "División por cero", 0
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
	push dword 8
	push dword 2
	pop dword ecx
	cmp ecx, 0
	je error_1
	pop dword eax
	cdq
	idiv ecx
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	push dword 5
	push dword 2
	pop dword ecx
	cmp ecx, 0
	je error_1
	pop dword eax
	cdq
	idiv ecx
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	push dword 5
	push dword 0
	pop dword ecx
	cmp ecx, 0
	je error_1
	pop dword eax
	cdq
	idiv ecx
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
error_1:
	push dword mensaje_1
	call print_string
	add esp, 4
	call print_endofline
fin:
	mov dword esp, [pila]
	ret
