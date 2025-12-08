#include <iostream>
#include <memory>
#include <vector>
#include <limits>
#include "Aluno.h"
#include "Arvore.h"
#include "Cardio.h"
#include "Forca.h"
#include "Ficha.h"

using namespace std;

// Árvores globais para armazenamento
Arvore<Aluno> arvoreAlunos;
Arvore<Ficha> arvoreFichas;
Arvore<Exercicio> arvoreExercicios;

// Funções auxiliares
void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pausar() {
    cout << "\nPressione Enter para continuar...";
    limparBuffer();
}

// CRUD ALUNOS

void cadastrarAluno() {
    string nome;
    cout << "\n=== CADASTRAR ALUNO ===\n";
    cout << "Nome do aluno: ";
    getline(cin, nome);
    
    Aluno* aluno = new Aluno(nome);
    arvoreAlunos.inserir(aluno);
    
    cout << "Aluno cadastrado com sucesso! ID: " << aluno->getId() << endl;
}

void listarAlunos() {
    cout << "\n=== LISTA DE ALUNOS ===\n";
    if (arvoreAlunos.estaVazia()) {
        cout << "Nenhum aluno cadastrado.\n";
        return;
    }
    
    arvoreAlunos.listarEmOrdem([](const Aluno* aluno) {
        aluno->exibirDados();
    });
}

void buscarAluno() {
    int id;
    cout << "\n=== BUSCAR ALUNO ===\n";
    cout << "ID do aluno: ";
    cin >> id;
    limparBuffer();
    
    Aluno* aluno = arvoreAlunos.buscar(id, [](const Aluno* a) {
        return a->getId();
    });
    
    if (aluno) {
        aluno->exibirDados();
        
        // Mostrar fichas do aluno
        const vector<int>& idsFichas = aluno->getIdsFichas();
        if (!idsFichas.empty()) {
            cout << "Fichas associadas:\n";
            for (int idFicha : idsFichas) {
                Ficha* ficha = arvoreFichas.buscar(idFicha, [](const Ficha* f) {
                    return f->getId();
                });
                if (ficha) {
                    cout << "  - ID " << ficha->getId() << ": " << ficha->getNome() << endl;
                }
            }
        }
    } else {
        cout << "Aluno não encontrado!\n";
    }
}

void removerAluno() {
    int id;
    cout << "\n=== REMOVER ALUNO ===\n";
    cout << "ID do aluno a remover: ";
    cin >> id;
    limparBuffer();
    
    // Verificar se aluno existe
    Aluno* aluno = arvoreAlunos.buscar(id, [](const Aluno* a) {
        return a->getId();
    });
    
    if (aluno) {
        // Remover associações com fichas
        for (int idFicha : aluno->getIdsFichas()) {
            Ficha* ficha = arvoreFichas.buscar(idFicha, [](const Ficha* f) {
                return f->getId();
            });
            if (ficha) {
                // Poderíamos optar por remover a ficha também
                cout << "Aviso: Aluno tem ficha associada (ID " << idFicha << ")\n";
            }
        }
        
        arvoreAlunos.remover(id, [](const Aluno* a) { return a->getId(); });
        delete aluno;
        cout << "Aluno removido com sucesso!\n";
    } else {
        cout << "Aluno não encontrado!\n";
    }
}

// CRUD EXERCÍCIOS

void cadastrarExercicio() {
    int tipo;
    cout << "\n=== CADASTRAR EXERCÍCIO ===\n";
    cout << "Tipo de exercício:\n";
    cout << "1. Cardio\n";
    cout << "2. Força\n";
    cout << "Escolha: ";
    cin >> tipo;
    limparBuffer();
    
    string nome;
    cout << "Nome do exercício: ";
    getline(cin, nome);
    
    if (tipo == 1) {
        int duracao;
        double caloriasPorMinuto;
        
        cout << "Duração (minutos): ";
        cin >> duracao;
        cout << "Calorias por minuto: ";
        cin >> caloriasPorMinuto;
        limparBuffer();
        
        Cardio* cardio = new Cardio(nome, duracao, caloriasPorMinuto);
        arvoreExercicios.inserir(cardio);
        cout << "Exercício Cardio cadastrado! ID: " << cardio->getId() << endl;
        
    } else if (tipo == 2) {
        double carga;
        int series, repeticoes, tempoDescanso;
        
        cout << "Carga (kg): ";
        cin >> carga;
        cout << "Séries: ";
        cin >> series;
        cout << "Repetições: ";
        cin >> repeticoes;
        cout << "Tempo de descanso (segundos): ";
        cin >> tempoDescanso;
        limparBuffer();
        
        Forca* forca = new Forca(nome, carga, series, repeticoes, tempoDescanso);
        arvoreExercicios.inserir(forca);
        cout << "Exercício Força cadastrado! ID: " << forca->getId() << endl;
    } else {
        cout << "Tipo inválido!\n";
    }
}

