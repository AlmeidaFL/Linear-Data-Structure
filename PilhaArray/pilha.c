/*
  Autor: Luis Felipe Almeida Beserra Matos
  Date: 11/10/09 10:58
  Descri��o: Define e implementa o tipo de dados Pilha
  que pode guardar at� MaxPilha n�meros reais positivos. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxPilha 10
#define Sinal 0
#define fantasma 0

typedef struct {
      int topo;	  // topo indica o local onde deve ser colocado o pr�ximo item
      float tabela[MaxPilha];
} c_Pilha;

typedef c_Pilha *Pilha;

Pilha newPilha();
float acessarTopo(Pilha);
bool PilhaVazia(Pilha);
bool PilhaCheia(Pilha);
void pushPilha(Pilha, float);
void popPilha(Pilha);
void mostrar(Pilha P);

Pilha newPilha(){		// 2.0 pontos
	Pilha A;
	A->topo = 0;
	return A;
}

bool PilhaVazia(Pilha P){	//1.0 ponto
	bool vazia = false;

	if(P->topo == Sinal) vazia = true;

	return vazia;
}

float acessarTopo(Pilha P){	//1.0 ponto
	float valor;
	int k;
	k = P->topo;

	if(k != Sinal){
		valor = P->tabela[k-1];
	}

	return valor;
}     

bool PilhaCheia(Pilha P){	// 2.0 pontos
	bool cheia = false;

	if(P->topo == MaxPilha) cheia = true;

	return cheia;
}

void pushPilha(Pilha P, float y){	// 2.0 pontos
	int tam = P->topo;

	if(tam != MaxPilha){
		P->tabela[tam] = y;
		P->topo++;
	}
}

void popPilha(Pilha P){		// 2.0 pontos
	int tam = P->topo;

	if(P->topo != Sinal){
		P->topo--;
	}
}

void mostrar(Pilha P){
	for(int i = 0; i < P->topo; i++){
		printf("%.1f\n", P->tabela[i]);
	}
}
