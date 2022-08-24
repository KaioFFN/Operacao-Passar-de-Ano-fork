/**
* @file: grafos.c
* @brief: Funções para criação e manipulação de grafos
* @author: Grupo
* @date: 17-08-2022
*/

/*Includes*/
#include "OperacaoPassarDeAno.h"

/* 
O índice 0 será reservado para o "Fim de Ano com Sucesso"
Portanto, os vértices (tarefas) são contadas a partir do índice 1*/

/*Qualquer valor maior que INT32_MAX/2 = 1073741823 será considerado INFINITO/IMPOSSÍVEL*/

/*Functs*/
//Retorna True se o nome de tarefas[indice] for igual ao nome de alguma outra tarefa em 'tarefas'.
bool comparaNomes (tarefa_t *tarefas, int indice) {
	for (int i=0; i<indice; i++) {
		if (strcmp(tarefas[indice].nome, tarefas[i].nome) == 0) return True;
	}

	return False;
}

//Cria um grafo com v vértices e inicializa as adjacências como NULL
grafo_t* criaGrafo(int v) {
	int i;

	grafo_t* grafo= (grafo_t*)malloc(sizeof(grafo_t)); //Aloca espaço para a estrutura grafo

	v++; // O +1 é devido ao índice 0 estar reservado ao Fim de Ano

	grafo->countVertices = v; //Atualiza o número de vértices
 	grafo->countArestas = 0; //Atualiza o número de arestas
	grafo->materia = rand()%NUM_MATERIAS;

	//Alocação dos vértices e das adjacências
	grafo->tarefas = (tarefa_t*)malloc(v * sizeof(tarefa_t)); 
	
	for (i = 0; i < v; i++)
	{
		grafo->tarefas[i].cabecaArestas = NULL;
		grafo->tarefas[i].ehPai = True;

		do {
			strcpy(grafo->tarefas[i].nome, atividades[rand()%NUM_MATERIAS]);
			strcat(grafo->tarefas[i].nome, " de ");
			strcat(grafo->tarefas[i].nome, subMaterias[grafo->materia][rand()%NUM_MATERIAS]);
		} while (comparaNomes(grafo->tarefas, i)); // Esse while randomiza o nome se ele for igual ao nome de outra tarefa, até ele não ser mais.
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
	printf("\033[1mAtividades (vertices):\033[0m %d.\n\033[1mDependencias (arestas):\033[0m %d. \n\n", grafo->countVertices, grafo->countArestas); //imprime numero de vértice e arestas
	printf("\033[1mAtividades e atividades que dependem delas:\033[0m\n\n");
	printf("A atividade de indice 0, escrita \033[93mem amarelo\033[0m, representa passar de ano.\033[0m\n\n");

	for (i = 1; i < grafo->countVertices; i++)
	{
		printf("\033[94m%d\033[0m - \033[4m%s\033[0m: ", i, grafo->tarefas[i].nome); //Imprime em qual aresta está
		aresta_t* ad = grafo->tarefas[i].cabecaArestas; //Chama a cabeça da lista de adjacência
		while (ad != NULL)
		{
			if(ad->vertice == 0) {
				printf("\033[93m%d (peso %d)\033[0m, ", ad->vertice, ad->peso); //Imprime o vértice 0 em cor
			} else {
				printf("%d (peso %d), ", ad->vertice, ad->peso); //Imprime a adjacência e seu peso
			}
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

// Checa se uma coluna está cheia
bool colunaCheia(int** matriz, int tamanho, int coluna)
{
	bool cheia = True;
	for (int i=0; i<tamanho; i++) {
		cheia *= matriz[i][coluna]; // Se algum dos valores da coluna for 0, 'cheia' vai virar 0 e não vai voltar a ser 1
	}

	return cheia;
}

/*--------------------------------------------------------------------------*/

// Transforma todos os valores de uma coluna em 1
void encheColuna(int** matriz, int tamanho, int coluna) 
{
	for (int i=0; i<tamanho; i++) {
		matriz[i][coluna] = 1;
	}
}

/*--------------------------------------------------------------------------*/

// Conta quantos vértices-pai existem num grafo e ajusta o número se for pequeno demais
int consertaPais(int** matriz, int tamanho) 
{
	bool* pais = (bool*) malloc (sizeof(bool) * tamanho); // Cria um vetor pra guardar quais vértices são pais 
	int numPais = 0;

	for (int i=0; i<tamanho; i++) { // Vê que vértices são pais e guarda no vetor
		pais[i] = colunaCheia(matriz, tamanho, i);
		numPais += pais[i];
	}

	while (numPais < MIN_PAIS) {
		int coluna = (rand()%tamanho);
		if (coluna == 0) coluna = 1; // Se 0 for pai, o caminho é impossível
		if (!pais[coluna]) { // Só aumenta o número de pais se a coluna sorteada já não for um pai
			encheColuna(matriz, tamanho, coluna);
			pais[coluna] = True;
			numPais++;
		}
	}

	free(pais);
}

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

	consertaPais(matFalhas, tamanho);

    for (int i=0; i<tamanho; i++) {
        completaGrafo(grafo, tamanho, i, matFalhas);
    }
    //mat_imprime (matFalhas, tamanho, tamanho); // Imprime a matriz de falhas pra motivos de debug

    mat_libera (matFalhas, tamanho); // Libera a matriz de falhas
}

/*--------------------------------------------------------------------------*/


// Encontra os menores caminhos para passar de ano, retorna um caminho_t**, com caminhos válidos até o primeiro índice com valor NULL
caminho_t** encontraMenoresCaminhos(grafo_t* grafo)
{
    int i, count;

	//Armazena o peso do menor caminho
	int pesoMenorCaminho = IMPOSSIVEL - 1;

	//Vetor para armazenar os ponteiros caminho_t*
	caminho_t** vetCaminhos = (caminho_t**) malloc(LIMITE_DE_CAMINHOS * sizeof(caminho_t*));

	//Contagem de caminhos+
	count = 0;

	//Percorre todos os vértices
	for(i = INDICE_INICIAL; i<grafo->countVertices;i++)
	{
		//Encontra as tarefas pai, ou seja, que não possuem nenhuma dependência pois ninguém aponta para elas
		if(grafo->tarefas[i].ehPai == True)
		{
			caminho_t* caminho = dijkstra(grafo, i);

			if (caminho->peso < pesoMenorCaminho)
			{
				count = 0;
				pesoMenorCaminho = caminho->peso;
				vetCaminhos[count] = caminho;
				count++;
			}
			else if (caminho->peso == pesoMenorCaminho && count < LIMITE_DE_CAMINHOS)
			{
				vetCaminhos[count] = caminho;
				count++;
			}
			else continue;
		}
	}
	vetCaminhos[count] = NULL;

	return vetCaminhos;
}


/*--------------------------------------------------------------------------*/
/* ======== Algoritmo de Dijkstra ======== */
/*--------------------------------------------------------------------------*/

void imprimeSituacao(grafo_t* grafo, int* distancia, int* precedencia, bool* aberto)
{
	int i;
	for(i = 0; i < grafo->countVertices; i++)
	{
		printf("[%d]-> D = %12d  |  PRE = %2d  |  A = %2d\n", i, distancia[i], precedencia[i], aberto[i]);
	}
	printf("\n\n----------------------------------------------------------------------------\n\n");
}

//Inicializa os vetores para o algoritmo de Dijkstra
void inicializaDijkstra(grafo_t* grafo, int* distancia, int* precedencia, bool* aberto, int s){
	int v;
	for (v = 0; v < grafo->countVertices; v++)
	{
		distancia[v] = IMPOSSIVEL; //A divisão por 2 evita que ocorra overflow ao analisar o vértice de menor distancia
		precedencia[v] = INDICE_INEXISTENTE;
		aberto[v] = True;
	}
	distancia[s] = 0;
}

//Função que realiza o relaxamento de um vértice
void relaxaVertice(grafo_t* grafo, int* distancia, int* precedencia, int u, int v){

	/*
	*	u -> vértice que irá relaxar v
	*	v -> vértice a ser relaxado
	*/

	aresta_t* ad = grafo->tarefas[u].cabecaArestas;

	//Percorre até encontrar o vértice com o qual u deverá relaxar
	while(ad && ad->vertice != v)
		ad = ad->prox;

	if (ad)
	{
		//Verifica se o vértice será ou não relaxado
		if(distancia[v] > distancia[u] + ad->peso)
		{
			distancia[v] = distancia[u] + ad->peso;
			precedencia[v] = u;
		}
	}
}

//Verifica se existe um vértice aberto no grafo
bool existeAberto(grafo_t* grafo, int * aberto){
	int i;

	for(i=0;i<grafo->countVertices;i++)
	{
		if(aberto[i]) return True;
	}
	return False;
}

//Retorna o vértice aberto de menor distância
int verticeMenorDistancia(grafo_t* grafo, int * aberto, int* distancia){


	int i, menor;

	//Encontra o primeiro vértice aberto
	for(i=0; i<grafo->countVertices;i++)
		if(aberto[i]) break;

	//Se não houver vértices abertos retorna INDICE_INEXISTENTE
	if (i == grafo->countVertices) return INDICE_INEXISTENTE;

	menor = i;

	//Encontra o menor vértice
	for(i=menor+1; i<grafo->countVertices; i++)
		if (aberto[i] && (distancia[menor] > distancia[i])) 
		{
			menor = i;
		}
		
	return menor;
}

//A partir dos dados da função dijkstra, essa função extrai o caminho, peso e quantidade de vértices do vértice v até PASSAR_DE_ANO
caminho_t* extraiCaminho(grafo_t* grafo, int* distancia, int* precedencia, int v, int s){
	//Aloca a estrutura caminho
	caminho_t* caminho = (caminho_t*)malloc(sizeof(caminho_t));
	int *verticesCaminhoInverso;
	
	//Verifica se existe um caminho de v até PASSAR_DE_ANO
	if(distancia[PASSAR_DE_ANO] < IMPOSSIVEL)
	{	
		int i = 0;
		int n = v;
		int j, count;

		caminho->peso = distancia[PASSAR_DE_ANO];
		//Aloca 
		verticesCaminhoInverso = (int*) malloc(grafo->countVertices * sizeof(int));
		
		verticesCaminhoInverso[i] = n;
		do{	
			i++;	
			n = precedencia[n];
			verticesCaminhoInverso[i] = n;
		}while (n != s);

		//Salva a contagem de vértices
		count = i + 1;
		caminho->countVertices = count;

		//Aloca um vetor para guardar os vértices do caminho
		caminho->vertices = (int*)malloc(count * sizeof(int));
		
		//Escreve o caminho na ordem correta
		for(i = 0, j = count - 1; i<count; i++, j--) {
			caminho->vertices[i] = verticesCaminhoInverso[j];
		}

		free(verticesCaminhoInverso);
	}
	else
	{
		caminho->peso = IMPOSSIVEL;
		caminho->countVertices = IMPOSSIVEL;
		caminho->vertices = NULL;
	}
	return caminho;
}


/*
* Executa o algoritmo de Dijkstra,
* retorna um vetor int* com as distancias dos vértices em relação ao vértice inicial s
*/
caminho_t* dijkstra(grafo_t* grafo, int s){
	//Declara as variáveis
	int* distancia = (int*) malloc(grafo->countVertices* sizeof(int));
	int* precedencia = (int*) malloc(grafo->countVertices* sizeof(int));
	bool* aberto = (bool*) malloc(grafo->countVertices* sizeof(bool));
	
	//Inicializa os valores de Dijkstra
	inicializaDijkstra(grafo, distancia, precedencia, aberto, s);

	while (existeAberto(grafo, aberto))
	{
		//Encontra o vértice de menor distância
		int u = verticeMenorDistancia(grafo, aberto, distancia);
		aberto[u] = False;
		
		//Encontra a cabeça do vértice
		aresta_t* ad = grafo->tarefas[u].cabecaArestas;
		while(ad)
		{
			//Relaxa o vértice, se necessário
			relaxaVertice(grafo, distancia, precedencia, u, ad->vertice);
			ad = ad->prox;
		}
	}

	return extraiCaminho(grafo, distancia, precedencia, PASSAR_DE_ANO, s);
}

//Imprime o caminho e seus atributos
void imprimeCaminho(caminho_t* caminho, grafo_t* grafo){

	int i;

	if (caminho->peso >= IMPOSSIVEL) printf("\nCaminho Impossivel\n");
	else
	{
		printf("Numero de tarefas feito: %d\n", caminho->countVertices);
		printf("Tempo necessario: %d\n", caminho->peso);

		
		for(i =0 ;i<caminho->countVertices;i++)
		{
			if (caminho->vertices[i] == 0) {	
				printf("Passar de ano!\n");
			} else {
				printf("%s -> ", grafo->tarefas[caminho->vertices[i]].nome);
			}
		}
	}

}


//Desaloca o grafo
void liberaGrafo(grafo_t* grafo){
	int i;
	aresta_t* cabeca;
	aresta_t* t;
	//Libera Arestas
	for(i = 0;i<grafo->countVertices;i++)
	{
		cabeca = grafo->tarefas[i].cabecaArestas;
		while (cabeca != NULL)
		{
			t = cabeca->prox;
			free(cabeca);
			cabeca = t;
		}
	}
	free(grafo->tarefas);
	free(grafo);
}

//Libera o vetor caminho
void liberaVetCaminho(caminho_t** vetCaminhos){
	int i;
	for(i = 0; vetCaminhos[i] != NULL; i++)
	{
		free(vetCaminhos[i]->vertices);
		free(vetCaminhos[i]);
	}
	free(vetCaminhos);
}