void listarExercicios() {
    cout << "\n=== LISTA DE EXERCÍCIOS ===\n";
    if (arvoreExercicios.estaVazia()) {
        cout << "Nenhum exercício cadastrado.\n";
        return;
    }
    
    arvoreExercicios.listarEmOrdem([](const Exercicio* exercicio) {
        cout << "\n---\n";
        exercicio->exibirDetalhes();
        cout << "Tipo: " << (exercicio->getTipo() == 1 ? "Cardio" : "Força") << endl;
        cout << "Tempo estimado: " << exercicio->calcularTempoEstimado() << " min" << endl;
        cout << "Calorias estimadas: " << exercicio->calcularCaloriasGastas() << " kcal" << endl;
    });
}

void buscarExercicio() {
    int id;
    cout << "\n=== BUSCAR EXERCÍCIO ===\n";
    cout << "ID do exercício: ";
    cin >> id;
    limparBuffer();
    
    Exercicio* exercicio = arvoreExercicios.buscar(id, [](const Exercicio* e) {
        return e->getId();
    });
    
    if (exercicio) {
        exercicio->exibirDetalhes();
        cout << "\nInformações adicionais:\n";
        cout << "Tipo: " << (exercicio->getTipo() == 1 ? "Cardio" : "Força") << endl;
        cout << "Tempo estimado: " << exercicio->calcularTempoEstimado() << " min" << endl;
        cout << "Calorias estimadas: " << exercicio->calcularCaloriasGastas() << " kcal" << endl;
    } else {
        cout << "Exercício não encontrado!\n";
    }
}

void removerExercicio() {
    int id;
    cout << "\n=== REMOVER EXERCÍCIO ===\n";
    cout << "ID do exercício a remover: ";
    cin >> id;
    limparBuffer();
    
    Exercicio* exercicio = arvoreExercicios.buscar(id, [](const Exercicio* e) {
        return e->getId();
    });
    
    if (exercicio) {
        arvoreExercicios.remover(id, [](const Exercicio* e) { return e->getId(); });
        delete exercicio;
        cout << "Exercício removido com sucesso!\n";
    } else {
        cout << "Exercício não encontrado!\n";
    }
}

// CRUD FICHAS

void criarFicha() {
    string nome;
    cout << "\n=== CRIAR FICHA ===\n";
    cout << "Nome da ficha: ";
    getline(cin, nome);
    
    Ficha* ficha = new Ficha(nome);
    
    // Adicionar exercícios à ficha
    char continuar;
    do {
        listarExercicios();
        
        if (!arvoreExercicios.estaVazia()) {
            int idExercicio;
            cout << "\nID do exercício para adicionar (0 para parar): ";
            cin >> idExercicio;
            limparBuffer();
            
            if (idExercicio != 0) {
                Exercicio* exercicio = arvoreExercicios.buscar(idExercicio, [](const Exercicio* e) {
                    return e->getId();
                });
                
                if (exercicio) {
                    ficha->adicionarExercicio(exercicio);
                    cout << "Exercício adicionado à ficha!\n";
                } else {
                    cout << "Exercício não encontrado!\n";
                }
            }
        } else {
            cout << "Não há exercícios cadastrados.\n";
            break;
        }
        
        cout << "Adicionar outro exercício? (s/n): ";
        cin >> continuar;
        limparBuffer();
        
    } while (continuar == 's' || continuar == 'S');
    
    arvoreFichas.inserir(ficha);
    cout << "Ficha criada com sucesso! ID: " << ficha->getId() << endl;
}

void listarFichas() {
    cout << "\n=== LISTA DE FICHAS ===\n";
    if (arvoreFichas.estaVazia()) {
        cout << "Nenhuma ficha cadastrada.\n";
        return;
    }
    
    arvoreFichas.listarEmOrdem([](const Ficha* ficha) {
        ficha->exibirFicha();
    });
}

