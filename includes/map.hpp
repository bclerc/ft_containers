/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:48:13 by bclerc            #+#    #+#             */
/*   Updated: 2022/04/11 15:34:11 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include "equal.hpp"
#include "iterator/reverse_iterator.hpp"
#include "tree.hpp"


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
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, T> >
	>
	class map
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef	ft::pair<Key, T>										value_type;
			typedef std::size_t												size_type;
			typedef std::ptrdiff_t											difference_type;
			typedef	Compare													key_compare;
			typedef Allocator												allocator_type;
			typedef value_type &											reference;
			typedef const value_type & 										const_reference;
			typedef	typename Allocator::pointer								pointer;
			typedef typename Allocator::const_pointer						const_pointer;
			typedef TREE<ft::pair<Key, T>, Compare, allocator_type>			tree;
			typedef bidirectional_iterator<typename tree::t_node>			iterator;
			typedef bidirectional_iterator<const typename  tree::t_node>	const_iterator;
			typedef typename ft::reverse_iterator<iterator>							reverse_iterator;
			typedef	typename ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		
		private:
			Allocator 	_alloc;
			Compare		_comp;
			size_t 		_size;
			tree		_rbt;

		public:
			map()
			{	
				_size = 0;
				_alloc = Allocator();
				_comp = Compare();
			}

			explicit map( const Compare& comp,
						const Allocator& alloc = Allocator() )
			{
				_size = 0;
				_alloc = alloc;
				_comp = comp;
			}

			template< class InputIt >
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			{
				_size = 0;
				_alloc = alloc;
				_comp = comp;

				while (first != last)
				{
					_rbt[first->first] = first->second;
					first++;
				}				
			}

			map( const map& other );
			~map() 	{}

			map& operator=( const map& other )
			{
				*this = other;
				return (*this);
			}

			allocator_type get_allocator() const
			{
				return _alloc;
			}

			T& at( const Key& key )
			{
				return (find(key)->second);
			}

			const T& at( const Key& key ) const
			{
				return (find(key)->second);
			}

			T& operator[]( const Key& key )
			{
				return(_rbt[key]);
			}

			iterator begin()
			{
				return (iterator(_rbt.min(), _rbt.getLast()));
			}
			iterator end()
			{
				return iterator(_rbt.getLast(), _rbt.getLast());
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(begin()));
			}
			//const_reverse_iterator rbegin() const;

			reverse_iterator rend()
			{
				return (reverse_iterator(end()));
			}
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

			void clear()
			{
				_rbt.destroy();
				_size = 0;
			}

			ft::pair<iterator, bool> insert( const value_type& value )
			{
				ft::pair<iterator, bool> ret;

				ret = _rbt.insert(value);
				if (ret.second)
					_size++;
				return (ret);				
			}

			iterator insert( iterator hint, const value_type& value )
			{
				(void)hint;
				return (insert(value)->first);
			}

			void erase( iterator pos )
			{
				_rbt.destroy(pos.base());
				_size--;
			}

			void erase( iterator first, iterator last )
			{
				iterator tmp = first;
				if (first != last)
					erase(++first, last);
				_rbt.destroy(tmp.base());
				_size --;
			}

			size_type erase( const Key& key )
			{
				if (_rbt.destroy(ft::make_pair(key, T())))
				{
					_size--;
					return (1);
				}
				return (0);
			}

			void swap( map& other );

			size_type count( const Key& key ) const
			{
				return (_rbt.count(ft::make_pair(key, T())));
			}

			iterator find( const Key& key )
			{
				iterator ret;
				value_type search;

				search = ft::make_pair(key, T());
				ret = iterator(_rbt.find(search), _rbt.getLast());
				return (ret);
			}

			const_iterator find( const Key& key ) const;

			ft::pair<iterator,iterator> equal_range( const Key& key )
			{
				return (make_pair(lower_bound(key), upper_bound(key)));
			}
			
			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const;

			iterator lower_bound( const Key& key )
			{
				iterator it = begin();
				iterator m_end = end();
				iterator parent = it;

				while (it != m_end)
				{
					if (!_comp(key, it->first))
						return (iterator(parent));
					parent = it;
					it++;
				}
				return (end());
			}

			const_iterator lower_bound( const Key& key ) const;
			
			iterator upper_bound( const Key& key )
			{
				iterator it = begin();
				iterator m_end = end();
				iterator parent = it;

				while (it != m_end)
				{
					if (_comp(key, it->first))
						return (iterator(it));
					parent = it;
					it++;
				}
				return (end());
			}

			const_iterator upper_bound( const Key& key ) const;
	};
};

#endif