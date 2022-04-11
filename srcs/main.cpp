#include "pair.tpp"
#include "stack.hpp"
#include "vector.hpp"
#include "../includes/map.hpp"

#include "../includes/tree.hpp"
#include "iterator/bidirectional_iterator.hpp"

#include <iostream>    
#include <algorithm>
#include <vector>
#include <map>


#define TESTED_TYPE int
#define TESTED_NAMESPACE ft

int main()
{

	std::map<int, int> test;
	ft::map<int, int>	youpi;


	
	std::cout << youpi.insert(ft::make_pair(5, 5)).second << " : Result" << std::endl;
	youpi.insert(ft::make_pair(5, 5));
	youpi.insert(ft::make_pair(5, 5));

	youpi.insert(ft::make_pair(12, 12));
	youpi.insert(ft::make_pair(89, 89));
	youpi.insert(ft::make_pair(8, 89));
	youpi.insert(ft::make_pair(7, 89));

	youpi.insert(ft::make_pair(65, 89));

	std::cout << "Count of : " << ((youpi.equal_range(7)).first)->first << std::endl;
	typedef ft::map<int, int>::iterator anotheriterator;
	typedef ft::map<int, int>::reverse_iterator reverse_terator;

	reverse_terator it = youpi.rend();


	//std::cout << it->first << std::endl;

	anotheriterator q1 = youpi.begin();
	anotheriterator q2 = youpi.begin();

	++q2;
	++q2;
	std::cout << "size: " << youpi.size() << " q1 " << q1->first << " q2 " << q2->first << std::endl; 

//	youpi.erase(q1, q2);
	youpi.insert(ft::make_pair(54, 12));
	std::cout << "Size << " << youpi.size() << std::endl;
//	youpi.clear();
//	youpi.clear();
	youpi.insert(ft::make_pair(1, 1));
	anotheriterator y = youpi.begin();

	for (anotheriterator i = youpi.begin(); i != youpi.end(); i++)
		std::cout << i->first << std::endl;

	std::cout << "====== " <<  youpi.end()->first  << " " << youpi.size() <<"=========" << std::endl;
	try
	{
		youpi[9] = 5;
		std::cout << "Find test : " <<  youpi[9] << std::endl;
		/* code */
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	


	std::cout << "===============" << std::endl;

	test.insert(std::make_pair(5, 12));

	test.insert(std::make_pair(5, 12));
	test.insert(std::make_pair(15, 12));
	test.insert(std::make_pair(98, 12));
	test.insert(std::make_pair(85, 12));
	test.insert(std::make_pair(12, 12));

	
	//its endtest = test.end();



}


// }