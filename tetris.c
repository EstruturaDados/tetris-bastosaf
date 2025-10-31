// ============================================================================
//         PROJETO TETRIS - DESAFIO DE CÓDIGO 
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

typedef struct {
    char nome;  /* Tipo da peça: 'I', 'O', 'T', 'L' */
    int id;     /* Identificador único */
} Peca;

/* ---------- FILA ---------- */
typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

void inserirFila(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

void removerFila(Fila *f, Peca *p) {
    if (filaVazia(f)) return;
    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA;
    f->total--;
}

void mostrarFila(Fila *f) {
    int i, idx;
    printf("Fila: ");
    for (i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX_FILA) {
        printf("[%c, %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

/* ---------- PILHA ---------- */
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) return;
    p->topo++;
    p->itens[p->topo] = x;
}

void pop(Pilha *p, Peca *x) {
    if (pilhaVazia(p)) return;
    *x = p->itens[p->topo];
    p->topo--;
}

void mostrarPilha(Pilha *p) {
    int i;
    printf("Pilha (topo -> base): ");
    for (i = p->topo; i >= 0; i--) {
        printf("[%c, %d] ", p->itens[i].nome, p->itens[i].id);
    }
    printf("\n");
}

/* ---------- GERADOR DE PEÇAS ---------- */
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int sorteio = rand() % 4;
    nova.nome = tipos[sorteio];
    nova.id = id;
    return nova;
}

/* ---------- TROCAS ---------- */
void trocarAtual(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Não foi possível trocar (fila ou pilha vazia).\n");
        return;
    }
    Peca temp = f->itens[f->inicio];
    f->itens[f->inicio] = p->itens[p->topo];
    p->itens[p->topo] = temp;
    printf("Troca realizada entre a frente da fila e o topo da pilha.\n");
}

void trocaMultipla(Fila *f, Pilha *p) {
    if (f->total < 3 || p->topo < 2) {
        printf("Não foi possível realizar troca múltipla (precisa de 3 peças em cada).\n");
        return;
    }
    int i, idx = f->inicio;
    for (i = 0; i < 3; i++) {
        Peca temp = f->itens[(idx + i) % MAX_FILA];
        f->itens[(idx + i) % MAX_FILA] = p->itens[p->topo - i];
        p->itens[p->topo - i] = temp;
    }
    printf("Troca múltipla realizada entre 3 peças da fila e 3 da pilha.\n");
}

/* ---------- MAIN ---------- */
int main() {
    Fila f;
    Pilha r;
    int opcao, idCounter;
    Peca removida, nova;

    inicializarFila(&f);
    inicializarPilha(&r);
    srand(time(NULL));
    idCounter = 1;

    /* Inicializa fila com 5 peças */
    while (!filaCheia(&f)) {
        nova = gerarPeca(idCounter++);
        inserirFila(&f, nova);
    }

    do {
        printf("\n--- Menu ---\n");
        printf("1 - Jogar peça (remover da fila)\n");
        printf("2 - Reservar peça (mover fila -> pilha)\n");
        printf("3 - Usar peça reservada (remover pilha)\n");
        printf("4 - Trocar peça atual (fila <-> pilha)\n");
        printf("5 - Troca múltipla (3 peças)\n");
        printf("6 - Mostrar estado atual\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) { /* Jogar peça */
            removerFila(&f, &removida);
            printf("Peça jogada: [%c, %d]\n", removida.nome, removida.id);
            nova = gerarPeca(idCounter++);
            inserirFila(&f, nova);

        } else if (opcao == 2) { /* Reservar peça */
            if (!filaVazia(&f) && !pilhaCheia(&r)) {
                removerFila(&f, &removida);
                push(&r, removida);
                printf("Peça reservada: [%c, %d]\n", removida.nome, removida.id);
                nova = gerarPeca(idCounter++);
                inserirFila(&f, nova);
            } else {
                printf("Não foi possível reservar (fila vazia ou pilha cheia).\n");
            }

        } else if (opcao == 3) { /* Usar peça reservada */
            if (!pilhaVazia(&r)) {
                pop(&r, &removida);
                printf("Peça usada da reserva: [%c, %d]\n", removida.nome, removida.id);
            } else {
                printf("Pilha de reserva vazia.\n");
            }

        } else if (opcao == 4) { /* Trocar peça atual */
            trocarAtual(&f, &r);

        } else if (opcao == 5) { /* Troca múltipla */
            trocaMultipla(&f, &r);

        } else if (opcao == 6) { /* Mostrar estado */
            mostrarFila(&f);
            mostrarPilha(&r);
        }

    } while (opcao != 0);

    return 0;
}
