#include <stdio.h>
#include <stdlib.h>
typedef struct Edge{
    int src, dest;
} Edge;

typedef struct Graph{
    int V, E;
    Edge* edge;
} Graph;

typedef struct Subset {
    int parent;
    int rank;
} Subset;

Graph *createGraph(int V, int E)
{
    Graph *graph = malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edge = malloc(graph->E * sizeof(Edge));
    return graph;
}

int find(Subset *subset, int i)
{
    if (subset[i].parent != i)
        subset[i].parent = find(subset, subset[i].parent);
    return subset[i].parent;
}

void unions(Subset *subset, int xroot, int yroot)
{
    if(subset[xroot].rank < subset[yroot].rank)
        subset[xroot].parent = yroot;
    else if(subset[xroot].rank > subset[yroot].rank)
        subset[yroot].parent = xroot;
    else
    {
        subset[yroot].parent = xroot;
        subset[xroot].rank++;
    }
}

int isCyle(Graph *graph)
{
    int V = graph->V;
    int E = graph->E;
    Subset *subset = malloc(V * sizeof(Subset));
    for(int v = 0; v < V; v++)
    {
        subset[v].parent = v;
        subset[v].rank = 0;
    }
    for(int e = 0; e < E;++e)
    {
        int x = find(subset, graph->edge[e].src);
        int y = find(subset, graph->edge[e].dest);
        if(x == y)
        {
            free(subset);
            return 1;
        }
        unions(subset, x, y);
    }
    free(subset);
    return 0;
}

int main()
{
    int V = 3, E = 1;
    Graph *graph = createGraph(V, E);
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    //graph->edge[1].src = 1;
    //graph->edge[1].dest = 2;
    //graph->edge[2].src = 0;
    //graph->edge[2].dest = 2;
    if (isCyle(graph))
        printf("Graph contains cycle");
    else
        printf("Graph doesn't contaion cycle");
    free(graph->edge);
    free(graph);
    //system("leaks a.out");
    //graph % gcc -g -fsanitize=address -Wall -Wextra -Werror isCycleTyping.c
    return 0;   
}
