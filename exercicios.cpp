#include "estruturas.h"
#include "suporte.h"
#include "exercicios.h"
#include "ajuda.h"
#include "menuInicial.h"
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

/*

Aqui ficam as funções que exibem o menu de exercícios,
cadastrar exercícios, e exibir os exercícios para o
usuário, além de funções secundarias que ajudam
nestas outras funções.

As descrições de cada função se encontram no arquivo
'exercicios.h' para não poluir visualmente (mais do
que já está poluído) este arquivo.

*/
void cadastrar_exercicio(){
    system("clear");
    exercicio novoExercicio; // Criando um novo exercicio

    // selecionando uma categoria dentre uma lista
    novoExercicio.categoria = selecionar_categoria();

    // mesma coisa, agora para a dificuldade
    novoExercicio.dificuldade = selecionar_dificuldade();

    cin.ignore();

    // Lendo o titulo do exercicio, e checando se o cara simplesmente não apertou enter sem digitar nada
    while (true){
        system("clear");
        cout << "|-------------------------------------------------------------|\n";
        cout << "|             Cadastrando Novo Exercicio: Titulo              |\n";
        cout << "|-------------------------------------------------------------|\n";
        cout << "Digite o titulo do exercicio: ";
        getline(cin, novoExercicio.titulo);
        if (novoExercicio.titulo.length() == 0){
            system("clear");
            cout << "O titulo do exercicio nao pode ficar vazio!\n";
            esperar(1.5);
            continue;
        }
        else break;
    }

    // Lendo a descricao do exercicio, do mesmo jeito que antes
    while (true){
        system("clear");
        cout << "|-------------------------------------------------------------|\n";
        cout << "|           Cadastrando Novo Exercicio: Descricao             |\n";
        cout << "|-------------------------------------------------------------|\n";
        cout << "Digite a descricao do exercicio: ";
        getline(cin, novoExercicio.descricao);
        if (novoExercicio.descricao.length() == 0){
            system("clear");
            cout << "A descricao do exercicio nao pode ficar vazia!\n";
            esperar(1.5);
            continue;
        }
        else break;
    }

    // Finalmente, salvando as devidas informações no arquivo de texto
    fstream arquivo;


    // Criando o caminho de onde o arquivo será salvo, com base na categoria e dificuldade
    /* Alocando um novo vetor para guardar a extensão do arquivo de texto. Os 26 se referem a soma das strings constantes
    vistas aí no código, mais o tamanho da categoria e da dificuldade, e depois mais 1 para nao estourar o vetor */
    novoExercicio.caminho = new char[26 + (strlen(novoExercicio.categoria)*2) + strlen(novoExercicio.dificuldade) + 1];
    //Formato padrão do caminho: database/categoria/categoria-dificuldade.txt
    strcat(novoExercicio.caminho, "database/exercicios/");
    strcat(novoExercicio.caminho, novoExercicio.categoria);
    strcat(novoExercicio.caminho, "/");
    strcat(novoExercicio.caminho, novoExercicio.categoria);
    strcat(novoExercicio.caminho, "-");
    strcat(novoExercicio.caminho, novoExercicio.dificuldade);
    strcat(novoExercicio.caminho, ".txt");
    // Ao final disso, novoExercicio.caminho deverá ter algo como: "database/exercicios/Sintaxe/Sintaxe-Facil.txt"

    // Finalmente, gravando o exercício no arquivo de texto. Note que sempre termina com um '\n', o nosso novo delimitador.
    arquivo.open(novoExercicio.caminho, ios::out|ios::app);
    arquivo << novoExercicio.titulo << "\n";
    arquivo << novoExercicio.descricao << "\n";
    arquivo << "\n";
    arquivo.close();

    // Exibindo para o admin os dados do exercício, com um delay de leve no final para ele ler tudo calmamente
    system("clear");
    cout << "|-------------------------------------------------------------|\n";
    cout << "|           Novo exercicio cadastrado com sucesso!            |\n";
    esperar(1);
    cout << "|-------------------------------------------------------------|\n";
    cout << "|         Exercicio alterado no seguinte arquivo:             |\n";
    cout << " " << novoExercicio.caminho << endl;
    esperar(1);
    cout << "|-------------------------------------------------------------|\n";
    cout << "|                  Titulo do exercicio:                       |\n";
    cout << " " << novoExercicio.titulo << endl;
    esperar(1);
    cout << "|-------------------------------------------------------------|\n";
    cout << "|                 Descricao do exercicio:                     |\n";
    cout << " " << novoExercicio.descricao << endl;
    esperar(1);
    cout << "|-------------------------------------------------------------|\n";
    cout << "|                 Categoria do exercicio:                     |\n";
    cout << " " << novoExercicio.categoria << endl;
    esperar(1);
    cout << "|-------------------------------------------------------------|\n";
    cout << "|                  Dificuldade do exercicio:                  |\n";
    cout << " " << novoExercicio.dificuldade << endl;
    cout << "|-------------------------------------------------------------|\n";
    esperar(1);

    // Deletando nosso vetor caminho, pois poderemos usar ele na proxima execução da função do programa e para liberar memória
    delete novoExercicio.caminho;

    // Um swtichzinho só para facilitar o cadastro de vários exercícios
    cout << "\n\nCadastrar novo exercicio?(S/N)\nDigite: ";
    char opcao;
    cin >> opcao;
    switch (opcao){
        case 'S':
        case 's':
            cadastrar_exercicio();
            break;
        case 'N':
        case 'n':
            menu_principal();
            break;
        default:
            cout << "Opcao invalida.";

    }

}

