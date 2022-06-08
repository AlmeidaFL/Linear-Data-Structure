/*
Autor: Luis Felipe Almeida Beserra Matos
Faculdade: PUCSP (Computacao)
Data: 08/06/2022
Descricao: Arquivo que contem TAD Lista duplamente encadeada (dinamica). Insere em ordem decrescente
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NULO NULL
#define ghost -1

typedef struct Celula{
    int valor;
    struct Celula* pre;
    struct Celula* next;
}Celula;

typedef struct{
    int tam;
    Celula* inicio;
    Celula* fim;
}Lista;

/*
Cria uma lista vazia
@return Lista
*/
Lista criarLista(){
    Lista A;
    A.inicio = NULL;
    A.fim = NULL;
    A.tam = 0;
    return A;
}

/*
Retorna o tamanho da lista
@param A Lista
@return int
*/
int determinarTamanho(Lista A){
    return A.tam;
}

/*
Verifica se a lista esta vazia
@param A Lista
@return bool
*/
bool listaVazia(Lista A){
    bool vazia = true;
    if(A.inicio != NULL) vazia = false;
    return vazia;
}

/*
Insere um inteiro na lista em ordem decrescente
@param A Lista
@param int valor
@return Lista
*/
Lista buscaInsere(Lista A, int valor){
    Celula* atual, *pre, *nova;

    nova = (Celula *) malloc(sizeof(Celula));
    nova->valor = valor;

    if((A.inicio == NULL) || (A.inicio->valor < valor)){//Inserçao no inicio
        nova->pre = NULL;
        nova->next = A.inicio;
        if(A.inicio == NULL) A.fim = nova;
        else A.inicio->pre = nova; //Quando tem uma celula que vai estar na "frente" da nova
        A.inicio = nova;
    }else{ 
        atual = A.inicio;
        while((atual->next != NULL) && (atual->valor > valor)){
            atual = atual->next;
        }
        if(atual->next == NULL){
            atual->next = nova;
            nova->pre = atual;
            nova->next = NULL;
            A.fim = nova;
        }else{
            pre = atual->pre;
            pre->next = nova;
            nova->pre = pre;
            nova->next = atual;
            atual->pre = nova;
        }
    }
    A.tam++;

    return A;
}

/*
Mostra a lista no console no formato decrescente
@param A Lista
@return void
*/
void mostrarListaED(Lista A){
    Celula* aux;

    if(A.inicio == NULL) printf("Lista vazia\n");
    else{
        aux = A.inicio;
        while(aux != NULL){
            printf("%d ", aux->valor);
            aux = aux->next;
        }
        printf("\n");
    }
}

/*
Mostra a lista no console no formato crescente
@param A Lista
@return void
*/
void mostrarListaDE(Lista A){
    Celula *aux;
    
    if(A.inicio == NULL) printf("Lista vazia\n");
    else{
        aux = A.fim;
        while(aux != NULL){
            printf("%d ", aux->valor);
            aux = aux->pre;
        }
        printf("\n");
    }
}

/*Retorna o endereco da celula que contem o 'valor'
@param A Lista
@param valor int
@return enderco Celula*
*/
Celula* buscarItem(Lista A, int valor){
    Celula* aux, *retorno = NULO;
    bool achou = false;

    if(A.inicio != NULL){
        aux = A.inicio;
        while((aux != NULL) && (achou == false)){
            if(aux->valor == valor) achou = true;
            aux = aux->next;
        }
        if(achou) retorno = aux->pre;
    }

    return retorno;
}

/*
Remove todas as duplicatas do valor passado pelo parametro
@param A Lista
@param valor int
@return Lista
*/
Lista removerDuplicata(Lista A, int valor){
    Celula* pre, *atual, *temp, *pos, *remover;
    bool achou = false;

    if(A.tam >= 2){
        pre = A.inicio;
        while((pre != NULL) && (achou == false)){
            if(pre->valor == valor){
                achou = true;
            }
            else pre = pre->next;
        }
        if((achou) && (pre->next != NULL)){
            atual = pre->next;
            do{
                pre = atual;
                atual = pre->next;
                if(pre->valor == valor){
                    temp = pre->pre;
                    temp->next = pre->next;
                    pos = pre->next;
                    if(pos != NULL) pos->pre = temp;
                    free(pre);
                }
            }while(atual != NULL);

            //Redefinindo o fim
            atual = A.inicio;
            while(atual->next != NULL){
                atual = atual->next;
            }
            A.fim = atual;
        }
    }

    return A;
}

/*Remove uma celula da lista conforme o valor passado no parametro
@param A Lista
@param valor int
@param A Lista
*/
Lista removerItem(Lista A, int valor){
    Celula* aux, *pre, *pos;
    bool achou = false;

    if(A.inicio != NULL){
        aux = A.inicio;
        while((aux != NULL) && (achou == false)){
            if(aux->valor == valor) achou = true;
            else aux = aux->next;
        }
        if(achou){
            if(aux->next == NULL){
                if(aux->pre == NULL){ //Um item na lista
                    A.inicio = NULL;
                    A.fim = NULL;
                }else{ //Ultimo item da lista
                    A.fim = aux->pre;
                    aux->pre->next = NULL;
                }
            }else if(aux->pre == NULL){ //Primeiro item na lista
                A.inicio = aux->next;
                aux->next->pre = NULL;
            }
            else{ //Meio da lista
                pre = aux->pre; pos = aux->next;
                pre->next = pos;
                pos->pre = pre;
            }
            free(aux);
            A.tam--;
        }
    }

    return A;
}

/*Retorna um inteiro baseado na ordem/posicao dele na lista
@param A Lista
@param ordem int
@return int
*/
int obterItemK(Lista A, int ordem){
    int contador = 1;
    int valor = ghost;
    Celula* aux;

    if(ordem <= A.tam){
        aux = A.inicio;
        while(contador < ordem){
            aux = aux->next;
            contador++;
        }
        valor = aux->valor;
    }

    return valor;
}

/*
Inverte a Lista
@param A Lista
@return Lista
*/
Lista inverterLista(Lista A){
    Celula* pre, *atual, *pos;
    Celula* temp;

    if(A.tam >= 2){
        atual = A.inicio; pos = atual;
        while(pos != NULL){
            pos = pos->next;
            pre = atual;
            temp = pre->pre;
            pre->pre = pre->next;
            pre->next = temp;
            atual = pos;
        }
        temp = A.inicio;
        A.inicio = A.fim;
        A.fim = temp;
    }

    return A;
}

/*
Esvazia a lista, liberando a memoria
@param A Lista
@return Lista
*/
Lista esvaziarLista(Lista A){
    Celula* atual, *aux;

    if(A.inicio != NULL){
        atual = A.inicio;
        while(atual != NULL){
            aux = atual;
            atual = atual->next;
            free(aux);
        }
        A.inicio = NULL;
        A.fim = NULL;
        A.tam = 0;
    }
}
/*
Retorna true se o item passado no parametro ja esta na lista
*/
bool itemDuplicado(Lista A, int valor){
    bool duplicado = false;
    Celula *aux;

    if(A.inicio != NULL){
        aux = A.inicio;
        while((aux != NULL) && (duplicado == false)){
            if(aux->valor == valor) duplicado = true;
            aux = aux->next;
        }
    }

    return duplicado;
}