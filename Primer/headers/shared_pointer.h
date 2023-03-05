#pragma once

#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H
#include <iostream>
#include <functional>
#include "DebugDelete.h"

template<typename T>
class shared_pointer {
public:
	// constructors
	shared_pointer() :
		pointer(nullptr),
		users(new std::size_t(1)),
		deleter(DebugDelete()) { } 

	shared_pointer(T* point) : pointer(point), 
		users(new std::size_t(1)), deleter(DebugDelete()) {}

	// copy constructor
	shared_pointer(const shared_pointer<T>& other) :
		pointer(other.pointer),
		users(other.users),
		deleter(other.deleter) { ++* users; }

	// move constructor
	shared_pointer(shared_pointer<T>&& rhs) noexcept : pointer(rhs.pointer), users(rhs.users),
		deleter(std::move(deleter)) {
		rhs.pointer = nullptr;
		rhs.users = nullptr;
	}

	// copy assignment 
	shared_pointer& operator=(const shared_pointer<T>&);

	// move assignment
	shared_pointer& operator=(shared_pointer<T>&&) noexcept;
	
	// * operator 
	T& operator*() const { return *pointer; }

	// -> operator /*return &this->operator*();*/
	T* operator->() const { return &(*pointer); }
	operator bool() const { return pointer; }

	// functions
	T* get() const { return pointer; }
	std::size_t use_count() const { return* users; }
	bool unique() const { return *users == 1; }
	void swap(shared_pointer<T>&);

	~shared_pointer() { decrement_delete(); }

private:
	void decrement_delete();

	T* pointer;
	std::size_t* users;
	std::function<void(T*)> deleter;
};

template <typename T>
shared_pointer<T>& shared_pointer<T>::operator=(const shared_pointer<T>& rhs) {
	++* rhs.users;
	decrement_delete();
	pointer = rhs.pointer;
	users = rhs.users;
	deleter = rhs.deleter;
	return *this;
}

template<typename T>
inline shared_pointer<T>& shared_pointer<T>::operator=(shared_pointer<T>&& rhs) noexcept{
	std::cout << "move = operator called" << std::endl;
	swap(rhs);
	rhs.decrement_delete();
	return *this;
}

template <typename T>
void shared_pointer<T>::decrement_delete() {
	// only executed when object should be deleted
	if (pointer && --*users == 0) {
		std::cout << "no users left " << std::endl;
		delete users,
		deleter(pointer);
	} 

	// when () init, pointer == nullptr, but users = 1;
	else if (!pointer && users) {
		delete users;
	}

	// leaving pointers in right state
	users = nullptr;
	pointer = nullptr;
}

template<typename T>
inline void shared_pointer<T>::swap(shared_pointer<T>& rhs) {
	using std::swap;
	swap(this->pointer, rhs.pointer);
	swap(this->users, rhs.users);
	swap(this->deleter, rhs.deleter);

	std::cout << "shared_ptr swapped: " 
		<<  *rhs.pointer << " "  << *rhs.users << std::endl;
}


#endif // !SHARED_PTR_H
