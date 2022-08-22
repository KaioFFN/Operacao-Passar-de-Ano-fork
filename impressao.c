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

void imprimeThumb()
{
    printf("╔══════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                           OPERAÇÃO PASSAR DE ANO                             ║\n");
    printf("╚══════════════════════════════════════════════════════════════════════════════╝\n");
}

//Imprime um menu e retorna a chave inserida
int imprimeMenu(int chave){
    switch (chave)
    {
        case 0:
            imprimeThumb();
            printf("╔════════════════════════════════╗\n");
            printf("║  1. Gerar tarefas/grafo        ║\n");
            printf("║  2. Imprimir menores caminhos  ║\n");
            printf("║  0. Sair                       ║\n");
            printf("╚════════════════════════════════╝\n");
            printf("╠  Chave -> ");
            scanf("%d", &chave);
            break;
        case 1:
            grafo_t* grafo = criaGrafo(TAM_GRAFO); // Faz um grafo de tamanho TAM_GRAFO+1
            encheGrafo(grafo, TAM_GRAFO+1, NUM_FALHAS, True);
            imprimeGrafo(grafo);
            printf("\n\n");
            
            printf("╠  Chave -> ");
            scanf("%d", &chave);
            break;
        case 2:
            imprimeMenoresCaminhos(grafo);
            printf("╠  Chave -> ");
            scanf("%d", &chave);
            break;
        default:
            scanf("%d", &chave);
            break;

    }
    return chave;

}

