#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5        // Tamanho fixo da fila

// Estrutura que representa uma peça
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX];
    int frente, tras, qtd;
} Fila;

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->qtd = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->qtd == MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->qtd == 0;
}

// Gera uma peça auto
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];         // escolhe aleatoriamente o tipo
    nova.id = id;
    return nova;
}

// Insere uma peça no final da fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("\n?? A fila esta cheia! Nao e possivel inserir nova peca.\n");
        return;
    }
    f->tras = (f->tras + 1) % MAX;
    f->itens[f->tras] = p;
    f->qtd++;
}

// Remove uma peça da frente da fila (dequeue)
void dequeue(Fila *f) {
    if (filaVazia(f)) {
        printf("\n?? A fila esta vazia! Nao ha pecas para jogar.\n");
        return;
    }
    Peca removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX;
    f->qtd--;

    printf("\n?? Voce jogou a peca: [%c %d]\n", removida.nome, removida.id);
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("\nFila vazia.\n");
        return;
    }

    printf("\nFila de pecas:\n");
    int i, idx;
    for (i = 0; i < f->qtd; i++) {
        idx = (f->frente + i) % MAX;
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

int main() {
    Fila fila;
    int opcao, idCounter = 0;

    srand(time(NULL));                  // inicializa semente para números aleatórios
    inicializarFila(&fila);

    // Inicializa a fila com 5 peças
    int i;
    for ( i = 0; i < MAX; i++) {
        enqueue(&fila, gerarPeca(idCounter++));
    }

    do {
        exibirFila(&fila);

        printf("\nOpcoes de acao:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue(&fila);
                break;
            case 2:
                enqueue(&fila, gerarPeca(idCounter++));
                break;
            case 0:
                printf("\nEncerrando o jogo...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
