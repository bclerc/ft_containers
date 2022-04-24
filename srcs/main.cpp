#include "../includes/stack.hpp"
#include "../includes/vector.hpp"
#include "../includes/map.hpp"

#include <iostream>    
#include <algorithm>
#include <vector>
#include <stack>
#include <map>

void construct_test()
{
	// constructors used in the same order as described above:
  TESTED_NAMESPACE::vector<int> first;                                // empty vector of ints
  TESTED_NAMESPACE::vector<int> second (4,100);                       // four ints with value 100
  TESTED_NAMESPACE::vector<int> third (second.begin(),second.end());  // iterating through second
  TESTED_NAMESPACE::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  TESTED_NAMESPACE::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (TESTED_NAMESPACE::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

}

void assign_test()
{
  TESTED_NAMESPACE::vector<int> first;
  TESTED_NAMESPACE::vector<int> second;
  TESTED_NAMESPACE::vector<int> third;

  first.assign (7,100);             // 7 ints with a value of 100

  TESTED_NAMESPACE::vector<int>::iterator it;
  it=first.begin()+1;

  second.assign (it,first.end()-1); // the 5 central values of first

  int myints[] = {1776,7,4};
  third.assign (myints,myints+3);   // assigning from array.

  std::cout << "Size of first: " << int (first.size()) << '\n';
  std::cout << "Size of second: " << int (second.size()) << '\n';
  std::cout << "Size of third: " << int (third.size()) << '\n';
  
}

void at_test()
{
 TESTED_NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized ints

  // assign some values:
  for (unsigned i=0; i<myvector.size(); i++)
    myvector.at(i)=i;

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector.at(i);
  std::cout << '\n';

  
}

void back_test()
{
TESTED_NAMESPACE::vector<int> myvector;
  myvector.push_back(10);

  while (myvector.back() != 0)
  {
    myvector.push_back ( myvector.back() -1 );
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size() ; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  
}

void capacity_test()
{
	TESTED_NAMESPACE::vector<int> myvector;

  // set some content in the vector:
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << (int) myvector.size() << '\n';
  std::cout << "capacity: " << (int) myvector.capacity() << '\n';
  std::cout << "max_size: " << (int) myvector.max_size() << '\n';
  
}

void cbegin_test()
{
	 TESTED_NAMESPACE::vector<int> myvector;

  // set some content in the vector:
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << (int) myvector.size() << '\n';
  std::cout << "capacity: " << (int) myvector.capacity() << '\n';
  std::cout << "max_size: " << (int) myvector.max_size() << '\n';
  
}

void clear_test()
{
	 TESTED_NAMESPACE::vector<int> myvector;
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  myvector.clear();
  myvector.push_back (1101);
  myvector.push_back (2202);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

}

void empty_test()
{
	
	 TESTED_NAMESPACE::vector<int> myvector;
  int sum (0);

  for (int i=1;i<=10;i++) myvector.push_back(i);

  while (!myvector.empty())
  {
     sum += myvector.back();
     myvector.pop_back();
  }

  std::cout << "total: " << sum << '\n';

}

void end_test()
{
	  TESTED_NAMESPACE::vector<int> myvector;
  for (int i=1; i<=5; i++) myvector.push_back(i);

  std::cout << "myvector contains:";
  for (TESTED_NAMESPACE::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void erase_test()
{
	TESTED_NAMESPACE::vector<int> myvector;

  // set some values (from 1 to 10)
  for (int i=1; i<=10; i++) myvector.push_back(i);

  // erase the 6th element
  myvector.erase (myvector.begin()+5);

  // erase the first 3 elements:
  myvector.erase (myvector.begin(),myvector.begin()+3);

  std::cout << "myvector contains:";
  for (unsigned i=0; i<myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
}

void front_test()
{
	 TESTED_NAMESPACE::vector<int> myvector;

  myvector.push_back(78);
  myvector.push_back(16);

  // now front equals 78, and back 16

  myvector.front() -= myvector.back();

  std::cout << "myvector.front() is now " << myvector.front() << '\n';

}

void allocator_test()
{
	  TESTED_NAMESPACE::vector<int> myvector;
  int * p;
  unsigned int i;

  // allocate an array with space for 5 elements using vector's allocator:
  p = myvector.get_allocator().allocate(5);

  // construct values in-place on the array:
  for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

  std::cout << "The allocated array contains:";
  for (i=0; i<5; i++) std::cout << ' ' << p[i];
  std::cout << '\n';

  // destroy and deallocate:
  for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
  myvector.get_allocator().deallocate(p,5);
}

void insert_test()
{
	 TESTED_NAMESPACE::vector<int> myvector (3,100);
  TESTED_NAMESPACE::vector<int>::iterator it;

  it = myvector.begin();
  it = myvector.insert ( it , 200 );

  myvector.insert (it,2,300);

  // "it" no longer valid, get a new one:
  it = myvector.begin();

  TESTED_NAMESPACE::vector<int> anothervector (2,400);
  myvector.insert (it+2,anothervector.begin(),anothervector.end());

  int myarray [] = { 501,502,503 };
  myvector.insert (myvector.begin(), myarray, myarray+3);

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';
}

void operator_equal_test()
{
  TESTED_NAMESPACE::vector<int> foo (3,0);
  TESTED_NAMESPACE::vector<int> bar (5,0);

  bar = foo;
  foo = TESTED_NAMESPACE::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';

}

void max_size_test()
{
	 TESTED_NAMESPACE::vector<int> myvector;

  // set some content in the vector:
  for (int i=0; i<100; i++) myvector.push_back(i);

  std::cout << "size: " << myvector.size() << "\n";
  std::cout << "capacity: " << myvector.capacity() << "\n";
  std::cout << "max_size: " << myvector.max_size() << "\n";
  
}

void operator_cage_test()
{
	 TESTED_NAMESPACE::vector<int> myvector (10);   // 10 zero-initialized elements

  TESTED_NAMESPACE::vector<int>::size_type sz = myvector.size();

  // assign some values:
  for (unsigned i=0; i<sz; i++) myvector[i]=i;

  // reverse vector using operator[]:
  for (unsigned i=0; i<sz/2; i++)
  {
    int temp;
    temp = myvector[sz-1-i];
    myvector[sz-1-i]=myvector[i];
    myvector[i]=temp;
  }

  std::cout << "myvector contains:";
  for (unsigned i=0; i<sz; i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  
}
void pop_back_test()
{

 TESTED_NAMESPACE::vector<int> myvector;
  int sum (0);
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  while (!myvector.empty())
  {
    sum+=myvector.back();
    myvector.pop_back();
  }

  std::cout << "The elements of myvector add up to " << sum << '\n';

  
}

void push_back_test()
{
	 TESTED_NAMESPACE::vector<int> myvector;

	for (int i = 0; i < 20; i ++)
		myvector.push_back(i);

  std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

  
}

void rbegin_test()
{
	  TESTED_NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints

  int i=0;

  TESTED_NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();
  for (; rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (TESTED_NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  
}

void rend_test()
{

	 TESTED_NAMESPACE::vector<int> myvector (5);  // 5 default-constructed ints

  TESTED_NAMESPACE::vector<int>::reverse_iterator rit = myvector.rbegin();

  int i=0;
  for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
    *rit = ++i;

  std::cout << "myvector contains:";
  for (TESTED_NAMESPACE::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  
}

void reserve_test()
{
	  TESTED_NAMESPACE::vector<int>::size_type sz;

  TESTED_NAMESPACE::vector<int> foo;
  sz = foo.capacity();
  std::cout << "making foo grow:\n";
  for (int i=0; i<100; ++i) {
    foo.push_back(i);
    if (sz!=foo.capacity()) {
      sz = foo.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }

  TESTED_NAMESPACE::vector<int> bar;
  sz = bar.capacity();
  bar.reserve(100);   // this is the only difference with foo above
  std::cout << "making bar grow:\n";
  for (int i=0; i<100; ++i) {
    bar.push_back(i);
    if (sz!=bar.capacity()) {
      sz = bar.capacity();
      std::cout << "capacity changed: " << sz << '\n';
    }
  }
  
}

void resize_test()
{
	  TESTED_NAMESPACE::vector<int> myvector;

  // set some initial content:
  for (int i=1;i<10;i++) myvector.push_back(i);

  myvector.resize(5);
  myvector.resize(8,100);
  myvector.resize(12);

  std::cout << "myvector contains:";
  for (size_t i=0;i<myvector.size();i++)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';

  
}

void size_test()
{

	  TESTED_NAMESPACE::vector<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<10; i++) myints.push_back(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.insert (myints.end(),10,100);
  std::cout << "2. size: " << myints.size() << '\n';

  myints.pop_back();
  std::cout << "3. size: " << myints.size() << '\n';

  
}

void swap_test()
{

	 TESTED_NAMESPACE::vector<int> foo (3,100);   // three ints with a value of 100
  TESTED_NAMESPACE::vector<int> bar (5,200);   // five ints with a value of 200

  foo.swap(bar);

  std::cout << "foo contains:";
  for (unsigned i=0; i<foo.size(); i++)
    std::cout << ' ' << foo[i];
  std::cout << '\n';

  std::cout << "bar contains:";
  for (unsigned i=0; i<bar.size(); i++)
    std::cout << ' ' << bar[i];
  std::cout << '\n';
}

void stack_empty()
{
	 TESTED_NAMESPACE::stack<int> mystack;
  int sum (0);

  for (int i=1;i<=10;i++) mystack.push(i);

  while (!mystack.empty())
  {
     sum += mystack.top();
     mystack.pop();
  }

  std::cout << "total: " << sum << '\n';

}

void stack_pop()
{
	  TESTED_NAMESPACE::stack<int> mystack;

  for (int i=0; i<5; ++i) mystack.push(i);

  std::cout << "Popping out elements...";
  while (!mystack.empty())
  {
     std::cout << ' ' << mystack.top();
     mystack.pop();
  }
  std::cout << '\n';

}

void stack_push()
{
	 TESTED_NAMESPACE::stack<int> mystack;

  for (int i=0; i<5; ++i) mystack.push(i);

  std::cout << "Popping out elements...";
  while (!mystack.empty())
  {
     std::cout << ' ' << mystack.top();
     mystack.pop();
  }
  std::cout << '\n';

}

void stack_size()
{
 TESTED_NAMESPACE::stack<int> myints;
  std::cout << "0. size: " << myints.size() << '\n';

  for (int i=0; i<5; i++) myints.push(i);
  std::cout << "1. size: " << myints.size() << '\n';

  myints.pop();
  std::cout << "2. size: " << myints.size() << '\n';

}

void stack_top()
{
TESTED_NAMESPACE::stack<int> mystack;

  mystack.push(10);
  mystack.push(20);

  mystack.top() -= 5;

  std::cout << "mystack.top() is now " << mystack.top() << '\n';

}

void map_begin()
{
	TESTED_NAMESPACE::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (TESTED_NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

}

void map_clear()
{
	  TESTED_NAMESPACE::map<char,int> mymap;

  mymap['x']=100;
  mymap['y']=200;
  mymap['z']=300;

  std::cout << "mymap contains:\n";
  for (TESTED_NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  mymap.clear();
  mymap['a']=1101;
  mymap['b']=2202;

  std::cout << "mymap contains:\n";
  for (TESTED_NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

}

void map_count()
{
	  TESTED_NAMESPACE::map<char,int> mymap;
  char c;

  mymap ['a']=101;
  mymap ['c']=202;
  mymap ['f']=303;

  for (c='a'; c<'h'; c++)
  {
    std::cout << c;
    if (mymap.count(c)>0)
      std::cout << " is an element of mymap.\n";
    else 
      std::cout << " is not an element of mymap.\n";
  }
}

void map_empty()
{
	TESTED_NAMESPACE::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  while (!mymap.empty())
  {
    std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
    mymap.erase(mymap.begin());
  }
}

void map_end()
{
	  TESTED_NAMESPACE::map<char,int> mymap;

  mymap['b'] = 100;
  mymap['a'] = 200;
  mymap['c'] = 300;

  // show content:
  for (TESTED_NAMESPACE::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

}

void map_equal_range()
{
	 TESTED_NAMESPACE::map<char,int> mymap;

  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;

  TESTED_NAMESPACE::pair<TESTED_NAMESPACE::map<char,int>::iterator,TESTED_NAMESPACE::map<char,int>::iterator> ret;
  ret = mymap.equal_range('b');

  std::cout << "lower bound points to: ";
  std::cout << ret.first->first << " => " << ret.first->second << '\n';

  std::cout << "upper bound points to: ";
  std::cout << ret.second->first << " => " << ret.second->second << '\n';

}

void map_erase()
{
	  TESTED_NAMESPACE::map<char,int> mymap;
  TESTED_NAMESPACE::map<char,int>::iterator it;

  // insert some values:
  mymap['a']=10;
  mymap['b']=20;
  mymap['c']=30;
  mymap['d']=40;
  mymap['e']=50;
  mymap['f']=60;

  it=mymap.find('b');
  mymap.erase (it);                   // erasing by iterator

  mymap.erase ('c');                  // erasing by key

  it=mymap.find ('e');
  mymap.erase ( it, mymap.end() );    // erasing by range

  // show content:
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

}

void map_find()
{
	 TESTED_NAMESPACE::map<char,int> mymap;
  TESTED_NAMESPACE::map<char,int>::iterator it;

  mymap['a']=50;
  mymap['b']=100;
  mymap['c']=150;
  mymap['d']=200;

  it = mymap.find('b');
  if (it != mymap.end())
    mymap.erase (it);

  // print content:
  std::cout << "elements in mymap:" << '\n';
  std::cout << "a => " << mymap.find('a')->second << '\n';
  std::cout << "c => " << mymap.find('c')->second << '\n';
  std::cout << "d => " << mymap.find('d')->second << '\n';

}

void map_allocator()
{
	 int psize;
  TESTED_NAMESPACE::map<char,int> mymap;
  TESTED_NAMESPACE::pair<const char,int>* p;

  // allocate an array of 5 elements using mymap's allocator:
  p=mymap.get_allocator().allocate(5);

  // assign some values to array
  psize = sizeof(TESTED_NAMESPACE::map<char,int>::value_type)*5;

  std::cout << "The allocated array has a size of " << psize << " bytes.\n";

  mymap.get_allocator().deallocate(p,5);

}

void map_insert()
{
	 TESTED_NAMESPACE::map<char,int> mymap;

  // first insert function version (single parameter):
  mymap.insert ( TESTED_NAMESPACE::pair<char,int>('a',100) );
  mymap.insert ( TESTED_NAMESPACE::pair<char,int>('z',200) );

  TESTED_NAMESPACE::pair<TESTED_NAMESPACE::map<char,int>::iterator,bool> ret;
  ret = mymap.insert ( TESTED_NAMESPACE::pair<char,int>('z',500) );
  if (ret.second==false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  // second insert function version (with hint position):
  TESTED_NAMESPACE::map<char,int>::iterator it = mymap.begin();
  mymap.insert (it, TESTED_NAMESPACE::pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert (it, TESTED_NAMESPACE::pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  TESTED_NAMESPACE::map<char,int> anothermap;
  anothermap.insert(mymap.begin(),mymap.find('c'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}

void map_max_size()
{  int i;
  TESTED_NAMESPACE::map<int,int> mymap;

  if (mymap.max_size()>1000)
  {
    for (i=0; i<1000; i++) mymap[i]=0;
    std::cout << "The map contains 1000 elements.\n";
  }
  else std::cout << "The map could not hold 1000 elements.\n";
}

void map_rbegin()
{
	 TESTED_NAMESPACE::map<char,int> mymap;

  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;

  // show content:
  TESTED_NAMESPACE::map<char,int>::reverse_iterator rit;
  for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
    std::cout << rit->first << " => " << rit->second << '\n';

}

void map_rend()
{
	 TESTED_NAMESPACE::map<char,int> mymap;

  mymap['x'] = 100;
  mymap['y'] = 200;
  mymap['z'] = 300;

  // show content:
  TESTED_NAMESPACE::map<char,int>::reverse_iterator rit;
  for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
    std::cout << rit->first << " => " << rit->second << '\n';

}

void map_size()
{
	 TESTED_NAMESPACE::map<char,int> mymap;
  mymap['a']=101;
  mymap['b']=202;
  mymap['c']=302;

  std::cout << "mymap.size() is " << mymap.size() << '\n';

}

void map_swap()
{
	 TESTED_NAMESPACE::map<char,int> foo,bar;

  foo['x']=100;
  foo['y']=200;

  bar['a']=11;
  bar['b']=22;
  bar['c']=33;

  foo.swap(bar);

  std::cout << "foo contains:\n";
  for (TESTED_NAMESPACE::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "bar contains:\n";
  for (TESTED_NAMESPACE::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

}

int main(void)
{
	std::cout << "TEST VECTOR " << std::endl;

	construct_test();
	assign_test();
	at_test();
	back_test();
	cbegin_test();
	clear_test();
	empty_test();
	end_test();
	erase_test();
	allocator_test();
	insert_test();
	max_size_test();
	operator_equal_test();
	operator_cage_test();
	pop_back_test();
	push_back_test();
	rbegin_test();
	rend_test();
	reserve_test();
	swap_test();
	std::cout << "TEST STACK " << std::endl;
	stack_empty();
	stack_pop();
	stack_push();
	stack_size();
	stack_top();
	std::cout << "TEST MAP" << std::endl;
	map_begin();
	map_clear();
	map_count();
	map_empty();
	map_equal_range();
	map_end();
	map_find();
	map_erase();
	map_allocator();
	map_insert();
	map_max_size();
	map_rbegin();
	map_rend();
	map_size();
	map_swap();

	return (0);
}

