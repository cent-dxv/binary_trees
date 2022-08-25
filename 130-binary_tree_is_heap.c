#include "binary_trees.h"
#include <stdlib.h>

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
 * binary_tree_balance - returns the balance of a tree
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
 * binary_tree_is_complete - returns 1 if the tree is complete
 * @tree: is the node from which to get the tree
 * Return: 1 if is complete, 0 if doesn't
 */

int binary_tree_is_complete(const binary_tree_t *tree)
{
	int complete_left = 1, complete_right = 1;

	if (!tree)
		return (0);
	if (tree->left)
		complete_left = binary_tree_is_complete(tree->left);
	if (tree->right)
		complete_right = binary_tree_is_complete(tree->right);
	if (binary_tree_balance(tree) == 1)
		return (complete_left * complete_right);
	if (!binary_tree_balance(tree))
	{
		if (!tree->right || (tree->left &&
			binary_tree_is_full(tree->left) && !binary_tree_balance(tree->left)))
			return (complete_left * complete_right);
		else
			return (0);
	}
	return (0);
}
/**
 * binary_tree_is_heap - returns 1 if a tree is a binary heap
 * @tree: pointer to the root of the tree
 * Return: 1 if binary heap, 0 if not
 */

int binary_tree_is_heap(const binary_tree_t *tree)
{
	int left_res = 1, right_res = 1;

	if (!tree)
		return (0);
	if (!binary_tree_is_complete(tree))
		return (0);
	if (tree->left)
	{
		if (tree->left->n >= tree->n)
			return (0);
		left_res = binary_tree_is_heap(tree->left);
	}
	if (tree->right)
	{
		if (tree->right->n >= tree->n)
			return (0);
		right_res = binary_tree_is_heap(tree->right);
	}
	return (left_res * right_res);
}
