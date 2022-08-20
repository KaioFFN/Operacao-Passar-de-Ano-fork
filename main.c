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
#include "grafos.h"


/*Consts*/
#define SUCCESS 0


/*Functs*/

int main (int argc, char ** argv){

	bool tmp;
	grafo_t* grafo = criaGrafo(5);

	tmp = criaAresta(grafo, 1, 3, 2);
	tmp = criaAresta(grafo, 3, 2, 2);
	tmp = criaAresta(grafo, 2, 4, 2);
	tmp = criaAresta(grafo, 4, 0, 2);

	imprimeGrafo(grafo);


	return SUCCESS;
}