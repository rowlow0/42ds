#include "arraygraph.h"

//create
ArrayGraph* createArrayGraph(int maxVertexCount, int type)
{
    if (maxVertexCount <= 0 || !(type == 1 || type == 2))
        return NULL;
    ArrayGraph *new = malloc(sizeof(ArrayGraph));
    new->currentVertexCount = 0;
    new->rear = -1;
    new->front = 0;
    new->graphType = type;
    new->maxVertexCount = maxVertexCount;
    new->ppAdjEdge = malloc(sizeof(int **) * maxVertexCount);
    new->pVertex = malloc(sizeof(int *) * maxVertexCount);
    return new;
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

//search vertex
int checkVertexValid(ArrayGraph* pGraph, int vertexID)
{
    //if (pGraph && pGraph->pVertex)
    for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++)
        if(pGraph->pVertex[i++ / (pGraph->maxVertexCount + 1)] == vertexID)
            return 1;
    return 0;
}

//add vertex
int addVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if(pGraph && pGraph->pVertex && pGraph->currentVertexCount < pGraph->maxVertexCount && !checkVertexValid(pGraph, vertexID))
    {
        pGraph->ppAdjEdge[pGraph->currentVertexCount] = calloc(sizeof(int *), sizeof(int *) * pGraph->maxVertexCount);
        return pGraph->pVertex[pGraph->rear++] = vertexID;
    }
    return 0;
}

//add edge to directed graph
int addEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if(pGraph && pGraph->pVertex && pGraph->graphType == 1 && checkVertexValid(pGraph, fromVertexID) && checkVertexValid(pGraph, toVertexID))
    {
        int x, y;
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % (pGraph->maxVertexCount + 1)] == fromVertexID)
            {
                x = i;
                break;
            }
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % (pGraph->maxVertexCount + 1)] == toVertexID)
            {
                y = i;
                break;
            }
        pGraph->ppAdjEdge[x][y] = 1;
        pGraph->ppAdjEdge[y][x] = 1;
        return 1;
    }
    return 0;
}

//add edge to directed graph
int addEdgewithWeightAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID, int weight)
{
    if(pGraph && pGraph->pVertex && pGraph->graphType == 2 && checkVertexValid(pGraph, fromVertexID) && checkVertexValid(pGraph, toVertexID))
    {
        int x, y;
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % (pGraph->maxVertexCount + 1)] == fromVertexID)
            {
                x = i;
                break;
            }
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % (pGraph->maxVertexCount + 1)] == toVertexID)
            {
                y = i;
                break;
            }
        pGraph->ppAdjEdge[x][y] = weight;
        return 1;
    }
    return 0;
}

//remove vertex
int removeVertexAG(ArrayGraph* pGraph, int vertexID)
{
    if (pGraph && pGraph->pVertex && checkVertexValid(pGraph, vertexID))
    {
        int y;
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % (pGraph->maxVertexCount + 1)] == vertexID)
            {
                y = i;
                break;
            }
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            pGraph->ppAdjEdge[i % (pGraph->maxVertexCount + 1)][y] = 0;
        if(pGraph->pVertex[pGraph->rear] == vertexID)
        {
            free(pGraph->ppAdjEdge[pGraph->rear]);
            pGraph->pVertex[pGraph->rear--] = 0;
        }
        else if(pGraph->pVertex[pGraph->front] == vertexID)
        {
            free(pGraph->ppAdjEdge[pGraph->front]);
            pGraph->pVertex[pGraph->front++] = 0;
            if(pGraph->front > pGraph->maxVertexCount)
                pGraph->front = 0;
            if(!pGraph->currentVertexCount - 1)
                pGraph->rear = -1;
        }
        else
            goto jump;
        pGraph->currentVertexCount--;
        return 1;
    }
    jump:
    return 0;
}

//remove edge
int removeEdgeAG(ArrayGraph* pGraph, int fromVertexID, int toVertexID)
{
    if (pGraph && pGraph->pVertex && checkVertexValid(pGraph, fromVertexID) && checkVertexValid(pGraph, toVertexID))
    {
        int x, y;
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % (pGraph->maxVertexCount + 1)] == fromVertexID)
            {
                x = i;
                break;
            }
        for(int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++, i++)
            if(pGraph->pVertex[i % (pGraph->maxVertexCount + 1)] == toVertexID)
            {
                y = i;
                break;
            }
        pGraph->ppAdjEdge[x][y] = 0;
        if(pGraph->graphType == 1)
            pGraph->ppAdjEdge[y][x] = 0;
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
    printf("max count : %d\n", pGraph->maxVertexCount);
    printf("current count : %d\n", pGraph->currentVertexCount);
    printf("front : %d\n", pGraph->front);
    printf("rear : %d\n", pGraph->rear);   
    printf("vetex : ");
    for (int i = pGraph->front, j = 0; j < pGraph->currentVertexCount; j++)
        printf("%d ",pGraph->pVertex[i++ / (pGraph->maxVertexCount + 1)]);
    printf("vetex edge map: \n");
    for (int i = 0; i < pGraph->currentVertexCount; i++)
    {
        for (int j = 0; j < pGraph->maxVertexCount; j++)
            printf("%d ", pGraph->ppAdjEdge[i][j]);
        printf("\n");
    }
    printf("\n");
}

int main()
{
    return (0);
}
