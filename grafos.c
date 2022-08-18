/**
* @file: grafos.c
* @brief: Funções para criação e manipulação de grafos
* @author: cHUPA CU
* @date: 17-08-2022
*/

/*Includes*/
#include <stdio.h>
#include <stdlib.h>

/*Consts*/
#define SUCCESS 0
#define PASSAR_DE_ANO 0
#define True 1
#define False 0

#define BRANCO 0 //Antes da busca
#define CINZA 1 //Vértice visitado
#define PRETO 2 //Todos os vértices adjacentes visitados 

#define INDICE_INICIAL 1

/*Types and structs*/
typedef int bool;

//Armazena os vértices adjacentes
typedef struct adjacencia_s {
	int vertice;
	int peso;
	struct adjacencia_s* prox;
}adjacencia_t; 

//Armazena as tarefas (são os vértices)
typedef struct tarefa_s {
	const char* nomeTarefa;
    bool ehPai;
	adjacencia_t* head; 
}tarefa_t;

//Tipo grafo, usado para armazenar as tarefas e suas ligações
typedef struct grafo_s {
	int countVertices;
	int countArestas;
	tarefa_t* vertices;
}grafo_t;


/*O índice 0 será reservado para o "Fim de Ano com Sucesso"*/


/*Functs*/

//Cria um grafo com v vértices e inicializa as adjacências como NULL
grafo_t* criaGrafo(int v) {
	int i;

	grafo_t* grafo= (grafo_t*)malloc(sizeof(grafo_t)); //Aloca espaço para a estrutura grafo

	v++; // O +1 é devido ao índice 0 estar reservado ao Fim de Ano

	grafo->countVertices = v; //Atualiza o número de vértices
 	grafo->countArestas = 0; //Atualiza o número de arestas

	//Alocação dos vértices e das adjacências
	grafo->vertices = (tarefa_t*)malloc(v * sizeof(tarefa_t)); 
	
	for (i = 0; i < v; i++)
		grafo->vertices[i].head = NULL;
		grafo->vertices[i].ehPai = True;

	return grafo;
}

//Cria uma adjacência, dado um vertice e seu peso
adjacencia_t* criaAdj(int v, int peso)
{
	adjacencia_t* temp = (adjacencia_t*)malloc(sizeof(adjacencia_t)); //Aloca o espaço para um nó
	temp->vertice = v; //Vértice alvo da adjacência
	temp->peso = peso; //Peso da aresta
	temp->prox = NULL;

	return temp; //Retorna o endereço da adjacência
}

//Cria uma aresta conectando os vertices vi e vf com peso peso
bool criaAresta(grafo_t* grafo, int vi, int vf, int peso)
{
	if (!grafo) return False; //Checa a existência do grafo

	//Verifica se os valores não são negativos ou maiores que o número de vértice do grafo
	if ((vf < 0) || (vf >= grafo->countVertices || (vi<INDICE_INICIAL))) return False;

	adjacencia_t* novo = criaAdj(vf, peso);

	//Altera os valores no vértice inicial
	novo->prox = grafo->vertices[vi].head; // O campo prox da adjacencia recebe a cabeça da lista
	grafo->vertices[vi].head = novo;
	grafo->countArestas++;

	//Altera o campo ehPai no vértice final
	grafo->vertices[vf].ehPai = False;

	return True;
}


//Imprime os vértices, suas adjacências e pesos
void imprimeGrafo(grafo_t* grafo) 
{
	int i;
	printf("Vertices: %d. Arestas: %d. \n", grafo->countVertices, grafo->countArestas); //imprime numero de vértice e arestas

	for (i = INDICE_INICIAL; i <= grafo->countVertices; i++)
	{
		printf("v%d: ", i); //Imprimo em qual aresta estou
		adjacencia_t* ad = grafo->vertices[i].head; //Chama a cabeça da lista de adjacência
		while (ad != NULL)
		{
			printf("v%d(%d) ", ad->vertice, ad->peso); //Imprime a adjacência e seu peso
			ad = ad->prox;
		}
		printf("\n");
	}

}

//Encontra os menores caminhos possíveis das tarefas até passar de ano
void encontraMenoresCaminhos(grafo_t* grafo)
{
    int i;

	for(i = INDICE_INICIAL; i<=grafo->countVertices;i++)
	{
		if(grafo->vertices[i].ehPai == True)
		{
			printf("PAI -> v%dn\n", i);
		}
	}
}


int main (int argc, char ** agv){

	bool tmp;
	grafo_t* grafo = criaGrafo(5);

	tmp = criaAresta(grafo, 1, 3, 2);
	tmp = criaAresta(grafo, 3, 2, 2);
	tmp = criaAresta(grafo, 2, 4, 2);
	tmp = criaAresta(grafo, 4, 0, 2);

	imprimeGrafo(grafo);

	encontraMenoresCaminhos(grafo);

	return SUCCESS;
}