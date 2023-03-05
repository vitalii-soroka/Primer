#pragma once
#ifndef DEBUG_DELETE_H
#define DEBUG_DELETE_H

#include <iostream>

class DebugDelete {
public:
	DebugDelete() {}

	template <typename T> void operator()(T* p,std::string name  = "pointer") const {
		std::cout << "DEBUG DELETE: deleting " << name << std::endl; 
		delete p;
	}

private:
	//std::ostream &os;
};









#endif // !DEBUG_DELETE_H
