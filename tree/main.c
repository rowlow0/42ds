#include "bintree.h"
//malloc
BinTree* makeBinTree(BinTreeNode rootNode)
{
    BinTree *newTree;
    newTree = malloc(sizeof(BinTree *));
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
    if (!pParentNode || pParentNode->pLeftChild)
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

//malloc2
BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    if (!pParentNode || pParentNode->pRightChild)
        return (NULL);
    pParentNode->pRightChild = malloc(sizeof(BinTreeNode));
    *(pParentNode->pRightChild) = element;
    pParentNode->pRightChild->parent = pParentNode;
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
    if (!pBinTree || !(*pBinTree))
        return ;
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
    if (*pBinTree && pBinTree) // *pBinTree == NULL  // pBinTree NULL
    {
        if ((*pBinTree)->pRootNode)
            deleteAllNode2((*pBinTree)->pRootNode);
        free(*pBinTree);
        *pBinTree = NULL;
    }
}

//count node

void dequeue_count(queue *q)
{
    q->front = q->front->next;
    q->i--;
}

int count_node(BinTreeNode* pParentNode)
{
    int i = 0;
    if (pParentNode)
    {
        queue *q = create(pParentNode);
        while (!empty(q))
        {
            if (q->front->pLeftChild)
                enqueue(q, q->front->pLeftChild);
            if (q->front->pRightChild)
                enqueue(q, q->front->pRightChild);
            dequeue_count(q);
            i++;
        }
        free(q);
    }
    return (i);
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
        if (pNode->parent == 0)
            tree->pRootNode->data = next->data;
        else if(pNode->parent->pLeftChild == pNode)
            pNode->data = next->data;
        else
            pNode->data = next->data;
        pNode->pLeftChild = 0;
        pNode->pRightChild = 0;
        free(next);
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
        return ;
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
    while (root)
    {
        if (root->pLeftChild == NULL)
        {
            printf("%c ", root->data);
            root = root->pRightChild;
        }
        else
        {
            BinTreeNode *pre = root->pLeftChild;
            while (pre->pRightChild && pre->pRightChild != root)
                pre = pre->pRightChild;
            if (!pre->pRightChild)
            {
                pre->pRightChild = root;
                root = root->pLeftChild;
            }
            else
            {
                pre->pRightChild = NULL;
                printf("%c ", root->data);
                root = root->pRightChild;
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
    int         done = 1;
      while(done)
      {
          if(root)
          {
            printf("%c ",root->data);
            root->parent = s;
            s = root; // push
            root = root->pLeftChild;
          }
          else
          {
              if(s)
              {
                root = s->pRightChild;
                s = s->parent; // pop
              }
              else
                done = 0;
          }
      }
      printf("\n");
}

//stack
void inOrder2(BinTreeNode *root)
{
      BinTreeNode *cursor = NULL;
      while(1)
      {
          if(root)
          {
              root->parent = cursor;
              cursor = root; // push
              root = root->pLeftChild;
          }
          else
          {
              if(cursor)
              {
                printf("%c ",cursor->data);
                root = cursor->pRightChild;
                cursor = cursor->parent; //pop
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
          while(root) // go to left
          {
            if(root->pRightChild)
            {
                root->pRightChild->parent = s;
                s = root->pRightChild;
            } // set as root->pRightChild as parent of root
            root->parent = s; 
            s = root; // push
            root = root->pLeftChild;
          }
          root = s;
          s = s->parent; // pop
          if (root->pRightChild && s == root->pRightChild) // if (root has right child)
          {
              root->parent = s->parent;
              s = root; // push
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

int height(BinTreeNode *node)
{
    if (!node)
        return 0;
    else
    {
        int lheight = height(node->pLeftChild);
        int rheight = height(node->pRightChild);
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

//traverse4

void    printf_level(BinTreeNode *node, int level)
{
    if (!node)
        return ;
    if (level == 1)
        printf("%c ", node->data);
    else if (level > 1)
    {
        printf_level(node->pLeftChild, level - 1);
        printf_level(node->pRightChild, level - 1);
    }
}

//recurssive
void    levelorder(BinTreeNode *root)
{
    int h = height(root);
    for (int i = 1; i <= h; i++)
        printf_level(root, i);
    printf("\n");
}

//deepcopy
BinTreeNode * deepcopy_recurssive(BinTreeNode *root)
{
    if (root == NULL)
        return NULL;
    BinTreeNode *node = malloc(sizeof(BinTreeNode));
    node->data = root->data;
    node->next = 0;
    node->visited = 0;
    node->parent = root;
    node->pLeftChild = deepcopy_recurssive(root->pLeftChild);
    node->pRightChild = deepcopy_recurssive(root->pRightChild);
    return node;
}

void    deepcopy(BinTree **tree, BinTreeNode *root)
{
    *tree = malloc(sizeof(BinTree *));
    (*tree)->pRootNode = deepcopy_recurssive(root);
}

//deepcopy without recurssive

//level order without recurssive
/*
    void levelorder2()
    {

    }
*/

// for balance of tree (AVL)
/*
is_binary
*/

//rotate && arranagement
/*
*/
int main()
{
    //init
    BinTree *tree;
    BinTree *tree2;
    BinTreeNode t;
    t.next = 0;
    t.parent = 0;
    t.pLeftChild = 0;
    t.pRightChild = 0;
    t.visited = 0;
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
    printf("preorder  : ");preOrder(tree->pRootNode);
    //inOrderTraversalBinTree(tree->pRootNode);printf("\n");
    printf("inorder   : ");inOrder(tree->pRootNode);
    //postOrderTraversalBinTree(tree->pRootNode);printf("\n");
    printf("postorder : ");postOrder(tree->pRootNode);
    printf("levelorder : ");levelorder(tree->pRootNode);
    printf("height : %d\n",height(tree->pRootNode));
    printf("count : %d\n",count_node(tree->pRootNode));

    //
    deepcopy(&tree2, tree->pRootNode);
    //deepcopy!
    deleteBinTree2(&tree); //deleteBinTree(&tree);
    //

    printf("preorder  : ");preOrder(tree2->pRootNode);
    //inOrderTraversalBinTree(tree->pRootNode);printf("\n");
    printf("inorder   : ");inOrder(tree2->pRootNode);
    //postOrderTraversalBinTree(tree->pRootNode);printf("\n");
    printf("postorder : ");postOrder(tree2->pRootNode);
    printf("levelorder : ");levelorder(tree2->pRootNode);
    printf("height : %d\n",height(tree2->pRootNode));
    printf("count : %d\n",count_node(tree2->pRootNode));
    deleteBinTree2(&tree2);

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
    preOrder(tree->pRootNode);
    deleteBinTreeNode(tree->pRootNode->pLeftChild,tree);
    inOrder(tree->pRootNode);
    deleteBinTree2(&tree);
    /*
    tree = 0;
    deleteBinTree2(0);
    */
    printf("==============================================\n");
    t.data = 'A';
    tree =  makeBinTree(t);
    t.data = 'B';
    insertLeftChildNodeBT(tree->pRootNode,t);
    t.data = 'C';
    insertRightChildNodeBT(tree->pRootNode,t);
    t.data = 'D';
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild,t);
    t.data = 'E';
    insertRightChildNodeBT(tree->pRootNode->pLeftChild,t);
    t.data = 'J';
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild->pRightChild,t);
    t.data = 'F';
    insertLeftChildNodeBT(tree->pRootNode->pRightChild,t);
    t.data = 'K';
    insertRightChildNodeBT(tree->pRootNode->pRightChild->pLeftChild,t);
    t.data = 'G';
    insertRightChildNodeBT(tree->pRootNode->pRightChild,t);
    t.data = 'L';
    insertLeftChildNodeBT(tree->pRootNode->pRightChild->pRightChild,t);
    t.data = 'M';
    insertRightChildNodeBT(tree->pRootNode->pRightChild->pRightChild,t);
    t.data = 'H';
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild->pLeftChild,t);
    t.data = 'I';
    insertRightChildNodeBT(tree->pRootNode->pLeftChild->pLeftChild,t);
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
    system("leaks a.out");
    return (0);
}
