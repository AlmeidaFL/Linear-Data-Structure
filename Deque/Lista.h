/*
Autor: Luis Felipe Almeida Beserra Matos
Faculdade: PUCSP (Computacao)
Data: 08/06/2022
Descricao: Arquivo que contem TAD Deque (inserir e remover no comeco e no final)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Celula{
    struct Celula* next;
    int item;
}Celula;

typedef Celula* Lista;

Lista criarLista(){
    Lista A;
    A = NULL;
    return A;
}
/*
Lista inserirInicio(Lista A, int valor){
    Celula* nova, *pre,*aux;

    nova = (Celula *) malloc(sizeof(Celula));

    if(nova != NULL){
        nova->item = valor;

        aux = A;
        do{
            aux = aux->next;
        }while(aux->next != A);

        if(aux == aux->next);
    }
    return A;
}
*/

/*
Insere um valor no fim da lista
@param A Lista
@param valor int
*/
Lista inserirFim(Lista A, int valor){
    Celula* nova, *aux;

    nova = (Celula *) malloc(sizeof(Celula));
    nova->item = valor;

    if(A == NULL){
        nova->next = NULL;
        A = nova;
    }else{
        aux = A;
        while(aux->next != A){
            aux = aux->next;
        }
        aux->next = nova;
        nova->next = A;
    }

    return A;
}

/*
Remove um valor do inicio da lista
@param A Lista
@return Lista
*/
Lista removerInicio(Lista A){
    Celula* aux;

    if(A != NULL){
        aux = A;
        if(A->next == A){
            A = NULL;
        }else{
            A = A->next;
        }
        free(aux);
    }

    return A;
}

/*
Remove um valor do fim da lista
@param A Lista
@return Lista
*/
Lista removerFim(Lista A){
    Celula* aux, *pre;

    if(A != NULL){
        aux = A;
        if(A->next != A){
            A = NULL;
        }else{
            while(aux->next != A){
                pre = aux;
                aux = aux->next;
            }
            pre->next = aux->next;
        }
        free(aux);
    }

    return A;
}

/*
Insere um item apos uma celula 'cel'
@param A Lista
@param cel Celula*
@param valor int
@return Lista
*/
Lista inserirApos(Lista A, Celula* cel, int valor){
    Celula *aux, *pre, *nova;
    bool achou = false;

    if(A != NULL){
        nova = (Celula *) malloc(sizeof(Celula));
        nova->item = valor;

        aux = A; pre = NULL;
        do{
            if(aux == cel){
                pre = aux;
                achou = true;
            }
            aux = aux->next;
        }while(aux->next != A);

        if(achou){
            nova->next = pre->next;
            pre->next = nova;
        }
    }

    return A;
}

/*
Insere um item antes de uma celula 'cel'
@param A Lista
@param cel Celula*
@param valor int
@return Lista
*/
Lista inserirAntes(Lista A, Celula* cel, int valor){
    Celula *aux, *pre, *nova;
    bool achou = false;

    if(A != NULL){
        nova = (Celula *) malloc(sizeof(Celula));
        nova->item = valor;

        aux = A;
        do{
            if(aux->next == cel){
                pre = aux;
                achou = true;
            }
            aux = aux->next;
        }while(aux != A);

        if(achou){
            if(pre->next == cel) A = nova;
            nova->next = cel;
            pre->next = nova;
        }
    }

    return A;
}

/*
Mostra a lista no console
@param A Lista
@return void
*/
void mostrarLista(Lista A){
    Celula* aux;

    if(A != NULL){
        aux = A->next;
        do{
            printf("%d ", aux->item);
            aux = aux->next;
        }while(aux != A);

        printf("\n");
    }
}