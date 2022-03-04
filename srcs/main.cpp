#include "pair.tpp"
#include "vector.hpp"
#include <iostream>    
#include <algorithm>
#include <vector>

# define NAMESPACE ft

using namespace NAMESPACE;

template <class T>
void	print(vector<vector<T> >& lst)
{
	for (typename vector<vector<T> >::iterator it = lst.begin(); it != lst.end(); it++)
	{
		for (typename vector<T>::iterator it2 = it->begin(); it2 != it->end(); it2++)
			std::cout << *it2 << ' ';
		std::cout << '\n';
	}
}

template <class T>
void	print(vector<T>& lst)
{
	for (typename vector<T>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << *it << ' ';
	std::cout << '\n';
}


int main ()
{
  vector<int> myvector (3,100);
  vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

 std::cout << "it after insert " << *it << std::endl;
  myvector.insert (it,2,300);

  vector<int> anothervector (2,400);
  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  it = myvector.begin();
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  // "it" no longer valid, get a new one:
std::cout << std::endl;
std::cout << "myvector contains: 501 502 503 300 300 400 400 200 100 100 100" << std::endl;
  return 0;
}

