/*
 * BST.c
 *
 *  Created on: Apr 5, 2016
 *      Author: Dennis Chau
 */
#include<stdio.h>
#include<string.h>
#include <limits.h>
#include<math.h>
#include"BST.h"

/*  Given a binary tree, return true if a node
 with the target data is found in the tree. Recurs
 down the tree, chooses the left or right
 branch by comparing the target to each node.
*/
unsigned char BSTsearch(struct BSTnode* root,struct BSTnode* root_parent, int target,
					struct BSTnode** node_found_parent,struct BSTnode** node_found)
{
	// 1. Base case == empty tree
	// in that case, the target is not found so return false
	if (root == NULL)
	{
		return(0);
	}
	else
	{
		// 2. see if found here
		if (target == root->data)
		{
			*node_found = root;
			*node_found_parent = root_parent;
			return(1);
		}
		else
		{
			// 3. otherwise, decide to go down left or right and then recursively down the correct subtree
			if (target < root->data)
			{
				return(BSTsearch(root->left,root, target,&node_found_parent,&node_found));
			}
			else
			{
				return(BSTsearch(root->right,root, target,&node_found_parent,&node_found));
			}
		}
	}
}

/*
 Helper function that allocates a new node
 with the given data and NULL left and right
 pointers.
*/
struct BSTnode* BSTnewNode(int data)
{
  struct BSTnode* newnode = malloc(sizeof(struct BSTnode));    // "new" is like "malloc"
  newnode->data = data;
  newnode->left = NULL;
  newnode->right = NULL;

  return(newnode);
}

/*
 Give a binary search tree and a number, inserts a new node
 with the given number in the correct place in the tree.
 Returns the new root pointer which the caller should
 then use (the standard trick to avoid using reference
 parameters).
*/
struct BSTnode* BSTinsert(struct BSTnode* node, int data)
{
	// 1. If the tree is empty, return a new, single node
	if (node == NULL)
	{
		return(BSTnewNode(data));
	}
	else
	{
		// 2. Otherwise, recur down the tree
		if (data == node->data) // don't allow duplicate
		{
			return node;
		}
		else if (data < node->data)
		{
			node->left = BSTinsert(node->left, data);
		}
		else
		{
			node->right = BSTinsert(node->right, data);
		}

		return(node); // return the (UNCHANGED) node pointer
	}
}

/*
 Compute the number of nodes in a tree.
*/
int BSTsize(struct BSTnode* node)
{
	if (node == NULL)
	{
		return(0);
	}
	else
	{
		return(BSTsize(node->left) + 1 + BSTsize(node->right)); //remember add 1 for root
	}
}

/*
 Compute the "maxDepth" of a tree -- the number of nodes along
 the longest path from the root node down to the farthest leaf node.
*/
int BSTDepth(struct BSTnode* node, unsigned char tocheckMax)
{
	if (node == NULL)
	{
		return(0);
	}
	else
	{
		// compute the depth of each subtree
		int lDepth = BSTDepth(node->left,tocheckMax);
		int rDepth = BSTDepth(node->right,tocheckMax);

		/*  when reach leaf (no child),lDepth = rDepth = 0 ; so function will return 1 */
		if(tocheckMax) //MAX DEPTH
		{
			if (lDepth > rDepth) return(lDepth+1);
			else return(rDepth+1);
		}
		else //MIN DEPTH
		{
			if (lDepth < rDepth) return(lDepth+1);
			else return(rDepth+1);
		}
	}
}

/*
 Given a binary search tree, print out
 its data elements in increasing
 sorted order.
*/
void BSTinOrderTraversal(struct BSTnode* node)
{
  if (node == NULL) return;
  BSTinOrderTraversal(node->left);
  printf("%d ", node->data);
  BSTinOrderTraversal(node->right);
}

/* root -> left -> right */
void BSTpreOrderTraversal(struct BSTnode* node)
{
	if (node == NULL) return;
	printf("%d ", node->data);
	BSTpreOrderTraversal(node->left);
	BSTpreOrderTraversal(node->right);
}

struct BSTnode* BSTclone(struct BSTnode* root )
{
   if (root == NULL ) return root;

   //create new node and make it a copy of node pointed by root
   struct BSTnode *temp = (struct BSTnode*)malloc(sizeof(struct BSTnode)) ;
   temp->data = root->data;    //copying data
   temp->left = BSTclone(root ->left);    //cloning left child
   temp->right = BSTclone(root ->right);  //cloning right child
   return temp;
}

