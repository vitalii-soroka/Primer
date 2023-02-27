#pragma once
#include <vector>
#include <iostream>
#include <memory>
class StrBlobPtr;
class ConstStrBlobPtr;
class StrBlobPtrPointer;

class StrBlob {
	friend class StrBlobPtr;
	friend class ConstStrBlobPtr;
	friend class StrBlobPtrPointer;
	friend bool operator==(const StrBlob&, const StrBlob&);
	friend bool operator!=(const StrBlob&, const StrBlob&);

	typedef std::vector<std::string>::size_type size_type;
public:
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	//
	StrBlob(const StrBlob& rhs) :
		data(std::make_shared<std::vector<std::string>>(*rhs.data)) {};

	StrBlob& operator=(const StrBlob&);
	std::string& operator[](std::size_t n);
	const std::string& operator[](std::size_t n) const;

	~StrBlob() {};
	//
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string& t) { data->push_back(t); }
	void push_back(std::string&&);
	void pop_back();
	std::string& front() { return do_front(); }
	std::string& back() { return do_back(); }
	const std::string& front() const { return do_front(); }
	const std::string& back() const { return do_back(); }

	StrBlobPtr begin();
	StrBlobPtr end();
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string& msg) const;
	std::string& do_front() const;
	std::string& do_back() const;
};
class StrBlobPtr {
	friend bool operator==(const StrBlobPtr&, const StrBlobPtr&);
	friend bool operator!=(const StrBlobPtr&, const StrBlobPtr&);
public:
	StrBlobPtr() :curr(0) { };
	StrBlobPtr(StrBlob& a, std::size_t sz = 0) :
		wptr(a.data), curr(sz) {};

	// operators
	std::string& operator*() const;
	std::string* operator->() const;
	StrBlobPtr& operator+=(const size_t);
	StrBlobPtr& operator-=(const size_t);
	StrBlobPtr& operator+(const size_t) const;
	StrBlobPtr& operator-(const size_t) const;
	StrBlobPtr& operator++();		// prefix operator
	StrBlobPtr& operator--();
	StrBlobPtr& operator++(int);	// postfix operator
	StrBlobPtr& operator--(int);	
	std::string& operator[](std::size_t n);
	const std::string& operator[](std::size_t n) const;

	std::string& deref() const;
	StrBlobPtr& incr();

private:
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t, const std::string&) const;

	// store a weak_ptr, that means vector can be destroyed.
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr; // curr pos of aray.

};  
class ConstStrBlobPtr {
public:
	ConstStrBlobPtr() : curr(0) {}
	ConstStrBlobPtr(const StrBlob& s, size_t sz = 0) : wptr(s.data), curr(sz) {};
	 
		
	const std::string& operator*() const;
	const std::string* operator->() const;

private:
	std::shared_ptr<std::vector<std::string>>
		check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr; 
};
class StrBlobPtrPointer {
public:
	StrBlobPtrPointer() : pointer(nullptr) {};
	StrBlobPtrPointer(StrBlobPtr* ptr) : pointer(ptr) {};

	StrBlobPtr& operator*() const { return *pointer; }
	StrBlobPtr* operator->() const { return pointer; }

private:
	StrBlobPtr* pointer;
};