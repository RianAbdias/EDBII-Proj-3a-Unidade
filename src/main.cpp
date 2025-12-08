#include <iostream>
#include "Aluno.h"
#include "Arvore.h"

int main() {
    Arvore<Aluno> arvoreAlunos;
    
    // Cria alguns alunos
    Aluno* aluno1 = new Aluno("João Silva");
    Aluno* aluno2 = new Aluno("Maria Santos");
    Aluno* aluno3 = new Aluno("Pedro Oliveira");
    
    // Insere na árvore
    arvoreAlunos.inserir(aluno1);
    arvoreAlunos.inserir(aluno2);
    arvoreAlunos.inserir(aluno3);
    
    // Lista todos
    std::cout << "=== Lista de Alunos ===" << std::endl;
    arvoreAlunos.listarEmOrdem([](const Aluno* a) {
        a->exibirDados();
    });
    
    // Busca
    Aluno* encontrado = arvoreAlunos.buscar(2, [](const Aluno* a) {
        return a->getId();
    });
    
    if (encontrado) {
        std::cout << "\nEncontrado: ";
        encontrado->exibirDados();
    }
    
    // Limpa memória (importante!)
    delete aluno1;
    delete aluno2;
    delete aluno3;
    
    return 0;
}