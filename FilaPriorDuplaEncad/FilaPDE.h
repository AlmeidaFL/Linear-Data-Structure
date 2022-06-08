/*
Autor: Luis Felipe Almeida Beserra Matos
Faculdade: PUCSP (Computacao)
Data: 08/06/2022
Descricao: Arquivo que contem TAD Fila duplamente encadeada (dinamica)
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ghost 36

typedef struct Celula{
    char item;
    int prioridade;
    struct Celula* next;
    struct Celula* pre;
}Celula;

typedef struct{
    Celula* inicio;
    Celula* fim;
    int tam;
}FilaP;

/*
Cria uma fila vazia
@return FilaP
*/
FilaP newFila(){
    FilaP A;
    A.inicio = NULL;
    A.fim = NULL;
    A.tam = 0;
    return A;
}

/*
Verifica se uma fila esta vazia
@param A FilaP
@return bool
*/
bool filaVazia(FilaP A){
    bool vazia = true;
    if(A.inicio != NULL) vazia = false;
    return vazia;
}

/*
Retorna o primeiro caracter da fila A
@param A FilaP
@return char
*/
char acessarFila(FilaP A){
    char item;

    if(A.inicio != NULL){
        item = A.inicio->item;
    }
    return item;
}

/*
Coloca um caracter no fim da fila
@param A FilaP
@param valor char
@param prioridade int
@return FilaP
*/
FilaP pushFila(FilaP A, char valor, int prioridade){
    Celula* aux, *nova;
    nova = (Celula *) malloc(sizeof(Celula));

    if(nova != NULL){
        nova->item = valor;
        nova->prioridade = prioridade;
        if(A.inicio == NULL){ //Lista vazia
            A.inicio = nova; A.fim = nova;
            nova->pre = NULL; nova->next = NULL;
        }else{
            aux = A.fim;
            aux->next = nova; 
            nova->pre = aux;
            nova->next = NULL;
            A.fim = nova;
        }
        A.tam++;
    }
    
    return A;
}

/*
Retira um caracter da fila conforme a prioridade
@param A FilaP
@return FilaP
*/
FilaP popFila(FilaP A){
    Celula* aux, *end;
    int maior;
    
    if(A.inicio != NULL){
        aux = A.inicio; end = aux;
        maior = aux->prioridade;
        while(aux->next != NULL){ //Busca sequencial para achar o item de maior prioridade
            aux = aux->next;
            if(aux->prioridade > maior){
                end = aux;
                maior = aux->prioridade;
            }
        }
        if(end->pre == NULL){ //Primeiro da lista
            if(end->next == NULL){ //So um item na lista
                A.fim = NULL; A.inicio = NULL; A.tam = 0;
            }else{ //Varios itens na lista
                aux = end->next;
                A.inicio = aux;
                aux->pre = NULL;
            }
        }else{
            if(end->next == NULL){ //Ultimo item da lista
                aux = end->pre; 
                aux->next = NULL;
                A.fim = aux;
            }else{ //Item no meio da lista
                aux = end->pre;
                aux->next = end->next;
                end->next->pre = aux;
            }
        }
        free(end);
        A.tam--;
    }

    return A;
}

/*
Esvazia a fila, limpando a memoria.
@param A FilaP
@return FilaP
*/
FilaP esvaziarFila(FilaP A){
    Celula *aux, *end;

    if(A.inicio != NULL){
        aux = A.inicio;
        while(aux != NULL){
            end = aux;
            aux = aux->next;
            free(end);
        }
        A.inicio = NULL; A.fim = NULL; A.tam = 0;
    }
}

/*
Busca o elemento com maior prioridade da fila, e coloca o novo char com prioridade maior
@param A FilaP
@param item char
@return FilaP
*/
FilaP furarFila(FilaP A, char valor){
    Celula* nova, *aux;
    int maior;

    if(A.inicio != NULL){
        nova = (Celula *) malloc(sizeof(Celula));
        nova->item = valor;
        aux = A.inicio; maior = aux->prioridade;
        while(aux != NULL){ //Buscando sequencialmente a maior prioridade
            if(aux->prioridade > maior) maior = aux->prioridade;
            aux = aux->next;
        }
        nova->pre = NULL;
        A.inicio->pre = nova;
        nova->next = A.inicio;
        A.inicio = nova;
        nova->prioridade = maior+1;
    }

    return A;
}

/*
Verifica se uma fila esta vazia
@return bool
*/
void mostrarFila(FilaP A){
    Celula* aux;
    
    if(A.inicio != NULL){
        aux = A.inicio;
        while(aux != NULL){
            printf("%c ", aux->item);
            aux = aux->next;
        }
        printf("\n");
    }
}