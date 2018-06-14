#include <iostream>
#include <string.h>

using namespace std;

int main(){
    char stringue[] = {"bundas*rolando*a*mil*por*hora"};
    char **split, *palavra;
    unsigned i, j, inicio = 0, fim, splitCount = 0, del = 0, indiceDel = 0, *delimiters;

    // contando quantas ocorrências do delimitador existem
    for (i = 0;i < strlen(stringue);i++){
        if (stringue[i] == '*') del++;
    }

    // criando a matriz alocada dinamicamente com o total de palavras presentes na string
    // antes que você pense, mas ah são 6 palavras mas o del deu 5 (por exemplo), lembre-se
    // que ao ler o vetor começamos do 0, então na teoria, ir de 0 até 5 é o mesmo que 6.
    split = new char*[del+1];
    for (i = 0;i < del+1;i++){
        split[i] = new char[100]; // são del palavras de 100 caracteres
    }

    //criando o vetor alocado dinamicamente que guardará todas as posições dos delimitadores
    delimiters = new unsigned[del+1];
    delimiters[del] = strlen(stringue); // isso vai ser util para pegar a ultima palavra apos o ultimo delimitador

    //guardando as posições dos delimitadores no vetor
    j = 0;
    for (i = 0;i < strlen(stringue);i++){
        if (stringue[i] == '*'){
            delimiters[j] = i;
            j++;
        }
    }

    // retirando a palavra de intervalos específicos, definidos através das posições
    // dos delimitadores

    while (splitCount < (del+1)){

        fim = delimiters[indiceDel]; // o fim das palavras é definido pelos elementos de delimiters
        palavra = new char[fim - inicio]; // o tamanho da palavra é dado pelo fim da palavra menos o inicio

        j = 0;
        for (i = inicio;i < fim;i++){ // armazenando a palavra entre o intervalo do inicio ao fim
            palavra[j] = stringue[i];
            j++;
        }
        cout << palavra << endl;

        // salvando a palavra na matriz e preparando para a próxima execução do laço
        split[splitCount] = palavra; //
        palavra = " "; // zerando palavra para novos usos nas próximas interações
        splitCount++;

        // selecionando a próxima posição guardada pelo delimitador, assim como o novo inicio que possui o antigo fim
        indiceDel++;
        inicio = fim + 1;

    }

    for (i = 0;i < del+1;i++){
        cout << split[i] << endl;
    }

    /*
    palavra = new char[5];

    for (i = 0;i < 6;i++){
        //cout << stringue[i];
        palavra[j] = stringue[i];
        j++;
    }
    cout << "\n" << palavra << "\n";

    split[0] = palavra;
    palavra = " ";
    j = 0;

    palavra = new char[6];
    for (i = 6+1;i < 14;i++){
        //cout << stringue[i];
        palavra[j] = stringue[i];
        j++;
    }
    cout << "\n" << palavra << "\n";

    split[1] = palavra;

    //cout << split[0];
    for (i = 0;i < 2;i++){
        cout << split[i] << endl;
    }


    for(i = 0;i < 2;i++){
        delete []split[2];
    }
    delete []split;
    delete []palavra;
    */
    return 0;
}
