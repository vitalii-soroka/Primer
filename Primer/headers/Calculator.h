#pragma once
#include <map>
#include <string>
#include <functional>

// different methods of function type
auto mod = [](int lhs, int rhs) { return lhs % rhs; };
struct Div { int operator()(int lhs, int rhs) const { return lhs / rhs; } };
int add(int lhs, int rhs) { return lhs + rhs; };
int power(int base, int p) { return p == 1 ? base : base * power(base, p - 1); }

class IntCalculator {
public:

	std::function<int(int, int)> & 
		operator[](std::string s) { return binops[s]; }

private:
	std::map<std::string, std::function<int(int, int)>> binops {
		{"+",add},								//function pointer
		{"-",std::minus<int>()},				//library funcrtion
		{"*",[](int i, int j) {return i * j; }},// unnamed lambda
		{"/", Div()},							// user-defined function
		{"%", mod},								// named lambda
		{"^",power}
	};
};