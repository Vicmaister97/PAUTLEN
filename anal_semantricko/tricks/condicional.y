condicional: if_exp_sentencias TOK_LLAVEDERECHA {
    ifthenelse_fin(out, $1.etiqueta); }
| if_exp_sentencias TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
    ifthenelse_fin(out, $1.etiqueta);
};

if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
  //COMPROBACIONES SEMANTICAS
  //GESTION ETIQUETA
  ifthen_inicio(out, $3.es_variable, $$.etiqueta);
};

if_exp_sentencias: if_exp sentencias {
  $$.etiqueta = $1.etiqueta;
  ifthenelse_fin_then(out, $$.etiqueta);
}
