#include "ai_header.h"

struct tree_node* create_node(int map[][7], int intree, int winorlose)
{
	struct tree_node *node = (struct tree_node*)malloc(sizeof(struct tree_node));
	if (node = NULL)
		return NULL;

	node->map = map;
	node->evaluation_value = -999;	//default value
	node->is_in_tree = intree;
	node->is_it_leaf_node = -999;
	node->is_it_winorlose = winorlose;
	node->child1 = NULL;
	node->child2 = NULL;
	node->child3 = NULL;
	node->child4 = NULL;
	node->child5 = NULL;
	node->child6 = NULL;
	node->child7 = NULL;
	node->next_sibling = NULL;
	
	return node;
}

/*i made tree structure function - create_node, insert_child.
In insert_child function, it automatically creates nodes, 
makes maps and inerts it into child nodes so you do not need to make child map using malloc.
you can make all 7 child nodes just uning insert_child function passing only argument as root node
But it can have some child nodes as empty node which has not_intree flag and null value on map pointer 
when child can not have a place to put stone any more*/
void insert_child(struct tree_node *root)
{
	if (root->is_in_tree == FALSE || root->is_it_winorlose == TRUE)
	{
		root->child1 = create_node(NULL, FALSE, FALSE);
		root->child2 = create_node(NULL, FALSE, FALSE);
		root->child3 = create_node(NULL, FALSE, FALSE);
		root->child4 = create_node(NULL, FALSE, FALSE);
		root->child5 = create_node(NULL, FALSE, FALSE);
		root->child6 = create_node(NULL, FALSE, FALSE);
		root->child7 = create_node(NULL, FALSE, FALSE);
		connect_siblings(root);
	}
	else
	{
		int **child_map1 = duplicate_root_map(root->map);
		int **child_map2 = duplicate_root_map(root->map);
		int **child_map3 = duplicate_root_map(root->map);
		int **child_map4 = duplicate_root_map(root->map);
		int **child_map5 = duplicate_root_map(root->map);
		int **child_map6 = duplicate_root_map(root->map);
		int **child_map7 = duplicate_root_map(root->map);
		int result; // 1 -> can move, 0 -> can not move,  2 -> state is win or lose

		result = modify_child_map(child_map1, 1);
		if (result == 1)
			root->child1 = create_node(child_map1, TRUE, FALSE);
		else if (result == 2)
			root->child1 = create_node(child_map1, TRUE, TRUE);
		else
		{
			free_map(child_map1);
			root->child1 = create_node(NULL, FALSE, FALSE);
		}

		result = modify_child_map(child_map2, 2);
		if (result == 1)
			root->child1 = create_node(child_map2, TRUE, FALSE);
		else if (result == 2)
			root->child1 = create_node(child_map2, TRUE, TRUE);
		else
		{
			free_map(child_map2);
			root->child2 = create_node(NULL, FALSE, FALSE);
		}
		
		result = modify_child_map(child_map3, 3);
		if (result == 1)
			root->child1 = create_node(child_map3, TRUE, FALSE);
		else if (result == 2)
			root->child1 = create_node(child_map3, TRUE, TRUE);
		else
		{
			free_map(child_map3);
			root->child3 = create_node(NULL, FALSE, FALSE);
		}
		
		result = modify_child_map(child_map4, 4);
		if (result == 1)
			root->child1 = create_node(child_map4, TRUE, FALSE);
		else if (result == 2)
			root->child1 = create_node(child_map4, TRUE, TRUE);
		else
		{
			free_map(child_map4);
			root->child4 = create_node(NULL, FALSE, FALSE);
		}
		
		result = modify_child_map(child_map5, 5);
		if (result == 1)
			root->child1 = create_node(child_map5, TRUE, FALSE);
		else if (result == 2)
			root->child1 = create_node(child_map5, TRUE, TRUE);
		else
		{
			free_map(child_map5);
			root->child5 = create_node(NULL, FALSE, FALSE);
		}
		
		result = modify_child_map(child_map6, 6);
		if (result == 1)
			root->child1 = create_node(child_map6, TRUE, FALSE);
		else if (result == 2)
			root->child1 = create_node(child_map6, TRUE, TRUE);
		else
		{
			free_map(child_map6);
			root->child6 = create_node(NULL, FALSE, FALSE);
		}
		
		result = modify_child_map(child_map7, 7);
		if (result == 1)
			root->child1 = create_node(child_map7, TRUE, FALSE);
		else if (result == 2)
			root->child1 = create_node(child_map7, TRUE, TRUE);
		else
		{
			free_map(child_map7);
			root->child7 = create_node(NULL, FALSE, FALSE);
		}

		connect_siblings(root);
	}
}

int** duplicate_root_map(int **root_map)
{
	int **child_map = (int**)malloc(sizeof(int*) * 6);
	int i, k;
	for (i = 0; i < 6; i++)
		child_map[i] = (int*)malloc(sizeof(int) * 7);
	
	for (i = 0; i < 6; i++)
	{
		for (k = 0; k < 7; k++)
		{
			child_map[i][k] = root_map[i][k];
		}
	}
	return child_map;
}

int modify_child_map(int **child_map, int number)
{
	number--;
	int i, result;
	for (i = 0; i < 6; i++)
	{
		if (child_map[i][number] == 0)
		{
			child_map[i][number] = 2;
			//it can move and retun 1 as success
			if ((result = decide_win_or_lose_or_continue(child_map)) == 0)
				return 1;
			else  //it is the case that it doesn;t need to make child nodes because after modifiying map, state of map is win or lose.  
				return 2;
		}
		if (i == 5)
		{
			/*it can not move because vertical row is full 
			  so return 0 as fail and do not make map 
			  (free map in upper function and set is_it_in_tree varibale as FALSE in child node)*/
			return 0;
		}
	}
}

int* mem_free_tree(struct tree_node *root)
{
	if (root->child1 == NULL&&root->child2 == NULL&&root->child3 == NULL&&root->child4 == NULL&&
		root->child5 == NULL&&root->child6 == NULL&&root->child7 == NULL)
	{
		free_map(root);
		free(root);
		return NULL;	//Check if it returns null so super root's child is null (debuging)
	}
	int *temp = NULL;
	temp = mem_free_tree(root->child1);
	temp = mem_free_tree(root->child2);
	temp = mem_free_tree(root->child3);
	temp = mem_free_tree(root->child4);
	temp = mem_free_tree(root->child5);
	temp = mem_free_tree(root->child6);
	root = mem_free_tree(root->child7);
}

void free_map(int **map)
{
	int i;
	for (i = 0; i < 6; i++)
	{
		free(map[i]);
	}
	free(map);
}

void connect_siblings(struct tree_node *root)
{
	root->child1->next_sibling = root->child2;
	root->child2->next_sibling = root->child3;
	root->child3->next_sibling = root->child4;
	root->child4->next_sibling = root->child5;
	root->child5->next_sibling = root->child6;
	root->child6->next_sibling = root->child7;
}