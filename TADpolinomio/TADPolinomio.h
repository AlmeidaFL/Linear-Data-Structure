/*
Autor: Luis Felipe Almeida Beserra Matos
Faculdade: PUCSP (Computacao)
Data: 08/06/2022
Descricao: Arquivo que contem o TAD Polinomio, com funcoes de soma e multiplicacao (nao incluindo a divisao)
*/

#ifndef TADPolinomio_H
#define TADPolinomio_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h> 
#include <math.h>
#include "ListaLigada.h"


#define ghost -1
#define sinal -1

typedef struct Celula{
    int coeficiente;
    int expo;
    struct Celula* next;
    struct Celula* pre;
}Celula;

typedef struct{
    int grau;
    int tam;
    Celula* inicio;
    Celula* fim;
}Polinomio;

typedef Polinomio* Poli;

Polinomio criarPoli();
Polinomio iniciarPoli();
bool monDuplicado(Polinomio A, int expoente);
Polinomio criarCelula(Polinomio A, int coeficiente, int expoente);
int charToInt(char c);
bool isEquationC(char *c);
void mostrarPoli(Polinomio A);
Polinomio esvaziarPoli(Polinomio A);
Polinomio removerItem(Polinomio A, int coeficiente);
Polinomio somarPolinomio(Polinomio A, Polinomio B);
int getExpo(char *c);
int getCoef(char *c);
Polinomio multPoli(Polinomio A, Polinomio B);


Polinomio iniciarPoli(){
    Polinomio A;
    A.inicio = NULL;
    A.fim = NULL;
    A.grau = ghost;
    A.tam = 0;
    return A;
}

bool monDuplicado(Polinomio A, int expoente){
    bool duplicado = false;
    Celula *aux;

    if(A.tam > 0){
        aux = A.inicio;
        while((aux != NULL) && (duplicado == false)){
            if(aux->expo == expoente) duplicado = true;
            aux = aux->next;
        }
    }

    return duplicado;
}

/*
Cria um polinomio dado uma quantidade 'n' de monomios
@param quantidade de argumentos int
@param monomios em strings char[]
@return Polinomio
*/
Polinomio criarPolid(int num_args, ...){
    Polinomio A;
    A = iniciarPoli();


    va_list args;
    va_start(args, num_args);

    if(num_args > 0){
        for(int i = 0; i < num_args; i++){
            char *aux = va_arg(args, char*);
            int len = strlen(aux);
            if(len >= 3){
                bool eq = isEquationC(aux);
                if(eq){ //Se for um monomio
                    int expo, coeficiente;
                    if(coeficiente != 0){
                        expo = getExpo(aux); coeficiente = getCoef(aux);
                        if(monDuplicado(A, expo) == false){ //Se nao tiver duplicadas
                            A = criarCelula(A, coeficiente, expo);
                        }
                    }
                }
            }
        }
    }

    va_end(args);

    return A;
}

