/**
* @file: grafos.c
* @brief: Funções para criação e manipulação de grafos
* @author: cHUPA CU
* @date: 17-08-2022
*/

/*Includes*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "grafos.h"

/*Consts*/
#define SUCCESS 0
#define PASSAR_DE_ANO 0


#define BRANCO 0 //Antes da busca
#define CINZA 1 //Vértice visitado
#define PRETO 2 //Todos os vértices adjacentes visitados 

#define INDICE_INICIAL 1

/* 
O índice 0 será reservado para o "Fim de Ano com Sucesso"
Portanto, os vértices (tarefas) são contadas a partir do índice 1*/

/*Functs*/
//Cria um grafo com v vértices e inicializa as adjacências como NULL
grafo_t* criaGrafo(int v) {
	int i;

	grafo_t* grafo= (grafo_t*)malloc(sizeof(grafo_t)); //Aloca espaço para a estrutura grafo

	v++; // O +1 é devido ao índice 0 estar reservado ao Fim de Ano

	grafo->countVertices = v; //Atualiza o número de vértices
 	grafo->countArestas = 0; //Atualiza o número de arestas

	//Alocação dos vértices e das adjacências
	grafo->tarefas = (tarefa_t*)malloc(v * sizeof(tarefa_t)); 
	
	for (i = 0; i < v; i++)
	{
		grafo->tarefas[i].cabecaArestas = NULL;
		grafo->tarefas[i].ehPai = True;
	}


	return grafo;
}

/*--------------------------------------------------------------------------*/

//Cria uma adjacência, dado um vertice e seu peso
aresta_t* criaAdj(int v, int peso)
{
	aresta_t* temp = (aresta_t*)malloc(sizeof(aresta_t)); //Aloca o espaço para um nó
	temp->vertice = v; //Vértice alvo da adjacência
	temp->peso = peso; //Peso da aresta
	temp->prox = NULL;

	return temp; //Retorna o endereço da adjacência
}

/*--------------------------------------------------------------------------*/

//Cria uma aresta conectando os vertices vi e vf com peso peso
bool criaAresta(grafo_t* grafo, int vi, int vf, int peso)
{
	if (!grafo) return False; //Checa a existência do grafo

	//Verifica se os valores não são negativos ou maiores que o número de vértice do grafo
	if ((vf < 0) || (vf >= grafo->countVertices || (vi<INDICE_INICIAL))) return False;

	aresta_t* novo = criaAdj(vf, peso);

	//Altera os valores no vértice inicial
	novo->prox = grafo->tarefas[vi].cabecaArestas; // O campo prox da aresta recebe a cabeça da lista
	grafo->tarefas[vi].cabecaArestas = novo;
	grafo->countArestas++;

	//Altera o campo ehPai no vértice final
	grafo->tarefas[vf].ehPai = False;

	return True;
}

/*--------------------------------------------------------------------------*/

//Imprime os vértices, suas adjacências e pesos
void imprimeGrafo(grafo_t* grafo) 
{
	int i;
	printf("Vertices: %d. Arestas: %d. \n", grafo->countVertices, grafo->countArestas); //imprime numero de vértice e arestas

	for (i = 0; i < grafo->countVertices; i++)
	{
		printf("v%d: ", i); //Imprimo em qual aresta estou
		aresta_t* ad = grafo->tarefas[i].cabecaArestas; //Chama a cabeça da lista de adjacência
		while (ad != NULL)
		{
			printf("v%d(%d) ", ad->vertice, ad->peso); //Imprime a adjacência e seu peso
			ad = ad->prox;
		}
		printf("\n");
	}

}

/*--------------------------------------------------------------------------*/




















//Encontra os menores caminhos possíveis das tarefas até passar de ano
void encontraMenoresCaminhos(grafo_t* grafo)
{
    int i;
	static uint32_t tamMenorCaminho = UINT32_MAX;
	

	for(i = INDICE_INICIAL; i<grafo->countVertices;i++)
	{
		//Encontra as tarefas pai, ou seja, que não possuem nenhuma dependência pois ninguém aponta para elas
		if(grafo->tarefas[i].ehPai == True)
		{
			printf("PAI -> v%dn\n", i);
		}
	}
}

/*--------------------------------------------------------------------------*/
