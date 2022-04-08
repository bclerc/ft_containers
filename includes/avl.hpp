/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 03:15:51 by bclerc            #+#    #+#             */
/*   Updated: 2022/04/08 15:32:32 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AVL_HPP
#define AVL_HPP

#include "pair.tpp"
#include <ostream>

#define BLACK 0
#define RED 1

template <class T>
struct s_node
{

	typedef T value_type;

	T data;
	int color;
	struct s_node *parent;
	struct s_node *left;
	struct s_node *right;


};

namespace ft
{

	template <class T>
	class RBT
	{

	public:
		typedef s_node<T> t_node;

	private:
		t_node *TNULL;
		t_node *root;

		t_node *_newNode(T data)
		{
			t_node *node = new t_node;

			node->parent = NULL;
			node->data = data;
			node->left = TNULL;
			node->right = TNULL;
			node->color = RED; // Red by default
			return node;
		}

		t_node *_search(t_node *node, T key)
		{
			t_node *ret;

			if (node == TNULL || key.first == node->data.first)
				ret = node;
			else if (key.first < node->data.first)
				ret = _search(node->left, key);
			else
				ret = _search(node->right, key);
			if (ret == TNULL)
				throw std::invalid_argument("Node not found");
			return (ret);
		}

		void _deleteFix(t_node *node)
		{
			t_node *tmp;

			while (node != root && node->color == BLACK)
			{
				if (node == node->parent->left)
				{
					tmp = node->parent->right;
					if (tmp->color == RED)
					{
						tmp->color = BLACK;
						node->parent->color = RED;
						leftRotate(node->parent);
						tmp = node->parent->right;
					}
					if (tmp->left->color == BLACK)
					{
						tmp->color = RED;
						node = node->parent;
					}
					else
					{
						if (tmp->right->color == BLACK)
						{
							tmp->left->color = BLACK;
							tmp->color = RED;
							rightRotate(tmp);
							tmp = node->parent->right;
						}
						tmp->color = node->parent->color;
						node->parent->color = 0;
						tmp->right->color = 0;
						leftRotate(node->parent);
						node = root;
					}
				}
				else
				{
					tmp = node->parent->left;
					if (tmp->color == RED)
					{
						tmp->color = BLACK;
						node->parent->color = RED;
						rightRotate(node->parent);
						tmp = node->parent->left;
					}
					if (tmp->right->color == BLACK)
					{
						tmp->color = RED;
						node = node->parent;
					}
					else
					{
						if (tmp->left->color == BLACK)
						{
							tmp->right->color = BLACK;
							tmp->color = RED;
							leftRotate(tmp);
							tmp = node->parent->left;
						}

						tmp->color = node->parent->color;
						node->parent->color = BLACK;
						tmp->left->color = BLACK;
						rightRotate(node->parent);
						node = root;
					}
				}
			}
			node->color = BLACK;
		}

		// Replace the first node by second for detach the deleted node from rbt
		void _transplant(t_node *first, t_node *second)
		{
			if (!first->parent)
				root = second;
			else if (first == first->parent->left)
				first->parent->left = second;
			else
				first->parent->right = second;
			second->parent = first->parent;
		}

	public:
		RBT() : TNULL(new t_node),
				root(TNULL)
		{
			TNULL->color = BLACK;
			TNULL->left = TNULL;
			TNULL->right = TNULL;
			TNULL->parent = TNULL;
			TNULL->data = T();
			return;
		}

		~RBT()
		{
			// delete TNULL;
		}

		void leftRotate(t_node *node_x)
		{
			t_node *node_y = node_x->right;

			node_x->right = node_y->left;
			if (node_y->left != TNULL)
				node_y->left->parent = node_x;
			node_y->parent = node_x->parent;
			if (node_x->parent == NULL)
				root = node_y;
			else if (node_x == node_x->parent->left)
				node_x->parent->left = node_y;
			else
				node_x->parent->right = node_y;
			node_y->left = node_x;
			node_x->parent = node_y;
			root->parent = NULL;
		}

		void rightRotate(t_node *node_x)
		{
			t_node *node_y = node_x->left;

			if (node_y->right != TNULL)
				node_y->right->parent = node_x;
			node_y->parent = node_x->parent;
			if (node_y->parent == NULL)
				root = node_y;
			else if (node_x == node_x->parent->right)
				node_x->parent->right = node_y;
			else
				node_x->parent->left = node_y;
			node_y->right = node_x;
			node_x->parent = node_y;
		
		}

		void insert(T data)
		{
			t_node *node = _newNode(data);
			t_node *node_y = NULL;
			t_node *node_x = root;
			while (node_x != TNULL) //	find position of new node
			{
				node_y = node_x;
				if (node->data.first < node_x->data.first)
					node_x = node_x->left;
				else
					node_x = node_x->right;
			}
			node->parent = node_y; // set new node to position
			if (node_y == NULL)
				root = node;
			else if (node->data.first < node_y->data.first)
				node_y->left = node;
			else
				node_y->right = node;

		//	_insertFix(node);
		
		}

		void deleteNode(T key)
		{
			t_node *node = root;
			t_node *node_z = TNULL;
			t_node *node_x;
			t_node *node_y;
			int y_color;

			while (node != TNULL)
			{
				if (node->data.first == key.first)
					node_z = node;
				if (node->data.first <= key.first)
					node = node->right;
				else
					node = node->left;
			}
			if (node_z == TNULL)
				throw std::invalid_argument("Key not found");
			node_y = node_z;
			y_color = node_y->color;
			if (node_z->left == TNULL)
			{
				node_x = node_z->right;
				_transplant(node_z, node_z->right);
			}
			else if (node_z->right == TNULL)
			{
				node_x = node_z->left;
				_transplant(node_z, node_z->left);
			}
			else
			{
				node_y = min(node_z->right);
				y_color = node_y->color;
				node_x = node_y->right;
				if (node_y->parent == node_z)
					node_x->parent = node_y;
				else
				{
					_transplant(node_y, node_y->right);
					node_y->right = node_z->right;
					node_y->right->parent = node_y;
				}

				_transplant(node_z, node_y);
				node_y->left = node_z->left;
				node_y->left->parent = node_y;
				node_y->color = node_z->color;
			}
			delete node_z;
		//	if (y_color == BLACK)
		//		_deleteFix(node_x);
		}

		T find(T key)
		{
			T ret = _search(root, key)->data;
			return (ret);
		}

		t_node *getRoot(void)
		{
			return this->root;
		}

		t_node *getLast(void)
		{
			return this->TNULL;
		}

		t_node *min(t_node *node)
		{
			t_node *tmp = node;

			while (tmp->left != TNULL)
				tmp = tmp->left;
			return (tmp);
		}

		t_node *min()
		{
			return (min(root));
		}
	};

	template <class T>
	T *node_min(T *node, T *end)
	{
		T *tmp = node;

		while (tmp->left != end)
			tmp = tmp->left;
		return (tmp);
	}

	template <class T>
	T *node_max(T *node, T *end)
	{
		T *tmp = node;

		while (tmp->right != end)
			tmp = tmp->right;
		return (tmp);
	}

	template <class T>
	T *node_root(T *node)
	{
		T *tmp = node;

		while (tmp->parent != NULL)
			tmp = tmp->parent;
		return (tmp);
	}
}

#endif