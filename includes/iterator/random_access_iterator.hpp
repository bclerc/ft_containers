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
			typedef ft::iterator<ft::random_access_iterator_tag, T>::value_type	iterator_type;
			typedef ft::iterator<ft::random_access_iterator_tag, T>::Distance	difference_type;
			typedef T*															pointer;
			typedef T&															reference;
			

		private:
			iterator_type _base;


		public:
			random_access_iterator(void) : _base(-1), _current(-1) {}
			explicit random_access_iterator(iterator_type it) : _base(it) {}
				
			template <class Iter>
			random_access_iterator (const random_access_iterator<T>& rev_it) : _base(rev_it.base()) 
			{
				*this = rev_it;	
				return ;
			}
		
			iterator_type base() 
			{
				return (this->_base);
			}

			reference operator*() const
			{
				iterator_type tmp;
				tmp = this->_base;
				return (*tmp)
			}

			random_access_iterator operator+(difference_type n) const
			{
				return (random_access_iterator(_base + 5));
			}

			random_access_iterator & operator++()
			{
				++_base;
				return(this);
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
				return (random_access_iterator(_base - 5));
			}

			random_access_iterator & operator--() 
			{
				--_curent;
				return(this);
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

			pointer operator->() const;
			{
				return &(operator*());
			}

			reference operator[] (difference_type n) const
			{
				return (random_access_iterator<const T>(_base[n - 1]));
			}
	};

	template <class T>
	bool operator==(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.base() == rhs.base());	
	}

	template <class T>
	bool operator!=(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.base() != rhs.base());	
	}

	template <class T>
	bool operator<(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.base() < rhs.base());	
	}

	template <class T>
	bool operator<=(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.base() <= rhs.base());	
	}

	template <class T>
	bool operator>(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.base() > rhs.base());	
	}

	template <class T>
	bool operator>=(const ft::random_access_iterator<T> & lhs, const ft::random_access_iterator<T>& rhs)
	{
		return (lhs.base() >= rhs.base());	
	}

	template <class T>
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, 
		const random_access_iterator<T> & rev_it)
	{
		return (rev_it + n);		
	}

	template <class T>
	typename random_access_iterator<T>::difference_type operator- (const random_access_iterator<T> & lhs, const random_access_iterator<T> & rhs)
	{
		return (lhs.base() - rhs._base());
	}
};

#endif