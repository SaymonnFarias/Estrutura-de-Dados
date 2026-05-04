#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ------------------ STRUCT MUSICA ------------------ //
typedef struct {
    char nomeMusica[50];
    char bandaMusica[50];
    float duracao;
} Musica;

// ------------------ NODO DUPLAMENTE ENCADEADO ------------------ //
typedef struct nodoMusica {
    Musica musica;
    struct nodoMusica *ant;
    struct nodoMusica *prox;
} nodoMusica;

// ------------------ STRUCT PLAYLIST ------------------ //
typedef struct Playlist {
    char nomePlaylist[50];
    nodoMusica *inicio;
    nodoMusica *fim;
    struct Playlist *prox;
} Playlist;

// ------------------ FILA ------------------ //
typedef struct nodoFila {
    Musica musica;
    struct nodoFila *prox;
} nodoFila;

typedef struct {
    nodoFila *inicio;
    nodoFila *fim;
} FilaD;

void inicializaFila(FilaD *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

void enfileira(FilaD *fila, Musica musica) {
    nodoFila *novo = (nodoFila *)malloc(sizeof(nodoFila));
    novo->musica = musica;
    novo->prox = NULL;
    if (fila->fim != NULL)
        fila->fim->prox = novo;
    else
        fila->inicio = novo;
    fila->fim = novo;
}

Musica desenfileira(FilaD *fila) {
    nodoFila *aux = fila->inicio;
    Musica musicaVazia = {"", "", 0};
    if (aux == NULL) //se não tiver nenhuma música na fila
        return musicaVazia;

    Musica musica = aux->musica;
    fila->inicio = aux->prox;
    if (fila->inicio == NULL)
        fila->fim = NULL;
    free(aux);
    return musica;
}

void imprimeFila(FilaD *fila) {
    nodoFila *aux = fila->inicio;
    if (aux == NULL) {
        printf("Fila vazia...\n");
        return;
    }
    printf("Proximas musicas:\n");
    while (aux != NULL) {
        printf("- %s (%s)\n", aux->musica.nomeMusica, aux->musica.bandaMusica);
        aux = aux->prox;
    }
}

// ------------------ PILHA ------------------ //
typedef struct nodoPilha {
    Musica musica;
    struct nodoPilha *prox;
} nodoPilha;

typedef struct {
    nodoPilha *topo;
} PilhaD;

void inicializaPilha(PilhaD *pilha) {
    pilha->topo = NULL;
}

void empilhar(PilhaD *pilha, Musica musica) {
    nodoPilha *novo = (nodoPilha *)malloc(sizeof(nodoPilha));
    novo->musica = musica;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

Musica desempilhar(PilhaD *pilha) {
    Musica musicaVazia = {"", "", 0};
    if (pilha->topo == NULL)
        return musicaVazia;

    nodoPilha *aux = pilha->topo;
    Musica musica = aux->musica;
    pilha->topo = aux->prox;
    free(aux);
    return musica;
}

// ------------------ LISTA DUPLAMENTE ENCADEADA ------------------ //
//Armzena as músicas nas listas (playlists). 
nodoMusica *criaNodo(Musica musica) {
    nodoMusica *novo = (nodoMusica *)malloc(sizeof(nodoMusica));
    novo->musica = musica;
    novo->ant = NULL;
    novo->prox = NULL;
    return novo;
}

void inserirFim(Playlist *p, Musica musica) {
    nodoMusica *novo = criaNodo(musica);
    if (p->inicio == NULL) {
        p->inicio = p->fim = novo;
    } else {
        p->fim->prox = novo;
        novo->ant = p->fim;
        p->fim = novo;
    }
}

void inserirDepoisDe(Playlist *p, char nomeAnt[50], Musica novaMusica) {
    nodoMusica *aux = p->inicio;
    while (aux != NULL && strcmp(aux->musica.nomeMusica, nomeAnt) != 0) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Musica '%s' nao encontrada.\n", nomeAnt);
        return;
    }

    nodoMusica *novo = criaNodo(novaMusica);
    novo->prox = aux->prox;
    novo->ant = aux;

    if (aux->prox != NULL)
        aux->prox->ant = novo;
    else
        p->fim = novo;

    aux->prox = novo;
    printf("Musica inserida apos '%s'.\n", nomeAnt);
}

void removerMusica(Playlist *p, char nomeRemover[50]) {
    nodoMusica *aux = p->inicio;
    while (aux != NULL && strcmp(aux->musica.nomeMusica, nomeRemover) != 0) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Musica '%s' nao encontrada.\n", nomeRemover);
        return;
    }

    if (aux->ant != NULL)
        aux->ant->prox = aux->prox;
    else
        p->inicio = aux->prox;

    if (aux->prox != NULL)
        aux->prox->ant = aux->ant;
    else
        p->fim = aux->ant;

    free(aux); // libera memoria 
    printf("Musica '%s' removida.\n", nomeRemover);
}

