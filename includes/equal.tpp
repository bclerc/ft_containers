#ifndef EQUAL_TPP
# define EQUAL_TPP
 
# include <iostream>

namespace ft 
{

	template <class T>
	struct is_integral
	{
		const bool value = false;
	};
	template <> struct is_integral<bool>					{const bool value = true;};
	template <> struct is_integral<char>					{const bool value = true;};
	template <> struct is_integral<char16_t>				{const bool value = true;};
	template <> struct is_integral<char32_t> 				{const bool value = true;};
	template <> struct is_integral<wchar_t>					{const bool value = true;};
	template <> struct is_integral<signed char>				{const bool value = true;};
	template <> struct is_integral<short int>				{const bool value = true;};
	template <> struct is_integral<int>						{const bool value = true;};
	template <> struct is_integral<long int>				{const bool value = true;};
	template <> struct is_integral<long long int>			{const bool value = true;};
	template <> struct is_integral<unsigned char>			{const bool value = true;};
	template <> struct is_integral<unsigned short int>		{const bool value = true;};
	template <> struct is_integral<unsigned int>			{const bool value = true;};
	template <> struct is_integral<unsigned long int>		{const bool value = true;};
	template <> struct is_integral<unsigned long long int>	{const bool value = true;};



	template <class InputIterator1, class InputIterator2>
	bool	equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			first1++;
			first2++;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool	equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!(pred(*first1, *first2)))
				return false;
			first1++;
			first2++;
		}
		return true;
	}

	template<class InputIterator1, class InputIterator2>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}


	template<class InputIterator1, class InputIterator2, class Compare>
	bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2,
									Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (comp(*first1, *first2))
				return true;
			first1++;
			first2++;
		}
		return (first2 != last2);
	}

};

#endif