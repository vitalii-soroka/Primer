#pragma once
#ifndef VEC_H
#define VEC_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <algorithm>

template <typename T> class Vec;

template <typename T>
bool operator==(const Vec<T>& lhs, const Vec<T>& rhs);

template <typename T>
bool operator!=(const Vec<T>& lhs, const Vec<T>& rhs);

// friend bool operator==(const StrVec&, const StrVec&);
// friend bool operator!=(const StrVec&, const StrVec&);
template <typename T> 
class Vec {
	friend bool operator== <>(const Vec&, const Vec&);
public:
	friend bool operator!= <>(const Vec&, const Vec&);
	Vec() :
		elements(nullptr),
		first_free(nullptr),
		cap(nullptr) {}
	Vec(std::initializer_list<T>);
	Vec(const Vec&);
	Vec(Vec&&) noexcept;

	Vec& operator=(Vec&& rhs) noexcept;
	Vec& operator=(const Vec&);
	Vec& operator=(std::initializer_list<T>);
	// StrVec& operator=(const StrVec&)& or && // this can be l/rvalue;
	// const & // ok
	T& operator[](std::size_t n) { return elements[n]; }
	const T& operator[](std::size_t n) const { return elements[n]; }

	~Vec() { free(); }

	void push_back(const T&); // copy element
	void push_back(T&&);		// move element

	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	void reserve(size_t n);
	void resize(size_t n, T);
	T* begin() const { return elements; }
	T* end() const { return first_free; }

	std::ostream& print_info(std::ostream&);

private:
	std::allocator<T> alloc;

	std::pair<T*, T*> alloc_n_copy
	(const T*, const T*);

	void free();
	void reallocate(size_t n = 2);
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }

	T* elements;
	T* first_free;
	T* cap;
};

template <typename T>
Vec<T>::Vec(std::initializer_list<T> ilst)
{
	auto newdata = alloc_n_copy(ilst.begin(), ilst.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template <typename T> 
Vec<T>::Vec(const Vec& s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template <typename T> 
Vec<T>::Vec(Vec&& s) noexcept :
	elements(s.elements), first_free(s.first_free), cap(s.cap)
{
	s.elements = s.first_free = s.cap = nullptr;
}

template <typename T>
Vec<T>& Vec<T>::operator=(Vec&& rhs) noexcept
{
	if (this != &rhs) {
		free();
		elements = rhs.elements;
		first_free = rhs.first_free;
		cap = rhs.cap;
		//should leave object in destructible state
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

template <typename T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

template<typename T>
Vec<T>& Vec<T>::operator=(std::initializer_list<T> il) {
	auto data = alloc_n_copy(il.begin(), il.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

template <typename T>
void Vec<T>::push_back(const T& s) {
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

template <typename T>
void Vec<T>::push_back(T&& s)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::move(s));
}

template <typename T>
std::pair<T*, T*>
Vec<T>::alloc_n_copy(const T* b, const T* e)
{
	// alocated space to hold elements in range
	auto data = alloc.allocate(e - b);
	// pair of first and one past last element
	return { data, std::uninitialized_copy(b,e, data) };
}

template <typename T>
void Vec<T>::free() {
	// 0 - or null poiter
	if (elements) {
		std::for_each(elements, first_free, 
			[this](T& p) { alloc.destroy(&p); });

		alloc.deallocate(elements, capacity());
	}
}

template <typename T>
void Vec<T>::reallocate(size_t n)
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

template <typename T> 
void Vec<T>::reserve(size_t n)
{
	// relocate if needs more space
	if (capacity() < n) {
		reallocate(n);
	}
}

template <typename T>
void Vec<T>::resize(size_t n, T val)
{
	if (n > size()) {
		for (size_t i = size(); i != n; ++i) {
			push_back(val);
		}
	}
}

template <typename T>
std::ostream& Vec<T>::print_info(std::ostream& os)
{
	os << "Elements number: " << size()
		<< " Capacity: " << capacity() << std::endl;

	os << "\t";
	for (auto p = begin(); p != end(); p++) {
		os << *p << " ";
	}
	return os << std::endl;
}

template <typename T>
bool operator==(const Vec<T>& lhs, const Vec<T>& rhs)
{
	return lhs.size() == rhs.size() ?
		std::equal(lhs.begin(), lhs.end(), rhs.begin())
		: false;
}

template <typename T>
bool operator!=(const Vec<T>& lhs, const Vec<T>& rhs)
{
	return !(lhs == rhs);
}

#endif // !VEC_H