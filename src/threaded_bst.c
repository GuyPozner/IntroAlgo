#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#ifndef MAX_NAME_LEN
#define MAX_NAME_LEN 30
#endif

/* Threaded tree node */
typedef struct tnode{

	unsigned int id;
	char *name;
	struct tnode *left, *right;
	unsigned int left_thread:1;
	unsigned int right_thread:1;

}tnode;


/* Threaded binary search tree */
typedef struct tbst{

	tnode *root;
	tnode *median;
	unsigned int parity:1; /* 1 when number of nodes is odd, 0 otherwise */

}tbst;




/* Allocate memory and assigns data to a new tree node */
tnode * new_tnode(unsigned int id, char *name){
	
	tnode *new;
	
	/* name is larger than allowed */
	if(strlen(name) > MAX_NAME_LEN){
		fprintf(stderr, "%s exceeds name character limitations(%d).\n", name, MAX_NAME_LEN);
		exit(0);
	}

	new = (tnode *)malloc(sizeof(tnode));
	new->name = (char *)malloc(sizeof(char) * MAX_NAME_LEN);

	new->id = id;
	strcpy(new->name, name);
	new->left = NULL;
	new->right = NULL;
	new->left_thread = 1;
	new->right_thread = 1;

	return new;
}




/* Allocate memory for the new threaded binary search tree
 * Assign 0 to parity, since a tree with no nodes has an even parity */
tbst * new_tree(){

	tbst *new = (tbst *)malloc(sizeof(tbst));
	tnode *root = NULL;
	tnode *median = NULL;
	
	/* Populate tree*/
	new->parity = 0;
	new->root = root;
	new->median = median;

	return new;
}


/* Prints the data of a tree node */
void print_tnode(tnode *node){
	
	if(node == NULL){
		printf("Warning: Trying to print an empty node.\n");
	} else {
		printf("%d: %s\n", node->id, node->name);
	}
}



/* Searches for a tnode containing the given id in the subtree,
 * if the given id exist in the tree the function
 * returns a pointer to the tnode holding it,
 * Otherwise, it returns a NULL pointer*/
tnode * subtree_search(tnode *root, unsigned int id){
	
	tnode *node = root;

	while(node != NULL){
		/* Move to the left subtree */
		if(id < node->id){
			if(node->left_thread == 0)
				node = node->left;
			else
				break;
		
		/* Move to the right subtree */
		} else if(id > node->id){
			if(node->right_thread == 0)
				node = node->right;
			else
				break;
		/* If id was found */
		} else {
			return node;
		}
	}
	/* return a NULL pointer if id wasn't found */
	printf("Id %d was not found.\n", id);
	return NULL;
}


/* Returns a pointer to the tnode holding the minimum id
 * If the subtree is empty, returns a NULL pointer */
tnode * subtree_minimum(tnode *root){
	
	tnode *tmp_tnode;

	/* Empty subtree */
	if(root == NULL)
		return NULL;

	tmp_tnode = root;
	while(tmp_tnode->left_thread == 0)
		tmp_tnode = tmp_tnode->left;

	return tmp_tnode;
}


/* Returns a pointer to the tnode holding the maximum id,
 * If the subtree is empty, returns a NULL pointer */
tnode * subtree_maximum(tnode *root){
	
	tnode *tmp_tnode;

	/* Empty subtree */
	if(root == NULL)
		return NULL;

	
	
	tmp_tnode = root;
	while(tmp_tnode->right_thread == 0)
		tmp_tnode = tmp_tnode->right;

	return tmp_tnode;
}


/* Search function for the tbst type
 * If tree is empty returns a NULL pointer */
tnode * tree_search(tbst *tree, unsigned int id){
	return subtree_search(tree->root, id);
}


/* Minimum function for tbst type
 * If tree is empty returns a NULL pointer */
tnode * tree_minimum(tbst *tree){
	return subtree_minimum(tree->root);
}


/* Maximum function for a tbst type
 * If tree is empty returns a NULL pointer */
tnode * tree_maximum(tbst *tree){
	return subtree_maximum(tree->root);
}


/* Returns the pointer to the tnode
 * holding the largest id which is smaller than
 * the id of the given tnode.
 * When given a tnode holding the minimum id
 * it return a NULL pointer */
