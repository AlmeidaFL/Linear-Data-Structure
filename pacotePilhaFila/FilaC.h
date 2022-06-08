#define sinal -1
#define Max 10
#define ghost 36

typedef struct{
    int inicio;
    int fim
    unsigned char Vetor[Max];
}Fila;

Fila criarFilaVazia(){
    Fila A;
    A.inicio = sinal;
    A.fim = sinal;
    return A;
}

bool FilaVazia(Fila A){
    bool vazia = TRUE;

    if(A.inicio != sinal) vazia = FALSE;
    return vazia;
}

bool FilaCheia(Fila A){
    bool cheia = TRUE;

    if(A.inicio-1 != A.fim) cheia = FALSE;
    return cheia; 
}

unsigned char acessarPrimeiro(Fila A){
    int valor = ghost, aux;

    if(A.inicio != sinal){
        aux = A.inicio;
        valor = A.Vetor[aux];
    }
    return valor;
}

Fila pushFila(Fila A, int valor){
    int seg;
    
    seg = (A.fim + 1) % Max;
    if(seg != A.inicio){
        A.Vetor[seg] = valor;
        if(A.inicio == sinal) A.inicio = seg;
        A.fim = seg;
    }
    return A;
}

Fila popFila(Fila A, int valor){
    int seg;

    if(A.inicio != sinal){
        if(A.inicio == A.fim){
            A.inicio = sinal;
            A.fim = sinal;
        }else{
            seg = (A.inicio + 1) % Max;
            A.inicio = seg;
        }
    }

    return A;
}

Fila esvaziarFila(Fila A){
    A.inicio = sinal;
    A.fim = sinal;
    return A;
}

void mostrarFila(Fila A){
    int i, k;

    if(A.inicio != sinal){
        i = A.inicio;
        k = A.fim;
        while(i != k){
            printf("%c ", A.Vetor[i]);
            i = (i + 1) % Max;
        }
        printf("%c\n", A.vetor[k]);
    }else{
        printf("\nFila Vazia\n");
    }
}