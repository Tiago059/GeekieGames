#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <time.h>
#include "GeekieGames.h";

using namespace std;

// Funções que ajudam as funções principais
void esperar(int segundos){
    /* Faz o programa esperar e não fazer nada por X segundos. */
	clock_t fim;
	fim = clock () + segundos * CLOCKS_PER_SEC;
	while (clock() < fim) {}
}

int buscaCaractere(char *stringue, char busca){
    /* usar o laço de while com isalpha ou algo assim */
    /* Essa função faz uma procura de um caractere específico em uma string. */
    bool achou = false;
    unsigned i;

    char *p;
    p = strstr(stringue, " "); // serve para verificar se há mais de um caractere de espaço em branco

    for (i = 0;i < strlen(stringue);i++){
        if( (stringue[i] == busca) || (p != NULL) ){
            achou = true;
            break;
        }
    }

    if (achou) return 1;
    else return 0;

}
char *split(char *stringue, char delimitador, unsigned *posicao){
    char *palavra;
    unsigned i, j, k;
    bool achou = false;

    for (i = *posicao;i < strlen(stringue);i++){
        if (stringue[i] == delimitador){
            palavra = new char[i-(*posicao)];
            j = 0;
            for (k = *posicao;k < i;k++){
                palavra[j] = stringue[k];
                j++;
            }
            *posicao = i + 1;
            achou = true;
            break;
        }
    }

    if (achou == false){
        palavra = new char[strlen(stringue)-(*posicao)];
        j = 0;
        for (k = *posicao;k < strlen(stringue);k++){
            palavra[j] = stringue[k];
            j++;
        }
        *posicao = strlen(stringue);
        return palavra;
    }

    else {
        return palavra;
    }

}

// funções principais
void menu_principal(){

    system("clear");
    cout << "Bem-vindo ao Recomenda Exercicios!";
    cout << "\nPor favor, digite uma opção:";
    cout << "\n1 - Novo Usuario? Cadastre-se agora.\n2 - Ja tem cadastro? Efetue login.\n0 - Sair da Aplicacao\n";
    cout << "\nDigite: ";

    selecionar_opcao();

}

void selecionar_opcao(){
    unsigned opcao;
    cin >> opcao;

    switch(opcao){
        case 1:
            cadastrar_usuario();
            break;
        case 2:
            login_usuario();
            break;
        case 0:
            exit(0);
            break;
        default:
            system("clear");
            cout << "Entrada invalida.Tente novamente.\n";
            esperar(1.5);
            system("clear");
            menu_principal();
    }
}

void cadastrar_usuario(){
    system("clear");
    login usuario; // variavel que receberá o nome de usuario e senha

    cout << "Bem-vindo a tela de cadastro de novos usuarios!\n" << endl;

    // adquirindo o nome de usuário
    while (true){
        cout << "Digite um nome de usuario que voce queira. \nPode usar qualquer simbolo exceto o '*' ou '/':";
        cin >> usuario.nome;
        // cin.getline(usuario.nome)

        // verificando se o nome é válido, e irá continuar nesse loop até que o usuário digite corretamente.
        if(((buscaCaractere(usuario.nome, '*')) + (buscaCaractere(usuario.nome, '/')) + (buscaCaractere(usuario.nome, ' '))) != 0){
            cout << "Entrada invalida. Digite novamente.\n";
            esperar(2);
            system("clear");
         }
         else {
            break;
         }
    }

    // gravando o nome do usuário no arquivo de texto
    fstream arquivo;
    arquivo.open("database/logins.txt", ios::out|ios::app);
    arquivo << usuario.nome << "*"; // lembre-se: o * é o delimitador que separa o nome de usuário de seu login
    arquivo.close();

    // adquirindo a senha do usuário
    while (true){
        cout << "Digite uma senha. \nEla tambem nao pode conter '*', '/' ou espacos em branco: ";
        cin >> usuario.senha;

        // verificando se a senha é válida, do mesmo jeitinho
        if(((buscaCaractere(usuario.senha, '*')) + (buscaCaractere(usuario.senha, '/')) + (buscaCaractere(usuario.senha, ' '))) != 0){
            cout << "Entrada invalida. Digite novamente.\n";
            esperar(2);
            system("clear");
         }
         else {
            break;
         }

    }

    // gravando a senha do usuário no arquivo de texto
    arquivo.open("database/logins.txt", ios::out|ios::app);
    arquivo << usuario.senha << "/"; // lembre-se: o / é o delimitador que separa cada LOGIN do outro
    arquivo.close();

    // mostrando pro usuário que deu tudo certo
    cout << "\nLogin: " << usuario.nome << endl;
    cout << "Senha: " << usuario.senha << endl;
    cout << "Cadastrado com sucesso!\n";
    esperar(2);
    system("clear");

    // chamando o menu principal novamente
    menu_principal();
}

