/*
Autor: Luis Felipe Almeida Beserra Matos
Faculdade: PUCSP (Computacao)
Data: 08/06/2022
Descricao: Arquivo que contem TAD Lista encadeada (dinamica) normal sem cabeca
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define fantasma '$'

typedef struct Celula{
    char item;
    struct Celula* next;
}Celula;

typedef Celula* Lista;

Lista newLista(){
    Lista L = NULL;
    return L;
}

/*
Verifica se uma lista esta vazia
@return bool
*/
bool ListaVazia(Lista L){
    bool vazia = true;
    if(L != NULL) vazia = false;
    return vazia;
}

/*
Insere um char 'valor' na lista L 
@param L Lista
@param valor char
@return Lista
*/
Lista inserirLista(Lista L, char valor){
    Celula *novo;
    novo = (Celula *) malloc(sizeof(Celula));
    novo->item = valor;
    novo->next = L;
    L = novo;
    return L;
}

/*
Retorna o tamanho da lista L
@param L Lista
@return int
*/
int obterTamanho(Lista L){
    int tam = 0;
    Celula *aux;

    if(L != NULL){
        aux = L;
        while(aux != NULL){
            tam++;
            aux = aux->next;
        }
    }

    return tam;
}

/*
Retorna o char contido na posicao/ordem 'valor
@param L Lista
@param valor int
@return char
*/
char obterElemento(Lista L, int valor){
    int contador = 1;
    Celula *aux, *vlr;
    char retorno = fantasma;

    aux = L; vlr = aux;
    while((aux != NULL) && (contador <= valor)){
        vlr = aux;
        aux = aux->next;            
        contador++;
    }
    if((vlr != NULL) && (valor == contador-1)) retorno = vlr->item; 

    return retorno;
}

/*
Mostra a lista L no console
@param L Lista
*/
void mostrarLista(Lista L){
    Celula *aux;

    if(L != NULL){
        aux = L;
        while(aux != NULL){
            printf("%c ", aux->item);
            aux = aux->next;
        }
    }
    printf("\n");

}

/*
Busca um item na lista correspondete ao parametro 'valor'
@param L Lista
@param valor char
@return Celula*
*/
Celula* buscarItem(Lista L, char valor){
    Celula *aux = NULL;
    bool sentinela = false;

    if(L != NULL){
        aux = L;
        while((aux != NULL) && (sentinela == false)){
            if(aux->item == valor) sentinela = true;
                else aux = aux->next;
        }
    }

    return aux;
}

/*
Remove a primeira celula da lista L
@param L Lista
@return Lista
*/
Lista removerPrimeiro(Lista L){
    Celula *aux;

    if(L != NULL){
        aux = L;
        L = L->next;
        free(aux);
    }

    return L;
}

/*
Esvazia a lista, liberando a memoria
@param L Lista
@return Lista
*/
Lista esvaziarLista(Lista L){
    Celula *aux;
    
    if(L != NULL){
        while(L != NULL){
            aux = L;
            L = L->next;
            free(aux);
        }
    }

    return L;
}

/*
Remove a ultima celula da lista L
@param L Lista
@return Lista
*/
Lista removerUltimo(Lista L){
    Celula* aux, *prox;
    
    if(L != NULL){
        aux = L; prox = aux;
        while(prox->next != NULL){
            aux = prox;
            prox = prox->next;
        }
        if(prox->next == NULL && prox != aux){ //Mais de um item na lista
            aux->next = NULL;
            free(prox);   
        }else{ //So um item na lista
            free(aux);
            L = NULL;
        }
    }

    return L;
}