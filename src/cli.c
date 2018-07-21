#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "threaded_bst.h"

#ifndef MAX_COMMAND_LEN
#define MAX_COMMAND_LEN 20
#endif

#ifndef MAX_LINE_LEN
#define MAX_LINE_LEN 80
#endif

#ifndef MAX_ID_LEN
#define MAX_ID_LEN 5
#endif

int command_to_num(char *command){

	int num;

	if(strcmp("insert", command) == 0)
		num = 1;
	else if(strcmp("delete", command) == 0)
		num = 2;
	else if(strcmp("search", command) == 0)
		num = 3;
	else if(strcmp("successor", command) == 0)
		num = 4;
	else if(strcmp("predecessor", command) == 0)
		num = 5;
	else if(strcmp("min", command) == 0)
		num = 6;
	else if(strcmp("max", command) == 0)
		num = 7;
	else if(strcmp("median", command) == 0)
		num = 8;
	else if(strcmp("inorder", command) == 0)
		num = 9;
	else if(strcmp("preorder", command) == 0)
		num = 10;
	else if(strcmp("postorder", command) == 0)
		num = 11;
	else if(strcmp("help", command) == 0)
		num = 12;
	else if(strcmp("quit", command) == 0)
		num = 13;
	else {
		printf("Unknown command.\n");
		num = 0;
	}

	return num;
}






int main(){

	char *id_str;
	char *name;
	unsigned int id;
	char line[MAX_LINE_LEN];
	char command[MAX_COMMAND_LEN];
	int command_num;
	tnode *node;
	tbst *tree;
	

	/* Arrays of pointers to functions
	 * in order to deal with functions with same input*/
	tnode *(*get_funcs[3]) (tbst *tmp_tree);
	void (*print_funcs[3]) (tbst *tmp_tree);

	get_funcs[2] = tree_minimum;
	get_funcs[1] = tree_maximum;
	get_funcs[0] = tree_median;

	print_funcs[2] = tree_inorder;
	print_funcs[1] = tree_preorder;
	print_funcs[0] = tree_postorder;




	tree = new_tree();
	node = NULL;

	printf("Write command after the >>, enter help for the command list\n>>");

	while(fgets(line, MAX_LINE_LEN, stdin)){
		
		/* Print the line for easy output file checks*/
		printf("%s", line);

		strcpy(command, strtok(line, " \n"));
		command_num = command_to_num(command);

		/* Quit */
		if(command_num == 13){
			break;


		/* Insert */
		} else if(command_num == 1){
			
			id_str = strtok(NULL, " \n");
			
			if(!id_str)
				printf("Not enough arguments.\n");

			else if(id_str){
				id = atoi(id_str);
				name = strtok(NULL, " \n");
				if(name == NULL)
					printf("Not enough arguments.\n");
				else{
					if(strtok(NULL, " \n") == NULL)
						tree = insert_tnode(tree, id, name);
					else
						printf("Too many arguments.\n");
				}
			}
		
		/* Delete */		
		} else if(command_num == 2){
			
			id_str = strtok(NULL, " \n");
			if(!id_str)
				printf("Not enough arguments.\n");

			else if(id_str){

				id = atoi(id_str);
				if((strtok(NULL, " \n") == NULL))
					tree = delete_tnode(tree, id);

				else
					printf("Too many arguments.\n");
			}


		/* Search */		
		} else if(command_num == 3){
			
			id_str = strtok(NULL, " \n");
			if(!id_str)
				printf("Not enough arguments.\n");

			else if(id_str){

				id = atoi(id_str);
				if((strtok(NULL, " \n") == NULL))
					node = tree_search(tree, id);
				else
					printf("Too many arguments.\n");
			}
			if(node)
				print_tnode(node);


		/* Successor */
		} else if(command_num == 4){
			
			id_str = strtok(NULL, " \n");
			if(!id_str)
				printf("Not enough arguments.\n");

			else if(id_str){

				id = atoi(id_str);
				if((strtok(NULL, " \n") == NULL))
					node = successor(tree_search(tree, id));
				else
					printf("Too many arguments.\n");
			}
			if(node)
				print_tnode(node);
		
		/* Predecessor */
		} else if(command_num == 5){
			
			id_str = strtok(NULL, " \n");
			if(!id_str)
				printf("Not enough arguments.\n");

			else if(id_str){

				id = atoi(id_str);
				if((strtok(NULL, " \n") == NULL))
					node = predecessor(tree_search(tree, id));
				else
					printf("Too many arguments.\n");
			}
			if(node)
				print_tnode(node);

		/* Get functions: min, max & median */
		} else if((command_num > 5) && (command_num <= 8)){
		
			if((strtok(NULL, " \n") == NULL)){
				node = (*get_funcs[8 - command_num])(tree);
				print_tnode(node);
			}
			else
				printf("Too many arguments.\n");
		
		/* Print functions: inorder, preorder & postorder */
		} else if((command_num > 8) && (command_num <= 11)){
		
			if((strtok(NULL, " \n") == NULL)){
				(*print_funcs[11 - command_num])(tree);
			}
			else
				printf("Too many arguments.\n");
		
		/* Print Documentation */
		} else if(command_num == 12){
			printf("Commands:\n---------\ninsert <id> <name>\n");
			printf("delete <id>\nsearch <id>\nsuccessor <id>\n");
			printf("predecessor <id>\nmin\nmax\nmedian\ninorder\n");
			printf("preorder\npostorder\nquit\n");
		}
		
		printf(">>");
		node = NULL;

	}


	return 0;

}
