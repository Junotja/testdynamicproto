#include <iostream>

class A
{
public:
	std::string toString()const
	{
		return std::string("to string!");
	}
};

class B
{

};

template <typename T>
struct HasToStringFucntion
{
	template<typename U,std::string (U::*)() const>
	struct Match;

	template<typename U>
	static char help(Match<U,&U::toString> *);

	template<typename U>
	static char help();

	enum
	{
		value = sizeof(help<T>()) == 1
	};
};

template <bool>
struct ToStringWrapper{};

template <>
struct ToStringWrapper<true>
{
	template <typename T>
	static std::string toString(T& x)
	{
		return x.toString();
	}
};

template <>
struct ToStringWrapper<false>
{
	template <typename T>
	static std::string toString(T& x)
	{
		return std::string(typeid(x).name());
	}
};


template <typename T>
std::string toString(const T&x)
{
	return ToStringWrapper<HasToStringFucntion<T>::value>::toString(x);
}

int main()
{
	A a;
	B b;
	toString<A>(a);
	toString<B>(b);
	system("pause");
	return 0;
}