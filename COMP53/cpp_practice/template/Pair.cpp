#include "Pair.h"


template<class T> 
Pair<T>::Pair()
{
}

template<class T>
Pair<T>::~Pair()
{
}

template<class T>
Pair<T>::Pair(T f, T s) {
	first = f;
	second = s;
}

template<class T>
T Pair<T>::getFirst() {
	return first;
}

template<class T>
T Pair<T>::getSecond() {
	return second;
}
