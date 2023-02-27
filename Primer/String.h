#pragma once
#include <memory>
#include <iostream>

class String {
	friend std::ostream& operator<<(std::ostream&, const String&);
	friend bool operator==(const String&, const String&);
	friend bool operator!=(const String&, const String&);
public:
	String():
		elements(nullptr),
		first_free(nullptr),
		cap(nullptr) {} 

	String(const char*);
	String(const String&);
	String(String&&) noexcept;
	String& operator=(String&&) noexcept;
	String& operator=(const String&);
	char& operator[](std::size_t n) { return elements[n]; }
	const char& operator[](std::size_t n) const { return elements[n]; }
	~String() { free(); }

	size_t capacity() const { return cap - elements; }
	size_t size() const { return first_free - elements;  }
	char* begin() const { return elements; }
	char* end() const { return cap; }
	void print() const;

private:
	std::allocator<char> alloc;

	std::pair<char*, char*>
		alloc_n_copy(const char*, const char*);
	void free();

	char* elements;
	char* first_free;
	char* cap;
};