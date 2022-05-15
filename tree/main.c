#include "bintree.h"

BinTree* makeBinTree(BinTreeNode rootNode)
{
    BinTree *newTree;

    newTree = malloc(sizeof(BinTree));
    newTree->pRootNode = malloc(sizeof(BinTreeNode));
    *(newTree->pRootNode) = rootNode;
    return(newTree);
}

BinTreeNode* getRootNodeBT(BinTree* pBinTree)
{
    if(pBinTree && pBinTree->pRootNode)
        return (pBinTree->pRootNode);
    return (NULL);
}

BinTreeNode* insertLeftChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    if (pParentNode->pLeftChild != NULL)
        return (NULL);
    pParentNode->pLeftChild = malloc(sizeof(BinTreeNode));
    *(pParentNode->pLeftChild) = element;
    return (pParentNode->pLeftChild);
}

BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    if (pParentNode->pRightChild != NULL)
        return (NULL);
    pParentNode->pRightChild = malloc(sizeof(BinTreeNode));
    *(pParentNode->pRightChild) = element;
    return (pParentNode->pRightChild);
}

BinTreeNode* getLeftChildNodeBT(BinTreeNode* pNode)
{
    if (pNode && pNode->pLeftChild)
        return (pNode->pLeftChild);
    return (NULL);
}

BinTreeNode* getRightChildNodeBT(BinTreeNode* pNode)
{
    if (pNode && pNode->pRightChild)
        return (pNode->pRightChild);
    return (NULL);
}

void deleteBinTree(BinTree** pBinTree)
{
    BinTreeNode *rootNode;
    if (!pBinTree || !(*pBinTree) || !((*pBinTree)->pRootNode))
        return ;
    rootNode = (*pBinTree)->pRootNode;
    deleteAllNode(rootNode);
    free(*pBinTree);
    *pBinTree = NULL;
}

void  deleteAllNode(BinTreeNode *root)
{
    if (root == NULL)
        return;
    deleteAllNode(root->pLeftChild);
    deleteAllNode(root->pRightChild);
    free(root);
}

void  deleteAllNode2(BinTreeNode *root)
{
    if (root == NULL)
        return;
    deleteAllNode(root->pLeftChild);
    deleteAllNode(root->pRightChild);
    free(root);
}

//not working
void deleteBinTreeNode(BinTreeNode** pNode)
{
    if (*pNode)
    {
        free(*pNode);
        *pNode = NULL;
    }
}

void preOrderTraversalBinTree(BinTreeNode *root)
{
    if (root == NULL)
        return;
    printf("%c ", root->data);
    preOrderTraversalBinTree(root->pLeftChild);
    preOrderTraversalBinTree(root->pRightChild);
}

void inOrderTraversalBinTree(BinTreeNode *root)
{
    if (root == NULL)
        return ;
    inOrderTraversalBinTree(root->pLeftChild);
    printf("%c ", root->data);
    inOrderTraversalBinTree(root->pRightChild);
}

void postOrderTraversalBinTree(BinTreeNode *root)
{
    if (root)
    {
        postOrderTraversalBinTree(root->pLeftChild);
        postOrderTraversalBinTree(root->pRightChild);
        printf("%c ", root->data);
    }
}

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
            if (predecessor)
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

void sPreOrder(BinTreeNode *root)
{
    
}

void sInOrder(BinTreeNode *root)
{
    
}

void sPostOrder(BinTreeNode *root)
{
    
}

int main()
{
    BinTree *tree;
    BinTreeNode t;
    t.data = '1';
    t.visited = 0;
    tree =  makeBinTree(t);
    t.data = '2';
    t.visited = 0;
    insertLeftChildNodeBT(tree->pRootNode,t);
    t.data = '3';
    t.visited = 0;
    insertRightChildNodeBT(tree->pRootNode,t);
    t.data = '4';
    t.visited = 0;
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild,t);
    t.data = '5';
    t.visited = 0;
    insertRightChildNodeBT(tree->pRootNode->pLeftChild,t);
    t.data = '6';
    t.visited = 0;
    insertLeftChildNodeBT(tree->pRootNode->pRightChild,t);
    t.data = '7';
    t.visited = 0;
    insertRightChildNodeBT(tree->pRootNode->pRightChild,t);
    t.data = '8';
    t.visited = 0;
    insertLeftChildNodeBT(tree->pRootNode->pLeftChild->pLeftChild,t);
    preOrderTraversalBinTree(tree->pRootNode);printf("\n");
    preOrder(tree->pRootNode);
    inOrderTraversalBinTree(tree->pRootNode);printf("\n");
    inOrder(tree->pRootNode);
    postOrderTraversalBinTree(tree->pRootNode);printf("\n");
    postOrder(tree->pRootNode);
    deleteBinTree(&tree);
    system("leaks a.out");
    return (0);
}
