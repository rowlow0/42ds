#include "bintree.h"

BinTree* makeBinTree(BinTreeNode rootNode)
{
    BinTree *newTree;

    newTree = malloc(sizeof(BinTree));
    newTree->pRootNode = malloc(sizeof(BinTreeNode));
    newTree->pRootNode->data = rootNode.data;
    newTree->pRootNode->pLeftChild = 0;
    newTree->pRootNode->pRightChild = 0;
    newTree->pRootNode->next = 0;
    newTree->pRootNode->visited = 0;
    newTree->pRootNode->parent = 0;
    return(newTree);
}

/*
BinTreeNode* getRootNodeBT(BinTree* pBinTree)
{
    if(pBinTree && pBinTree->pRootNode)
        return (pBinTree->pRootNode);
    return (NULL);
}
*/

//calloc
BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    if (pParentNode->pLeftChild)
        return (NULL);
    pParentNode->pLeftChild = calloc(1, sizeof(BinTreeNode));
    pParentNode->pLeftChild->data = element.data;
    pParentNode->pLeftChild->parent = pParentNode;
    /*
    pParentNode->pLeftChild->pLeftChild = 0;
    pParentNode->pLeftChild->pRightChild = 0;
    pParentNode->pLeftChild->next = 0;
    pParentNode->pLeftChild->visited = 0;
    */
    return (pParentNode->pLeftChild);
}

//malloc
BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    if (pParentNode->pRightChild)
        return (NULL);
    pParentNode->pRightChild = malloc(sizeof(BinTreeNode));
    pParentNode->pRightChild->data = element.data;
    pParentNode->pRightChild->parent = pParentNode;
    pParentNode->pRightChild->pLeftChild = 0;
    pParentNode->pRightChild->pRightChild = 0;
    pParentNode->pRightChild->next = 0;
    pParentNode->pRightChild->visited = 0;
    return (pParentNode->pRightChild);
}

/*
BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode)
{
    if (pNode && pNode->pLeftChild)
        return (pNode->pLeftChild);
    return (NULL);
}
*/

/*
BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode)
{
    return (pNode->pRightChild);
    
    //if (pNode && pNode->pRightChild)
        //return (NULL);
    
}
*/

void deleteBinTree(BinTree** pBinTree)
{
    if (!pBinTree)
        return ;
    if ((*pBinTree)->pRootNode)
        deleteAllNode((*pBinTree)->pRootNode);
    free(*pBinTree);
    *pBinTree = NULL;
}

//post order
void  deleteAllNode(BinTreeNode *root)
{
    if (root == NULL)
        return;
    deleteAllNode(root->pLeftChild);
    deleteAllNode(root->pRightChild);
    free(root);
}

//delete Queue without recussive method
typedef struct Queue
{
    int         i;
	BinTreeNode *front;
    BinTreeNode *rear;
} queue;

queue *create(BinTreeNode * node)
{
    queue *q = malloc(sizeof(queue));
    q->rear = node;
    q->front = node;
    q->i = 1;
    return q;
}

void enqueue(queue *q, BinTreeNode *node)
{
    q->rear->next = node;
    q->rear = node;
    q->i++;
}

void dequeue(queue *q)
{
    BinTreeNode *t = q->front;
    q->front = q->front->next;
    free(t);
    q->i--;
}

int empty(queue *q)
{
    return q->i == 0;
}

void  deleteAllNode2(BinTreeNode *root)
{
    queue *q = create(root);
    while(!empty(q))
    {
        if (q->front->pLeftChild)
            enqueue(q, q->front->pLeftChild);
        if (q->front->pRightChild)
            enqueue(q, q->front->pRightChild);
        dequeue(q);
    }
    free(q);
}

void deleteBinTree2(BinTree** pBinTree)
{
    if (pBinTree)
    {
        if ((*pBinTree)->pRootNode)
            deleteAllNode2((*pBinTree)->pRootNode);
        free(*pBinTree);
        *pBinTree = NULL;
    }
}

//delete node

//binary tree
BinTreeNode* find_minimum(BinTreeNode* pNode)
{
    while (pNode ->pLeftChild)
        pNode = pNode->pLeftChild;
    return (pNode);
}

//node
void deleteBinTreeNode(BinTreeNode* pNode, BinTree *tree)
{
    if (!pNode)
        ;
        //zero
    else if (!pNode->pLeftChild && !pNode->pRightChild)
    {
        if (pNode == tree->pRootNode)
            tree->pRootNode = 0;
        else if (pNode->parent->pLeftChild == pNode)
            pNode->parent->pLeftChild = 0;
        else if (pNode->parent->pRightChild == pNode)
            pNode->parent->pRightChild = 0;
        free(pNode);
    }
        //two
    else if (pNode->pLeftChild && pNode->pRightChild)
    {
        BinTreeNode *t = find_minimum(pNode->pRightChild);
        pNode->data = t->data;
        if(t != pNode->pRightChild)
        {
            t->parent->pLeftChild = 0;
            free(t);
        }
        else
        {
            free(t);
            pNode->pRightChild = 0;
        }
    }
        //one
    else
    {
        BinTreeNode* next = pNode->pLeftChild ? pNode->pLeftChild : pNode->pRightChild;
        BinTreeNode*t = pNode;
        if (pNode->parent == 0)
            tree->pRootNode = next;
        else if(pNode->parent->pLeftChild == pNode)
            pNode->parent->pLeftChild = next;
        else
            pNode->parent->pRightChild = next;
        free(t);
    }
}

