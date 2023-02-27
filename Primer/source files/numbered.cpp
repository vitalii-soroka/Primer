#include "numbered.h"

int numbered::last_id = 0;

void numbered::f() {
	std::cout << name << std::endl;
 	std::cout << "\tmysn: " << mysn << std::endl;
	std::cout << "\tid: " << last_id << std::endl;
}