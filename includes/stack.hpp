/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:56:08 by bclerc            #+#    #+#             */
/*   Updated: 2022/03/20 02:29:52 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
 
# include "vector.hpp"

namespace ft {

	template<class T, class Container = ft::vector<T> >
	class stack {

		public:
			typedef Container							container_type;
			typedef	typename Container::value_type		value_type;
			typedef typename Container::size_type		size_type;
			typedef typename Container::reference		reference;
			typedef typename Container::const_reference	const_reference;

		private: 
			Container container;

		public :

			explicit stack( const Container& cont = Container())
			{
				container = cont;
			}

			stack (const stack<T, Container> & other)
			{
				this->container = other.container;
				return ;
			}

			~stack(void){};

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

			friend bool operator== ( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
			{
				return (lhs.container == rhs.container);
			}

			friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{
				return (lhs.container != rhs.container);
			}

			friend bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{
				return (lhs.container < rhs.container);
			}

			friend bool operator<= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{
				return (lhs.container <= rhs.container);
			}

			friend bool operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{
				return (lhs.container > rhs.container);
			}

			friend bool operator>= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{
				return (lhs.container >= rhs.container);
			}
	};

};

#endif