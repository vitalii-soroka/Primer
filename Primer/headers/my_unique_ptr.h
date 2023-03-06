#pragma once

#ifndef MY_UNIQUE_PTR
#define MY_UNIQUE_PTR

#include <memory>
#include "DebugDelete.h"

template <
	typename T,
	class Deleter = DebugDelete>
class unique_pointer {
public:
	// constructors
	unique_pointer() : pointer(nullptr), deleter() {}
	//
	unique_pointer(T* item, Deleter&& d = DebugDelete()) 
		: pointer(item), deleter(std::move(d)) {}
	unique_pointer(unique_pointer&& rhs) : 
		pointer(rhs.pointer) { rhs.pointer = nullptr; }

	~unique_pointer() { deleter(pointer); }

	// operators
	T& operator*() const { return *pointer; }
	unique_pointer& operator=(unique_pointer&&) noexcept;
	unique_pointer& operator=(nullptr_t np) noexcept;

	// functions
	T* get() const { return pointer; }
	T* release() { T* p = pointer; pointer = (T*)nullptr; return p; }
	void reset(T* p = (T*)nullptr) { delete pointer; pointer = p; }
	void swap(unique_pointer&);

	const Deleter get_deleter() const { return deleter;}

private:
	T* pointer;
	Deleter deleter;
};

template<typename T, class Deleter>
inline unique_pointer<T,Deleter>& 
unique_pointer<T, Deleter>::operator=(unique_pointer&& rhs) noexcept {
	if (this->pointer != rhs.pointer) {
		deleter(pointer);
		pointer = nullptr;
		this->swap(rhs);
		//::swap(*this, rhs);
	}
	return *this;

}

template<typename T, class Deleter>
inline void unique_pointer<T, Deleter>::swap(unique_pointer<T,Deleter>& right){
	using std::swap;
	swap(this->pointer, right.pointer);
	swap(this->deleter,right.deleter);
}


#endif // !MY_UNIQUE_PTR;