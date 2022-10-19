/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2021                           **/
/**   <turma> - Prof. Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   EP 2 - Fila Preferencial                                      **/
/**                                                                 **/
/**   <Odélio Porto Júnior>                   <12701501>            **/
/**                                                                 **/
/*********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#define true 1
#define false 0

typedef int bool;

typedef struct aux {
  int id;
  bool ehPreferencial;
  struct aux* ant;
  struct aux* prox;
} ELEMENTO, * PONT;

typedef struct {
  PONT cabeca;
  PONT inicioNaoPref;
} FILAPREFERENCIAL, * PFILA;




PFILA criarFila(){
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->cabeca = (PONT) malloc(sizeof(ELEMENTO));
    res->inicioNaoPref = res->cabeca;
    res->cabeca->id = -1;
    res->cabeca->ehPreferencial = false;
    res->cabeca->ant = res->cabeca;
    res->cabeca->prox = res->cabeca;
    return res;
}

int tamanho(PFILA f){
	PONT atual = f->cabeca->prox;
	int tam = 0;
	while (atual != f->cabeca) {
		atual = atual->prox;
		tam++;
	}
	return tam;
}

PONT buscarID(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual;
		atual = atual->prox;
	}
	return NULL;
}

void exibirLog(PFILA f){
	int numElementos = tamanho(f);
	printf("\nLog fila [elementos: %i]\t- Inicio:", numElementos);
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->prox;
	}
	printf("\n                       \t-    Fim:");
	atual = f->cabeca->ant;
	while (atual != f->cabeca) {
		printf(" [%i;%i]", atual->id, atual->ehPreferencial);
		atual = atual->ant;
	}
	printf("\n\n");
}


bool consultarPreferencial(PFILA f, int id){
	PONT atual = f->cabeca->prox;
	while (atual != f->cabeca) {
		if (atual->id == id) return atual->ehPreferencial;
		atual = atual->prox;
	}
	return -1;
}

bool busca(PFILA f, int id){ // função para verificar se já existe um valor igual a 'id'
   PONT pos = f->cabeca->prox;
   if(pos == f->cabeca) //somente a cabeça como elemento
        return false;
   while(pos != f->cabeca){
        if (id == pos->id){
            return false;
        }
        pos = pos->prox;
   }
}

bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial){
    PONT pontAnterior;

    if(id < 0){
        return false;
    }
    busca(f, id); // verificar se já existe 'id'

    PONT novaPessoa = (PONT) malloc(sizeof(ELEMENTO));// alocar memória para o novo elemento
    novaPessoa->id = id;
    novaPessoa->ehPreferencial = ehPreferencial;

    if(novaPessoa->ehPreferencial == true){ // se o novo elemento for preferencial
        PONT pos = f->cabeca->prox;

        while(pos->ehPreferencial == true){ //verificar onde a pessoa preferencial será inserida
            pontAnterior = pos;
            pos = pos->prox;
        }
        pos->ant = novaPessoa;
        novaPessoa->prox = pos;
        novaPessoa->ant = pontAnterior;
        pontAnterior->prox = novaPessoa;
        if(novaPessoa->prox == f->cabeca){
            f->cabeca->ant = novaPessoa;
        }
    }

    else{ // se a pessoa inserida não é preferencial, colocar no fim da fila
        PONT pos = f->cabeca->prox;
        while(pos != f->cabeca){
            pontAnterior = pos;
            pos = pos->prox;
        }
        pontAnterior->prox = novaPessoa;
        novaPessoa->ant = pontAnterior;
        novaPessoa->prox = f->cabeca;
        f->cabeca->ant = novaPessoa;
        if(novaPessoa->ant->ehPreferencial == true){
            f->inicioNaoPref = novaPessoa;
        }
        return true;
    }
}

bool atenderPrimeiraDaFila(PFILA f, int* id){
    if (f->cabeca->prox == f->cabeca && f->cabeca->ant == f->cabeca) //fila sem pessoas
        return false;

    *id = f->cabeca->prox->id;//coloca o identificador na variável apontada

    if(f->cabeca->ant == f->cabeca->prox){//(I)caso em que há somente um elemento na fila
       f->cabeca->ant = f->cabeca;
       f->cabeca->prox = f->cabeca;
       f->inicioNaoPref = f->cabeca;
       return true;
    }

    else if(f->cabeca->prox->ehPreferencial == false){//(II)somente pessoas sem atendimento preferencial
       PONT elementoRemovido = f->cabeca->prox;
       PONT novoPrimeiroElemento = elementoRemovido->prox;

       f->inicioNaoPref = novoPrimeiroElemento;
       f->cabeca->prox = novoPrimeiroElemento;
       novoPrimeiroElemento->ant = f->cabeca;
       free(elementoRemovido);
       return true;
    }

    else if(f->cabeca->ant->ehPreferencial == true){//(III)somente pessoas com atendimento preferencial
       PONT elementoRemovido = f->cabeca->prox;
       PONT novoPrimeiroElemento = elementoRemovido->prox;

       f->cabeca->prox = novoPrimeiroElemento;
       novoPrimeiroElemento->ant = f->cabeca;
       free(elementoRemovido);
       return true;
    }

    else{//(IV)misto - pessoas com e sem atendimento preferencial
       PONT elementoRemovido = f->cabeca->prox;
       PONT novoPrimeiroElemento = elementoRemovido->prox;

       if(novoPrimeiroElemento->ehPreferencial == false){ //atualiza inicioNãoPref no caso de elemento comum
       f->inicioNaoPref = novoPrimeiroElemento;
       }

       f->cabeca->prox = novoPrimeiroElemento;
       novoPrimeiroElemento->ant = f->cabeca;
       free(elementoRemovido);
       return true;
    }
}


bool desistirDaFila(PFILA f, int id){
    int idEncontrado = 0;
    int contadorBusca = 0;
    PONT pontIdEncontrado;

    PONT pos = f->cabeca->prox;
    while(pos != f->cabeca){ //encontrar o id buscado
        if (id == pos->id){
            idEncontrado = 1;
            pontIdEncontrado = pos;
        }
        pos = pos->prox;
    }

    if(idEncontrado == 0) //caso em que id não é encontrado
        return false;

    else if(f->cabeca->ant == pontIdEncontrado){ //(I) fila com elemento único
        f->cabeca->ant = f->cabeca;
        f->cabeca->prox = f->cabeca;
        if(pontIdEncontrado->ehPreferencial == false)
            f->inicioNaoPref = f->cabeca;
        free(pontIdEncontrado);
        return true;
    }

    else if(f->cabeca->prox == pontIdEncontrado && pontIdEncontrado->ehPreferencial == false){  //(II) o primeiro elemento da fila é não preferencial
        f->inicioNaoPref = pontIdEncontrado->prox;
        f->cabeca->prox = pontIdEncontrado->prox;
        pontIdEncontrado->prox->ant = f->cabeca;
        free(pontIdEncontrado);
        return true;
    }

    else if (f->cabeca->prox == pontIdEncontrado){ //(III) o elemento buscado é o primeiro da fila e é prefencial
        f->cabeca->prox = pontIdEncontrado->prox;
        pontIdEncontrado->prox->ant = f->cabeca;
        free(pontIdEncontrado);
        return true;
    }

    else{ //(IV) demais casos
    pontIdEncontrado->prox->ant = pontIdEncontrado->ant;
    pontIdEncontrado->ant->prox = pontIdEncontrado->prox;
    free(pontIdEncontrado);
    return true;
    }
}


int main() {
	PFILA f = criarFila();
	int id;
	bool ehPreferencial;
	bool res;

	printf("################# INSERINDO #######################\n");

	exibirLog(f);
	res = inserirPessoaNaFila(f, -1, false);
	if(res) printf("Insercao retornou true (0).\n");
	else printf("Insercao retornou false (0). [OK]\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 1, false);
	if(res) printf("Insercao retornou true (1). [OK]\n");
	else printf("Insercao retornou false (1).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 2, false);
	if(res) printf("Insercao retornou true (2). [OK]\n");
	else printf("Insercao retornou false (2).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 3, false);
	if(res) printf("Insercao retornou true (3). [OK]\n");
	else printf("Insercao retornou false (3).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 4, true);
	if(res) printf("Insercao retornou true (4). [OK]\n");
	else printf("Insercao retornou false (4).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 5, true);
	if(res) printf("Insercao retornou true (5). [OK]\n");
	else printf("Insercao retornou false (5).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 6, true);
	if(res) printf("Insercao retornou true (6). [OK]\n");
	else printf("Insercao retornou false (6).\n");
	exibirLog(f);


	printf("################# ATENDENDO #######################\n");
	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (7), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (7).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (8), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (8).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (9), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (9).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (10), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (10).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (11), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (11).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (12), id=%i. [OK]\n",id);
	else printf("Atendimento retornou false (12).\n");

	exibirLog(f);
	res = atenderPrimeiraDaFila(f, &id);
	if(res) printf("Atendimento retornou true (13), id=%i.\n",id);
	else printf("Atendimento retornou false (13). [OK]\n");
	exibirLog(f);



	printf("################# INSERINDO PARTE 2 ###############\n");

	exibirLog(f);
	res = inserirPessoaNaFila(f, 7, true);
	if(res) printf("Insercao retornou true (14). [OK]\n");
	else printf("Insercao retornou false (14).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 8, false);
	if(res) printf("Insercao retornou true (15). [OK]\n");
	else printf("Insercao retornou false (15).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 9, true);
	if(res) printf("Insercao retornou true (16). [OK]\n");
	else printf("Insercao retornou false (16).\n");
	exibirLog(f);
	res = inserirPessoaNaFila(f, 10, false);
	if(res) printf("Insercao retornou true (17). [OK]\n");
	else printf("Insercao retornou false (17).\n");
	exibirLog(f);


	printf("################# SAINDO DA FILA ##################\n");

	exibirLog(f);
	res = desistirDaFila(f, 6);
	if(res) printf("Desistindo da fila retornou true (18).\n");
	else printf("Desistindo da fila retornou false (18). [OK]\n");
	exibirLog(f);
	res = desistirDaFila(f, 7);
	if(res) printf("Desistindo da fila retornou true (19). [OK]\n");
	else printf("Desistindo da fila retornou false (19).\n");
	exibirLog(f);
	res = desistirDaFila(f, 8);
	if(res) printf("Desistindo da fila retornou true (20). [OK]\n");
	else printf("Desistindo da fila retornou false (20).\n");
	exibirLog(f);
	res = desistirDaFila(f, 9);
	if(res) printf("Desistindo da fila retornou true (21). [OK]\n");
	else printf("Desistindo da fila retornou false (21).\n");
	exibirLog(f);
	res = desistirDaFila(f, 10);
	if(res) printf("Desistindo da fila retornou true (22). [OK]\n");
	else printf("Desistindo da fila retornou false (22).\n");
	exibirLog(f);

	return 0;
}
