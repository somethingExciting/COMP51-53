#pragma once
template<class T>
class Pair
{
public:
	Pair();
	~Pair();
	Pair(T f, T s);
	T getFirst();
	T getSecond();
private:
	T first;
	T second;
};

