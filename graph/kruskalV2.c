#include "graphlinkedlist.c"

typedef struct Dsu
{
    int *parent;
    int *rank;
} Dsu;

void print_container(GraphVertex *container, int size)
{
    for(int i = 0; i < size; i++)
        printf("%d ",container[i].weight);
    printf("\n");
}


// find & unite algorithm
int find(int i, int *parent)
{
    if(parent[i] == -1)
        return i;
    return parent[i] = find(parent[i], parent);
}

void unite(int x, int y, Dsu *dsu)
{
    int s1 = find(x, dsu->parent);
    int s2 = find(y, dsu->parent);
    if(s1 != s2)
    {
        if(dsu->rank[s1] < dsu->rank[s2])
        {
            dsu->parent[s1] = s2;
            dsu->rank[s2] += dsu->rank[s1];
        }
        else
        {
            dsu->parent[s2] = s1;
            dsu->rank[s1] += dsu->rank[s2];
        }
    }
}


//init
void dsu_init(Dsu **dsu,int size)
{
    (*dsu) = malloc(sizeof(Dsu));
    (*dsu)->parent = malloc(sizeof(int) * size);
    (*dsu)->rank = malloc(sizeof(int) * size);
    for(int i = 0; i < size; i++){
        (*dsu)->parent[i] = -1;
        (*dsu)->rank[i] = 1;
    }
}

void container_init(GraphVertex **container, LinkedList *list)
{
    *container = malloc(sizeof(GraphVertex) * list->headerNode.data.count);
    ListNode *pointer = list->headerNode.pLink, *pointer2;
    GraphVertex *iter = *container;
    for(;pointer;)
    {
        pointer2 = pointer->head;
        while(pointer2)
        {
            *iter++ = pointer2->data;
            pointer2 = pointer2->head;
        }
        pointer = pointer->pLink;
    }
}

void swap(GraphVertex *container, GraphVertex *container2)
{
    GraphVertex container3 = *container;
    *container = *container2;
    *container2 = container3;
}

//bubble sort
void container_sort2(GraphVertex *container, int size)
{
    int flag;

    for (int i = 0; i < size; i++)
    {
        flag = 0;
        for (int j = i + 1; j < size; j++)
        {
            if((container + i)->weight > (container + j)->weight)
            {
                swap(container + i, container + j);
                //swap(&container[i], &container[j]);
                flag = 1;
            }
        }
        if (!flag) // issorted
            break;
    }
}

//select sort
void container_sort3(GraphVertex *container, int size)
{
    int pos;
    int k;
    int mid;

    mid = (float)size / 2 + 0.5;
    print_container(container, size);
    for (int i = 0; i < mid; i++)
    {
        pos = k = i;
        for (int j = i + 1; j < size - i; j++)
        {
            if((container + pos)->weight > (container + j)->weight)
                pos = j;
            else if((container + k)->weight < (container + j)->weight)
                k = j;
        }
        if (pos == i) // issorted
            break;
        else
        {
            swap(container + i, container + pos);
            if(k != i)
                swap(container + size - 1 - i, container + k);
            else
                swap(container + size - 1 - i, container + pos);
        }
    }
    print_container(container, size);
}

int medianThree(int a, int b, int c) {
    if ((a > b) ^ (a > c))
        return a;
    else if ((b < a) ^ (b < c)) 
        return b;
    else
        return c;
}

int findMedian(GraphVertex *container, int n)
{
    if (n == 3)
        return medianThree(container->weight, (container + 1)->weight, (container + 2)->weight);
    return container->weight;
}

int partition(GraphVertex *container, int l, int r, int x)
{
    int i = 0;
    for(i =l;i<r;i++)
        if((container+i)->weight == x)
            break;
    swap(container + i, container + r);
    i = l;
    for(int j = l; j<= r-1;j++)
    {
        if((container + j)->weight <= x)
        {
            swap(container + i, container + j);
            i++;
        }
    }
    swap(container + i, container + r);
    return i;
}

int kthSmallest(GraphVertex *container, int l, int r, int k)
{
    if(k > 0 && k <= r - l + 1)
    {
        int n = r-l+1;
        int i;
        GraphVertex *median = malloc((n+2)/3 * sizeof(GraphVertex));

        for(i = 0; i<n/3;i++)
            (median +i)->weight = findMedian(container+l+i*3, 3);
        if(i*3<n)
        {
            (median+i)->weight = findMedian(container+l+i*3, n%3);
            i++;
        }
        int medOfMEd = (i == 1) ? (median + i - 1)->weight : kthSmallest(median, 0, i-1, i/2);
        free(median);
        int pos = partition(container, l, r, medOfMEd);
        if(pos-l == k-1)
            return (container + pos)->weight;
        if(pos-l > k-1)
            return kthSmallest(container, l, pos-1, k);
        else
            return kthSmallest(container, pos+1,r, k-pos+l-1);
    }
    return -1;
}