/* left -> right -> root */
void BSTpostOrderTraversal(struct BSTnode* node)
{
	if (node == NULL) return;
	BSTpostOrderTraversal(node->left);
	BSTpostOrderTraversal(node->right);
	printf("%d ", node->data);
}

/*  This function traverses tree in post order to
    to delete each and every node of the tree
    NOTE that caller need to set root to null after this function return */
void BSTdeleteTree(struct BSTnode* node)
{
    if (node == NULL) return;

    /* first delete both subtrees */
    BSTdeleteTree(node->left);
    BSTdeleteTree(node->right);

    /* then delete the node */
    printf("\n Deleting node: %d", node->data);
    free(node);
}

int BSTminValue(struct BSTnode* node)
{
  struct BSTnode* current = node;
  // loop down to find the leftmost leaf
  while (current->left != NULL)
  {
    current = current->left;
  }

  return(current->data);
}

int BSTmaxValue(struct BSTnode* node)
{
  struct BSTnode* current = node;
  // loop down to find the leftmost leaf
  while (current->right != NULL)
  {
    current = current->right;
  }

  return(current->data);
}

/*
 * utility helper function that traverses down the tree, keeping track of the narrowing min and max allowed values as it goes,
 * looking at each node only once.
 * The initial values for min and max should be INT_MIN and INT_MAX -- they narrow from there.
 * the very top node: the limit [INT_MIN ..INT_MAX]
 * traverse down next node on the right: [parentNode ..INT_MAX]
 * traverse down next node on the left: [INT_MIN ..parentNode]
 *  Returns true if the given tree is a BST and its
 *   values are >= min and <= max.
*/
int isBSTUtil(struct BSTnode* node, int min, int max)
{
	if (node==NULL) return(1);

	// false if this node violates the min/max constraint
	if (node->data < min || node->data > max) return(0);

	// otherwise check the subtrees recursively,
	// TIGHTENING the min or max constraint
	return
	(
		isBSTUtil(node->left, min, node->data) &&
		isBSTUtil(node->right, node->data, max)
	);
}

/*
 * Returns true if the given tree is a binary search tree (efficient version).
 * The initial values for min and max should be INT_MIN and INT_MAX -- they narrow from there.
*/
int isBST2(struct BSTnode* node)
{
  return(isBSTUtil(node, INT_MIN, INT_MAX));
}

/* deletes a node from the binary search tree
 * http://www.dailyfreecode.com/code/insert-delete-node-binary-search-tree-2843.aspx */
void BSTdeletenode (struct BSTnode **root, int num )
{
    unsigned char found ;
    struct BSTnode *parent, *x, *xsucc ;

    /* if tree is empty */
    if (*root == NULL )
    {
        printf ( "\nTree is empty" ) ;
        return ;
    }

    parent = x = NULL ;

    /* call to search function to find the node to be deleted */
    found = BSTsearch (root, NULL, num, &parent, &x) ;

    /* if the node to deleted is not found */
    if (found == 0)
    {
        printf ( "\nData to be deleted, not found" ) ;
        return ;
    }

    /* CASE 1: if the node to be deleted has TWO children
     * It's very complicated to remove node directly because we have 2 subtree to handle
     * instead, we "swap" it with  */
    if (x->left != NULL && x->right != NULL)
    {
    	/* http://www.algolist.net/Data_structures/Binary_search_tree/Removal
		 * find a minimum value in the right subtree
		 * replace value of the node to be removed with found minimum.
		 * Now,right subtree contains a duplicate!
		 * apply remove to the right subtree to remove a duplicate.*/
    	parent = x ;
        xsucc = x -> right;

        /* travel left to find minimum */
        while ( xsucc->left != NULL )
        {
            parent = xsucc ;
            xsucc = xsucc->left;
        }

        x->data = xsucc->data ;
        /* now x point to "minimum node in the right subtree" that need to be remove
         *  the node with minimum value has no left child (it it has, mean it's NOT the MIN value !?!)
         *  therefore, it's removal may result in CASE 2 or 3 below only  */
        x = xsucc ;
    }

    /*CASE 2: if the node to be deleted has NO child */
    if (x->left == NULL && x->right == NULL)
    {
        if (parent->right == x)
            parent->right = NULL ;
        else
            parent->left = NULL ;

        free (x) ;
        if (*root == x) *root = NULL;
        x = NULL;
        return ;
    }

    /*CASE 3a: if the node to be deleted has only RIGHT child */
    if (x->left == NULL && x -> right != NULL)
    {
        if ( parent->left == x )
            parent->left = x->right ;
        else
            parent->right = x->right;

        free (x) ;
        if (*root == x) *root = NULL;
        x = NULL;
        return ;
    }

    /*CASE 3b: if the node to be deleted has only LEFT child */
    if (x->left!= NULL && x -> right == NULL)
    {
        if ( parent->left == x )
            parent->left = x->left ;
        else
            parent->right = x->left ;

        free (x) ;
        if (*root == x) *root = NULL;
        x = NULL;
        return ;
    }
}

