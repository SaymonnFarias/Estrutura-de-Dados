#include <stdio.h>
#define MAX_SIZE 3

// estrutura fila estática 
typedef struct {
    int itens[5];
    int inicio;
    int fim;
    int qtd; 
} FilaEst ;

//inicializar 
void inicializaFila(FilaEst *fila){
    fila->inicio = 0;
    fila->fim = -1; // se fim < inicio, logo a fila esta vazia; 
    fila->qtd = 0; 
}

int cheiaFila(FilaEst *fila){
    return(fila->qtd == MAX_SIZE );
}

int vaziaFila(FilaEst *fila){
    return(fila->qtd == 0);
}

void primeiro(FilaEst *fila){
    if(vaziaFila(fila)){
        printf("\nErro: Fila vaiza\n");
    }
    printf("\nPrimeiro: %d\n", fila->itens[fila->inicio]);
}

void tamanho(FilaEst *fila){
    if(vaziaFila(fila)==1){
        printf("\nFila vazia!\n");
    }else{
        printf("\nTam:%d\n", (fila->fim - fila->inicio)+1);
    }
}

//-----------------------------------------------// mudança no cálculo da fila 
void enfileira(FilaEst *fila, int valor){
    if(cheiaFila(fila)==1){
        printf("\nFila Cheia!\n");
    }else{
        fila->fim = (fila->fim + 1) % MAX_SIZE;
        fila->itens[fila->fim] = valor; 
        fila->qtd ++;
    }
}

//-----------------------------------------------// mudança no cálculo da fila 
void desenfileira(FilaEst *fila){
    int item;
    if(vaziaFila(fila)){
        printf("\nErro: Fila vazia\n");
        return; 
    }
    item =  fila->itens[fila->inicio];
    fila->itens[fila->inicio] = 0; 
    fila->inicio = (fila->inicio + 1) % MAX_SIZE;
    fila->qtd--;
    printf("\nDesenfileirado: %d\n", item);
}

void imprimeFila(FilaEst *fila) {
    if (vaziaFila(fila)) {
        printf("Fila vazia.\n");
        return;
    }

    printf("\nElementos da fila:\n");
    for(int i = fila->inicio; i<MAX_SIZE; i++){
        if(i == fila->inicio){
            printf("Inicio [%d]:\n",i,fila->itens[i]);
        }else if(i == fila->fim){
            printf("Fim [%d]:\n",i,fila->itens[i]);
        }
        
    }
}
int main(){
    FilaEst fila;

    inicializaFila(&fila); 
    enfileira(&fila, 10);
    enfileira(&fila, 11); 
    enfileira(&fila, 12); 
   
    imprimeFila(&fila); 

    desenfileira(&fila);

    imprimeFila(&fila); 

  
    


}
