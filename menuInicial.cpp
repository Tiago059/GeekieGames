#include "menuInicial.h"
#include "suporte.h"
#include "usuarios.h"
#include "ajuda.h"
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
    cout << "3 - Ajuda\n0 - Sair da Aplicacao\n";
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
            exibirAjuda();
            menu_principal();
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
