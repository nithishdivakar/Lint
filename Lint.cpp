#include "Lint.h"

#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
#include "shorts.h"

#define DEBUG 1

//constructors

Lint::Lint():sign(true){
	digits.push_back(0);
}

Lint::Lint(uint32_t i):sign(true){
	if(i == 0){ digits.push_back(0); return;}
	while(i){
		digits.push_back(i%BASE);
		i = i/BASE;
	}
}

Lint::Lint(const Lint& I){
	if(this != &I){
		sign = I.sign;
		digits.clear();
		digits = digits_t(I.digits);
	}
}

//operations

void Lint::add(Lint &B){
	add_to_element(this->sign, this->digits , B.sign, B.digits);
}


void Lint::sub(Lint &B){
	substract_to_element(this->sign, this->digits , B.sign, B.digits);
}

void Lint::mul(Lint &M){
	multiply_to_element(this->sign, this->digits , M.sign, M.digits);
}




//overloaded operators

Lint& Lint::operator=(const Lint &I){
	if(this != &I){ //self assignment
		sign = I.sign;
		digits.clear();
		digits = digits_t(I.digits);
	}
	return *this;
}

const Lint Lint::operator+(const Lint &B){
	Lint C = *this;
	add_to_element(C.sign, C.digits , B.sign, B.digits);
	return C;
}

const Lint Lint::operator-(const Lint &B){
	Lint C = *this;
	substract_to_element(C.sign, C.digits , B.sign, B.digits);
	return C;
}

const Lint Lint::operator*(const Lint& M){
	Lint C = *this;
	multiply_to_element(C.sign, C.digits , M.sign, M.digits);	
	return C;

}

//other functions
std::string Lint::to_string() const{
	std::stringstream ss;
//	std::cout<<sign<<"\n";
	if(sign == false){
		ss<<"-";
	}
	RTRAV(digits,it){
		ss<<*it;
		#if(DEBUG)
			ss<<" ";
		#endif
	}
	return ss.str();
}
/*
#include<cstdio>
void Lint::print(){
	bool flag = true;
	RTRAV(digits,it){
		if(flag){
			printf("%2d",*it);
			flag = false;
		}else{
			printf("%02d",*it);
		}
	}
	printf("\n");
}
*/



//private member functions

void Lint::add_to_element(bool & asign, digits_t& a, const bool bsign, const digits_t& b){
	//TO DO handle sign
	// a <- a + b
	digit_t carry = 0;
	uint64_t sum; // can overflow. So use larges available
	FOR(i,0,std::min(a.size(),b.size())){
		sum   = b[i]+a[i] + carry;
		a[i]  = sum % BASE;
		carry = sum / BASE;
	}
	FOR(i,std::min(a.size(),b.size()),a.size()){
		sum   = a[i] + carry;
		a[i]  = sum % BASE;
		carry = sum / BASE;
	}
	FOR(i,std::min(b.size(),a.size()),b.size()){
		sum   = b[i] + carry;
		a.push_back( sum % BASE );
		carry = sum / BASE;
	}
	if(carry){
		a.push_back(carry);
	}
}


void Lint::multiply_to_element(bool & asign, digits_t& a, const bool bsign, const digits_t& b){

//	asign = asign*bsign;
	
	digits_t c ;

	for(unsigned int i=0;i<b.size();i++){
		digit_t carry = 0, x;
		uint64_t digit; // can overflow. so declare as maximum available
		
		unsigned int j;
		for(j=i;j<a.size()+i;j++){
			if(c.size()>j) x = c[j]; else x = 0;
			digit = x + (b[i]*a[j-i])+carry;
			carry = digit / BASE;
			if(c.size()>j) c[j] = digit % BASE;
			else      c.push_back(digit % BASE);
		}
		if(carry){
			if(c.size()>j) x = c[j]; else x = 0;
			digit = x + carry;
			carry = digit / BASE;
			if(c.size()>j) c[j] = digit % BASE;
			else      c.push_back(digit % BASE);
		}
	}
	a.clear();
	a.insert(a.begin(),ALL(c));
}

//*
void Lint::substract_to_element(bool& asign, digits_t& a, const bool bsign, const digits_t& b){
	
	if(asign != bsign){
		//shouldnt be doing substraction
		if(asign == false && bsign == true){
			//-a - +b = -(a+b)
			add_to_element(asign, a,asign,b);
			asign = false;
			return ;
		}

		if(asign == true && bsign == false){
			//+a - -b = -(a+b)
			add_to_element(asign, a,asign,b);
			asign = true;
			return ;
		}
	}
	
	if(a.size() < b.size()){
		digits_t c(b);
		bool sign = bsign;
		substract_to_element(sign, c, asign, a);
		a.clear();
		a = digits_t(c);
		asign = true - sign;
		return;
	}

	digit_t borrow = 0;
	uint64_t diff; // can overflow. So use larges available
	int k;
	FOR(i,0,std::min(a.size(),b.size())){
		//std::cout<<a[i]<<" "<<b[i]<<"\n";
		int64_t num = a[i]- borrow;
		if(num <b[i] ){
			diff = BASE - b[i] + num;
			borrow = 1;
		}else{
			diff = num - b[i];
			borrow = 0;
		}
		a[i]  = diff;
	}
	FOR(i,std::min(a.size(),b.size()),a.size()){
		//a is longer
		int64_t num = a[i]- borrow;
		if(num <0 ){
			diff = BASE - num;
			borrow = 1;
		}else{
			diff = num;
			borrow = 0;
		}
		a[i]  = diff;
		k = i;
	}

	if(borrow){
		a[k] = BASE - a[k];
		asign = true - asign;
	}//*/
}

//*/
/*
std::pair<digit_t,digit_t> Lint::mul_no_owerflow(const digit_t u, const digit_t v){
	std::pair<digit_t, digit_t> M;
	digit & wlo = M.second;
	digit & whi = M.first;

	digit_t u0,u1,v0,v1,k,t,w0,w1,w2;

	u1 = u>>32; u0 = u & 0xFFFFFFFF;
	v1 = v>>32; v0 = v & 0xFFFFFFFF;

	t = u0*v0;
	w0 = t & 0xFFFFFFFF;
	k = t >>32;

	t = u1*v0 +k;
	w1 = t & 0xFFFFFFFF;
	w2 = t>>32;
	t = u0*v1 + w1;
	k = t>>32;
	wlo = (t<<32) + w0;
	whi = u1*v1 + w2 +k ;
	return M;
}*/
