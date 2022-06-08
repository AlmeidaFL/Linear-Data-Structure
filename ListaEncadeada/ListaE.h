/*
Autor: Luis Felipe Almeida Beserra Matos
Faculdade: PUCSP (Computacao)
Data: 08/06/2022
Descricao: Arquivo que contem TAD Lista encadeada (dinamica) normal com cabeca
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define fantasma -1

typedef struct Celula{
    int item;
    struct Celula *next;
}Celula;

typedef struct{
    int tam;
    Celula *inicio;
}Lista;

/*
Cria uma lista vazia
@return Lista
*/
Lista criarLista(){
    Lista L;
    L.inicio = NULL;
    L.tam = 0;
    return L;
}

/*
Insere uma celula na lista
@param valor int
@param L Lista*
@return void
*/
void inserirLista(Lista* L, int valor){
    Celula *aux;
    aux = (Celula *) malloc(sizeof(Celula));
    aux->item = valor;
    aux->next = L->inicio;
    L->inicio = aux;
    L->tam++;
}

/*
Verifica se uma lista L esta vazia
@param L Lista
@return bool
*/
bool verListaVazia(Lista L){
    bool vazia = true;
    if(L.inicio != NULL) vazia = true;
    return vazia;
}

/*
Remove o primeiro item da lista L
@param L Lista*
@return void
*/
void removerPrimeiro(Lista *L){
    Celula *aux;
    if(L->inicio != NULL){
        aux = L->inicio->next;
        free(L->inicio) ;
        L->inicio = aux;
        L->tam--;
    }
}

