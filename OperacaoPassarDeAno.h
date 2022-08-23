/**
* @file: OperacaoPassarDeAno.h
* @brief: Protótipos de funções para criação e manipulação de grafos
* @author: Grupo
* @date: 17-08-2022
*/

/*Includes*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

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
#define MIN_PAIS 3
#define IMPOSSIVEL (INT32_MAX/2)

#define LIMITE_DE_CAMINHOS 100

#define TAM_GRAFO 9
#define NUM_FALHAS 9 // É bom fazer NUM_FALHAS ser bem próximo de TAM_GRAFO, pra ter um núnero bom de vértices pais

#define NUM_MATERIAS 5
#define MAX_PALAVRA 16


/*Tipos e structs*/
typedef int bool;

//Armazena os vértices adjacentes
typedef struct aresta_s {
	int vertice;
	int peso;
	struct aresta_s* prox;
}aresta_t; 

//Armazena as tarefas (são os vértices)
typedef struct tarefa_s {
	char nome[MAX_PALAVRA*2];
    bool ehPai;
	aresta_t* cabecaArestas; 
}tarefa_t;

//Tipo grafo, usado para armazenar as tarefas e suas ligações
typedef struct grafo_s {
	int countVertices;
	int countArestas;
	int materia;
	tarefa_t* tarefas;
}grafo_t;

//Estrutura usada para identificar um caminho possível
typedef struct caminho_s{
	int* vertices; // Armazena os vértices na ordem do caminho, ex: v0 -> v1 -> v2
	int countVertices; // Quantidade de vértices no caminho
	int peso; // Armazena o peso do caminho
}caminho_t;


/*Declarando variáveis estáticas*/

// Criando a matriz que guarda os nomes de atividades
static char atividades[NUM_MATERIAS][MAX_PALAVRA] = {"Formulario", "Questionario", "Resumo", "Redacao", "Prova"};

// Criando a matriz que guarda os nomes das submatérias
static char subMaterias[NUM_MATERIAS][NUM_MATERIAS][MAX_PALAVRA] = {
	{"gramatica", "romantismo", "ortografia", "prod. de texto", "literatura"}, // Port
	{"matrizes", "sistemas", "algebra", "geometria", "probabilidade"}, // Mat
	{"eletrostatica", "mecanica", "dinamica", "hidrostatica", "magnetismo"}, // Fis
	{"grafos", "arvores", "hash", "ordenacao", "OOP"}, // AEDS
	{"memoria", "processamento", "controle", "IO", "ling. maquina"} // OCS
};


/*Funcoes*/
// Um regex que limpa a tela, muitas vezes mais rápido que o system("clear") e funciona em qualquer plataforma
void limpaTerm();

//Retorna True se o nome de tarefas[indice] for igual ao nome de alguma outra tarefa em 'tarefas'.
bool comparaNomes (tarefa_t *tarefas, int indice);

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

// Checa se uma coluna está cheia
bool colunaCheia(int** matriz, int tamanho, int coluna);

// Transforma todos os valores de uma coluna em 1
void encheColuna(int** matriz, int tamanho, int coluna);

// Conta quantos vértices-pai existem num grafo e ajusta o número se for pequeno demais
int consertaPais(int** matriz, int tamanho);

// Conecta um vértice com todos os outros, com algumas 'falhas de conexão' aleatórias
void completaGrafo(grafo_t* grafo, int countVertices, int indice, int **falhas);

// Faz lAdj_completa com um grafo inteiro
void encheGrafo(grafo_t* grafo, int tamanho, int numFalhas, bool orientada);

// Encontra os menores caminhos para passar de ano, retorna um caminho_t**, com caminhos válidos até o primeiro índice com valor NULL
caminho_t** encontraMenoresCaminhos(grafo_t* grafo);

//Inicializa os vetores para o algoritmo de Dijkstra
void inicializaDijkstra(grafo_t* grafo, int* distancia, int* precedencia, bool* aberto, int s);

//Função que realiza o relaxamento de um vértice
void relaxaVertice(grafo_t* grafo, int* distancia, int* precedencia, int u, int v);

//Verifica se existe um vértice aberto no grafo
bool existeAberto(grafo_t* grafo, int * aberto);

//Retorna o vértice aberto de menor distância
int verticeMenorDistancia(grafo_t* grafo, int * aberto, int* distancia);

//A partir dos dados da função dijkstra, essa função extrai o caminho, peso e quantidade de vértices do vértice v até PASSAR_DE_ANO
caminho_t* extraiCaminho(grafo_t* grafo, int* distancia, int* precedencia, int v, int s);

/*
* Executa o algoritmo de Dijkstra,
* retorna um vetor int* com as distancias dos vértices em relação ao vértice inicial s
*/
caminho_t* dijkstra(grafo_t* grafo, int s);

//Imprime o caminho e seus atributos
void imprimeCaminho(caminho_t* caminho, grafo_t* grafo);

//Imprime os menores caminhos até o fim do ano
void imprimeMenoresCaminhos(grafo_t* grafo);

//Imprime um menu e retorna a chave inserida
int imprimeMenu(int chave);