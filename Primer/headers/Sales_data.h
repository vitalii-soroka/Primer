#pragma once
#include <iostream>
#include <string>

#ifndef SALES_DATA_H
#define SALES_DATA_H
	

template<class T> struct std::hash; // for friend declaration

class Sales_data {
	friend std::hash<Sales_data>;

	friend std::istream& operator>>(std::istream&, Sales_data&);
	friend std::ostream& operator<<(std::ostream&, const Sales_data&);
	friend Sales_data& operator+(const Sales_data&, const Sales_data&);
	friend bool operator==(const Sales_data&, const Sales_data&);
	friend bool operator!=(const Sales_data&, const Sales_data&);

public:
	Sales_data() : bookNo(""), units_sold(0), revenue(0.0) {}
	Sales_data(const std::string& s, unsigned n = 0, double p = 0.0f) :
		bookNo(s), units_sold(n), revenue(n* p) {}
	Sales_data(const Sales_data&);
	
	Sales_data& operator=(const Sales_data&);
	Sales_data& operator+=(const Sales_data&);
	Sales_data& operator=(const std::string&);
	
	// explicit operator double() const { return revenue; }
	//explicit operator std::string() const { return bookNo; }

	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;

private:

	std::string bookNo;
	unsigned units_sold;
	double revenue;
};

namespace std {
	// opens std namespace to specialize std::hash
	template<>					// we're defining a specialization with
	struct hash<Sales_data> {	// template parameter of Sales_data
		// the type used to hash an unordered container must define these types
		typedef size_t result_type;      
		typedef Sales_data argument_type; // by default, this type needs == 
		size_t operator()(const Sales_data& s) const {
			return hash<std::string>()(s.bookNo) ^
				hash<unsigned>()(s.units_sold) ^
				hash<double>()(s.revenue);
		}
		// class uses synthesized copy control  and default constructor
	};
} // no semicolon after close std namespace


#endif // SALES_DATA_H