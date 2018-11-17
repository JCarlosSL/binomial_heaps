#include <iostream>
#include "binomial.cpp"
#include <time.h>

using namespace std;

int main(){
	binomial<int> carlos;

	for(int i=0;i<30;++i){
		carlos.insert(i);
	}
	//carlos.deletemin();
	carlos._delete(12);
	carlos.print();
	return 0;
}
