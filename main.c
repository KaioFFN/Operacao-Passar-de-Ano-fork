/**
* @file: main
* @brief: Arquivo principal trabalho de grafos
* @author: Grupo
* @date: 19-08-2022
*/

/*Includes*/
#include "OperacaoPassarDeAno.h"

/*Consts*/
#define SUCCESS 0

/*Functs*/



int main (int argc, char ** argv){
	bool tmp;
	
	srand(time(NULL));

	int chave = 0;

	do{
		chave = imprimeMenu(chave);
	}while (chave!=0);

	
	return SUCCESS;

	// FALTA FAZER: Checar se o número de conexões com o vértice 0 é apropriado (não pode ter um monte de vértice ligando nele, mas não pode ser impossível chegar nele)
}
