#include <iostream>
#include <memory>
#include <new>


void Exercise12_23() {
	std::string msg = "hello there";

	char* p = new char[msg.size()];//{'h', 'e', 'l','l','o', ' ','t','h','e','r','e'};
	int i = 0;
	for (char* q = p; q != p + msg.size(); ++i, ++q) {
		*q = msg[i];
		std::cout << *q << ' ';
	}
	std::cout << std::endl;
	delete[] p;
}

//int main() {
//
//	Exercise12_23();
//	return 0;
//}