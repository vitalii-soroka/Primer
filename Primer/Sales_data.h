#pragma once
#include <iostream>
#include <string>

#ifndef SALES_DATA_H
#define SALES_DATA_H

class Sales_data {
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
	
	explicit operator double() const { return revenue; }
	explicit operator std::string() const { return bookNo; }

	std::string isbn() const { return bookNo; }
	Sales_data& combine(const Sales_data&);
	double avg_price() const;

private:

	std::string bookNo;
	unsigned units_sold;
	double revenue;
};
#endif // SALES_DATA_H