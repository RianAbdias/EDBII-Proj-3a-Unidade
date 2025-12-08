#ifndef ALUNO_H
#define ALUNO_H

#include <string>
#include <vector>
#include <iostream>

class Aluno {
private:
    int id;
    std::string nome;
    std::vector<int> idsFichas;  // IDs das fichas de treino do aluno
    
    static int proximoId;

public:
    // Construtores
    Aluno(std::string nome);
    Aluno(int id, std::string nome);  // Para leitura de arquivo

    ~Aluno();

    // Métodos para gerenciar fichas
    void adicionarFicha(int idFicha);
    void removerFicha(int idFicha);
    
    // Exibição
    void exibirDados() const;
    
    // Getters
    int getId() const;
    std::string getNome() const;
    const std::vector<int>& getIdsFichas() const;
    int getQuantidadeFichas() const;
    
    // Atualiza o contador estático se o ID lido for maior
    static void atualizarProximoId(int maiorId);
};

#endif
