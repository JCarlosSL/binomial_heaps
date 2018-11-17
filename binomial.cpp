#include "binomial.h"

template<class T>
void binomial<T>::insert(T d){
	nodob<T> *p_new=new nodob<T>(d);
	root.push_front(p_new);
	auto it=root.begin();
	auto it1=root.begin();
	++it1;
	while(it1!=root.end()){
		if((*it)->grade==(*it1)->grade){
			if((*it)->date < (*it1)->date){
				auto p=it;
				it=it1;
				it1=p;
			}
			auto p=_union(*it,*it1);
			root.remove(p);
		}
		it=it1;
		++it1;
	}
}

template<class T>
auto binomial<T>::_union(nodob<T>* &it,nodob<T>* &it1){
	if(it1->date <= it->date){
		it1->grade++;
		it->father=it1;
		it1->m_son.push_front(it);
		return it;
	}
	else{
		it->grade++;
		it1->father=it;
		it->m_son.push_front(it1);
		return it1;
	}
}

template <class T>
auto binomial<T>::getmin(){
	auto it=root.begin();
	auto min=root.begin();
	while(it!=root.end()){
		if((*it)->date<(*min)->date){
			min=it;
		}
		++it;
	}	
	return min;
}

template <class T>
auto binomial<T>::deletemin(){
	auto min=getmin();
	auto mson=(*min)->m_son;
	auto itmin=mson.begin();
	root.remove(*min);
	std::list<nodob<T>*> list1;
	while(itmin!=mson.end()){
		(*itmin)->father=nullptr;
		list1.push_front(*itmin);
		++itmin;
	}
	actualizar(list1);

}

template <class T>
void binomial<T>::actualizar(std::list<nodob<T>*> &list1){
	auto it=list1.begin();
	auto r=root;
	auto itr=r.begin();
	root.clear();
	while(it!=list1.end()){
		if((*it)->grade==(*itr)->grade){
			auto p=_union(*it,*itr);
			if(p==(*it)){
				root.push_back(*itr);
			}
			else{
				root.push_back(*it);
			}
			++itr;
		}
		else{
			root.push_back(*it);
		}
		++it;
	}
	while(itr!=r.end()){
		root.push_back(*itr);
		++itr;
	}
}

template<class T>
void binomial<T>::reduccion(nodob<T> **&p){
	auto it=getmin();
	T min=(*it)->date-1;
	while((*p)->father){
		(*p)->date=(*p)->father->date;
		(*p)->father->date=min;
		p=&(*p)->father;
	}

}

template<class T>
void binomial<T>::_delete(T d){
	nodob<T> **p;
	if(findson(d,root,p)){
		reduccion(p);
		deletemin();
	}
}

template<class T>
bool binomial<T>::findson(T d,std::list<nodob<T>*> list1,nodob<T> **&p){
	auto q=list1.begin();
	while(q!=list1.end()){
			if((*q)->date==d){
				p=&(*q);
				return 1;
			}
			if((*q)->date > d){
				++q;
			}
			else{
				return findson(d,(*q)->m_son,p);
			}
	}
	return 0;
}


template <class T>
void binomial<T>::print(){
	std::ofstream file("binomial.dot");
	file<<"digraph{"<<std::endl;
	auto it=root.begin();
	int cont=1;
	while(it!=root.end()){
		file<<(*it)->date<<std::endl;
		print((*it)->m_son,cont,file);
		++it;
	}
	file<<"}";
	file.close();
	system("dot -Tpdf binomial.dot -o binomial.pdf");
}

template <class T>
void binomial<T>::print(std::list<nodob<T>*> son,int cont,std::ofstream &file ){
	auto it=son.begin();
	while(it!=son.end()){
		file<<(*it)->father->date<<" ->";
		file<<(*it)->date<<std::endl;
		print((*it)->m_son,cont+1,file);
		++it;
	}
}