//value
/*
void deleteBinTreeNode2(BinTreeNode** pNode, char c, BinTree *root)
{
    if (pNode)
    {
        free(*pNode);
        *pNode = NULL;
    }
}
*/

//traverse

//recursive
void preOrderTraversalBinTree(BinTreeNode *root)
{
    if (root == NULL)
        return;
    printf("%c ", root->data);
    preOrderTraversalBinTree(root->pLeftChild);
    preOrderTraversalBinTree(root->pRightChild);
}

//recursive
void inOrderTraversalBinTree(BinTreeNode *root)
{
    if (root == NULL)
        return ;
    inOrderTraversalBinTree(root->pLeftChild);
    printf("%c ", root->data);
    inOrderTraversalBinTree(root->pRightChild);
}

//recursive
void postOrderTraversalBinTree(BinTreeNode *root)
{
    if (root)
    {
        postOrderTraversalBinTree(root->pLeftChild);
        postOrderTraversalBinTree(root->pRightChild);
        printf("%c ", root->data);
    }
}

//traverse2

//iterator
void preOrder(BinTreeNode *root)
{
    while (root)
    {
        if (root->pLeftChild == NULL)
        {
            printf( "%c ", root->data);
            root = root->pRightChild;
        }
        else
        {
            BinTreeNode* current = root->pLeftChild;
                while (current->pRightChild && current->pRightChild != root)
                    current = current->pRightChild;
            if (current->pRightChild == root)
            {
                current->pRightChild = NULL;
                root = root->pRightChild;
            }
            else
            {
                printf("%c ", root->data);
                current->pRightChild = root;
                root = root->pLeftChild;
            }
        }
    }
    printf("\n");
}

//iterator
void inOrder(BinTreeNode* root)
{
    if (!root)
        return;
    BinTreeNode *current = root, *pre;
    while (current) {
        if (!current->pLeftChild) {
            printf("%c ", current->data);
            current = current->pRightChild;
        }
        else {
            pre = current->pLeftChild;
                while (pre->pRightChild && pre->pRightChild != current)
                    pre = pre->pRightChild;
            if (!pre->pRightChild) {
                pre->pRightChild = current;
                current = current->pLeftChild;
            }
            else {
                pre->pRightChild = NULL;
                printf("%c ", current->data);
                current = current->pRightChild;
            }
        }
    }
    printf("\n");
}

//iterator
void postOrder(BinTreeNode *root)
{
    if (!root)
        return;
    char *result = malloc(10);
    int m = 0, mem = 10;
    while (root)
    {
        if (root->pRightChild == NULL)
        {
            *(result + m++) = root->data;
            root = root->pLeftChild;
        }
        else
        {
            BinTreeNode* predecessor = root->pRightChild;
            while (predecessor->pLeftChild && predecessor->pLeftChild != root)
                predecessor = predecessor->pLeftChild;
            if (predecessor->pLeftChild == NULL)
            {
                *(result + m++) = root->data;
                predecessor->pLeftChild = root;
                root = root->pRightChild;
            }
            else
            {
                predecessor->pLeftChild = NULL;
                root = root->pLeftChild;
            }
        }
        //realloc
        if (m >= mem)
        {
            mem *= 3;
            result = realloc(result, mem);
        }
    }

    //reverse
    for (int i = 0, j = m - 1; i < m / 2; i++, j--)
    {
        char tmp = *(result + i);
        *(result + i) = *(result + j);
        *(result + j) = tmp;
    }

    //traverse
    for ( int  i = 0; i < m; i++)
        printf("%c ", *(result + i));
    printf("\n");
    free(result);
}

//traverse3

//stack
void preOrder2(BinTreeNode *root)
{
    BinTreeNode *s = NULL;
      while(1)
      {
          if(root)
          {
            printf("%c ",root->data);
              root->parent = s;
              s = root;
              root = root->pLeftChild;
          }
          else
          {
              if(s)
              {
                root = s;
                s = s->parent;
                root = root->pRightChild;
              }
              else
                break;
          }
      }
      printf("\n");
}

//stack
void inOrder2(BinTreeNode *root)
{
      BinTreeNode *s = NULL;
      while(1)
      {
          if(root)
          {
              root->parent = s;
              s = root;
              root = root->pLeftChild;
          }
          else
          {
              if(s)
              {
                root = s;
                s = s->parent;
                printf("%c ",root->data);
                root = root->pRightChild;
              }
              else
                break;
          }
      }
      printf("\n");
}

