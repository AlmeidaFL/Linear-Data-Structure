#define Max 100
#define sinal -1
#define ghost 36

#include "Booleano.h"

typedef struct{
    int topo;
    unsigned char Vetor[Max];
}Pilha;

//Interface
Pilha criarPilha();
bool PilhaVazia(PilhaC pilha);
bool PilhaCheia(PilhaC pilha);
char acessarPilha(PilhaC pilha);
Pilha pushPilha(PilhaC pilha, unsigned char valor);
Pilha popPilha(PilhaC pilha);
Pilha esvaziarPilha(PilhaC pilha);
void mostrarPilha(PilhaC pilha);

Pilha criarPilha(){
    PilhaC pilha;
    pilha.topo = sinal;

    return pilha;
}

bool PilhaVazia(PilhaC pilha){
    bool vazia = TRUE;
    if(pilha.topo != sinal){
        vazia = FALSE;
    }
    return vazia;
}

bool PilhaCheia(PilhaC pilha){
    bool cheia = TRUE;

    if(pilha.topo != Max-1){
        cheia = FALSE;
    }
    return cheia;
}

char acessarPilha(PilhaC pilha){
    char valor = ghost;
    int topo = pilha.topo;

    if(pilha.topo != sinal){
        valor = pilha.Vetor[topo];
    }

    return valor;
}

Pilha pushPilha(PilhaC pilha, unsigned char valor){
    int topo = pilha.topo;

    if(topo < Max-1){
        topo += 1;
        pilha.Vetor[topo] = valor;
        pilha.topo = topo;
    }

    return pilha;
}

Pilha popPilha(PilhaC pilha){
    int topo = pilha.topo;

    if(topo != sinal){
        pilha.topo -= 1;
    }

    return pilha;
}

Pilha esvaziarPilha(PilhaC pilha){
    pilha.topo = sinal;

    return pilha;
}

void mostrarPilha(PilhaC pilha){
    int topo = pilha.topo;

    for(int i = topo; i >= 0; i--){
        printf("%c\n", pilha.Vetor[i]);
    }
}
