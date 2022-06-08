/*
Autor: Luis Felipe Almeida Beserra Matos
Faculdade: PUCSP (Computacao)
Data: 08/06/2022
Descricao: Arquivo que contem TAD Fila
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define sinal -1
#define MaxFila 3
#define ghost 999

typedef struct{
    int inicio;
    int fim;
    int item[MaxFila];
}t_Fila;

typedef t_Fila* Fila;

Fila criarFilaVazia();
int acessarInicio(Fila);
bool verificarFilaVazia(Fila);
bool verificarFilaCheia(Fila);
void pushFila(Fila, int);
void popFila(Fila);
void esvaziarFila(Fila);

/*
Cria uma fila vazia
@return Fila
*/
Fila criarFilaVazia(){
    Fila A;
    A = (t_Fila *) malloc(sizeof(t_Fila));
    A->inicio = sinal;
    A->fim = sinal;
    return A;
}

/*
Retorna o item no inicio da fila 
@param A Fila
@return int
*/
int acessarInicio(Fila A){
    int valor = ghost;
    if(A->inicio != sinal) valor = A->item[A->inicio];
    return valor;
}

/*
Verifica se uma lista esta vazia
@param Fila
@return bool
*/
bool verificarFilaVazia(Fila A){
    bool vazia = true;
    if(A->inicio != sinal) vazia = false;
    return vazia;
}

/*
Verifica se uma lista esta cheia
@param Fila
@return bool
*/
bool verificarFilaCheia(Fila A){
    bool cheia = true;
    int aux = (A->inicio + 1) % MaxFila;
    if(aux != A->fim) cheia = false;
    return cheia;
}

/*
Insere um valor no fim da fila A
@param A Fila
@param valor int
@return void
*/
void pushFila(Fila A, int valor){
    int seg;

    seg = (A->fim + 1) % MaxFila;

    if(seg != A->inicio){
        A->item[seg] = valor;
        if(A->inicio == sinal) A->inicio = seg;
        A->fim = seg;
    }
}

/*
Remove um valor no inicio da fila A
@param A Fila
@return void
*/
void popFila(Fila A){
    int seg = (A->inicio + 1) % MaxFila;

    if(A->inicio != sinal){
        if(A->inicio == A->fim){
            A->inicio = sinal;
            A->fim = sinal;
        }else{
            A->inicio = seg;
        }
    }
}

/*
Fura a fila, colocando um valor no inicio da fila
@param A Fila
@param valor int
@return void
*/
void furaFila(Fila A, int valor){
    int seg = (A->inicio - 1) % MaxFila;
    if(seg < 0) seg += MaxFila;

    if(A->inicio != sinal){
        if(seg != A->fim){
            A->item[seg] = valor;
            A->inicio = seg;
        }
    }
}

/*
Mostra a fila no console em formato texto
@return void
*/
void mostrarFila(Fila A){
    int k = A->inicio - 1;

    if(A->inicio == sinal) printf("Fila vazia\n");
    else{
        do{
            k = (k + 1) % MaxFila;
            printf("%d ", A->item[k]);
        }while(k != A->fim);
        printf("\n");
    }
}