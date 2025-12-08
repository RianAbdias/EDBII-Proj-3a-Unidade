#include "Arvore_aluno.h"
#include <iostream>
#include <iomanip>

// ============================================
// Construtor e Destrutor
// ============================================

Arvore_aluno::Arvore_aluno() : raiz(nullptr) {}

Arvore_aluno::~Arvore_aluno() {
    destruir(raiz);
}

void Arvore_aluno::destruir(NoAVL* no) {
    if (no != nullptr) {
        destruir(no->esquerda);
        destruir(no->direita);
        delete no->aluno;  // Deleta o aluno
        delete no;         // Deleta o nó
    }
}

// ============================================
// Métodos Auxiliares
// ============================================

int Arvore_aluno::altura(NoAVL* no) {
    if (no == nullptr) return 0;
    return no->altura;
}

int Arvore_aluno::maximo(int a, int b) {
    return (a > b) ? a : b;
}

int Arvore_aluno::fatorBalanceamento(NoAVL* no) {
    if (no == nullptr) return 0;
    return altura(no->esquerda) - altura(no->direita);
}

// ============================================
// Rotações AVL
// ============================================

// Rotação simples à direita
NoAVL* Arvore_aluno::rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esquerda;
    NoAVL* T2 = x->direita;
    
    // Realiza a rotação
    x->direita = y;
    y->esquerda = T2;
    
    // Atualiza alturas
    y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;
    
    return x;
}

// Rotação simples à esquerda
NoAVL* Arvore_aluno::rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->direita;
    NoAVL* T2 = y->esquerda;
    
    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;
    
    // Atualiza alturas
    x->altura = maximo(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = maximo(altura(y->esquerda), altura(y->direita)) + 1;
    
    return y;
}

// ============================================
// Inserção com Balanceamento AVL
// ============================================

NoAVL* Arvore_aluno::inserir(NoAVL* no, Aluno* aluno) {
    // 1. Inserção normal de BST
    if (no == nullptr) {
        return new NoAVL(aluno);
    }
    
    if (aluno->getId() < no->aluno->getId()) {
        no->esquerda = inserir(no->esquerda, aluno);
    } else if (aluno->getId() > no->aluno->getId()) {
        no->direita = inserir(no->direita, aluno);
    } else {
        // ID duplicado - não insere
        return no;
    }
    
    // 2. Atualiza a altura do nó ancestral
    no->altura = 1 + maximo(altura(no->esquerda), altura(no->direita));
    
    // 3. Obtém o fator de balanceamento
    int balance = fatorBalanceamento(no);
    
    // 4. Casos de desbalanceamento
    
    // Caso Esquerda-Esquerda
    if (balance > 1 && aluno->getId() < no->esquerda->aluno->getId()) {
        return rotacaoDireita(no);
    }
    
    // Caso Direita-Direita
    if (balance < -1 && aluno->getId() > no->direita->aluno->getId()) {
        return rotacaoEsquerda(no);
    }
    
    // Caso Esquerda-Direita
    if (balance > 1 && aluno->getId() > no->esquerda->aluno->getId()) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }
    
    // Caso Direita-Esquerda
    if (balance < -1 && aluno->getId() < no->direita->aluno->getId()) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }
    
    return no;
}

void Arvore_aluno::inserir(Aluno* aluno) {
    raiz = inserir(raiz, aluno);
}

// ============================================
// Remoção com Balanceamento AVL
// ============================================

NoAVL* Arvore_aluno::encontrarMinimo(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esquerda != nullptr) {
        atual = atual->esquerda;
    }
    return atual;
}

