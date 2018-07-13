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

    cout << "Bem-vindo a tela de cadastro de exercicios, adminstrador.\n";
    // selecionando uma categoria dentre uma lista
    cout << "1. Selecione a categoria do exercicio.";
    novoExercicio.categoria = selecionar_categoria();

    // mesma coisa, agora para a dificuldade
    cout << "2. Selecione a dificuldade do exercicio.";
    novoExercicio.dificuldade = selecionar_dificuldade();

    /* Ao pressionar o enter na função anterior houve um salto para o proximo comando depois do getline
    a seguir, ou seja, esse problema ocorre pois o comando ‘\n’ (quebra de linha) está no buffer fazendo
    com que o comando getline interprete que é o final do caracter, por esse motivo é realizado um salto para o próximo comando.
    Sempre usar cin.ignore apos digitar um enter que depois desse enter apareça um getline. */
    cin.ignore();

    // Lendo o titulo do exercicio
    cout << "3. Digite o titulo do exercicio.\nDigite: ";
    getline(cin, novoExercicio.titulo);

    // Lendo a descricao do exercicio
    system("clear");
    cout << "4. Digite a descricao do exercicio.\n";
    getline(cin, novoExercicio.descricao);

    // Finalmente, salvando as devidas informações no arquivo de texto
    fstream arquivo;
    /* Criando o caminho de onde o arquivo será salvo, com base na categoria e dificuldade */

    /* Alocando um novo vetor para guardar a extensão do arquivo de texto. Os 26 se referem a soma das strings constantes
    vistas aí no código, mais o tamanho da categoria e da dificuldade, e depois mais 1 para nao estourar o vetor */
    novoExercicio.caminho = new char[(26 + (strlen(novoExercicio.categoria)*2) + strlen(novoExercicio.dificuldade) + 1)];
    //Formato padrão do caminho: database/categoria/categoria-dificuldade.txt
    strcat(novoExercicio.caminho, "database/exercicios/");
    strcat(novoExercicio.caminho, novoExercicio.categoria);
    strcat(novoExercicio.caminho, "/");
    strcat(novoExercicio.caminho, novoExercicio.categoria);
    strcat(novoExercicio.caminho, "-");
    strcat(novoExercicio.caminho, novoExercicio.dificuldade);
    strcat(novoExercicio.caminho, ".txt");
    // AO final disso, novoExercicio caminho deverá ter algo como: "database/exercicios/Sintaxe/Sintaxe-Facil.txt"

    // Finalmente, gravando o exercício no arquivo de texto. Note que sempre termina com um '\n', o nosso novo delimitador.
    arquivo.open(novoExercicio.caminho, ios::out|ios::app);
    arquivo << novoExercicio.titulo << "\n";
    arquivo << novoExercicio.descricao << "\n";
    arquivo << "\n";
    arquivo.close();

    // Exibindo para o admin os dados do exercício, com um delay de leve para ele ler tudo calmamente
    system("clear");
    cout << "Novo exercicio cadastrado com sucesso!" << endl;
    esperar(1);
    cout << "Exercicio alterado em: " << novoExercicio.caminho << endl;
    esperar(1);
    cout << "Titulo: " << novoExercicio.titulo << endl;
    esperar(1);
    cout << "Descricao: "<< novoExercicio.descricao << endl;
    esperar(1);
    cout << "Categoria: " << novoExercicio.categoria << endl;
    esperar(1);
    cout << "Dificuldade: " << novoExercicio.dificuldade << endl;

    // Deletando nosso vetor caminho, pois poderemos usar ele na proxima execução da função do programa.
    delete novoExercicio.caminho;

    // Um swtichzinho só para facilitar o cadastro de vários exercícios
    cout << "\n\nCadastrar novo exercicio?(S/N)?\nDigite: ";
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

    cout << "Bem-vindo a tela de visualizacao de exercicios, " << usuarioAtual.nome << "!";
    cout << "\nSelecione uma das opcoes a seguir: ";
    cout << "\n1 - Visualizar exercicios aleatoriamente por categoria/dificuldade";
    cout << "\n2 - Exibir Ajuda";
    cout << "\n3 - Logoff & Retornar ao Menu Principal";
    cout << "\nDigite: ";
    cin >> opcao;

    switch (opcao){ // trocar por um if
        case 1:
            system("clear");
            // Escolhendo a categoria e a dificuldade para saber qual arquivo de exercicios deverá ser lido
            cout << "Escolha uma categoria de exercicios: ";
            categoriaEscolhida = selecionar_categoria();
            cout << "Escolha uma dificuldade dos exercicios: ";
            dificuldadeEscolhida = selecionar_dificuldade();

            // Definindo qual arquivo de exercicios sera lido
            caminhoExercicio = new char[(26 + (strlen(categoriaEscolhida)*2) + strlen(dificuldadeEscolhida) + 1)];
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
                if (!arquivo.is_open()){ // Checando primeiramente se o arquivo existe, ou seja: se ele existe entao ele está aberto
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

                listaExercicios[i].resolvido = false; // valor padrão, pois o usuario ainda nao marcou como resolvida

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
    unsigned opcao;
    if ( (quantExercicios - 1) != 0 ) { // Se a lista de exercícios têm mais de duas questões, então podemos gerar um intervalo
        while (numero == anterior) numero = aleatorio(0, quantExercicios-1); // pra garantir que um mesmo exercicio não se repita
    }

    cout << "\t\t\t\tExercicio Nº " << numero + 1 << endl;
    cout << "Titulo: " << exercicios[numero].titulo << endl;
    cout << "Enunciado: " << exercicios[numero].descricao << "\n\n";

    cout << "Selecione uma opcao:";
    cout << "\n1 - Proximo Exercicio            \t2 - Exercicio Anterior";
    cout << "\n3 - Marcar como visualizada      \t4 - Reverter as visualizacoes";
    cout << "\n5 - Voltar ao menu de exercicios \t6 - Voltar ao menu prinicipal (Logoff)";
    cout << "\nDigite: ";
    cin >> opcao;

    switch (opcao) {
        case 1:
            anterior = numero; // Guardando o exercicio anterior, para a próxima execução
            numero = aleatorio(0, quantExercicios-1); // E gerando um novo exercicio aleatorio
            exibir_exercicios(numero, anterior, quantExercicios, exercicios, usuario);
            break;
        case 2:
            if (anterior == -1) {
                system("clear");
                cout << "Opcao invalida (inicio do programa). \n";
                esperar(1.5);
                exibir_exercicios(numero, anterior, quantExercicios, exercicios, usuario); // Chamando novamente a funcao com o mesmo numero, mais um loop indireto
            }
            else exibir_exercicios(anterior, numero, quantExercicios, exercicios, usuario); // Imprimindo o exercicio anterior
            break;
        case 3:
            cout << "em desenvolvimento...";
            exit(0);
            break;
        case 4:
            cout << "em desenvolvimento...";
            exit(0);
            break;
        case 5:
            menu_exercicios(usuario);
            break;
        case 6:
            menu_principal();
            break;
        default:
            system("clear");
            cout << "Opcao invalida.\n";
            esperar(1.5);
            exibir_exercicios(numero, anterior, quantExercicios, exercicios, usuario);
    }

}
/* ---------------------------------------------------------------- */
const char *selecionar_categoria(){
    const char *categoria;
    int opcao;

    while (true) {
        cout << "\n\nSelecione a categoria: ";
        cout << "\n1 - Sintaxe\n2 - Condicionais\n3 - Lacos de Repeticao\n4 - Vetores & Matrizes";
        cout << "\n5 - Funcoes\n6 - Ponteiros\n7 - Strings\n8 - Estruturas\n9 - Arquivos";
        cout << "\nDigite: ";
        cin >> opcao;

        if ( (opcao < 0) || (opcao > 9) ){
            system("clear");
            cout << "Categoria invalida. Tente novamente.";
            system("clear");
            continue;
        }
        else { // substituir por switch
            if (opcao == 1) categoria = "Sintaxe";
            else if (opcao == 2) categoria = "Condicionais";
            else if (opcao == 3) categoria = "Lacos de Repeticao";
            else if (opcao == 4) categoria = "Vetores & Matrizes";
            else if (opcao == 5) categoria = "Funcoes";
            else if (opcao == 6) categoria = "Ponteiros";
            else if (opcao == 7) categoria = "Strings";
            else if (opcao == 8) categoria = "Estrutuas";
            else if (opcao == 9) categoria = "Arquivos";

            system("clear");
            break;
        }
    }

    return categoria;
}

/* ---------------------------------------------------------------- */
const char *selecionar_dificuldade(){
    const char *dificuldade;
    unsigned opcao;

    while (true) {
        cout << "\n\nSelecione a dificuldade: ";
        cout << "\n1 - Facil\n2 - Medio\n3 - Dificil";
        cout << "\nDigite: ";
        cin >> opcao;

        if ( (opcao < 0) || (opcao > 3) ){
            system("clear");
            cout << "Dificuldade invalida. Tente novamente.";
            continue;
        }
        else { // também trocar por switch
            if (opcao == 1) dificuldade = "Facil";
            else if (opcao == 2) dificuldade = "Medio";
            else if (opcao == 3) dificuldade = "Dificil";

            system("clear");
            break;
        }
    }

    return dificuldade;
}
