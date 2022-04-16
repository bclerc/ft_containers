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
#include "iterator/iterator.hpp"
#include <ostream>

#define BLACK 0
#define RED 1

namespace ft
{

	template <class T, class Compare, class Allocator>
	class TREE
	{

	private:
		class Node
		{
		public:
			typedef T value_type;

			T data;
			Node *parent;
			Node *left;
			Node *right;
			int color;

			Node()
				: data(T()), parent(NULL), left(NULL), right(NULL), color(RED)
			{
				return;
			}

			Node(Node *parent, Node *left, Node *right)
				: data(T()), parent(parent), left(left), right(right), color(RED)
			{
				return;
			}

			Node(T data, Node *parent, Node *left, Node *right)
				: data(data), parent(parent), left(left), right(right), color(RED)
			{
				return;
			}
			Node(const Node &other)
				: data(other.data), parent(other.parent), left(other.left), right(other.right), color(RED)
			{
			}
			~Node() {}
		};

	public:
		template <class Value>
		class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, Value>
		{

		public:
			typedef Value value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::value_type iterator_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
			typedef const pointer const_pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;
			typedef const reference const_reference;

		private:
			Node *_min;
			Node *_max;
			Node *root;
			Node *_base;
			Node *_end;

		public:
			bidirectional_iterator(void) : _base(NULL), _end(NULL) {}
			bidirectional_iterator(Node *it, Node *end) : _base(it), _end(end)
			{
				if (_base != _end)
				{
					root = noderoot(_base);
					_max = node_max(root, _end);
					_min = node_min(root, _end);
				}
				else
				{
					root = NULL;
					_max = NULL;
					_min = NULL;
				}
			}

			// bidirectional_iterator (const bidirectional_iterator & rev_it) : _base(rev_it.base())
			//{
			//	return ;
			// }

			virtual ~bidirectional_iterator() {}

			Node* base() const
			{
				return (this->_base);
			}


			reference operator*()
			{
				return (_base->data);
			}

			const_reference operator*() const
			{
				return (_base->data);
			}

			bidirectional_iterator &operator=(const bidirectional_iterator &rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_base = rhs._base;
				this->_end = rhs._end;
				this->_max = rhs._max;
				this->_min = rhs._min;
				return *this;
			}

			bidirectional_iterator &operator++()
			{
				Node *tmp;

				if (_base->right != _end)
				{
					_base = _base->right;
					while (_base->left != _end)
						_base = _base->left;
				}
				else if (_max != _base)
				{
					tmp = _base->parent;
					while (tmp && _base == tmp->right)
					{
						_base = tmp;
						tmp = tmp->parent;
					}
					_base = tmp;
				}
				else if (_base == _end || !_base)
					_base = _end->parent;
				else 
					_base = _end;
				return (*this);
			}

			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			bidirectional_iterator &operator--()
			{
				Node *tmp;
				if (_base == _end || !_base)
					_base = _end->parent;
				else if (this->_base->left != _end)
					_base = node_max(this->_base->left, _end);
				else if (_min != _base)
				{
					tmp = _base->parent;
					while (tmp && _base == tmp->left)
					{
						_base = tmp;
						tmp = tmp->parent;
					}
					_base = tmp;
				}
				else 
					_base = _end;
				return (*this);
			}

			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			pointer operator->()
			{
				return &(_base->data);
			}

			const_pointer operator->() const
			{
				return &(_base->data);
			}

			operator bidirectional_iterator<const T>() const
			{
				return (bidirectional_iterator<const T>(_base, _end));
			}

			bool operator==(bidirectional_iterator<T> const &rhs) const
			{
				return (_base == rhs.base());
			}

			bool operator!=(bidirectional_iterator<T> const &rhs) const
			{
				return (_base != rhs.base());
			}

			bool operator==(bidirectional_iterator<const T> const &rhs) const
			{
				return (_base == rhs.base());
			}

			bool operator!=(bidirectional_iterator<const T> const &rhs) const
			{
				return (_base != rhs.base());
			}
		};

		typedef bidirectional_iterator<T> iterator;
		typedef bidirectional_iterator<const T> const_iterator;

	private:
		typedef typename Allocator::template rebind<Node>::other node_allocator;

		Node *TNULL;
		Node *root;
		Allocator _alloc;
		node_allocator _node_alloc;
		Compare _comp;

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
			else if (_comp(key.first, node->data.first))
				ret = _search(node->left, key);
			else
				ret = _search(node->right, key);
			return (ret);
		}

