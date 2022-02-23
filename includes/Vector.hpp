/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:56:08 by bclerc            #+#    #+#             */
/*   Updated: 2022/02/23 21:26:27 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TPP
# define VECTOR_TPP
 
# include <iostream>
# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>
# include "iterator/random_access_iterator.hpp"


namespace ft {

	template<class T, class Allocator = std::allocator<T>>
	class vector {

		public:
			typedef T									value_type;
			typedef Allocator							allocator_type;
			typedef std::size_t							size_type;
			typedef std::ptrdiff_t						difference_type;
			typedef value_type	&						reference;
			typedef const value_type & 					const_reference;
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef random_access_iterator<T>			iterator;
			typedef const random_access_iterator<T>		const_iterator;
		
		private: 
			T*				_data;
			size_type		_size;
			iterator		_start;
			iterator		_end;
			size_type		_capacity;
			allocator_type	_alloc;

		public :
	
			vector (void) : _size(0), _max_size(0) {
				_alloc = Allocator;
				_data = _alloc.allocate(0);
				return ;
			}
			explicit vector (const Allocator & alloc)
			{
				

			}
			explicit vector (size_type count, const T& value = T(), const Allocator & alloc = Allocator()) : _size(count), _alloc(alloc)
			{
				_data = _alloc.allocate(count);
				_data = _alloc.construct ()
				std::uninitialized_fill_n(_data, count, value);
				return ;
			}
			vector (vector const & cpy);
			
			template< class InputIt >
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator());
			~vector(void)
			{
				_alloc.deallocate(this->_data, );
			};
			
			vector& operator=( const vector& other );

			void assign( size_type count, const T& value );
		
			template< class InputIt >
			void assign( InputIt first, InputIt last );
		
			allocator_type get_allocator() const;
			reference at( size_type pos );
			const_reference at( size_type pos ) const;

			reference operator[]( size_type pos );
			const_reference operator[]( size_type pos ) const;

			reference front();
			const_reference front() const;

			reference back();
			const_reference back() const;

			T* data(void)
			{
				return this->_data;
			}

			const T* data(void) const
			{
				return const_cast<T*>(this->_data);
			}

			iterator begin()
			{
				return (iterator(this->_data));
			};
			const_iterator begin() const;

			iterator end()
			{
				return (iterator(this->_data + _size));
			};

			const_iterator end();

			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
		
			reverse_iterator rend();
			const_reverse_iterator rend() const;

			bool empty(void) const
			{
				return (this->_size == 0)
			}

			size_type size(void) const
			{
				return this->_size;
			}

			size_type max_size() const
			{
				_alloc.max_size();
			}

			void reserve( size_type new_cap );
			size_type capacity() const;

			void clear();

			iterator insert( iterator pos, const T& value );
			void insert( iterator pos, size_type count, const T& value );
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last );
			iterator erase( iterator pos );
			iterator erase( iterator first, iterator last );

			void push_back( const T& value );
			void resize( size_type count, T value = T() );
			void pop_back();
			void swap( vector& other );
	};
};

#endif