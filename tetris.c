// ============================================================================
//         PROJETO TETRIS - DESAFIO DE CÓDIGO 
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5

typedef struct {
    char nome;  // Tipo da peça: 'I', 'O', 'T', 'L' //
    int id;     // Identificador único //
} Peca;

typedef struct {
    Peca itens[MAX];
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
    return f->total == MAX;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

void inserir(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX; 
    f->total++;
}

void remover(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return;
    }

    *p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX; 
    f->total--;
}

void mostrarFila(Fila *f) {
    int i, idx;
    printf("Fila: ");
    for (i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\n");
}

// Função para gerar nova peça automaticamente //
Peca gerarPeca(int id) {
    Peca nova;
    char tipos[] = {'I', 'O', 'T', 'L'};
    int sorteio = rand() % 4; // gera número entre 0 e 3 //
    nova.nome = tipos[sorteio];
    nova.id = id;
    return nova;
}

int main() {
    Fila f;
    int opcao, idCounter;
    Peca removida, nova;

    inicializarFila(&f);
    srand(time(NULL)); // inicializa gerador de aleatórios //
    idCounter = 1;

    // Inicializa fila com 5 peças //
    while (!filaCheia(&f)) {
        nova = gerarPeca(idCounter++);
        inserir(&f, nova);
    }

    do {
        printf("\n--- Menu ---\n");
        printf("1 - Jogar peça (remover)\n");
        printf("2 - Inserir nova peça\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            remover(&f, &removida);
            printf("Peça jogada: [%c, %d]\n", removida.nome, removida.id);
        } else if (opcao == 2) {
            if (!filaCheia(&f)) {
                nova = gerarPeca(idCounter++);
                inserir(&f, nova);
                printf("Peça inserida: [%c, %d]\n", nova.nome, nova.id);
            } else {
                printf("Fila cheia. Não é possível inserir nova peça.\n");
            }
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

