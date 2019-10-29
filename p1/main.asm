segment .data
	;declaracion de variables inicializadas
	;
	mensaje_1 db "División por cero", 0
	mensaje_2 db "Indice fuera de rango", 0
segment .bss
	;declaracion de variables sin inicializar
	;
	__esp resd 1
	_m resd 1
segment .text
	global main
	;habilitar funciones de alfalib
	extern scan_int, scan_boolean
	extern print_int, print_boolean, print_string, print_blank, print_endofline
	;codigo correspondiente a la compilacion del no terminal "funciones" 
	;
main:
	mov dword [__esp], esp
	mov dword eax, 0
	push dword eax
	pop dword eax
	mov dword [_m], eax 
	mov dword eax, _m
	push dword eax
	mov dword eax, 5
	push dword eax
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jg fin_menorigual_1
	mov ecx, 0
fin_menorigual_1:
	push dword ecx
	pop eax
	cmp eax, 1
	jne fin_then_1
	mov dword eax, 2
	push dword eax
	pop dword eax
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
	jmp fin_then_else_1
fin_then_1:
	mov dword eax, 3
	push dword eax
	pop dword eax
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
fin_then_else_1:
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
