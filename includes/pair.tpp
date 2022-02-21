#ifndef PAIR_HPP
# define PAIR_HPP
 
# include <iostream>
 
namespace ft {
	
	template<class T1, class T2>
	struct pair {

		public:
			T1 first;
			T2 seconds;

			explicit pair(void)
			{
				this->first = NULL;
				this->second = NULL;
				return  ;
			}

			explicit pair(T1 const & first, T2 const & second)
			{
				this->first = first;
				this->second = second;
				return ;
			}

			~pair(void);

	};

};

#endif