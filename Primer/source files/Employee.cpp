#include "Employee.h"

int Employee::index = 0;

std::ostream& Employee::print(std::ostream& os) {
	os << "Employee data:" << std::endl <<
		"\tname: " << name << std::endl <<
		"\tid: " << id;
	return os;
}