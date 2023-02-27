#pragma once
#include <vector>
#include <memory>
#include <string>

template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T> bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob {
	friend class BlobPtr<T>;
	friend bool operator==<T> (const Blob<T>&, const Blob<T>&);
public:
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;
	// constructors
	Blob();
	Blob(std::initializer_list<T> il);
	// number of elements in the Blob
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	// add and remove elements
	void push_back(const T& t) { data->push_back(t); }
	void push_back(T&& t) { data->push_back(t); }
	void pop_back();
	// element access
	T& back();
	T& operator[](size_type);
private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type, const std::string&) const;
};

template <typename T> class BlobPtr {
public:
	BlobPtr() : curr(0) {}
	BlobPtr(Blob<T> &a, size_t sz = 0) : wptr(a.data), curr(sz) { }
	T& operator*() const {
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	// when in scope, compiler treats references to the template itself
	BlobPtr<T>& operator++(int);			// prefix
	BlobPtr& operator--();					// equal to BlobPtr<T>& 

private:
	std::shared_ptr<std::vector<T>>
		check(std::size_t, const std::string&) const;
	// weak pointer, means the underlying vector might be destroyed 
	std::weak_ptr<std::vector<T>> wptr;
	// position in array
	std::size_t curr;
};

template<typename T>
inline bool operator==(const Blob<T>& lhs, const Blob<T>& rhs)
{
	return lhs.data == rhs.data;
}
