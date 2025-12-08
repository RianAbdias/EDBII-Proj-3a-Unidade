#include "Forca.h"
#include <iostream>

// Construtor para novos cadastros
Forca::Forca(std::string nome, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(nome), carga(carga), series(series), repeticoes(repeticoes), tempoDescanso(tempoDescanso) {
}

// Construtor para leitura de arquivo
Forca::Forca(int id, std::string nome, bool ativo, double carga, int series, int repeticoes, int tempoDescanso)
    : Exercicio(id, nome, ativo), carga(carga), series(series), repeticoes(repeticoes), tempoDescanso(tempoDescanso){
}

// Exibir detalhes do exercício
void Forca::exibirDetalhes() const {
    std::cout << "Tipo: " << getTipo() << "\nNome: " << getNome() << "\nID do exercício: " << getId() << "\nStatus: " << (isAtivo() ? "Ativo" : "Não ativo") << "\nCarga do exercício: " << getCarga() << "\nQuantidade de séries: " << getSeries() << "\nQuantidade de repetições por série: " << getRepeticoes() << "\nTempo de descanso entre séries: " << getTempoDescanso() << " segundos" << std::endl;
}

// Calcular tempo estimado (em minutos)
double Forca::calcularTempoEstimado() const {
    return ((series*repeticoes*3)+(series*tempoDescanso))/60;
}

// Calcular calorias gastas
double Forca::calcularCaloriasGastas() const {
    return series*repeticoes*carga*0.15;
}

// Retornar tipo do exercício (2 = Força)
int Forca::getTipo() const {
    return 2;
}

// Getters
double Forca::getCarga() const { 
    return carga;
}

int Forca::getSeries() const { 
    return series;
}

int Forca::getRepeticoes() const { 
    return repeticoes;
}

int Forca::getTempoDescanso() const { 
    return tempoDescanso;
}

