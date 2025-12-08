// main.cpp - Arquivo de teste para Aluno e Arvore_aluno
// Compile com: g++ -o main.exe main.cpp Aluno.cpp Arvore_aluno.cpp -std=c++11

#include <iostream>
#include "Aluno.h"
#include "Arvore_aluno.h"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   TESTE - ALUNO E ARVORE AVL" << std::endl;
    std::cout << "========================================\n" << std::endl;

    // Cria a árvore AVL para gerenciar os alunos
    Arvore_aluno arvore;

    // ========================================
    // TESTE 1: Inserção de Alunos
    // ========================================
    std::cout << ">>> TESTE 1: Inserindo alunos na arvore AVL..." << std::endl;
    
    Aluno* aluno1 = new Aluno("Joao Silva");
    Aluno* aluno2 = new Aluno("Maria Santos");
    Aluno* aluno3 = new Aluno("Pedro Oliveira");
    Aluno* aluno4 = new Aluno("Ana Costa");
    Aluno* aluno5 = new Aluno("Carlos Souza");

    // Adicionando fichas aos alunos
    aluno1->adicionarFicha(1);
    aluno1->adicionarFicha(2);
    
    aluno2->adicionarFicha(1);
    
    aluno3->adicionarFicha(3);
    aluno3->adicionarFicha(4);
    aluno3->adicionarFicha(5);
    
    // aluno4 sem fichas
    
    aluno5->adicionarFicha(2);

    // Inserindo na árvore
    arvore.inserir(aluno1);
    arvore.inserir(aluno2);
    arvore.inserir(aluno3);
    arvore.inserir(aluno4);
    arvore.inserir(aluno5);

    std::cout << "5 alunos inseridos com sucesso!\n" << std::endl;

    // ========================================
    // TESTE 2: Listar Alunos
    // ========================================
    std::cout << ">>> TESTE 2: Listando todos os alunos (ordenados por ID)..." << std::endl;
    arvore.listarAlunos();

    // ========================================
    // TESTE 3: Buscar Aluno
    // ========================================
    std::cout << ">>> TESTE 3: Buscando aluno com ID 3..." << std::endl;
    Aluno* encontrado = arvore.buscar(3);
    if (encontrado != nullptr) {
        std::cout << "Aluno encontrado!" << std::endl;
        encontrado->exibirDados();
    } else {
        std::cout << "Aluno nao encontrado.\n" << std::endl;
    }

    std::cout << ">>> Buscando aluno com ID 99 (inexistente)..." << std::endl;
    Aluno* naoEncontrado = arvore.buscar(99);
    if (naoEncontrado != nullptr) {
        naoEncontrado->exibirDados();
    } else {
        std::cout << "Aluno com ID 99 nao encontrado.\n" << std::endl;
    }

    // ========================================
    // TESTE 4: Exibir Dados Detalhados
    // ========================================
    std::cout << ">>> TESTE 4: Exibindo dados detalhados do aluno 1..." << std::endl;
    aluno1->exibirDados();

    // ========================================
    // TESTE 5: Remover Aluno
    // ========================================
    std::cout << ">>> TESTE 5: Removendo aluno com ID 2..." << std::endl;
    arvore.remover(2);
    std::cout << "Aluno removido!\n" << std::endl;

    std::cout << ">>> Lista apos remocao:" << std::endl;
    arvore.listarAlunos();

    // ========================================
    // TESTE 6: Mais Inserções (Testar Balanceamento)
    // ========================================
    std::cout << ">>> TESTE 6: Inserindo mais alunos para testar balanceamento..." << std::endl;
    
    Aluno* aluno6 = new Aluno("Fernanda Lima");
    Aluno* aluno7 = new Aluno("Roberto Dias");
    Aluno* aluno8 = new Aluno("Julia Mendes");
    
    aluno6->adicionarFicha(1);
    aluno7->adicionarFicha(2);
    aluno7->adicionarFicha(3);
    
    arvore.inserir(aluno6);
    arvore.inserir(aluno7);
    arvore.inserir(aluno8);

    std::cout << "3 alunos adicionados!\n" << std::endl;
    arvore.listarAlunos();

    // ========================================
    // TESTE 7: Verificar se Árvore está Vazia
    // ========================================
    std::cout << ">>> TESTE 7: Verificando se arvore esta vazia..." << std::endl;
    if (arvore.estaVazia()) {
        std::cout << "Arvore esta vazia." << std::endl;
    } else {
        std::cout << "Arvore NAO esta vazia.\n" << std::endl;
    }

    // ========================================
    // TESTE 8: Remover Ficha de um Aluno
    // ========================================
    std::cout << ">>> TESTE 8: Removendo ficha 1 do aluno com ID 1..." << std::endl;
    Aluno* alunoModificar = arvore.buscar(1);
    if (alunoModificar != nullptr) {
        std::cout << "Antes da remocao:" << std::endl;
        alunoModificar->exibirDados();
        
        alunoModificar->removerFicha(1);
        
        std::cout << "Depois da remocao da ficha 1:" << std::endl;
        alunoModificar->exibirDados();
    }

    std::cout << "========================================" << std::endl;
    std::cout << "   TESTES FINALIZADOS COM SUCESSO!" << std::endl;
    std::cout << "========================================" << std::endl;

    return 0;
}
