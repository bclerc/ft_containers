#include "pair.tpp"
#include "stack.hpp"
#include "vector.hpp"
#include "avl.hpp"
#include "iterator/bidirectional_iterator.hpp"

#include <iostream>    
#include <algorithm>
#include <vector>
#include <map>



#define TESTED_TYPE int
#define TESTED_NAMESPACE ft

int main(int argc, char **argv)
{
	std::map<int, int> test;


	test.insert(std::make_pair(5, 12));
	test.insert(std::make_pair(15, 12));
	test.insert(std::make_pair(98, 12));
	test.insert(std::make_pair(85, 12));
	test.insert(std::make_pair(12, 12));

	

	typedef std::map<int, int>::iterator its;
	for (its lol = test.begin(); lol != test.end(); lol++)
		std::cout << "test map :: " << (*lol).first << std::endl;

	ft::RBT<ft::pair<int, int> > rbt;
	
	rbt.insert(ft::make_pair(5,12));
	rbt.insert(ft::make_pair(15, -12));
	rbt.insert(ft::make_pair(98, 3));
	rbt.insert(ft::make_pair(85, 3));
	rbt.insert(ft::make_pair(12, 3));

	rbt.test(rbt.getRoot());

	ft::bidirectional_iterator<ft::RBT<ft::pair<int, int> >::t_node> it(rbt.getRoot(), rbt.getLast());

	std::cout << "Iterator test : " <<  (*(++it)).first << std::endl << std::endl;

	for (int i = 1; i < argc; i++)
	{
		try
		{
			std::cout << "Key: " << argv[i]  << " = " << rbt.find(ft::make_pair(atoi(argv[i]), int())).second << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
	}

}


//int main(void)
//{
// 	ft::AVL<int, std::string> avl;

// 	avl._root = avl.insert(avl._root, ft::pair<int, std::string>(2, std::string("Caca 2")));
// 	avl._root = avl.insert(avl._root, ft::pair<int, std::string>(3, std::string("Trop bien b 3")));
// 	avl._root = avl.insert(avl._root, ft::pair<int, std::string>(1, std::string("ouou 1")));
// 	avl._root = avl.insert(avl._root, ft::pair<int, std::string>(0, std::string("Youhou 0")));
// 	avl._root = avl.insert(avl._root, ft::pair<int, std::string>(4, std::string("Caca lol 4")));

// 	for (int i = 0; i < 5; i++)
// 		std::cout << "Value find : " << avl.find(i) << std::endl;
// 	try
// 	{
// 			std::cout << "Value find : " << avl.find(2) << std::endl;
// 	}
// 	catch(const std::exception& e)
// 	{
// 		std::cerr << e.what() << '\n';
// 	}
	
// 	avl._root = avl.deleteNode(avl._root, 0);
// 	avl._root = avl.deleteNode(avl._root, 5);
// 	avl._root = avl.deleteNode(avl._root, 1);	
// 	avl._root = avl.deleteNode(avl._root, 12);
// 	avl._root = avl.deleteNode(avl._root, 3);
// 	avl._root = avl.deleteNode(avl._root, 4);
// 	avl._root = avl.insert(avl._root, ft::pair<int, std::string>(4, std::string("Caca lol 5")));

// 	std::cout << " ===== Value find : " << avl.find(4) << std::endl;
// 	avl._root = avl.deleteNode(avl._root, 4);

// 	ft::AVL<std::string, std::string> test;
// 	test._root = test.insert(test._root, ft::pair<std::string, std::string>("testouille", std::string("ouou 1")));
// 	test._root = test.insert(test._root, ft::pair<std::string, std::string>("chalu", std::string("ouou 2")));
// 	std::cout << " ===== Value find : " << test.find("testouille") << std::endl;
// 	std::cout << " ===== Value find : " << test.find("chalu") << std::endl;


// }