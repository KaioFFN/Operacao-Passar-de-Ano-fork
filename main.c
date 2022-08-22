/**
* @file: main
* @brief: Arquivo principal trabalho de grafos
* @author: Grupo
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

//Imprime os menores caminhos até o fim do ano
void imprimeMenoresCaminhos(grafo_t* grafo){
    //Encontra os menores caminhos
    caminho_t** vetCaminhos = encontraMenoresCaminhos(grafo);

    int i;

    printf("|----------------------------------------------------------------------------------------------------|\n");
    printf("|                               Menores Caminhos ate Passar de Ano                                   |\n");
    printf("|----------------------------------------------------------------------------------------------------|\n");

	if(vetCaminhos[0] == NULL)
	{
		printf("Nenhum caminho possivel -> Voce vai bombar!\n\n");
	}
	else
	{
		for(i=0;vetCaminhos[i] != NULL; i++)
		{
			printf("--------------------------------------------------------\n");
			imprimeCaminho(vetCaminhos[i]);
			printf("--------------------------------------------------------\n");
		}
    
	}

    printf("\n\n");

}

int main (int argc, char ** argv){
	bool tmp;
	grafo_t* grafo = criaGrafo(TAM_GRAFO); // Faz um grafo de tamanho TAM_GRAFO+1

	srand(time(NULL));

	encheGrafo(grafo, TAM_GRAFO+1, NUM_FALHAS, True);
/*
	grafo_t* grafo = criaGrafo(5);

	(void)criaAresta(grafo, 1, 2, 2);

	(void)criaAresta(grafo, 2, 3, 8);
	(void)criaAresta(grafo, 2, 4, 3);

	(void)criaAresta(grafo, 4, 0, 1);

	(void)criaAresta(grafo, 3, 0, 1);

*/
	imprimeGrafo(grafo);
	printf("\n\n");

	imprimeMenoresCaminhos(grafo);

	return SUCCESS;

	// FALTA FAZER: Checar se o número de conexões com o vértice 0 é apropriado (não pode ter um monte de vértice ligando nele, mas não pode ser impossível chegar nele)
}
