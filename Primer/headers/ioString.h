#pragma once
#include <iostream>
#include <string>

class PrintString {
public:
	PrintString(std::ostream& o = std::cout, char c = ' ') :
		os(o), sep(c) {}
	void operator()(const std::string &s) const {
		os << s << sep; }

private:
	std::ostream& os;
	char sep;
};
class ReadString {
public:
	ReadString(std::istream& i = std::cin):is(i) {}
	std::string operator()() {
		std::string s;
		std::getline(is, s);
		return is ? s : std::string();
	}
private:
	std::istream& is;
};
class SizeComp {
public:
	SizeComp(size_t n) : sz(n) {}
	bool operator()(const std::string& str) {
		return sz == str.size();}

private:
	size_t sz;
};
class inSizeRange {
public:
	inSizeRange(size_t l = 1, size_t u = 10) : lower(l),upper(u){}
	bool operator()(const std::string& str) {
		return str.size() >= upper ? true : false; }
private:
	size_t lower;
	size_t upper;
};