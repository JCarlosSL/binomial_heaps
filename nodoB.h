#ifndef NodoB_H
#define NodoB_H
#include <list>
#include <algorithm>
#include <iterator>
template<class T>
class nodob{
public:
	T date;
	int grade;
	nodob<T> *father;
	std::list<nodob<T>*> m_son;
public:
	nodob(){
		father=nullptr;
	}
	nodob(T _date){
		date=_date;
		father=nullptr;
		grade=0;
	}
};


#endif
