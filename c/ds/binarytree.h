/* 
 * This is a C based binary tree implementation.
 */
#ifndef BINARYTREE_H
#define BINARYTREE_H

struct btreenode {
	void *node;
	struct btreenode *left;
	struct btreenode *right;
};

int searchbtree(struct btreenode *root, int searchby)
{
	if (!root || !root->node)
		return 0;
	if (root->node->value < searchby)
		return searchbtree(root->left, searchby);
	else
		return searchbtree(root->right, searchby); 
}

#endif
