/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vscode <vscode@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:56:08 by bclerc            #+#    #+#             */
/*   Updated: 2022/03/07 01:34:05 by vscode           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_TPP
# define VECTOR_TPP
 
# include <iostream>
# include <memory>
# include <cstring>
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
			typedef ft::random_access_iterator<T>				iterator;
			typedef ft::random_access_iterator<const T>			const_iterator;
			typedef	ft::reverse_iterator<iterator>			reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		private: 
			T*				_data;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;


		public :
			vector (void) 
			{
				this->_alloc = Allocator();
				this->_capacity = 0;
				this->_size = 0;
				this->_data = NULL;
				return ;
			}

			explicit vector (const Allocator & alloc)
			{
				_alloc = alloc;
				_capacity = NULL;
				_data = NULL;
				_size = 0;
				return ;
			}

			explicit vector (size_type count, const T& value = T(), const Allocator & alloc = Allocator()) : _size(count), _alloc(alloc)
			{
				_data = _alloc.allocate(count);
				_capacity = count;
				this->assign(count, value);
				return ;
			}

			vector (vector const & cpy)
			{
				_alloc = cpy._alloc;
				_data = NULL;
				_capacity = 0;
				_size = 0;				
				this->assign(cpy.begin(), cpy.end());
			}	

			template< class InputIt >
			vector(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last, const Allocator& alloc = Allocator())
			{
				_alloc = alloc;
				_capacity = 0;
				_size = 0;
				_data = NULL;
				this->assign(first, last);
			};

			~vector(void)
			{
				this->clear();
				if (_capacity && _data)
					_alloc.deallocate(_data, _capacity);
			};

			vector& operator=( const vector& other )
			{
				_size = 0;
				_capacity = 0;
				this->assign(other.begin(), other.end());
				return (*this);
			}

			void assign( size_type count, const value_type& value )
			{
				resize(count, value);
				for (size_type it = 0; it < count; it++)
					_alloc.construct(_data + it, value);
			}

			template< class InputIt >
			void assign( InputIt first, InputIt last,
			 typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type value = NULL)
			{
				(void) value;
				this->clear();
				this->insert(this->begin(), first, last);
			}	

			allocator_type get_allocator() const
			{
				return (_alloc);
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
				return (*(_data + pos));
			}

			reference operator[]( size_type pos )
			{
				return (*(_data + pos));
			}

			const_reference operator[]( size_type pos ) const
			{
				return (*(_data = pos));
			}

			reference front()
			{
				return (*_data);
			}

			const_reference front() const
			{
				return (*_data);
			}

			reference back()
			{
				return (*(_data + (_size - 1)));
			}

			const_reference back() const
			{
				return (*(_data + (_size - 1)));
			};

			T* data(void)
			{
				return _data;
			}

			const T* data(void) const
			{
				return const_cast<T*>(_data);
			}

			iterator begin()
			{
				return (_data);
			}

			const_iterator begin() const
			{
				return (_data);
			}

			iterator end()
			{
				if (_size == 0)
					return (_data);
				return (_data + _size);
			}

			const_iterator end() const
			{
				if (_size == 0)
					return (_data);
				return (_data + _size);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(this->end());
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(this->end());
			}

			reverse_iterator rend()
			{
				return reverse_iterator(this->begin());
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(this->begin());
			}

			bool empty(void) const
			{
				return (_size == 0);
			}

			size_type size(void) const
			{
				return _size;
			}

			size_type max_size() const
			{
				return (_alloc.max_size());
			}

			void reserve(size_type new_cap)
			{
				T* new_data;
				if (new_cap > max_size())
					throw std::length_error("vector::reserve");
				if (new_cap < capacity())
					return ;
				new_data = _alloc.allocate(new_cap);
				for(size_type i = 0; i < _size; i++)
				{
					_alloc.construct(new_data + i, *(_data + i));
					_alloc.destroy(_data + i);
				}
				_alloc.deallocate(_data, _capacity);
				_data = (new_data);
				_capacity = new_cap;
			}

			size_type capacity() const
			{
				return (_capacity);	
			}

			void clear()
			{
				for (size_type i = 0; i < _size; i--)
					_alloc.destroy(_data + i);
				_size = 0;
			}

			iterator insert(iterator pos, const T& value )
			{
				pointer p_pos = &(*(pos));
				size_type	int_pos = p_pos - _data;
				
				if (_size == _capacity)
					reserve(_capacity * 2);
				for (size_type i = _size; i > int_pos; i--)
				{
					_alloc.construct(_data + i, *((_data + i) - 1));
					_alloc.destroy((_data + i) - 1);
				}
				_alloc.construct(_data + (int_pos), value);
				_size += 1;
				return iterator(_data + int_pos);
			}
			
			void insert( iterator pos, size_type count, const T& value )
			{
				size_type first = (&(*pos) - _data);
				if (_size + count > _capacity)
					reserve(std::max((_size + count), _capacity * 2));
				for (size_type i = 0; i < _size - first ; i++)
				{
					_alloc.construct((_data + _size) - i + (count - 1), *((_data + _size) - i - 1));
					_alloc.destroy((_data + _size) - i - 1);
				}
				for (size_type i = 0; i < count; i++)
					_alloc.construct(_data + first + i, value);
				_size += count;
			}
	
			template< class InputIt >
			void insert( iterator pos,
				typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first,
				 InputIt last)
				 {
					size_type dist = ft::distance<InputIt>(first, last);
					size_type id =  _size - (&(*(pos)) - _data);
					size_type size_first = _size - id;
					if (_size + dist > _capacity)
					reserve(std::max((_size + dist), _capacity * 2));
					for (size_type i = 0; i < id; i++)
						_alloc.construct((_data + _size) + (dist - 1) - i, *((_data + _size) - i - 1));
 					for (size_type i = 0; i < dist; i++)
						_alloc.construct(_data + size_first + i, *(first++));
					_size += dist;
				 }

			iterator erase( iterator pos )
			{
				pointer del = &(*(pos));
				_alloc.destroy(del);
				for (int i = 0; i < ((_data + _size) - del) - 1; i++)		
				{
					_alloc.construct(del + i, *(del + i + 1));
					_alloc.destroy(del + i + 1);
				}
				_size -= 1;
				return (iterator(del)); 
			}

			iterator erase( iterator first, iterator last )
			{
				pointer p_first = &(*(first));
				pointer	p_last = &(*(last));
				
				for (; first != last; first++)
					_alloc.destroy(&(*(first)));
				for (int i = 0; i < ((_data + _size) - p_last); i++)
				{
					_alloc.construct(p_first + i, *(p_last + i));
					_alloc.destroy(p_last + i);
				}
				_size -= p_last - p_first;
				return (iterator(p_first));
			}

			void push_back( const T& value )
			{
				if (_size  == _capacity)
					reserve(!_capacity ? 1 : _capacity * 2);
				_alloc.construct(_data + _size , value); 
				_size++;
			}

			void pop_back(void)
			{
				_alloc.destroy(_data + _size - 1);
				_size -= 1;
			}

			void resize( size_type count, T value = T())
			{
				size_type tmp;

				if (_size > count)
				{
					tmp = _size -  1;
					while (tmp > count)
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
						for (size_type i = _size; i < count; i++)
								_alloc.construct(_data + i , value);
						_size = count;
					}
					catch (std::exception & e ) {
						std::cerr << e.what() << std::endl;
					}
				}
			}

			void swap (vector& x)
			{
				allocator_type alloc_tmp = _alloc;
				T* data_tmp = _data;
				size_type size_tmp = _size;
				size_type capacity_tmp = _capacity;

				_alloc = x._alloc;
				_data = x._data;
				_size = x._size;
				_capacity = x._capacity;

				x._alloc = alloc_tmp;
				x._data = data_tmp;
				x._size = size_tmp;
				x._capacity = capacity_tmp;	
			}
	};

	template <class T>
	void swap (vector<T>& x, vector<T>& y)
	{
		x.swap(y);
	}

	template <class T>
  	bool operator== (const vector<T>& lhs, const vector<T>& rhs)
	{
		if (rhs.begin() == rhs.end() && lhs.begin() != lhs.end())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T>
  	bool operator!= (const vector<T>& lhs, const vector<T>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T>
  	bool operator<  (const vector<T>& lhs, const vector<T>& rhs)
	{
		
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end()));
	}

	template <class T>
 	bool operator<= (const vector<T>& lhs, const vector<T>& rhs)
	{
		return (!(lhs > rhs));
	}
	template <class T>
  	bool operator> (const vector<T>& lhs, const vector<T>& rhs)
  	{
		return (!(lhs < rhs));
  	}

	template <class T>
  	bool operator>= (const vector<T>& lhs, const vector<T>& rhs)
  	{
		  return !(lhs < rhs);
  	}
};

#endif