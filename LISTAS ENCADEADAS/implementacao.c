#include <stdio.h>
#include <stdlib.h>

//Estrutura básica
typedef struct nodo{
    int valor;
    struct nodo *prox;
}Nodo;


//Inicialização 
Nodo *criaNodo(int valor){
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo)); //aloca epaço em memória
    if(novo==NULL){ //verifica se ouve erro ao alocar memoria 
        printf("Erro ao alocar memoria!\n");
        exit(1); 
    }

    novo->valor = valor; // atribui o valor passado
    novo->prox = NULL; // o próximo é nulo
    return novo; 
}

//Inserção no inicio
Nodo* inserirInicio(Nodo *head, int valor){
    Nodo *novo = criaNodo(valor); 
    novo->prox = head;
    return novo; 
}

//Algoritmo de busca 
Nodo* buscarLista(Nodo *head, int valor){
    Nodo *temp = head; //variavel  temporaria aponta para a cabeça
    while(temp != NULL){ // percorre a lista 
        if(temp->valor == valor){ //verifica igualdade do valor 
            return temp; // atualiza o temp 
        }
        temp = temp->prox; // aponta para o proximo 
    }
    return NULL; //se chegou aqui então não achou o valor. 
}

//Impressão da lista
void imprimeLista(Nodo *head){
    Nodo *aux = head; 
    while(aux != NULL){
        printf("%d\n", aux->valor); // imprime o valor
        aux = aux->prox; // aponta para o próximo
    }
}

//Remoção no inicio 
Nodo* removerInicio(Nodo *lista){
    if (lista == NULL) {
        printf("Lista vazia \n");
        return NULL; 
    }
    Nodo *temp = lista;
    printf("Valor removido: %d\n", temp->valor);
    lista = lista->prox; //aponta para o prox 
    free(temp); //libera o temporário
    return lista; 
}

//--------------PILHA------------------------------//

Nodo* inserirTopo(Nodo *topo, int valor){
    Nodo *novo = criaNodo(valor); 
    novo->prox = topo;
    return novo; 
}

Nodo* buscarPilha(Nodo *topo, int valor){
    Nodo *temp = topo; //variavel  temporaria aponta para a cabeça
    while(temp != NULL){ // percorre a lista 
        if(temp->valor == valor){ //verifica igualdade do valor 
            return temp; // atualiza o temp 
        }
        temp = temp->prox; // aponta para o proximo 
    }
    return NULL; //se chegou aqui então não achou o valor. 
}
void imprimePilha(Nodo *pilha){
    Nodo *aux = pilha; 
    while(aux != NULL){
        printf("%d\n", aux->valor); // imprime o valor
        aux = aux->prox; // aponta para o próximo
    }
}
Nodo* removerTopo(Nodo *pilha){
    if (pilha == NULL) {
        printf("pilha vazia \n");
        return NULL; 
    }
    Nodo *temp = pilha;
    printf("Valor removido: %d\n", temp->valor);
    pilha = pilha->prox; //aposta para o prox 
    free(temp); //libera o temporário
    return pilha; 
}

//-----------FILAS--------------------//
typedef struct fila{
    Nodo *inicio; 
    Nodo *fim;
    int tam; 
}Fila;

void inicializaFila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tam = 0;
}

void inserirFinalFila(Fila *fila, int valor) {
    Nodo *novo = criaNodo(valor);
    if (fila->inicio == NULL) { // fila vazia
        fila->inicio = novo;
    } else {
        fila->fim->prox = novo;
    }
    fila->fim = novo;
    fila->tam++;
}

void imprimirFila(Fila *fila) {
    Nodo *atual = fila->inicio;
    printf("Fila: ");
    while (atual != NULL) {
        printf("%d ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}


int main() {
    Fila fila;
    inicializaFila(&fila); 
    inserirFinalFila(&fila, 1);
    inserirFinalFila(&fila, 2);
    inserirFinalFila(&fila, 3);
    imprimirFila(&fila); 

    Nodo *lista = NULL;
   // Nodo *pilha = NULL; 
    lista = criaNodo(10);
    lista = inserirInicio(lista, 20);
    lista = inserirInicio(lista, 30); 
    imprimeLista(lista); 

    lista = removerInicio(lista);
    imprimeLista(lista); 
    lista = removerInicio(lista);
    imprimeLista(lista); 
    lista = removerInicio(lista);
    imprimeLista(lista); 

}
