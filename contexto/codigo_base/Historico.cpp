#include "Historico.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Adicionar registro ao histórico
void Historico::adicionarRegistro(const RegistroTreino& registro) {
    registros.push_back(registro);
}

// Exibir histórico completo
void Historico::exibirHistorico() const {
    std::cout << "=============== histórico de treinos ============== " << std::endl;
    for (const auto& registro : registros){
        std::cout << registro.dataHora << " - " << registro.nomeFicha << "\nCalorias Gastas: " << registro.caloriasTotal << "KCal; Tempo: " << registro.tempoTotal << " minutos" << std::endl << std::endl; 
    }
    std::cout << "=================================================== " << std::endl;
}

// Getter de registros
const std::vector<RegistroTreino>& Historico::getRegistros() const {
    static std::vector<RegistroTreino> vazio; // Placeholder para compilar

    for(const auto& registro : registros){
        vazio.push_back(registro);
    }

    return vazio;
}

// Carregar histórico do arquivo
void Historico::carregarDeArquivo() {
    std::ifstream arquivo("historico.txt");
    if (!arquivo.is_open()){
        std::cout << "erro ao tentar ler arquivo!" << std::endl;
        return;
    }

    std::string linha;

    while(getline(arquivo, linha)){
        std::stringstream ss(linha);
        std::string token;

        RegistroTreino temp;

        getline(ss, temp.dataHora, ';');
        getline(ss, token, ';');
        temp.idFicha = stoi(token);
        getline(ss, temp.nomeFicha, ';');
        getline(ss, token, ';');
        temp.tempoTotal = stod(token);
        getline(ss, token, ';');
        temp.caloriasTotal = stod(token);

        registros.push_back(temp);
    }

    arquivo.close();
}

// Salvar histórico no arquivo
void Historico::salvarEmArquivo() const {
    std::ofstream arquivo("historico.txt");
    if (!arquivo.is_open()){
        std::cout << "erro ao tentar ler arquivo!" << std::endl;
        return;
    }

    for (const RegistroTreino& registro : registros){
        arquivo << registro.dataHora << ";" << registro.idFicha << ";" << registro.nomeFicha << ";" << registro.tempoTotal << ";" << registro.caloriasTotal << std::endl;
    }

    arquivo.close();
    std::cout << "Histórico salvo como sucesso!" << std::endl;
}
