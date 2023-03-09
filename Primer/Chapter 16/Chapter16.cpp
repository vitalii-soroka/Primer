#include <iostream>
#include <fstream>
#include <algorithm>
#include <memory>
#include <vector>
#include <type_traits> // remove_pointer, remove_reference
#include <sstream> // string stream
#include <unordered_set>

#include "BlobPtr.h"
#include "Screen.h"
#include "Vec.h"
#include "StrVec.h"
#include "Sales_data.h"
#include "DebugDelete.h"
#include "MyTextQuery.h"
#include "my_unique_ptr.h"
#include "shared_pointer.h"

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

	/*BlobPtr<int> blobptr1(blob1,2);
	BlobPtr<int> blobptr2(blob1,0);
	std::cout << "BlobPtr's not equal: " << (blobptr1 != blobptr2) << std::endl;
	std::cout << "BlobPtr's smaller: " << (blobptr1 < blobptr2) << std::endl;
	std::cout << *(--blobptr1) << std::endl;*/
}
void Exercise16_14() {
	Screen<2,5> screen('c');
	screen.move(1, 4);
	
}
void Exercise16_15() {
	Screen<8,8> screen;
	std::cin >> screen;
	std::cout << screen << std::endl;
	
}
void Exercise16_16() {
	Vec<std::string> svec({ "1", "2", "3", "4" });
	svec.reserve(30);
	svec.print_info(std::cout);
}
void Exercise16_18() {
	
}

template<typename T> using _twin = std::pair<T, T>;
void TestTwins() {
	_twin<std::string> authors;
	_twin<int> win_lose;
}

//template <typename T, typename U, typename V> void f1(T, U, V);
// illegal U needs name ^^^^^  

//template<typename T> T f2( /*int*/&T);
// T already a template type ^^^ 

// /*inline*/ template<typename T> inline T foo(T, unsigned int*);
// ^^^ illegal, inline   after   ^^^^^  template 

//template <typename T> void f4(T, T);
// return type		 ^^^^^^

//typedef char Ctype;
//template <typename Ctype> Ctype f5(Ctype a);
// typename hides typedef 

template <typename T> 
void ex16_19(T& container) {
	for (typename T::size_type i = 0; i < container.size(); ++i) {
		std::cout << container[i] << " ";
	}
	std::cout << std::endl;
}

void Exercise16_19() {
	std::vector<int> vec{ 1,2,7,9,0,34,7,8};
	ex16_19(vec);
}

