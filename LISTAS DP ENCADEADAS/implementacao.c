#include <stdio.h>
#include <stdlib.h>

//Estrutura básica
typedef struct nodoDuplo{
    int valor;
    struct nodoDuplo *prox;
    struct nodoDuplo *ant; 
}nodoDuplo;


//Inicialização 
nodoDuplo *criaNodoDuplo(int valor){
    nodoDuplo *novo = (nodoDuplo*)malloc(sizeof(nodoDuplo)); //aloca epaço em memória
    if(novo==NULL){ //verifica se ouve erro ao alocar memoria 
        printf("Erro ao alocar memoria!\n");
        exit(1); 
    }

    novo->valor = valor; // atribui o valor passado
    novo->prox = NULL; // o próximo é nulo
    novo->ant = NULL; // o anterior é nulo
    return novo; 
}
//Inserção no inicio
nodoDuplo* inserirInicio(nodoDuplo *lista, int valor){
    Nodo *novo = criaNodoDuplo(valor); 
    if(lista == NULL){
        lista = novo;
        return novo; 
    }
    novo->prox = lista;
    lista->ant = novo;
    novo ->prox = lista; //lliga o novo no na lista 
    return novo; 
}
//Inserção no meio
nodoDuplo* inserirMeio(nodoDuplo *lista, int valor){
    nodoDuplo *novo = criarNodoDuplo(valor);
    nodoDuplo *temp = lista;
    while(temp->prox != NULL){
        temp = temp->prox;
    }
    temp->prox = novo;
    novo->ant = temp;
    novo->prox = lista;  //  liga o novo nó na lista
    return novo;
}
//Inserção no fim 
nodoDuplo* inserirFim(nodoDuplo *lista, int valor){
    nodoDuplo *novo = criarNodoDuplo(valor);
    nodoDuplo *temp = lista;
    while(temp->prox != NULL){
        temp = temp->prox;
    }
    temp->prox = novo;
    novo->ant = temp;
    novo->prox = lista;  //  liga o novo nó na lista
    return novo;
}
