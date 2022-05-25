#include "arraygraph.h"

//create
ArrayGraph* createArrayUnDirectedGraph(int maxVertexCount, int type)
{
    ArrayGraph *new = malloc(sizeof(ArrayGraph));
    new->currentVertexCount = 0;
    new->rear = -1;
    new->front = 0;
    new->graphType = type;
    new->maxVertexCount = maxVertexCount;
    new->ppAdjEdge = malloc(sizeof(int **) * maxVertexCount);
    new->pVertex = malloc(sizeof(int *) * maxVertexCount);
}

//delete
void deleteArrayGraph(ArrayGraph** pGraph)
{
    if(pGraph && *pGraph)
    {
        if((*pGraph)->ppAdjEdge)
        {
            if ((*pGraph)->rear >= 0)
            {
                int min = (*pGraph)->front < (*pGraph)->rear ? (*pGraph)->front : (*pGraph)->rear;
                int max = (*pGraph)->front > (*pGraph)->rear ? (*pGraph)->front : (*pGraph)->rear;
                while (min <= max)
                    free((*pGraph)->ppAdjEdge[min++]);
            }
            free((*pGraph)->ppAdjEdge);
        }
        if((*pGraph)->pVertex)
            free((*pGraph)->pVertex);
        free(*pGraph);
        *pGraph = NULL;
    }
}

//is empty
int isEmptyAG(ArrayGraph* pGraph)
{
    return !pGraph || !pGraph->currentVertexCount;
}

//add vertex
int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if(pGraph && pGraph->pVertex && pGraph->currentVertexCount < pGraph->maxVertexCount)
    {
        pGraph->pVertex[pGraph->rear++] = vertexID;
        return 1;
    }
    return 0;
}

//is in array
static int isValidId(ArrayGraph* pGraph, int vertex)
{
    for(int i = 0; i < pGraph->currentVertexCount; i++)
        if(pGraph->pVertex[i] == vertex)
            return 1;
    return 0;
}

//add edge
int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if(pGraph && pGraph->pVertex && pGraph->graphType == 1)
    {
        return 1;
    }
    return 0;
}

int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    if(pGraph && pGraph->pVertex && pGraph->graphType == 2)
    {
        return 1;
    }
    return 0;
}

//is vertex ok
int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
    if (pGraph && pGraph->pVertex)
        for(int i = 0; i < pGraph->currentVertexCount; i++)
            if(pGraph->pVertex[i] == vertexID)
                return 1;
    return 0;
}

//remove vertex
int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if (pGraph && pGraph->pVertex)
    {
        if(pGraph->pVertex[pGraph->rear] == vertexID)
            ;
        else if(pGraph->pVertex[pGraph->front] == vertexID)
            ;
        else
            goto jump;
        return 1;
    }
    jump:
    return 0;
}

//remove edge
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (pGraph && pGraph->pVertex)
    {
        return 1;
    }
    return 0;
}

//display
void displayArrayGraph(ArrayGraph* pGraph)
{
    if (pGraph->graphType == 1)
        printf("type : undirected\n");
    else
        printf("type : directed\n");
    printf("max count : %d\n",pGraph->maxVertexCount);
    printf("current count : %d\n",pGraph->currentVertexCount);
    printf("front : \n", pGraph->front);
    printf("rear : \n", pGraph->rear);   
    printf("vetex : ");
    for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++)
        printf("%d ",pGraph->pVertex[i++ / (pGraph->maxVertexCount + 1)]);
    printf("\n");
}

int main()
{
    return (0);
}
