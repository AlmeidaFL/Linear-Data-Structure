#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define Max 10

typedef struct{
    int tamanho;
    int tab[Max];
}Heap;

void restauraHeapAcima(Heap *A, int pai, int filho);
void trocar(Heap *lista, int indiceA, int indiceB);
void inserirHeap(Heap *A, int valor);
Heap criarHeapMaxima();
void restauraHeapAbaixo(Heap* A, int pai);

Heap criarHeapMaxima(){
    Heap A;
    A.tamanho = 0;
    return A;
}

void inserirHeap(Heap *A, int valor){
    if(A->tamanho < Max){
        int indice = ++A->tamanho;
        A->tab[indice] = valor;
        restauraHeapAcima(A, floor(indice/2), indice);
    }
}

void restauraHeapAcima(Heap *A, int pai, int filho){
    if((filho > 1) && (pai != 0)){
        int valorFilho = A->tab[filho]; 
        int valorPai = A->tab[pai];
        if(valorFilho > valorPai){
            trocar(A, pai, filho);
            restauraHeapAcima(A, floor(pai/2), floor(filho/2));
        }
    }
}

void trocar(Heap *lista, int indiceA, int indiceB){
    if(lista->tamanho >= 2){
        int valor = lista->tab[indiceA];
        lista->tab[indiceA] = lista->tab[indiceB];
        lista->tab[indiceB] = valor;
    }
}

void retirarPrimeiro(Heap* A){
    if(A->tamanho >= 1){
        A->tab[A->tamanho];
        A->tab[1] = A->tab[A->tamanho];
        --A->tamanho;
        restauraHeapAbaixo(A, 1);
    }
}

void restauraHeapAbaixo(Heap* A, int pai){
    if(A->tamanho >= 2){
        int filhoEsq = pai*2;
        if(filhoEsq <= A->tamanho){
            int filhoDir = pai*2+1;
            int indice = filhoEsq;
            if(filhoDir <= A->tamanho){
                if(A->tab[filhoDir] > A->tab[filhoEsq]) indice = filhoDir;
            }
            if(A->tab[indice] > A->tab[pai]){
                trocar(A, pai, indice);
                restauraHeapAbaixo(A, indice);
            }
        }
    }
}
