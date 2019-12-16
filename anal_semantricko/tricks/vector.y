clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO TOK_CONSTANTE_ENTERA TOK_CORCHETEDERECHO {
  //EN $4.valor TENEMOS EL TAMAÑO DEL VECTOR 
  //COMPROBACIONES SEMANTICAS (TAMANO > 0 y TAMANO < MAX) Y PROPAGACION EN $$.valor
};

asignacion: TOK_IDENTIFICADOR TOK_ASIGNACION exp {...}
| elemento_vector TOK_ASIGNACION exp {
  //COMPROBACIONES SEMANTICAS (VER SI $1.tipo == $3.tipo)
  //$1.valor ES EL INDICE DEL VECTOR EN EL QUE QUEREMOS ASIGNAR exp
  escribir_operando(out, $1.valor, 0);
  escribir_elemento_vector(out, $1.nombre, simbolo->longitud, $3.es_variable);
  asignarDestinoEnPila(out, $3.es_variable);
};

elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {
  //COMPROBACIONES SEMANTICAS PARA EL SIMBOLO CON IDENTIFICADOR $1.nombre
  //NECESITAMOS EN $$: tipo, es_variable = 1, valor de $3 (ES EL INDICE DEL VECTOR)
  escribir_elemento_vector(out, $1.nombre, simbolo->longitud, $3.es_variable);
};
