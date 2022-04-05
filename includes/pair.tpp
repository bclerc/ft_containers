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

			explicit pair(void)
			{
				return  ;
			}

			explicit pair(T1 const & first, T2 const & second)
			{
				this->first = first;
				this->second = second;
				return ;
			}

			pair & operator=(const pair & rhs) {
				this->first = rhs.first;
				this->second = rhs.second;
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

	template< class T1, class T2 >
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
	bool operator<=( const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs )
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