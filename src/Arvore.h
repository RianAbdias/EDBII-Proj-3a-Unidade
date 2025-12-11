#ifndef ARVORE_H
#define ARVORE_H

#include <iostream>
#include <functional>
#include <algorithm>

template <typename T>
struct NoAVL {
    T* objeto;
    NoAVL* esquerda;
    NoAVL* direita;
    int altura;

    NoAVL(T* obj) : objeto(obj), esquerda(nullptr), direita(nullptr), altura(1) {}
};

template <typename T>
class Arvore {
private:

void imprimirRec(NoAVL<T>* no, int nivel) const {
    if (!no) return;

    for (int i = 0; i < nivel; i++)
        std::cout << "   ";

    std::cout << "- " << no->objeto->getId()
              << " (h=" << no->altura << ")" << std::endl;

    imprimirRec(no->esquerda, nivel + 1);
    imprimirRec(no->direita, nivel + 1);
}

void imprimirBonitaRec(NoAVL<T>* no, int espaco) const {
    if (!no) return;

    const int incremento = 6;
    espaco += incremento;

    imprimirBonitaRec(no->direita, espaco);

    std::cout << std::endl;
    for (int i = incremento; i < espaco; i++)
        std::cout << " ";
    std::cout << no->objeto->getId() << "\n";

    imprimirBonitaRec(no->esquerda, espaco);
}

    NoAVL<T>* raiz;
    
    // Métodos internos
    int altura(NoAVL<T>* no) {
        return no ? no->altura : 0;
    }
    
    int fatorBalanceamento(NoAVL<T>* no) {
        return no ? altura(no->esquerda) - altura(no->direita) : 0;
    }
    
    NoAVL<T>* rotacaoDireita(NoAVL<T>* y) {
        if (!y || !y->esquerda) return y;
        
        NoAVL<T>* x = y->esquerda;
        NoAVL<T>* T2 = x->direita;
        
        x->direita = y;
        y->esquerda = T2;
        
        y->altura = std::max(altura(y->esquerda), altura(y->direita)) + 1;
        x->altura = std::max(altura(x->esquerda), altura(x->direita)) + 1;
        
        return x;
    }
    
    NoAVL<T>* rotacaoEsquerda(NoAVL<T>* x) {
        if (!x || !x->direita) return x;
        
        NoAVL<T>* y = x->direita;
        NoAVL<T>* T2 = y->esquerda;
        
        y->esquerda = x;
        x->direita = T2;
        
        x->altura = std::max(altura(x->esquerda), altura(x->direita)) + 1;
        y->altura = std::max(altura(y->esquerda), altura(y->direita)) + 1;
        
        return y;
    }
    
    NoAVL<T>* encontrarMinimo(NoAVL<T>* no) {
        if (!no) return nullptr;
        while (no->esquerda) no = no->esquerda;
        return no;
    }
    
    NoAVL<T>* inserir(NoAVL<T>* no, T* objeto) {
        if (!no) return new NoAVL<T>(objeto);
        
        int id = objeto->getId();
        int idNo = no->objeto->getId();
        
        if (id < idNo) {
            no->esquerda = inserir(no->esquerda, objeto);
        } else if (id > idNo) {
            no->direita = inserir(no->direita, objeto);
        } else {
            return no; // ID duplicado
        }
        
        no->altura = 1 + std::max(altura(no->esquerda), altura(no->direita));
        int balance = fatorBalanceamento(no);
        
        if (balance > 1 && id < no->esquerda->objeto->getId())
            return rotacaoDireita(no);
        if (balance < -1 && id > no->direita->objeto->getId())
            return rotacaoEsquerda(no);
        if (balance > 1 && id > no->esquerda->objeto->getId()) {
            no->esquerda = rotacaoEsquerda(no->esquerda);
            return rotacaoDireita(no);
        }
        if (balance < -1 && id < no->direita->objeto->getId()) {
            no->direita = rotacaoDireita(no->direita);
            return rotacaoEsquerda(no);
        }
        
        return no;
    }
    
