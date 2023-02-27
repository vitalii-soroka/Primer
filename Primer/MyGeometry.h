#pragma once
#include <iostream>
#include <string>
#include <cmath> /* abs */

double calculateDist(const std::pair<int, int>& a, const std::pair<int, int>& b);
bool check_rect(const std::pair<int, int>& a,const std::pair<int, int>& b,
	const std::pair<int, int>& c,const std::pair<int, int>& d);

class Figure {
public:
	typedef std::pair<int, int> Coordinate;

	Figure() = default;
	Figure(const std::string& s) : name(s) {}
	virtual double area() const = 0;
	virtual double perimeter() const = 0;

	virtual std::ostream& print_info(std::ostream& os) const { return os << "Figure: " << name; };

protected:
	std::string name;
};

class Quadrangle : public Figure {
public:
	Quadrangle(const std::string& s, const Coordinate& a, const Coordinate& b, 
		const Coordinate& c, const Coordinate& d) : 
		Figure(s), a(a),b(b),c(c),d(d){}

	~Quadrangle() = default;

	 virtual double area() const override;
	 virtual double perimeter() const override;
	 virtual std::ostream& print_info(std::ostream&) const override;

protected:
	Coordinate a;
	Coordinate b;
	Coordinate c;
	Coordinate d;
};

class Rectangle : public Quadrangle {
public:
	Rectangle(const std::string& s, const Coordinate& a, const Coordinate& b,
		const Coordinate& c, const Coordinate& d) : Quadrangle(s,a,b,c,d) {
		if (!check_rect(a, b, c, d)) {
			std::cout << "incorrect parameters for - " << name <<
				" . Default parameters used instead." << std::endl;
			Quadrangle::a = { 0,0 };
			Quadrangle::b = { 0,1 };
			Quadrangle::c = { 1,1 };
			Quadrangle::d = { 1,0 };
		}
	}

	~Rectangle() = default;

	double area() const override;
	std::ostream& print_info(std::ostream&) const override;


private:

};