void login_usuario(){
    system("clear");
    login usuario; // novo login
    string linha; // string que guarda os dados do arquivo de texto
    fstream arquivo; // manipulador de arquivos
    bool achou = false; // flag pra saber se o login foi valido ou nao
    char *string1, *string2, *string3, *buffer;
    unsigned posBusca1 = 0, posBusca2 = 0; /* preciso de dois posBuscas e dois strings porque vou dividir
    minha string duas vezes por dois delimitadores diferentes */

    // ficará no loop até digitar corretamente ou voltar ao menu inicial
    while (achou == false){

        cout << "Bem-vindo a tela de login!\nDigite suas informacoes para acessar o Proximo Exercicio!\n";
        cout << "Digite o seu nome de usuario: ";
        cin >> usuario.nome;
        cout << "Digite a sua senha: ";
        cin >> usuario.senha;

        // retirando do arquivo de texto os logins e salvando em buffer
        arquivo.open("database/logins.txt", ios::in);
        getline(arquivo, linha); // pegando a linha que é string
        buffer = new char[linha.length()]; // alocando dinamicamente um vetor de char com o tamanho da string
        strcpy(buffer, linha.c_str()); // copiando o conteudo da string para o vetor de char

        /* posBusca1 e posBusca2 são modificados na função toda vez que um delimitador novo é encontrado
        portanto, ao chamar a função mais de uma vez, ele irá procurar a partir
        do novo valor de posBuscaX */
        // separando os logins e fazendo a checagem
        // fazendo a checagem inicial se o usuario é o queridissimo adminstrador
        if ( (strcmp(usuario.nome, "admin") == 0) && (strcmp(usuario.senha, "admin") == 0) ) {
            cadastrar_exercicio();
        }
        else {
            while (posBusca1 < strlen(buffer)){
                // separando um login (nome e senha juntos)
                string1 = split(buffer, '/', &posBusca1);
                cout << string1 << endl;
                // separando o nome
                string2 = split(string1, '*', &posBusca2);
                cout << string2 << endl;
                // separando a senha
                string3 = split(string1, '*', &posBusca2);
                cout << string3 << endl;
                // comparando se a senha e o nome batem
                if ( (strcmp(usuario.nome, string2) == 0) && (strcmp(usuario.senha, string3) == 0) ) {
                    achou = true;
                    break;
                }
                posBusca2 = 0; // para sempre procurar desde o inicio da substring, a cada interação
            }
        }


        // mostrando pro usuario se ele conseguiu logar ou não
        if (achou) menu_exercicios(usuario); // retornando o usuário atual para a função do menu de exercícios.
        else {
            system("clear");
            cout << "Usuario e/ou senha invalidos. Tente novamente.\n";
            esperar(2);
            system("clear");
            login_usuario();
        }

    }

}

