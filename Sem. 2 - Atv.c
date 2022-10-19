#include <stdio.h>
#include <stdlib.h>

typedef struct aux{
    int id;
    struct aux* mae;
    struct aux* pai;
    } PESSOA;

PESSOA* inicializar(int id){ //função que cria um cadastro com os dados de uma pessoa.
    PESSOA* pessoa = (PESSOA*) malloc(sizeof(PESSOA)); // reserva espaço na memória e aloca o endereço na variável pessoa
    pessoa -> id = id;
    pessoa -> mae = NULL;
    pessoa -> pai = NULL;
    return pessoa;
    }

int main(){

    int id = 12314678;
    PESSOA mae;
    PESSOA pai;
    PESSOA* pessoa;

pessoa = inicializar(id);

printf("id: %i", pessoa->id);
}