/* ---------------------------------------------------------------- */
void menu_exercicios(login usuarioAtual){
    system("clear");
    unsigned i, opcao, quantExercicios = 0;
    int numero, anterior = -1;
    const char *categoriaEscolhida, *dificuldadeEscolhida;
    char *caminhoExercicio;
    exercicio *listaExercicios;
    ifstream arquivo;
    string linha, linhaTitulo, linhaDescricao, linhaPivo;

    cout << "|--------------------------------------------------------------------|\n";
    cout << "|                    Visualizacao de exercicios                      |\n";
    cout << "|--------------------------------------------------------------------|\n";
    cout << " Bem-vindo(a), " << usuarioAtual.nome << "!\n";
    cout << "|--------------------------------------------------------------------|\n";
    cout << "|                       Opcoes Disponiveis                           |\n";
    cout << "|                                                                    |\n";
    cout << "| 1 - Visualizar exercicios aleatoriamente por categoria/dificuldade |\n";
    cout << "| 2 - Exibir a ajuda                                                 |\n";
    cout << "| 3 - Logoff & Retornar ao Menu Principal                            |\n";
    cout << "|--------------------------------------------------------------------|\n";
    cout << "Selecione uma das opcoes:";
    cin >> opcao;

    switch (opcao){ // trocar por um if
        case 1:
            system("clear");
            // Escolhendo a categoria e a dificuldade para saber qual arquivo de exercicios deverá ser lido
            cout << "Escolha uma categoria de exercicios: \n";
            categoriaEscolhida = selecionar_categoria();
            cout << "Escolha uma dificuldade dos exercicios: \n";
            dificuldadeEscolhida = selecionar_dificuldade();

            // Definindo qual arquivo de exercicios sera lido
            caminhoExercicio = new char[26 + (strlen(categoriaEscolhida)*2) + strlen(dificuldadeEscolhida) + 1];
            //Formato padrão do caminho: database/categoria/categoria-dificuldade.txt
            strcat(caminhoExercicio, "database/exercicios/");
            strcat(caminhoExercicio, categoriaEscolhida);
            strcat(caminhoExercicio, "/");
            strcat(caminhoExercicio, categoriaEscolhida);
            strcat(caminhoExercicio, "-");
            strcat(caminhoExercicio, dificuldadeEscolhida);
            strcat(caminhoExercicio, ".txt");

            arquivo.open(caminhoExercicio, ios::in); // abrindo nosso maravilhoso arquivo
            // contando quantos exercicios ha no arquivo de texto escolhido

            do {
                if (!arquivo.is_open()){ // Checando primeiramente se o arquivo existe, ou seja: se ele existe entao ele estará aberto
                    system("clear");
                    cout << "Desculpe, nao ha nenhum exercicio cadastrado com essa categoria e/ou dificuldade.\n";
                    esperar(2);
                    system("clear");
                    delete caminhoExercicio; // Zerando o vetor de caminho para ser usado na próxima execução
                    arquivo.close(); // Limpando o buffer do arquivo, pois deixei memória aberta ao tentar abrir um arquivo (e isso gerou um bug)
                    menu_exercicios(usuarioAtual); // Chamando de volta o menu de exercícios com o usuário logado atualmente
                    break;
                }
                else {
                    getline(arquivo, linha);
                    if (linha.length() == 0) quantExercicios++; // Significa que ele encontrou o delimitador
                }
            } while(!arquivo.eof());

            // Gravando os exercicios no vetor de exercicios
            quantExercicios--; // como o delimitador é o \n, no final da execução o quantExercicios ficara com 1 a mais
            listaExercicios = new exercicio[quantExercicios]; // Alocando nosso vetorzinho de exercicios

            /* Fechando o arquivo e abrindo-o novamente. Porque? Para fazer o ponteiro do arquivo retornar a posicao do inicio
            do arquivo. seekg() por algum motivo místico obscuro não está funcionando... */
            arquivo.close();
            arquivo.open(caminhoExercicio, ios::in);

            for (i = 0; i < quantExercicios; i++){
                // Pegando a primeira linha, o titulo
                getline(arquivo, linhaTitulo);
                listaExercicios[i].titulo = linhaTitulo;

                // Pegando a segunda linha, a descricao
                getline(arquivo, linhaDescricao);
                listaExercicios[i].descricao = linhaDescricao;

                // Pegando a categoria e a dificuldade escolhida antes
                listaExercicios[i].categoria = categoriaEscolhida;
                listaExercicios[i].dificuldade = dificuldadeEscolhida;

                getline(arquivo, linhaPivo); /* serve apenas para pular uma linha para a proxima linha do arquivo,
                já que nessa linha encontra-se o delimitador, fazendo ir ao proximo bloco de exercicios (ou ao fim do arquivo) */
            }

            // Exibindo os exercicios para o usuario, aleatoriamente
            numero = aleatorio(0, quantExercicios-1); // Escolhendo o primeiro exercício aleatório
            exibir_exercicios(numero, anterior, quantExercicios, listaExercicios, usuarioAtual);

            arquivo.close();
            break;
        case 2:
            exibirAjuda();
            menu_exercicios(usuarioAtual);
            break;
        case 3:
            menu_principal();
            break;
        default:
            system("clear");
            cout << "Opcao invalida. Tente novamente.";
            menu_exercicios(usuarioAtual);
    }

}

