#include <stdio.h>
#include "graph.h"

int main () {
	FILE *f, *f2;
	f = fopen("nodes.txt", "r");
    f2 = fopen("edges.txt", "r");

    int ini, fim;
    float arqmb;
    float *T;
    float time;
    Graph *G;
    G = createGraph(6);
    RWGraph(G,f,f2);

    int var = 0;
    printf("que operação deseja realizar?\n");
    printf("1-Descobrir o menor caminho entre dois pontos para um dado arquivo;\n");
    printf("2-apresetar a cobertura de envio de um PoP\n");
    printf("3-mostrar as informações do grafo\n");
    printf("4-sair do programa\n");
    scanf("%d",&var);

    switch(var)
        {
        case 1:
            printf("digite o ponto de partida o destino e o tamanho do arquivo, respectivamente:");
            scanf("%d %d %f", &ini, &fim, &arqmb);
            Dijkstra(G,ini,fim,arqmb);
            break;
        case 2:
            printf("digite o ponto de partida o destino, tamanho do arquivo e o tempo limite, respectivamente:");
            scanf("%d %d %f %f", &ini, &fim, &arqmb, &time);
               T =  Dijkstra(G,ini,fim, arqmb);
            calcula_tempo(T,fim,time);
        break;

        case 3:
        printf("\n\n");
        printGraph(G);
        break;



        case 4:
        return 0;
        }


    freeGraph(G);



    return 0;
}
