/*Kevin Monteiro do Nascimento Ponciano*/

// Crie em C a estrutura de uma árvore binária cuja informação seja um inteiro.
// Escreva funções que recebam um ponteiro para a raiz da árvore e façam:

// Inserção de um elemento na árvore;
// Pesquisa de um elemento na árvore;
// Exclusão de um elemento na árvore.

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

struct noArvore
{
    int dado;
    struct noArvore *filhoEsquerda;
    struct noArvore *filhoDireita;
};

typedef struct noArvore* arvoreBinaria; // Definindo um ponteiro para a raiz da árvore
typedef struct noArvore noArvore; // Definindo um nó da árvore

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

int excluirNo(arvoreBinaria *raiz, int dado){ // Precisa ser refatorado, algum nó esta perdendo referencia
    if(raiz == NULL){
        return 0;
    }
    noArvore *noAtual = buscarNo(raiz, dado);
    if(noAtual == NULL){
        return 0;
    }
    noArvore *pai = NULL;
    noArvore *filho = NULL;

    if(noAtual->filhoEsquerda == NULL){
        filho = noAtual->filhoDireita;
        }else if(noAtual->filhoDireita == NULL){
            filho = noAtual->filhoEsquerda;
        }else{
            pai = noAtual;
            filho = noAtual->filhoEsquerda;
            while(filho->filhoDireita != NULL){
                pai = filho;
                filho = filho->filhoDireita;
            }
            if(pai != noAtual){
                pai->filhoDireita = filho->filhoEsquerda;
                filho->filhoEsquerda = noAtual->filhoEsquerda;
            }
            filho->filhoDireita = noAtual->filhoDireita;
        }
        if(pai == NULL){
            free(noAtual);
            *raiz = filho;
        }else{
            if(noAtual == pai->filhoDireita){
                pai->filhoDireita = filho;
            }else{
                pai->filhoEsquerda = filho;
            }
            free(noAtual);
        }
        return 1;       
        
}

void imprimeArvorePreOrdem(noArvore *raiz){
    if(raiz != NULL){
        printf("%d ", raiz->dado);
        imprimeArvorePreOrdem(raiz->filhoEsquerda);
        imprimeArvorePreOrdem(raiz->filhoDireita);
    }
}


int main(void){
    arvoreBinaria *raiz = criarArvoreBinaria();
    inserirNo(raiz, 10);
    inserirNo(raiz, 5);
    inserirNo(raiz, 15);
    inserirNo(raiz, 3);
    inserirNo(raiz, 7);
    inserirNo(raiz, 12);
    inserirNo(raiz, 20);
    inserirNo(raiz, 1);
    inserirNo(raiz, 4);
    inserirNo(raiz, 6);
    inserirNo(raiz, 8);
    imprimeArvorePreOrdem(*raiz);
    printf("\n");
    inserirNo(raiz, 11);
    inserirNo(raiz, 13);
    inserirNo(raiz, 18);
    inserirNo(raiz, 25);
    inserirNo(raiz, 2);
    inserirNo(raiz, 9);
    inserirNo(raiz, 14);
    inserirNo(raiz, 17);
    inserirNo(raiz, 19);
    inserirNo(raiz, 24);
    inserirNo(raiz, 26);

    imprimeArvorePreOrdem(*raiz);
    printf("\n");

    noArvore *no = buscarNo(raiz, 15);
    if(no != NULL){
        printf("Nó encontrado: %d\n", no->dado);
    }else{
        printf("Nó não encontrado.\n");
    }
    
    excluirNo(raiz,15);
    imprimeArvorePreOrdem(*raiz);
    printf("\n");

    return 0;
}
    