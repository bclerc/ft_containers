/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 17:57:09 by bclerc            #+#    #+#             */
/*   Updated: 2022/03/03 00:52:36 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "iterators_traits.hpp"

namespace ft {

	template <class Iterator>
	class reverse_iterator {

		public:
			typedef Iterator 													iterator_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference; 

		private:
			iterator_type _base;

		public:
			reverse_iterator(void) : _base(-1) {}
			explicit reverse_iterator(iterator_type it) : _base(it){}
				
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iterator>& rev_it) : _base(rev_it.base())
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
				return (*(--tmp));
			}

			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(_base - n));
			}

			reverse_iterator & operator++()
			{
				--_base;
				return(this);
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			reverse_iterator operator+=(difference_type n)
			{
				_base -= n;
				return (*this);
			}

			reverse_iterator operator-(difference_type n) const
			{
				return (reverse_iterator(_base +  5));
			}

			reverse_iterator & operator--() 
			{
				++_base;
				return(this);
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			reverse_iterator operator-=(difference_type n)
			{
				_base += n;
				return (*this);
			}

			pointer operator->() const
			{
				return &(operator*());
			}

			reference operator[] (difference_type n) const
			{
				return (_base()[-n - 1]);
			}
	};

	template <class Iterator>
	bool operator==(const ft::reverse_iterator<Iterator> & lhs, const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() == rhs.base());	
	}

	template <class Iterator>
	bool operator!=(const ft::reverse_iterator<Iterator> & lhs, const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() != rhs.base());	
	}

	template <class Iterator>
	bool operator<(const ft::reverse_iterator<Iterator> & lhs, const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() < rhs.base());	
	}

	template <class Iterator>
	bool operator<=(const ft::reverse_iterator<Iterator> & lhs, const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() <= rhs.base());	
	}

	template <class Iterator>
	bool operator>(const ft::reverse_iterator<Iterator> & lhs, const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() > rhs.base());	
	}

	template <class Iterator>
	bool operator>=(const ft::reverse_iterator<Iterator> & lhs, const ft::reverse_iterator<Iterator>& rhs)
	{
		return (lhs.base() >= rhs.base());	
	}

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, 
		const reverse_iterator<Iterator> & rev_it)
	{
		return (rev_it + n);		
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator> & lhs, const reverse_iterator<Iterator> & rhs)
	{
		return (lhs.base() - rhs._base());
	}
};
#endif