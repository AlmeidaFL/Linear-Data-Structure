/*
Autor: Luis Felipe Almeida Beserra Matos
Faculdade: PUCSP (Computacao)
Data: 08/06/2022
Descricao: Arquivo que contem o TAD Polinomio, com funcoes de soma e multiplicacao (nao incluindo a divisao)
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define fantasma -1

typedef struct Tipo{
    int item;
    struct Tipo *next;
}Tipo;

typedef struct{
    int tam;
    Tipo *inicio;
}Lista;

Lista criarLista(){
    Lista L;
    L.inicio = NULL;
    L.tam = 0;
    return L;
}

void inserirLista(Lista* L, int valor){
    Tipo *aux;
    aux = (Tipo *) malloc(sizeof(Tipo));
    aux->item = valor;
    aux->next = L->inicio;
    L->inicio = aux;
    L->tam++;
}

bool verListaVazia(Lista L){
    bool vazia = true;
    if(L.inicio != NULL) vazia = true;
    return vazia;
}

void removerPrimeiro(Lista *L){
    Tipo *aux;
    if(L->inicio != NULL){
        aux = L->inicio->next;
        free(L->inicio) ;
        L->inicio = aux;
        L->tam--;
    }
}
/*
int obterTamanho(Lista *L){
    return L->tam;
}*/

void removerUltimo(Lista *L){
    Tipo *prim, *aux, *endereco;
    if(L->inicio != NULL){ 
        if(L->inicio->next == NULL){ //Quando so temos um item na lista
            L->inicio = NULL;
        }else{ //Mais de um item
            aux = L->inicio; 
            do{
                prim = aux->next->next;
                if(prim != NULL) aux = aux->next;
            }while(prim != NULL);
            free(aux->next);
            aux->next = NULL;
            L->tam--;
        }
    }
}

int obterElemento(Lista *L, int valor){
    Tipo *aux, *end; int cont = 0;
    int retorno = fantasma;

    if((L->inicio != NULL) && (valor <= L->tam) && (valor > 0)){
        aux = L->inicio;
        while(cont < valor){
            end = aux;
            aux = aux->next;
            cont++;
        } 
        if(cont == valor) retorno = end->item; 
    }

    return retorno;
}

bool itemDuplicado(Lista A, int valor){
    bool duplicado = false;
    Tipo *aux;

    if(A.inicio != NULL){
        aux = A.inicio;
        while((duplicado == false) && (aux != NULL)){
            if(aux->item == valor) duplicado = true;
            aux = aux->next;
        }
    }

    return duplicado;
}

void esvaziarLista(Lista *A){
    Tipo *aux;

    if(A->inicio != NULL){
        Tipo *lixo;
        aux = A->inicio;
        while(aux != NULL){
            lixo = aux;
            aux = aux->next;
            free(lixo);
        }
    }
}
