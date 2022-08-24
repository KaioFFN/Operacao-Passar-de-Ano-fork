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
void imprimeMenoresCaminhos(grafo_t* grafo, caminho_t** vetCaminhos){


    int i;

    printf("\033[96m|==============================================================================|\033[0m\n"); // Essas sequências de caracteres estranhas são códigos de escape ANSI, que mudam a cor dos caracteres impressos.
    printf("\033[96m|\033[0m                      \033[33mMenores caminhos ate passar de ano\033[0m                      \033[96m|\033[0m\n");
    printf("\033[96m|==============================================================================|\033[0m\n");

	if(vetCaminhos[0] == NULL)
	{
		printf("Nenhum caminho possivel -> Voce vai bombar!\n\n");
	}
	else
	{
		for(i=0;vetCaminhos[i] != NULL; i++)
		{
			printf("\033[96m--------------------------------------------------------\033[0m\n");
			imprimeCaminho(vetCaminhos[i], grafo);
			printf("\033[96m--------------------------------------------------------\033[0m\n");
		}
    
	}
}

void imprimeThumb()
{
    printf("\033[96m|==============================================================================|\033[0m\n");
    printf("\033[96m|\033[0m                           \033[33mOPERACAO PASSAR DE ANO\033[0m                             \033[96m|\033[0m\n");
    printf("\033[96m|==============================================================================|\033[0m\n");
}

//Imprime um menu e retorna a chave inserida
int imprimeMenu(int chave){
    //Cria o grafo inicial, enche e encontra os menores caminhos
    grafo_t* grafo = criaGrafo(TAM_GRAFO); // Faz um grafo de tamanho TAM_GRAFO+1
    encheGrafo(grafo, TAM_GRAFO+1, NUM_FALHAS, True);
    caminho_t** vetCaminhos = encontraMenoresCaminhos(grafo); //Encontra os menores caminhos
    switch (chave)
    {
        case 0:
            imprimeThumb();
            printf("\033[96m|================================|\033[0m\n");
            printf("\033[96m|\033[0m  \033[34m1.\033[0m Gerar tarefas/grafo        \033[96m|\033[0m\n");
            printf("\033[96m|\033[0m  \033[34m2.\033[0m Imprimir menores caminhos  \033[96m|\033[0m\n");
            printf("\033[96m|\033[0m  \033[34m3.\033[0m Imprimir grafo             \033[96m|\033[0m\n");
            printf("\033[96m|\033[0m  \033[34m0.\033[0m Sair                       \033[96m|\033[0m\n");
            printf("\033[96m|================================|\033[0m\n");
            printf("\033[96m|\033[0m  \033[32mChave ->\033[0m ");
            scanf("%d", &chave);
            limpaTerm();
            break;
        case 1:
            liberaGrafo(grafo);
            liberaVetCaminho(vetCaminhos);
            grafo_t* grafo = criaGrafo(TAM_GRAFO); // Faz um grafo de tamanho TAM_GRAFO+1
            encheGrafo(grafo, TAM_GRAFO+1, NUM_FALHAS, True);
            imprimeGrafo(grafo);
            caminho_t** vetCaminhos = encontraMenoresCaminhos(grafo); //Encontra os menores caminhos
            printf("\n\n");
            printf("\033[96m|\033[0m  \033[32mChave ->\033[0m ");
            scanf("%d", &chave);
            limpaTerm();
            break;
        case 2:
            imprimeMenoresCaminhos(grafo, vetCaminhos);
            printf("\033[96m|\033[0m  \033[32mChave ->\033[0m ");
            scanf("%d", &chave);
            limpaTerm();
            break;
        case 3:
            imprimeGrafo(grafo);
            printf("\n\n");
            printf("\033[96m|\033[0m  \033[32mChave ->\033[0m ");
            scanf("%d", &chave);
            limpaTerm();
            break;
        default:
            printf("\033[96m|\033[0m  Chave Invalida - Tente novamente -> ");
            scanf("%d", &chave);
            break;
    }
    return chave;

}

