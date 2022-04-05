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

namespace ft {

	template <class T>
	class bidirectional_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {

		public:
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type		iterator_type;
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
			typedef T*																			pointer;
			typedef T&																			reference;
			

		private:
			*RBT _base;

		public:
			bidirectional_iterator(void) : _base(NULL) {}
			bidirectional_iterator(pointer it) : _base(it) {}
				
			bidirectional_iterator (const bidirectional_iterator & rev_it) : _base(rev_it.base())
			{
				return ;
			}
		
			virtual ~bidirectional_iterator() {}

			pointer base() const
			{
				return (this->_base);
			}

			reference operator*() const
			{
				return (_base.);
			}


			bidirectional_iterator &operator=(const bidirectional_iterator & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_base = (rhs._base);
				return *this;
			}


			bidirectional_iterator operator+(difference_type n) const
			{
				T *tmp;
				tmp = _base + n;
				return (bidirectional_iterator(tmp));
			}

			bidirectional_iterator & operator++()
			{
				++_base;
				return(*this);
			}

			bidirectional_iterator operator++(int)
			{
				bidirectional_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			bidirectional_iterator operator+=(difference_type n)
			{
				_base += n;
				return (*this);
			}

			bidirectional_iterator operator-(difference_type n) const
			{
				T *tmp;
				tmp = _base - n;
				return (bidirectional_iterator(tmp));
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

			bidirectional_iterator operator-=(difference_type n)
			{
				_base -= n;
				return (*this);
			}

			pointer operator->() const
			{
				return &(operator*());
			}

			reference operator[] (difference_type n) const
			{
				return (*(_base + n));
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

	template <class T, class Other>
	bool operator<(ft::bidirectional_iterator<T> const & lhs, ft::bidirectional_iterator<Other> const& rhs)
	{
		return (lhs.base() < rhs.base());	
	}

	template <class T, class Other>
	bool operator<=(ft::bidirectional_iterator<T> const & lhs, ft::bidirectional_iterator<Other> const& rhs)
	{
		return (lhs.base() <= rhs.base());	
	}

	template <class T, class Other>
	bool operator>(ft::bidirectional_iterator<T> const & lhs, ft::bidirectional_iterator<Other> const& rhs)
	{
		return (lhs.base() > rhs.base());	
	}

	template <class T, class Other>
	bool operator>=(ft::bidirectional_iterator<T> const & lhs, ft::bidirectional_iterator<Other> const& rhs)
	{
		return (lhs.base() >= rhs.base());	
	}

	template <class T>
	bidirectional_iterator<T> operator+(typename bidirectional_iterator<T>::difference_type n, 
		const bidirectional_iterator<T> & rev_it)
	{
		return (rev_it + n);		
	}

	template <class T, class O>
	typename bidirectional_iterator<T>::difference_type operator- (bidirectional_iterator<T> const & lhs, bidirectional_iterator<O>  const & rhs)
	{
		return (lhs.base() - rhs.base());
	}
};

#endif