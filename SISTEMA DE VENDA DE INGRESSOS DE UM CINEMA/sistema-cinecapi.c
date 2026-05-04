#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 100

// Estrutura do ingresso
typedef struct {
    char nomeFilme[50];
    char sala[5];
    float horario;
    float valor;
} Ingresso;

// Estrutura do cliente
typedef struct {
    char nomeCliente[50];
    Ingresso ingresso;
} Cliente;

// Estrutura da pilha de ingressos
typedef struct {
    Ingresso itens[MAX_SIZE];
    int topo;
} Pilha;

// Estrutura da fila circular de clientes
typedef struct {
    Cliente fila[MAX_SIZE];
    int inicio, fim, qtd;
} Fila;

// Funções da Pilha
void inicializaPilha(Pilha* pilha) {
    pilha->topo = -1;
}

int vaziaPilha(Pilha* pilha) {
    return (pilha->topo == -1);
}

int cheiaPilha(Pilha* pilha) {
    return (pilha->topo == MAX_SIZE - 1);
}

void push(Pilha* pilha, Ingresso ing) {
    if (cheiaPilha(pilha)) {
        printf("Erro: Pilha de ingressos cheia!\n");
        return;
    }
    pilha->itens[++pilha->topo] = ing;
}

Ingresso pop(Pilha* pilha) {
    Ingresso vazio = {"", "", 0.0, 0.0};
    if (vaziaPilha(pilha)) {
        printf("Erro: Pilha de ingressos vazia!\n");
        return vazio;
    }
    return pilha->itens[pilha->topo--];
}

void mostrarPilhaIngressos(Pilha* pilha) {
    if (vaziaPilha(pilha)) {
        printf("Nenhum ingresso disponivel!\n");
        return;
    }
    printf("\n--- Ingressos disponiveis ---\n");
    for (int i = pilha->topo; i >= 0; i--) {
        printf("Filme: %s | Sala: %s | Horario: %.2f | Valor: R$%.2f\n",
               pilha->itens[i].nomeFilme,
               pilha->itens[i].sala,
               pilha->itens[i].horario,
               pilha->itens[i].valor);
    }
}

// Funções da Fila Circular
void inicializaFila(Fila* fila) {
    fila->inicio = 0;
    fila->fim = -1;
    fila->qtd = 0;
}

int vaziaFila(Fila* fila) {
    return (fila->qtd == 0);
}

int cheiaFila(Fila* fila) {
    return (fila->qtd == MAX_SIZE);
}

void enfileira(Fila* fila, Cliente c) {
    if (cheiaFila(fila)) {
        printf("Erro: Fila cheia!\n");
        return;
    }
    fila->fim = (fila->fim + 1) % MAX_SIZE;
    fila->fila[fila->fim] = c;
    fila->qtd++;
}

Cliente desenfileira(Fila* fila) {
    Cliente vazio = {"", {"", "", 0.0, 0.0}};
    if (vaziaFila(fila)) {
        printf("Erro: Fila vazia!\n");
        return vazio;
    }
    Cliente c = fila->fila[fila->inicio];
    fila->inicio = (fila->inicio + 1) % MAX_SIZE;
    fila->qtd--;
    return c;
}

// Catálogo de ingressos
const char* filmes[] = {"DARCIMUS", "TUIUTAS", "ZECAS"};
const char* salas[]  = {"A", "B", "C"};
float horarios[]     = {18.30, 19.00, 20.30};
float valorIngresso  = 20.0;
int totalOpcoes = 3;

// Preencher a pilha com ingressos aleatórios
void preencherPilhaIngressos(Pilha* p, int qtd) {
    for (int i = 0; i < qtd; i++) {
        Ingresso ing;
        int idx = rand() % totalOpcoes;//variavel auxiliar
        strcpy(ing.nomeFilme, filmes[idx]);
        strcpy(ing.sala, salas[idx]);
        ing.horario = horarios[idx];
        ing.valor = valorIngresso;
        push(p, ing);
    }
}

// Programa principal
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilhaIngressos;
    int qtdIngressos;
    int opcao;

    inicializaFila(&fila);
    inicializaPilha(&pilhaIngressos);

    printf("Quantos ingressos teremos disponiveis hoje? ");
    scanf("%d", &qtdIngressos);
    preencherPilhaIngressos(&pilhaIngressos, qtdIngressos);

    do {
        printf("\n=== SISTEMA CINECAPI ===\n");
        printf("1. Adicionar cliente (compra ingresso)\n");
        printf("2. Mostrar os clientes da fila\n");
        printf("3. Liberar cliente da fila\n");
        printf("4. Mostrar ingressos disponiveis\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch(opcao) {
            case 1: {
                if (vaziaPilha(&pilhaIngressos)) {
                    printf("Nao tem mais ingressos disponiveis!\n");
                    break;
                }
                char nomeCliente[50];
                printf("Digite o nome do cliente: ");
                scanf(" %[^\n]", nomeCliente); //ler todos os caracteres até o /n e ignorar os espaços 

                Cliente novo;
                strcpy(novo.nomeCliente, nomeCliente);
                novo.ingresso = pop(&pilhaIngressos);

                enfileira(&fila, novo);
                printf("Cliente '%s' comprou ingresso para '%s'.\n",
                       novo.nomeCliente, novo.ingresso.nomeFilme);
                break;
            }
            case 2: {
                if (vaziaFila(&fila)) {
                    printf("Fila vazia!\n");
                } else {
                    printf("\n--- Fila de clientes ---\n");
                    int idx = fila.inicio;
                    for (int i = 0; i < fila.qtd; i++) {
                        Cliente c = fila.fila[idx];
                        printf("%d) %s -> Filme: %s, Sala: %s, Horario: %.2f\n",
                               i+1, c.nomeCliente,
                               c.ingresso.nomeFilme,
                               c.ingresso.sala,
                               c.ingresso.horario);
                        idx = (idx + 1) % MAX_SIZE;
                    }
                }
                break;
            }
            case 3: {
                if (vaziaFila(&fila)) {
                    printf("Fila vazia!\n");
                } else {
                    Cliente c = desenfileira(&fila);
                    printf("Cliente '%s' entrou na sala para assistir '%s'.\n",
                           c.nomeCliente, c.ingresso.nomeFilme);
                }
                break;
            }
            case 4: {
                mostrarPilhaIngressos(&pilhaIngressos);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
