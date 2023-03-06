#pragma once
#ifndef BLOBPTR_H
#define BLOBPTR_H

#include "Blob.h"

template <typename T> class BlobPtr;

template<typename T>
bool operator==(const BlobPtr<T>&, const BlobPtr<T>&);

template<typename T>
bool operator !=(const BlobPtr<T>&, const BlobPtr<T>&);

template<typename T>
bool operator < (const BlobPtr<T>&, const BlobPtr<T>&);


template <typename T> class BlobPtr {
	friend bool operator== <T>(const BlobPtr<T>&, const BlobPtr<T>&);
	friend bool operator!= <T>(const BlobPtr<T>&, const BlobPtr<T>&);
	friend bool operator < <T>(const BlobPtr<T>&, const BlobPtr<T>&);

public:
	BlobPtr() : curr(0) {}
	// temp data while Blob uses own shared_pointer
	//BlobPtr(Blob<T>& a, size_t sz = 0) : wptr(/*a.data*/), curr(sz) { }

	T& operator*() const {
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}

	// prefix
	BlobPtr<T>& operator++();
	BlobPtr<T>& operator--();

	// when in scope, compiler treats references to the template itself
	BlobPtr<T>& operator++(int);			// postfix
	BlobPtr& operator--(int);				// equal to BlobPtr<T>& 

private:
	std::shared_ptr<std::vector<T>>
		check(std::size_t, const std::string&) const;
	// weak pointer, means the underlying vector might be destroyed 
	std::weak_ptr<std::vector<T>> wptr;
	// position in array
	std::size_t curr;
};

template<typename T>
std::shared_ptr<std::vector<T>> 
BlobPtr<T>::check(std::size_t i, const std::string& msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}

/*******************************************
                  OPERATORS					  
*******************************************/

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {

	// if curr already points past the end of the container, can't increment it
	check(curr, "increment past end of StrBlob");
	++curr;
	return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
	--curr;
	check(curr, "decrement past begin of BlobPtr");
	return *this;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++(int) {
	// no check; the call to prefix will do the check;
	BlobPtr ret = *this;  // save the current value
	++* this;
	return ret;
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--(int) {
	BlobPtr ret = *this;
	--* this;
	return ret;
}

template<typename T>
bool operator==(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
	if (lhs.wptr.lock() != rhs.wptr.lock()) {
		throw std::runtime_error("BlobPtrs are pointing to different objects");
	}
	return lhs.curr == rhs.curr;

}

template<typename T>
bool operator!=(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs) {
	return !(lhs == rhs);
}

template<typename T>
bool operator <(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs)
{
	if (lhs.wptr.lock() != rhs.wptr.lock()) {
		throw std::runtime_error("BlobPtrs are pointing to different objects");
	}

	return lhs.curr < rhs.curr;	
}

#endif // !BLOBPTR_H