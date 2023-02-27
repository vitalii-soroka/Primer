#pragma once
#include <string>
#include <iostream>

class Employee {
public:
	Employee() :id(index++) {}
	Employee(const std::string& n):name(n), id(index++){}
	Employee(const Employee& rhs) :name(rhs.name),id(index++){};
	Employee& operator=(Employee& rhs) { name = rhs.name; return *this; }

	std::ostream& print(std::ostream&);

private:
	std::string name;
	int id;
	static int index;
};
