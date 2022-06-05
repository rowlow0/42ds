#include "arraygraph.c"

int find(int i, int *array)
{
    while(array[i] != i)
        i = array[i];
    return i;
}

void union1(int i, int j, int *array)
{
    int a = find(i, array);
    int b = find(j, array);
    array[a] = b;
}

void    kruskal(ArrayGraph *g)
{
    int mincost = 0;
    int *array = malloc(sizeof(int) * g->currentVertexCount);
    for (int i = 0; i < g->currentVertexCount; i++)
        array[i] = i;
    int edge_count = 0;
    while(edge_count < g->currentVertexCount -1)
    {
        int min = INT_MAX, a = -1, b = -1;
        for (int i = 0; i < g->currentVertexCount; i++)
        {
            for(int j = 0; j < g->currentVertexCount; j++)
            {
                if(find(i, array) != find(j, array) && g->ppAdjEdge[i][j] < min)
                {
                    min = g->ppAdjEdge[i][j];
                    a = i;
                    b = j;
                }
            }
        }
        union1(a, b, array);
        if(min == INT_MAX)
        {
            printf("there is no answer\n");
            free(array);
            return ;
        }
        printf("Edge %d: (%d %d) cost:%d \n", edge_count++, a, b, min);
        mincost += min;
    }
    printf("\n minimum cost = %d \n",mincost);
    free(array);
}

int main()
{
    ArrayGraph *g = createArrayGraph(6,GRAPH_UNDIRECTED);
    addVertexAG(g, 0);
    addVertexAG(g, 1);
    addVertexAG(g, 2);
    addVertexAG(g, 3);
    addVertexAG(g, 4);
    addVertexAG(g, 5);
    addEdgewithWeightAG(g, 1, 0, 4);
    addEdgewithWeightAG(g, 1, 2, 2);
    addEdgewithWeightAG(g, 0, 2, 3);
    addEdgewithWeightAG(g, 2, 3, 1);
    addEdgewithWeightAG(g, 4, 3, 1);
    addEdgewithWeightAG(g, 4, 5, 6);
    addEdgewithWeightAG(g, 3, 5, 5);
    for (int i = 0; i < g->currentVertexCount; i++)
        for (int j = 0; j < g->currentVertexCount; j++)
            if (g->ppAdjEdge[i][j] == 0)
                g->ppAdjEdge[i][j] = INT_MAX;
    //displayArrayGraph(g);
    kruskal(g);
    deleteArrayGraph(&g);
    //system("leaks a.out");
    return (0);
}