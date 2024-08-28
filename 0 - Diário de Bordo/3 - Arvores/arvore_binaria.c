/*Kevin Monteiro do Nascimento Ponciano*/

// Crie em C a estrutura de uma árvore binária cuja informação seja um inteiro.
// Escreva funções que recebam um ponteiro para a raiz da árvore e façam:

// Inserção de um elemento na árvore;
// Pesquisa de um elemento na árvore;
// Exclusão de um elemento na árvore.

# include <stdio.h>
# include <stdlib.h>

struct noArvore
{
    int dado;
    struct noArvore *filhoEsquerda;
    struct noArvore *filhoDireita;
};

typedef struct noArvore* arvoreBinaria; // Definindo um ponteiro para a raiz da árvore

/*
    Função para criar a árvore binária
    Retorno:
        - Ponteiro para a raiz da árvore
*/
arvoreBinaria *criarArvoreBinaria(){
    arvoreBinaria *raiz = (arvoreBinaria*) malloc(sizeof(arvoreBinaria));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

/*
    Função para criar um nó da árvore
    Parâmetros:
        - int dado: valor a ser inserido no nó
    Retorno:
        - Ponteiro para o nó criado
*/
noArvore *criarNo(int dado){
    noArvore *novoNo = (noArvore*) malloc(sizeof(noArvore));
    if(novoNo == NULL){
        printf("Erro: Falha ao alocar memória para o novo nó.\n");
        exit(-1);
    }
    novoNo->dado = dado;
    novoNo->filhoEsquerda = NULL;
    novoNo->filhoDireita = NULL;
    return novoNo;
}

/*
    Função para inserir um nó na árvore
    Parâmetros:
        - arvoreBinaria *raiz: ponteiro para a raiz da árvore
        - int dado: valor a ser inserido no nó
    Retorno:
        - 1: inserção realizada com sucesso
        - 0: falha ao inserir o nó
*/

int inserirNo(arvoreBinaria *raiz, int dado){
    if(raiz == NULL){
        return 0;
    }
    noArvore *novoNo = criarNo(dado);
    if(*raiz == NULL){ // Se a árvore estiver vazia o novo nó será a raiz
        *raiz = novoNo;
    }else{
        noArvore *atual = *raiz;
        noArvore *anterior = NULL;
        while(atual != NULL){
            anterior = atual;
            if(dado == atual->dado){
                free(novoNo);
                return 0;
            }
            if(dado > atual->dado){
                atual = atual->filhoDireita;
            }else{
                atual = atual->filhoEsquerda;
            }
        }
        if(dado > anterior->dado){
            anterior->filhoDireita = novoNo;
        }else{
            anterior->filhoEsquerda = novoNo;
        }
    }
    return 1;
}

/*
    Função para buscar um nó na árvore
    Parâmetros:
        - arvoreBinaria *raiz: ponteiro para a raiz da árvore
        - int dado: valor a ser buscado
    Retorno:
        - noArvore *: ponteiro para o nó encontrado
        - NULL: nó não encontrado
*/

noArvore *buscarNo(arvoreBinaria *raiz, int dado){
    if(raiz == NULL){
        return NULL;
    }
    noArvore *atual = *raiz;
    while(atual != NULL){
        if(dado == atual->dado){
            return atual;
        }
        if(dado > atual->dado){
            atual = atual->filhoDireita;
        }else{
            atual = atual->filhoEsquerda;
        }
    }
    return NULL;
}

int excluirNo(arvoreBinaria *raiz, int dado){
    if(raiz == NULL){
        return 0;
    }
    noArvore *noAtual = encontrarNo(raiz, dado);
    if(noAtual == NULL){
        return 0;
    }
    noArvore *pai = NULL;
    noArvore *filho = NULL;

    if(noAtual->filhoEsquerda == NULL){
        filho = noAtual->filhoDireita;
        }else if(noAtual->filhoDireita == NULL){
            
    }
    
}