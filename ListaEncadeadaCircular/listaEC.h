/*
Autor: Luis Felipe Almeida Beserra Matos
Faculdade: PUCSP (Computacao)
Data: 08/06/2022
Descricao: Arquivo que contem TAD Lista encadeada circular (dinamica) normal sem cabeca
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ghost -1

typedef struct Celula{
    int valor;
    struct Celula* next;
}Celula;

typedef Celula* Lista;

Lista criarLista();
int determinarTamanho(Lista);
bool listaVazia(Lista);
void mostrarLista(Lista);
Celula* buscarItem(Lista, int);
int obterItemK(Lista, int);
Lista insere(Lista, int);
Lista removerItem(Lista, int);
Lista esvaziarLista(Lista);

/*
Cria uma lista vazia
@return Lista
*/
Lista criarLista(){
    Lista A;
    A = NULL;
    return A;
}

/*
Retorna o tamanho da lista A
@param A Lista
@return int
*/
int determinarTamanho(Lista A){
    int qtd = 0;
    Celula *pos;

    if(A != NULL){
        if(A->next != A){ //Mais de um elemento na lista
            pos = A->next; 
            qtd++;
            while(pos != A){
                pos = pos->next;
                qtd++;
            }

        }else qtd++; //So um elemento na lista
    }

    return qtd;
}

/*
Verifica se a lista esta vazia
@param A Lista
@return bool
*/
bool listaVazia(Lista A){
    bool vazia = true;
    if(A != NULL) vazia = false;
    return vazia;
}

/*
Mostra a lista no console 
@param A Lista
*/
void mostrarLista(Lista A){
    Celula* aux;

    if(A != NULL){
        if(A->next != A){
            printf("%d ", A->valor);
            aux = A->next;
            while(aux != A){
                printf("%d ", aux->valor);
                aux = aux->next;
            }

        }else printf("%d\n", A->valor);
        printf("\n");
    }
}

/*
Busca o item baseado no valor passado no parametro
@param item int
@param A Lista
@return Celula*
*/
Celula *buscarItem(Lista A, int item) {

  Celula *pos = NULL;

  if (A != NULL) {
    pos = A;
    while ((pos->valor != item) && (pos->next != A)) {
      pos = pos->next;
    }

    if(pos->valor != item){
      pos = NULL;
    }
  }
  return pos;
}

/*
Retorna o item baseado na posicao/ordem do valor
@param valor int
@param A Lista
@return int
*/
int obterItemK(Lista A, int valor){
    int item = ghost; int ordem = 1;
    Celula* aux, *pre;

    if(A != NULL){
            pre = A;
            aux = A->next;
            while((aux != A) && (ordem < valor)){ //Talvez colocar <=
                pre = aux;
                aux = aux->next;
                ordem++;
            }
            if(ordem == valor) item = pre->valor;
    
    }

    return item;
}

/*
Coloca um item na lista de maneira ordenada (Lista precisa estar ordenada)
@param A Lista
@param valor int
@return Lista
*/
Lista inserirOrdenado(Lista A, int valor){
    Celula* nova, *aux, *end;
    nova = (Celula *) malloc(sizeof(Celula));

    if(nova != NULL){
        nova->valor = valor;
        if(A == NULL){
            A = nova;
            nova->next = nova;
        }else{
            aux = A; end = A;
            while(aux->next != A){
                if(aux->valor < valor) end = aux;
                aux = aux->next;
            }
            if(end == A){
                if(end->valor >= valor){
                    A = nova;
                    nova->next = end;
                    aux->next = A;
                } 
                if(end->next == A){
                    nova->next = end;
                    end->next = nova;
                }else if(end->valor < valor){
                    nova->next = end->next;
                    end->next = nova;
                }
            }else if(end->next->valor < valor){
                nova->next = end->next->next;
                end->next->next = nova;
            }
            else{
                nova->next = end->next;
                end->next = nova;
            }
        }
    }

    return A;
}

