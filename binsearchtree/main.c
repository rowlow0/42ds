#include	"bin_search_tree.h"
#include    "bintree.c"
// 트리 생성
// 검색
// 자료 추가
// 자료 제거

BinTree* makeBinSearchTree(BinTreeNode rootNode)
{
    BinTree *newTree;

    newTree = malloc(sizeof(BinTree));
    newTree->pRootNode = calloc(1, sizeof(BinTreeNode));
    newTree->pRootNode->key = rootNode.key;
    newTree->pRootNode->data = rootNode.data;
    newTree->pRootNode->parent = 0;
    return(newTree);
}


BinTreeNode	*searchBinTreeNode(BinTree *tree, int key)
{
	BinTreeNode	* result = tree->pRootNode;
	while(result != NULL)
	{
		if (key == result->key)
			break;
		else if (key < result->key)
			result = result ->pLeftChild;
		else
			result = result ->pRightChild;
	}
	return result;
}

BinTreeNode *insertUtiRecurssive(BinTreeNode *root, int key, BinTreeNode *root2)
{
    if(!root)
        return (root2);
    if (key < root->key)
        root = insertUtiRecurssive(root->pLeftChild, key, root);
    else
        root = insertUtiRecurssive(root->pRightChild, key, root);
    return root;
}

BinTreeNode *insertBinSearchTree(BinTree *tree, BinTreeNode element)
{
    if (!searchBinTreeNode(tree, element.key))
    {
        BinTreeNode *pParentNode = insertUtiRecurssive(tree->pRootNode, element.key, 0);
        BinTreeNode *tmp = calloc(1, sizeof(BinTreeNode));
        tmp->data = element.data;
        tmp->key = element.data;
        tmp->parent = pParentNode;
        if(pParentNode->key >element.key)
            pParentNode->pLeftChild = tmp;
        else
            pParentNode->pRightChild = tmp;
        return (tmp);
    }
    else
        return (NULL);
	// 같은 노드가 있는지 search
	// 있다면 printf("fail to insert : same key\n");
	// key < element->key
	// 	search(element->left, key);
	// else
	// 	search(element->right, key);
	// return;
}

static BinTreeNode* find_minimum_search(BinTreeNode* pNode)
{
    while (pNode ->pLeftChild)
		pNode = pNode->pLeftChild;
    return (pNode);
}

void deleteBinSearchTreeNode(BinTreeNode* pNode, BinTree *tree)
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
        BinTreeNode *t = find_minimum_search(pNode->pRightChild);
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


//stack
void preOrder2B(BinTreeNode *root)
{
    BinTreeNode *s = NULL;
    int         done = 1;
      while(done)
      {
          if(root)
          {
            printf("%d ",root->key);
            root->parent = s;
            s = root; // push
            root = root->pLeftChild;
          }
          else
          {
              if(s)
              {
                root = s;
                s = s->parent; // pop
                root = root->pRightChild;
              }
              else
                done = 0;
          }
      }
      printf("\n");
}

//iterator
void inOrderB(BinTreeNode* root)
{
    if (!root)
        return;
    while (root)
    {
        if (root->pLeftChild == NULL)
        {
            printf("%d ", root->key);
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
                printf("%d ", root->key);
                root = root->pRightChild;
            }
        }
    }
    printf("\n");
}

//stack
void postOrder2B(BinTreeNode *root)
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
              printf("%d ", root->key);
              root = NULL;
          }
      }while(s);
      printf("\n");
}

int main()
{
    BinTreeNode root;
    root.key = 10;
    BinTree *tree = makeBinSearchTree(root);
    root.key = 15;
    insertBinSearchTree(tree, root);
    root.key = 20;
    insertBinSearchTree(tree, root);
    root.key = 5;
    insertBinSearchTree(tree, root);
    root.key = 0;
    insertBinSearchTree(tree, root);
    root.key = -5;
    insertBinSearchTree(tree, root);
        preOrder2B(tree->pRootNode);
    inOrderB(tree->pRootNode);
    postOrder2B(tree->pRootNode);
    deleteBinTree2(&tree);
    system("leaks a.out");
    return (0);
}