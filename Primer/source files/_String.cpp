#include "_String.h"

_String::_String(const char* b)
{
	auto e = b;
	while (*e != '\0') ++e;

	auto newdata = alloc_n_copy(b,e);
	elements = newdata.first;
	first_free = cap = newdata.second;

}
_String::_String(const _String& s)
{
	std::cout << "String copy called" << std::endl;
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
_String::_String(_String&& s) noexcept : 
	cap(s.cap), elements(s.elements), first_free(s.first_free)
{
	std::cout << "String(String&&) - called" << std::endl;
	s.cap = s.elements = s.first_free = nullptr;
}
_String& _String::operator=(_String&& rhs) noexcept
{
	std::cout << "operator=(String&&) - called" << std::endl;
	if (this != &rhs) {
		free();
		cap = rhs.cap;
		elements = rhs.elements;
		first_free = rhs.first_free;

		cap = elements = first_free = nullptr;
	}
	return *this;
}
_String& _String::operator=(const _String& rhs)
{
	std::cout << "String operator= called" << std::endl;
	auto newdata = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
	
}
void _String::print() const
{
	for (auto p = elements; p != first_free; ++p) {
		std::cout << *p;
	}
	std::cout << std::endl;

}
std::pair<char*, char*> _String::alloc_n_copy(const char* b, const char* e)
{
	// alocated space (uninitialized) to hold elements in range
	auto data = alloc.allocate(e - b);
	// pair of first and one past last element, copy returns pointer to past last?
	return { data, std::uninitialized_copy(b,e, data) };
}
void _String::free()
{
	if (elements) {
		for (auto p = first_free; p != elements; )
			alloc.destroy(--p);
		alloc.deallocate(elements, cap - elements);
	}
}

std::ostream& operator<<(std::ostream& os, const _String& s)
{
	for (auto it = s.begin(); it != s.end(); ++it) os << *it;
	return os;
}

bool operator==(const _String& lhs, const _String& rhs)
{
	
	return lhs.size() == rhs.size()  ?
		std::equal(lhs.begin(), lhs.end(), rhs.begin()) : false;
}
bool operator!=(const _String& lhs, const _String& rhs)
{
	return !(lhs == rhs);
}
