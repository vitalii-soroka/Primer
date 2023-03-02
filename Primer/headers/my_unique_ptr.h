#pragma once

#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR

#include <memory>
#include "DebugDelete.h"

template <
	typename T,
	class Deleter = DebugDelete>
class My_Unique_ptr {
public:
	// constructors
	My_Unique_ptr() : pointer(nullptr), deleter() {}
	//
	My_Unique_ptr(T* item, Deleter&& d = DebugDelete()) 
		: pointer(item), deleter(std::move(d)) {}
	
	~My_Unique_ptr() { deleter(pointer); }

	// operators
	T& operator*() const { return *pointer; }

	// functions
	T* get() const { return pointer; }
	T* release() { T* p = pointer; pointer = (T*)nullptr; return p; }
	void reset(T* p = (T*)nullptr) { delete pointer; pointer = p; }
	void swap(My_Unique_ptr& right);


private:
	T* pointer;
	Deleter deleter;
};





#endif // !MY_UNIQUE_PTR;