    NoAVL<T>* remover(NoAVL<T>* no, int id, std::function<int(const T*)> getId) {
        if (!no) return no;
        
        int idNo = getId(no->objeto);
        
        if (id < idNo) {
            no->esquerda = remover(no->esquerda, id, getId);
        } else if (id > idNo) {
            no->direita = remover(no->direita, id, getId);
        } else {
            if (!no->esquerda || !no->direita) {
                NoAVL<T>* temp = no->esquerda ? no->esquerda : no->direita;
                
                if (!temp) {
                    temp = no;
                    no = nullptr;
                } else {
                    *no = *temp;
                }
                
                delete temp;
            } else {
                NoAVL<T>* temp = encontrarMinimo(no->direita);
                no->objeto = temp->objeto;
                no->direita = remover(no->direita, getId(temp->objeto), getId);
            }
        }
        
        if (!no) return no;
        
        no->altura = 1 + std::max(altura(no->esquerda), altura(no->direita));
        int balance = fatorBalanceamento(no);
        
        if (balance > 1 && fatorBalanceamento(no->esquerda) >= 0)
            return rotacaoDireita(no);
        if (balance > 1 && fatorBalanceamento(no->esquerda) < 0) {
            no->esquerda = rotacaoEsquerda(no->esquerda);
            return rotacaoDireita(no);
        }
        if (balance < -1 && fatorBalanceamento(no->direita) <= 0)
            return rotacaoEsquerda(no);
        if (balance < -1 && fatorBalanceamento(no->direita) > 0) {
            no->direita = rotacaoDireita(no->direita);
            return rotacaoEsquerda(no);
        }
        
        return no;
    }
    
    NoAVL<T>* buscarNo(NoAVL<T>* no, int id, std::function<int(const T*)> getId) {
        if (!no) return nullptr;
        
        int idNo = getId(no->objeto);
        
        if (id == idNo) return no;
        if (id < idNo) return buscarNo(no->esquerda, id, getId);
        return buscarNo(no->direita, id, getId);
    }
    
    void destruir(NoAVL<T>* no) {
        if (no) {
            destruir(no->esquerda);
            destruir(no->direita);
            delete no;
        }
    }
    
    void listarEmOrdemRecursivo(NoAVL<T>* no, std::function<void(const T*)> imprimir) const {
        if (!no) return;
        listarEmOrdemRecursivo(no->esquerda, imprimir);
        imprimir(no->objeto);
        listarEmOrdemRecursivo(no->direita, imprimir);
    }

public:
    Arvore() : raiz(nullptr) {}
    
    ~Arvore() {
        destruir(raiz);
    }

    void exibirEstrutura() const {
    if (!raiz) {
        std::cout << "[Árvore vazia]\n";
        return;
    }
    imprimirRec(raiz, 0);
}

void exibirBonita() const {
    if (!raiz) {
        std::cout << "[Árvore vazia]\n";
        return;
    }
    imprimirBonitaRec(raiz, 0);
}

    
    void inserir(T* objeto) {
        raiz = inserir(raiz, objeto);
    }
    
    void remover(int id, std::function<int(const T*)> getId) {
        raiz = remover(raiz, id, getId);
    }
    
    T* buscar(int id, std::function<int(const T*)> getId) {
        NoAVL<T>* no = buscarNo(raiz, id, getId);
        return no ? no->objeto : nullptr;
    }
    
    void listarEmOrdem(std::function<void(const T*)> imprimir) const {
        listarEmOrdemRecursivo(raiz, imprimir);
    }
    
    bool estaVazia() const {
        return raiz == nullptr;
    }
    
    int getAltura() const {
        return altura(raiz);
    }
    
    // Proibir cópia
    Arvore(const Arvore&) = delete;
    Arvore& operator=(const Arvore&) = delete;
};

#endif