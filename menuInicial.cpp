#include "menuInicial.h"
#include "estruturas.h"
#include "exercicios.h"
#include "suporte.h"
#include "usuarios.h"
#include "ajuda.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

/* Aqui ficam as funções que exibem o menu prinicipal
e seleciona uma opção do menu prinicipal, e então
direcionam ela para outra função (login, exercicio).

As descrições de cada função se encontram no
arquivo 'menuInicial.h' para não poluir visualmente (mais do
que já está poluído) este arquivo.

*/


void menu_principal(){

    system("clear");
    cout << "Bem-vindo ao Recomenda Exercicios!";
    cout << "\nPor favor, digite uma opção:";
    cout << "\n1 - Novo Usuario? Cadastre-se agora.\n2 - Ja tem cadastro? Efetue login.\n";
    cout << "3 - Cadastrar Exercício (Adminstrador)\n4 - Ajuda\n0 - Sair da Aplicacao\n";
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
            menu_administrador();
            break;
        case 4:
            exibirAjuda();
            menu_principal();
            break;
        case 0:
            exit(0);
            break;
        default:
            system("clear");
            cout << "Entrada invalida. Tente novamente.\n";
            esperar(1.5);
            system("clear");
            menu_principal();
    }
}

void menu_administrador(){
    system("clear");
    login admin;
    char opcao;
    cout << "Bem-vindo a tela do administrador!";
    while (true){
        cout << "\nDigite seu login de administrador. ";
        cout << "\nUsuario: ";
        cin.ignore();
        getline(cin, admin.nomeString);
        admin.nome = admin.nomeString.c_str();

        cout << "Senha: ";
        getline(cin, admin.nomeString);
        admin.nome = admin.senhaString.c_str();

        //cin >> admin.senha;

        if ( (strcmp(admin.nome, "admin") == 0) && (strcmp(admin.senha, "admin") == 0) ) cadastrar_exercicio();
        else {
            cout << "\nUsuario e/ou senha invalidos.\n";
            // Um swtichzinho só para facilitar o erro do nosso querido usuário
            cout << "Tentar novamente?(S para sim, qualquer outra tecla para voltar ao menu principal)?\nDigite: ";
            cin >> opcao;
            switch (opcao){
                case 'S':
                case 's':
                    system("clear");
                    menu_administrador();
                    break;
                default:
                    system("clear");
                    menu_principal();
            }
        }

    }

}

