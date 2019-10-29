segment .data
	;declaracion de variables inicializadas
	;
	mensaje_1 db "División por cero", 0
	mensaje_2 db "Indice fuera de rango", 0
segment .bss
	;declaracion de variables sin inicializar
	;
	__esp resd 1
	_x resd 1
	_y resd 1
	_z resd 1
	_j resd 1
segment .text
	global main
	;habilitar funciones de alfalib
	extern scan_int, scan_boolean
	extern print_int, print_boolean, print_string, print_blank, print_endofline
	;codigo correspondiente a la compilacion del no terminal "funciones" 
	;
main:
	mov dword [__esp], esp
	push dword _x
	call scan_int
	add esp, 4
	push dword _z
	call scan_int
	add esp, 4
	mov dword eax, _x
	push dword eax
	pop dword eax
	mov dword eax, [eax]
	neg eax
	push dword eax
	pop dword eax
	mov dword [_j], eax 
	mov dword eax, _j
	push dword eax
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, _z
	push dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	mov dword eax, [eax]
	sub eax, ebx
	push dword eax
	pop dword eax
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 2
	push dword eax
	pop dword ecx
	cmp ecx, 0
	je error_1
	pop dword eax
	mov dword eax, [eax]
	cdq
	idiv ecx
	push dword eax
	pop dword eax
	mov dword [_y], eax 
	mov dword eax, _y
	push dword eax
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, _y
	push dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	mov dword eax, [eax]
	imul ebx
	push dword eax
	pop dword eax
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	jmp fin
error_1:
	push dword mensaje_1
	call print_string
	add esp, 4
	mov dword esp, [__esp]
	call print_endofline
	jmp fin
error_2:
	push dword mensaje_2
	call print_string
	add esp, 4
	mov dword esp, [__esp]
	call print_endofline
	jmp fin
fin:
	mov dword esp, [__esp]
	ret
