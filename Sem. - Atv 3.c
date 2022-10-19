#include <stdio.h>
#include <stdlib.h>

typedef struct aux{
    int id;
    struct aux* mae;
    struct aux* pai;
    } PESSOA;

void registrar(PESSOA* filho, PESSOA* mae, PESSOA* pai){
  filho -> mae = &mae;
  filho -> pai = &pai;
  return 0;
}

int main(){

    PESSOA mae;
    mae.id = 123;

    PESSOA pai;
    pai.id = 456;

    PESSOA filho;
    filho.id = 789;

registrar(&filho, &mae, &pai);

printf("ID da mae: %i\n",filho.mae->id);

}