tnode *predecessor(tnode *node){
	

	tnode *tmp_tnode = node;

	/* Empty node */
	if(tmp_tnode == NULL)
		return NULL;

	/* If a left thread is found than left points to the predecessor */
	if(node->left_thread == 1)
		return node->left;
	
	/* Otherwise it is the maximum child of the left subtree */
	tmp_tnode = subtree_maximum(tmp_tnode->left);

	return tmp_tnode;
}


/* Returns the pointer to the tnode
 * holding the smallest id which is greater than
 * the id of the given tnode.
 * When given a tnode holding the maximum id
 * it return a NULL pointer */
tnode *successor(tnode *node){

	tnode *tmp_tnode = node;

	/* Empty node */
	if(tmp_tnode == NULL)
		return NULL;

	/* If a right thread is found than right points to the succesor */
	if(node->right_thread == 1)
		return node->right;

	/* Otherwise it is the minimum child of the right subtree */
	tmp_tnode = subtree_minimum(tmp_tnode->right);

	return tmp_tnode;
}


/* Inserts a new node to the threaded binary tree */
tbst * insert_tnode(tbst *tree, unsigned int id, char *name){
	
	tnode *node, *parent;
	tnode *new;


	/* Find the position of the new node */
	node = tree->root;
	parent = NULL;
	
	while(node != NULL){

		parent = node;

		/* Move to the left subtree */
		if(id < node->id){
			if(node->left_thread == 0)
				node = node->left;
			else
				break;
		
		/* Move to the right subtree */
		} else if(id > node->id){
			if(node->right_thread == 0)
				node = node->right;
			else
				break;

		/* Do not add a tnode with duplicated id */
		} else {
			printf("Warning: tnode id: %d already exists.\n", id);
			return tree;
		}
	}
	/* Inserting changes the parity of the tree */
	tree->parity = tree->parity ^ 1;

	/* Create the new node */
	new = new_tnode(id, name);

	/* Insert to an empty tree */
	if(parent == NULL){
		tree->root = new;
		new-> left = NULL;
		new->right = NULL;
		tree->median = new;
	
	
	} else {

		/* New node is a left child */
		if(id < parent->id){
			new->left = parent->left;
			new->right = parent;
			parent->left_thread = 0;
			parent->left = new;

	
		/* New node is a right child */
		} else {
			new->left = parent;
			new->right = parent->right;
			parent->right_thread = 0;
			parent->right = new;
		}

		/* Keep track of the median
		 * Notice that the median changes only when 
		 * the newly inserted node is either smaller than
		 * the previous median and it is an even insertion
		 * or its greater than the old median and it is
		 * an odd insertion.
		 */

		if(new->id < tree->median->id && !tree->parity)
			tree->median = predecessor(tree->median);

		else if(new->id > tree->median->id && tree->parity)
			tree->median = successor(tree->median);

	}

	return tree;
}

/* Deletes a leaf, returns pointer to the root */
tnode * leaf_deletion(tnode *root, tnode *parent, tnode *node){

	/* The leaf is the root */
	if(parent == NULL)
		root = NULL;

	/*The leaf is a left child*/
	else if(node ==	parent->left){
		parent->left_thread = 1;
		parent->left = node->left;

	/* The leaf is a right child */
	} else {
		parent->right_thread = 1;
		parent->right = node->right;
	}

	/* Free the memory taken by the deleted node */
	free(node);
	return root;
}

tnode * one_child_deletion(tnode *root, tnode *parent, tnode *node){

	tnode *child, *s, *p;

	/* Store the subtree of the child */
	if(node->left_thread)
		child = node->right;
	else
		child = node->left;


	/* Root deletion */
	if(parent == NULL)
		root = child;

	/* The deleted node is a left child */
	else if(node == parent->left)
		parent->left = child;

	/* The deleted node is a right child */
	else
		parent->right = child;

	/* Populate the threads of the deleted node succesor/predecesor */
	s = successor(node);
	p = predecessor(node);
	

	/* If the node to be deleted has a right subtree
	 * Its succesor inherits its predecessor */
	if(node->left_thread == 0){
		p->right = s;
	
	/* Otherwise, its predecessor inherits its succesor */
	} else {
		if(node->right_thread == 0)
			s->left = p;
	}
	
	/* Free the memory taken by the deleted node */
	free(node);
	return root;
}

