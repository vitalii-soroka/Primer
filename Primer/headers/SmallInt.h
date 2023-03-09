#pragma once
#include <iostream>

class SmallInt {
public:
	SmallInt(int i = 0): val(i){
		if (i < 0 || i > 255)
			throw std::out_of_range("Bad SmallInt Value");
	}
	explicit operator int() const { return (int)val; }
private:
	std::size_t val;
};