void buscarFicha() {
    int id;
    cout << "\n=== BUSCAR FICHA ===\n";
    cout << "ID da ficha: ";
    cin >> id;
    limparBuffer();
    
    Ficha* ficha = arvoreFichas.buscar(id, [](const Ficha* f) {
        return f->getId();
    });
    
    if (ficha) {
        ficha->exibirFicha();
        
        // Mostrar alunos que usam esta ficha
        cout << "\nAlunos que usam esta ficha:\n";
        bool encontrou = false;
        arvoreAlunos.listarEmOrdem([id, &encontrou](const Aluno* aluno) {
            for (int idFicha : aluno->getIdsFichas()) {
                if (idFicha == id) {
                    cout << "  - " << aluno->getNome() << " (ID: " << aluno->getId() << ")\n";
                    encontrou = true;
                }
            }
        });
        
        if (!encontrou) {
            cout << "  Nenhum aluno associado.\n";
        }
    } else {
        cout << "Ficha não encontrada!\n";
    }
}

void removerFicha() {
    int id;
    cout << "\n=== REMOVER FICHA ===\n";
    cout << "ID da ficha a remover: ";
    cin >> id;
    limparBuffer();
    
    Ficha* ficha = arvoreFichas.buscar(id, [](const Ficha* f) {
        return f->getId();
    });
    
    if (ficha) {
        // Remover associações com alunos
        arvoreAlunos.listarEmOrdem([id](const Aluno* aluno) {
            Aluno* alunoMod = const_cast<Aluno*>(aluno);
            vector<int> ids = aluno->getIdsFichas();
            if (find(ids.begin(), ids.end(), id) != ids.end()) {
                alunoMod->removerFicha(id);
                cout << "Ficha removida do aluno " << aluno->getNome() << endl;
            }
        });
        
        arvoreFichas.remover(id, [](const Ficha* f) { return f->getId(); });
        delete ficha;
        cout << "Ficha removida com sucesso!\n";
    } else {
        cout << "Ficha não encontrada!\n";
    }
}

// ASSOCIAÇÕES

void associarFichaAluno() {
    int idAluno, idFicha;
    cout << "\n=== ASSOCIAR FICHA A ALUNO ===\n";
    
    cout << "ID do aluno: ";
    cin >> idAluno;
    cout << "ID da ficha: ";
    cin >> idFicha;
    limparBuffer();
    
    Aluno* aluno = arvoreAlunos.buscar(idAluno, [](const Aluno* a) {
        return a->getId();
    });
    
    Ficha* ficha = arvoreFichas.buscar(idFicha, [](const Ficha* f) {
        return f->getId();
    });
    
    if (aluno && ficha) {
        aluno->adicionarFicha(idFicha);
        cout << "Ficha associada ao aluno com sucesso!\n";
        cout << "Aluno: " << aluno->getNome() << endl;
        cout << "Ficha: " << ficha->getNome() << endl;
    } else {
        cout << "Aluno ou ficha não encontrados!\n";
    }
}

void removerFichaAluno() {
    int idAluno, idFicha;
    cout << "\n=== REMOVER FICHA DE ALUNO ===\n";
    
    cout << "ID do aluno: ";
    cin >> idAluno;
    cout << "ID da ficha: ";
    cin >> idFicha;
    limparBuffer();
    
    Aluno* aluno = arvoreAlunos.buscar(idAluno, [](const Aluno* a) {
        return a->getId();
    });
    
    if (aluno) {
        aluno->removerFicha(idFicha);
        cout << "Ficha removida do aluno com sucesso!\n";
    } else {
        cout << "Aluno não encontrado!\n";
    }
}

// MENU PRINCIPAL

void mostrarMenuPrincipal() {
    cout << "\n======================================\n";
    cout << "|      SISTEMA DE ACADEMIA - MENU      |\n";
    cout << "|======================================|\n";
    cout << "|  1. Gerenciar Alunos                 |\n";
    cout << "|  2. Gerenciar Exercícios             |\n";
    cout << "|  3. Gerenciar Fichas                 |\n";
    cout << "|  4. Associações (Aluno-Ficha)        |\n";
    cout << "|  0. Sair                             |\n";
    cout << "========================================\n";
    cout << "Escolha uma opção: ";
}

