;D:	main
;D:	{
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	x
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	x
;R2:	<declaraciones> ::= <declaracion>
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
segment .text
	global main
	;habilitar funciones de alfalib
	extern scan_int, scan_boolean
	extern print_int, print_boolean, print_string, print_blank, print_endofline
;R21:	<funciones> ::= 
	;codigo correspondiente a la compilacion del no terminal "funciones" 
	;
main:
	mov dword [__esp], esp
;D:	=
;D:	9
	; inicio de la funcion escribir_operando
	mov dword eax, 9
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_x], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	if
;D:	(
;D:	(
;D:	x
;D:	>
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	10
	; inicio de la funcion escribir_operando
	mov dword eax, 10
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	)
	; inicio de la funcion mayor
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jg fin_menorigual_0
	mov ecx, 0
fin_menorigual_0:
	push dword ecx
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	; inicio de la funcion ifthen_inicio
	pop eax
	cmp eax, 1
	jne fin_then_1
;D:	{
;D:	printf
;D:	100
	; inicio de la funcion escribir_operando
	mov dword eax, 100
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir
	pop dword eax
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	else
	; inicio de la funcion ifthenelse_fin_then
	jmp fin_then_else_1
fin_then_1:
;D:	{
;D:	printf
;D:	-
;D:	12345
	; inicio de la funcion escribir_operando
	mov dword eax, 12345
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, 12345
	push dword eax
	; inicio de la funcion cambiar_signo
	pop dword eax
	neg eax
	push dword eax
;R76:	<exp> ::= - <exp>
	; inicio de la funcion escribir
	pop dword eax
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
	; inicio de la funcion ifthenelse_fin
fin_then_else_1:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
	; inicio de la funcion escribir_fin
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
