#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDEM 3 

typedef struct NoB {
    int chaves[2 * ORDEM - 1];         // Array de chaves
    struct NoB* filhos[2 * ORDEM];     // Ponteiros para filhos
    int numChaves;                     // Número de chaves atualmente no nó
    bool folha;                        // Verdadeiro se o nó for folha
} NoB;

// Função para criar um novo nó
NoB* criarNo(bool folha) {
    NoB* novoNo = (NoB*)malloc(sizeof(NoB));
    novoNo->folha = folha;
    novoNo->numChaves = 0;
    for (int i = 0; i < 2 * ORDEM; i++) {
        novoNo->filhos[i] = NULL;
    }
    return novoNo;
}

// Função para dividir um filho cheio
void dividirFilho(NoB* pai, int i, NoB* filho) {
    NoB* novoNo = criarNo(filho->folha);
    novoNo->numChaves = ORDEM - 1;

    // Copia as últimas (ORDEM - 1) chaves do filho para o novo nó
    for (int j = 0; j < ORDEM - 1; j++) {
        novoNo->chaves[j] = filho->chaves[j + ORDEM];
    }

    // Se o filho não for folha, copie os filhos também
    if (!filho->folha) {
        for (int j = 0; j < ORDEM; j++) {
            novoNo->filhos[j] = filho->filhos[j + ORDEM];
        }
    }

    filho->numChaves = ORDEM - 1;

    // Move os filhos do pai para dar espaço ao novo filho
    for (int j = pai->numChaves; j >= i + 1; j--) {
        pai->filhos[j + 1] = pai->filhos[j];
    }
    pai->filhos[i + 1] = novoNo;

    // Move as chaves do pai para dar espaço à nova chave
    for (int j = pai->numChaves - 1; j >= i; j--) {
        pai->chaves[j + 1] = pai->chaves[j];
    }

    // Coloca a chave mediana do filho no pai
    pai->chaves[i] = filho->chaves[ORDEM - 1];
    pai->numChaves++;
}

// Função para inserir uma chave no nó não cheio
void inserirNoNaoCheio(NoB* no, int chave) {
    int i = no->numChaves - 1;

    if (no->folha) {
        while (i >= 0 && chave < no->chaves[i]) {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        no->numChaves++;
    } else {
        while (i >= 0 && chave < no->chaves[i]) {
            i--;
        }
        i++;

        if (no->filhos[i]->numChaves == 2 * ORDEM - 1) {
            dividirFilho(no, i, no->filhos[i]);
            if (chave > no->chaves[i]) {
                i++;
            }
        }
        inserirNoNaoCheio(no->filhos[i], chave);
    }
}

// Função principal para inserir uma chave na árvore B
NoB* inserir(NoB* raiz, int chave) {
    if (raiz->numChaves == 2 * ORDEM - 1) {
        NoB* novaRaiz = criarNo(false);
        novaRaiz->filhos[0] = raiz;
        dividirFilho(novaRaiz, 0, raiz);

        int i = 0;
        if (novaRaiz->chaves[0] < chave) {
            i++;
        }
        inserirNoNaoCheio(novaRaiz->filhos[i], chave);
        return novaRaiz;
    } else {
        inserirNoNaoCheio(raiz, chave);
        return raiz;
    }
}

// Função auxiliar para encontrar o predecessor de uma chave em um nó
int encontrarPredecessor(NoB* no) {
    while (!no->folha) {
        no = no->filhos[no->numChaves];
    }
    return no->chaves[no->numChaves - 1];
}

// Função para remover uma chave de um nó
NoB* remover(NoB* no, int chave) {
    int i;
    for (i = 0; i < no->numChaves && no->chaves[i] < chave; i++);

    if (i < no->numChaves && no->chaves[i] == chave) {
        if (no->folha) {
            for (int j = i; j < no->numChaves - 1; j++) {
                no->chaves[j] = no->chaves[j + 1];
            }
            no->numChaves--;
        } else {
            int predecessor = encontrarPredecessor(no->filhos[i]);
            no->chaves[i] = predecessor;
            no->filhos[i] = remover(no->filhos[i], predecessor);
        }
    } else if (!no->folha) {
        no->filhos[i] = remover(no->filhos[i], chave);
    }
    return no;
}

// Função para imprimir a árvore B em ordem crescente
void imprimir(NoB* no) {
    if (no != NULL) {
        for (int i = 0; i < no->numChaves; i++) {
            imprimir(no->filhos[i]);
            printf("%d ", no->chaves[i]);
        }
        imprimir(no->filhos[no->numChaves]);
    }
}

// Função principal para testar a árvore B
int main() {
    NoB* raiz = criarNo(true);  // Inicializa a árvore B com raiz como folha

    int chaves[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int tamanho = sizeof(chaves) / sizeof(chaves[0]);

    for (int i = 0; i < tamanho; i++) {
        raiz = inserir(raiz, chaves[i]);
    }

    printf("Árvore B em ordem:\n");
    imprimir(raiz);
    printf("\n");

    // Remover uma chave
    int chaveRemover = 6;
    raiz = remover(raiz, chaveRemover);
    printf("Árvore B após remover %d:\n", chaveRemover);
    imprimir(raiz);
    printf("\n");

    return 0;
}