/*http://web.archive.org/web/20071224095835/http://www.openasthra.com/wp-content/uploads/2007/12/binary_trees1.c */

int MIN (int X, int Y)
{
  return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y)
{
  return ((X) > (Y)) ? (X) : (Y);
}

asciinode * build_ascii_tree_recursive(struct BSTnode * t)
{
	asciinode * node;
	if (t == NULL) return NULL;
	node = malloc(sizeof(asciinode));
	node->left = build_ascii_tree_recursive(t->left);
	node->right = build_ascii_tree_recursive(t->right);
	if (node->left != NULL)
	{
		node->left->parent_dir = -1;
	}

	if (node->right != NULL)
	{
		node->right->parent_dir = 1;
	}
	sprintf(node->label, "%d", t->data);
	node->lablen = strlen(node->label);
	return node;
}

//Copy the tree into the ascii node structre
asciinode * build_ascii_tree(struct BSTnode * t)
{
	asciinode *node;
	if (t == NULL) return NULL;
	node = build_ascii_tree_recursive(t);
	node->parent_dir = 0;
	return node;
}

//Free all the nodes of the given tree
void free_ascii_tree(asciinode *node)
{
	if (node == NULL) return;
	free_ascii_tree(node->left);
	free_ascii_tree(node->right);
	free(node);
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
void compute_lprofile(asciinode *node, int x, int y)
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
	if (node->left != NULL)
	{
		for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
	{
		lprofile[y+i] = MIN(lprofile[y+i], x-i);
	}
	}
	compute_lprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
	compute_lprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

void compute_rprofile(asciinode *node, int x, int y)
{
	int i, notleft;
	if (node == NULL) return;
	notleft = (node->parent_dir != -1);
	rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
	if (node->right != NULL)
	{
		for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++)
		{
			rprofile[y+i] = MAX(rprofile[y+i], x+i);
		}
	}
	compute_rprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
	compute_rprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

//This function fills in the edge_length and
//height fields of the specified tree
void compute_edge_lengths(asciinode *node)
{
	int h, hmin, i, delta;
	if (node == NULL) return;
	compute_edge_lengths(node->left);
	compute_edge_lengths(node->right);

	/* first fill in the edge_length of node */
	if (node->right == NULL && node->left == NULL)
	{
		node->edge_length = 0;
	}
	else
	{
		if (node->left != NULL)
		{
			for (i=0; i<node->left->height && i < MAX_HEIGHT; i++)
			{
				rprofile[i] = -INFINITY;
			}
			compute_rprofile(node->left, 0, 0);
			hmin = node->left->height;
		}
		else
		{
			hmin = 0;
		}

		if (node->right != NULL)
		{
			for (i=0; i<node->right->height && i < MAX_HEIGHT; i++)
			{
				lprofile[i] = INFINITY;
			}
			compute_lprofile(node->right, 0, 0);
			hmin = MIN(node->right->height, hmin);
		}
		else
		{
			hmin = 0;
		}
		delta = 4;
		for (i=0; i<hmin; i++)
		{
			delta = MAX(delta, GAP + 1 + rprofile[i] - lprofile[i]);
		}

		//If the node has two children of height 1, then we allow the
		//two leaves to be within 1, instead of 2
		if (((node->left != NULL && node->left->height == 1) ||
		  (node->right != NULL && node->right->height == 1))&&delta>4)
		{
		  delta--;
		}

		node->edge_length = ((delta+1)/2) - 1;
	}

	//now fill in the height of node
	h = 1;
	if (node->left != NULL)
	{
		h = MAX(node->left->height + node->edge_length + 1, h);
	}
	if (node->right != NULL)
	{
		h = MAX(node->right->height + node->edge_length + 1, h);
	}
	node->height = h;
}


//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
void print_level(asciinode *node, int x, int level)
{
	int i, isleft;
	if (node == NULL) return;
	isleft = (node->parent_dir == -1);
	if (level == 0)
	{
		for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++)
	{
	printf(" ");
	}
		print_next += i;
		printf("%s", node->label);
		print_next += node->lablen;
	}
	else if (node->edge_length >= level)
	{
		if (node->left != NULL)
		{
			for (i=0; i<(x-print_next-(level)); i++)
			{
				printf(" ");
			}
			print_next += i;
			printf("/");
			print_next++;
		}
		if (node->right != NULL)
		{
			for (i=0; i<(x-print_next+(level)); i++)
			{
				printf(" ");
			}
			print_next += i;
			printf("\\");
			print_next++;
		}
	}
	else
	{
		print_level(node->left,
				x-node->edge_length-1,
				level-node->edge_length-1);
		print_level(node->right,
				x+node->edge_length+1,
				level-node->edge_length-1);
	}
}


