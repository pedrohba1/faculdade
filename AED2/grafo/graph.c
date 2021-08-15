#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "float.h" //biblioteca com o valor máximo de float.


Graph* createGraph ( int nodes )
{
    if (nodes < 1)
    {
        return NULL;
    }

    Graph* G = (Graph*) malloc(sizeof(Graph));

    if (!G)
    {
        return NULL;
    }

    G->nodes = nodes;
    G->edges = 0;
    G->degree = (int*) calloc(nodes, sizeof(int));

    if (!G->degree)
    {
        free(G);

        return NULL;
    }

    G->M = (PoP**) malloc(nodes * sizeof(PoP*));

    if (!G->M)
    {
        free(G->degree);
        free(G);

        return NULL;
    }

    int i, j;
    for (i=0; i<nodes; ++i)
    {
        G->M[i] = (PoP*) calloc(nodes, sizeof(PoP));

        if (!G->M[i])
        {
            for (j=i; j>0; --j)
            {
                free(G->M[j]);
            }

            free(G->M);
            free(G->degree);
            free(G);

            return NULL;
        }
    }

    return G;
}

void freeGraph ( Graph* G )
{

    int i;

    for (i=0; i< G->nodes; ++i)
    {
        free(G->M[i]);
    }

    free(G->M);
    free(G->degree);
    free(G);

    G = NULL;

}

void printGraph ( Graph* G )
{
    if (!G)
    {
        printf("Not exist!\n");
        return;
    }

    printf("Nodes: %d \n", G->nodes);
    printf("Edges: %d \n", G->edges);

    puts("");

    int i, j;

    for (i=0; i<G->nodes; ++i)
    {
        printf("DEGREE[%d]: %d\n", i, G->degree[i]);
    }

    puts("");

    for (i=0; i<G->nodes; ++i)
    {

        for (j=0; j<G->nodes; ++j)
        {
            printf("%.2f ", G->M[i][j].weight);
        }
        printf("\n");
    }

    puts("");
}

int verifyNodeGraph ( Graph* G, int node )
{
    if (!G || node < 0 || node > G->nodes)
    {
        return 0;
    }

    return 1;
}

int insertEdgeGraph ( Graph* G, int N1, int N2, float w )
{
    if (!G || !verifyNodeGraph(G, N1) || !verifyNodeGraph(G, N2))
    {
        return -1;
    }

    if (G->M[N1][N2].weight != 0)
    {
        return 0;
    }

    G->M[N1][N2].weight = w;
    G->M[N2][N1].weight = w;
    G->edges++;
    G->degree[N1]++;
    G->degree[N2]++;

    return 1;
}

int checkEdgeGraph ( Graph* G, int N1, int N2 )
{
    if (!G || !verifyNodeGraph(G, N1) || !verifyNodeGraph(G, N2))
    {
        return -1;
    }

    return G->M[N1][N2].weight;
}

int removeEdgeGraph ( Graph* G, int N1, int N2 )
{
    if (!G || !verifyNodeGraph(G, N1) || !verifyNodeGraph(G, N2))
    {
        return -1;
    }

    if (!G->M[N1][N2].weight)
    {
        return 0;
    }

    G->M[N1][N2].weight = 0;
    G->M[N2][N1].weight = 0;

    G->edges--;
    G->degree[N1]--;
    G->degree[N2]--;
    return 1;
}



int RWGraph(Graph* G, FILE *f, FILE *f2)
{
    if(f == NULL || f2 == NULL) printf("arquivo não encontrado\n");


    else
    {
        PoP p;
        int i=0;
        while(fscanf(f,"%d; %[A-Za-z]; %d; %d",&p.id, &p.name, &p.x, &p.y ) != EOF)
        {
            G->M[i][i] = p;
            G->M[i][i].weight = 0;
            i++;
        }


        int from;
        int to;
        float weight;
        while(fscanf(f2,"%d;%d;%f",&from, &to, &weight) != EOF)
        {
            insertEdgeGraph(G,from,to,weight);
        }

        fclose(f);
        fclose(f2);
    }
    return 1;
}



//funções requisitadas pelo professor:


int numVertices(Graph *G)
{
    return G->nodes;
}

int grauVertice(Graph *G, int v)
{
    return G->degree[v];
}


int ehAdjacente(Graph *G, int v1, int v2)
{
    if(G->M[v1][v2].weight ==0 || G->M[v2][v1].weight == 0) return 0;
    else return 1;


}

