/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 01:48:13 by bclerc            #+#    #+#             */
/*   Updated: 2022/04/14 11:25:33 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <memory>
#include "iterator/reverse_iterator.hpp"
#include "equal.hpp"

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
			typedef	ft::pair<const Key, T>									value_type;
			typedef std::size_t												size_type;
			typedef std::ptrdiff_t											difference_type;
			typedef	Compare													key_compare;
			typedef Allocator												allocator_type;
			typedef value_type &											reference;
			typedef const value_type & 										const_reference;
			typedef	typename Allocator::pointer								pointer;
			typedef typename Allocator::const_pointer						const_pointer;
			typedef TREE<value_type, Compare, allocator_type>				tree;
			typedef typename tree::iterator									iterator;
			typedef	typename tree::const_iterator							const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef	typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		
		private:
			Allocator 	_alloc;
			Compare		_comp;
			size_t 		_size;
			tree		_rbt;

			class value_compare {
				
				protected:
					Compare comp;
				public :
					value_compare(void) : comp(Compare())
					{
						return ;
					}

					value_compare(Compare compare) : comp(compare)
					{
						return ;
					}
					
					~value_compare()
					{
						return ;
					}

					bool operator()(const value_type& lhs, const value_type& rhs)
					{
						return (comp(lhs.first, rhs.first));
					}
			};

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

				this->insert(first, last);
			}

			map( const map& other ) : _alloc(other._alloc), _comp(other._comp) , _rbt()
			{
				_alloc = other._alloc;
				_comp = other._comp;
				_size = 0;

				this->insert(other.begin(), other.end());
				return ;
			}

			~map() 	{}

			map& operator=( const map& other )
			{
				if (this == &other)
					return (*this);

				this->clear();
				insert(other.begin(), other.end());
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
				return(_rbt.get_insert(key, _size));
			}

			iterator begin()
			{
				return (iterator(_rbt.min(), _rbt.getLast()));
			}

			iterator end()
			{
				return iterator(_rbt.getLast(), _rbt.getLast());
			}

			const_iterator begin() const
			{
				return (const_iterator(_rbt.min(), _rbt.getLast()));
			}
			
			const_iterator end() const
			{
				return const_iterator(_rbt.getLast(), _rbt.getLast());
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(end()));
			}
			const_reverse_iterator rbegin() const
			{
				return (reverse_iterator(end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(begin()));
			}
			const_reverse_iterator rend() const
			{
				return (reverse_iterator(begin()));
			}

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
				return (_rbt.max_size());
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
				return (insert(value).first);
			}

			template< class InputIt >
			void insert( InputIt first, InputIt last )
			{
				ft::pair<iterator, bool> ret;

				while (first != last)
				{
					ret = _rbt.insert(ft::make_pair(first->first, first->second));
					if (ret.second)
						_size++;
					first++;
				}
			}

			void erase( iterator pos )
			{
				_rbt.destroy(pos.base()->data);
				_size--;
			}

			void erase( iterator first, iterator last )
			{
				while (first != last && first.base())
				{
					erase((first++)->first);
				}
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

				ret = iterator(
						_rbt.find(
						ft::make_pair(key, T())),
						_rbt.getLast()
						);
				return (ret);
			}

			const_iterator find( const Key& key ) const
			{
				const_iterator ret;

				ret = const_iterator(
						_rbt.find(
						ft::make_pair(key, T())),
						_rbt.getLast()
						);
				return (ret);
			}

			ft::pair<iterator,iterator> equal_range( const Key& key )
			{
				return (ft::make_pair(lower_bound(key), upper_bound(key)));
			}
			
			ft::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
			{
				ft::pair<const_iterator, const_iterator> ret(lower_bound(key), upper_bound(key));
				return (ret);
			}

			iterator lower_bound( const Key& key )
			{
				iterator it = begin();
				iterator m_end = end();

				while (it != m_end)
				{
					if (key <= (*it).first)
						return (it);
					it++;
				}
				std::cout << "coucou" << std::endl;
				return (end());
			}

			const_iterator lower_bound( const Key& key ) const
			{
				const_iterator it = begin();
				const_iterator m_end = end();
				const_iterator parent = it;

				while (it != m_end)
				{
					if (key <= (*it).first)
						return (it);
					it++;
				}
				return (end());

			};
			
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

			const_iterator upper_bound( const Key& key ) const
			{
				const_iterator it = begin();
				const_iterator m_end = end();
				const_iterator parent = it;

				while (it != m_end)
				{
					if (_comp(key, it->first))
						return (const_iterator(it));
					parent = it;
					it++;
				}
				return (end());
			}

			key_compare key_comp(void) const
			{
				return (_comp);
			}
			value_compare value_comp(void) const
			{
				return (value_compare(_comp));
			}

			friend bool operator==( const ft::map<Key,T,Compare,Allocator>& lhs, const ft::map<Key,T,Compare,Allocator>& rhs )
			{
				if (rhs.begin() == rhs.end() && lhs.begin() != lhs.end())
					return false;
				if (lhs.size() != rhs.size())
					return false;
				return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));

			}
	
			friend bool operator!=( const ft::map<Key,T,Compare,Allocator>& lhs, const ft::map<Key,T,Compare,Allocator>& rhs )
			{
				return (!(lhs == rhs));
			}

			friend bool operator<  (const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
			{
				
				return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
													rhs.begin(), rhs.end()));
			}

			friend bool operator<= (const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
			{
				return (!(lhs > rhs));
			}

			friend bool operator> (const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
			{
				return (ft::lexicographical_compare(rhs.begin(), rhs.end(),
													lhs.begin(), lhs.end()));
			}

			friend bool operator>= (const ft::map<Key, T, Compare, Allocator>& lhs, const ft::map<Key, T, Compare, Allocator>& rhs)
			{
				return (!(lhs < rhs));
			}
		};

};
#endif