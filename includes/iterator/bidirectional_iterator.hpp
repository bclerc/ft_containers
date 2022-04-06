/* *** *********************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bidirectional_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:21:35 by bclerc            #+#    #+#             */
/*   Updated: 2022/02/23 20:47:38 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef bidirectional_iterator_HPP
# define bidirectional_iterator_HPP

#include "iterator.hpp"
#include "../avl.hpp"
#include <typeinfo>

namespace ft {

	template <class T>
	class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {

		public:
			typedef typename T::value_type																value_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::value_type		iterator_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type	difference_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer			pointer;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference		reference;
			typedef T*																					node;
		private:
			T* _base;
			T* _end;

		public:
			bidirectional_iterator(void) : _base(NULL) {}
			bidirectional_iterator(T *it, T* end) : _base(it), _end(end) {}
				
			bidirectional_iterator (const bidirectional_iterator & rev_it) : _base(rev_it.base())
			{
				return ;
			}
		
			virtual ~bidirectional_iterator() {}

			reference base() const
			{
				return (this->_base->data);
			}

			reference operator*() const
			{
				return (_base->data);
			}

			bidirectional_iterator &operator=(const bidirectional_iterator & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_base = (rhs._base);
				return *this;
			}


			bidirectional_iterator & operator++()
			{
				if (_base->left != _end)
				{
					std::cout << "Coucou ? " << _base->data.first << std::endl;
					_base = _base->left;
					std::cout << "Coucou ? " << _base->data.first << std::endl;

				}
				return (*this);
			}

			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			bidirectional_iterator & operator--() 
			{
				--_base;
				return(*this);
			}

			bidirectional_iterator operator--(int)
			{
				bidirectional_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			pointer operator->() const
			{
				return &(_base->data);
			}

            operator bidirectional_iterator<const T> () const
            {
				 return (bidirectional_iterator<const T>(this->_base));
			}
	};

	template <class T, class Other>
	bool operator==(ft::bidirectional_iterator<T> const & lhs, ft::bidirectional_iterator<Other> const& rhs)
	{
		return (lhs.base() == rhs.base());	
	}

	template <class T, class Other>
	bool operator!=(ft::bidirectional_iterator<T> const & lhs, ft::bidirectional_iterator<Other> const& rhs)
	{
		return (lhs.base() != rhs.base());	
	}
};

#endif