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

	shared_pointer(T* ptr, std::function<void(T*)> del = DebugDelete()) 
		: pointer(ptr),
		users(new std::size_t(1)),
		deleter(del) {}

	// copy constructor
	shared_pointer(const shared_pointer<T>& other) :
		pointer(other.pointer),
		users(other.users),
		deleter(other.deleter) { ++* users; }

	explicit shared_pointer(std::shared_ptr<T>&&,
		std::function<void(T*)> d = DebugDelete());

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

	// -> operator /* return &this->operator*();*/
	T* operator->() const { return &(*pointer); }
	operator bool() const { return pointer; }

	// functions
	T* get() const { return pointer; }
	std::size_t use_count() const { return* users; }
	bool unique() const { return *users == 1; }
	void swap(shared_pointer<T>&);
	void reset() noexcept { decrement_delete(); }
	void reset(T* ptr, std::function<void(T*)> del = DebugDelete());

	~shared_pointer() { decrement_delete(); }

private:
	void decrement_delete();

	T* pointer;
	std::size_t* users;
	std::function<void(T*)> deleter;
};

template<typename T>
inline shared_pointer<T>::shared_pointer(std::shared_ptr<T>&& sp, std::function<void(T*)> d)
{
	if (sp.unique())
		*this = shared_pointer(new T(*sp));
	else
		throw std::runtime_error
		("only unique/rvalue reference can transfer ownership\n");
}

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
}

template<typename T>
inline void shared_pointer<T>::reset(T* ptr, std::function<void(T*)> del)
{
	decrement_delete();
	pointer = ptr;
	users = new std::size_t(1);
	deleter = del;
}


#endif // !SHARED_PTR_H
