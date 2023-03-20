#pragma once
#include <stdexcept> // for runtime_error
class out_of_stock_error : public std::runtime_error {
public:
	explicit out_of_stock_error(const std::string &s) : std::runtime_error(s) {}
};

class isbn_mismatch : public std::logic_error {
public:
	explicit isbn_mismatch(const std::string& s): std::logic_error(s) {}

	isbn_mismatch(const std::string &s, const std::string &lhs, const std::string &rhs) :
		std::logic_error(s), left(lhs), right(rhs) {}
	const std::string left, right;
};