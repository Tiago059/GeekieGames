#include <iostream>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <time.h>
#include "GeekieGames.h";

using namespace std;

void esperar(int segundos){
	clock_t fim;
	fim = clock () + segundos * CLOCKS_PER_SEC;
	while (clock() < fim) {}
}

int buscaCaractere(char *stringue, char busca){
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

void menu_principal(){

    cout << "Bem-vindo ao Recomenda Exercicios!";
    cout << "\nPor favor, digite uma opção:";
    cout << "\n1 - Novo Usuario? Cadastre-se agora.\n2 - Ja tem cadastro? Efetue login.\n3 - Sair da aplicacao";
    cout << "\nDigite: ";

    selecionar_opcao();

}

void selecionar_opcao(){
    char opcao;
    cin >> opcao;

    switch(opcao){
        case '1':
            cadastrar_usuario();
            break;
        case '2':
            login_usuario();
            break;
        case '3':
            exit(0);
            break;
        default:
            system("clear");
            cout << "Entrada invalida.\n";
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
    login usuario;
    //char escape;
    fstream arquivo;
    string linha;

    cout << "Bem-vindo a tela de login!Digite suas informacoes para acessar o Proximo Exercicio!\n";
    while (true){
        //cout << "Aperte ESC para cancelar e retornar ao menu prinicipal.\n"
        cout << "Digite o seu nome de usuario: ";
        cin >> usuario.nome;
        cout << "\nDigite a sua senha: ";
        cin >> usuario.senha;

        // Verificando se o nome e a senha batem com alguma parte do texto
        arquivo.open("database/logins.txt", ios::in);
        getline(arquivo, linha); // pegando a unica linha q tem no arquivo de texto e salvando em "linha"


        break;
    }




}

/* while ( (opcao != 1) || (opcao != 2) ) {

        cout << "\n1 - Novo Usuario? Cadastre-se agora.\n2 - Ja tem cadastro? Efetue login.";
        cout << "\nDigite: ";
        cin >> opcao;

        cout << opcao << endl;
        if ( (opcao != 1) || (opcao != 2) ) {
            cout << "\nPor favor, digite uma opcao valida.";
            system("clear"); // limpa a tela no linux, igual ao system("cls")
        }
        else {
            return opcao;
            break;
        }
    }
*/
// if ( (isalpha(opcao)) || (iscntrl(opcao)) || (ispunct(opcao)) || (isspace(opcao)) ) opcao == 0;
