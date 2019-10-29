segment .data
	;declaracion de variables inicializadas
	;
	mensaje_1 db "División por cero", 0
	mensaje_2 db "Indice fuera de rango", 0
segment .bss
	;declaracion de variables sin inicializar
	;
	__esp resd 1
	_b1 resd 1
	_x resd 1
segment .text
	global main
	;habilitar funciones de alfalib
	extern scan_int, scan_boolean
	extern print_int, print_boolean, print_string, print_blank, print_endofline
	;codigo correspondiente a la compilacion del no terminal "funciones" 
	;
main:
	mov dword [__esp], esp
	push dword _b1
	call scan_boolean
	add esp, 4
	push dword _x
	call scan_int
	add esp, 4
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jg fin_menorigual_0
	mov ecx, 0
fin_menorigual_0:
	push dword ecx
	pop dword eax
	push dword eax
	call print_boolean
	add esp, 4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jge fin_menorigual_1
	mov ecx, 0
fin_menorigual_1:
	push dword ecx
	pop dword eax
	push dword eax
	call print_boolean
	add esp, 4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jl fin_menorigual_2
	mov ecx, 0
fin_menorigual_2:
	push dword ecx
	pop dword eax
	push dword eax
	call print_boolean
	add esp, 4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jle fin_menorigual_3
	mov ecx, 0
fin_menorigual_3:
	push dword ecx
	pop dword eax
	push dword eax
	call print_boolean
	add esp, 4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	je fin_igual_4
	mov ecx, 0
fin_igual_4:
	push dword ecx
	pop dword eax
	push dword eax
	call print_boolean
	add esp, 4
	call print_endofline
	mov dword eax, _x
	push dword eax
	mov dword eax, 3
	push dword eax
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jne fin_dist_5
	mov ecx, 0
fin_dist_5:
	push dword ecx
	pop dword eax
	push dword eax
	call print_boolean
	add esp, 4
	call print_endofline
	mov dword eax, _b1
	push dword eax
	mov dword eax, 0
	push dword eax
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	and eax, ebx
	push dword eax
	pop dword eax
	push dword eax
	call print_boolean
	add esp, 4
	call print_endofline
	mov dword eax, _b1
	push dword eax
	mov dword eax, 1
	push dword eax
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	or eax, ebx
	push dword eax
	pop dword eax
	push dword eax
	call print_boolean
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
