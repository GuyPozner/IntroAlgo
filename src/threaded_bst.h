#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef MAX_NAME_LEN
#define MAX_NAME_LEN 30
#endif


typedef struct tbst tbst;


typedef struct tnode tnode;


/*	Function: new_tree
 *	------------------
 *	A function to initialize a new threaded binary search tree(tbst).
 *	returns: Empty tbst.
 */
tbst * new_tree();


/*	Function: print_tnode
 *	------------------
 *	A function to print a tbst node.
 */
void print_tnode(tnode *);


/*	Function: tree_search
 *	------------------
 *	Searches the tbst in linear time on the hight of the tbst.
 * 	
 *	param1: a tbst pointer.
 *	parma2: an id to search for.
 *	returns: A pointer to the tnode containing the given id,
 *  		 if id not found, returns a NULL pointer.
 */
tnode * tree_search(tbst *, unsigned int);


/*	Function: tree_minimum
 *	------------------
 *	Finds the miniof the tbst in linear time on the hight of the tree.
 * 	
 *	param1: a tbst pointer.
 *	returns: A pointer to the tnode holding the minimum id,
 *			 If the tree is empty it returns a NULL pointer.
 */
tnode * tree_minimum(tbst *);


/*	Function: tree_maximum
 *	------------------
 *	Finds the maximum of the tbst in linear time on the hight of the tree.
 * 	
 *	param1: a tbst pointer.
 *	returns: A pointer to the tnode holding the maximum id,
 *			 If the tree is empty it returns a NULL pointer.
 */
tnode * tree_maximum(tbst *);


/*	Function: predecessor
 *	------------------
 *	Finds the predecessor of the tnode in linear time on the hight of the tree.
 * 	
 *	param1: a tnode pointer.
 *	returns: A pointer to the tnode holding the largest id, 
 *  		 which is smaller than the id of the given tnode.
 */
tnode *predecessor(tnode *);


/*	Function: successor
 *	------------------
 *	Finds the succesor of the tnode in linear time on the hight of the tree.
 * 	
 *	param1: a tnode pointer.
 *	returns: A pointer to the tnode holding the smallest id, 
 *  		 which is greater than the id of the given tnode.
 */
tnode *successor(tnode *);


/*	Function: insert_tnode
 *	------------------
 *	Inserts a new tnode to the tbst, from a given id and name,
 *  in linear time on the hight of the tree. Maintains the median
 *	and the threads.
 * 	
 *	param1: a tbst pointer.
 * 	param2: id.
 *  param3: name.
 *	returns: A pointer to the tbst.
 */
tbst * insert_tnode(tbst *, unsigned int, char *);


/*	Function: delete_tnode
 *	------------------
 *	Deletes the  tnode by id in linear time on the hight of the tree.
 *  Maintains the median and the threads.
 * 	
 *	param1: a tbst pointer.
 * 	param2: id.
 *	returns: A pointer to the tbst.
 */
tbst * delete_tnode(tbst *, unsigned int);

/*	Function: tree_median
 *	------------------
 * 	
 *	param1: a tbst pointer.
 * 	param2: id.
 *	returns: A pointer to the tnode containing the median id,
 *			 or NULL pointer if tree is empty.
 */
tnode * tree_median(tbst *);


/*	Function: tree_median
 *	------------------
 * 	Prints the tbst iterativly inorder in linear time on the number of tnodes.
 *	param1: a tbst pointer.
 */
void tree_inorder(tbst *);

/*	Function: tree_median
 *	------------------
 * 	Prints the tbst recursively in preorder in linear time on the number of tnodes.
 *	param1: a tbst pointer.
 */
void tree_preorder(tbst *);

/*	Function: tree_median
 *	------------------
 * 	Prints the tbst irecursively in postorder in linear time on the number of tnodes.
 *	param1: a tbst pointer.
 */
void tree_postorder(tbst *);