/*
Cria uma celula/monomio do polinomio 'A' passado como parametro
@param A Polinomio
@param monomio Celula**
@return expoente do monomio int
*/
Polinomio criarCelula(Polinomio A, int coeficiente, int expoente){
    Celula* atual, *pre, *nova;

    nova = (Celula *) malloc(sizeof(Celula));
        if(nova != NULL){
        nova->expo = expoente;
        nova->coeficiente = coeficiente;

        if((A.inicio == NULL) || (A.inicio->expo < nova->expo)){//Inserçao no inicio
            nova->pre = NULL;
            nova->next = A.inicio;
            if(A.inicio == NULL) A.fim = nova;
            else A.inicio->pre = nova; //Quando tem uma celula que vai estar na "frente" da nova
            A.inicio = nova;
        }else{ 
                atual = A.inicio;
                while((atual->next != NULL) && (atual->expo > expoente)){
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
    }

    return A;
}

/*
Retorna o numero correspondente do char da tabela ASCII
@param A char
@return inteiro correspondente ao char int
*/
int charToInt(char c){
    int aux = sinal;
    aux = c - '0';
    return aux;
}

/*
Verifica se uma string eh uma equacao no formato "numberxnumber" 
@param string char*
@return se eh uma equacao ou nao bool
*/
bool isEquationC(char *c){
    bool value = false;
    int len = strlen(c);

    if(len > 0){
        bool negativo = false, digito;
        int start = 0, contador = 0;
        char aux = ' ';
        if(c[0] == '-') {
            negativo = true;
            start++;
        }
        //Monomio exemplo "421x2\0"
        //Verifica a primeira parte do monomio -> 421x
        while((aux != 'x') && (contador < 2)){
            aux = c[start];
            digito = isdigit(aux);
            if(digito == false) contador++;
            start++; 
        }
        //Verifica a segunda parte do monomio -> "2\0". Só podendo contador = 1 (unico digito -> x);
        //start precisa ser >= 2 pois o "monomio" pode ser -ax
        if(aux == 'x'){
            int number = start;
            if(negativo) number--;
            if((number >= 2) && (contador == 1)){
                contador = 0; aux = ' ';
                if(c[start] != '\0'){
                    value = true;
                    while((aux != '\0') && (contador < 2)){
                        aux = c[start];
                        digito = isdigit(aux);
                        if((digito == false) && (aux != '\0')) value = digito;
                        start++; 
                    }
                }
            } 
        }
    }

    return value;
}

/*Retorna o coeficiente da string no formato coeficientexexpoente
@param string *char
@return coeficiente int
*/
int getCoef(char *c){
    bool negativo = false;
    int number = 0, len = 0;
    
    if(c[0] == '-'){
        negativo = true;
    }
    //Acha o x com o len da parte do coeficiente
    while(c[len] != 'x'){
        len++;
    }
    
    int aux = 0;
    if(negativo){
        len--; aux++;
    }
    while(len > 0){
        number += charToInt(c[aux]) * ceil(pow(10,len-1));
        len--; aux++;
    }
    if(negativo) number = -number;

    return number;
}

/*Retorna o expoente da string no formato numeroxexpoente
@param string *char
@return expoente int
*/
int getExpo(char *c){
    bool terminador = false;
    int number, len = 0, retorno = 0;

    while(c[len] != '\0'){
        if(c[len] == 'x') number = len;
        len++;
    }
    int tamanho = len;
    len = len-number-1; number++;
    while(number < tamanho){
        retorno += charToInt(c[number]) * ceil(pow(10,len-1));
        len--; number++;
    }

    return retorno;
}

/*
Mostra o polinomio 'A' passado como parametro no terminal
@param A Polinomio
@return void
*/
void mostrarPoli(Polinomio A){
    Celula* aux;

    if(A.inicio == NULL) printf("Lista vazia\n");
    else{
        aux = A.inicio;
        while(aux != NULL){
            printf("%dx%d ", aux->coeficiente,aux->expo);
            aux = aux->next;
        }
        printf("\n");
    }
}

/*Soma dois polinomios A e B
@param A Polinomio
@param B Polinomio
@return polinomio somado Polinomio
*/
Polinomio somarPolinomio(Polinomio A, Polinomio B){
    Polinomio C;
    C = iniciarPoli();

    if(A.tam == 0) return B;
    else if(B.tam == 0) return A;
    else{
        int expoente, coefic, soma;
        Celula *auxA, *auxB, *lixoA, *lixoB;
        bool achou;

        //Percorrendo o poli A para verificar se acha um correspondente. Achando, coloca no poli C e exclue 
        //A celula do A e do B
        auxA = A.inicio;
        while(auxA != NULL){
            achou = false;
            auxB = B.inicio;
        
            while((auxB != NULL) && (achou == false)){
                if(auxA->expo == auxB->expo){
                    soma = auxA->coeficiente + auxB->coeficiente;
                    if(soma != 0){
                        C = criarCelula(C, soma, auxA->expo);
                    }
                    achou = true;
                    lixoA = auxA; lixoB = auxB;
                }
                auxB = auxB->next;
            }
            auxA = auxA->next;
            if(achou){
                A = removerItem(A, lixoA->coeficiente);
                B = removerItem(B, lixoB->coeficiente);
            }
        }

        //Colocando na lista C os monomios que nao se foi achado correspodente
        if(A.tam > 0 || B.tam > 0){
            auxA = A.inicio;
            while(auxA != NULL){
                C = criarCelula(C, auxA->coeficiente, auxA->expo);
                lixoA = auxA;
                auxA = auxA->next;
                free(lixoA);
            }
            auxB = B.inicio;
            while(auxB != NULL){
                C = criarCelula(C, auxB->coeficiente, auxB->expo);
                lixoB = auxB;
                auxB = auxB->next;
                free(lixoB);
            }
        }
    }

    return C;
}

/* Remove um item do polinomio baseado no coeficiente passado como parametro
@param A Polinomio
@param coeficiente int
@return Polinomio
*/
Polinomio removerItem(Polinomio A, int coeficiente){
    Celula* aux, *pre, *pos;
    bool achou = false;

    if(A.inicio != NULL){
        aux = A.inicio;
        while((aux != NULL) && (achou == false)){
            if(aux->coeficiente == coeficiente) achou = true;
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

/*
Refaz um polinomio caso ele tenha expoentes iguais nao somados
@param A Polinomio
@return Polinomio
*/
Polinomio redoPoli(Polinomio A){
    Polinomio C;
    C = iniciarPoli();

    
    if(A.inicio != NULL){
        Celula* aux = A.inicio, *auxB;
        Lista B = criarLista();

        while(aux != NULL){
            bool duplicado = itemDuplicado(B, aux->expo);
            inserirLista(&B, aux->expo);

            if(duplicado == false){
                auxB = A.inicio;
                int coef = 0, expo = 0;
                bool achou = false;
                expo = aux->expo;
                while(auxB != NULL){
                    if((aux->expo == auxB->expo) && (aux != auxB)){
                        coef = aux->coeficiente+auxB->coeficiente;
                        achou = true;
                    }
                    auxB = auxB->next;
                }
                if(achou == false){
                    expo = aux->expo; coef = aux->coeficiente;
                }
                C = criarCelula(C, coef, expo);
            }
            aux = aux->next;
        }
        A = esvaziarPoli(A);
        esvaziarLista(&B);
    }

    return C;
}

/*
Multiplica um polinomio A pelo pelonomio B
@param A Polinomio
@param B Polinomio
@return Polinomio
*/
Polinomio multPoli(Polinomio A, Polinomio B){
    Polinomio C;
    C = iniciarPoli();

    if((A.inicio != NULL) && (B.inicio != NULL)){
        Celula* auxA = A.inicio, *auxB;
        int expo, coef;
        for(int i = 0; i < A.tam; i++){
            auxB = B.inicio;
            for(int j = 0; j < B.tam; j++){
                expo = auxA->expo + auxB->expo;
                coef = auxA->coeficiente * auxB->coeficiente;
                C = criarCelula(C, coef, expo);
                auxB = auxB->next;
            }
            auxA = auxA->next;
        }
        esvaziarPoli(A);
        esvaziarPoli(B);
        C = redoPoli(C);
    }

    return C;
}
/*
Esvazia um polinomio e o reinicia
@param Polinomio
@return Polinomio
*/
Polinomio esvaziarPoli(Polinomio A){
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
        A.grau = ghost;
    }
}

#endif