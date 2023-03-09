#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <algorithm>

class StrVec {
	friend bool operator==(const StrVec&, const StrVec&);
	friend bool operator!=(const StrVec&, const StrVec&);
public:
	StrVec(): 
		elements(nullptr), 
		first_free(nullptr),
		cap(nullptr){}
	StrVec(std::initializer_list<std::string>);
	StrVec(const StrVec&);
	StrVec(StrVec&&) noexcept;

	StrVec& operator=(StrVec&& rhs) noexcept;
	StrVec& operator=(const StrVec&);
	StrVec& operator=(std::initializer_list<std::string>);
	// StrVec& operator=(const StrVec&)& or && // this can be l/rvalue;
	// const & // ok
	std::string& operator[](std::size_t n) { return elements[n]; }
	const std::string& operator[](std::size_t n) const { return elements[n]; }

	~StrVec() { free(); }

	// Exercise 16.58
	template <class... Args> void emplace_back(Args&&...);

	void push_back(const std::string&); // copy element
	void push_back(std::string&&);		// move element

	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	void reserve(size_t n);
	void resize(size_t n, std::string val = std::string());
	std::string* begin() const { return elements;}
	std::string* end() const { return first_free; }

	std::ostream& print_info(std::ostream&);

private:
	std::allocator<std::string> alloc;
	
	std::pair<std::string*, std::string*> alloc_n_copy
	(const std::string*, const std::string*);
	
	void free();
	void reallocate(size_t n = 2);
	void chk_n_alloc() { if (size() == capacity()) reallocate();}

	std::string* elements;
	std::string* first_free;
	std::string* cap;
};

template <class... Args>
void StrVec::emplace_back(Args&&... args) {
	chk_n_alloc();
	alloc.construct(first_free++,
		std::forward<Args>(args)...);
}