void menuAlunos() {
    int opcao;
    do {
        cout << "\n========================================\n";
        cout << "|           GERENCIAR ALUNOS             |\n";
        cout << "|========================================|\n";
        cout << "|  1. Cadastrar Aluno                    |\n";
        cout << "|  2. Listar Alunos                      |\n";
        cout << "|  3. Buscar Aluno por ID                |\n";
        cout << "|  4. Remover Aluno                      |\n";
        cout << "|  0. Voltar ao Menu Principal           |\n";
        cout << "==========================================\n";
        cout << "Escolha: ";
        cin >> opcao;
        limparBuffer();
        
        switch (opcao) {
            case 1: cadastrarAluno(); break;
            case 2: listarAlunos(); break;
            case 3: buscarAluno(); break;
            case 4: removerAluno(); break;
            case 0: cout << "Voltando...\n"; break;
            default: cout << "Opção inválida!\n";
        }
        if (opcao != 0) pausar();
    } while (opcao != 0);
}

void menuExercicios() {
    int opcao;
    do {
        cout << "\n========================================\n";
        cout << "|          GERENCIAR EXERCÍCIOS          |\n";
        cout << "|========================================|\n";
        cout << "|  1. Cadastrar Exercício                |\n";
        cout << "|  2. Listar Exercícios                  |\n";
        cout << "|  3. Buscar Exercício por ID            |\n";
        cout << "|  4. Remover Exercício                  |\n";
        cout << "|  0. Voltar ao Menu Principal           |\n";
        cout << "==========================================\n";
        cout << "Escolha: ";
        cin >> opcao;
        limparBuffer();
        
        switch (opcao) {
            case 1: cadastrarExercicio(); break;
            case 2: listarExercicios(); break;
            case 3: buscarExercicio(); break;
            case 4: removerExercicio(); break;
            case 0: cout << "Voltando...\n"; break;
            default: cout << "Opção inválida!\n";
        }
        if (opcao != 0) pausar();
    } while (opcao != 0);
}

void menuFichas() {
    int opcao;
    do {
        cout << "\n========================================\n";
        cout << "|            GERENCIAR FICHAS            |\n";
        cout << "|========================================|\n";
        cout << "|  1. Criar Ficha                        |\n";
        cout << "|  2. Listar Fichas                      |\n";
        cout << "|  3. Buscar Ficha por ID                |\n";
        cout << "|  4. Remover Ficha                      |\n";
        cout << "|  0. Voltar ao Menu Principal           |\n";
        cout << "==========================================\n";
        cout << "Escolha: ";
        cin >> opcao;
        limparBuffer();
        
        switch (opcao) {
            case 1: criarFicha(); break;
            case 2: listarFichas(); break;
            case 3: buscarFicha(); break;
            case 4: removerFicha(); break;
            case 0: cout << "Voltando...\n"; break;
            default: cout << "Opção inválida!\n";
        }
        if (opcao != 0) pausar();
    } while (opcao != 0);
}

void menuAssociacoes() {
    int opcao;
    do {
        cout << "\n========================================\n";
        cout << "|          ASSOCIAÇÕES                   |\n";
        cout << "|========================================|\n";
        cout << "|  1. Associar Ficha a Aluno             |\n";
        cout << "|  2. Remover Ficha de Aluno             |\n";
        cout << "|  0. Voltar ao Menu Principal           |\n";
        cout << "==========================================\n";
        cout << "Escolha: ";
        cin >> opcao;
        limparBuffer();
        
        switch (opcao) {
            case 1: associarFichaAluno(); break;
            case 2: removerFichaAluno(); break;
            case 0: cout << "Voltando...\n"; break;
            default: cout << "Opção inválida!\n";
        }
        if (opcao != 0) pausar();
    } while (opcao != 0);
}

