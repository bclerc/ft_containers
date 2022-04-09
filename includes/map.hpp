/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:48:13 by bclerc            #+#    #+#             */
/*   Updated: 2022/04/09 07:38:59 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include "equal.hpp"
#include "iterator/reverse_iterator.hpp"
#include "iterator/bidirectional_iterator.hpp"
#include "avl.hpp"


namespace ft 
{
	template <class T> struct less : std::binary_function <T,T,bool> {
		bool operator() (const T& x, const T& y) const 
		{
			return x < y ;
		}
	};

	template<
		class Key,
		class T,
		class Compare = ft::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class map
	{
		public:
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef	ft::pair<Key, T>									value_type;
			typedef std::size_t											size_type;
			typedef std::ptrdiff_t										difference_type;
			typedef	Compare												key_compare;
			typedef Allocator											allocator_type;
			typedef value_type &										reference;
			typedef const value_type & 									const_reference;
			typedef	typename Allocator::pointer							pointer;
			typedef typename Allocator::const_pointer					const_pointer;
			typedef RBT<ft::pair<Key, T>, Compare>						tree;
			typedef bidirectional_iterator<typename tree::t_node>		iterator;
			typedef bidirectional_iterator<const typename  tree::t_node>			const_iterator;
			//typedef reverse_iterator<Iterator>					reverse_iterator;
			//typedef	reverse_iterator<const_iterator>			const_reverse_iterator;
		
		private:
			Allocator _alloc;
			size_t _size;
			tree	rbt;

		public:
			map()
			{
				_size = 0;
				_alloc = Allocator();
			}

			explicit map( const Compare& comp,
						const Allocator& alloc = Allocator() );
			template< class InputIt >

			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator());
			map( const map& other );
			~map()
			{
	
			}
			void print()
			{
				rbt.printHelper(rbt.getRoot(), " ", true);
			}
			map& operator=( const map& other );
			allocator_type get_allocator() const
			{
				return _alloc;
			}
			T& at( const Key& key );
			const T& at( const Key& key ) const;
			T& operator[]( const Key& key );
			iterator begin()
			{
				return (iterator(rbt.min(), rbt.getLast()));
			}
			iterator end()
			{
				return iterator(rbt.getLast(), rbt.getLast());
			}
			//reverse_iterator rbegin();
			//const_reverse_iterator rbegin() const;
			//sreverse_iterator rend();
			//const_reverse_iterator rend() const;

			bool empty() const
			{
				return !(_size > 0);
			}

			size_type size() const
			{
				return _size;
			}

			size_type max_size() const
			{
				return (this->_alloc.max_size());
			}

			void clear();
			ft::pair<long, bool> insert( const value_type& value )
			{
				_size++;
				rbt.insert(value);
				return (make_pair(NULL, true));
			}
			iterator insert( iterator hint, const value_type& value );
			void erase( iterator pos );
			void erase( iterator first, iterator last );
			size_type erase( const Key& key );
			void swap( map& other );
			size_type count( const Key& key ) const;
			iterator find( const Key& key );
			const_iterator find( const Key& key ) const;
			ft::pair<iterator,iterator> equal_range( const Key& key );
			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;
			iterator lower_bound( const Key& key );
			const_iterator lower_bound( const Key& key ) const;
			iterator upper_bound( const Key& key );
			const_iterator upper_bound( const Key& key ) const;
	};
};

#endif