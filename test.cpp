#include "Lint.h"
#include <iostream>

int main(){

	Lint t1(1);
//	Lint t2("-111111000349863538922852502256258268327573765392628053650836253265302532058650836530285632085630285353620864203");
	Lint t3("-1234567890"),t4("-1234567890");
	t4 = t3+t1;

//	t3 = t2;
	std::cout<<"["<<(t4==t3)<<"}\n";
//	std::cout<<(t1==t3)<<"\n";
//	std::cout<<t4.to_string()<<"\n";
	//std::cout<<(t1+-t2).to_string()<<"\n";
	//std::cout<<(t2+-t1).to_string()<<"\n";
	return 0;
}