template <typename T>
void ex16_20(T& container) {
	for (typename T::iterator it = container.begin(); it != container.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}
void Exercise16_20() {
	std::vector<int> vec{ 1,2,7,9,0,34,7,8 };
	ex16_20(vec);
}
void Exercise16_22() {
	std::ifstream ifs("data/text.txt");
	MyTextQuery text(ifs);
	text.query("hello"); // query constructs shared_ptr with my deleter
	// deleter deletes shared ptr in the end of this scope.
}
void Exercise16_24() {
	std::vector<int> ivec{ 1,2,3,4,5,6,7 };
	Blob<int> blob(ivec.begin(), ivec.end());
	std::cout << "blob size: " << blob.size() << std::endl;
}
void unqTest() {
	std::unique_ptr<int, DebugDelete> p(new int, DebugDelete());
	std::unique_ptr<std::string, DebugDelete> sp(new std::string, DebugDelete());
}

void Exercise16_28() {

	// std unique ptr
	int* p = new int(55);
	std::unique_ptr<int> up(p/*new int(3)*/);
	up.reset(new int(4));
	
	std::cout << (*up.get()) << std::endl;
	std::cout << (*p) << std::endl;

	// my unique ptr
	int* p1 = new int(44);
	unique_pointer<int,DebugDelete> idel(p1, DebugDelete());
	unique_pointer<int,DebugDelete> idel2(new int(2));

	idel.reset(new int(10));
	std::cout << "get pointer 1: " << (*idel.get()) << std::endl;
	std::cout << "int pointer: " << (*p1) << std::endl;
	std::cout << "released pointer 2: " << *(idel2.release()) << std::endl;
	
	idel.reset(new int(10));
	idel2.reset(new int(50));
	idel.swap(idel2);
	std::cout << *idel.get() << std::endl;
	std::cout << *idel2 << std::endl;


}
void Exercise16_28_shared() {

	std::shared_ptr<int> ss(new int(4));
	shared_pointer<int> msp1(new int(1));
	shared_pointer<int> msp3(new int(3));
	// ss.reset(new int(4));
	msp1 = msp1;
	msp1 = std::move(msp3);
	std::cout << *msp1 << " " << msp1.use_count() << std::endl;
	shared_pointer<int> msp4;
	if (msp1) std::cout << " true " << std::endl;
	std::cout << std::endl;
	
	// -> operator
	std::vector<int> v{ 1,2,3,4 };
	shared_pointer<std::vector<int>> shvec(new std::vector<int>());
	shvec->push_back(2);
	std::cout << shvec->front() << std::endl;

	// reset pointer
	std::cout << std::endl;
	shared_pointer<int> spointer(new int(88));
	spointer.reset(new int(99));
	std::cout << "after reset: " << *spointer << std::endl << std::endl;
}
void Exercise16_29_30() {

	// Blob uses my shared_pointer
	Blob<std::string> blob({"hey","lol"});
	std::cout << blob[0] << std::endl;

}

/* -------------------------Template conversions-----------------------------
	const conversions and array or function to pointer are the only automatic
	conversions for arguments to parameters with template types.
	Normal conversions are applied to arguments whose types is not a template.
----------------------------------------------------------------------------*/

template <typename T> void fobj(T, T) { }; // copy arguments
template <typename T> void fref(const T&, const T&) {}; // reference arguments

void templateTest() {
	std::string s1("a value");
	const std::string s2("b value");
	fobj(s1, s2); // const is ignored for copy
	fref(s1, s2); // converts to const

	int a[10], b[42], c[10];
	fobj(a, b); // ok calls f(int*,int*)
	//fref(a, b); // takes by references, error types don't match int[10],int[42]
	fref(a, c); // ok types match int[10],int[10];

}

void Exercise16_34() {
	// fref("hi", "world"); // error: const char[3], const char[6]
	fref("bey", "dad"); // ok type const char(&)[4]
}

template <typename T> void calc(T, int) {};
template <typename T> void fcn(T, T) {};
void Exercise16_35() {
	double d = 0.5; float f = 1; char c = 'c';
	calc(c, 'c');  // ok: T is char, 'c' converted to int - not template
	calc(d, (int) f);	   // ok: T is double, float converted to int -
	fcn(c,'c'); // ok: T is char, 'c' is also char
	//fcn(d,f);   // error: T is double and float can't convert
}

template <typename T> void f1(T, T) {};
template <typename T1, typename T2> void f2(T1, T2) {};
void Exercise16_36() {
	int i = 0, j = 42, *p1 = &i, *p2 = &j;
	const int* cp1 = &i, * cp2 = &j;
	f1(p1, p2);  // ok, type is int*
	f2(p1, p2);  // ok types are int*
	f1(cp1,cp2); // ok, type is const int*
	f2(cp1, cp2);// ok, types is const int*
	// f1(p1,cp1);// error: T1 int* and const int*
	f2(p1, cp1); // ok types are T1 int* and T2 const int*
}
void Exercise16_37() {
	// std::max(5,7.8) // error: T not match 
	// std::max<int>(2.3, 3);
}
void Exercise16_38() {
	// internet says:
	// without specified type given, make_shared has no possibility to
	// to determine how big the size it should allocate.
}

template <typename T>
int compare(const T& v1, const T& v2) {
	if (v1 < v2) return -1; if (v2 < v1) return 1; return 0;
}

void Exercise16_39() {
	// compare("sss", "aaaa"); error: const char[4], const char[5]
	compare<std::string>("sss", "aaaa"); // ok: explicit determined as string
}

/* ----------------------------- Trailing return -----------------------------
Trailing return lets declare the return type after the parameter list is seen
----------------------------------------------------------------------------*/
template <typename It>
auto fcn_auto(It beg, It end) -> decltype(*beg) {
	// process the range
	return *beg; // return a reference to an element from the range
}
// using type_traits
template <typename It>
auto fcn_rmv_ref(It beg, It end) ->
typename std::remove_reference<decltype(*beg)>::type {
	// process range
	return *beg; // return a copy of an element from the range
}
void Exercise_Trailing_return() {
	std::vector<int> ivec{ 1,2,3,4 };
	// can assign int& and int
	int& rch = fcn_auto(ivec.begin(), ivec.end());
	rch = 25; 
	std::cout << *ivec.begin() << std::endl;

	// can't return and assign reference
	int ch = fcn_rmv_ref(ivec.begin(), ivec.end());


}

// 199 value doesn't matter, only type that yields ( <type> + int ) 
template <typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 199) {
	return *beg;
}
void Exercise16_40() {
	// function is legal, but only types that supports + operator,
	// return type depends on result of sum operations
	std::string s("string");
	auto ref = fcn3(s.begin(), s.end());
	// example 
	std::cout << "fcn3(): " << ref << " , " << (*s.begin() + 0) << std::endl;
}

