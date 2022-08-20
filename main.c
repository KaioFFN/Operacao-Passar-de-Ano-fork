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

void imprimeDistancias(grafo_t* grafo, int* distancia){

	int i;

	for(i = 0; i < grafo->countVertices; i++)
	{
		printf("[%d] -> %d\n", i, distancia[i]);
	}
}



int main (int argc, char ** argv){
	bool tmp;
	grafo_t* grafo = criaGrafo(TAM_GRAFO); // Faz um grafo de tamanho TAM_GRAFO+1

	srand(time(NULL));

	encheGrafo(grafo, TAM_GRAFO+1, NUM_FALHAS, True);

	//grafo_t* grafo = criaGrafo(8);

/*
	(void)criaAresta(grafo, 1, 2, 2);
	(void)criaAresta(grafo, 1, 4, 1);

	(void)criaAresta(grafo, 2, 3, 8);

	(void)criaAresta(grafo, 4, 1, 5);
	(void)criaAresta(grafo, 4, 2, 9);
	(void)criaAresta(grafo, 4, 5, 5);
	(void)criaAresta(grafo, 4, 6, 1);

	(void)criaAresta(grafo, 5, 2, 1);
	(void)criaAresta(grafo, 5, 3, 5);

	(void)criaAresta(grafo, 6, 5, 3);
	(void)criaAresta(grafo, 6, 7, 1);

	(void)criaAresta(grafo, 7, 5, 1);
*/

	imprimeGrafo(grafo);
	printf("\n\n");

	int* distancia = dijkstra(grafo, 1);
	imprimeDistancias(grafo, distancia);

	return SUCCESS;

	// FALTA FAZER: Checar se o número de conexões com o vértice 0 é apropriado (não pode ter um monte de vértice ligando nele, mas não pode ser impossível chegar nele)
}