void quickSort(GraphVertex *container, int l, int h)
{
    if(l < h)
    {
        int n = h-1+1;
        int med = kthSmallest(container, l, h, n/2);
        int p = partition(container, l, h, med);
        quickSort(container, l, p-1);
        quickSort(container, p+1, h);
    }
}

//quick sort
/*
randomly picking up
using insertion sort for small sized array to reduce recursive calls.
tail recursive
intro sort
*/
void container_sort(GraphVertex *container, int size)
{
    quickSort(container, 0, size - 1);
    print_container(container, size);
    printf("\n");
}

//insertion sort
void container_sort4(GraphVertex *container, int size)
{
    int i, j;
    GraphVertex key;
    for(i = 1; i < size; i++)
    {
        key= *(container + i);
        j = i - 1;
        while(j >= 0 && (container + j)->weight > key.weight)
        {
            *(container + j + 1) = *(container + j);
            j--;
        }
        *(container + j + 1) = key;
    }
}

void merge(GraphVertex *container, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    GraphVertex L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = container[l + i];
    for (j = 0; j < n2; j++)
        R[j] = container[m + 1 + j];
 
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].weight <= R[j].weight) {
            container[k] = L[i];
            i++;
        }
        else {
            container[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        container[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        container[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(GraphVertex *container, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(container, l, m);
        mergeSort(container, m + 1, r);

        merge(container, l, m, r);
    }
}

//merge sort
void container_sort5(GraphVertex *container, int size)
{
    mergeSort(container, 0, size -1);
}

//heap sort
void container_sort6(GraphVertex *container, int size)
{

}

//radix sort
void container_sort7(GraphVertex *container, int size)
{

}

void kruskalV2(LinkedList *list)
{
    Dsu *s;
    GraphVertex *container;
    int ans;

    ans = 0;
    dsu_init(&s, list->currentElementCount);
    container_init(&container, list);
    container_sort5(container, list->headerNode.data.count);
    for(int i = 0; i < list->headerNode.data.count; i++)
    {
        if(find((container + i)->vertexID, s->parent) != find((container + i)->parent_ID, s->parent))
        {
            unite((container + i)->parent_ID, (container + i)->vertexID, s);
            ans += (container + i)->weight;
            printf("%d -- %d == %d\n", (container + i)->parent_ID, (container + i)->vertexID, (container + i)->weight);
        }
    }
    printf("minimum cost spanning tree: %d\n", ans);
    free(s->parent);
    free(s->rank);
    free(s);
    free(container);
}

int main()
{
    LinkedList *list = createLinkedList();
    ListNode element;
    GraphVertex g;
    element.pLink = 0;
	g.weight = 0;
    g.count = 0;
    g.parent_ID = 0;
    g.vertexID = 1;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 2;
    element.data = g;
    addLLElement(list,1,element);
    g.vertexID = 3;
    element.data = g;
    addLLElement(list,2,element);
    g.vertexID = 4;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 5;
    element.data = g;
    addLLElement(list,100,element);
    g.vertexID = 0;
    element.data = g;
    addLLElement(list,0,element);
    g.vertexID = 6;
    element.data = g;
    addLLElement(list,100,element);
    addLLEEdge(list,0,0,99);
    addLLEEdge(list,0,6,99);
    addLLEEdge(list,0,3,99);
    addLLEEdge(list,0,1,1);
    addLLEEdge(list,0,1,6);
    addLLEEdge(list,0,2,99);
    addLLEEdge(list,1,2,2);
    addLLEEdge(list,1,2,3);
    addLLEEdge(list,1,3,4);
    addLLEEdge(list,1,4,99);
    addLLEEdge(list,2,4,5);
    addLLEEdge(list,3,5,6);
    addLLEEdge(list,4,6,7);
    addLLEEdge(list,5,1,8);
    addLLEEdge(list,6,2,9);
    addLLEEdge(list,6,3,10);
    addLLEEdge(list,7,4,11);
    addLLEEdge(list,7,5,12);
    
    //addLLEEdge(list,0,2,3);
    //addLLEEdge(list,1,2,2);
    //addLLEEdge(list,3,5,5);
    //addLLEEdge(list,4,5,6);
    //addLLEEdge(list,0,1,4);
    //addLLEEdge(list,2,3,1);
    //addLLEEdge(list,4,3,1);
    print_list(list);
    kruskalV2(list);
    deleteLinkedList(&list);
    //gcc -g -fsanitize=address -Wall -Wextra -Werror kruskalv2.c
    //gcc -Wall -Wextra -Werror kruskalV2.c
    //system("leaks a.out");
    return (0);
}