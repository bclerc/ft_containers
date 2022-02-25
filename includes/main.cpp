#include "pair.tpp"
#include "equal.tpp"
#include "Vector.hpp"
#include <iostream>    
#include <algorithm>
#include <vector>


int main(void)
{
	ft::vector<int> tab(5);

	std::vector<int> lol;
	std::cout << lol.capacity() << std::endl;

	std::vector<int> tab_std(5);
	std::cout << "std::vector::capacity = " << tab_std.capacity() << std::endl;
	std::cout << "ft::vector::capacity = " << tab.capacity() << std::endl;
	tab.push_back(1);
	tab.push_back(2);
	tab.push_back(3);
	tab.push_back(4);
	tab.push_back(150);

	tab_std.push_back(1);
	tab_std.push_back(2);
	tab_std.push_back(3);
	tab_std.push_back(4);
	tab_std.push_back(150);
	
	std::cout << std::endl <<  "ft::vector::at " << tab.at(9) << std::endl;
	std::cout <<				"std::vector::at " << tab_std.at(9) << std::endl << std::endl;

	typedef typename ft::vector<int>::iterator iterator;
	for (iterator it = tab.begin(); it != tab.end(); it++)
	{
		std::cout << "Iterator: " << *it << std::endl;
	}
	std::cout << "==" << std::endl; 
	typedef typename std::vector<int>::iterator iteratorstd;
	for (iteratorstd it = tab_std.begin(); it != tab_std.end(); it++)
	{
		std::cout << "Iterator: " << *it << std::endl;
	}

	std::cout << "std::vector::capacity = " << tab_std.capacity() << std::endl;
	std::cout << "ft::vector::capacity = " << tab.capacity() << std::endl;
	std::cout << "std::vector::size = " << tab_std.size() << std::endl;
	std::cout << "ft::vector::size = " << tab.size() << std::endl;

	return 0;
}