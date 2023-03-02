#pragma once
#ifndef DEBUG_DELETE_H
#define DEBUG_DELETE_H

#include <iostream>

class DebugDelete {
public:
	DebugDelete(std::ostream &s = std::cout) : os(s) {}

	template <typename T> void operator()(T* p,std::string name  = "pointer") const {
		os << "DEBUG DELETE: deleting " << name << std::endl; 
		delete p;
	}

private:
	std::ifstream ifStream;
	
	std::ostream &os;
};









#endif // !DEBUG_DELETE_H
