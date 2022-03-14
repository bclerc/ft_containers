/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 05:16:19 by bclerc            #+#    #+#             */
/*   Updated: 2022/03/14 05:40:36 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:56:08 by bclerc            #+#    #+#             */
/*   Updated: 2022/03/14 05:12:13 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
 
# include "vector.hpp"

namespace ft {

	template<class T, class Container = ft::vector<T> >
	class stack {

		public:
			typedef Container					container_type;
			typedef	Container::value_type		value_type;
			typedef Container::size_type		size_type;
			typedef Container::reference		reference;
			typedef Container::const_reference	const_reference;

		private: 
			Container container;

		public :
			stack (void) 
			{
				container = Container();
			}

			explicit stack( const Container& cont = Container());
			{
				container = cont();
			}

			stack (const stack & other)
			{
				container = Container(other);
			}

		
			~stack(void)
			{
				Container::~Container();
			};

			stack& operator=( const stack & other )
			{
				*this = other;
			}

			size_type	size()
			{
				return (container.size());
			}

			bool empty() const
			{
				return (container.empty());
			}

			size_type	capacity()
			{
				return (container.capacity());
			}

			reference top()
			{
				return (container.back());
			}

			const_reference top() const
			{
				return (container.back());
			}

			void	push( const value_type & value)
			{
				container.push_back(value);
			}

			void	pop()
			{
				container.pop_back();
			}
	};

	template <class T>
  	bool operator== (const stack<T>& lhs, const stack<T>& rhs)
	{
		if (rhs.begin() == rhs.end() && lhs.begin() != lhs.end())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T>
  	bool operator!= (const stack<T>& lhs, const stack<T>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T>
  	bool operator<  (const stack<T>& lhs, const stack<T>& rhs)
	{
		
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end()));
	}

	template <class T>
 	bool operator<= (const stack<T>& lhs, const stack<T>& rhs)
	{
		return (!(lhs > rhs));
	}
	template <class T>
  	bool operator> (const stack<T>& lhs, const stack<T>& rhs)
  	{
		return (!(lhs < rhs));
  	}

	template <class T>
  	bool operator>= (const stack<T>& lhs, const stack<T>& rhs)
  	{
		  return !(lhs < rhs);
  	}
};

#endif