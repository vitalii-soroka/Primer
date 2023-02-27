#include "HasPtr.h"

void swap(HasPtr& lhs, HasPtr& rhs)
{
	using std::swap;
	swap(lhs.ps, rhs.ps);
	swap(lhs.i, rhs.i);
	std::cout << "swap(HasPtr&,HasPtr&)" << std::endl;
}

// HasPtrRef
void HasPtrRef::remove_check() {
	//if users goes to 0, deletes all pointers
	if (-- * users == 0) {
		delete ps;
		delete users;
	}
}

HasPtrRef&
HasPtrRef::operator=(const HasPtrRef& rhs) {
	++*rhs.users;
	remove_check();

	ps = rhs.ps;
	i = rhs.i;
	users = rhs.users;
	return *this;
}
HasPtrRef::~HasPtrRef() {
	remove_check();
}
std::ostream& HasPtrRef::print(std::ostream& os)
{
	os << *ps << ' ' << i << " users: " << *users;
	return os;
}

// HasPtr
HasPtr& HasPtr::operator=(const HasPtr& rhs)
{
	// WARNING: ensure self assignment gets the correct result!!!
	// Remember to free resources before deleting!!!
	auto newp = new std::string(*rhs.ps);
	delete ps;

	ps = newp;
	i = rhs.i;
	
	return*this;
	// ps = new std::string(*rhs.ps);
	// i = rhs.i;

}
HasPtr& HasPtr::operator=(HasPtr&& rhs) noexcept
{
	if (this != &rhs) {
		delete ps;
		ps = rhs.ps;
		i = rhs.i;
		rhs.ps = nullptr;
	}
	return *this;
}
