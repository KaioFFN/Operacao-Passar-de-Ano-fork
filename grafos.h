/**
* @file: grafos.h
* @brief: Protótipos de funções para criação e manipulação de grafos
* @author: cHUPA CU
* @date: 17-08-2022
*/

/*Consts*/
#define True 1
#define False 0

#define SUCCESS 0
#define PASSAR_DE_ANO 0

#define BRANCO 0 //Antes da busca
#define CINZA 1 //Vértice visitado
#define PRETO 2 //Todos os vértices adjacentes visitados 

#define INDICE_INICIAL 1
#define INDICE_INEXISTENTE -1
#define MAX_PESO 10 // O máximo que o peso de uma aresta pode ter

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

//Estrutura usada para identificar um caminho possível
typedef struct caminho_s{
	int* vertices; //Armazena os vértices na ordem do caminho, ex: v0 -> v1 -> v2
	int* countVertices; // Quantidade de vértices no caminho
	int peso; //Armazena o peso do caminho
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

// Cria uma matriz de altura alt e largura larg
int** mat_cria(int** matriz, int alt, int larg);

// Insere um número numa matriz. Se não for usar peso, coloca peso=1
void mat_insere(int** matriz, int v1, int v2, bool orientada, int peso);

// Imprime uma matriz
void mat_imprime(int** matriz, int larg, int alt);

// Libera uma matriz quadrada
void mat_libera(int** matriz, int alt);

// Conecta um vértice com todos os outros, com algumas 'falhas de conexão' aleatórias
void completaGrafo(grafo_t* grafo, int countVertices, int indice, int **falhas);

// Faz lAdj_completa com um grafo inteiro
void encheGrafo(grafo_t* grafo, int tamanho, int numFalhas, bool orientada);

//Encontra os menores caminhos possíveis das tarefas até passar de ano
void encontraMenoresCaminhos(grafo_t* grafo);

//Inicializa os vetores para o algoritmo de Dijkstra
void inicializaDijkstra(grafo_t* grafo, int* distancia, int* precedencia, bool* aberto, int s);

//Função que realiza o relaxamento de um vértice
void relaxaVertice(grafo_t* grafo, int* distancia, int* precedencia, int u, int v);

//Verifica se existe um vértice aberto no grafo
bool existeAberto(grafo_t* grafo, int * aberto);

//Retorna o vértice aberto de menor distância
int verticeMenorDistancia(grafo_t* grafo, int * aberto, int* distancia);

/*
* Executa o algoritmo de Dijkstra,
* retorna um vetor int* com as distancias dos vértices em relação ao vértice inicial s
*/
int* dijkstra(grafo_t* grafo, int s);
