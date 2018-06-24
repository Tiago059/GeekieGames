#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "GeekieGames.h";

using namespace std;

// funções que ajudam as funções principais
void esperar(int segundos){
    /* Faz o programa esperar e não fazer nada por X segundos. */
	clock_t fim;
	fim = clock () + segundos * CLOCKS_PER_SEC;
	while (clock() < fim) {}
}

int buscaCaractere(char *stringue, char busca){
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

char **splitting(char *stringues, char delimiter, int mode){

    /* Essa função pega uma string e divide ela toda vez que encontra um delimitador específico, salvando todas as divisões
    em um vetor de strings (matriz). Existem dois modos: uma pra quando uma string TERMINA com um delimitador, que é o 1,
    e outro para quando a string NÃO TERMINA com um delimitador, que é o 2. A diferença está em preencher a ultima
    posicao da matriz. */

    //char stringue[] = {"bundas*rolando*a*mil*por*hora*"};
    char **split, *palavra;
    unsigned i, j, inicio = 0, fim, splitCount = 0, del = 0, indiceDel = 0, *delimiters, finish;

    // contando quantas ocorrências do delimitador existem
    for (i = 0;i < strlen(stringues);i++) if (stringues[i] == delimiter) del++;

    /* criando a matriz alocada dinamicamente com o total de palavras presentes na string
    antes que você pense, mas ah são 6 palavras mas o del deu 5 (por exemplo), lembre-se
    que ao ler o vetor começamos do 0, então na teoria, ir de 0 até 5 é o mesmo que 6. */
    split = new char*[del];
    for (i = 0;i < del;i++) split[i] = new char[100]; // sendo generoso e supondo palavras de no máximo 100 caracteres

    for (i = 0;i < del;i++) split[i] = NULL;
    //criando o vetor alocado dinamicamente que guardará todas as posições dos delimitadores
    delimiters = new unsigned[del];
    if (mode == 2) delimiters[del] = strlen(stringues); // isso vai ser util para pegar a ultima palavra apos o ultimo delimitador

    //guardando as posições dos delimitadores no vetor
    j = 0;
    for (i = 0;i < strlen(stringues);i++){
        if (stringues[i] == delimiter){
            delimiters[j] = i;
            j++;
        }
    }

    /* dependendo do modo, ele altera o final da string. Se o modo é 1, entao o tamanho da matriz vai até o delimitador,
    pois a string termina com um delimitador. Se não, acrescenta-se mais um espaço, pois neste caso, como após o ultimo
    delimitador da string existe mais caracteres, é preciso guardar uma posição para eles. */
    if (mode == 1) finish = del;
    else finish = del + 1;

    // retirando a palavra de intervalos específicos, definidos através das posições dos delimitadores
    while (splitCount < finish){
        fim = delimiters[indiceDel]; // o fim das palavras é definido pelos elementos de delimiters
        palavra = new char[fim - inicio]; // o tamanho da palavra é dado pelo fim da palavra menos o inicio

        j = 0;
        for (i = inicio;i < fim;i++){ // armazenando a palavra entre o intervalo do inicio ao fim
            palavra[j] = stringues[i];
            j++;
        }

        // salvando a palavra na matriz e preparando para a próxima execução do laço
        split[splitCount] = palavra; //
        //cout << palavra;
        palavra = NULL; // zerando palavra para novos usos nas próximas interações
        splitCount++;

        // selecionando a próxima posição guardada pelo delimitador, assim como o novo inicio que possui o antigo fim
        indiceDel++;
        inicio = fim + 1;

    }

    // finalmente, retornando a matriz com todas as palavras bonitinhas
    return split;
}

// funções principais
void menu_principal(){

    system("clear");
    cout << "Bem-vindo ao Recomenda Exercicios!";
    cout << "\nPor favor, digite uma opção:";
    cout << "\n1 - Novo Usuario? Cadastre-se agora.\n2 - Ja tem cadastro? Efetue login.\n3 - Sair da aplicacao";
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
        case 3:
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
        cout << "Digite um nome de usuario que voce queira. \nPode usar qualquer simbolo exceto o '*', '/' ou espacos em branco: ";
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
    char **vetorLogin, **vetorLogin2, *buffer; // dois vetores de strings e um vetor de caracteres, normal
    bool achou = false; // flag pra saber se o login foi valido ou nao
    unsigned i;

    cout << "Bem-vindo a tela de login!\nDigite suas informacoes para acessar o Proximo Exercicio!\n";

    // ficará no loop até digitar corretamente ou voltar ao menu inicial
    while (achou == false){

        // lendo as entradas do usuário
        //cout << "Tecle ESC ou DEL e então ENTER para voltar ao menu inicial.\n";

        cout << "Digite o seu nome de usuario: ";
        cin >> usuario.nome;
        cout << "Digite a sua senha: ";
        cin >> usuario.senha;

        // retirando do arquivo de texto os logins e salvando em buffer
        arquivo.open("database/logins.txt", ios::in);
        getline(arquivo, linha); // pegando a linha que é string
        buffer = new char[linha.length()+1]; // alocando dinamicamente um vetor de char com o tamanho da string
        strcpy(buffer, linha.c_str()); // copiando o conteudo da string para o vetor de char

        // separando os logins
        vetorLogin = splitting(buffer, '/', 1); // salvando todos os logins em uma matriz

        i = 0;
        while (vetorLogin[i] != NULL){
            // separando cada nome de usuario e de login
            vetorLogin2 = splitting(vetorLogin[i], '*', 2);
            // comparando se a string do arquivo de texto é o mesmo da entrada do usuario
            if ( (strcmp(vetorLogin2[0], usuario.nome) == 0) && (strcmp(vetorLogin2[1], usuario.senha) == 0) ) achou = true;
            i++;
        }

        // mostrando pro usuario se ele conseguiu logar ou não
        if (achou){
            cout << "LOGADO COM SUCESSO";
            //esperar(1.5);
            // menu_exercicios();
            break;
        }
        else {
            system("clear");
            cout << "Usuario e/ou senha invalidos. Tente novamente.\n";
            esperar(2);
            system("clear");
            continue;
        }

    }

}
