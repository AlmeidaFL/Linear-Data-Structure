/* Arquivo: Luis_Felipe_ListaP.h
   Autor: Luis Felipe Almeida Beserra Matos, Jonas Edward Tashiro
   Date: 21/04/2022
   Descricao: Arquivo contendo TAD ListaP com funções semelhantes ao tipo list da linguagem
   Python.
*/

#include <stdio.h>
#define Max 11
#define fantasma '$'

typedef struct{
    int tam;
    unsigned char vetor[Max];
}ListaP;

ListaP newLista();
unsigned char acessar(ListaP, int);
void append(ListaP *, unsigned char);
void clear(ListaP *);
ListaP copy(ListaP);
int count(ListaP, unsigned char);
int indexI(ListaP, unsigned char);
int len(ListaP);
ListaP extend(ListaP, ListaP);
unsigned char max(ListaP);
unsigned char min(ListaP);
void pop(ListaP *, int );
void remover(ListaP *, unsigned char);
void reverse(ListaP *);
void sort(ListaP *);
void insert(ListaP *, unsigned char, int);

/*
Cria uma lista vazia
@return ListaP
*/
ListaP newLista(){
    ListaP lista;
    lista.tam = 0;
    return lista;
}

/*
Retorna um elemento da lista baseado no indice
@param lista ListaP
@param indice int
@return unsigned char
*/
unsigned char acessar(ListaP lista, int indice){
    int i;
    unsigned char valor = fantasma;

    if((indice >= 0) && (indice < lista.tam)){
        valor = lista.vetor[indice];
    }else{
        i = lista.tam - indice;
        if(i >= 0)
            valor = lista.vetor[i];
    }

    return valor;
}

/*
Acrescente um item no fim da lista
@param lista ListaP*
@param valor unsigned char
@return void
*/
void append(ListaP *lista, unsigned char valor){
    int tam = lista->tam;

    if(tam < Max){
        lista->vetor[tam] = valor;
        lista->tam++;
    }
}

/*
Esvazia a lista
@param lista ListaP*
@return void
*/
void clear(ListaP *lista){
    lista->tam = 0;
}

/*
Retorna a lista copiada
@return ListaP
*/
ListaP copy(ListaP lista){
    ListaP retorno;

    retorno = newLista();

    if(lista.tam > 0){
        for(int i = 0; i < lista.tam; i++){
            retorno.vetor[i] = lista.vetor[i];
        }
    }
    retorno.tam = lista.tam;

    return retorno;
}

/*
Retorna a quantidade de elementos iguais ao 'valor'
@param lista ListaP
@param valor unsigned char
@return int
*/
int count(ListaP lista, unsigned char valor){
    int qtd = 0;

    if(lista.tam > 0){
        for(int i = 0; i < lista.tam; i++){
            if(lista.vetor[i] == valor)
                qtd++;
        }
    }

    return qtd;
}

/*
Concatena duas listas A e B e retorna a lista concatenada
@param listaA ListaP
@param listaB ListaP
@return ListaP
*/
ListaP extend(ListaP listaA, ListaP listaB){
    ListaP listaC;
    int tamC = listaA.tam + listaB.tam;

    for(int i = 0; i < listaA.tam; i++){
        listaC.vetor[i] = listaA.vetor[i];
    }
    for(int j = 0; j < listaB.tam; j++){
        listaC.vetor[j+listaA.tam] = listaB.vetor[j];
    }

    listaC.tam = tamC;
    return listaC;
}

/*
Retorna o indice onde esta localizado o elemento 'valor'
@param valor unsigned char
@return int
*/
int indexI(ListaP lista, unsigned char valor){
    int indice = fantasma;
    int i = 0;

    if(lista.tam > 0){
        while(i < lista.tam && lista.vetor[i] != valor){
            i++;
        }
        if(lista.vetor[i] == valor)
            indice = i;
    }

    return indice;
}

/*
Retorna a quantidade de elementos na lista
@return int
*/
int len(ListaP lista){
    return lista.tam;
}

/*
Retorna o maior elemento da lista
@return unsigned char
*/
unsigned char max(ListaP lista){
    unsigned char maior = fantasma;

    if(lista.tam > 0){
        maior = lista.vetor[0];
        for(int i = 1; i < lista.tam; i++){
            if(lista.vetor[i] > maior)
                maior = lista.vetor[i];
        }
    }
    return maior;
}

/*
Retorna o menor elemento da lista
@return unsigned char
*/
unsigned char min(ListaP lista){
    unsigned char menor = fantasma;

    if(lista.tam > 0){
        menor = lista.vetor[0];
        for(int i = 1; i < lista.tam; i++){
            if(lista.vetor[i] < menor)
                menor = lista.vetor[i];
        }
    }
    return menor;
}

/*
Remove um elemento localizado no indice passado no parametro
@param indice int
@return void
*/
void pop(ListaP *lista, int indice){

    if(lista->tam > 0){
        if(indice < lista->tam && indice >= 0){
            for(int i = indice; i < lista->tam-1;i++){
                lista->vetor[i] = lista->vetor[i+1];
            }
            lista->tam--;
        }
    }
}

/*
Remove um elemento baseado no valor passado no parametro
@param valor int
@return void
*/
void remover(ListaP *lista, unsigned char valor){

    if(lista->tam >= 0){
        int indice = indexI(*lista, valor);
        pop(lista, indice);
    }

}

/*
Inverte a lista
*/
void reverse(ListaP *lista){
    int tam = (lista->tam-1)/2;
    int aux, c = lista->tam-1;

    for(int i = 0; i <= tam; i++){
        aux = lista->vetor[i];
        lista->vetor[i] = lista->vetor[c];
        lista->vetor[c] = aux;
        c--;
    }
}

/*
Ordena a lista por meio do inserction sort
*/
void sort(ListaP *lista){
    int k,n,aux;
    n = lista->tam-1;

    for(int i = 1; i <= n; i++){
        aux = lista->vetor[i];
        k = i-1;

        while ((k >= 0) && (lista->vetor[k] > aux)) {
            lista->vetor[k+1] = lista->vetor[k];
            k = k - 1;
        }
        lista->vetor[k+1] = aux;
    }
}

/*
Insere um elemento no indice passado como parametro, sem remover o valor contido nele
@param valor unsigned char
@param indice int
@return void
*/
void insert(ListaP *lista, unsigned char valor, int indice){

    if(lista->tam < Max){
        for(int i = lista->tam; i > indice; i--){
            lista->vetor[i] = lista->vetor[i-1];
        }
        lista->tam++;
        lista->vetor[indice] = valor;
    }
}