#include <iostream>
#include "Sales_data.h"
#include <algorithm>
#include <vector>
#include "BlobPtr.h"
#include "Screen.h"

// Exercise 16.11 
template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
	List<elemType>();
	List<elemType>(const List<elemType>&);
	List<elemType>& operator=(const List<elemType>&);
	~List();
	void insert(ListItem<elemType>* ptr, elemType value);
	//					 ^^^^^^^^ - need to declare type of list Item
private:
	ListItem<elemType>* front, * end;
	//       ^^^^^^^^ - same

};


template <typename T>
int _compare(const T& v1, const T& v2);

template <unsigned N, unsigned M>
int _compare(const char(&p1)[N], const char(&p2)[M]);

template <typename It,typename V>
It myfind(It beg, It end, const V& v);

template <typename T, size_t _size>
void myprint(const T (&_array)[_size]);

template <typename T, unsigned _size>
T* mybegin(T(&_array)[_size]);

template <typename T, unsigned _size>
T* myend(T(&_array)[_size]);

template<typename T, unsigned _size>
constexpr unsigned mysize(T(&_array)[_size]);

void Exercise16_2() {
	std::cout << _compare(1, 0) << std::endl;

	// int compare(const char (&p1)[3], const char (&p2)[4]) -- size including '\0'
	std::cout << _compare("hi", "mom") << std::endl;
}
void Exercise16_3() {

	// error on compilation, Sales data has no < operator
	/*Sales_data data1, data2;
	std::cout << compare(data1, data2) << std::endl;*/
}
void Exercise16_4() {
	std::vector<int> ivec{ 1,2,3,4,5 };
	std::vector<std::string> svec{ "hi","cool","hello" };
	auto it = myfind(ivec.begin(), ivec.end(), 2);
	if (it != ivec.end()) std::cout << *it << std::endl;
	else std::cout << " element not found " << std::endl;


	auto it2 = myfind(svec.begin(), svec.end(), "cool");
	if (it2 != svec.end()) std::cout << *it2 << std::endl;
	else std::cout << " element not found " << std::endl;
}
void Exercise16_5() {
	int a[4] = { 0,4,5,155 };
	const char b[3] = { 'w','s','c' };
	
	myprint(a);
	myprint(b);
}
void Exercise16_6() {
	int a[4] = { 78,4,5,155 };
	std::cout << *mybegin(a) << std::endl;
	std::cout << *(myend(a) - 1) << std::endl;

	for (auto it = mybegin(a); it != myend(a); ++it ) {
		std::cout << *it << " " << std::endl;
	}
	std::cout << std::endl;
}
void Exercise16_7() {
	int a[3] = { 1,3,4};
	std::cout << "size: " << mysize(a) << std::endl;
}
void Exercise16_8() {
	// usually more classes define '!=' operator than '<' operator
	// So template class require less to work
	// for example some pointers or iterators
}
void Exercise16_12() {
	Blob<int> blob;
	Blob<int> blobV({ 1,2,3, });
	//blob.push_back(1);
	std::cout << blobV.back() << std::endl;
	Blob<int> blob1({1,2,3});
	Blob<int> blob2({1,2,3});

	BlobPtr<int> blobptr1(blob1,2);
	BlobPtr<int> blobptr2(blob1,0);
	std::cout << "BlobPtr's not equal: " << (blobptr1 != blobptr2) << std::endl;
	std::cout << "BlobPtr's smaller: " << (blobptr1 < blobptr2) << std::endl;
	std::cout << *(--blobptr1) << std::endl;
}
void Exercise16_15() {
	Screen<2,5> screen('c');
	std::cout << screen;
}
template<typename T> using _twin = std::pair<T, T>;
void TestTwins() {
	_twin<std::string> authors;
	_twin<int> win_lose;
}

int main() {
	
	Exercise16_15();
	Exercise16_12();
	Exercise16_7();
	Exercise16_6();
	Exercise16_5();
	Exercise16_4();
	Exercise16_3();
	Exercise16_2();

	return 0;
}

template<typename T>
int _compare(const T& v1, const T& v2)
{
	// problem when two pointer used and they are ot pointing to the same object
	//if (v1 < v2) return -1;
	//if (v2 < v1) return 1;
	// version of compare that will be correct even if used on pointers.
	if (std::less<T>()(v1, v2)) return -1;
	if (std::less<T>()(v2, v1)) return 1;
	return 0;
}

template<unsigned N, unsigned M>
int _compare (const char (&p1)[N], const char(&p2)[M]) {
	return std::strcmp(p1, p2);
}

template<typename It, typename V>
It myfind(It beg, It end, const V& v)
{
	while (beg != end) {
		if (*beg == v) {
			return beg;
		}
		++beg;
	}
	return end;
}

template <typename T, size_t _size>
void myprint(const T(&_array)[_size])
{
	for (auto i = 0; i != _size; ++i)
		std::cout << _array[i] << std::endl;
}

template<typename T, unsigned _size>
T* mybegin(T(&_array)[_size]){
	return _array;
}

template<typename T, unsigned _size>
T* myend(T(&t)[_size])
{
	return t + _size;
}

template<typename T, unsigned _size>
constexpr unsigned mysize(T(&_array)[_size])
{
	return _size;
}
