;escribir_subseccion_data
segment .data
	msg_error_indice_vector db "Indice de vector fuera de rango", 0
	msg_error_division db "Error division por 0", 0
;escribir_cabecera_bss
segment .bss
	__esp resd 1
;D:	main
;D:	{
;D:	array
;D:	int
;R10:	<tipo> ::= int
;D:	[
;D:	3
;D:	]
;R15:	<clase_vector> ::= array <tipo> [ <constante_entera> ]
;R7:	<clase> ::= <clase_vector>
;D:	vector1
;declarar_variable
	_vector1 resd 3
;R108:	<identificador> ::= TOK_IDENTIFICADOR
;D:	;
;R18:	<identificadores> ::= <identificador>
;R4:	<declaracion> ::= <clase> <identificadores> ;
;D:	vector1
;R2:	<declaraciones> ::= <declaracion>
;escribir_segmento_codigo
segment .text
	global main
	extern malloc, free
	extern scan_int, print_int, scan_boolean, print_boolean
	extern print_endofline, print_blank, print_string
;R21:	<funciones> ::=
;escribir_inicio_main
; -----------------------
; PROCEDIMIENTO PRINCIPAL
main:
	mov dword [__esp], esp
;D:	[
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector1
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector1
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;D:	=
;D:	10
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 10
;R81:	<exp> ::= <constante>
;D:	;
;escribir_operando
	push dword 0
; escribir_elemento_vector vector1
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector1
	lea eax, [edx + eax*4]
	push dword eax
; asignarDestinoEnPila:
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R44:	<asignacion> ::= <elemento_vector> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	vector1
;D:	[
;D:	1
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector1
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector1
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;D:	=
;D:	20
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 20
;R81:	<exp> ::= <constante>
;D:	;
;escribir_operando
	push dword 1
; escribir_elemento_vector vector1
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector1
	lea eax, [edx + eax*4]
	push dword eax
; asignarDestinoEnPila:
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R44:	<asignacion> ::= <elemento_vector> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	vector1
;D:	[
;D:	2
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector1
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector1
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;D:	=
;D:	30
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 30
;R81:	<exp> ::= <constante>
;D:	;
;escribir_operando
	push dword 2
; escribir_elemento_vector vector1
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector1
	lea eax, [edx + eax*4]
	push dword eax
; asignarDestinoEnPila:
	pop dword ebx
	pop dword eax
	mov dword [ebx], eax
;R44:	<asignacion> ::= <elemento_vector> = <exp>
;R34:	<sentencia_simple> ::= <asignacion>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	vector1
;D:	[
;D:	0
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 0
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector1
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector1
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;R85:	<exp> ::= <elemento_vector>
;D:	;
;escribir
	pop eax
	mov eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	vector1
;D:	[
;D:	1
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 1
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector1
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector1
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;R85:	<exp> ::= <elemento_vector>
;D:	;
;escribir
	pop eax
	mov eax, [eax]
	push dword eax
	call print_int
	add esp, 4
	call print_endofline
;R56:	<escritura> ::= printf <exp>
;R36:	<sentencia_simple> ::= <escritura>
;R32:	<sentencia> ::= <sentencia_simple> ;
;D:	printf
;D:	vector1
;D:	[
;D:	2
;R104:	<constante_entera> ::= <numero>
;R99:	<constante> ::= <constante_logica>
;escribir_operando
	push dword 2
;R81:	<exp> ::= <constante>
;D:	]
; escribir_elemento_vector vector1
	pop dword eax
	cmp eax, 0
	jl near fin_indice_fuera_rango
	cmp eax, 2
	jg near fin_indice_fuera_rango
	mov dword edx, _vector1
	lea eax, [edx + eax*4]
	push dword eax
;R48:	<elemento_vector> ::= <identificador> [ <exp> ]
;R85:	<exp> ::= <elemento_vector>
;D:	;
;escribir
	pop eax
	mov eax, [eax]
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
;R1:	<programa> ::= main { <declaraciones> <funciones> <sentencias> }
;escribir_fin

	jmp near fin
fin_error_division: 
	push dword msg_error_division
	call print_string
	add esp, 4
	call print_endofline
	jmp near fin
fin_indice_fuera_rango: 
	push dword msg_error_indice_vector
	call print_string
	add esp, 4
	call print_endofline
	jmp near fin
fin: 
	mov esp, [__esp]
	ret
