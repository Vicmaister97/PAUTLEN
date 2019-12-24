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
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	boolean
;R11:	<tipo> ::= boolean
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	z
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	x
;R2:	<declaraciones> ::= <declaracion>
;R3:	<declaraciones> ::= <declaracion> <declaraciones>
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
;D:	5
	; inicio de la funcion escribir_operando
	mov dword eax, 5
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
;D:	3
	; inicio de la funcion escribir_operando
	mov dword eax, 3
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
;D:	(
;D:	x
;D:	==
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	y
;D:	)
	; inicio de la funcion escribir_operando
	mov dword eax, _y
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
	; inicio de la funcion no
	pop dword eax
	mov dword eax, [eax]
	cmp eax, 0
	je negar_0_0
	mov dword ebx, 0
	jmp fin_neg_0
negar_0_0:
	mov dword ebx, 1
fin_neg_0:
	push dword ebx
;R93:	<comparacion> ::= <exp> == <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	x
;D:	!=
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	y
;D:	)
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
	; inicio de la funcion distinto
	pop dword ebx
	mov ebx, [ebx]
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jne fin_dist_0
	mov ecx, 0
fin_dist_0:
	push dword ecx
;R94:	<comparacion> ::= <exp> != <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	x
;D:	<
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	y
;D:	)
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
	; inicio de la funcion menor
	pop dword ebx
	mov ebx, [ebx]
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jl fin_menorigual_1
	mov ecx, 0
fin_menorigual_1:
	push dword ecx
;R97:	<comparacion> ::= <exp> < <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	x
;D:	<=
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	y
;D:	)
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
	; inicio de la funcion menor_igual
	pop dword ebx
	mov ebx, [ebx]
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jle fin_menorigual_2
	mov ecx, 0
fin_menorigual_2:
	push dword ecx
;R95:	<comparacion> ::= <exp> <= <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	x
;D:	>
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	y
;D:	)
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
	; inicio de la funcion mayor
	pop dword ebx
	mov ebx, [ebx]
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jg fin_menorigual_3
	mov ecx, 0
fin_menorigual_3:
	push dword ecx
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	x
;D:	>=
	; inicio de la funcion escribir_operando
	mov dword eax, _x
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	y
;D:	)
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
	; inicio de la funcion mayor_igual
	pop dword ebx
	mov ebx, [ebx]
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jge fin_menorigual_4
	mov ecx, 0
fin_menorigual_4:
	push dword ecx
;R96:	<comparacion> ::= <exp> >= <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	1
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	>=
;D:	0
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	)
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
	; inicio de la funcion mayor_igual
	pop dword ebx
	pop dword eax
	mov ecx, 1
	cmp eax, ebx
	jge fin_menorigual_5
	mov ecx, 0
fin_menorigual_5:
	push dword ecx
;R96:	<comparacion> ::= <exp> >= <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	1
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	>
;D:	0
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	)
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
	; inicio de la funcion mayor
	pop dword ebx
	pop dword eax
	mov ecx, 1
	cmp eax, ebx
	jg fin_menorigual_6
	mov ecx, 0
fin_menorigual_6:
	push dword ecx
;R98:	<comparacion> ::= <exp> > <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	1
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	==
;D:	0
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	)
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
	; inicio de la funcion no
	pop dword eax
	cmp eax, 0
	je negar_0_1
	mov dword ebx, 0
	jmp fin_neg_1
negar_0_1:
	mov dword ebx, 1
fin_neg_1:
	push dword ebx
;R93:	<comparacion> ::= <exp> == <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	1
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	<
;D:	0
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	)
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
	; inicio de la funcion menor
	pop dword ebx
	pop dword eax
	mov ecx, 1
	cmp eax, ebx
	jl fin_menorigual_7
	mov ecx, 0
fin_menorigual_7:
	push dword ecx
;R97:	<comparacion> ::= <exp> < <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	1
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	<=
;D:	0
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	)
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
	; inicio de la funcion menor_igual
	pop dword ebx
	pop dword eax
	mov ecx, 1
	cmp eax, ebx
	jle fin_menorigual_8
	mov ecx, 0
fin_menorigual_8:
	push dword ecx
;R95:	<comparacion> ::= <exp> <= <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	z
;D:	=
;D:	(
;D:	4
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	!=
;D:	3
	; inicio de la funcion escribir_operando
	mov dword eax, 3
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	)
	; inicio de la funcion escribir_operando
	mov dword eax, 4
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 3
	push dword eax
	; inicio de la funcion distinto
	pop dword ebx
	pop dword eax
	mov ecx, 1
	cmp eax, ebx
	jne fin_dist_9
	mov ecx, 0
fin_dist_9:
	push dword ecx
;R94:	<comparacion> ::= <exp> != <exp>
;R83:	<exp> ::= ( <comparacion> )
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
	call print_boolean
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
