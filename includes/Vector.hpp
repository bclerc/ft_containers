/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclerc <bclerc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:56:08 by bclerc            #+#    #+#             */
/*   Updated: 2022/03/01 15:04:31 by bclerc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TPP
# define VECTOR_TPP
 
# include <iostream>
# include <memory>
# include <algorithm>
# include <cstddef>
# include <tgmath.h>
# include <exception>
# include "iterator/random_access_iterator.hpp"
# include "iterator/reverse_iterator.hpp"
# include "equal.hpp"

namespace ft {

	template<class T, class Allocator = std::allocator<T> >
	class vector {

		public:
			typedef T										value_type;
			typedef Allocator								allocator_type;
			typedef std::size_t								size_type;
			typedef std::ptrdiff_t							difference_type;
			typedef value_type	&							reference;
			typedef const value_type & 						const_reference;
			typedef typename Allocator::pointer				pointer;
			typedef typename Allocator::const_pointer		const_pointer;
			typedef random_access_iterator<T>				iterator;
			typedef const random_access_iterator<T>			const_iterator;
			typedef	reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private: 
			T*				_data;
			size_type		_size;
			iterator		_start;
			iterator		_end;
			size_type		_capacity;
			allocator_type	_alloc;

		public :
	
			vector (void) : _size(0), _capacity(0) {
				_alloc = Allocator();
				_data = NULL;
				return ;
			}
			
			explicit vector (const Allocator & alloc)
			{
				_alloc = Allocator();
				_data = _alloc.allocate(5);
				return ;
			}
			explicit vector (size_type count, const T& value = T(), const Allocator & alloc = Allocator()) : _size(count), _alloc(alloc)
			{
				_data = _alloc.allocate(count);
				_capacity = count;
				std::uninitialized_fill_n(_data, count, value);

				return ;
			}
			vector (vector const & cpy)
			{
				this->_alloc = cpy->_alloc;
				this->size = cpy.size();
				this->capacity = cpy.capacity();
				this->assign(cpy.begin(), cpy.end());
			}	
		
			template< class InputIt >
			vector( InputIt first, InputIt last, const Allocator& alloc = Allocator());
			~vector(void)
			{
				for(int i = 0; i < _capacity; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(this->_data, _capacity);
			};
			
			vector& operator=( const vector& other )
			{
				this->assign(other.begin(), other.end());
				return (*this);
			}

			void assign( size_type count, const value_type& value )
			{
				resize(count);
				for (int it = 0; it < count; it++)
					_alloc.construct(_data + it, value);
			}

			template< class InputIt >
			void assign( InputIt first,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last)
			{
				InputIt tmp = first;
				int		count = 0;

				for (InputIt it = first; it != last; it++)
					count++;
				resize(count);
				for (int it = 0; it < count; it++)
				{
					_alloc.construct(_data + it, *first);
					first++;
				}
			}	
		
			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}
			
			reference at( size_type pos )
			{
				if (pos >= size())
					throw std::out_of_range("vector<T>::at (pos > this->size())");
				return (*(_data + pos));
			}
			const_reference at( size_type pos ) const
			{
				if (pos >= size())
					throw std::out_of_range("vector<T>::at (pos > this->size())");
				return (const_cast<const_reference>(*(_data + pos)));
			}

			reference operator[]( size_type pos )
			{
				return (*(_data + pos));
			}

			const_reference operator[]( size_type pos ) const
			{
				return (const_cast<const_reference>(*(_data = pos)));
			}

			reference front()
			{
				return (*_data);
			}

			const_reference front() const
			{
				return (const_cast<const_reference>(*_data));
			}

			reference back()
			{
				return (_data + (_size - 1));
			}
			const_reference back() const
			{
				return (const_cast<const_reference>(_data + (_size - 1)));
			};

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
			}
			const_iterator begin() const
			{
				return (const_iterator(this->_data));
			}

			iterator end()
			{
				return (iterator(this->_data + _size));
			}

			const_iterator end() const
			{
				return const_iterator(_data + _size);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(_data);
			}
			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(_data);
			}
		
			reverse_iterator rend()
			{
				return reverse_iterator(_data + _size);
			}
			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(_data + _size);
			}

			bool empty(void) const
			{
				return (this->_size == 0);
			}

			size_type size(void) const
			{
				return this->_size;
			}

			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			void reserve(size_type new_cap)
			{
				T* new_data;
				if (new_cap > max_size())
					throw std::length_error("vector<T>::reserve::new_cap > max_size()");
				if (new_cap < capacity())
					return ;
				new_data = _alloc.allocate(new_cap);
				for(int i = 0; i < _size; i++)
				{
					_alloc.construct(new_data + i, *(_data + i));
					_alloc.destroy(_data + i);
				}
				_alloc.deallocate(this->_data, this->_capacity);
				this->_data = new_data;
				this->_capacity = new_cap;
			}

			size_type capacity() const
			{
				return (this->_capacity);	
			}

			void clear()
			{
				for (int i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_size = 0;
			}

			iterator insert(iterator pos, const T& value );
			void insert( iterator pos, size_type count, const T& value );
			template< class InputIt >
			void insert( iterator pos, InputIt first, InputIt last );

			iterator erase( iterator pos )
			{
				iterator	it = this->begin();
				int			i = 0;
				int			e = 0;
				T 			*new_data;
				
				new_data = _alloc.allocate(_size - 1);
				while (i < (_size ))
				{
					if (pos != it)
					{	
						_alloc.construct(new_data + e, *(_data + i));
						e++;
					}
					i++;
					it++;
				}
				this->clear();
				_alloc.deallocate(_data, _size);
				_data = new_data;
				_size = i - 1;
				return (iterator(_data));
			}

			iterator erase( iterator first, iterator last )
			{
				
			}

			void push_back( const T& value )
			{
				if (_size  == _capacity)
					reserve(_capacity < 5 ? _capacity + 1 : _capacity * 2);
				_alloc.construct(_data + _size , value); 
				_size++;
			}

			void resize( size_type count, T value = T())
			{
				int tmp;

				if (_size > count)
				{
					tmp = _size;
					while (tmp >= 0)
					{	
						_alloc.destroy(_data + tmp);
						tmp--;
					}				
					_size = count;
				}
				else 
				{
					try {
						if (count > _capacity)
							reserve(std::max(_capacity * 2, count));
						for (int i = _size; i < count; i++)
								_alloc.construct(_data + i , value);
						_size = count;
					}
					catch (std::exception & e ) {
						std::cerr << e.what() << std::endl;
					}
				}
			}
	};
};

#endif