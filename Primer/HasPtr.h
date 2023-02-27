#include <string>
#include <iostream>

class HasPtr {
	friend void swap(HasPtr&, HasPtr&);
public:
	HasPtr(const std::string& s = std::string()) :
		ps(new std::string(s)), i(0) {}
	HasPtr(const HasPtr& rhs) : 
		ps(new std::string(*rhs.ps)), i(rhs.i) {}
	// move constructor
	HasPtr(HasPtr&& p) noexcept : ps(p.ps), i(p.i) { p.ps = nullptr; }
	// move and copy - assignment operator in one, thanks to move constr
	// lvalues are copied and rvalues are moved 
	// HasPtr& operator=(HasPtr) {	swap(*this, rhs);return *this;}
	HasPtr& operator=(const HasPtr&);
	HasPtr& operator=(HasPtr&&) noexcept;

	bool operator<(const HasPtr& rhs) {
		return *ps < *rhs.ps;
	}
	~HasPtr() { delete ps; }

	void set_ps(const std::string& rhs) { *ps = rhs; }
	std::ostream& print(std::ostream& os) {
		return os << *ps << ' ' << i;
	}

private:
	std::string* ps;
	int i;
};
class HasPtrRef {
public:
	HasPtrRef(const std::string& s = std::string()) :
		ps(new std::string(s)), i(0), users(new std::size_t(1)) {}

	HasPtrRef(const HasPtrRef& rhs) :
		ps(rhs.ps), i(rhs.i), users(rhs.users) { ++*users;}

	HasPtrRef& operator=(const HasPtrRef&);
	~HasPtrRef();

	void set_ps(const std::string& rhs) { *ps = rhs; }

	std::ostream& print(std::ostream& os);

private:
	std::string* ps;
	std::size_t* users;
	int i;

	void remove_check();
};