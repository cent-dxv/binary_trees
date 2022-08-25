#include "binary_trees.h"
#include <stdlib.h>

/**
 * height_recursion - function that calculates the height using recursion
 * @tree: node to find recursion
 * Return: the number of height nodes
 */

size_t height_recursion(const binary_tree_t *tree)
{
	size_t left_count = 0, right_count = 0;

	if (tree->left)
		left_count = height_recursion(tree->left);
	if (tree->right)
		right_count = height_recursion(tree->right);
	return ((left_count > right_count) ? left_count + 1 : right_count + 1);
}

/**
 * binary_tree_balance - returns the height of a tree
 * @tree: is the node from which to get the node
 * Return: an integer with the height or 0 if node is null
 */

int binary_tree_balance(const binary_tree_t *tree)
{
	int left = 0, right = 0;

	if (tree)
	{
		if (tree->left)
			left = height_recursion(tree->left);
		if (tree->right)
			right = height_recursion(tree->right);
		return (left - right);
	}
	else
		return (0);
}

/**
 * binary_tree_is_full - checks if a tree is full.
 * @tree: root node.
 * Return: 1 if full or 0 if not
 */

int binary_tree_is_full(const binary_tree_t *tree)
{
	if (!tree)
		return (1);
	if (!binary_tree_is_full(tree->left))
		return (0);
	if (!binary_tree_is_full(tree->right))
		return (0);
	if ((tree->left && !tree->right) || (!tree->left && tree->right))
		return (0);
	return (1);
}

/**
 * binary_tree_is_perfect - Returns if the tree is perfect
 * @tree: is the node from which to get the node
 * Return: 1 if is perfect, 0 if doesn't
 */

int binary_tree_is_perfect(const binary_tree_t *tree)
{
	int isperfect_left = 1, isperfect_right = 1;

	if (tree == NULL)
		return (0);
	if (tree->left)
		isperfect_left = binary_tree_is_perfect(tree->left);
	if (tree->right)
		isperfect_right = binary_tree_is_perfect(tree->right);
	if (binary_tree_is_full(tree) && !binary_tree_balance(tree))
		return (isperfect_left * isperfect_right);
	return (0);
}

/**
 * recursion_heap - performs the recursion for adding new nodes
 * @node: root
 * @value: value of the new node
 * Return: pointer to the new node
 */

heap_t *recursion_heap(heap_t **node, int value)
{
	heap_t *new_node_r = NULL, *new_node_l = NULL, *tmp;

	if (*node == NULL)
	{
		*node = binary_tree_node(*node, value);
		return (*node);
	}
	tmp = *node;
	if (binary_tree_is_perfect(tmp) && !(tmp->parent))
	{
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = binary_tree_node(tmp, value);
		return (tmp->left);
	}
	else if (tmp->left && !tmp->right)
	{
		tmp->right = binary_tree_node(tmp, value);
		return (tmp->right);
	}
	else if (tmp->left && tmp->right && binary_tree_balance(tmp) == 1
	&& binary_tree_is_perfect(tmp->left))
	{
		tmp = tmp->right;
		while (tmp->left)
			tmp = tmp->left;
		tmp->left = binary_tree_node(tmp, value);
		return (tmp->left);
	}
	if (tmp->left)
		new_node_l = recursion_heap(&(tmp->left), value);
	if (tmp->right && !new_node_l)
		new_node_r = recursion_heap(&(tmp->right), value);
	if (new_node_l)
		return (new_node_l);
	else if (new_node_r)
		return (new_node_r);
	return (NULL);
}

/**
 * heap_insert - inserts a value in a binary heap.
 * @root: root of a tree.
 * @value: value to insert.
 * Return: The new node or null.
 */

heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *tmp, *new_node, *current;
	new_node = recursion_heap(root, value);

	while (new_node && new_node->parent && new_node->n > new_node->parent->n)
	{
		tmp = new_node->parent;
		if (tmp->right == new_node)
		{
			current = new_node->left, new_node->left = tmp->left;
			if (new_node->left)
				new_node->left->parent = new_node;
			tmp->left = current;
			if (tmp->left)
				tmp->left->parent = tmp;
			current = new_node->right, new_node->right = tmp;
			tmp->right = current;
		}
		else
		{
			current = new_node->right, new_node->right = tmp->right;
			if (new_node->right)
				new_node->right->parent = new_node;
			tmp->right = current;
			if (tmp->right)
				tmp->right->parent = tmp;
			current = new_node->left, new_node->left = tmp;
			tmp->left = current;
		}
		if (current)
			current->parent = tmp;
		new_node->parent = tmp->parent;
		if (tmp->parent && tmp->parent->right == tmp)
			tmp->parent->right = new_node;
		else if (tmp->parent)
			tmp->parent->left = new_node;
		tmp->parent = new_node;
	}
	if (new_node && !new_node->parent)
		*root = new_node;
	return (new_node);
}
