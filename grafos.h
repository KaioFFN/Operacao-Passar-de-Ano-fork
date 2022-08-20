/**
* @file: grafos.h
* @brief: Protótipos de funções para criação e manipulação de grafos
* @author: cHUPA CU
* @date: 17-08-2022
*/

/*Consts*/
#define True 1
#define False 0

/*Types and structs*/
typedef int bool;

//Armazena os vértices adjacentes
typedef struct aresta_s {
	int vertice;
	int peso;
	struct aresta_s* prox;
}aresta_t; 

//Armazena as tarefas (são os vértices)
typedef struct tarefa_s {
	char* nomeTarefa;
    bool ehPai;
	aresta_t* cabecaArestas; 
}tarefa_t;

//Tipo grafo, usado para armazenar as tarefas e suas ligações
typedef struct grafo_s {
	int countVertices;
	int countArestas;
	tarefa_t* tarefas;
}grafo_t;

//Estrutura usada para o algoritmo de dijkstra
typedef struct caminho_s{
	int* caminho;
	int* peso;
}caminho_t;


/*Functs*/
//Cria um grafo com v vértices e inicializa as adjacências como NULL
grafo_t* criaGrafo(int v);

//Cria uma adjacência, dado um vertice e seu peso
aresta_t* criaAdj(int v, int peso);

//Cria uma aresta conectando os vertices vi e vf com peso peso
bool criaAresta(grafo_t* grafo, int vi, int vf, int peso);

//Imprime os vértices, suas adjacências e pesos
void imprimeGrafo(grafo_t* grafo);