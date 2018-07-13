/*

Aqui ficam todos os headers referentes as funções de suporte.

*/

/* Faz o programa ficar em pausa por uma quantidade X de segundos e não fazer
nada durante este tempo. Um delay básico. */
void esperar(int segundos);

/* "Converte" um valor booleano para um const char. Ou seja, imprime
"true" se o valor passado é true, por exemplo. */
const char *BoolToString(bool b);

/* Realiza uma busca de um caractere específico em uma string. Retorna 1 se encontrado;0 se não. */
int buscaCaractere(char *stringue, char busca);

/* Esta função divide uma string quando encontra um delimitador específico, a partir de um índice
de procura (se for 0 por exemplo, a procura é feita desde o começo da string) salva numa outra
string e então retorna essa string. Basicamente, você passa o próprio índice de procura como
referência e chama a função num while para que você consiga todos os splits da função, caso precise. */
char *split(char *stringue, char delimitador, unsigned *posicao);

/* Esta função gera um número aleatório entre um intervalo especificado. */
int aleatorio(int min, int max);

