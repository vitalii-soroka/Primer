#include "MyGeometry.h"

double calculateDist(const std::pair<int, int>& a, const std::pair<int, int>& b) {
	return std::sqrt
	(std::abs(a.first - b.first) + std::abs(a.second - b.second));
}

bool check_rect(const std::pair<int, int>& a, const std::pair<int, int>& b, const std::pair<int, int>& c, const std::pair<int, int>& d)
{
	int ab = (int)calculateDist(a, b);
	int bc = (int)calculateDist(b, c);
	int cd = (int)calculateDist(c, d);
	int da = (int)calculateDist(d, a);
	int ac = (int)calculateDist(a, c);
	int bd = (int)calculateDist(b, d);
	return (ab ^ bc ^ cd ^ da ^ ac ^ bd) == 0;
}



double Quadrangle::area() const
{
	return 0.0;
}

double Quadrangle::perimeter() const
{
	return calculateDist(a, b) + calculateDist(b, c) +
		calculateDist(c, d) + calculateDist(d, a);
}

std::ostream& Quadrangle::print_info(std::ostream& os) const {
	return Figure::print_info(os) << std::endl
		<< "\t a: " << '{' << a.first << ',' << a.second << '}' << std::endl
		<< "\t b: " << '{' << b.first << ',' << b.second << '}' << std::endl
		<< "\t c: " << '{' << c.first << ',' << c.second << '}' << std::endl
		<< "\t d: " << '{' << d.first << ',' << d.second << '}';
}

std::ostream& Rectangle::print_info(std::ostream& os) const {
	return Quadrangle::print_info(os);
}

double Rectangle::area() const  {
	double ab = calculateDist(a, b);
	double bc = calculateDist(b, c);
	return ab * bc;
	// 
}

//inline double Rectangle::perimetr() const
//{
//	
//}
