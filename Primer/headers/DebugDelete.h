#pragma once
#ifndef DEBUG_DELETE_H
#define DEBUG_DELETE_H

#include <iostream>

class DebugDelete {
public:
	DebugDelete(std::ostream &s = std::cerr) : os(s) {}

	template <typename T> void operator()(T* p) const {
		os << "deleting unique_ptr" << std::endl; 
		delete p;
	}

private:
	std::ifstream ifStream;
	
	std::ostream &os;
};









#endif // !DEBUG_DELETE_H
