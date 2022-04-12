#ifndef PAIR_HPP
# define PAIR_HPP
 
# include <iostream>
 
namespace ft {
	
	template<class T1, class T2>
	struct pair {

		public:
			typedef T1 first_type;
			typedef T2 second_type;

			T1 first;
			T2 second;

			pair(void) : first(T1()), second(T2())
			{
				
				return  ;
			}
	
			pair(ft::pair<T1, T2> & other) : first(other.first), second(other.second)
			{
				return ;
			}

			pair(T1 const & first, T2 const & second) : first(first), second(second)
			{
				return ;
			}

			template< class U1, class U2 >
			pair( const pair<U1, U2>& p ) : first(p.first), second(p.second)
			{
				return ;
			}

			template<class U, class V>
			pair & operator=(const pair<U, V> & rhs) {
				this->first = static_cast<U>(rhs.first);
				this->second = static_cast<V>(rhs.second);
				return *this;
			}

			~pair(void)	{};
	};

	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 first, T2 second)
	{
		return (ft::pair<T1, T2>(first, second));
	}
};



	template< class T1 , class T2>
	bool operator==( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template< class T1, class T2 >
	bool operator!=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (!(lhs == rhs));
	}

	template< class T1, class T2 >
	bool operator<( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		if (lhs.first < rhs.first)
			return (true);
		else if (rhs.first  < lhs.first)
			return (false);
		else if (lhs.second < rhs.second)
			return (true);
		else
			return (false);
	}

	template< class T1, class T2 >
	bool operator<=( const ft::pair<int,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (!(rhs < lhs));
	}

	template< class T1, class T2 >
	bool operator>( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (rhs < lhs);
	}

	template< class T1, class T2 >
	bool operator>=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
	{
		return (!(lhs < rhs));
	}

#endif