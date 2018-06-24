// structs
typedef struct _login_ {
    char nome[100], senha[100];
} login;


// funções
// funções que ajudam outras funções
void esperar(int segundos);
int buscaCaractere(char *stringue, char *busca);
char **splitting(char *stringue, char delimiter);

// funções que exibem menus
void menu_principal();
void selecionar_opcao();
void cadastrar_usuario();
void login_usuario();

