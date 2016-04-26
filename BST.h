/*
 * BST.h
 *
 *  Created on: Apr 5, 2016
 *      Author: Dennis Chau
 */

#ifndef BST_H_
#define BST_H_

//http://cslibrary.stanford.edu/110/BinaryTrees.html#csoln

struct BSTnode
{
    int data;
    struct BSTnode* left;
    struct BSTnode* right;
};

typedef struct asciinode_struct asciinode;

struct asciinode_struct
{
	asciinode * left, * right;
	//length of the edge from this node to its children
	int edge_length;
	int height;
	int lablen;
	//-1=I am left, 0=I am root, 1=right
	int parent_dir;
	//max supported unit32 in dec, 10 digits max
	char label[11];
};

#define MAX_HEIGHT 1000
#define GAP  3 //adjust gap between left and right nodes

int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];

//used for printing next node in the same level,
//this is the x coordinate of the next char printed
int print_next;
#define INFINITY (1<<20)

unsigned char BSTsearch(struct BSTnode* root,struct BSTnode* root_parent, int target,
					struct BSTnode** node_found_parent,struct BSTnode** node_found);
struct BSTnode* BSTnewNode(int data);
struct BSTnode* BSTinsert(struct BSTnode* node, int data);
int BSTsize(struct BSTnode* node);
int BSTDepth(struct BSTnode* node, unsigned char tocheckMax);
void BSTinOrderTraversal(struct BSTnode* node);
void BSTpreOrderTraversal(struct BSTnode* node);
struct BSTnode* BSTclone(struct BSTnode* root );
void BSTpostOrderTraversal(struct BSTnode* node);
int BSTminValue(struct BSTnode* node);
int BSTmaxValue(struct BSTnode* node);
int isBST2(struct BSTnode* node);

#endif /* BST_H_ */