template <typename A, typename B>
auto sum_large(A a, B b) -> decltype(a + b){
	return a + b;
}
void Exercise16_41() {
	auto sum = sum_large(123456789123456789,1);
}

/* --------------------------- Function pointers ----------------------------
When the address of a function-template instantiation is taken, the context
must be such that it allows a unique type or value to be determined fro each
template parameter.
----------------------------------------------------------------------------*/

// overload pfunc
int (*pf1)(const  int&, const int&) = _compare;
void pfunc(int(*)(const int&, const int&)) {};
void pfunc(int(*)(const std::string&, const std::string&)) {};
void funcPointers() {
	// pfunc(_compare); //error
	pfunc(_compare<std::string>); // ok: explicity specify which pfunc;
}

/* ------------------------- Reference collapsing ----------------------------
Reference collapsing applies only when a reference to a reference is created
indirectly, such as in type alias or a template parameters.
-----
An argument of any type can be passed to a function parameter that is an 
rvalue reference to a template parameter type (i.e., T&&). When an lvalue is 
passed to such a parameter, the function parameter is instantiated as an
ordinary, lvalue reference (T&).
----------------------------------------------------------------------------*/
template <typename T> void f3(T&& val) {
	T t = val; // copy or binding a reference?
	//t = fcn(t); // does the assignment change only t or val and t?
	if(val == t) { /* */ } // always true if T is a reference type
};
// it's better to overload
template <typename T> void _fref(T&&) {};		// binds to nonconst rvalues
template <typename T> void _fref(const T&) {};  // lvalues and const rvalues
void Exercise16_42() {
	int i = 3; int& ri = i; const int ci = 4;
	f3(i);		// int& illustration code : void f3<int&>(int& &&); 
	f3(ri);		// int&
	f3(ci);		// const int&
	f3(4);		// int&& - rvalue
	f3(i * ci); // int && - return rvalue
}
void Exercise16_43() {
	int i = 3; const int ci = 4;
	f3(i = ci);	// int& - return lvalue after assign 
}
template <typename T> void g16_44(T) {};
template <typename T> void gc16_44(const T&) {};
void Exercise16_44() {
	int i = 3; const int ci = 4;
	g16_44(i);		// int, copy value 
	g16_44(ci);		// int, copy value 
	g16_44(i * ci); // int, copy rvalue

	gc16_44(i);		// int, takes const lvalue reference
	gc16_44(ci);	// int, takes const lvalue reference
	gc16_44(i * ci);// int, takes const rvalue reference
	//        ^^ if not const in declaration, call will be error
}
template <typename T> void g16_45(T&& val) { 
	std::vector<std::remove_reference<T>> v;
	// remove reference ^^^^^^^^^^^^^ when int& passed
}
void Exercise16_45() {
	int a = 2;
	g16_45(42); // T - is int, vector of ints
	g16_45(a);  // T - is int&, vector<int&> is an error :( 
	//ok : if we remove reference in function.

	
} 

