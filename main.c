/**
* @file: main
* @brief: Arquivo principal trabalho de grafos
* @author: Grupo
* @date: 19-08-2022
*/

/*Includes*/
#include "OperacaoPassarDeAno.h"

/*Functs*/

int main (int argc, char ** argv){
	// Declarações
	int chave = 0;

	// Fazendo a seed pro rand()
	srand(time(NULL));

	// Loop de menu
	do {
		chave = imprimeMenu(chave);
	} while (chave!=0);

	return EXIT_SUCCESS;
}
/**
* Feito Por
* Kaio Fernandes Ferreira Nunes 
* Eduardo Santos Birchal
* Rafael Eustaquio Pinto 
* Gabrielle Maia De Andrade Souza
/