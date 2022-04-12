/* *** *********************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:21:35 by bclerc            #+#    #+#             */
/*   Updated: 2022/02/23 20:47:38 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef const_bidirectional_iterator_HPP
# define const_bidirectional_iterator_HPP

#include "iterator.hpp"
#include "../tree.hpp"

namespace ft {

	template <class T, class Value>
	class const_bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {

		public:
			typedef Value																				value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::value_type			iterator_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer			pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference			reference;
		
		private:

			T* _min;
			T* _max;
			T* _root;
			T* _base;
			T* _end;

		public:
			const_bidirectional_iterator(void) : _base(NULL)
			{}

			const_bidirectional_iterator(T *it, T *end) : _base(it), _end(end) {
				if (_base != _end)
				{
					_root = node_root(_base);
					_max = node_max(_root, _end);
					_min  = node_min(_root, _end);
				}
			}
				
			const_bidirectional_iterator (const const_bidirectional_iterator & rev_it)
			{
				_base = rev_it._base;
				_min = rev_it._min;
				_max = rev_it._max;
				_end = rev_it._end;
				_root = rev_it._root;
				return ;
			}

			virtual ~const_bidirectional_iterator() {}

			reference base()
			{
				return (_base->data);
			}

			const value_type & operator*() const
			{
				return (&const_cast<value_type>(_base->data));
			}

			const_bidirectional_iterator &operator=(const const_bidirectional_iterator & rhs)
			{
				_base = rhs._base;
				_min = rhs._min;
				_max = rhs._max;
				_end = rhs._end;
				_root = rhs._root;
				
				return *this;
			}

			const_bidirectional_iterator & operator++()
			{
				T*	tmp;

				if (_base->right != _end)
				{
					_base = _base->right;
					while (_base->left != _end)
						_base = _base->left;
				}
				else if (_base != _end && _max != _base)
				{
					tmp = _base->parent;
					while (tmp && _base == tmp->right)
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

			const_bidirectional_iterator operator++(int)
			{
				const_bidirectional_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			const_bidirectional_iterator & operator--() 
			{
				T*	tmp;

				if (this->_base->left != _end)
					_base = node_max(this->_base->left, _end);
				else if (_base != _end && _min != _base)
				{
					tmp = _base->parent;
					while  (tmp && _base == tmp->left)
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

			const_bidirectional_iterator operator--(int)
			{
				const_bidirectional_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			value_type * operator->() const
			{
				return &(operator*());
			}
			

            operator const_bidirectional_iterator<const T, value_type> () const
            {
				 return (const_bidirectional_iterator<const T, value_type>(this->_base));
			}

			bool operator==(ft::const_bidirectional_iterator<T, value_type> const& rhs)
			{
				return (_base == rhs._base);	
			}

			bool operator!=(ft::const_bidirectional_iterator<T, value_type> const& rhs)
			{
				return (!(*this == rhs));	
			}
	};

};

#endif