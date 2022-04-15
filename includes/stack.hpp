/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:56:08 by bclerc            #+#    #+#             */
/*   Updated: 2022/04/15 15:42:28 by vscode           ###   ########.fr       */
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

		public :
			Container c;

			explicit stack( const Container& cont = Container())
			{
				c = cont;
			}

			stack (const stack<T, Container> & other)
			{
				this->c = other.c;
				return ;
			}

			~stack(void){};

			stack& operator=( const stack & other )
			{
				*this = other;
			}

			size_type	size()
			{
				return (c.size());
			}

			bool empty() const
			{
				return (c.empty());
			}

			size_type	capacity()
			{
				return (c.capacity());
			}

			reference top()
			{
				return (c.back());
			}

			const_reference top() const
			{
				return (c.back());
			}

			void	push( const value_type & value)
			{
				c.push_back(value);
			}

			void	pop()
			{
				c.pop_back();
			}

			friend bool operator== ( const stack<T,Container>& lhs, const stack<T,Container>& rhs )
			{
				return (lhs.c == rhs.c);
			}

			friend bool operator!= (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{
				return (lhs.c != rhs.c);
			}

			friend bool operator<  (const stack<T, Container>& lhs, const stack<T, Container>& rhs)
			{
				return (lhs.c < rhs.c);
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