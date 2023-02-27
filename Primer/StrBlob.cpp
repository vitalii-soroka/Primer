#include "StrBlob.h"

// 
bool operator==(const StrBlob& lhs, const StrBlob& rhs) {
	return lhs.size() == rhs.size() ?
		 std::equal(lhs.data->begin(), lhs.data->end(),
					rhs.data->begin()) : false;
}
bool operator!=(const StrBlob& lhs, const StrBlob& rhs) {
	return !(lhs == rhs);
}

//copy-assign
StrBlob& StrBlob::operator=(const StrBlob& rhs)
{ 
	auto newp = std::make_shared
		<std::vector<std::string>>(*rhs.data);
	data.reset();
	data = newp;
	return *this;
}
std::string& StrBlob::operator[](std::size_t n)
{
	check(n, "out_of_range");
	return data->at(n);
}
const std::string& StrBlob::operator[](std::size_t n) const
{
	check(n, "out_of_range");
	return data->at(n);
}
//constructors
StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){};
StrBlob::StrBlob(std::initializer_list<std::string> il) :
	data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_type i, const std::string& msg) const {
	if (i >= data->size())
		throw std::out_of_range(msg);
};
void StrBlob::push_back(std::string&& s) 
{
	check(0, "pop_back on empty StrBlob");
	data->push_back(std::move(s));
}
void StrBlob::pop_back() {
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}
std::string& StrBlob::do_front() const {
	check(0, "front on empty StrBlob");
	return data->front();
}
std::string& StrBlob::do_back() const {
	check(0, "back on empty StrBlob");
	return data->back();
}
StrBlobPtr StrBlob::begin() { return  StrBlobPtr(*this); };
StrBlobPtr StrBlob::end() { auto ret = StrBlobPtr(*this, data->size()); return ret; };

bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
	// return true; // lhs.wptr == rhs.wptr;
	return lhs.curr == rhs.curr;
}
bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
	// return false; // 
	return !(lhs == rhs);
}
std::shared_ptr<std::vector<std::string>>
StrBlobPtr::check(std::size_t i, const std::string& msg) const {
	auto ret = wptr.lock();
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}
std::string& StrBlobPtr::operator*() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}
std::string* StrBlobPtr::operator->() const{
	// .
	//delegate the real work to the dereference operator
	return &this->operator*();
}
StrBlobPtr& StrBlobPtr::operator+=(const size_t n){
	check(curr + n, "increment past end of StrBlobPtr");
	curr += n;
	return *this;
}
StrBlobPtr& StrBlobPtr::operator-=(const size_t n){
	check(curr - n, "decrement past begin of StrBlobPtr");
	curr -= n;
	return *this;
}
StrBlobPtr& StrBlobPtr::operator+(const size_t n) const{
	StrBlobPtr ret = *this;
	ret += n;				// auto check for error
	return ret;				// return new saved data
}
StrBlobPtr& StrBlobPtr::operator-(const size_t n) const
{
	StrBlobPtr ret = *this;
	ret += n;
	return ret;
}

StrBlobPtr& StrBlobPtr::operator++()
{
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}
StrBlobPtr& StrBlobPtr::operator--()
{
	// id curr zero - yields invalid subscript, large int number
	check(--curr, "decrement past begin of StrBlobPtr");
	return *this;
}
StrBlobPtr& StrBlobPtr::operator++(int)
{
	StrBlobPtr ret = *this;
	++* this;
	return ret; // return the saved state
}
StrBlobPtr& StrBlobPtr::operator--(int)
{
	StrBlobPtr ret = *this;
	--* this;
	return ret;
}
std::string& StrBlobPtr::operator[](std::size_t n)
{
	auto p = check(n, "out_of_range");
	return (*p)[n];
}
const std::string& StrBlobPtr::operator[](std::size_t n) const
{
	auto p = check(n, "out_of_range");
	return (*p)[n];
}
std::string& StrBlobPtr::deref() const {
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}
StrBlobPtr& StrBlobPtr::incr() {
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}



const std::string& ConstStrBlobPtr::operator*() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

const std::string* ConstStrBlobPtr::operator->() const
{
	return &this->operator*();
}

std::shared_ptr<std::vector<std::string>> 
ConstStrBlobPtr::check(std::size_t i , const std::string& msg) const
{
	auto ret = wptr.lock();
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}
