MATRIZ* multiplicarMatrizes(MATRIZ* m1, MATRIZ* m2){
if (m1->colunas != m2->linhas) return NULL;
MATRIZ* res = inicializarMatriz(m1->linhas,m2->colunas);
int i,j,k;
int valor;
/* COMPLETAR */
return res;
}