int obterTamanho(Lista *L){
    return L->tam;
}
/*
Remove o ultimo item da lista
@param L Lista*
*/
void removerUltimo(Lista *L){
    Celula *prim, *aux, *endereco;
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

/*
Obtem o elemento de ordem/posicao baseado no 'valor'
@param valor int
@param L Lista*
@return int
*/
int obterElemento(Lista *L, int valor){
    Celula *aux, *end; int cont = 0;
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

/*
Retorna o endereco de uma celula na lista que contenha o elemento 'valor'
@param valor int
@param L Lista*
@return Celula*
*/
Celula* buscarItem(Lista* L, int valor){
    Celula *aux = L->inicio, *endereco = NULL;
    bool achou = false;

    while(aux != NULL && achou == false){
        if(aux->item == valor){
            achou = true;
            endereco = aux;
        }
        aux = aux->next;
    }

    return endereco;
}

void mostrarLista(Lista L){
    Celula *aux;

    if(L.inicio != NULL){
        aux = L.inicio;
        while(aux != NULL){
            printf("%d ", aux->item);
            aux = aux->next;
        }
    }
    printf("\n");

}

/*
Remove a primeira ocorrencia de valor na lista.
Ao encontrar o valor, é necessario verificar se ele é o ultimo da lista,
se ele está no meio de duas Celulas, ou se é o primeiro. Se for o primeiro, mudamos o inicio da cabeca
Se for o ultimo, na variavel endereco(que guardao endereco da ultima celula)->next 
colocamos o NULL. Se não for o ultimo, o endereco->next sera o proximo do proximo.
@param L Lista*
@param valor int
@return void
*/
void buscaRemove(Lista* L, int valor){
    Celula *aux = L->inicio, *endereco = aux;
    bool achou = false;

    while((aux != NULL) && (achou == false)){
        
        if(aux->item == valor){
            achou = true;
            if(aux == L->inicio){ //Primeiro da lista
                L->inicio = aux->next;
            }else{
                if(aux->next == NULL){ //Ultimo item da lista
                    endereco->next = NULL;
                }else{ //Item esta no meio de duas celulas
                    endereco->next = endereco->next->next;
                }
            }
            free(aux);
            L->tam--;
        }
        endereco = aux;
        aux = aux->next;
    }
}

/*
Insere no inicio uma celula com o valor y somente se esse valor não ocorre na lista
@param lista Lista*
@param valor int
@return void
*/
void buscaInsere(Lista *L, int valor){
    Celula* aux = L->inicio; Celula* nova = NULL;
    bool achou = false;

    while((aux != NULL) && (achou == false)){
        if(aux->item == valor){
            achou = true;
        }
        aux = aux->next;
    } 
    if(!achou){
        nova = (Celula *) malloc(sizeof(Celula));
        nova->item = valor;
        nova->next = L->inicio;
        L->inicio = nova;
        L->tam++;
    }
}

/*
Verifica se a lista esta em ordem crescente. Nao tem duplicata
@param l Lista
@return bool
*/
bool verificaCrescente(Lista L){
    bool crescente = true;
    int vAux;
    Celula* aux = L.inicio;

    if(aux != NULL){
        vAux = aux->item;
        while((aux != NULL) && (crescente == true) && (aux->next != NULL)){
            if(vAux > aux->next->item){
                crescente = false;
            }
            vAux = aux->next->item;
            aux = aux->next;
        }
    }else crescente = false;

    return crescente;
}

/*
Verifica se as duas listas contem os mesmos elementos, nao importando a ordem desses.
As listas nao contem duplicatas
@param A Lista
@param B Lista
@return bool
*/
bool verificaIgual(Lista A, Lista B){
    Celula* auxA, *auxB;
    int valor;
    bool achou = true; //achou serve tanto para o retorno, quanto p/ verificar se achou
                        //paridade de itens nas duas listas, com os testes

    if(A.inicio != NULL && B.inicio != NULL){
        auxA = A.inicio;
        achou = true;
        while((auxA != NULL) && (achou != false)){
            auxB = B.inicio;
            achou = false;
            while((auxB != NULL) && (achou == false)){
                if(auxA->item == auxB->item) achou = true;
                auxB = auxB->next;
            }
            auxA = auxA->next;
        }
    }else achou = false;

    return achou;
}



/*
Constroi uma nova lista com a concatenacao das listas na ordem dos parametros
@param A Lista*
@param B Lista*
@return Lista
*/
Lista concatenarListas(Lista* A, Lista* B){
    Celula* aux, *var;
    Lista nova;

    aux = A->inicio;

    if(aux != NULL){ //Lista A nao é nula
        nova.inicio = aux;
        
        while(aux != NULL){
            var = aux;
            aux = aux->next;
        }
        var->next = B->inicio;
        nova.tam = B->tam + A->tam;
    }else{ //Lista A é nula ou tambem a lista B é nula.
        nova.inicio = B->inicio;
        nova.tam = B->tam;
    }
    
    return nova;
}

/*
Constroi uma nova lista com a concatenacao das listas na ordem dos parametros e
devolve a segunda lista vazia
@param A Lista*
@param B Lista*
@return Lista
*/
Lista concatenarListasV(Lista* A, Lista* B){
    Celula* aux, *var;
    Lista nova;

    aux = A->inicio;

    if(aux != NULL){ //Lista A nao é nula
        nova.inicio = aux;
        
        while(aux != NULL){
            var = aux;
            aux = aux->next;
        }
        var->next = B->inicio;
        nova.tam = B->tam + A->tam;
    }else{ //Lista A é nula ou tambem a lista B é nula.
        nova.inicio = B->inicio;
        nova.tam = B->tam;
    }

    //Esvaziando lista B
    aux = B->inicio;
    while(aux != NULL){
        var = aux;
        aux = aux->next;
        free(var);
    }
    B->tam = 0;
    
    return nova;
}

/*
Verifica se duas listas 'A' e 'B' sao iguais sem duplicatas
@param A Lista
@param B Lista
@param bool
*/
bool verificaIgualS(Lista A, Lista B){
    Celula *auxA = A.inicio, *auxB = B.inicio;
    int valor;
    bool achou = false;

    if(auxA != NULL && auxB != NULL){
        achou = true;
        while((achou != false) && (auxA != NULL)){
            valor = auxA->item;
            if(auxB != NULL){
                if(auxB->item != valor) achou = false;
                else{
                    auxA = auxA->next;
                    auxB = auxB->next;
                }
            } else achou = false;
        }
    }
    
    return achou;
}

/*
Separa duas listas a partir do valor passado como parametro. Retorna a nova lista
@param valor int
@param A Lista*
@return Lista
*/
Lista separarLista(Lista* A, int valor){
    Lista nova;
    Celula* aux, *endereco;
    bool achou = false;
    int tam = 0;

    if(A->inicio != NULL){
        aux = A->inicio; endereco = aux;

        while((aux != NULL) && (achou == false)){
            endereco = aux;
            if(endereco->item == valor) achou = true;
            aux = aux->next;
            tam++;
        }if(achou){
            aux = endereco->next;
            endereco->next = NULL;
            nova.inicio = aux;
            nova.tam = A->tam - tam;
            A->tam = tam;
        }
        
    }else{
        nova.tam = 0;
        nova.inicio = NULL;
    }

    return nova;
}

/*
Concatena duas listas em um nova, com novas celulas, na ordem dos parametros
@param A Lista*
@para B Lista*
@return Lista
*/
Lista concatenarListasS(Lista* A, Lista* B){ 
    Lista nova;
    Celula* aux, *end, *auxNova;
    
    nova.inicio = NULL;
    nova.tam = 0;

    if(A->inicio == NULL && B->inicio == NULL){
        nova.tam = 0;
    }else{
        aux = A->inicio;
        while(aux != NULL){ //Adicionando itens de A
            end = aux;
            auxNova = (Celula *) malloc(sizeof(Celula));
            auxNova->item = end->item;
            auxNova->next = nova.inicio;
            nova.inicio = auxNova;
            nova.tam++;
            aux = aux->next;
        }
        aux = B->inicio;
        while(aux != NULL){ //Adicionando itens de B
            end = aux;
            auxNova = (Celula *) malloc(sizeof(Celula));
            auxNova->item = end->item;
            auxNova->next = nova.inicio;
            nova.inicio = auxNova;
            nova.tam++;
            aux = aux->next;
        }
    }

    return nova;
}

/*
Invertendo lista com novas celulas
@param A Lista
@return Lista
*/
Lista inverterLista(Lista A){
    Lista nova;
    Celula* aux, *auxNova, *end;
    
    nova.inicio = NULL;
    nova.tam = 0;

    if(A.inicio != NULL){
        aux = A.inicio;
        while(aux != NULL){
            end = aux;
            auxNova = (Celula*) malloc(sizeof(Celula));
            auxNova->item = aux->item;
            auxNova->next = nova.inicio;
            nova.inicio = auxNova;
            nova.tam++;
            aux = aux->next;
            free(end);
        }    
    }

    return nova;
}

void obterTamanho(Lista A){
    printf("Tamanho da lista: %d\n", A.tam);
}

Lista esvaziarLista(Lista A){
    Celula* aux = NULL, *end;

    if(A.inicio != NULL){
        end = A.inicio; 
        while(end != NULL){
            aux = end;
            end = end->next;
            free(aux);
        }
        A.inicio = NULL;
        A.tam = 0;
    }

    return A;
}

/*
Verifica se o elemento 'valor' passado como parametro ja esta na lista
@param A Lista
@param valor int
@return bool
*/
bool itemDuplicado(Lista A, int valor){
    bool duplicado = false;
    Celula *aux;

    if(A.inicio != NULL){
        aux = A.inicio;
        while((duplicado == false) && (aux != NULL)){
            if(aux->item == valor) duplicado = true;
            aux = aux->next;
        }
    }

    return duplicado;
}

/*
Verifica se duas listas sao iguais, nao importando a ordem podendo conter duplicadas
Explicacao: Crio duas listas auxiliares em relação a lista A. Uma lista guarda os itens sem duplicadas
Ex: Lista A = {1,2,2,3,1}; aux1 = {1,2,3}. E outra lista guarda a qtd desses itens, aux2 = {2,2,1} ('1' tem 2 itens,
'2' tem 2 itens, '3' tem 1 item) aux1 -> aux2. Com essas duas listas, so preciso percorrer a lista B e comparar
cada item da lista A, com a lista B, e ver quantos itens na lista B são iguais. Com essa qtd, comparar com o primeiro
indice da aux2 e assim por diante
@param B Lista
@param A Lista
@return bool se a lista eh igual, mesmo com duplicadas
*/
bool verificaIgualDuplicado(Lista A, Lista B){
    bool igual = false;
    Lista qtd, itens;
    int itemA, itemANext;
    Celula *itemComparar; int itemComp;
    Celula *aux, *auxNext, *auxB;
    bool duplicado;
    int qtdItens = 0;
    bool diferente = false;

    if(A.tam == B.tam){
        if(A.inicio != NULL && B.inicio != NULL){
            diferente = true;

            qtd = criarLista();
            itens = criarLista();

            aux = A.inicio;
            while(aux != NULL){
                itemA = aux->item;
                duplicado = itemDuplicado(itens, itemA);
                if(duplicado == false){
                    inserirLista(&itens, itemA);
                    itemComparar = itens.inicio;
                    itemComp = itemComparar->item;

                    auxNext = aux->next;
                    qtdItens = 1;
                    if(auxNext != NULL){
                        while(auxNext != NULL){
                            itemANext = auxNext->item; 
                            if(itemComp == itemANext){
                                qtdItens++;
                            }
                            auxNext = auxNext->next;
                        }
                    }
                    inserirLista(&qtd, qtdItens);
                }
                aux = aux->next;
            }

            int qtdItensIndividuais = itens.tam;
            int i = 1;
            Celula *qtdComparar;
            int qtdComp = 0;
            while((i <= qtdItensIndividuais) && (diferente == true)){
                if(i == 1){
                    itemComparar = itens.inicio; qtdComparar = qtd.inicio;
                }
                else {
                    itemComparar = itemComparar->next; qtdComparar = qtdComparar->next;
                }

                itemComp = itemComparar->item;
                qtdComp = qtdComparar->item;

                auxB = B.inicio;
                qtdItens = 0;
                while(auxB != NULL){
                    if(auxB->item == itemComp){
                        qtdItens++;
                    }
                    auxB = auxB->next;
                }
                if(qtdComp != qtdItens) diferente = false;
                i++;
            }
        }
        itens = esvaziarLista(itens);
        qtd = esvaziarLista(qtd);
    }

    return diferente;
}

/*
Retorna uma lista sem duplicadas
@param A Lista
@param valor int
@return Lista
*/
Lista removerDuplicada(Lista A, int valor){
    Celula* pre, *pos, *end;
    int itemComp;

    if((A.inicio != NULL) && (A.tam >= 2)){
        pre = A.inicio;
        while(pre->next != NULL && pre->item != valor){
            pre = pre->next;
        }
        if(pre->next != NULL){
            pos = pre->next;
            while(pos != NULL){
                if(pos->item == valor){
                    end = pos;
                    pos = pos->next;
                    free(end);
                    pre->next = pos;
                }else{
                    pre = pre->next;
                    pos = pos->next;
                }
            }
        }
    }

    return A;
}
/*
Lista trocarCelulas(Lista listaTrocar, Celula* A, Celula* B){
    Celula* auxA, *auxB, *pre, *pos;

    if((listaTrocar.inicio != NULL) && listaTrocar.tam >= 2){
        if(A->next == B){
            pre = A; pos = B;
        }else if(B->next == A){
            pre = B; pos = A;
        }
        auxA = listaTrocar.inicio;
        while((auxA->next != pre) && (auxA != NULL)){
            auxA = auxA->next;
        }
        if(auxA != NULL){
            pre->next = pos->next;
            pos->next = pre;
            auxA = pos;
        }
    }
}*/