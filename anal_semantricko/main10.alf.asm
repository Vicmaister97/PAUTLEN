;D:	main
;D:	{
;D:	int
;R10:	<tipo> ::= int
;R9:	<clase_escalar> ::= <tipo>
;R5:	<clase> ::= <clase_escalar>
;D:	z
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	,
;D:	res
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
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
	_res resd 1
segment .text
	global main
	;habilitar funciones de alfalib
	extern scan_int, scan_boolean
	extern print_int, print_boolean, print_string, print_blank, print_endofline
;D:	int
;R10:	<tipo> ::= int
;D:	mayorQue5
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
;D:	,
;D:	rv
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R19:	<identificadores> ::= <identificador> , <identificadores>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	auxArg
;R2:	<declaraciones> ::= <declaracion>
;R28:	<declaraciones_funcion> ::= <declaraciones>
	; inicio de la funcion declararFuncion
	_mayorQue5:
	push ebp
	mov ebp, esp
	sub esp, 8
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
;D:	arg
;D:	;
	; inicio de la funcion escribirParametro
	lea eax, [ebp + 8]
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
;D:	rv
;D:	=
;D:	1
	; inicio de la funcion escribir_operando
	mov dword eax, 1
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribirVariableLocal
	lea eax, [ebp - 8]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	if
;D:	(
;D:	(
;D:	auxArg
;D:	<
	; inicio de la funcion escribirVariableLocal
	lea eax, [ebp - 4]
	push dword eax
;R80:	<exp> ::= <identificador>
;D:	5
	; inicio de la funcion escribir_operando
	mov dword eax, 5
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	)
	; inicio de la funcion menor
	pop dword ebx
	pop dword eax
	mov eax, [eax]
	mov ecx, 1
	cmp eax, ebx
	jl fin_menorigual_0
	mov ecx, 0
fin_menorigual_0:
	push dword ecx
;R97:	<comparacion> ::= <exp> < <exp>
;R83:	<exp> ::= ( <comparacion> )
;D:	)
	; inicio de la funcion ifthen_inicio
	pop eax
	cmp eax, 1
	jne fin_then_1
;D:	{
;D:	rv
;D:	=
;D:	0
	; inicio de la funcion escribir_operando
	mov dword eax, 0
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribirVariableLocal
	lea eax, [ebp - 8]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
;D:	else
	; inicio de la funcion ifthenelse_fin_then
	jmp fin_then_else_1
fin_then_1:
;D:	{
;D:	rv
;D:	=
;D:	100
	; inicio de la funcion escribir_operando
	mov dword eax, 100
	push dword eax
;R105:	<constante_entera> ::= <numero>
;R100:	<constante> ::= <constante_entera>
;R81:	<exp> ::= <constante>
;D:	;
	; inicio de la funcion escribirVariableLocal
	lea eax, [ebp - 8]
	push dword eax
	; inicio de la funcion asignarDestinoEnPila
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	}
;R30:	<sentencias> ::= <sentencia>
	; inicio de la funcion ifthenelse_fin
fin_then_else_1:
;R51:	<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }
;R40:	<bloque> ::= <condicional>
;R33:	<sentencia> ::= <bloque>
;D:	return
;D:	rv
;D:	;
	; inicio de la funcion escribirVariableLocal
	lea eax, [ebp - 8]
	push dword eax
;R80:	<exp> ::= <identificador>
	; inicio de la funcion retornarFuncion
	pop dword eax
	mov eax, [eax]
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
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R31:	<sentencias> ::= <sentencia> <sentencias>
;R22:	<funcion> ::= function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }
;D:	scanf
;R21:	<funciones> ::= 
;R20:	<funciones> ::= <funcion> <funciones>
	;codigo correspondiente a la compilacion del no terminal "funciones" 
	;
main:
	mov dword [__esp], esp
;D:	z
	; inicio de la funcion leer
	push dword _z
	call scan_int
	add esp, 4
;R54:	<lectura> ::= scanf <identificador>
;R35:	<sentencia_simple> ::= <lectura>
;D:	;
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
;D:	res
;D:	=
;D:	mayorQue5
;D:	(
;D:	z
;D:	)
	; inicio de la funcion escribir_operando
	mov dword eax, 100
	push dword eax
	; inicio de la funcion operandoEnPilaAArgumento
;R80:	<exp> ::= <identificador>
;R92:	<resto_lista_expresiones> ::= 
;R89:	<lista_expresiones> ::= <exp> <resto_lista_expresiones>
	; inicio de la funcion llamarFuncion
	call _mayorQue5
	; inicio de la funcion limpiarPila
	add esp, 4
	push dword eax
;R88:	<exp> ::= id_llamada_funcion ( <lista_expresiones> )
;D:	;
	; inicio de la funcion asignar
	pop dword eax
	mov dword [_res], eax 
;R43:	<asignacion> ::= <identificador> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	res
;D:	;
	; inicio de la funcion escribir_operando
	mov dword eax, _res
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