#include "Ficha.h"
#include <iostream>
#include <iomanip>

int Ficha::proximoId = 1;

// Construtor para novos cadastros
Ficha::Ficha(std::string nome) : nome(nome) {
    this->id = proximoId++;
}

// Construtor para leitura de arquivo
Ficha::Ficha(int id, std::string nome) : nome(nome){
    this->id = id;

    if (id >= proximoId) {
        proximoId = id + 1;
    }
}

// Destrutor (não deletar exercícios, apenas limpar vector)
Ficha::~Ficha() {
    exercicios.clear();
}

// Adicionar exercício à ficha
void Ficha::adicionarExercicio(Exercicio* exercicio) {
    exercicios.push_back(exercicio);
}

// Exibir ficha completa com exercícios e totais
void Ficha::exibirFicha() const {

    std::cout <<"Ficha: " << nome << "\nID: " << id << "\n\n";

    for (const auto& exercicio : exercicios){
        std::cout << exercicio->getNome() << std::endl;
    }

    std::cout << "\nTempo estimado de execução do treino: " << calcularTempoTotal() << " minutos\nEstimativa de calorias totais gastas no treino: " << calcularCaloriasTotais() << "Kcal" << std::endl << std::endl;
}

// Calcular tempo total da ficha
double Ficha::calcularTempoTotal() const {

    double total = 0.0;

    for (const auto& exercicio : exercicios){
        total += exercicio->calcularTempoEstimado();
    }

    return total;
}

// Calcular calorias totais da ficha
double Ficha::calcularCaloriasTotais() const {

    double total = 0.0;

    for (const auto& exercicio : exercicios){
        total += exercicio->calcularCaloriasGastas();
    }

    return total;
}

// Getters
int Ficha::getId() const { 
    return id;
}

std::string Ficha::getNome() const { 
    return nome;
}

const std::vector<Exercicio*>& Ficha::getExercicios() const {
    return exercicios;
}

// Atualizar próximo ID
void Ficha::atualizarProximoId(int maiorId) {
    // Já implementado no contrutor
}
