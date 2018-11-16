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
	merge(list1);

}

template <class T>
void binomial<T>::merge(std::list<nodob<T>*> &list1){
	auto it=list1.begin();
	auto r=root.begin();
	while(it!=list1.end()){
		if((*it)->grade < (*r)->grade){
			root.push_front(*it);
		}
		else if((*it)->grade==(*r)->grade){
			auto p=_union(*it,*r);
			if((*r)==p){
				r=it;	
			}
			if(r!=root.end()){
				++r;
			}
			else{
				break;
			}
			
		}
		else{
			root.push_back(*it);
		}
		++it;
	}
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


