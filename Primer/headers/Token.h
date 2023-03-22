#pragma once
#include <string>
#include <iostream>
#include "Sales_data.h"

class Token {
public:
	// copy control needed bacause our class has a union with a string member
	// to do: move constructor and move-assignment operator 
	Token() : tok(INT), ival{ 0 } { }
	Token(const Token& t) : tok(t.tok) { copyUnion(t); }
	Token(Token&&) noexcept;
	Token& operator=(const Token&);
	Token& operator=(Token&&) noexcept;

	// if union holds a string, we must destroy it? 19.1.2 p824
	~Token() { check_objects(); }

	Token& operator=(const Sales_data&);
	Token& operator=(const std::string&);
	Token& operator=(char);
	Token& operator=(int);
	Token& operator=(double);

	std::ostream& print(std::ostream&);

private:
	enum { INT, CHAR, DBL, STR, SD } tok; // discriminant
	// nested, unnamed, umscoped enumeration
	union {							// anonymous union
		char		cval;
		int			ival;
		double		dval;
		std::string sval;
		Sales_data  sale;
	}; // each Token object has an unnamed member of this unnamed union type

	void check_objects();

	void copyUnion(const Token&);
	void moveUnion(Token&&);
};

inline void Token::check_objects() {
	switch (tok) {
	case STR: sval.~basic_string(); return;
	case  SD: sale.~Sales_data(); return;
	}
}

Token::Token(Token&& t) noexcept : tok(std::move(t.tok)) {
	moveUnion(std::move(t));
}

Token& Token::operator=(int i) {
	check_objects();
	ival = i;
	tok = INT;
	return *this;
}
Token& Token::operator=(char c) {
	check_objects();
	cval = c;
	tok = CHAR;
	return *this;
}
Token& Token::operator=(double d) {
	check_objects();
	dval = d;
	tok = DBL;
	return *this;
}
Token& Token::operator=(Token&& t) noexcept {
	if (this != &t) {
		if (tok == STR && t.tok != STR) sval.~basic_string();
		if (tok == STR && t.tok != STR) sval = std::move(t.sval);
		else moveUnion(std::move(t)); // basic types copy
	}
	return *this;
}
Token& Token::operator=(const Token& t) {
	// need to free old string
	if (tok == STR && t.tok != STR) sval.~basic_string();
	else if (tok == SD && t.tok != SD) sale.~Sales_data();
	
	if (tok == STR && t.tok == STR) sval = t.sval;
	else if (tok == SD && t.tok == SD) sale = t.sale;

	else
		copyUnion(t);

	tok = t.tok;
	return *this;
}
Token& Token::operator=(const Sales_data& s) {
	if (tok == STR) sval.~basic_string();
	if (tok == SD) sale = s; 
	else {
		new (&sale) Sales_data(s);
		tok = SD;
	}
	return *this;
}
Token& Token::operator=(const std::string& s) {
	if (tok == SD) sale.~Sales_data();	// need to release string correctly

	if (tok == STR)	sval = s;			// just assign if already a string		
	else {
		new (&sval) std::string(s);	// otherwise construct(not allocates) a string
		tok = STR;
	}
	return *this;
}

void Token::copyUnion(const Token& t) {
	switch (t.tok) {
	case Token::INT: ival = t.ival; break;
	case Token::CHAR: cval = t.cval; break;
	case Token::DBL: dval = t.dval; break;
	case Token::STR: new (&sval) std::string(t.sval); break;
	case Token::SD: new (&sale) Sales_data(t.sale);  break;
	default: break;
	}
}
void Token::moveUnion(Token&& t) {
	switch (t.tok) {
	case Token::STR: new (&sval) std::string(std::move(t.sval)); break;
	case Token::SD:  new (&sale) Sales_data(std::move(t.sale)); break;
	default: copyUnion(t); break;			// can't move built in types 
	}
}

std::ostream& Token::print(std::ostream& os) {
	os << "Token: " << tok << "\t";
	switch (tok) {
	case Token::INT: os << ival; break;
	case Token::CHAR: os << cval; break;
	case Token::DBL: os << dval; break;
	case Token::STR: os << sval; break;
	case Token::SD: os << sale;  break;
	default: os << "no value";
	}

	return os;
}
