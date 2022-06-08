/*
Autor: Luis Felipe Almeida Beserra Matos
Faculdade: PUCSP (Computacao)
Data: 08/06/2022
Descricao: Arquivo que contem TAD Fila encadeada (dinamica)
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Celula{
    struct Celula* next;
    int prioridade;
    char* item;
}Celula;

typedef Celula* Fila;

/*
Cria uma fila vazia
@return Fila
*/
Fila criarFila(){
    Fila A;
    A = NULL;
    return A;
}

/*
Coloca uma string no fim da fila
@param A Fila
@param item char*
@param prioridade int
@return Fila
*/
Fila pushFila(Fila A, char* item, int prioridade){
    Celula* nova, *aux;
    nova = (Celula*) malloc(sizeof(Celula));

    if(nova != NULL){
        nova->item = item;
        nova->prioridade = prioridade;
        if(A == NULL){
            A = nova;
            nova->next = nova;
        }else{
            aux = A;
            while(aux->next != A){
                aux = aux->next;
            }
            aux->next = nova;
            nova->next = A;
        }
    }

    return A;
}

/*
Retira uma string da fila conforme a prioridade
@param A Fila
@return Fila
*/
Fila popFila(Fila A){
    Celula* aux, *confirmaEnd;
    int maior;

    if(A != NULL){
        aux = A; maior = A->prioridade;
        while(aux->next != A){
            if(aux->next->prioridade > maior){
                 confirmaEnd = aux;
                 maior = aux->next->prioridade;
            }
            aux = aux->next;
        }
        if(A->next == A){
            free(aux);
            A = NULL;
        }else{
            if(maior == A->prioridade){ //Maior prioridade no comeco da lista
                aux->next = A->next;
                aux = A;
                A = A->next;
            }else{
                aux = confirmaEnd->next;
                confirmaEnd->next = aux->next;
            }
            free(aux);
        }
    }

    return A;
}

/*
Busca o elemento com maior prioridade da fila, e coloca a nova string com prioridade maior
@param A Fila
@param item char*
@return Fila
*/
Fila furaFila(Fila A, char* item){
    Celula *aux, *nova;
    int prioridade = 0;

    nova = (Celula *) malloc(sizeof(Celula));

    if((A != NULL) && (nova != NULL)){
        nova->item = item;
        aux = A; prioridade = A->prioridade;
        while(aux->next != A){
            aux = aux->next;
            if(aux->prioridade > prioridade) prioridade = aux->prioridade;
        }
        nova->next = A;
        nova->prioridade = prioridade+1;
        A = nova;
        aux->next = A;
    }

    return A;
}

/*
Verifica se uma fila esta vazia
@return bool
*/
bool filaVazia(Fila A){
    bool vazia = true;
    if(A != NULL) vazia = false;
    return vazia;
}

/*
Esvazia a fila, limpando a memoria.
@param A Fila
@return Fila
*/
Fila esvaziarFila(Fila A){
    Celula* aux = NULL, *end;

    if(A != NULL){
        end = A->next;
        while(aux != A){
            aux = end;
            end = end->next;
            free(end);
        }
        A = NULL;
    }
}

/*
Mostra a fila A no console em formato texto
@param A Fila
@return void
*/
void mostrarFila(Fila A){
    Celula* aux;

    if(A == NULL) printf("Fila Vazia\n");
    else{
        aux = A;
        printf("%s ", aux->item);
        while(aux->next != A){
            aux = aux->next;
            printf("%s ", aux->item);
        }
        printf("\n");
    }
}