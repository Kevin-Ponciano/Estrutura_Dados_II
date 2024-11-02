#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura de nó da Treap, contendo chave e prioridade
typedef struct Node {
    int key, priority;     // key é a chave do BST e priority é a prioridade do heap
    struct Node *left, *right;  // ponteiros para os filhos esquerdo e direito
} Node;

// Função para criar um novo nó da Treap com chave e prioridade aleatória
Node* novoNo(int key) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->key = key;
    temp->priority = rand() % 100; // Define uma prioridade aleatória
    temp->left = temp->right = NULL; // Inicializa filhos como NULL
    return temp;
}

// Rotação à direita para manter a propriedade de heap
Node* rotacaoDireita(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    return x; // Retorna nova raiz após rotação
}

// Rotação à esquerda para manter a propriedade de heap
Node* rotacaoEsquerda(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    return y; // Retorna nova raiz após rotação
}

// Função para inserir um novo nó na Treap
Node* inserir(Node* raiz, int key) {
    if (!raiz) return novoNo(key); // Insere o nó se a raiz estiver vazia

    // Inserção estilo BST
    if (key < raiz->key) {
        raiz->left = inserir(raiz->left, key);

        // Verifica a prioridade e realiza rotação, se necessário
        if (raiz->left->priority > raiz->priority)
            raiz = rotacaoDireita(raiz);
    } else {
        raiz->right = inserir(raiz->right, key);

        // Verifica a prioridade e realiza rotação, se necessário
        if (raiz->right->priority > raiz->priority)
            raiz = rotacaoEsquerda(raiz);
    }
    return raiz; // Retorna a raiz modificada da Treap
}

// Função para remover um nó com determinada chave da Treap
Node* remover(Node* raiz, int key) {
    if (!raiz) return raiz; // Retorna NULL se a árvore estiver vazia

    // Pesquisa estilo BST para encontrar o nó a ser removido
    if (key < raiz->key)
        raiz->left = remover(raiz->left, key);
    else if (key > raiz->key)
        raiz->right = remover(raiz->right, key);
    else {
        // Nó encontrado: realiza remoção
        if (!raiz->left) {
            Node* temp = raiz->right;
            free(raiz);
            raiz = temp;
        } else if (!raiz->right) {
            Node* temp = raiz->left;
            free(raiz);
            raiz = temp;
        } else if (raiz->left->priority < raiz->right->priority) {
            // Rotação à esquerda para priorizar o nó direito
            raiz = rotacaoEsquerda(raiz);
            raiz->left = remover(raiz->left, key);
        } else {
            // Rotação à direita para priorizar o nó esquerdo
            raiz = rotacaoDireita(raiz);
            raiz->right = remover(raiz->right, key);
        }
    }
    return raiz; // Retorna a raiz após remoção e rotações
}

// Função de impressão em pré-ordem (raiz, esquerda, direita)
void imprimirPreOrdem(Node* raiz) {
    if (raiz) {
        printf("(%d, %d) ", raiz->key, raiz->priority); // Imprime chave e prioridade
        imprimirPreOrdem(raiz->left);
        imprimirPreOrdem(raiz->right);
    }
}

// Função de impressão em in-ordem (esquerda, raiz, direita)
void imprimirInOrdem(Node* raiz) {
    if (raiz) {
        imprimirInOrdem(raiz->left);
        printf("(%d, %d) ", raiz->key, raiz->priority); // Imprime chave e prioridade
        imprimirInOrdem(raiz->right);
    }
}

// Função de impressão em pós-ordem (esquerda, direita, raiz)
void imprimirPosOrdem(Node* raiz) {
    if (raiz) {
        imprimirPosOrdem(raiz->left);
        imprimirPosOrdem(raiz->right);
        printf("(%d, %d) ", raiz->key, raiz->priority); // Imprime chave e prioridade
    }
}

// Função principal para testar a Treap
int main() {
    srand(time(NULL)); // Semente para gerar prioridades aleatórias
    Node* raiz = NULL;

    int chaves[] = {10, 20, 30, 40, 50, 25};
    int tamanho = sizeof(chaves) / sizeof(chaves[0]);

    // Inserindo elementos na Treap
    for (int i = 0; i < tamanho; i++) {
        raiz = inserir(raiz, chaves[i]);
    }

    // Imprimindo a Treap em diferentes ordens
    printf("Treap após inserções (Pré-Ordem):\n");
    imprimirPreOrdem(raiz);
    printf("\n");

    printf("Treap após inserções (In-Ordem):\n");
    imprimirInOrdem(raiz);
    printf("\n");

    printf("Treap após inserções (Pós-Ordem):\n");
    imprimirPosOrdem(raiz);
    printf("\n");

    // Removendo um elemento e mostrando a estrutura após remoção
    raiz = remover(raiz, 30);
    printf("Treap após remoção de 30 (Pré-Ordem):\n");
    imprimirPreOrdem(raiz);
    printf("\n");

    return 0;
}
