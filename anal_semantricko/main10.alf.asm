;D:	main
;D:	{
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	z
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	function
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
	_z resd 1
segment .text
	global main
	;habilitar funciones de alfalib
	extern scan_int, scan_boolean
	extern print_int, print_boolean, print_string, print_blank, print_endofline
;D:	int
;R10:	<tipo> ::= int
;D:	printandret2
;D:	(
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	arg
;R27:	<parametro_funcion> ::= <tipo> <idpf>
;D:	)
;R26:	<resto_parametros_funcion> ::= 
;R23:	<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>
;D:	{
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	auxArg
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	auxArg
;R2:	<declaraciones> ::= <declaracion>
;R28:	<declaraciones_funcion> ::= <declaraciones>
	; inicio de la funcion declararFuncion
	_printandret2:
	push ebp
	mov ebp, esp
	sub esp, 4
;D:	=
;D:	arg
;D:	;
	; inicio de la funcion escribirParametro
	lea eax, [ebp + 8]
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion escribirVariableLocal
	lea eax, [ebp - 4]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov dword [ebx], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	auxArg
;D:	;
	; inicio de la funcion escribirVariableLocal
	lea eax, [ebp - 4]
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
;D:	return
;D:	3
	; inicio de la funcion escribir_operando
	mov dword eax, 3
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion retornarFuncion
	pop dword eax
	mov esp, ebp
	pop dword ebp
	ret
;R61:	<retorno_funcion> ::= return <exp>
;R38:	<sentencia_simple> ::= <retorno_funcion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R22:	<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }
;D:	z
;R21:	<funciones> ::= 
;R20:	<funciones> ::= <funcion> <funciones>
	;codigo correspondiente a la compilacion del no terminal "funciones" 
	;
main:
	mov dword [__esp], esp
;D:	=
;D:	99
	; inicio de la funcion escribir_operando
	mov dword eax, 99
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_z], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	printandret2
;D:	(
;D:	z
;D:	)
	; inicio de la funcion escribir_operando
	mov dword eax, 99
	push dword eax
	; inicio de la funcion operandoEnPilaAArgumento
;R80:	<exp> ::= <identificador>
;R92:	<resto_lista_expresiones> ::= 
;R89:	<lista_expresiones> ::= <exp> <resto_lista_expresiones>
	; inicio de la funcion llamarFuncion
	call _printandret2
	; inicio de la funcion limpiarPila
	add esp, 4
	push dword eax
;R88:	<exp> ::= id_llamada_funcion ( <lista_expresiones> )
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
