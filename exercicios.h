/*

Aqui ficam todos os headers referentes as funções relacionadas
diretamente com os exercícios - criação, acesso, e outras
funções secundárias relacionadas.

*/

/* Chama a tela de cadastro de exercicio, cujo somente o administrador poderá
ter acesso a ela. Ela permite cadastrar exercícios com toda sua glória,
contendo título, descrição e etc. Todos os exercícios de uma categoria
específica X e dificuldade específica Y são guardados em um único arquivo de texto,
com os nomes das pastas e arquivos referentes as categorias e dificuldade.
Exemplo: Todos os exercícios da categoria "Sintaxe" de dificuldade "Fácil" estão
em um arquivo de texto chamado "Sintaxe-Facil.txt" e no caminho "database/exercicios/Sintaxe". */
void cadastrar_exercicio();

/* Esta tela é direcionada automaticamente para um usuário assim que ele efetua o login no sistema.
Ele então pede para que uma categoria e dificuldade sejam escolhidas, e então lê o arquivo
de exercícios correspodente e começa a exibir exercícios aleatórios para o usuário. Permite também
ver um exercício anterior, marcar um exercício como resolvida de modo que não apareça mais, e desfazer
as visualizações, voltando a exibir os exercícios que ele havia marcado para não serem exibidos. */
void menu_exercicios(login login);

/* Função de suporte. Ela lista 9 categorias, pede para o usuário escolher uma delas, e então
devolve uma string contendo o nome da categoria. */
const char *selecionar_categoria();

/* Função de suporte. Elas existem basicamente para não poluir as funções principais. Análoga
a anterior, esta aqui lista 3 dificuldades, pede para o usuário escolher uma delas, e então
devolve uma string contendo a doficuldade. */
const char *selecionar_dificuldade();

/* Funçao secundária. Ela exibe os exercícios aleatoriamente para o usuário, após um número
de exercício ter sido gerado aleatoriamente, e após ter criado um vetor de structs contendo os exercícios.
Permite também fazer que exercícios específicos não apareçam mais para um usuário específico. */
void exibir_exercicios(int numero, int anterior, int quantExercicios, exercicio *exercicios, login login);