/*
Coloca um item no fim da lista
@param A Lista
@param valor int
@return Lista
*/
Lista insere(Lista A, int valor){
    Celula* nova, *pos, *pre;
    nova = (Celula *) malloc(sizeof(Celula));
    
    if(nova != NULL){
        nova->valor = valor;
        if(A != NULL){ //Ja tem Celula na lista
            pre = A;
            pos = A->next;
            while(pos != A){
                pre = pos;
                pos = pos->next;
            }
            pre->next = nova;
            nova->next = A;

        }else{ //So um item
            nova->next = nova;
        }
        A = nova;
    }

    return A;
} 

/*
Remove um determinado item da lista
@param A Lista
@param valor int
@return Lista
*/
Lista removerItem(Lista A, int valor){
    Celula *pre, *atual, *pos;
    bool achou = false;

    if(A != NULL){
        if(A->next != A){ //Mais de um item na lista
            pre = A;
            atual = A->next;
            while((atual != A) && (achou == false)){ //Remove no "meio da lista"
                if(atual->valor == valor) achou = true;
                else{
					pre = atual;
					atual = atual->next;
				}
            }
            if(achou){
                pre->next = atual->next;
                free(atual);
            }else if(A->valor == valor){ //Quando queremos remover o primeiro e tem mais de um elemento na lista
                	A = atual->next;
					pre->next = A;
					free(atual);
            }
        }else{ //So tem um item na lista
			atual = A;
            free(atual);
            A = NULL;
        }
    }

    return A;
}

/*
Inverte a lista A
@param A Lista
@return Lista
*/
Lista inverterLista(Lista A){
    Celula *pre, *atual, *pos = NULL;

    if(A != NULL){
        if(A->next != A){
            pre = A; atual = pre->next;
            while(pos != A){
                pos = atual->next;
                atual->next = pre; 
                pre = atual;
                atual = pos;
            }
            pos->next = pre;
            A = pre;
        }
    }

    return A;
}

/*
Verifica se um item passado no parametro ja esta na lista
@param A Lista
@param valor int
@return bool
*/
bool itemDuplicado(Lista A, int valor){
    bool duplicado = false;
    Celula* aux = A;

    while((aux != A) && (duplicado == false)){
        if(aux->valor == valor) duplicado = true;
        aux = aux->next;
    }

    return duplicado;
}

/*
Retorna a lista contendo a interseccao da lista A e B
@param A Lista
@param B Lista
@return Lista
*/
Lista interseccao(Lista A, Lista B){
    Lista inter;
    inter = criarLista();
    Celula *preA, *auxA, *preB, *auxB;
    bool duplicado, achou;

    if((A != NULL) && (B != NULL)){
        auxA = A;
            do{
                duplicado = itemDuplicado(inter, auxA->valor);
                auxB = B;
                if(duplicado == false){
                    achou = false;
                    do{
                        if(auxB->valor == auxA->valor){
                            inter = insere(inter, auxA->valor);
                            achou = true;
                        }
                        auxB = auxB->next;
                    }while((auxB != B) && (achou == false));
                }
                auxA = auxA->next;
            }while(auxA != A);
    }

    return inter;
}

/*
Troca duas celulas A e B de posicao
@param list Lista
@param A Celula*
@param B Celula*
@return Lista
*/
Lista trocarCelula(Lista list, Celula* A, Celula* B){
    Celula *antA, *antB, *aux;

    if(A != NULL && B != NULL){
        //Anterior de A
        antA = list;
        while(antA->next != A){
            antA = antA->next;
        }
        //Anterior de B
        antB = list;
        while(antB->next != B){
            antB = antB->next;
        }
        //Celula A vem atras de B
        if(A->next == B){
            antA->next = B;
            A->next = B->next;
            B->next = A;
        }else if(B->next == A){ //Celula B vem atras de A
            antB->next = A;
            B->next = A->next;
            A->next = B;
        }else if(A->next != B && B->next != A){  //Celula A e B em lugares diferentes
            aux = A->next;
            antA->next = B;
            antB->next = A;
            A->next = B->next;
            B->next = aux;
        }

        if(list == A) list = B;
        else if(list == B) list = A;
    }

    return list;
}

/*
Esvazia a lista, liberando a memoria
@param A Lista
@return Lista
*/
Lista esvaziarLista(Lista A){
    Celula* aux = NULL, *end;

    if(A != NULL){
        end = A->next; 
        while(aux != A){
            aux = end;
            end = end->next;
            free(aux);
        }
        A = NULL;
    }

    return A;
}