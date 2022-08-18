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
#define True 1
#define False 0

#define BRANCO 0 //Antes da busca
#define CINZA 1 //Vértice visitado
#define PRETO 2 //Todos os vértices adjacentes visitados 

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
	const char* nome_tarefa
	adjacencia_t* head; 
}tarefa_t;

//Tipo grafo, usado para armazenar as tarefas e suas ligações
typedef struct grafo_s {
	int count_vertices;
	int count_arestas;
	vertice_t* vertices;
}grafo_t;



