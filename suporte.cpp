#include "suporte.h"
#include <string.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

/*

Aqui ficam as funções que servem de suporte para
as outras funções. São funções secundárias, mas
as funções principais não funcionariam sem estas aqui.

As descrições de cada função se encontram no
arquivo 'suporte.h' para não poluir visualmente (mais do
que já está poluído) este arquivo.

*/

void esperar(int segundos){
	clock_t fim;
	fim = clock () + segundos * CLOCKS_PER_SEC;
	while (clock() < fim) {}
}

const char *BoolToString(bool b) {
   if (b) return "true";
   else return "false";
}

int buscaCaractere(char *stringue, char busca){
    bool achou = false;
    unsigned i;

    for (i = 0;i < strlen(stringue);i++){
        if (stringue[i] == busca) {
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

int aleatorio(int min, int max){
    srand(time(NULL));
    return (rand()% (max - min + 1) + min);
}
