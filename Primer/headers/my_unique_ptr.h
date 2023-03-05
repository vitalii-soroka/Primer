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
	My_Unique_ptr(My_Unique_ptr&& rhs) : 
		pointer(rhs.pointer) { rhs.pointer = nullptr; }


	~My_Unique_ptr() { deleter(pointer); }

	// operators
	T& operator*() const { return *pointer; }
	My_Unique_ptr& operator=(My_Unique_ptr&&) noexcept;
	My_Unique_ptr& operator=(nullptr_t np) noexcept;

	// functions
	T* get() const { return pointer; }
	T* release() { T* p = pointer; pointer = (T*)nullptr; return p; }
	void reset(T* p = (T*)nullptr) { delete pointer; pointer = p; }
	void swap(My_Unique_ptr&);

	const Deleter get_deleter() const {
		return deleter;
	}


private:
	T* pointer;
	Deleter deleter;
};

template<typename T, class Deleter>
inline My_Unique_ptr<T,Deleter>& 
My_Unique_ptr<T, Deleter>::operator=(My_Unique_ptr&& rhs) noexcept {
	if (this->pointer != rhs.pointer) {
		deleter(pointer);
		pointer = nullptr;
		this->swap(rhs);
		//::swap(*this, rhs);
	}
	return *this;

}

template<typename T, class Deleter>
inline void My_Unique_ptr<T, Deleter>::swap(My_Unique_ptr<T,Deleter>& right){
	using std::swap;
	swap(this->pointer, right.pointer);
	swap(this->deleter,right.deleter);
}


#endif // !MY_UNIQUE_PTR;