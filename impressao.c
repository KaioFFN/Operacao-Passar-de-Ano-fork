/**
* @file: grafos.c
* @brief: Funções para criação e manipulação de grafos
* @author: Grupo
* @date: 17-08-2022
*/

/*Includes*/
#include "OperacaoPassarDeAno.h"

/*Consts*/

/*Functs*/
// Um regex que limpa a tela, muitas vezes mais rápido que o system("clear") e funciona em qualquer plataforma
void limpaTerm(){
    printf("\033[1;1H\033[2J");
}

//Imprime os menores caminhos até o fim do ano
void imprimeMenoresCaminhos(grafo_t* grafo){
    //Encontra os menores caminhos
    caminho_t** vetCaminhos = encontraMenoresCaminhos(grafo);

    int i;

    printf("|------------------------------------------------------------------------------|\n");
    printf("|                         Menores Caminhos ate Passar de Ano                   |\n");
    printf("|------------------------------------------------------------------------------|\n");

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

void imprimeThumb()
{
    printf("|==============================================================================|\n");
    printf("|                           OPERACAO PASSAR DE ANO                             |\n");
    printf("|==============================================================================|\n");
}

//Imprime um menu e retorna a chave inserida
int imprimeMenu(int chave){
    switch (chave)
    {
        case 0:
            imprimeThumb();
            printf("|================================|\n");
            printf("|  1. Gerar tarefas/grafo        |\n");
            printf("|  2. Imprimir menores caminhos  |\n");
            printf("|  0. Sair                       |\n");
            printf("|================================|\n");
            printf("|  Chave -> ");
            scanf("%d", &chave);
            limpaTerm();
            break;
        case 1:
            grafo_t* grafo = criaGrafo(TAM_GRAFO); // Faz um grafo de tamanho TAM_GRAFO+1
            encheGrafo(grafo, TAM_GRAFO+1, NUM_FALHAS, True);
            imprimeGrafo(grafo);
            printf("\n\n");
            
            printf("|  Chave -> ");
            scanf("%d", &chave);
            limpaTerm();
            break;
        case 2:
            imprimeMenoresCaminhos(grafo);
            printf("|  Chave -> ");
            scanf("%d", &chave);
            limpaTerm();
            break;
        default:
            printf("|  Chave Invalida - Tente novamente -> ");
            scanf("%d", &chave);
            break;
    }
    return chave;

}

