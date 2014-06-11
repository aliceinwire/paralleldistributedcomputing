#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HEIGHT 4

struct node {
	int value;
	struct node *left;
	struct node *right;
	struct node *next;
};

struct node *btree_root = NULL;

unsigned int print_btree(struct node *root, unsigned int level)
{
	static unsigned int height = 0;

	if (!root)
		return;
	if (height < level)
		height = level;
	print_btree(root->left, level+1);
	printf ("[level : value] : [%6u : %6u]\n", level, root->value);
	print_btree(root->right, level+1);
	return height;
}

void print_arr(struct node **arr, unsigned int size)
{
	unsigned int i = 0;
	struct node *tmp = NULL;

	for (; i < size; ++i) {
		tmp = arr[i];
		printf ("\nLevel[%u]", i+1);
		while (tmp) {
			printf (" -> %u", tmp->value);
			tmp = tmp->next;
		}
	} 
}

void add_to_btree(struct node *curr, struct node *newnode)
{
	if (!curr || !newnode)
		return;
	if (curr->value > newnode->value) {
		if (curr->left)
			add_to_btree(curr->left, newnode);
		else
			curr->left = newnode; 
	} else {
		if (curr->right)
			add_to_btree(curr->right, newnode);
		else
			curr->right = newnode; 
	}
}

void init_node(struct node **n, int val)
{
	struct node *tmp = NULL;

	*n = (struct node *)malloc(sizeof(struct node));
	tmp = *n;
	if (tmp) {
		tmp->left = tmp->right = tmp->next = NULL; 
		tmp->value = val;
	}
}

struct node *build_btree()
{
	unsigned int arr[] = {10, 5, 0, 20, 34, 40, 188, 100, 98, 61, 63, 62};
	unsigned int len = sizeof(arr)/sizeof(arr[0]);
	unsigned int i = 0;
	struct node *newnode;

	init_node(&btree_root, arr[0]);
	for (i = 1; i < len; ++i) {
		newnode = NULL; 
		init_node(&newnode, arr[i]);
		add_to_btree(btree_root, newnode);
	}
	return btree_root;
}

void append_to_list(struct node **arr, struct node *curr, unsigned int level)
{
	struct node *tmp = NULL;

	if (!curr)
		return;
	tmp = arr[level];
	if (!tmp) {
		arr[level] = curr;
		return;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = curr;
}

void build_arr(struct node **arr, struct node *curr, unsigned int h)
{
	if (!curr)
		return;
	append_to_list(arr, curr, h);
	build_arr(arr, curr->left, h+1);
	build_arr(arr, curr->right, h+1);
}

int main()
{
	struct node *btree_root = build_btree();
	unsigned int btree_height = print_btree(btree_root, 0);
	struct node *arr[btree_height];
	unsigned int i[2];

	memset(arr, 0, sizeof(arr)); 
	printf ("Height of binary tree is %u.\n", btree_height);
	build_arr(arr, btree_root, 0);
	print_arr(arr, sizeof(arr)/sizeof(arr[0]));
	printf ("\nBinary tree is as above.\n");
	return 0;
}

