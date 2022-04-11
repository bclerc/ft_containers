/* *** *********************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator_const.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:21:35 by bclerc            #+#    #+#             */
/*   Updated: 2022/02/23 20:47:38 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef BIDIRECTIONAL_ITERATOR_CONST_HPP
# define BIDIRECTIONAL_ITERATOR_CONST_HPP

#include "iterator.hpp"
#include "../tree.hpp"

namespace ft {

	template <class T>
	class bidirectional_iterator_const : public ft::iterator<ft::bidirectional_iterator_tag, T> {

		public:
			typedef typename T::value_type																value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::value_type		iterator_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer			pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference		reference;
			typedef T*
																							node;
		private:
			T* _min;
			T* _max;
			T* _root;
			T* _base;
			T* _end;
		public:
			bidirectional_iterator_const(void) : _base(NULL) {}
			bidirectional_iterator_const(T *it, T *end) : _base(it), _end(end) {
				if (_base != _end)
				{
					_root = node_root(_base);
					_max = node_max(_root, _end);
					_min  = node_min(_root, _end);
				}
			}
				
			//bidirectional_iterator_const (const bidirectional_iterator_const & rev_it) : _base(rev_it.base())
			//{
			//	return ;
			//}
		
			virtual ~bidirectional_iterator_const() {}

			reference base() const
			{
				return (this->_base->data);
			}

			reference operator*() const
			{
				return (_base->data);
			}

			bidirectional_iterator_const &operator=(const bidirectional_iterator_const & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_base = (rhs._base);
				return *this;
			}


			bidirectional_iterator_const & operator++()
			{
				T*	tmp;

				if (this->_base->right != _end)
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

			bidirectional_iterator_const operator++(int)
			{
				bidirectional_iterator_const tmp = *this;
				++(*this);
				return (tmp);
			}

			bidirectional_iterator_const & operator--() 
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

			bidirectional_iterator_const operator--(int)
			{
				bidirectional_iterator_const tmp = *this;
				--(*this);
				return (tmp);
			}

			pointer operator->() const
			{
				return &(_base->data);
			}

            operator bidirectional_iterator_const<const T> () const
            {
				 return (bidirectional_iterator_const<const T>(this->_base));
			}
	};

	template <class T, class Other>
	bool operator==(ft::bidirectional_iterator_const<T> const & lhs, ft::bidirectional_iterator_const<Other> const& rhs)
	{
		return (lhs->first == rhs->first && lhs->second == lhs->second);	
	}

	template <class T, class Other>
	bool operator!=(ft::bidirectional_iterator_const<T> const & lhs, ft::bidirectional_iterator_const<Other> const& rhs)
	{
		return (!(lhs == rhs));	
	}
};

#endif