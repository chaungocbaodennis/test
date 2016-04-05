/*
 * BST.c
 *
 *  Created on: Apr 5, 2016
 *      Author: Dennis Chau
 */
#include<stdio.h>
#include<string.h>
#include <limits.h>
#include"BST.h"

/*  Given a binary tree, return true if a node
 with the target data is found in the tree. Recurs
 down the tree, chooses the left or right
 branch by comparing the target to each node.
*/

static int lookup(struct node* node, int target)
{
	// 1. Base case == empty tree
	// in that case, the target is not found so return false
	if (node == NULL)
	{
		return(0);
	}
	else
	{
		// 2. see if found here
		if (target == node->data) return(1);
		else
		{
			// 3. otherwise, decide to go down left or right and then recurvisely down the correct subtree
			if (target < node->data) return(lookup(node->left, target));
			else return(lookup(node->right, target));
		}
	}
}

/*
 Helper function that allocates a new node
 with the given data and NULL left and right
 pointers.
*/
struct node* NewNode(int data)
{
  struct node* newnode = malloc(sizeof(struct node));    // "new" is like "malloc"
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
struct node* insert(struct node* node, int data)
{
	// 1. If the tree is empty, return a new, single node
	if (node == NULL)
	{
		return(NewNode(data));
	}
	else
	{
		// 2. Otherwise, recur down the tree
		if (data <= node->data)
		{
			node->left = insert(node->left, data);
		}
		else
		{
			node->right = insert(node->right, data);
		}

		return(node); // return the (unchanged) node pointer
	}
}

/*
 Compute the number of nodes in a tree.
*/
int size(struct node* node)
{
	if (node == NULL)
	{
		return(0);
	}
	else
	{
		return(size(node->left) + 1 + size(node->right));
	}
}

/*
 Compute the "maxDepth" of a tree -- the number of nodes along
 the longest path from the root node down to the farthest leaf node.
*/
int maxDepth(struct node* node)
{
	if (node == NULL)
	{
		return(0);
	}
	else
	{
		// compute the depth of each subtree
		int lDepth = maxDepth(node->left);
		int rDepth = maxDepth(node->right);
		// use the larger one
		if (lDepth > rDepth) return(lDepth+1);
		else return(rDepth+1);
	}
}

/*
 Given a binary search tree, print out
 its data elements in increasing
 sorted order.
*/
void printTree(struct node* node)
{
  if (node == NULL) return;
  printTree(node->left);
  printf("%d ", node->data);
  printTree(node->right);
}

int minValue(struct node* node)
{
  struct node* current = node;
  // loop down to find the leftmost leaf
  while (current->left != NULL)
  {
    current = current->left;
  }

  return(current->data);
}

int maxValue(struct node* node)
{
  struct node* current = node;
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
int isBSTUtil(struct node* node, int min, int max)
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
int isBST2(struct node* node) {
  return(isBSTUtil(node, INT_MIN, INT_MAX));
}
