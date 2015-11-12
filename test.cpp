#include "Lint.h"
#include <iostream>

int main(){

	Lint t1(789);
	Lint t2("-111111000349863538922852502256258268327573765392628053650836253265302532058650836530285632085630285353620864203");
	Lint t3(""),t4;
	

	t3 = t1-t2;
	t4 = t2*t2*t2;
	std::cout<<t2.to_string()<<"\n";
	std::cout<<t3.to_string()<<"\n";
	std::cout<<t4.to_string()<<"\n";
	//std::cout<<(t1+-t2).to_string()<<"\n";
	//std::cout<<(t2+-t1).to_string()<<"\n";
	return 0;
}