/* ----------------------------- ST::MOVE ------------------------------------
A function parameter that is an rvalue reference to a template type parameter
(i.e., T&&) preserves the constNess and lvalue/rvalue property of its 
corresponding argument.
--
When used with a function parameter that is an rvalue reference to template
type parameter (T&&), forward preserves all the details about an argument type.
--
As with std::move, it's a good idea not to provide a using declaration for 
std::forward. 
----------------------------------------------------------------------------*/
template <typename T>
typename std::remove_reference<T>::type&& my_move(T&& t) {
	return 
		static_cast<typename std::remove_reference<T>::type&&>(t);
}
void my_move_test() {
	std::string s1(std::string("hi!")), s2;
	//s2 = std::move("bye!"); // ok: moving from an rvalue
	// ^^ call: string && my_move(string &&t);
	s2 = std::move(s1);					 // ok: but after assignment s1 has indeterminate
	// ^^ call: string && my_move(string &t);
	int i = 10;
	// flip(_f, i, 42); hmm
}
// Exercise 16 47
template<typename F, typename T1, typename T2>
void my_flip(F f, T1&& t1, T2&& t2)
{
	f(std::forward<T2>(t2), std::forward<T1>(t1));
}
void my_f1(int& t1, int& t2)
{
	std::cout << t1 << " " << t2 << std::endl;
}
void my_f2(int&& t1, int&& t2)
{
	std::cout << t1 << " " << t2 << std::endl;
}
void my_Flip_Test() {
	int i = 9, j = 7;
	my_flip(my_f1, i, j); 
	std::cout << "Flip lvalue: " << i << " " << j << std::endl;
}
/* ------------------------- Overloaded templates --------------------------
When there are several overloaded templates that provide an equally 
good match for a call, the most specialized version is preferred.
--
when a non template function provides an equally good match for a call 
as a function template, the non template version is preferred.
--------------------------------------------------------------------------*/
// Ex 16.48
// prints (T) object
template <typename T> std::string debug_rep(const T& t) {
	std::ostringstream ret;
	ret << t;		  // T's output operator to print t
	return ret.str(); // copy of string to which ret is bound
}
// prints (T*) pointers
template <typename T> std::string debug_rep(T* p) {
	std::ostringstream ret;
	ret << "pointer: " << p;		 // prints the pointer's own value 
	if (p)
		ret << " " << debug_rep(*p); // prints the value to which p points
	else
		ret << " null pointer";		 // print if(p) is false = null pointer
	return ret.str();				 // copy of string to which ret is bound
}
// prints non template string
std::string debug_rep(const std::string& s) {
	return '"' + s + '"';
}
// prints C style strings
template<> // ex 16.65
std::string debug_rep(char* p) {
	return debug_rep(std::string(p));
}
template<> // ex 16.65
std::string debug_rep(const char* p) {
	return debug_rep(std::string(p));
}
void Debug_rep_Test() {
	std::string s("hi");
	int* sNull = nullptr;
	const char* pchar("hello\0");
	std::cout << debug_rep(s) << std::endl;
	std::cout << debug_rep(&s) << std::endl;
	std::cout << debug_rep(sNull) << std::endl;
	std::cout << debug_rep(pchar) << std::endl;
}
//
template <typename T> void f(T) { std::cout << "f(T) called" << std::endl; }
template <typename T> void f(const T*) { std::cout << "f(const T*) called" << std::endl; }
template <typename T> void g(T) { std::cout << "g(T) called" << std::endl; }
template <typename T> void g(T*) { std::cout << "g(T*) called" << std::endl; }
void Exercise16_50() {
	int i = 42, * p = &i;
	const int ci = 0, * p2 = &ci;
	g(42); // <int> g(int)
	g(p);  // <int> g(int*)
	g(ci); // <int> g(int)
	g(p2); // <int> g(int*)
	//
	f(42); // <int> f(int)
	f(p);  // <int*> f(int*)
	f(ci); // <int> f(int)
	f(p2);  // <int> f(const int*)
}

/* --------------------------- Variadic Templates ---------------------------

----------------------------------------------------------------------------*/
template <typename T, typename... Args>
void fooArgs(const T& t, const Args& ...rest) {
	std::cout << "Number of type parameters: " << sizeof...(Args) << std::endl;
	std::cout << "Number of function parameters: " << sizeof...(rest) << std::endl;
}
void Exercise16_51() {
	int i = 0, i2 = 1; double d = 3.14; std::string s = "how now brown cow";
	fooArgs(i, s, 42, d); //  3 , 3
	fooArgs(s, 42, "hi"); //  2 , 2
	fooArgs(d, s);		  //  1 , 1 
	fooArgs("hi");        //  0 , 0
}

