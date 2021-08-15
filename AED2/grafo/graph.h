#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

typedef struct pop {
	int id;
	float weight;
	char name[20];
	int x, y;
} PoP;

struct graph
{
    int nodes, edges;
    int *degree;
    PoP **M;
};


typedef struct pop PoP;

typedef struct graph Graph;

Graph* createGraph ( int nodes );
void freeGraph ( Graph* G );
void printGraph ( Graph* G );

int insertEdgeGraph ( Graph* G, int N1, int N2, float weight );
int checkEdgeGraph ( Graph* G, int N1, int N2 );
int removeEdgeGraph ( Graph* G, int N1, int N2 );
int RWGraph(Graph * G, FILE *f, FILE *f2);

//funções requisitadas pelo professor:
int numVertices(Graph *G);
int grauVertice(Graph *G, int v);
int ehAdjacente(Graph *G, int v1, int v2);
float* Dijkstra(Graph *G, int origem, int destino, float tamMB);
void calcula_tempo(float *T, int tam, float tempo_limite);
void cobertura(Graph*  G,int origem, int inter);


//funções auxiliares:

void print_vetor(float *v, int tam);
void print_vetorint(int *v, int tam);
void escreve_caminho(Graph* G,int*v, int tam, int ini, int fim);
int busca_menor(float *v,int tam, int *S); // necesário para o dijkstra



#endif // GRAPH_H_INCLUDED
