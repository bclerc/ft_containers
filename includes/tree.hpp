/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 03:15:51 by bclerc            #+#    #+#             */
/*   Updated: 2022/04/09 07:53:05 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
#define TREE_HPP

#include "pair.tpp"
#include <ostream>

#define BLACK 0
#define RED 1

namespace ft
{

	template <class T, class Compare, class Allocator = std::allocator<T> >
	class TREE
	{
	
		private:
			class Node
			{
				public:
					typedef T		value_type;

					T		data;
					Node*	parent;
					Node*	left;
					Node*	right;
					int		color;

					Node()
					: data(T()), parent(NULL), left(NULL), right(NULL), color(RED)
					{
						return ;
					}
					
					Node(Node* parent, Node* left, Node* right)
					: data(T()), parent(parent), left(left), right(right), color(RED)
					{
						return ;
					}

					Node(T data, Node* parent, Node* left, Node* right)
					: data(data), parent(parent), left(left), right(right), color(RED)
					{
						return ;
					}
					~Node() {}
			};

			typedef std::allocator<Node> node_allocator;

			Node			*TNULL;
			Node			*root;
			Allocator 		_alloc;
			node_allocator	_node_alloc; 

			Node *_newNode(T data)
			{
				Node *node = _node_alloc.allocate(1);
				_node_alloc.construct(node, Node(data, NULL, TNULL, TNULL));
				node->color = RED; // Red by default
				return node;
			}

			Node *_search(Node *node, T key) const
			{
				Node *ret;

				if (node == TNULL || key.first == node->data.first)
					ret = node;
				else if (key.first < node->data.first)
					ret = _search(node->left, key);
				else
					ret = _search(node->right, key);
				if (ret == TNULL)
					throw std::invalid_argument("Tree::Node: not found");
				return (ret);
			}

			// Replace the first node by second for detach the deleted node from rbt
			void _transplant(Node *first, Node *second)
			{
				if (!first->parent)
					root = second;
				else if (first == first->parent->left)
					first->parent->left = second;
				else
					first->parent->right = second;
				second->parent = first->parent;
			}

			void _destroy(Node *node)
			{
				if (node != TNULL)
				{
					_destroy(node->left);
					_destroy(node->right);
					_node_alloc.destroy(node);
					_node_alloc.deallocate(node, 1);
				}
			}

		public:
			typedef Node	t_node;

			TREE()
			{
				_alloc = Allocator();
				_node_alloc = node_allocator();
				TNULL = _node_alloc.allocate(1);
				_node_alloc.construct(TNULL, Node(TNULL, TNULL, TNULL));
				root = TNULL;
				return;
			}

			~TREE()
			{
				if (TNULL)
				{
					destroy();
					_node_alloc.destroy(TNULL);
					_node_alloc.deallocate(TNULL, 1);
					TNULL = NULL;
				}
			}

			void leftRotate(Node *node_x)
			{
				Node *node_y = node_x->right;

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

			void rightRotate(Node *node_x)
			{
				Node *node_y = node_x->left;

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

			Node *insert(T data)
			{
				Node *node;
				Node *node_y = NULL;
				Node *node_x = root;
				
				while (node_x != TNULL) //	find position of new node
				{
					if (node_x->data.first == data.first)
						throw std::invalid_argument("Key already exist");
					node_y = node_x;
					if (data.first < node_x->data.first)
						node_x = node_x->left;
					else
						node_x = node_x->right;
				}
				node = _newNode(data);
				node->parent = node_y; // set new node to position
				if (node_y == NULL)
					root = node;
				else if (node->data.first < node_y->data.first)
					node_y->left = node;
				else
					node_y->right = node;
				return (node);
			}

			void deleteNode(T key)
			{
				Node *node = root;
				Node *node_z = TNULL;
				Node *node_x;
				Node *node_y;
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
				_node_alloc.destroy(node_z);
				_node_alloc.deallocate(node_z, 1);
			}

			void destroy()
			{
				_destroy(root);
				root = TNULL;
			}

			void destroy(T key)
			{
				deleteNode(key);
			}

			int count (T key ) const
			{
				try {
					_search(root, key);
				} catch (const std::exception& e) {
					return (0); }
				return (1);
			}
		
			Node *find(T key)
			{
				Node *ret = _search(root, key);
				return (ret);
			}

			Node *getRoot(void) const
			{
				return this->root;
			}

			Node *getLast(void) const
			{
				return this->TNULL;
			}

			Node *min(Node *node)
			{
				Node *tmp = node;

				while (tmp->left != TNULL)
					tmp = tmp->left;
				return (tmp);
			}

			Node *min()
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