void menuRelatorios() {
    int opcao;
    do {
        cout << "\n========================================\n";
        cout << "|               RELATÓRIOS               |\n";
        cout << "|========================================|\n";
        cout << "|  1. Relatório Completo                 |\n";
        cout << "|  2. Estatísticas                       |\n";
        cout << "|  0. Voltar ao Menu Principal           |\n";
        cout << "==========================================\n";
        cout << "Escolha: ";
        cin >> opcao;
        limparBuffer();
        
        switch (opcao) {
            case 1: {
                cout << "\n=== RELATÓRIO COMPLETO ===\n";
                
                cout << "\n--- ALUNOS ---\n";
                listarAlunos();
                
                cout << "\n--- EXERCÍCIOS ---\n";
                listarExercicios();
                
                cout << "\n--- FICHAS ---\n";
                listarFichas();
                break;
            }
            case 2: {
                cout << "\n=== ESTATÍSTICAS ===\n";
                
                int totalAlunos = 0;
                int totalExercicios = 0;
                int totalFichas = 0;
                
                // Contar alunos
                arvoreAlunos.listarEmOrdem([&totalAlunos](const Aluno* a) {
                    totalAlunos++;
                });
                
                // Contar exercícios
                arvoreExercicios.listarEmOrdem([&totalExercicios](const Exercicio* e) {
                    totalExercicios++;
                });
                
                // Contar fichas
                arvoreFichas.listarEmOrdem([&totalFichas](const Ficha* f) {
                    totalFichas++;
                });
                
                cout << "Total de Alunos: " << totalAlunos << endl;
                cout << "Total de Exercícios: " << totalExercicios << endl;
                cout << "Total de Fichas: " << totalFichas << endl;
                
                if (totalAlunos > 0) {
                    int fichasPorAluno = 0;
                    arvoreAlunos.listarEmOrdem([&fichasPorAluno](const Aluno* a) {
                        fichasPorAluno += a->getQuantidadeFichas();
                    });
                    cout << "Média de fichas por aluno: " 
                         << (float)fichasPorAluno / totalAlunos << endl;
                }
                break;
            }
            case 0: cout << "Voltando...\n"; break;
            default: cout << "Opção inválida!\n";
        }
        if (opcao != 0) pausar();
    } while (opcao != 0);
}

// DADOS INICIAIS (PARA TESTES)

void carregarDadosIniciais() {
    cout << "Carregando dados iniciais para testes...\n";
    
    // Cadastrar alguns exercícios
    Cardio* corrida = new Cardio("Corrida na esteira", 30, 10.5);
    Cardio* bicicleta = new Cardio("Bicicleta ergométrica", 45, 8.7);
    Forca* supino = new Forca("Supino reto", 60, 3, 10, 90);
    Forca* agachamento = new Forca("Agachamento livre", 80, 4, 8, 120);
    
    arvoreExercicios.inserir(corrida);
    arvoreExercicios.inserir(bicicleta);
    arvoreExercicios.inserir(supino);
    arvoreExercicios.inserir(agachamento);
    
    // Cadastrar algumas fichas
    Ficha* fichaIniciante = new Ficha("Treino Iniciante");
    fichaIniciante->adicionarExercicio(corrida);
    fichaIniciante->adicionarExercicio(supino);
    
    Ficha* fichaCardio = new Ficha("Treino Cardio Intenso");
    fichaCardio->adicionarExercicio(corrida);
    fichaCardio->adicionarExercicio(bicicleta);
    
    arvoreFichas.inserir(fichaIniciante);
    arvoreFichas.inserir(fichaCardio);
    
    // Cadastrar alguns alunos
    Aluno* joao = new Aluno("João Silva");
    Aluno* maria = new Aluno("Maria Santos");
    
    joao->adicionarFicha(fichaIniciante->getId());
    maria->adicionarFicha(fichaCardio->getId());
    
    arvoreAlunos.inserir(joao);
    arvoreAlunos.inserir(maria);
    
    cout << "Dados iniciais carregados com sucesso!\n";
}

int main() {
    cout << "=========================================\n";
    cout << "  SISTEMA DE GERENCIAMENTO DE ACADEMIA  \n";
    cout << "=========================================\n";
    
    char carregarDados;
    cout << "Deseja carregar dados iniciais para testes? (s/n): ";
    cin >> carregarDados;
    limparBuffer();
    
    if (carregarDados == 's' || carregarDados == 'S') {
        carregarDadosIniciais();
    }
    
    int opcao;
    do {
        mostrarMenuPrincipal();
        cin >> opcao;
        limparBuffer();
        
        switch (opcao) {
            case 1: menuAlunos(); break;
            case 2: menuExercicios(); break;
            case 3: menuFichas(); break;
            case 4: menuAssociacoes(); break;
            case 5: menuRelatorios(); break;
            case 0: 
                cout << "\n=========================================\n";
                cout << "  Encerrando sistema... Até logo!      \n";
                cout << "=========================================\n";
                break;
            default: 
                cout << "Opção inválida! Tente novamente.\n";
                pausar();
        }
    } while (opcao != 0);
    
    return 0;
}