/*

Aqui ficam todos os headers referentes as funções do menu inicial.

*/

/* Exibe uma telinha mostrando as opções, e então chama a função
selecionar_opcao() para selecionar a opção. */
void menu_principal();

/* Pede para o usuário escolher uma opção, e então, a partir
da escolha do usuário, ele é direcionado para outra função.
Caso algo dê errado, ele chama a função menu_principal(), de
modo que fique num "loop indireto" até que o usuário escolha
uma opção válida. */
void selecionar_opcao();
