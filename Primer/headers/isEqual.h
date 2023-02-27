#pragma once
class isEqual {
public:
	isEqual(int v) : value(v){}
	bool operator()(const int& v) const {
		return v == value;
	}
private:
	int value;
};