		void insertFix(Node* k) {
		Node* u;
		while (k->parent->color == 1) {
		if (k->parent == k->parent->parent->right) {
			u = k->parent->parent->left;
			if (u->color == 1) {
			u->color = 0;
			k->parent->color = 0;
			k->parent->parent->color = 1;
			k = k->parent->parent;
			} else {
			if (k == k->parent->left) {
				k = k->parent;
				rightRotate(k);
			}
			k->parent->color = 0;
			k->parent->parent->color = 1;
			leftRotate(k->parent->parent);
			}
		} else {
			u = k->parent->parent->right;

			if (u->color == 1) {
			u->color = 0;
			k->parent->color = 0;
			k->parent->parent->color = 1;
			k = k->parent->parent;
			} else {
			if (k == k->parent->right) {
				k = k->parent;
				leftRotate(k);
			}
			k->parent->color = 0;
			k->parent->parent->color = 1;
			rightRotate(k->parent->parent);
			}
		}
		if (k == root) {
			break;
		}
		}
		root->color = 0;
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
				node = NULL;
			}
		}

	public:
		typedef Node t_node;
		typedef typename T::first_type first_type;
		typedef typename T::second_type second_type;

		TREE()
		{
			_comp = Compare();
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

		ft::pair<iterator, bool> insert(T data)
		{
			Node *node;
			Node *node_y = NULL;
			Node *node_x = root;

			while (node_x != TNULL)
			{
				node_y = node_x;
				if (TNULL->parent->data.first == data.first - 1)
				{
					node_y = TNULL->parent;
					break ;
				}
				if (data.first == node_x->data.first)
					return (ft::make_pair(iterator(node_x, TNULL), false));
				if (_comp(data.first, node_x->data.first))
					node_x = node_x->left;
				else
					node_x = node_x->right;
			}
			node = _newNode(data);
			node->parent = node_y;
			if (node_y == NULL)
				root = node;
			else if (node->data.first < node_y->data.first)
				node_y->left = node;
			else
				node_y->right = node;
			TNULL->parent = max(root);
			insertFix(node);
			return (ft::make_pair(iterator(node, TNULL), true));
		}

		size_t deleteNode(T key)
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
				return (0);
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
			TNULL->parent = max(root);
			return (1);
		}

		void destroy()
		{
			_destroy(root);
			root = TNULL;
		}

		size_t destroy(T key)
		{
			return (deleteNode(key));
		}

		int count(T key) const
		{
			if (_search(root, key) != TNULL)
				return (1);
			return (0);
		}

		Node *find(T key) const
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

		Node *max(Node *node) const
		{
			Node *tmp = node;

			while (tmp->right != TNULL)
				tmp = tmp->right;
			return (tmp);
		}

		Node *max() const
		{
			return (max(root));
		}

		Node *min(Node *node) const
		{
			Node *tmp = node;

			while (tmp->left != TNULL)
				tmp = tmp->left;
			return (tmp);
		}

		Node *min() const
		{
			return (min(root));
		}

		size_t	max_size() const
		{
			return (_node_alloc.max_size());
		}

		void swap(TREE & other)
		{
			std::swap(root, other.root);
			std::swap(TNULL, other.TNULL);
			std::swap(_comp, other._comp);
			std::swap(_alloc, other._alloc);
			std::swap(_node_alloc, other._node_alloc);

		}

		second_type &get_insert(const first_type &key, size_t &size)
		{
			Node *node;
			Node *node_y = NULL;
			Node *node_x = root;

			while (node_x != TNULL) //	find position of new node
			{
				node_y = node_x;
				if (node_x->data.first == key)
					return (node_x->data.second);
				else if (_comp(key, node_x->data.first))
					node_x = node_x->left;
				else
					node_x = node_x->right;
			}
			node = _newNode(T(key, second_type()));
			node->parent = node_y; // set new node to position
			if (node_y == NULL)
				root = node;
			else if (_comp(node->data.first, node_y->data.first))
				node_y->left = node;
			else
				node_y->right = node;
			size++;
			TNULL->parent = max(root);
			return (node->data.second);
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
	T *noderoot(T *node)
	{
		T *tmp = node;

		while (tmp->parent != NULL)
			tmp = tmp->parent;
		return (tmp);
	}
}

#endif