NoAVL* Arvore_aluno::remover(NoAVL* no, int id) {
    // 1. Remoção normal de BST
    if (no == nullptr) {
        return no;
    }
    
    if (id < no->aluno->getId()) {
        no->esquerda = remover(no->esquerda, id);
    } else if (id > no->aluno->getId()) {
        no->direita = remover(no->direita, id);
    } else {
        // Encontrou o nó a ser removido
        
        // Nó com um filho ou sem filhos
        if (no->esquerda == nullptr || no->direita == nullptr) {
            NoAVL* temp = no->esquerda ? no->esquerda : no->direita;
            
            // Sem filhos
            if (temp == nullptr) {
                temp = no;
                no = nullptr;
            } else {
                // Um filho - copia o conteúdo do filho
                *no = *temp;
            }
            
            delete temp->aluno;
            delete temp;
        } else {
            // Nó com dois filhos: obtém o sucessor in-order (menor da subárvore direita)
            NoAVL* temp = encontrarMinimo(no->direita);
            
            // Copia os dados do sucessor para este nó
            no->aluno = temp->aluno;
            
            // Remove o sucessor
            no->direita = remover(no->direita, temp->aluno->getId());
        }
    }
    
    // Se a árvore tinha apenas um nó
    if (no == nullptr) {
        return no;
    }
    
    // 2. Atualiza a altura do nó atual
    no->altura = 1 + maximo(altura(no->esquerda), altura(no->direita));
    
    // 3. Obtém o fator de balanceamento
    int balance = fatorBalanceamento(no);
    
    // 4. Casos de desbalanceamento
    
    // Caso Esquerda-Esquerda
    if (balance > 1 && fatorBalanceamento(no->esquerda) >= 0) {
        return rotacaoDireita(no);
    }
    
    // Caso Esquerda-Direita
    if (balance > 1 && fatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacaoEsquerda(no->esquerda);
        return rotacaoDireita(no);
    }
    
    // Caso Direita-Direita
    if (balance < -1 && fatorBalanceamento(no->direita) <= 0) {
        return rotacaoEsquerda(no);
    }
    
    // Caso Direita-Esquerda
    if (balance < -1 && fatorBalanceamento(no->direita) > 0) {
        no->direita = rotacaoDireita(no->direita);
        return rotacaoEsquerda(no);
    }
    
    return no;
}

void Arvore_aluno::remover(int id) {
    raiz = remover(raiz, id);
}

// ============================================
// Busca
// ============================================

NoAVL* Arvore_aluno::buscarNo(NoAVL* no, int id) {
    if (no == nullptr || no->aluno->getId() == id) {
        return no;
    }
    
    if (id < no->aluno->getId()) {
        return buscarNo(no->esquerda, id);
    }
    return buscarNo(no->direita, id);
}

Aluno* Arvore_aluno::buscar(int id) {
    NoAVL* no = buscarNo(raiz, id);
    if (no != nullptr) {
        return no->aluno;
    }
    return nullptr;
}

// ============================================
// Listagem
// ============================================

void Arvore_aluno::listarEmOrdem(NoAVL* no) const {
    if (no != nullptr) {
        listarEmOrdem(no->esquerda);
        
        std::cout << "| " << std::setw(4) << no->aluno->getId() 
                  << " | " << std::setw(25) << std::left << no->aluno->getNome() << std::right
                  << " | " << std::setw(8) << no->aluno->getQuantidadeFichas()
                  << " |" << std::endl;
        
        listarEmOrdem(no->direita);
    }
}

void Arvore_aluno::listarAlunos() const {
    if (raiz == nullptr) {
        std::cout << "\n*** Nenhum aluno cadastrado ***\n" << std::endl;
        return;
    }
    
    std::cout << "\n============= LISTA DE ALUNOS =============" << std::endl;
    std::cout << "+------+---------------------------+----------+" << std::endl;
    std::cout << "|  ID  |           Nome            |  Fichas  |" << std::endl;
    std::cout << "+------+---------------------------+----------+" << std::endl;
    
    listarEmOrdem(raiz);
    
    std::cout << "+------+---------------------------+----------+" << std::endl;
    std::cout << "=============================================\n" << std::endl;
}

// ============================================
// Utilitários
// ============================================

bool Arvore_aluno::estaVazia() const {
    return raiz == nullptr;
}
