#pragma once
#include "StrVec.h";



StrVec::StrVec(std::initializer_list<std::string> ilst)
{
	auto newdata = alloc_n_copy(ilst.begin(), ilst.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
StrVec::StrVec(const StrVec& s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}
StrVec::StrVec(StrVec&& s) noexcept :
	elements(s.elements), first_free(s.first_free), cap(s.cap)
{
	s.elements = s.first_free = s.cap = nullptr;
}
StrVec& StrVec::operator=(StrVec&& rhs) noexcept
{
	if (this != &rhs) {
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		//should leave object in destructable state
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}
StrVec& StrVec::operator=(const StrVec& rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
StrVec& StrVec::operator=(std::initializer_list<std::string> il) {
	auto data = alloc_n_copy(il.begin(), il.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}
void StrVec::push_back(const std::string& s) {
	chk_n_alloc();
	alloc.construct(first_free++, s);
}
void StrVec::push_back(std::string&& s)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}
std::pair<std::string*, std::string*>
StrVec::alloc_n_copy(const std::string* b, const std::string* e)
{
	// alocated space to hold elements in range
	auto data = alloc.allocate(e - b);
	// pair of first and one past last element
	return { data, std::uninitialized_copy(b,e, data) };
}
void StrVec::free() {
	// 0 - or null poiter
	if (elements) {
		std::for_each(elements, first_free,
			[&](std::string& p) { alloc.destroy(&p); });
		alloc.deallocate(elements, capacity());
		//for (auto p = first_free; p != elements; /**/)
		//	alloc.destroy(--p);
		//alloc.deallocate(elements, cap - elements);
	}
}
void StrVec::reallocate(size_t n)
{
	// allocates n as many elements as the current size 
	auto newcapacity = size() ? n * size() : 1;
	auto first = alloc.allocate(newcapacity);

	// move  the elements 
	auto last = std::uninitialized_copy(
		std::make_move_iterator(begin()),
		std::make_move_iterator(end()),
		first);
	free();
	elements = first;
	first_free = last;
	cap = elements + newcapacity;

	// old way
	/*auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;

	for (size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();

	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;*/
}
void StrVec::reserve(size_t n)
{
	// relocate if needs more space
	if (capacity() < n) {
		reallocate(n);
	}
}
void StrVec::resize(size_t n, std::string val)
{
	if (n > size()) {
		for (size_t i = size(); i != n; ++i) {
			push_back(val);
		}
	}
}
std::ostream& StrVec::print_info(std::ostream& os)
{
	os << "Elements number: " << size()
		<< " Capacity: " << capacity() << std::endl;

	os << "\t";
	for (auto p = begin(); p != end(); p++) {
		os << *p << " ";
	}
	return os << std::endl;
}
bool operator==(const StrVec& lhs, const StrVec& rhs)
{
	return lhs.size() == rhs.size() ? 
		std::equal(lhs.begin(), lhs.end(), rhs.begin())
		: false;
}
bool operator!=(const StrVec& lhs, const StrVec& rhs)
{
	return !(lhs == rhs);
}
