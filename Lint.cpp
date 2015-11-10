#include "Lint.h"

#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>
#include "shorts.h"



//constructors

Lint::Lint(){
	digits.push_back(0);
}

Lint::Lint(uint32_t i){
	if(i == 0){ digits.push_back(0); return;}
	while(i){
		digits.push_back(i%BASE);
		i = i/BASE;
	}
}

Lint::Lint(const Lint& I){
	if(this != &I){
		digits.clear();
		digits = digits_t(I.digits);
	}
}

Lint::Lint(digits_t vec){
	TRAV(vec,it){
		digits.push_back( (*it) % BASE );
	}
}


//operations

void Lint::add(Lint &B){
	add_to_element(this->sign, this->digits , B.sign, B.digits);
}


void Lint::mul(Lint &M){
	multiply_to_element(this->sign, this->digits , M.sign, M.digits);
}




//overloaded operators

Lint& Lint::operator=(const Lint &I){
	if(this != &I){ //self assignment
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

const Lint Lint::operator*(const Lint& M){
	Lint C = *this;
	multiply_to_element(C.sign, C.digits , M.sign, M.digits);	
	return C;

}

//other functions
std::string Lint::to_string(){
	std::stringstream ss;
	RTRAV(digits,it){
		ss<<*it;
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
		sum   = a[i] + carry;
		a.push_back( sum % BASE );
		carry = sum / BASE;
	}
	if(carry){
		a.push_back(carry);
	}
}


void Lint::multiply_to_element(bool & asign, digits_t& a, const bool bsign, const digits_t& b){

	asign = asign*bsign;
	
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
