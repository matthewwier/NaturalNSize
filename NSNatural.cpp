
#include <iostream>
#include <iomanip>
#include <limits.h>
#include <numeric>
using namespace std;

template<bool flag, int n1, int n2> struct If_then_else
{
	static const int result = n1;
};
template<int n1, int n2> struct If_then_else<false, n1, n2>
{
	static const int result = n2;
};
template<class T, T n1, T n2> struct Select
{
	static const int greater = If_then_else<(n1>n2), n1, n2>::result;
	static const int smaller = If_then_else<(n1<n2), n1, n2>::result;
	static const bool equal = (n1 == n2);
};

template <int size, class basic_type=unsigned int> class NSizeNatural
{
	basic_type elementy[size];

public:
	NSizeNatural()
	{
		for (int i = 0; i < size; i++) elementy[i] = 0;
	}

	NSizeNatural(basic_type s)
	{
		elementy[0] = s;
		for (int i = 1; i < size; i++) elementy[i] = 0;
	}

	NSizeNatural(basic_type s[], int length)
	{
		for (int i = 0; i < length; i++)
		{
			elementy[i] = s[i];
		}
	}
	const basic_type& operator[](int i ) const
	{
		return elementy[i];
	}

	basic_type& operator[](int i)
	{
		return elementy[i];
	}
};
template<int length, class basic_type> ostream & operator<<(ostream &out, const NSizeNatural <length, basic_type> &n)
{
	unsigned long long x;
	short one_basic_width = std::numeric_limits<basic_type>::digits/4;
	for (int i = length-1; i >= 0; i--)
	{
		out << std::setfill('0') << std::setw(one_basic_width) << (unsigned long long)n[i];
	}

	return out;
}
template<int firstLength, int secondLength, class basic_type>
NSizeNatural<Select<int, firstLength, secondLength>::greater,basic_type> operator+(const NSizeNatural<firstLength, basic_type> & first,
																					const NSizeNatural<secondLength, basic_type> &second)
{
	NSizeNatural<Select<int, firstLength, secondLength>::greater, basic_type> result;
	int carry = 0;
	for (int i = 0; i < Select<int, firstLength, secondLength>::smaller; i++)
	{
		basic_type wynik = first[i] + second[i];
		if (carry == 1)
			wynik = first[i] + second[i] + carry;
		else
			wynik = first[i] + second[i];

		if ((wynik < first[i] || wynik < second[i]))
			carry = 1;
		else
			carry = 0;
		result[i] = wynik;
	}
	

	int i = Select<int, firstLength, secondLength>::smaller;
	while (i < Select<int, firstLength, secondLength>::greater)
	{
		result[i] = firstLength > secondLength ? first[i] : second[i];
		i++;
	}
	
	return result;
}
template<int lengthFirst, int lengthSecond, class basic_type> bool operator==(const NSizeNatural<lengthFirst, basic_type> &n1,
																						const NSizeNatural<lengthSecond, basic_type> &n2)
{
	return Select<int, lengthFirst, lengthSecond>::equal;
}
template<int lengthFirst, int lengthSecond, class basic_type> bool operator>(const NSizeNatural<lengthFirst, basic_type> &n1,
																						const NSizeNatural<lengthSecond, basic_type> &n2)
{
	return (Select<int, lengthFirst, lengthSecond>::greater == lengthFirst) ? true : false;
}
template<int lengthFirst, int lengthSecond, class basic_type> bool operator<(const NSizeNatural<lengthFirst, basic_type> &n1,
																						const NSizeNatural<lengthSecond, basic_type> &n2)
{
	return (Select<int, lengthFirst, lengthSecond>::smaller == lengthFirst) ? true : false;
}

template<class Typ> void writeFibbonacci(int n)
{
	Typ i_1 ;
	Typ i_2 ;
	Typ wynik ;
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			i_1 = 1;
			wynik = i_1;
		}
		if (i == 1)
		{
			i_2 = 1;
			wynik = i_2;
		}
		if (i>1)
		{
			wynik = i_1 + i_2;
			Typ tmp = i_1;
			i_1 = wynik;
			i_2 = tmp;
		}
		if (i >= 1)
			cout << i << ":" << wynik << endl;
	}

}

template <int length, class basic_type>
	class numeric_limits<NSizeNatural<length, basic_type>>
	{
	public:
		static NSizeNatural<length, basic_type> max()
		{
			NSizeNatural<length, basic_type> result;
			for (int i = 0; i < length; i++)
			{
				result[i] = numeric_limits<basic_type>::max();
			}
			return result;
		}
		static NSizeNatural<length, basic_type> min()
		{
			NSizeNatural<length, basic_type> result;
			for (int i = 0; i < length; i++)
			{
				result[i] = numeric_limits<basic_type>::min();
			}
			return result;
		}

		static const bool is_integer = numeric_limits<basic_type>::is_integer;
		static const bool is_signed = numeric_limits<basic_type>::is_signed;
		static const bool is_specialized = numeric_limits<basic_type>::is_specialized;

	};

	
int main()
{
	NSizeNatural<3> a(101);
	NSizeNatural<3> b(201);

	cout << std::hex;
	cout << a + b << endl;

	unsigned char   cs[3] = { 125, 250, 126 };
	NSizeNatural<1, unsigned char> ac(101);
	NSizeNatural<2, unsigned char> bc(cs, 2);
	NSizeNatural<3, unsigned char> cc(cs, 3);
	cout << cc << endl;
	cout << ac + bc << endl;
	cout << ac + cc + bc << endl;

	cout << (bc < cc) << endl;
	cout << (ac > cc) << endl;
	cout << (cc == cc) << endl;

	writeFibbonacci<NSizeNatural <4, unsigned char> >(46);
	writeFibbonacci<NSizeNatural <3, unsigned long long> >(200);
	cout << numeric_limits<NSizeNatural<3, unsigned char> >::max() << endl;
	cout << numeric_limits<NSizeNatural<3> >::is_specialized << endl;
	cout << numeric_limits<NSizeNatural<3, char> >::is_signed << endl;
	cout << numeric_limits<NSizeNatural<3> >::is_integer << endl;



}
