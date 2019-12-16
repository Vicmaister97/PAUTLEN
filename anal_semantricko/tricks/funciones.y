funcion: fn_declaration sentencias TOK_LLAVEDERECHA {
  //COMPROBACIONES SEMANTICAS
  //ERROR SI LA FUNCION NO TIENE SENTENCIA DE RETORNO
  //ERROR SI YA SE HA DECLARADO UNA FUNCION CON NOMBRE $1.nombre
  //CIERRE DE AMBITO, ETC
  simbolo->num_parametros = num_parametros;
};

fn_declaration : fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion {
  //COMPROBACIONES SEMANTICAS
  //ERROR SI YA SE HA DECLARADO UNA FUNCION CON NOMBRE $1.nombre
  simbolo->num_parametros = num_parametros;
  strcpy($$.nombre, $1.nombre);
  $$.tipo = $1.tipo;
  //GENERACION DE CODIGO
  declararFuncion(out, $1.nombre, num_variables_locales_actual);
} 

fn_name : TOK_FUNCTION tipo TOK_IDENTIFICADOR {
  //COMPROBACIONES SEMANTICAS
  //ERROR SI YA SE HA DECLARADO UNA FUNCION CON NOMBRE $3.nombre
  simbolo.identificador = $3.nombre;
  simbolo.cat_simbolo = FUNCION;
  simbolo.tipo = tipo_actual;
  $$.tipo = tipo_actual;
  strcpy($$.nombre, $3.nombre);

  //ABRIR AMBITO EN LA TABLA DE SIMBOLOS CON IDENTIFICADOR $3.nombre
  //RESETEAR VARIABLES QUE NECESITAMOS PARA PROCESAR LA FUNCION:
  //posicion_variable_local, num_variables_locales, posicion_parametro, num_parametros
}

parametros_funcion: parametro_funcion resto_parametros_funcion}
|
;

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion
|
;

parametro_funcion: tipo idpf {
  //INCREMENTAR CONTADORES, POR EJEMPLO
  num_parametros++;
  posicion_parametro++;
};

idpf : TOK_IDENTIFICADOR {
    //COMPROBACIONES SEMANTICAS PARA $1.nombre
    //EN ESTE CASO SE MUESTRA ERROR SI EL NOMBRE DEL PARAMETRO YA SE HA UTILIZADO
    simbolo.identificador = $1.nombre;
    simbolo.cat_simbolo = PARAMETRO;
    simbolo.tipo = tipo_actual;
    simbolo.categoria = ESCALAR;
    simbolo.posicion = posicion_paremetro;
    //DECLARAR SIMBOLO EN LA TABLA
}
