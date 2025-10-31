// ============================================================================
//         PROJETO TETRIS - DESAFIO DE CÓDIGO 
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5
#define MAX_PILHA 3

typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L' //
    int id;     // Identificador único //
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
    if (filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA;
    f->total++;
}

void removerFila(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return;
    }
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
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Não é possível reservar.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = x;
}

void pop(Pilha *p, Peca *x) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Não é possível usar.\n");
        return;
    }
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
        printf("4 - Mostrar estado atual (fila + pilha)\n");
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
        } else if (opcao == 4) { /* Mostrar estado */
            mostrarFila(&f);
            mostrarPilha(&r);
        }

    } while (opcao != 0);

    return 0;
}

//int main() {

    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.



    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


//    return 0;
//}

