#include "bintree.h"

BinTree* makeBinTree(BinTreeNode rootNode)
{
    BinTree *newTree;

    newTree = calloc(1, sizeof(BinTree));
    newTree->pRootNode = calloc(1, sizeof(BinTreeNode));
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
    pParentNode->pLeftChild = calloc(1, sizeof(BinTreeNode));
    *(pParentNode->pLeftChild) = element;
    return (pParentNode->pLeftChild);
}
BinTreeNode* insertRightChildNodeBT(BinTreeNode* pParentNode, BinTreeNode element)
{
    if (pParentNode->pRightChild != NULL)
        return (NULL);
    pParentNode->pRightChild = calloc(1, sizeof(BinTreeNode));
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

void deleteBinTreeNode(BinTreeNode** pNode)
{
    free(*pNode);
    *pNode = NULL;
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
    if (root == NULL)
        return ;
    postOrderTraversalBinTree(root->pLeftChild);
    postOrderTraversalBinTree(root->pRightChild);
    printf("%c ", root->data);
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
    preOrderTraversalBinTree(tree->pRootNode);
    printf("\n");
    inOrderTraversalBinTree(tree->pRootNode);
    printf("\n");
    postOrderTraversalBinTree(tree->pRootNode);
    printf("\n");
    deleteBinTree(&tree);
    system("leaks a.out");
    return (0);
}