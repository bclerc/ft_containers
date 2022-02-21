#include "pair.tpp"
#include "equal.tpp"
#include <vector>

int main(void)
{
	ft::pair<int, int> yo{10, 20};
	std::cout << yo.first << " " << yo.second;

	std::vector<int> tab;
	std::vector<int> tab2;

	tab.push_back(5);
	tab.push_back(4);
	tab.push_back(3);
	tab.push_back(2);

	
	tab2.push_back(5);
	tab2.push_back(8);
	tab2.push_back(3);
	tab2.push_back(2);


	if (std::equal(tab.begin(), tab.end(), tab2.begin()))
		std::cout << "Equal" << std::endl;

	return 0;
}