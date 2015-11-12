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
	void addition    (digits_t& , const  digits_t&) const;
	bool substraction(digits_t& , const  digits_t&) const;
	void add_to_element      (bool&, digits_t& , const bool,const  digits_t&) const;
	void substract_to_element(bool&, digits_t& , const bool,const  digits_t&) const ;
	void multiply_to_element (bool&, digits_t& , const bool, const digits_t&) const;

public://constructors
	Lint();
	Lint(uint32_t);
	Lint(const Lint&);
	Lint(const std::string&);

public://operations
	void add(const Lint &);
	void sub(const Lint &);
	void mul(const Lint &);
	void negative();

public://overloaded operators
	Lint& operator=(const Lint &);
	const Lint operator+(const Lint &) const;
	const Lint operator-(const Lint &) const;
	const Lint operator*(const Lint &) const;
	const Lint operator-() const;
	Lint & operator+=(const Lint &);
	Lint & operator-=(const Lint &);
	bool operator==(const Lint &) const;
	bool operator!=(const Lint &) const;
public://other functions
	std::string to_string() const;
};



#endif