tnode * two_children_deletion(tnode *root, tnode *parent, tnode *node){

	tnode *successor, *successor_parent;

	/* Find the succsor and its parent of the node to be delted */
	successor_parent = node;
	successor = node->right;
	while(successor->left_thread == 0){
		successor_parent = successor;
		successor = successor->left;
	}

	/* Copy the information from the succesor to the pointer of the deleted node,
	 * delete the succesor with one child or leaf deletion */
	node->id = successor->id;
	strcpy(node->name, successor->name);

	if(successor->left_thread && successor->right_thread)
		root = leaf_deletion(root, successor_parent, successor);
	else
		root = one_child_deletion(root, successor_parent, successor);

	return root;
}


tbst * delete_tnode(tbst *tree, unsigned int id){
	
	tnode *node, *parent;
	unsigned int found = 0;

	/* Search for the node and its parent in the tree */
	node = tree->root;
	parent = NULL;
	
	while(node != NULL){
		if(node->id == id){
			found = 1;
			break;
		}

		parent = node;
		
		/* Move in the left subtree */
		if(id < node->id){
			if(node->left_thread == 0)
				node = node->left;
			else
				break;

		/* Move in the right subtree */
		} else {
			if(node->right_thread == 0)
				node = node->right;
			else
				break;
		}

	}

	if(found == 0){
		printf("Id %d was not found, and cannot be deleted.\n", id);
		return tree;
	}

	/* Deletion changes the parity */
	tree->parity = tree->parity ^ 1;
 	
	/* Update the median */
	if(!(node->left_thread == 0 && node->right_thread == 0)){
		
		if(id >= tree->median->id && !tree->parity)
			tree->median = predecessor(tree->median);

		else if(id <= tree->median->id && tree->parity)
			tree->median = successor(tree->median);
	
	/* The deletion of a node with two children copies the information of the succesor
	 * into the deleted node position in memory*/
	} else {

		if(id > tree->median->id && !tree->parity)
			tree->median = predecessor(tree->median);

		else if(id < tree->median->id && tree->parity)
			tree->median = successor(tree->median);

		else if(id == tree->median->id && !tree->parity)
			tree->median = predecessor(tree->median);
	}


    /* The deleted node has two children */
    if(node->left_thread == 0 && node->right_thread == 0)
        tree->root = two_children_deletion(tree->root, parent, node);
    	

    /* The deleted node has one child */
    else if(node->left_thread == 0)
        tree->root = one_child_deletion(tree->root, parent, node);
    
    else if(node->right_thread == 0)
        tree->root = one_child_deletion(tree->root, parent, node);
 
    /* The deleted node is a leaf */
    else
        tree->root = leaf_deletion(tree->root, parent, node);

    return tree;
}


/* Iterative inorder print of a sub threaded binary search tree*/
void subtree_inorder(tnode *root){
	
	tnode *tmp_tnode = subtree_minimum(root);

    if(tmp_tnode == NULL)
        printf("Tree is empty");
 
    while(tmp_tnode != NULL){
    	printf("%d ", tmp_tnode->id);
    	tmp_tnode = successor(tmp_tnode);
    }
    putchar('\n');
}

/* Preorder print of a sub threaded binary tree */
void subtree_preorder(tnode *root){
	
	printf("%d ", root->id);
	if(root->left_thread == 0){
		subtree_preorder(root->left);
	}
	if(root->right_thread == 0){
		subtree_preorder(root->right);
	}
}

/* Postorder print of a sub threaded binary tree */
void subtree_postorder(tnode *root){
	
	if(root->left_thread == 0){
		subtree_postorder(root->left);
	}

	if(root->right_thread == 0){
		subtree_postorder(root->right);
	}
	printf("%d ", root->id);
}

/* Iterative inorder print of a threaded binary search tree */
void tree_inorder(tbst *tree){
	if(tree->root != NULL)
		subtree_inorder(tree->root);
	else
		printf("Tree is empty.\n");
}


/* Recursive preorder print of a threaded binary search tree */
void tree_preorder(tbst *tree){
	if(tree->root != NULL){
		subtree_preorder(tree->root);
		putchar('\n');
	} else {
		printf("Tree is empty.\n");
	}
	
	
}

/* Recursive post print of a threaded binary search tree */
void tree_postorder(tbst *tree){
	
	if(tree->root != NULL){
		subtree_postorder(tree->root);
		putchar('\n');
	} else {
		printf("Tree is empty.\n");
	}
	
}

/* Gets the median tnode
 * If tree is empty returns a NULL pointer */
tnode * tree_median(tbst *tree){

	/* An empty tree has no median */
	if(tree->root == NULL)
		return NULL;

	return tree->median;
}
