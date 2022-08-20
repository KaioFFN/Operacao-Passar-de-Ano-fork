/**
* @file: main
* @brief: Arquivo principal trabalho de grafos
* @author: cHUPA CU
* @date: 19-08-2022
*/

/*Includes*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "grafos.h"


/*Consts*/
#define SUCCESS 0

#define TAM_GRAFO 9
#define NUM_FALHAS 9 // É bom fazer NUM_FALHAS ser bem próximo de TAM_GRAFO, pra ter um núnero bom de vértices pais


/*Functs*/

int main (int argc, char ** argv){
	bool tmp;
	grafo_t* grafo = criaGrafo(TAM_GRAFO); // Faz um grafo de tamanho TAM_GRAFO+1

	srand(time(NULL));

	encheGrafo(grafo, TAM_GRAFO+1, NUM_FALHAS, True);

	imprimeGrafo(grafo);

	encontraMenoresCaminhos(grafo);
	return SUCCESS;

	// FALTA FAZER: Checar se o número de conexões com o vértice 0 é apropriado (não pode ter um monte de vértice ligando nele, mas não pode ser impossível chegar nele)
}
