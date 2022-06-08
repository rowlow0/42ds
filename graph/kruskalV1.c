#include "arraygraph.c"

int find(int i, int *parent)
{
    while(parent[i] != i)
        i = parent[i];
    return i;
}

void union1(int i, int j, int *parent)
{
    int a = find(i, parent);
    int b = find(j, parent);
    parent[a] = b;
}

void init_parent(int **parent, ArrayGraph *g)
{
    *parent = malloc(sizeof(int) * g->currentVertexCount);
    for (int i = 0; i < g->currentVertexCount; i++)
        (*parent)[i] = i;
}

void    kruskalV1(ArrayGraph *g)
{
    int mincost = 0, edge_count = 0, *parent;
    init_parent(&parent, g);
    while(edge_count < g->currentVertexCount -1)
    {
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < g->currentVertexCount; i++)
        {
            for(int j = 0; j < g->currentVertexCount; j++)
            {
                if(find(i, parent) != find(j, parent) && g->ppAdjEdge[i][j] < min)
                {
                    min = g->ppAdjEdge[i][j];
                    a = i;
                    b = j;
                }
            }
        }
        if(a != b)
        {
            union1(a, b, parent);
            for (int i = 0; i < g->currentVertexCount; i++)
                printf("%d ", parent[i]);
            printf("\n");
            printf("Edge %d: (%d %d) cost:%d \n", edge_count, a, b, min);
            mincost += min;
        }
        edge_count++;
    }
    free(parent);
    printf("\n minimum cost = %d \n", mincost);
}

int main()
{
    ArrayGraph *g = createArrayGraph(7,GRAPH_UNDIRECTED);
    addVertexAG(g, 0);
    addVertexAG(g, 1);
    addVertexAG(g, 2);
    addVertexAG(g, 3);
    addVertexAG(g, 4);
    addVertexAG(g, 5);
    addVertexAG(g, 6);
    //addEdgewithWeightAG(g, 1, 0, 2);
    addEdgewithWeightAG(g, 1, 2, 11);
    addEdgewithWeightAG(g, 0, 2, 2);
    addEdgewithWeightAG(g, 2, 3, 1);
    addEdgewithWeightAG(g, 4, 3, 1);
    addEdgewithWeightAG(g, 4, 5, 6);
    addEdgewithWeightAG(g, 3, 5, 5);
    addEdgewithWeightAG(g, 1, 6, 1);
    addEdgewithWeightAG(g, 0, 6, 8);
    displayArrayGraph(g);
    for (int i = 0; i < g->currentVertexCount; i++)
        for (int j = 0; j < g->currentVertexCount; j++)
            if (g->ppAdjEdge[i][j] == 0)
                g->ppAdjEdge[i][j] = INT_MAX;
    kruskalV1(g);
    deleteArrayGraph(&g);
    //gcc -g -fsanitize=address -Wall -Wextra -Werror kruskalv1.c
    //system("leaks a.out");
    return (0);
}

//https://www.geeksforgeeks.org/kruskals-algorithm-simple-implementation-for-adjacency-matrix/