#include "Lint.h"
#include <iostream>

int main(){

	Lint t1(789);
	Lint t2(111111000);
	Lint t3,t4;
	

	t3 = t1-t2;
	t4 = t2-t1;
	std::cout<<t3.to_string()<<"\n";
	std::cout<<t4.to_string()<<"\n";
	std::cout<<(t1+-t2).to_string()<<"\n";
	std::cout<<(t2+-t1).to_string()<<"\n";
	return 0;
}