// function to end the recursion and print the last elements
template <typename T>
std::ostream& printVariadic(std::ostream &os, const T &t) {
	return os << t;
}
// version of print will be called for all but the last element in pack
template <typename T, typename... Args>
std::ostream& printVariadic(std::ostream& os, const T& t, const Args&... rest) {
	os << t << ", ";				   // print the first element
	return printVariadic(os, rest...); // recursive call - print other arguments
	
}

void Exercise16_53() {
	int i = 0, i2 = 1; double d = 3.14; std::string s = "how now brown cow";
	printVariadic(std::cout, i) << std::endl;
	printVariadic(std::cout, i,s,42) << std::endl;
	printVariadic(std::cout, i,d,s,i2,101) << std::endl;
	
}
void Exercise16_54() {
	Blob<int> blob({ 1,2,3 });
	//printVariadic(std::cout,1,blob) << std::endl; 
	// << no operator found     ^^^^ 
}
void Exercise16_55() {
	// no matching overloaded function found when in rest no args,
	// because other print will not be visible
}
/* ----------------------------- Pack Expansion -----------------------------
The pattern in an expansion applies separately to each element in pack.
----------------------------------------------------------------------------*/
template <typename... Args>
std::ostream& errorMsg(std::ostream& os, const Args&... rest) {
	// print(os, rep(a1),rep(a2) ... rep(an) vv
	return printVariadic(os, debug_rep(rest)...);

	// passes the pack to debug_rep; print(os,debug_rep(a1,a2,...an))
	// print(os, debug_rep(rest...); // error: no match
}
void Exercise16_56() {
	int* i = new int(32);
	errorMsg(std::cout, 1, i, "hello") << std::endl;

}
/* ----------------------- Forwarding Parameter Pack -------------------------
Added emplace_back to StrVec.
----------------------------------------------------------------------------*/

void Exercise16_59() {
	std::string s("Hello");
	StrVec svec;
	// calls s - lvalue emplace_back<string&>(string &) and passes to construct string& (not &&)
	// would call string class type's copy constructor to copy construct a new string 
	// object allocated in dynamic memory
	svec.emplace_back(s);
	std::cout << s << std::endl;
	s = "new Hello";
	std::cout << *svec.begin() << std::endl;
}
void Exercise16_60() {
	// function make_shared behaves almost like emplace_back illustrated in section 16.4.3;
	// make_shared should be a variadic template function that forwards all arguments 
	// to underlying constructors that allocate and initializes an object in dynamic memory 
	// and build a shared_ptr by wrapping the raw pointer.
}
// Exercise 16.61
template <typename _Ty, class..._Types>
std::shared_ptr<_Ty> my_make_shared(_Types&&... args) {
	return std::shared_ptr<_Ty>(new _Ty(std::forward<_Types>(args)...));
}
void Exercise16_61() {
	auto n = my_make_shared<int>(55);
	std::cout << *n << std::endl;
}
/* ----------------------- Template Specializations -------------------------
	Specializations instantiate a template; they do not overload it.
As a result, specializations do not affect function matching.
--
Templates and their specializations should be declared in the same header file.
Declarations for all the templates with a given name should appear first,
followed by any specializations of those templates.
----------------------------------------------------------------------------*/
template <typename T> int Tcompare(const T&, const T&) { return 0; }

// handle string literals
template <size_t N, size_t M>
int Tcompare(const char(&)[N], const char(&)[M]) { return 0; }
//	const char *p1 = "hi", *p2 = "mom";
//  compare(p1,p2);			// calls the first template (not ok)
//	compare("hi","mom");	// calls the second template

// handles pointers to characters arrays, but doesn't participate in matching
template <>
int Tcompare(const char* const& p1, const char* const& p2) {
	return std::strcmp(p1, p2);
}

/* --------------------- Class Template Specializations ----------------------
We can partially specialize only a class template. We cannot partially
specialize a function template.
----------------------------------------------------------------------------*/
template <class T> struct Cremove_reference {
	typedef T type;
};
// partial specializations will be used for lvalue and rvalue references
template <class T> struct Cremove_reference<T&> // lvalue ref
{ typedef T type; };
template <class T> struct Cremove_reference<T&&> // rvalue ref
{ typedef T type; };

