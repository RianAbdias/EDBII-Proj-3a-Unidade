#ifndef ARVORE_ALUNO_H
#define ARVORE_ALUNO_H

#include "Aluno.h"

// Estrutura do nó da Árvore AVL
struct NoAVL {
    Aluno* aluno;
    NoAVL* esquerda;
    NoAVL* direita;
    int altura;
    
    NoAVL(Aluno* aluno) : aluno(aluno), esquerda(nullptr), direita(nullptr), altura(1) {}
};

class Arvore_aluno {
private:
    NoAVL* raiz;
    
    // Métodos auxiliares privados para AVL
    int altura(NoAVL* no);
    int fatorBalanceamento(NoAVL* no);
    int maximo(int a, int b);
    
    // Rotações
    NoAVL* rotacaoDireita(NoAVL* y);
    NoAVL* rotacaoEsquerda(NoAVL* x);
    
    // Operações recursivas
    NoAVL* inserir(NoAVL* no, Aluno* aluno);
    NoAVL* remover(NoAVL* no, int id);
    NoAVL* buscarNo(NoAVL* no, int id);
    NoAVL* encontrarMinimo(NoAVL* no);
    
    // Listagem e destruição
    void listarEmOrdem(NoAVL* no) const;
    void destruir(NoAVL* no);

public:
    Arvore_aluno();
    ~Arvore_aluno();
    
    // Operações públicas da árvore
    void inserir(Aluno* aluno);
    void remover(int id);
    Aluno* buscar(int id);
    
    // Listagem
    void listarAlunos() const;
    
    // Utilitários
    bool estaVazia() const;
};

#endif
