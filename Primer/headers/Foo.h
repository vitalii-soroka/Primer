#pragma once
#include <vector>
#include <algorithm>

class Foo {
public:
	Foo sorted()&&;			// may run on modifiable rvalues
	Foo sorted() const&;	// may run on any kind of Foo
	Foo& operator=(const Foo& )&;

	// Foo sorted()&&;		// reference qualified
	// Foo sorted() const;	// error : no reference qualified

	using Comp = bool(const int&, const int&);
	Foo sorted(Comp*);			// ok:
	Foo sorted(Comp*) const ;	// ok: reference qualified

private:
	std::vector<int> data;
};
// sorts rvalue object
Foo Foo::sorted()&& {
	std::cout << "sorted&& called" << std::endl;
	std::sort(data.begin(), data.end());
	return *this;
}

// object or const or lvalue; either way we can't sort in place;
Foo Foo::sorted() const& {
	std::cout << "sorted const& called" << std::endl;
	//Foo ret(*this);			// infinity loop
	//return ret.sorted();
	return Foo(*this).sorted();

	// Foo ret(*this);									// makes copy
	// std::sort(ret.data.begin(), ret.data.end());	// sort copy
	// return ret;										// return copy
}