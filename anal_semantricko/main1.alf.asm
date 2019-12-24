;D:	main
;D:	{
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	x
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	,
;D:	y
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	,
;D:	z
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R19:	<identificadores> ::= <identificador> , <identificadores>
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
	_y resd 1
	_z resd 1
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
;D:	1
	; inicio de la funcion escribir_operando
	mov dword eax, 1
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
;D:	y
;D:	=
;D:	2
	; inicio de la funcion escribir_operando
	mov dword eax, 2
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_y], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	y
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _y
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion asignar
	pop dword eax
	mov dword eax, [eax]
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	x
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	y
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _y
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	x
;D:	+
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	y
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _y
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, _y
	push dword eax
	; inicio de la funcion sumar
	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	mov dword eax, [eax]
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	3
	; inicio de la funcion escribir_operando
	mov dword eax, 3
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	+
;D:	4
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, 3
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
	; inicio de la funcion sumar
	pop dword ebx
	pop dword eax
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	x
;D:	+
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	4
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
	; inicio de la funcion sumar
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	3
	; inicio de la funcion escribir_operando
	mov dword eax, 3
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	+
;D:	y
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _y
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir_operando
	mov dword eax, 3
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, _y
	push dword eax
	; inicio de la funcion sumar
	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	3
	; inicio de la funcion escribir_operando
	mov dword eax, 3
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	+
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir_operando
	mov dword eax, 3
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
	; inicio de la funcion sumar
	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	z
;D:	+
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	2
	; inicio de la funcion escribir_operando
	mov dword eax, 2
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 2
	push dword eax
	; inicio de la funcion sumar
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	z
;D:	+
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	x
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
	; inicio de la funcion sumar
	pop dword ebx
	mov dword ebx, [ebx]
	pop dword eax
	mov dword eax, [eax]
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	z
;D:	*
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	10
	; inicio de la funcion escribir_operando
	mov dword eax, 10
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 10
	push dword eax
	; inicio de la funcion multiplicar
	pop dword ebx
	pop dword eax
	mov dword eax, [eax]
	imul ebx
	push dword eax
;R75:	<exp> ::= <exp> * <exp>
;D:	;
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	z
;D:	/
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	11
	; inicio de la funcion escribir_operando
	mov dword eax, 11
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 11
	push dword eax
	; inicio de la funcion dividir
	pop dword ecx
	cmp ecx, 0
	je error_1
	pop dword eax
	mov dword eax, [eax]
	cdq
	idiv ecx
	push dword eax
;R74:	<exp> ::= <exp> / <exp>
;D:	;
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	-
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
	; inicio de la funcion cambiar_signo
	pop dword eax
	mov dword eax, [eax]
	neg eax
	push dword eax
;R76:	<exp> ::= - <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	z
;D:	-
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	x
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
	; inicio de la funcion cambiar_signo
	pop dword eax
	mov dword eax, [eax]
	neg eax
	push dword eax
;R73:	<exp> ::= <exp> - <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	5
	; inicio de la funcion escribir_operando
	mov dword eax, 5
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	+
;D:	4
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, 5
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
	; inicio de la funcion sumar
	pop dword ebx
	pop dword eax
	add eax, ebx
	push dword eax
;R72:	<exp> ::= <exp> + <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	5
	; inicio de la funcion escribir_operando
	mov dword eax, 5
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	-
;D:	4
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, 5
	push dword eax
	; inicio de la funcion cambiar_signo
	pop dword eax
	neg eax
	push dword eax
;R73:	<exp> ::= <exp> - <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	5
	; inicio de la funcion escribir_operando
	mov dword eax, 5
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	*
;D:	4
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
	; inicio de la funcion escribir_operando
	mov dword eax, 5
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
	; inicio de la funcion multiplicar
	pop dword ebx
	pop dword eax
	imul ebx
	push dword eax
;R75:	<exp> ::= <exp> * <exp>
;D:	;
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	20
	; inicio de la funcion escribir_operando
	mov dword eax, 20
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	/
;D:	4
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
	; inicio de la funcion escribir_operando
	mov dword eax, 20
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
	; inicio de la funcion dividir
	pop dword ecx
	cmp ecx, 0
	je error_1
	pop dword eax
	cdq
	idiv ecx
	push dword eax
;R74:	<exp> ::= <exp> / <exp>
;D:	;
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	-
;D:	5
	; inicio de la funcion escribir_operando
	mov dword eax, 5
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, 5
	push dword eax
	; inicio de la funcion cambiar_signo
	pop dword eax
	neg eax
	push dword eax
;R76:	<exp> ::= - <exp>
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	z
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _z
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir
	pop dword eax
	mov dword eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
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
