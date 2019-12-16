bucle: while_exp sentencias TOK_LLAVEDERECHA {
  while_fin(out, $1.etiqueta);
;

while: TOK_WHILE TOK_PARENTESISIZQUIERDO {
  //GESTION ETIQUETA
  while_inicio(out, $$.etiqueta);
};

while_exp: while exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
  //COMPROBACIONES SEMANTICAS (VER SI EL TIPO DE exp ES BOOLEAN)
  $$.etiqueta = $1.etiqueta;
  while_exp_pila(out, $2.es_variable, $$.etiqueta);
};
