#include "ajuda.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
/*

Aqui fica a função que exibe a ajuda para o usuário. É só isso mesmo.

Mesmo que esse arquivo não esteja tão poluído assim, a descrição dessa função
se encontra no arquivo 'help.h', apenas para manter o padrão.

*/

void exibirAjuda(){
    system("clear");
    ifstream arquivo;
    string linha;

    // Exibindo o arquivo de ajuda para o usuário. Nada demais.
    arquivo.open("database/help.txt");
    // Lendo o arquivo de texto ate o fim dele
    while (!arquivo.eof()){
        getline(arquivo, linha);
        cout << linha << endl;
    }
    arquivo.close();
    system("read -p '\nAperte qualquer tecla para retornar:' var"); // para o linux. no windows, use system("pause")
}
