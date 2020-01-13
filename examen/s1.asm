;D:	main
;D:	{
;D:	array
;D:	boolean
;R11:	<tipo> ::= boolean
;D:	[
;D:	3
;D:	]
;R15:	<clase_vector> ::= array <tipo> [ constante_entera ]
;R7:	<clase> ::= <clase_vector>
;D:	lel
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	array
;D:	int
;R10:	<tipo> ::= int
;D:	[
;D:	4
;D:	]
;R15:	<clase_vector> ::= array <tipo> [ constante_entera ]
;R7:	<clase> ::= <clase_vector>
;D:	v
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	init
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
	_lel resd 3
	_v resd 4
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
;D:	lel
;REX5:	<principio_init> ::= init <identificador> ;
;D:	{
;D:	true
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
;R102:	<constante_logica> ::= true
;R99:	<constante> ::= <constante_logica>
;R81:	<exp> ::= <constante>
;D:	}
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
	; inicio de la funcion escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near error_2
	cmp eax, 3
	jge near error_2
	mov dword edx, _lel
	lea eax, [edx + eax*4]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;REX6:	<lista_vector> ::= <exp> ; <lista_vector>
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
	; inicio de la funcion escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near error_2
	cmp eax, 3
	jge near error_2
	mov dword edx, _lel
	lea eax, [edx + eax*4]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
	; inicio de la funcion escribir_operando
	mov dword eax, 2
	push dword eax
	; inicio de la funcion escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near error_2
	cmp eax, 3
	jge near error_2
	mov dword edx, _lel
	lea eax, [edx + eax*4]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;REX2:	<lista_vector> ::= <exp> ;
;REX3:	<init_vector> ::= <principio_init> { <lista_vector> } ;
;REX4:	<sentencia_simple> ::= <init_vector>
;D:	;
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	lel
;D:	[
;D:	0
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	]
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
	; inicio de la funcion escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near error_2
	cmp eax, 3
	jge near error_2
	mov dword edx, _lel
	lea eax, [edx + eax*4]
	push dword eax
;R85:	<exp> ::= <elemento_vector>
;D:	;
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
;D:	printf
;D:	lel
;D:	[
;D:	1
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	]
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
	; inicio de la funcion escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near error_2
	cmp eax, 3
	jge near error_2
	mov dword edx, _lel
	lea eax, [edx + eax*4]
	push dword eax
;R85:	<exp> ::= <elemento_vector>
;D:	;
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
;D:	printf
;D:	lel
;D:	[
;D:	2
	; inicio de la funcion escribir_operando
	mov dword eax, 2
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	]
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
	; inicio de la funcion escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near error_2
	cmp eax, 3
	jge near error_2
	mov dword edx, _lel
	lea eax, [edx + eax*4]
	push dword eax
;R85:	<exp> ::= <elemento_vector>
;D:	;
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
;D:	init
;D:	v
;REX5:	<principio_init> ::= init <identificador> ;
;D:	{
;D:	10
	; inicio de la funcion escribir_operando
	mov dword eax, 10
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
	; inicio de la funcion escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near error_2
	cmp eax, 4
	jge near error_2
	mov dword edx, _v
	lea eax, [edx + eax*4]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;REX6:	<lista_vector> ::= <exp> ; <lista_vector>
;D:	20
	; inicio de la funcion escribir_operando
	mov dword eax, 20
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
	; inicio de la funcion escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near error_2
	cmp eax, 4
	jge near error_2
	mov dword edx, _v
	lea eax, [edx + eax*4]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;REX6:	<lista_vector> ::= <exp> ; <lista_vector>
;D:	30
	; inicio de la funcion escribir_operando
	mov dword eax, 30
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, 2
	push dword eax
	; inicio de la funcion escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near error_2
	cmp eax, 4
	jge near error_2
	mov dword edx, _v
	lea eax, [edx + eax*4]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;REX6:	<lista_vector> ::= <exp> ; <lista_vector>
;D:	50
	; inicio de la funcion escribir_operando
	mov dword eax, 50
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, 3
	push dword eax
	; inicio de la funcion escribir_elemento_vector
	pop dword eax
	cmp eax, 0
	jl near error_2
	cmp eax, 4
	jge near error_2
	mov dword edx, _v
	lea eax, [edx + eax*4]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;REX6:	<lista_vector> ::= <exp> ; <lista_vector>
;D:	40
	; inicio de la funcion escribir_operando
	mov dword eax, 40
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
