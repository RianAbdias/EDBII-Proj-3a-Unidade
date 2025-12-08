#include "Sistema.h"
#include "Cardio.h"
#include "Forca.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>

Sistema::Sistema() {
    carregarDados();
}

Sistema::~Sistema() {
    salvarDados();
    // Deletar ponteiros de exercicios e fichas
    for (auto p : exercicios){
        delete p;
    }
    for (auto f : fichas){
        delete f;
    }
}

// Carregar dados dos arquivos
void Sistema::carregarDados() {

    // Carregar exercicios.txt

    std::ifstream arquivo_exercicios("exercicios.txt");
    if (!arquivo_exercicios.is_open()){
        std::cout << "Erro ao abrir arquivo exercicios.txt!" << std::endl;
        return;
    }

    std::string linha;

    while (getline(arquivo_exercicios, linha)){ 
        std::stringstream ss(linha);
        std::string token;

        getline(ss, token, ';');
        int tipo = stoi(token);

        if(tipo == 1){

            int id, duracao;
            std::string nome;
            bool ativo;
            double calorias;

            getline(ss, token, ';');
            id = stoi(token);

            getline(ss, nome, ';');

            getline(ss, token, ';');
            duracao = stoi(token);

            getline(ss, token, ';');
            calorias = stod(token);

            getline(ss, token);
            ativo = (stoi(token) == 1) ? true : false;
            
            Cardio* cardio = new Cardio(id, nome, ativo, duracao, calorias);

            exercicios.push_back(cardio);

        }else if(tipo == 2){

            int id, series, reps, descanso;
            std::string nome;
            double carga;
            bool ativo;

            getline(ss, token, ';');
            id = stoi(token);

            getline(ss, nome, ';');

            getline(ss, token, ';');
            carga = stod(token);

            getline(ss, token, ';');
            series = stoi(token);

            getline(ss, token, ';');
            reps = stoi(token);

            getline(ss, token, ';');
            descanso = stoi(token);

            getline(ss, token);
            ativo = (stoi(token) == 1) ? true : false;

            Forca* forca = new Forca(id, nome, ativo, carga, series, reps, descanso);
            exercicios.push_back(forca);
        }else{
            std::cout << "Erro ao carregar arquivos!" << std::endl;
        }
    }
    arquivo_exercicios.close();
    
    // Carregar fichas.txt

    std::ifstream arquivo_fichas("fichas.txt");
    if (!arquivo_fichas.is_open()){
        std::cout << "Erro ao abrir arquivo fichas.txt!" << std::endl;
        return;
    }

    while (getline(arquivo_fichas,linha)){
        
        std::stringstream ss(linha);
        std::string token;

        int id, qtdExerc, idExerc;
        std::string nome;

        getline(ss, token, ';');
        id = stoi(token);

        getline(ss, nome, ';');

        getline(ss, token, ';');
        qtdExerc = stoi(token);

        Ficha* ficha = new Ficha(id, nome);
        fichas.push_back(ficha);

        for (int i = 0; i<qtdExerc; i++){

            getline(ss, token, ';');
            idExerc = stoi(token);

            for (Exercicio* exercicio : exercicios){
                if (idExerc == exercicio->getId()){
                    ficha->adicionarExercicio(exercicio);
                    break;
                }
            }
        }
    }
    arquivo_fichas.close();

    historico.carregarDeArquivo();
}

// Salvar dados nos arquivos
void Sistema::salvarDados() {
    // Salvar exercicios.txt
    std::ofstream arquivo_exercicios("exercicios.txt");
    if (!arquivo_exercicios.is_open()){
        std::cout << "Erro ao abrir arquivo exercicios.txt!" << std::endl;
        return;
    }

    for (const Exercicio* exercicio : exercicios){

        if(exercicio->getTipo() == 1){
            Cardio* c = (Cardio*) exercicio;

            arquivo_exercicios << c->getTipo() << ";" << c->getId() << ";" << c->getNome() << ";" << c->getDuracao() << ";" << c->getCaloriasPorMinuto() << ";" << (c->isAtivo() ? 1 : 0) << "\n";

        }else{

            Forca* f = (Forca*) exercicio;

            arquivo_exercicios << f->getTipo() << ";" << f->getId() << ";" << f->getNome() << ";" << f->getCarga() << ";" << f->getSeries() << ";" << f->getRepeticoes() << ";" << f->getTempoDescanso() << ";" << (f->isAtivo() ? 1 : 0) << "\n";
        }
    }

    std::cout<< "\nExercícios salvos com sucesso!" << std::endl;

    arquivo_exercicios.close();

    // Salvar fichas.txt
    std::ofstream arquivo_fichas("fichas.txt");
    if (!arquivo_fichas.is_open()){
        std::cout << "Erro ao abrir arquivo fichas.txt!" << std::endl;
        return;
    }

    for (const Ficha* ficha : fichas){

        arquivo_fichas << ficha->getId() << ";" << ficha->getNome() << ";" << ficha->getExercicios().size();

        for(const Exercicio* exercicio : ficha->getExercicios()){
            arquivo_fichas << ";" << exercicio->getId();
        }

        arquivo_fichas << "\n";
    }
    std::cout<< "\nFichas salvas com sucesso!" << std::endl << std::endl;
    arquivo_fichas.close();

    historico.salvarEmArquivo();
}