//prints ascii tree for given Tree structure
void print_ascii_tree(struct BSTnode* t)
{
	asciinode *proot;
	int xmin, i;
	if (t == NULL) return;
	proot = build_ascii_tree(t);
	compute_edge_lengths(proot);
	for (i=0; i<proot->height && i < MAX_HEIGHT; i++)
	{
		lprofile[i] = INFINITY;
	}
	compute_lprofile(proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
	{
		xmin = MIN(xmin, lprofile[i]);
	}
	for (i = 0; i < proot->height; i++)
	{
		print_next = 0;
		print_level(proot, -xmin, i);
		printf("\n");
	}
	if (proot->height >= MAX_HEIGHT)
	{
		printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
	}
	free_ascii_tree(proot);
}

/*                       BALANCING BST USING Day–Stout–Warren (DSW) algorithm
 * https://xuyuanguo.wordpress.com/2013/02/06/dsw-algorithm-balancing-binary-search-tree/ */

/*
		[3]					[1] <-- input
	   /   \			   /   \
	  [1]  [4]   <--      [0]  [3]
	 /   \                     / \
   [0]   [2]                 [2] [4]
*/
struct BSTnode* BSTleftRotate (struct BSTnode* root)
{
	if (root->right != NULL)
	{
		struct BSTnode* righchild_temp = root->right;
		root->right = righchild_temp->right;
		righchild_temp->right = righchild_temp->left;
		righchild_temp->left = root->left;
		root->left = righchild_temp;

		int temp = root->data;
		root->data = righchild_temp->data;
		righchild_temp->data = temp;
	}
	return root;
}

/*
intput->[3]					[1]
	   /   \			   /   \
	  [1]  [4]   -->      [0]  [3]
	 /   \                     / \
   [0]   [2]                 [2] [4]
*/
struct BSTnode* BSTrightRotate (struct BSTnode* root)
{
	if (root->left != NULL)
	{
		struct BSTnode* leftchild_temp = root->left;
		root->left = leftchild_temp->left;
		leftchild_temp->left = leftchild_temp->right;
		leftchild_temp->right = root->right;
		root->right = leftchild_temp;

		int temp = root->data;
		root->data = leftchild_temp->data;
		leftchild_temp->data = temp;
	}
	return root; //the addr of root is NOT changed. However, its data and left/right children are changed
}

/* this will create a single branch on the right, smallest to largest */
struct BSTnode* BSTcreateRightVine(struct BSTnode* root)
{
	while(root->left != NULL)
	{
		root = BSTrightRotate(root);
	}

	if (root->right != NULL)
	{
		root->right = BSTcreateRightVine(root->right);
	}
	return root;
}

struct BSTnode* BSTbalance (struct BSTnode*root, int nodeCount)
{
	int times = (int)log2(nodeCount); //alternatively,  log2 (x) = logy(x)/logy(2) wherein y can be any base (change of base)
	struct BSTnode* newRoot = root;
	for (int i = 0; i < times; i++)
	{
		newRoot = BSTleftRotate(root);
		root = newRoot->right;
		for (int j = 0; j < nodeCount/2 - 1; j++)
		{
			root = BSTleftRotate(root);
			root = root->right;
		}
		nodeCount >>= 1;
	}
	return newRoot;
}
