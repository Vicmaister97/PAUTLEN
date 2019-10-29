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
segment .text
	global main
	;habilitar funciones de alfalib
	extern scan_int, scan_boolean
	extern print_int, print_boolean, print_string, print_blank, print_endofline
	;codigo correspondiente a la compilacion del no terminal "funciones" 
	;
main:
	mov dword [__esp], esp
	push dword 8
	call print_int
	add esp, 4
	call print_endofline
	pop dword eax
	mov dword [_x] , eax 
	push dword [_x]
	call print_int
	add esp, 4
	call print_endofline
	push dword _y
	call scan_int
	add esp, 4
	push dword [_y]
	call print_int
	add esp, 4
	call print_endofline
	push dword [_x]
	call print_int
	add esp, 4
	call print_endofline
	push dword [_y]
	call print_int
	add esp, 4
	call print_endofline
	pop dword ebx
	mov ebx, [ebx]
	pop dword eax
	mov eax, [eax]
	add eax, ebx
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	pop dword eax
	mov dword [_z] , eax 
	push dword [_z]
	call print_int
	add esp, 4
	call print_endofline
	push dword [_z]
	call print_int
	add esp, 4
	call print_endofline
	pop dword eax
	mov eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	push dword 7
	call print_int
	add esp, 4
	call print_endofline
	push dword [_y]
	call print_int
	add esp, 4
	call print_endofline
	pop dword ebx
	mov ebx, [ebx]
	pop dword eax
	add eax, ebx
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	pop dword eax
	mov dword [_z] , eax 
	push dword [_z]
	call print_int
	add esp, 4
	call print_endofline
	push dword [_z]
	call print_int
	add esp, 4
	call print_endofline
	pop dword eax
	mov eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
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
fin:ret