// Buscar exercício por ID
Exercicio* Sistema::buscarExercicioPorId(int id) {
    for (Exercicio* exercicio : exercicios){

        if (exercicio->getId() == id){
            return exercicio;
        }
    }

    std::cout << "Exercício não encontrado ou inexistente!" << std::endl;
    return nullptr;
}

// Buscar ficha por ID
Ficha* Sistema::buscarFichaPorId(int id) {

    for (Ficha* ficha : fichas){

        if (ficha->getId() == id){
            return ficha;
        }
    }

    std::cout << "Ficha não encontrada ou inexistente!" << std::endl;
    return nullptr;
}

// Cadastrar novo exercício
void Sistema::cadastrarExercicio() {
    int tipo;

    std::cout << "Tipo (1 - Cardio;  2 - Força): ";
    std::cin >> tipo;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (tipo == 1){
        std::string nome;
        double duracao;
        double calorias;

        std::cout << "Nome do exercicio: ";
        getline(std::cin, nome);

        std::cout << "Duração do exercício: ";
        std::cin >> duracao;

        std::cout << "Calorias por minuto: ";
        std::cin >> calorias;

        exercicios.push_back(new Cardio(nome, duracao, calorias));

    }else if (tipo == 2){
        std::string nome;
        double carga;
        int series;
        int repeticoes;
        int tempoDescanso;

        std::cout << "Nome do exercicio: ";
        getline(std::cin, nome);

        std::cout << "Carga do exercício: ";
        std::cin >> carga;

        std::cout << "Quantidade de séries: ";
        std::cin >> series;

        std::cout << "Quantidade de repetições: ";
        std::cin >> repeticoes;

        std::cout << "Tempo de descanso entre séries (em segundos): ";
        std::cin >> tempoDescanso;

        exercicios.push_back(new Forca(nome, carga, series, repeticoes, tempoDescanso));
    }else{
        std::cout << "Valor informado não coresponde a um tipo de exercício!" << std::endl;
    }
    pausar();

}

// Listar exercícios ativos
void Sistema::listarExercicios() {

    std::cout << "================ Lista de Exercícios Disponíveis =================" << std::endl;
    for (const auto e : exercicios){

        if(e->isAtivo()){
            e->exibirDetalhes();
        }
        std::cout << "-----------------------" << std::endl;
    }
    std::cout << "==================================================================" << std::endl;
    pausar();
}

// Desativar exercício
void Sistema::excluirExercicio() {
    
    int id;
    std::cout << "Informe o ID do exercício que deseja desatvar: ";
    std::cin >> id;

    for (Exercicio* e : exercicios){

        if(e->getId() == id ){
            e->desativar();
            std::cout << "Exercicio desativado." << std::endl;
        }
    }
    pausar();
}

// Criar nova ficha
void Sistema::criarFicha() {

    std::string nome;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Informe o nome da ficha: ";
    getline(std::cin, nome);

    fichas.push_back(new Ficha(nome));
    std::cout << "\nFicha " << nome << " criada com sucesso!" << std::endl;
    pausar();

}

// Adicionar exercício à ficha
void Sistema::adicionarExercicioFicha() {

    int idFicha, idExer;
    std::cout << "Informe os ID's da ficha e do exercício respectivamente: ";
    std::cin >> idFicha;
    std::cin >> idExer;

    for(Ficha* ficha : fichas){

        if(ficha->getId() == idFicha){

            for(Exercicio* exercicio : exercicios){

                if(exercicio->getId() == idExer){

                    ficha->adicionarExercicio(exercicio);
                    std::cout << "\nExercício " << exercicio->getNome() << " adicionado à ficha " << ficha->getNome() << " com sucesso!" << std::endl;
                    break;
                }
            }
            break;
        }
    }
    pausar();
}

// Listar todas as fichas
void Sistema::listarFichas() {
    // Implementar
    std::cout << "======== Lista de Fichas ========" << std::endl;

    for (Ficha* ficha : fichas){
        ficha->exibirFicha();
        std::cout << "-----------------------" << std::endl;
    }

    std::cout << "=================================\n" << std::endl;
    pausar();
}

// Registrar treino realizado
void Sistema::registrarTreino() {
    // Implementar
    int idFicha;
    std::cout << "Informe o id da ficha: ";
    std::cin >> idFicha;

    Ficha* ficha = buscarFichaPorId(idFicha);
    
    RegistroTreino registro{
        getDataHoraAtual(),
        ficha->getId(), 
        ficha->getNome(), 
        ficha->calcularTempoTotal(), 
        ficha->calcularCaloriasTotais()
    };

    historico.adicionarRegistro(registro);

    std::cout << "Treino registrado no histórico!" << std::endl;
    pausar();
}

// Exibir histórico de treinos
void Sistema::exibirHistorico() {

    historico.exibirHistorico();
    pausar();
}
