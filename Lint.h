#ifndef __LINT__
#define __LINT__

#include<vector>
#include<cstdint>


class Lint {
private:
	typedef uint32_t digit_t;
	typedef std::vector<digit_t> digits_t;

	static const digit_t BASE=100000L;

	digits_t digits;
	bool sign;//todo true positive false negative

private: // functions;
	void addition    (digits_t& , const  digits_t&);
	bool substraction(digits_t& , const  digits_t&);
	void add_to_element      (bool&, digits_t& , const bool,const  digits_t&);
	void substract_to_element(bool&, digits_t& , const bool,const  digits_t&);
	void multiply_to_element (bool&, digits_t& , const bool, const digits_t&);

public://constructors
	Lint();
	Lint(uint32_t i);
	Lint(const Lint&);

public://operations
	void add(Lint &A);
	void sub(Lint &A);
	void mul(Lint &A);

public://overloaded operators
	Lint& operator=(const Lint &I);
	const Lint operator+(const Lint &B);
	const Lint operator-(const Lint &B);
	const Lint operator*(const Lint &M);
	const Lint operator-();

public://other functions
	std::string to_string() const;
};



#endif


