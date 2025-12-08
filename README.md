# EDBII-Proj-3a-Unidade
Projeto da terceira unidade de EDB II.
Componentes:
Lazaro Gabriel Ewerton da Silva Santos
Mayke Gian de Melo Gomes
Rian Abdias Balbino de Azevedo

O projeto se trata de um sistema de academia, onde podem ser cadastrados alunos, exercícios e fichas.
Os exercícios podem ser do tipo cardio ou de força, e podem ser adicionados numa ficha de treinos.
Os alunos podem ter várias fichas de treino.

Para compilar o código mais facilmente, utilize o Makefile, dentro da pasta src, simplesmente usando o comando:
`make`

Caso não possua o necessário para rodar o makefile use o comando:

`g++ -std=c++11 -Wall main.cpp Aluno.cpp Exercicio.cpp Cardio.cpp Forca.cpp Ficha.cpp -o academia`

Depois de compilar, é só rodar o arquivo do programa "academia".
