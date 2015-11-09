#include "Lint.h"

int main(){

	Lint t1(123456789);
	Lint t2(111111110);
	Lint t3,t4;
	
	printf(" 234567899 = \n"); 

	t3=t1+t2;
	t3.print();
	t1.print();
	t2.print();

	t4 = t2*t2;
	printf(" 12345678765432100 = \n"); 
	t4.print();
	/*
	int N = 15-2;
	while(N--){
		t3 = t2;
		t3*t3;
		t3+t1;
		t1 = t2;
		t2 = t3;
	}
	t2.print();
	*/
	return 0;
}
