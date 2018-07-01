/*

    Structs utilizadas pelo programa

*/
typedef struct _login_ {
    char nome[100], senha[100];
} login;

typedef struct _exercicio_ {
    char *titulo, *descricao, *categoria, *dificuldade; // dados do exercicio
    char *caminho; // dados de em qual pasta serão salvos o arquivo
    bool resolvido;
    //const char *categoria;
} exercicio;

/*

    Funções utilizadas pelo programa

*/

// Funções de suporte para outras funções
void esperar(int segundos);
int buscaCaractere(char *stringue, char *busca);
char *split(char *stringue, char delimitador, unsigned *posicao);

// Função que exibe o menu principal e seleciona uma opção
void menu_principal();
void selecionar_opcao();

// Cadastro de usuários e login no sistema
void cadastrar_usuario();
void login_usuario();

// Cadastro de exercícios
void cadastrar_exercicio();
const char *selecionar_categoria();
char *selecionar_dificuldade();

