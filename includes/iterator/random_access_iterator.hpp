/* *** *********************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_access_iterator.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:21:35 by bclerc            #+#    #+#             */
/*   Updated: 2022/02/23 20:47:38 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

	template <class T>
	class random_access_iterator : public ft::iterator<ft::random_access_iterator_tag, T> {

		public:
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type		iterator_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
			typedef T*																			pointer;
			typedef T&																			reference;
			

		private:
			pointer _base;


		public:
			random_access_iterator(void) : _base(NULL) {}
			random_access_iterator(pointer it) : _base(it) {}
				
			random_access_iterator (const random_access_iterator & rev_it) : _base(rev_it.base())
			{
				return ;
			}
		
			virtual ~random_access_iterator() {}

			pointer base() const
			{
				return (this->_base);
			}

			reference operator*() const
			{
				return (*this->_base);
			}


			random_access_iterator &operator=(const random_access_iterator & rhs)
			{
				if (this == &rhs)
					return (*this);
				this->_base = (rhs._base);
				return *this;
			}


			random_access_iterator operator+(difference_type n) const
			{
				T *tmp;
				tmp = _base + n;
				return (random_access_iterator(tmp));
			}

			random_access_iterator & operator++()
			{
				++_base;
				return(*this);
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			random_access_iterator operator+=(difference_type n)
			{
				_base += n;
				return (*this);
			}

			random_access_iterator operator-(difference_type n) const
			{
				T *tmp;
				tmp = _base - n;
				return (random_access_iterator(tmp));
			}

			random_access_iterator & operator--() 
			{
				--_base;
				return(*this);
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			random_access_iterator operator-=(difference_type n)
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

            operator random_access_iterator<const T> () const
            {
				 return (random_access_iterator<const T>(this->_base));
			}
	};

	template <class T, class Other>
	bool operator==(ft::random_access_iterator<T> const & lhs, ft::random_access_iterator<Other> const& rhs)
	{
		return (lhs.base() == rhs.base());	
	}

	template <class T, class Other>
	bool operator!=(ft::random_access_iterator<T> const & lhs, ft::random_access_iterator<Other> const& rhs)
	{
		return (lhs.base() != rhs.base());	
	}

	template <class T, class Other>
	bool operator<(ft::random_access_iterator<T> const & lhs, ft::random_access_iterator<Other> const& rhs)
	{
		return (lhs.base() < rhs.base());	
	}

	template <class T, class Other>
	bool operator<=(ft::random_access_iterator<T> const & lhs, ft::random_access_iterator<Other> const& rhs)
	{
		return (lhs.base() <= rhs.base());	
	}

	template <class T, class Other>
	bool operator>(ft::random_access_iterator<T> const & lhs, ft::random_access_iterator<Other> const& rhs)
	{
		return (lhs.base() > rhs.base());	
	}

	template <class T, class Other>
	bool operator>=(ft::random_access_iterator<T> const & lhs, ft::random_access_iterator<Other> const& rhs)
	{
		return (lhs.base() >= rhs.base());	
	}

	template <class T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, 
		const random_access_iterator<T> & rev_it)
	{
		return (rev_it + n);		
	}

	template <class T, class O>
	typename random_access_iterator<T>::difference_type operator- (random_access_iterator<T> const & lhs, random_access_iterator<O>  const & rhs)
	{
		return (lhs.base() - rhs.base());
	}
};

#endif