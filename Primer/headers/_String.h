#pragma once
#include <memory>
#include <iostream>

class _String {
	friend std::ostream& operator<<(std::ostream&, const _String&);
	friend bool operator==(const _String&, const _String&);
	friend bool operator!=(const _String&, const _String&);
public:
	_String():
		elements(nullptr),
		first_free(nullptr),
		cap(nullptr) {} 

	_String(const char*);
	_String(const _String&);
	_String(_String&&) noexcept;
	_String& operator=(_String&&) noexcept;
	_String& operator=(const _String&);
	char& operator[](std::size_t n) { return elements[n]; }
	const char& operator[](std::size_t n) const { return elements[n]; }
	~_String() { free(); }

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