void cadastrar_exercicio(){
    system("clear");
    exercicio novoExercicio; // criando um novo exercicio

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

    /* alocando um novo vetor para guardar a extensão do arquivo de texto. Os 26 se referem a soma das strings constantes
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
    arquivo << novoExercicio.categoria << "\n";
    arquivo << novoExercicio.dificuldade << "\n";
    arquivo << "\n";
    arquivo.close();

    // Exibindo para o usuario que deu tudo certo
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

    // deletando nosso vetor caminho, pois usuaremos ele na proxima execução do programa.
    delete novoExercicio.caminho;

    // um swtichzinho só para facilitar o cadastro de vários exercícios
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

const char *selecionar_categoria(){
    const char *categoria;
    int opcao;

    while (true) {
        cout << "\n\nSelecione a categoria: ";
        cout << "\n1 - Sintaxe\n2 - Condicionais\n3 - Lacos de Repeticao\n4 - Vetores & Matrizes";
        cout << "\n5 - Funcoes\n6 - Ponteiros\n7 - Strings\n8 - Estruturas\n9 - Arquivos\n0 - Retornar ao menu principal\n";
        cout << "Digite: ";
        cin >> opcao;

        if ( (opcao < 0) || (opcao > 9) ){
            system("clear");
            cout << "Categoria invalida. Tente novamente.";
            system("clear");
            continue;
        }
        else {
            if (opcao == 0) menu_principal();
            else if (opcao == 1) categoria = "Sintaxe";
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

const char *selecionar_dificuldade(){
    const char *dificuldade;
    unsigned opcao;

    while (true) {
        cout << "\n\nSelecione a dificuldade: ";
        cout << "\n1 - Facil\n2 - Medio\n3 - Dificil\n0 - Retornar ao menu principal\n";
        cout << "Digite: ";
        cin >> opcao;

        if ( (opcao < 0) || (opcao > 3) ){
            system("clear");
            cout << "Dificuldade invalida. Tente novamente.";
            continue;
        }
        else {
            if (opcao == 0) menu_principal();
            else if (opcao == 1) dificuldade = "Facil";
            else if (opcao == 2) dificuldade = "Medio";
            else if (opcao == 3) dificuldade = "Dificil";

            system("clear");
            break;
        }
    }

    return dificuldade;
}

void menu_exercicios(login usuarioAtual){
    system("clear");
    unsigned opcao;
    const char *categoriaEscolhida, *dificuldadeEscolhida;
    ifstream arquivo;
    string linha;

    cout << "Bem-vindo a tela de visualizacao de exercicios, " << usuarioAtual.nome << "!";
    cout << "\nSelecione uma das opcoes a seguir: ";
    cout << "\n1 - Visualizar exercicios aleatoriamente por categoria/dificuldade";
    cout << "\n2 - Exibir Ajuda";
    cout << "\n3 - Logoff & Retornar ao Menu Principal";
    cout << "\nDigite: ";
    cin >> opcao;

    switch (opcao){
        case 1:
            // Escolhendo a categoria e a dificuldade para saber qual arquivo de exercicios deverá ser lido
            cout << "\nEscolha uma categoria de exercicios: ";
            categoriaEscolhida = selecionar_categoria();
            cout << "Escolha uma dificuldade dos exercicios: ";
            dificuldadeEscolhida = selecionar_dificuldade();

            cout << "\n";
            cout << categoriaEscolhida << "  " << dificuldadeEscolhida;
            break;
        case 2:
            // Exibindo o arquivo de ajuda para o usuário. Nada demais.
            arquivo.open("database/help.txt");
            // lendo o arquivo de texto ate o fim dele
            while (!arquivo.eof()){
                getline(arquivo, linha);
                cout << linha << endl;
            }
            arquivo.close();
            system("read -p '\nAperte qualquer tecla para voltar:' var"); // para o linux. no windows, use system("pause")
            menu_exercicios(usuarioAtual);
            break;
        case 3:
            system("clear");
            cout << "Ate a proxima, " << usuarioAtual.nome << "!";
            menu_principal();
            break;
        default:
            system("clear");
            cout << "Opcao invalida. Tente novamente.";
            menu_exercicios(usuarioAtual);
    }

}