void imprimirPlaylist(Playlist *p) {
    nodoMusica *aux = p->inicio;
    if (aux == NULL) {
        printf("Playlist vazia.\n");
        return;
    }
    printf("Musicas da playlist '%s':\n", p->nomePlaylist);
    while (aux != NULL) {
        printf("- %s (%s) : %2.f\n", aux->musica.nomeMusica, aux->musica.bandaMusica, aux->musica.duracao);
        aux = aux->prox;
    }
}

// ------------------ TOCAR PLAYLIST ------------------ //
void tocarPlaylist(Playlist *p, int modoShuffle) {
    if (p->inicio == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    FilaD fila;
    PilhaD pilha;
    inicializaFila(&fila);
    inicializaPilha(&pilha);

    nodoMusica *aux = p->inicio; //ponteiro para o inicio daa playlist 
    int count = 0;
    //retorna o tamanho da playlist (quantidade de musicas)
    while (aux != NULL) {
        count++;
        aux = aux->prox;
    }

    Musica vetor[count]; //cria um vetor com tamanho igual ao numero de musicas na playlist 
    aux = p->inicio;
    for (int i = 0; i < count; i++) {
        vetor[i] = aux->musica; 
        aux = aux->prox;
    }

    if (modoShuffle) {
        srand(time(NULL)); // chamada de função para aleatoriedade de reprodução 
        for (int i = count - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Musica temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }
    //define a fila de proximas musicas 
    for (int i = 0; i < count; i++)
        enfileira(&fila, vetor[i]); 

    char opcao;
    Musica atual = desenfileira(&fila);

    //menu de opções 
    while (1) {
        printf("\nTocando: %s (%s)\n", atual.nomeMusica, atual.bandaMusica);
        printf("[N] Proxima | [V] Voltar | [L] Lista proximas | [S] Sair\n");
        scanf(" %c", &opcao);

        if (opcao == 'N' || opcao == 'n') {
            empilhar(&pilha, atual); // empilha a musica que esta tocando 
            Musica prox = desenfileira(&fila); // desenfileira da lista de proximas 
            if (strcmp(prox.nomeMusica, "") == 0) {
                printf("Fim da playlist.\n");
                break;
            }
            atual = prox;
        } else if (opcao == 'V' || opcao == 'v') {
            Musica anterior = desempilhar(&pilha); // desempilha a musica tocada anteriormente 
            if (strcmp(anterior.nomeMusica, "") == 0) {
                printf("Sem musica anterior.\n");
            } else {
                enfileira(&fila, atual);
                atual = anterior;
            }
        } else if (opcao == 'L' || opcao == 'l') {
            imprimeFila(&fila);
        } else if (opcao == 'S' || opcao == 's') {
            break;
        }
    }
}

// ------------------ GERENCIAR PLAYLISTS ------------------ //
Playlist *criarPlaylist(Playlist **listaPlaylists, char nome[50]) {
    Playlist *nova = (Playlist *)malloc(sizeof(Playlist));
    strcpy(nova->nomePlaylist, nome);
    nova->inicio = NULL; // inicialização da playlist 
    nova->fim = NULL;
    nova->prox = *listaPlaylists;
    *listaPlaylists = nova;
    return nova;
}

Playlist *buscarPlaylist(Playlist *lista, char nome[50]) {
    Playlist *aux = lista;
    while (aux != NULL && strcmp(aux->nomePlaylist, nome) != 0) // compara as strings 
        aux = aux->prox;
    return aux;
}

// ------------------ MAIN ------------------ //
int main() {
    Playlist *listaPlaylists = NULL;
    int opcao;
    char nomePlaylist[50];

    while (1) {
        printf("\n1 - Criar playlist\n2 - Inserir musica\n3 - Inserir musica apos outra (meio)\n4 - Ver playlist\n5 - Tocar playlist\n6 - Remover musica\n7 - Sair\nOpcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            printf("Nome da nova playlist: ");
            fgets(nomePlaylist, 50, stdin); // lendo string de no max 49 char e armazenando no vetor nomePlaylist.
            nomePlaylist[strcspn(nomePlaylist, "\n")] = 0; // retorna o indice do primeiro \n e remove ele 
                                                           // substituímos o \n por '\0', que é o terminador de string em C
            Playlist *p = buscarPlaylist(listaPlaylists, nomePlaylist);
            if (p != NULL) {


                printf("Ja existe uma playlist com esse nome.\n");
                continue;
            }

            criarPlaylist(&listaPlaylists, nomePlaylist);
            printf("Playlist '%s' criada com sucesso!\n", nomePlaylist);
                
        } else if (opcao == 2) {
            printf("Nome da playlist: ");
            fgets(nomePlaylist, 50, stdin);
            nomePlaylist[strcspn(nomePlaylist, "\n")] = 0;
            Playlist *p = buscarPlaylist(listaPlaylists, nomePlaylist);
            if (p == NULL) {
                printf("Playlist nao encontrada.\n");
                continue;
            }
            Musica m;
            printf("Nome da musica: ");
            fgets(m.nomeMusica, 50, stdin);
            m.nomeMusica[strcspn(m.nomeMusica, "\n")] = 0;
            printf("Banda: ");
            fgets(m.bandaMusica, 50, stdin);
            m.bandaMusica[strcspn(m.bandaMusica, "\n")] = 0;
            printf("Duracao: ");
            scanf("%f", &m.duracao);
            getchar();
            inserirFim(p, m);
        } else if (opcao == 3) {
            printf("Nome da playlist: ");
            fgets(nomePlaylist, 50, stdin);
            nomePlaylist[strcspn(nomePlaylist, "\n")] = 0;
            Playlist *p = buscarPlaylist(listaPlaylists, nomePlaylist);
            if (p == NULL) {
                printf("Playlist nao encontrada.\n");
                continue;
            }
            char nomeAnt[50];
            printf("Inserir apos qual musica: ");
            fgets(nomeAnt, 50, stdin);
            nomeAnt[strcspn(nomeAnt, "\n")] = 0;

            Musica m;
            printf("Nome da nova musica: ");
            fgets(m.nomeMusica, 50, stdin);
            m.nomeMusica[strcspn(m.nomeMusica, "\n")] = 0;
            printf("Banda: ");
            fgets(m.bandaMusica, 50, stdin);
            m.bandaMusica[strcspn(m.bandaMusica, "\n")] = 0;
            printf("Duracao: ");
            scanf("%f", &m.duracao);
            getchar();

            inserirDepoisDe(p, nomeAnt, m);
        } else if (opcao == 4) {
            printf("Nome da playlist: ");
            fgets(nomePlaylist, 50, stdin);
            nomePlaylist[strcspn(nomePlaylist, "\n")] = 0;
            Playlist *p = buscarPlaylist(listaPlaylists, nomePlaylist);
            if (p != NULL)
                imprimirPlaylist(p);
            else
                printf("Playlist nao encontrada.\n");
        } else if (opcao == 5) {
            printf("Nome da playlist: ");
            fgets(nomePlaylist, 50, stdin);
            nomePlaylist[strcspn(nomePlaylist, "\n")] = 0;
            Playlist *p = buscarPlaylist(listaPlaylists, nomePlaylist);
            if (p == NULL) {
                printf("Playlist nao encontrada.\n");
                continue;
            }
            int modo;
            printf("Modo 1 - Sequencial | 2 - Shuffle: ");
            scanf("%d", &modo);
            tocarPlaylist(p, modo == 2);
        } else if (opcao == 6) {
            printf("Nome da playlist: ");
            fgets(nomePlaylist, 50, stdin);
            nomePlaylist[strcspn(nomePlaylist, "\n")] = 0;
            Playlist *p = buscarPlaylist(listaPlaylists, nomePlaylist);
            if (p == NULL) {
                printf("Playlist nao encontrada.\n");
                continue;
            }
            imprimirPlaylist(p);
            char nomeRemover[50];
            printf("Remover qual musica: ");
            fgets(nomeRemover, 50, stdin);
            nomeRemover[strcspn(nomeRemover, "\n")] = 0;
            removerMusica(p, nomeRemover);
        } else if (opcao == 7) {
            break;
        }
    }
    return 0;
}
