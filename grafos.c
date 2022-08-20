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
#include <time.h>
#include "grafos.h"

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
/* ======== Funções de matriz ======== */
/*--------------------------------------------------------------------------*/

// Cria uma matriz de altura alt e largura larg
int** mat_cria(int** matriz, int alt, int larg) 
{
	// Alocando
    matriz = (int**) malloc (sizeof(int*) * alt); // A matriz precisa ser declarada antes da função, mas não alocada
    for (int i=0; i<larg; i++) {
        matriz[i] = (int*) malloc (sizeof(int) * larg);
    }

	// Inicializando todos os pontos da matriz como 0
    for (int i=0; i<alt; i++) {
        for (int j=0; j<larg; j++) {
            matriz[i][j] = 0;
        }
    }

    return matriz;
}

/*--------------------------------------------------------------------------*/

// Insere um número numa matriz. Se não for usar peso, coloca peso=1
void mat_insere(int** matriz, int v1, int v2, bool orientada, int peso) 
{
    matriz[v1][v2] = peso;
    if(!orientada) {
        matriz[v2][v1] = peso;
    }
}

/*--------------------------------------------------------------------------*/

// Imprime uma matriz
void mat_imprime(int** matriz, int larg, int alt) 
{
    printf("    ");
    for (int i=0; i<larg; i++) { // Imprimir números em cima
        printf("%i  ", i);
    }
    printf("\n  ");
    for (int i=0; i<larg; i++) { // Imprimir margem em cima
        printf("---");
    }
    printf("\n");

    for(int i=0; i<alt; i++) {
        printf("%i | ", i); // Imprimir margem do lado

        for(int j=0; j<larg; j++) { // Imprimir números da matriz
            printf("%i  ", matriz[i][j]);
        }
        printf("\n");
    }
}

/*--------------------------------------------------------------------------*/

// Libera uma matriz quadrada
void mat_libera(int** matriz, int alt) 
{ 
    for(int i=0; i<alt; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

/*--------------------------------------------------------------------------*/
/* ======== Funções de encher grafo ======== */
/*--------------------------------------------------------------------------*/

// Conecta um vértice com todos os outros, com algumas 'falhas de conexão' aleatórias
void completaGrafo(grafo_t* grafo, int countVertices, int indice, int **falhas) 
{
    for(int i=0; i<countVertices; i++) {
        if (!falhas[indice][i] && i != indice) { // Se um dos vértices tem o outro como falha, não cria a aresta. Também não cria arestas que ligam um vértice a si mesmo
            criaAresta (grafo, indice, i, (rand() % MAX_PESO)+1); // O peso da aresta é determinado aleatoriamente, no mínimo 1 e no máximo MAX_PESO
        }													  	  // rand() % N retorna um número aleatório de 0 a N
    }
}

/*--------------------------------------------------------------------------*/

// Faz lAdj_completa com um grafo inteiro
void encheGrafo(grafo_t* grafo, int tamanho, int numFalhas, bool orientada) 
{ 
    int **matFalhas;
    matFalhas = mat_cria (matFalhas, tamanho, tamanho);

    for (int i=0; i<tamanho; i++) { // Coloca um número de falhas igual a numFalhas pra cada vértice do grafo
        for (int j=0; j<numFalhas; j++) {
            mat_insere(matFalhas, i, rand() % tamanho, orientada, True); // Determina as falhas de conexão aleatoriamente e guarda elas numa matriz.
        }																 // rand() % N retorna um número aleatório de 0 a N			 
    }
    for (int i=0; i<tamanho; i++) {
        completaGrafo(grafo, tamanho, i, matFalhas);
    }
    mat_imprime (matFalhas, tamanho, tamanho); // Imprime a matriz de falhas pra motivos de debug

    mat_libera (matFalhas, tamanho); // Libera a matriz de falhas
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
