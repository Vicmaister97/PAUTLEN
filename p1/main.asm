segment .data
	;declaracion de variables inicializadas
	;
	mensaje_1 db "División por cero", 0
	mensaje_2 db "Indice fuera de rango", 0
segment .bss
	;declaracion de variables sin inicializar
	;
	__esp resd 1
	_z resd 1
segment .text
	global main
	;habilitar funciones de alfalib
	extern scan_int, scan_boolean
	extern print_int, print_boolean, print_string, print_blank, print_endofline
	_doble:
	push ebp
	mov ebp, esp
	sub esp, 4
	lea eax, [ebp + 8]
	push dword eax
	lea eax, [ebp - 4]
	push dword eax
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov dword [ebx], eax
	mov dword eax, 2
	push dword eax
	lea eax, [ebp + 8]
	push dword eax
	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	imul ebx
	push dword eax
	pop dword eax
	mov esp, ebp
	pop dword ebp
	ret
	;codigo correspondiente a la compilacion del no terminal "funciones" 
	;
main:
	mov dword [__esp], esp
	mov dword eax, 2
	push dword eax
	pop dword eax
	mov dword [_z], eax 
	mov dword eax, _z
	push dword eax
	pop dword eax
	mov eax, [eax]
	push dword eax
	call _doble
	add esp, 4
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