float* Dijkstra(Graph *G, int origem, int destino, float tamMB)
{


    float *T; // Vetor para encontrar as bandas mais potentes.
    T = (float*) malloc(G->nodes*sizeof(float));


    //vetor de Tempo de entrega
    int j;
    for(j=0; j< G->nodes; j++) T[j] = FLT_MAX;

    //marcar a banda como 0.
    T[origem] = 0;



    //vetor de visitados
    int *S;
    S= (int*) calloc(G->nodes, sizeof(int));
    //marcar o vetor de origem como visitado:
    S[origem] = 1;

    //vetor de antecessores:
    int *Ant;
    Ant = (int*) malloc(G->nodes*sizeof(int));
    for(j=0; j<G->nodes; j++) Ant[j] = -1;


    //encontra os primeiros pesos para a primeira iteração
    // e coloca o primeiro melhor caminho
    int i;
    for(i=0; i< G->nodes; i++)
    {
        if(S[i] == 0)
        {
            if(G->M[origem][i].weight !=0 )
            {
                T[i] = (tamMB)/(G->M[origem][i].weight);

                Ant[origem] = i;
            }
        }
    }



    int k;
    int tnode;
    int j2  =0;
    int k2;
    for(k=0; k<G->nodes; k++)
    {

        tnode =  busca_menor(T,G->nodes, S);
        S[tnode] = 1;



        for(j2 = 0; j2< G->nodes; j2++)
        {
            if(S[j2] != 0) continue;
            if(ehAdjacente(G,tnode,j2))
            {
                T[j2] = T[tnode] + (tamMB)/(G->M[tnode][j2].weight);
                Ant[tnode] = j2;
            }
        }
    }

    printf("vetor de tempos:\n");
    print_vetor(T,G->nodes);
    printf("\n");
    printf("vetor de visitados:\n");
    print_vetorint(S, G->nodes);
    printf("\n");
    printf("vetor de caminho:\n");
    print_vetorint(Ant, G->nodes);
    escreve_caminho(G,Ant,G->nodes,origem,destino);
    printf("Tempo total de transmissão: %.2f", T[destino]);
    printf("\n\n");


    return T;
}

int busca_menor(float *v,int tam, int *S)
{
    int i;
    float menor;
    menor = FLT_MAX;
    int position;

    for(i=0; i< tam ; i++)
    {
        if(S[i] == 1) continue;
        if(v[i] < menor && v[i] != 0)
        {

             menor = v[i];
             position = i;
        }



    }
    return position;
}





void print_vetor(float *v, int tam)
{


    int i;
    for(i=0; i< tam; i++)
    {

        if(v[i] == FLT_MAX)
        {
            printf(" inf ");
            continue;
        }
        printf(" %.2f ", v[i]);
    }
}



void print_vetorint(int* v, int tam)
{

    int i;
    for(i=0; i< tam; i++)
    {
        printf(" %d ", v[i]);
    }

}

void escreve_caminho(Graph* G,int*v, int tam, int ini, int fim)
{
    printf("\n\n");

    int repeat = ini;

    printf("CAMINHO MAIS RÁPIDO PELOS NÚMEROS DE ID:\n");
    printf("%d->", ini);
    while(v[ini] != -1)
    {
        if(ini == fim) break;
        printf("%d->", v[ini]);
        ini = v[ini];
    }
    printf("\n");


    ini = repeat;
    int aux;
    printf("CAMINHO MAIS RÁPIDO PELO NOME DAS CIDADES:\n");

    printf("%s->",G->M[ini][ini].name);
    while(v[ini] != -1)
    {
        if(ini == fim) break;
        aux = v[ini];
        printf("%s->", G->M[aux][aux].name);
        ini = v[ini];
    }
    printf("\n\n");

}

void cobertura(Graph*  G,int origem, int inter)
{
    int *S;
    S = calloc(G->nodes,sizeof(int));
    int i;
    for(i =0; i< G->nodes; i++)
    {
    if(ehAdjacente(G,origem,i)) S[i] = 1;
    }
}



void calcula_tempo(float *T, int tam, float tempo_limite)
{
    int i;
    for(i=0; i<tam; i++)
    {
    if(T[i] < tempo_limite && T[i] != 0) printf("tempo de tranissão até %d: %f \n", i, T[i]);
    }

}

