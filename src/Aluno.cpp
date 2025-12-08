#include "Aluno.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// Inicialização da variável estática
int Aluno::proximoId = 1;

// Construtor para novos cadastros
Aluno::Aluno(std::string nome) : nome(nome) {
    this->id = proximoId++;
}

// Construtor para leitura de arquivo
Aluno::Aluno(int id, std::string nome) : nome(nome) {
    this->id = id;

    if (id >= proximoId) {
        proximoId = id + 1;
    }
}

// Destrutor
Aluno::~Aluno() {
    idsFichas.clear();
}

// Adicionar ficha ao aluno
void Aluno::adicionarFicha(int idFicha) {
    // Verifica se a ficha já não está na lista
    for (int id : idsFichas) {
        if (id == idFicha) {
            return;  // Ficha já existe, não adiciona duplicada
        }
    }
    idsFichas.push_back(idFicha);
}

// Remover ficha do aluno
void Aluno::removerFicha(int idFicha) {
    auto it = std::find(idsFichas.begin(), idsFichas.end(), idFicha);
    if (it != idsFichas.end()) {
        idsFichas.erase(it);
    }
}

// Exibir dados do aluno
void Aluno::exibirDados() const {
    std::cout << "\n--- Dados do Aluno ---" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Nome: " << nome << std::endl;
    std::cout << "Quantidade de Fichas: " << idsFichas.size() << std::endl;
    
    if (!idsFichas.empty()) {
        std::cout << "IDs das Fichas: ";
        for (size_t i = 0; i < idsFichas.size(); i++) {
            std::cout << idsFichas[i];
            if (i < idsFichas.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------\n" << std::endl;
}

// Getters
int Aluno::getId() const {
    return id;
}

std::string Aluno::getNome() const {
    return nome;
}

const std::vector<int>& Aluno::getIdsFichas() const {
    return idsFichas;
}

int Aluno::getQuantidadeFichas() const {
    return idsFichas.size();
}

// Atualizar próximo ID
void Aluno::atualizarProximoId(int maiorId) {
    if (maiorId >= proximoId) {
        proximoId = maiorId + 1;
    }
}
