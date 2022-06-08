#include <stdio.h>
#include <stdlib.h>

#define ghost '$'

typedef struct Celula{
    unsigned char item;
    struct Celula* next;
}Celula;

typedef Celula* Pilha;

Pilha criarPilha();
Pilha pushPilha(Pilha A, int item);
Pilha popPilha(Pilha A);
void mostrarPilha();
Pilha esvaziarPilha(Pilha A);

Pilha criarPilha(){
    Pilha A;
    A = NULL;
    return A;
}

Pilha pushPilha(Pilha A, int item){
    Celula* aux, *nova;

    nova = (Celula *) malloc(sizeof(Celula));

    if(nova != NULL){
        nova->item = item;
        if(A == NULL){
            nova->next = A;
            A = nova;
        }else{
            aux = A;
            while(aux->next != NULL){
                aux = aux->next;
            }
            nova->next = NULL;
            aux->next = nova;
        }
    }

    return A;
}

Pilha popPilha(Pilha A){
    Celula* aux, *pre;

    if(A != NULL){
        if(A->next == NULL){
            aux = A;
            A = NULL;
            free(aux);
        }else{
            aux = A;
            while(aux->next != NULL){
                pre = aux;
                aux = aux->next;
            }
            pre->next = NULL;
            free(aux);
        }
    }

    return A;
}

void mostrarPilha(Pilha A){
    Celula* aux;

    if(A != NULL){
        aux = A;
        while(aux != NULL){
            printf("%d\n", aux->item);
            aux = aux->next;
        }
        printf("\n");
    }
}