void  partial_specializations_test() {
	int i  = 66;
	// delctype(42) is int, uses the original template
	Cremove_reference<decltype(42)>::type a;
	// decltype(i) is int&, uses first (T&) partial specialization
	Cremove_reference<decltype(i)>::type b;
	// decltype(std::move(i)) is int&&, uses second T&& partial specialization
	Cremove_reference<decltype(std::move(i))>::type c;

	// ! a,b,c have type int
	// so due to partial specialization T& T&& we can extract type T

}

template <typename T> struct Foo {
	Foo(const T &t = T()) : mem(t){ }
	void Bar() { /*...*/ }
	T mem;
	// other members
};
template<>				// specializing a template
void Foo<int>::Bar()	// specializing the Bar of Foo <int>
{
	// do anything that applies to int
	
	// Foo<string> fs;  // instantiates Foo<string>::Foo()
	// fs.Bar();		// instantiates Foo<string>::Bar()
	// Foo<int> fi;		// instantiates Foo<int>::Foo()
	// fi.Bar();		// uses our specialization of Foo<int>::Bar()
}
//
void Exercise16_62() {
	std::unordered_multiset<Sales_data> Saleset;
	Saleset.emplace("Book1",2,10);
	Saleset.emplace("Book2",4,16);
	Saleset.emplace("Book3",5,23);

	std::for_each(Saleset.begin(), Saleset.end(), 
		[](auto const& x) { std::cout << x << std::endl; });
}
//
template <typename T>
int countOccur(const std::vector<T>& vec, T v) {
	int count = 0;
	std::for_each(vec.cbegin(), vec.cend(),
		[&](auto const& x) { if (x == v) ++count; });
	return count;
}
template <>
int countOccur(const std::vector<const char*>& vec, const char* cp) {
	int count = 0;
	std::for_each(vec.cbegin(), vec.cend(),
		[&](auto const& x) { if (std::strcmp(cp, x) == 0) ++count; });
	return count;
}
void Exercise16_63() {
	std::vector<int> ivec{ 1,2,3,1,1 };
	std::vector<double> dvec{ 1.1,2.2,3.3,1.1,2.2 };
	std::vector<std::string> svec{ "hello","hello","no","no","fine"};
	std::string s("no");

	std::cout << "1 occurs: " << countOccur(ivec, 1) << std::endl;
	std::cout << "2.2 occurs: " << countOccur(dvec, 2.2) << std::endl;
	std::cout << s << " occurs: " << countOccur(svec,s) << std::endl;

}
void Exercise16_64() {
	const char* cp("yes");
	std::vector<const char*> cpvec{ "yes","no","yes","yes","no"};
	std::cout << cp << "  occurs: " << countOccur(cpvec, "yes") << std::endl;
}
void Exercise16_66_67() {
	// overloading changes the function match.
	// specialization doesn't change match
	// hidden convertions will not be possible ?

	// Template specialization would not influence the match process of function;
	// for that template specialization is a instance of a template,
	// not an overload of it.

}

int main() {

	Debug_rep_Test();
	Exercise16_64();
	Exercise16_63();
	Exercise16_62();
	Exercise16_61();
	Exercise16_59();
	Exercise16_56();
	Exercise16_53();
	Exercise16_51();
	/* 
	Debug_rep_Test();
	my_Flip_Test();
	Exercise16_45();
	Exercise16_44();
	Exercise16_43();
	Exercise16_42();
	funcPointers();
	Exercise16_41();
	Exercise16_40();
	Exercise_Trailing_return();
	Exercise16_29_30();
	Exercise16_28_shared();
	Exercise16_28();
	std::cout << std::endl;
	Exercise16_22();
	Exercise16_24();
	unqTest();
	Exercise16_20();
	Exercise16_19();
	Exercise16_16();
	Exercise16_15();
	Exercise16_14();
	Exercise16_12();
	Exercise16_7();
	Exercise16_6();
	Exercise16_5();
	Exercise16_4();
	Exercise16_3();
	Exercise16_2();
	*/

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