//stack
void postOrder2(BinTreeNode *root)
{
      BinTreeNode *s = NULL;
      do
      {
          while(root)
          {
            if(root->pRightChild)
            {
                root->pRightChild->parent = s;
                s = root->pRightChild;
            }
            root->parent = s;
            s = root;
            root = root->pLeftChild;
          }
          root = s;
          s = s->parent;
          if (root->pRightChild && s == root->pRightChild)
          {
              s = s->parent;
              root->parent = s;
              s = root;
              root = root->pRightChild;
          }
          else
          {
              printf("%c ", root->data);
              root = NULL;
          }
      }while(s);
      printf("\n");
}

/*
//rotate && arranagement for balance of tree
*/
int main()
{
    //init
    BinTree *tree;
    BinTreeNode t;
    t.data = '1';
    tree =  makeBinTree(t);
    t.data = '2';
    insertLeftChildNodeBT(tree->pRootNode,t);
    t.data = '3';
    insertRightChildNodeBT(tree->pRootNode,t);
    t.data = '4';
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild,t);
    t.data = '5';
    insertRightChildNodeBT(tree->pRootNode->pLeftChild,t);
    t.data = '6';
    insertLeftChildNodeBT(tree->pRootNode->pRightChild,t);
    t.data = '7';
    insertRightChildNodeBT(tree->pRootNode->pRightChild,t);
    t.data = '8';
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild->pLeftChild,t);
    //preOrderTraversalBinTree(tree->pRootNode);printf("\n");
    preOrder(tree->pRootNode);
    //inOrderTraversalBinTree(tree->pRootNode);printf("\n");
    inOrder(tree->pRootNode);
    //postOrderTraversalBinTree(tree->pRootNode);printf("\n");
    postOrder(tree->pRootNode);
    deleteBinTree2(&tree); //deleteBinTree(&tree);

    printf("==============================================\n");

    t.data = '1';
    tree =  makeBinTree(t);
    inOrder(tree->pRootNode);
    inOrder2(tree->pRootNode);
    deleteBinTreeNode(tree->pRootNode,tree);
    deleteBinTree2(&tree);

    printf("==============================================\n");
    t.data = '1';
    tree =  makeBinTree(t);
    inOrder(tree->pRootNode);
    t.data = '2';
    insertLeftChildNodeBT(tree->pRootNode,t);
    t.data = '3';
    insertRightChildNodeBT(tree->pRootNode,t);
    t.data = '4';
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild,t);
    t.data = '5';
    insertRightChildNodeBT(tree->pRootNode->pLeftChild,t);
    t.data = '6';
    insertLeftChildNodeBT(tree->pRootNode->pRightChild,t);
    t.data = '7';
    insertRightChildNodeBT(tree->pRootNode->pRightChild,t);
    t.data = '8';
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild->pLeftChild,t);
    deleteBinTreeNode(tree->pRootNode,tree);
    deleteBinTreeNode(tree->pRootNode->pLeftChild,tree);
    deleteBinTreeNode(tree->pRootNode->pLeftChild->pLeftChild,tree);

    //preOrderTraversalBinTree(tree->pRootNode);printf("\n");
    preOrder(tree->pRootNode);
    //inOrderTraversalBinTree(tree->pRootNode);printf("\n");
    inOrder(tree->pRootNode);
    //postOrderTraversalBinTree(tree->pRootNode);printf("\n");
    postOrder(tree->pRootNode);
    deleteBinTree2(&tree);
    printf("==============================================\n");
    t.data = '1';
    tree =  makeBinTree(t);
    t.data = '2';
    insertLeftChildNodeBT(tree->pRootNode,t);
    t.data = '3';
    insertRightChildNodeBT(tree->pRootNode,t);
    t.data = '4';
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild,t);
    t.data = '5';
    insertRightChildNodeBT(tree->pRootNode->pLeftChild,t);
    t.data = '6';
    insertLeftChildNodeBT(tree->pRootNode->pRightChild,t);
    t.data = '7';
    insertRightChildNodeBT(tree->pRootNode->pRightChild,t);
    t.data = '8';
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild->pLeftChild,t);
    preOrderTraversalBinTree(tree->pRootNode);printf("\n");
    preOrder(tree->pRootNode);
    preOrder2(tree->pRootNode);
    inOrderTraversalBinTree(tree->pRootNode);printf("\n");
    inOrder(tree->pRootNode);
    inOrder2(tree->pRootNode);
    postOrderTraversalBinTree(tree->pRootNode);printf("\n");
    postOrder(tree->pRootNode);
    postOrder2(tree->pRootNode);
    deleteBinTree2(&tree);
    printf("==============================================\n");
    t.data = '1';
    tree =  makeBinTree(t);
    t.data = '2';
    insertLeftChildNodeBT(tree->pRootNode,t);
    t.data = '3';
    insertRightChildNodeBT(tree->pRootNode,t);
    deleteBinTreeNode(tree->pRootNode->pLeftChild,tree);
    inOrder(tree->pRootNode);
    deleteBinTree2(0);
    deleteBinTree2(&tree);
    system("leaks a.out");
    return (0);
}
