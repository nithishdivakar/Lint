#include<vector>
#include<iostream>
#include<cstdint>
#include<cstdio>
#include "shorts.h"

using namespace std;
class integer{
	typedef vector<uint8_t> storage;
	static const uint32_t BASE=100;
	public:
	storage v;
	integer(){v.push_back(0);}
	integer(uint32_t i){
		if(i == 0){ v.push_back(0); return;}
		while(i){
			v.push_back(i%BASE);
			i = i/BASE;
		}
	}
	integer(integer& i){
		v.clear();
		v = storage(i.v);
	}
	integer(storage vec){
		TRAV(vec,it){
			v.push_back(*it%BASE);
		}
	}
	void print(){
		bool flag = true;
		RTRAV(v,it){
			if(flag){
				printf("%2d",*it);
				flag = false;
			}else{
				printf("%02d",*it);
			}
		}
	}
	void operator=(integer &I){
		v.clear();
		v = storage(I.v);
	}
	void operator+(integer &add){
		storage &a = add.v;
		uint32_t carry = 0;
		FOR(i,0,min(a.size(),v.size())){
			uint32_t sum = a[i]+v[i] + carry;
			v[i]  = sum % BASE;
			carry = sum / BASE;
		}
		FOR(i,min(a.size(),v.size()),v.size()){
			uint32_t sum = v[i] + carry;
			v[i]  = sum % BASE;
			carry = sum / BASE;
		}
		FOR(i,min(a.size(),v.size()),a.size()){
			uint32_t sum = a[i] + carry;
			v.push_back( sum % BASE );
			carry = sum / BASE;
		}
		if(carry){
			v.push_back(carry);
		}

	}
	void operator*(integer& mult){
		storage &a = (this->v);
		storage &b = mult.v;
		storage c ;
		FOR(i,0,b.size()){
			int carry = 0;
			int digit,j,x;
			for(j=i;j<a.size()+i;j++){
				if(c.size()>j) x = c[j]; else x = 0;
				digit = x + (b[i]*a[j-i])+carry;
				carry = digit/BASE;
				if(c.size()>j) c[j] = digit % BASE;
				else     c.push_back(digit % BASE);
			}
			if(carry){	
				if(c.size()>j) x = c[j]; else x = 0;
				digit = x + carry;
				carry = digit / BASE;
				if(c.size()>j) c[j] = digit % BASE;
				else     c.push_back(digit % BASE);
			}
		}
		v.clear();
		v.insert(v.begin(),ALL(c));
		return;
	}
};


int main(){

	integer t1(1);
	integer t2(2);
	integer t3;
	int N = 15-2;
	while(N--){
		t3 = t2;
		t3*t3;
		t3+t1;
		t1 = t2;
		t2 = t3;
	}
	t2.print();
	return 0;
}
