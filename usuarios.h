/*

Aqui ficam todos os headers referentes as funções relacionadas
diretamente com o usuário - login de usuários e cadastro de novos.

*/

/* Tem como base a struct de usuario, e então cadastra um usuário com nome e senha
em um arquivo de texto chamado logins.txt. */
void cadastrar_usuario();

/* Recupera do arquivo de texto logins.txt, e com base nas entradas digitadas
pelo usuário, checa se o mesmo existe no arquivo de texto e efetua o login,
criando uma struct de usuario, e então chama o menu de exercícios passando
como argumento aquela struct. */
void login_usuario();