/* ---------------------------------------------------------------- */
void exibir_exercicios(int numero, int anterior, int quantExercicios, exercicio *exercicios, login usuario){
    system("clear");
    int *exerciciosVisualizados, quantVisu = 0, pivo, opcao, i, j;
    string linhaTeste;
    fstream arquivo;
    char *caminho;
    bool deletar;

    if ( (quantExercicios - 1) != 0 ) { // Se a lista de exercícios têm mais de duas questões, então podemos gerar um intervalo
        while (numero == anterior) numero = aleatorio(0, quantExercicios-1); // pra garantir que um mesmo exercicio não se repita
    }

    // Criando o caminho até o arquivo do historico
    // Padrão: "database/exercicios/Sintaxe/historico/italo-tiago.txt"
    caminho = new char[35 + strlen(exercicios[0].categoria) + strlen(exercicios[0].dificuldade) + strlen(usuario.nome) + 1];
    strcat(caminho, "database/");
    strcat(caminho, "exercicios/");
    strcat(caminho, exercicios[0].categoria);
    strcat(caminho, "/");
    strcat(caminho, "historico");
    strcat(caminho, exercicios[0].dificuldade);
    strcat(caminho, "/");
    strcat(caminho, usuario.nome);
    strcat(caminho, ".txt");

    arquivo.open(caminho, ios::out|ios::app); // Criando/acessando o arquivo
    arquivo.close();

    // Fazendo os exercicios escolhidos pelo usuário não repetirem mais
    arquivo.open(caminho, ios::in);
    arquivo >> linhaTeste;
    arquivo.close();

    if ( linhaTeste.length() != 0 ){ // Significa que há números de exercícios que o usuário não quer mais ver
        // Contando quantos exercícios já foram visualizados
        arquivo.open(caminho, ios::in);
        while (arquivo.eof() == false){
            arquivo >> pivo; // Variável "pivô", serve apenas para mover o cursor por dentro do arquivo
            quantVisu++;
        }
        arquivo.close();
        exerciciosVisualizados = new int[quantVisu - 1]; // Subtrai-se 1 porque o cursor vai até o eof, tendo um elemento a mais
        // Checando se o usuário marcou todas as questões como resolvidas
        if ( (quantVisu - 1) >= quantExercicios){
            cout << "|----------------------------------------------------------------------------|\n";
            cout << "|   Todos os exercicios desta categoria e dificuldade foram marcados         |\n";
            cout << "|   como visualizados pelo usuario. Selecionar a opcao 4 desfaz isso.        |\n";
            cout << "|----------------------------------------------------------------------------|\n\n";
            cout << " Titulo: --" << endl;
            cout << " Enunciado: --\n\n";
        }
        else {
            // Criando o vetor com exercícios visualizados e preenchendo eles
            arquivo.open(caminho, ios::in);
            for (i = 0;i < (quantVisu - 1);i++) arquivo >> exerciciosVisualizados[i]; // Gravando no vetor os exercícios visualizados
            // Checando se o número gerado aleatoriamente está dentro do vetor de exercícios visualizados
            i = j = 0;
            while (i < (quantVisu - 1)){
                j++;
                if (numero == exerciciosVisualizados[i]){
                    numero = aleatorio(0, quantExercicios-1); // Gerando uma nova tentativa de exercício
                    j = 0; // Para fazer reinciar o loop, fazendo que o programa só saia desse loop quando encontrar um número que não esteja no vetor
                }
                i = j;
            }
            delete exerciciosVisualizados; // Aquela liberada de memória básica
            cout << "|----------------------------------------------------------------------------|\n";
            cout << "\t\t\t\tExercicio Nº " << numero + 1 << endl;
            cout << "|----------------------------------------------------------------------------|\n\n";
            cout << " Titulo: " << exercicios[numero].titulo << endl;
            cout << " Enunciado: " << exercicios[numero].descricao << "\n\n";
        }
    }
    else {
        cout << "|----------------------------------------------------------------------------|\n";
        cout << "\t\t\t\tExercicio Nº " << numero + 1 << endl;
        cout << "|----------------------------------------------------------------------------|\n\n";
        cout << " Titulo: " << exercicios[numero].titulo << endl;
        cout << " Enunciado: " << exercicios[numero].descricao << "\n\n";
    }

    cout << "|----------------------------------------------------------------------------|\n";
    cout << "|                                 Menu                                       |\n";
    cout << "|----------------------------------------------------------------------------|\n";
    cout << "| 1 - Proximo Exercicio                2 - Exercicio Anterior                |\n";
    cout << "| 3 - Marcar como visualizada          4 - Reverter as visualizacoes         |\n";
    cout << "| 5 - Voltar ao menu de exercicios     6 - Voltar ao menu prinicipal(Logoff) |\n";
    cout << "|----------------------------------------------------------------------------|\n";
    cout << "Selecione uma opcao: ";
    cin >> opcao;

    if (opcao == 1){
        deletar = true;
        anterior = numero; // Guardando o exercicio anterior, para a próxima execução
        numero = aleatorio(0, quantExercicios-1); // E gerando um novo exercicio aleatorio
    }
    else if (opcao == 2){
        deletar = true;
        if (anterior == -1) {
            system("clear");
            cout << "Opcao invalida (pois estamos no inicio do programa...). \n";
            system("clear");
            esperar(1.5);
        }
        else {
            int aux = anterior; // Imprimindo o exercicio anterior, trocando os valores de numero e anterior
            anterior = numero;
            numero = aux;
        }
    }
    else if (opcao == 3){
        deletar = true;
        fstream arquivoVisu;
        arquivoVisu.open(caminho, ios::out|ios::app); // Abrindo o arquivo de visualizações
        arquivoVisu << numero << " "; // Gravando o número do exercício que o usuário não quer mais ver
        arquivoVisu.close();
    }
    else if (opcao == 4){
        deletar = true;
        // Zerando o arquivo de visualizações, abrindo e fechando o arquivo do usuário
        fstream arquivoVisu;
        arquivoVisu.open(caminho, ios::out); // Note que isto funciona porque não abro o arquivo no modo ios::app
        arquivoVisu.close();
        numero = aleatorio(0, quantExercicios-1); // Gerando um novo número aleatório, só para continuar o programa
    }
    else if (opcao == 5) {
        delete caminho;
        menu_exercicios(usuario);
    }
    else if (opcao == 6){
        delete caminho;
        menu_principal();
    }
    else {
        deletar = true;
        system("clear");
        cout << "Opcao invalida.\n";
        esperar(1.5);
        numero = aleatorio(0, quantExercicios-1); // Gerando um novo número aleatório, só para continuar o programa
    }

    // Se ele entra no if, então preciso garantir que o vetor de caminho será deletado e chamar novamente a função
    if (deletar){
        delete caminho;
        exibir_exercicios(numero, anterior, quantExercicios, exercicios, usuario);
    }
}
/* ---------------------------------------------------------------- */
const char *selecionar_categoria(){
    system("clear");
    const char *categoria;
    int opcao;

    cout << "|-------------------------------------------------------------|\n";
    cout << "|                   Categorias Disponiveis                    |\n";
    cout << "|-------------------------------------------------------------|\n";
    cout << "| 1 - Sintaxe                                                 |\n";
    cout << "| 2 - Condicionais                                            |\n";
    cout << "| 3 - Lacos de Repeticao                                      |\n";
    cout << "| 4 - Vetores & Matrizes                                      |\n";
    cout << "| 5 - Funcoes                                                 |\n";
    cout << "| 6 - Ponteiros                                               |\n";
    cout << "| 7 - Strings                                                 |\n";
    cout << "| 8 - Estruturas                                              |\n";
    cout << "| 9 - Arquivos                                                |\n";
    cout << "|-------------------------------------------------------------|\n";
    cout << "\n\nSelecione a categoria: ";
    cin >> opcao;

    switch (opcao){
        case 1: categoria = "Sintaxe"; break;
        case 2: categoria = "Condicionais"; break;
        case 3: categoria = "Lacos de Repeticao"; break;
        case 4: categoria = "Vetores & Matrizes"; break;
        case 5: categoria = "Funcoes"; break;
        case 6: categoria = "Ponteiros"; break;
        case 7: categoria = "Strings"; break;
        case 8: categoria = "Estruturas"; break;
        case 9: categoria = "Arquivos"; break;
        default:
            system("clear");
            cout << "Categoria invalida. Tente novamente.\n";
            esperar(1.5);
            system("clear");
            selecionar_categoria();
            break;
    }

    return categoria;
}

/* ---------------------------------------------------------------- */
const char *selecionar_dificuldade(){
    system("clear");
    const char *dificuldade;
    unsigned opcao;

    cout << "|-------------------------------------------------------------|\n";
    cout << "|                   Dificuldades Disponiveis                  |\n";
    cout << "|-------------------------------------------------------------|\n";
    cout << "| 1 - Facil                                                   |\n";
    cout << "| 2 - Medio                                                   |\n";
    cout << "| 3 - Dificil                                                 |\n";
    cout << "|-------------------------------------------------------------|\n";
    cout << "\nSelecione a dificuldade: ";
    cin >> opcao;

    switch (opcao){
        case 1: dificuldade = "Facil"; break;
        case 2: dificuldade = "Medio"; break;
        case 3: dificuldade = "Dificil"; break;
        default:
            system("clear");
            cout << "Dificuldade invalida. Tente novamente.\n";
            esperar(1.5);
            system("clear");
            selecionar_dificuldade();
            break;
    }

    return dificuldade;
}
