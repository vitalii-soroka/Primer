#pragma once
#include <vector>
#include <memory>
#include <string>
#include <stdexcept>      // std::out_of_range

#ifndef BLOB_H
#define BLOB_H

template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);


template <typename T> class Blob {
	friend class BlobPtr<T>;
	friend bool operator==<T>
		(const Blob<T>&, const Blob<T>&);
public:

	//typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;

	// constructors
	Blob();
	Blob(std::initializer_list<T>);

	// number of elements in the Blob
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	// add and remove elements
	void push_back(const T& t) { data->push_back(t); }
	void push_back(T&& t) { data->push_back(std::move(t)); }
	void pop_back();

	//element access
	T& operator[](size_type);
	const T& operator[] (size_type) const;

	~Blob() {};

	// front and back
	T& front() { return do_front(); }
	T& back() { return do_back(); }
	const T& front() const { return data->front();  }
	const T& back() const { return data->back();  }


private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type, const std::string&) const;

	T& do_front() const;
	T& do_back() const;

};

// ****************************************** //
//                   BLOB
// ****************************************** //

template<typename T>
Blob<T>::Blob() : data(std::make_shared<std::vector<T>>()){}

template<typename T>
Blob<T>::Blob(std::initializer_list<T> il):
	data(std::make_shared<std::vector<T>>(il)) {}

template <typename T>
void Blob<T>::check(size_type i, const std::string& msg) const {
	if (i >= data->size()) {
		throw std::out_of_range(msg);
	}
}

template<typename T>
void Blob<T>::pop_back() {
	check(0, "pop_back on empty Blob");
	data->pop_back();
}

template<typename T>
T& Blob<T>::operator[](size_type i) {
	check(i, "subscript " + i + " out of range");
	return data->at(i);
}

template<typename T>
const T& Blob<T>::operator[](size_type i) const
{
	check(i, "subscript " + i + " out of range");
	return data->at(i);
}

template <typename T>
T& Blob<T>::do_front() const {
	check(0, "front on empty Blob");
	return data->front();
}

template<typename T>
T& Blob<T>::do_back() const
{
	check(0, "back on empty Blob");
	return data->back();
}

// ****************************************** //
//                 GENERAL
// ****************************************** //

template<typename T>
bool operator==(const Blob<T>& lhs, const Blob<T>& rhs){
	return lhs.size() == rhs.size() ?
		std::equal(lhs.data->begin(), lhs.data->end(),
			rhs.data->begin()) : false;
}

#endif // !BLOB_H