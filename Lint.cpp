#include "Lint.h"

#include <iostream>
#include <utility>
#include <algorithm>
#include <sstream>


/*  Short hands */
#define ALL(c) (c).begin(),(c).end()
#define TRAV(c,i) for(\
				typeof((c).begin()) i = (c).begin();\
				i != (c).end();\
				i++)
#define RTRAV(c,i) for(\
				typeof((c).rbegin()) i = (c).rbegin();\
				i != (c).rend();\
				i++)
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
/*  Short hands */



#define NEGATIVE_SIGN  false
#define POSITIVE_SIGN  true


#define DEBUG 1

//constructors

Lint::Lint():sign(POSITIVE_SIGN){
	digits.push_back(0);
}

Lint::Lint(uint32_t i):sign(POSITIVE_SIGN){
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

Lint::Lint(const std::string& s):sign(POSITIVE_SIGN){
int start =0,end = s.length();
	if(s.length()<1){digits.push_back(0); return ;}

	if(s[0] == '-'){
		sign =  NEGATIVE_SIGN;
		start = 1;
	}else if(s[0] == '+'){
		sign = POSITIVE_SIGN;
		start = 1;
	}

	FOR(i,start,end){
		if(s[i] < '0' || s[i] >'9'){
			digits.push_back(0);
			return;
		}
	}

	digit_t b = BASE;
	int digitsBASE = 0;

	// counting no of digits in BASE
	while(b/=10){digitsBASE++;}

	for(int i=end;i>=start;i-=digitsBASE){
		int pos,len;
		pos = std::max(i-digitsBASE,start);
		len = i-pos;
		if(len<=0) continue;
//		std::cout<<"\n"<<pos<<" "<<len;
		std::string D = s.substr(pos,len);
		digit_t dig = stoi(D);
		digits.push_back(dig);
	}
}
//operations

void Lint::add(const Lint &B){
	add_to_element(this->sign, this->digits , B.sign, B.digits);
}


void Lint::sub(const Lint &B){
	substract_to_element(this->sign, this->digits , B.sign, B.digits);
}

void Lint::mul(const Lint &M){
	multiply_to_element(this->sign, this->digits , M.sign, M.digits);
}

void Lint::negative(){
	if(sign == POSITIVE_SIGN){
		sign = NEGATIVE_SIGN;
	}else{
		sign = POSITIVE_SIGN;
	}
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

const Lint Lint::operator+(const Lint &B) const{
	Lint C = *this;
	add_to_element(C.sign, C.digits , B.sign, B.digits);
	return C;
}

const Lint Lint::operator-(const Lint &B) const {
	Lint C = *this;
	substract_to_element(C.sign, C.digits , B.sign, B.digits);
	return C;
}

const Lint Lint::operator*(const Lint& M) const{
	Lint C = *this;
	multiply_to_element(C.sign, C.digits , M.sign, M.digits);	
	return C;

}

const Lint Lint::operator-() const{
	Lint C = *this;
	if(C.sign == POSITIVE_SIGN){
		C.sign = NEGATIVE_SIGN;
	}else{
		C.sign = POSITIVE_SIGN;
	}
	return C;
}

Lint & Lint::operator+=(const Lint &B){
	add(B);
	return *this;
}

Lint & Lint::operator-=(const Lint &B){
	sub(B);
	return *this;
}

bool Lint::operator==(const Lint &I) const{
	return !(*this != I);
}
bool Lint::operator!=(const Lint &I) const{
	if(I.sign != sign){
		std::cout<<"1";
		return true;
	}
	if(I.digits.size() != digits.size() ){
		std::cout<<"2";
		return true;
	}

	auto UN = std::mismatch(ALL(I.digits), digits.begin());
	// std::cout<<*UN.first<<" "<<*UN.second<<" ";
	return (UN.first != I.digits.end() || UN.second != digits.end());
}
//other functions
std::string Lint::to_string() const{
	std::stringstream ss;
//	std::cout<<sign<<"\n";
	if(sign == NEGATIVE_SIGN){
		ss<<"-";
	}
	int b=BASE,d=0;
	while(b/=10){d++;}

	char buffer[d+1];
	bool firstdigit=true;	

	RTRAV(digits,it){
		if(firstdigit){
			sprintf(buffer,"%d",*it);
			firstdigit = NEGATIVE_SIGN;
		}else{
			sprintf(buffer,"%0.*d",d,*it);
		}
		ss<<buffer;
		#if(DEBUG)
			ss<<" ";
		#endif
	}
	return ss.str();
}
/*
#include<cstdio>
void Lint::print(){
	bool flag = POSITIVE_SIGN;
	RTRAV(digits,it){
		if(flag){
			printf("%2d",*it);
			flag = NEGATIVE_SIGN;
		}else{
			printf("%02d",*it);
		}
	}
	printf("\n");
}
*/



//private member functions


void Lint::add_to_element(bool & asign, digits_t& a, const bool bsign, const digits_t& b) const{
/*
-x + -y = -(x+y)
+x + +y = +(x+y)
-x + +y = -(x-y)
+x + -y = +(x-y)
*/
	if(asign == bsign){
		addition(a,b);
		//asign = asign;// no change for sign
	}else{
		if(substraction(a,b))
			asign = !asign;
		//asign = asign;// no change in sign
	}
}

void Lint::substract_to_element(bool & asign, digits_t& a, const bool bsign, const digits_t& b) const{

/*
-x - -y = -(x+y)
+x - +y = +(x+y)
-x - +y = -(x-y)
+x - -y = +(x-y)
*/
	if(asign == bsign){
		if(substraction(a,b))
			asign = !asign;
		//asign = asign;// no change for sign
	}else{
		addition(a,b);
		//asign = asign;// no change in sign
	}

}




void Lint::addition(digits_t& a,const digits_t& b) const{
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


void Lint::multiply_to_element(bool & asign, digits_t& a, const bool bsign, const digits_t& b) const{

	if(asign == bsign){
		asign = POSITIVE_SIGN;
	}else{
		asign = NEGATIVE_SIGN;
	}
	
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
bool Lint::substraction(digits_t& a, const digits_t& b) const{
	
	if(a.size() < b.size()){
		digits_t c(b);
		substraction(c, a);
		a.clear();
		a = digits_t(c);
		return true;//flip the sign
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
	}
	return false;
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
