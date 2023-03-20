#include <iostream>
#include <fstream>
#include <vector>
#include "Sales_data.h"
#include "ZooAnimal.h"

/* ----------------------------- Exception ----------------------------------
Destructor are run during stack unwinding affects how we write destructors.
An exception raised - and during unwinding thrown a new exception and not caught
in the function that thew it, terminate is called.
--
So destructors should not thrown exception that they can't handle itself;
--
The only way for a constructor to handle an exception from a constructor
initializer is to write the constructor as a function try block
----------------------------------------------------------------------------*/
/* ---------------- Exercise 18.1 ----------------- */
// second time is std::exception not std::range_error.
//  terminate called after throwing an 'std::exception*'.
/* ---------------- Exercise 18.2 ----------------- */
void Exercise18_2(int* b, int* e) {
	std::vector<int> v(b, e);			// v will be deleted by it's destructor
	auto* p = new int[v.size()];		// p will be deleted, but memory not deallocated
	std::ifstream in("data/text.txt"); // in will be deleted
	// exception occurs here
	delete[]p;
}
/* ---------------- Exercise 18.3 ----------------- */
// use shared_ptr
// create own array class with destructor
/* ---------------- Exercise 18.4 ----------------- */
// try {
// } cath(exception){
// } catch(const runtime_error &re){
// } catch(overflow_error_eobj) {}
//
// first match will be used in throw
// due to exception in top hierarchy, it will never proceed
/* ---------------- Exercise 18.5 ----------------- */
void Exercise18_5() {
	try {
		std::range_error ex(0);
		throw ex;
	}
	// runtime errors
	catch (std::range_error re) {
		std::cerr << re.what() << std::endl;
		std::abort();
	}
	catch (std::underflow_error ue) {
		std::cerr << ue.what() << std::endl;
		std::abort();
	}
	catch (std::overflow_error ofe) {
		std::cerr << ofe.what() << std::endl;
		std::abort();
	}
	// logic errors
	catch (std::length_error le) {
		std::cerr << le.what() << std::endl;
		std::abort();
	}
	catch (std::out_of_range oute) {
		std::cerr << oute.what() << std::endl;
		std::abort();
	}
	catch (std::invalid_argument invalide) {
		std::cerr << invalide.what() << std::endl;
		std::abort();
	}
	catch (std::domain_error dome) {
		std::cerr << dome.what() << std::endl;
		std::abort();
	}
	// general runtime
	catch (std::runtime_error rune) {
		std::cerr << rune.what() << std::endl;
		std::abort();
	}
	// general logic
	catch (std::logic_error loge) {
		std::cerr << loge.what() << std::endl;
		std::abort();
	}
	// general cast
	catch (std::bad_cast badce) {
		std::cerr << badce.what() << std::endl;
		std::abort();
	}
	// general bad allocate
	catch (std::bad_alloc bade) {
		std::cerr << bade.what() << std::endl;
		std::abort();
	}
	// all exceptions
	catch (std::exception e) {
		std::cerr << e.what() << std::endl;
		std::abort();
	}
}
/* ---------------- Exercise 18.6 ----------------- */
class exceptionType {};
void Exercise18_6() {
	// (a)
	try {
		exceptionType et;
		exceptionType* pet = &et;
		throw pet;
	}
	catch (exceptionType* pet) {
		std::cerr << "exceptionType catched" << std::endl;
	}
	// b
	try {
		std::exception e;
		throw e;
	}
	catch (...) {
		std::cerr << "... catched" << std::endl;
	}
	// c
	typedef int EXCPTYPE;
	try {
		EXCPTYPE ex(1);
		throw ex;
	}
	catch (EXCPTYPE) {
		std::cout << "EXCPTYPE catched" << std::endl;
	}
}
/* ---------------- Exercise 18.7 ----------------- */
// look in Blob.h
/* ---------------- Exercise 18.8 ----------------- */
// Be sure that function and operation called in one destructor must be noexcept,
// then this destructor is noexcept;
// or that could not be guaranteed,
// use function try block in destructor to handle exceptions.
/* ---------------- Exercise 18.9 ----------------- */
// look Sales data
/* --------------- Exercise 18.10 ----------------- */
void Exercise18_10() {
	Sales_data sale1("ISBN-1"), sale2("ISBN-2"), sum;
	try {
		sum = sale1 + sale2;
	}
	catch (const isbn_mismatch& e) {
		std::cerr << e.what() << ": left isbn(" << e.left
			<< ") right isbn(" << e.right << ")" << std::endl;
	}
}
/* --------------- Exercise 18.11 ----------------- */
// what() - usually called during stack unwinding, if it throws an exception
// it can't handle program will terminate

/* ----------------------------- Namespaces ----------------------------------
:: global scope
--
inline namespace - names in inline can be used as they were direct members of
enclosing namespace name.
--
unnamed namespace - variables have static lifetime
--
move and forward  are templates, and takes single rvalue ref - that in templates can match                                                                                                                                                                                        any type
then if our program has own move with one parameter, no matter of type it will collide with the library
----------------------------------------------------------------------------*/

/* --------------- Exercise 18.12 ----------------- */
// look for Query and TextQuery

/* --------------- Exercise 18.13 ----------------- */
// When need to define a name which is visible in current file, locally ,
// but not so for external files.

/* --------------- Exercise 18.14 ----------------- */
// // mathLib::MatrixLib::matrix mathLib::MatrixLib::operator*(const matrix&, const matrix&);

namespace cplusplus_primer {}
namespace primer = cplusplus_primer;

/* --------------- Exercise 18.15 ----------------- */
// - using declaration
// introduces one member of specified namespace at one time;
// could put in global scope, local scope, namespace scope and class scope;
// name conflict bug easy to find and correct;
// - using directive
// make all names of specified namespace visible and accessible;
// could put in global scope, local scope and namespace scope, but not class scope;
// more complicated mechanism, it lifts namespace members to the most close outer scope
// which includes namespace itself and using directive;
// more likely to bring name conflict issue, bug hard to find and correct;

/* --------------- Exercise 18.16-17 ----------------- */
namespace Exercise18_16 {
	int ivar = 0;
	double dvar = 0;
	const int limit = 1000;
}

int ivar = 0;
//using namespace Exercise18_16;
//using Exercise18_16::ivar;
//using Exercise18_16::limit;
//using Exercise18_16::dvar;
// ^^ position 1
// ^^ directive: ++ivar will be ambiguous;
//	  dvar hides Ex dvar;
//    declaration: multiple declaration of 'ivar', two declarations in one scope

void manip() {
	// position 2
	//using Exercise18_16::ivar;
	using Exercise18_16::limit;
	//using Exercise18_16::dvar;
	// - directive: ++ivar will be still ambiguous
	// dvar hides Ex dvar;
	// - declaration: dvar - multiple initialization
	// ivar decl, hides global ivar;
	double dvar = 3.1416;
	int iobj = limit + 1;
	++ivar;
	++::ivar;
}
namespace nA {
	class C {
		friend void f2();
		friend void f(const C&) {}
	};
	void f2() {}
}
void looknamespace() {
	std::string s;
	// look firstly in this scope, then in std due to cin class
	operator>>(std::cin, s);
	// other we would
	using std::operator>>; // need t allow cin>>s
	std::operator>>(std::cin, s); // ok: explicity use std::>>
	//
	nA::C cobj;
	f(cobj); // ok: finds A::f through the friend decl A::C
	nA::f2(); //f2(); // error A::f2() should be
}
/* --------------- Exercise 18.18-19 ----------------- */
// using std::swap all the following uses of swap in the scope of the function will
// look for the matching template for its argument types in the standard library.
// would use the matching std version of swap for that specific call.
namespace primerLib {
	void compute() {};					// doesn't match
	void compute(const void*) {};		// matches, converts 0 to const void *
}
// using primerLib::compute;
void compute(int) {}					// best match
void compute(double, double = 3.4) {}	// matches, collision with const void*, char*
void compute(char*, char* = 0) { };		// matches, collision with const void*, double
void Exercise18_20() {
	// when on this position
	using primerLib::compute;			// const void * will be selected, will not look for compute above
	compute(0);							// if not match to const void* - then error
}
/* --------------- Exercise 18.21 ----------------- */
// example from Internet
// (a) class CADVehice
// CAD Vehicle publicly inherits from CAD and privaetely inherits from Vehicle.CADVehicle gets 
// all the public and private methods that Vehicle has but cant be cast to a Vehicle argument.
// It is an "inaccessible" base.
//CadVehicle example;
//void foo(Vehicle) {/*do something*/ };
//foo(CADVehicle);//will not work, will work if Vehicle were public

/* --------------- Exercise 18.22 ----------------- */
using std::cout;
struct A { public: A() { cout << "A"; } };
struct B : public A {  B() : A() { cout << "B"; } };
struct C : public B {  C() : B() { cout << "C"; } };
struct X { public: X() { cout << "X"; } };
struct Y { public: Y() { cout << "Y"; } };
struct Z : public X, public Y { Z() : X(), Y() { cout << "Z"; } };
struct MI : public C, public Z { MI() : C(), Z() { cout << "MI"; } };

//  A, B, C ; X Y Z,MI; - construct order
void Exercise18_22() {
	MI x;
	std::cout << std::endl;
}
/* --------------- Exercise 18.23 ----------------- */
class D : public X, public C { public: D() : X(), C() { std::cout << "D"; } };
void Exercise18_23() {
	// all ok
	D* pd = new D;
	X* px = pd;
	A* pa = pd;
	B* pb = pd;
	C* pc = pd;
}
/* --------------- Exercise 18.24 ----------------- */
void Exercise18_24() {
	//ZooAnimal* pb = new Panda("ying_yang");

	//pb->print();	// ok, part of ZooAnimal interface
	//pb->cuddle();	// error, static type ZooAnimal has no member cuddle
	//pb->highlight();// error, static type ZooAnimal has no member highlight
	//delete pb;		// ok Panda::~Panda()

	Panda p("yuind");
	//p.get_max_weight() // ambiguos
	p.ZooAnimal::get_max_weight(); // ok
}

/* --------------- Exercise 18.25 ----------------- */
struct Base1 {
	virtual void print() { std::cout << "Base1::print() "; }
	virtual ~Base1() { std::cout << "Base1::~Base1() "; };
};
struct Base2 {
	virtual void print() { std::cout << "Base2::print() " ; }
	virtual ~Base2() { std::cout << "Base2::~Base2() "; };
};
struct D1 : public Base1 {
	void print() override { std::cout << "D1::print()" << std::endl; }
	~D1() override { std::cout << "D1::~D1() "; };
};
struct D2 : public Base2 {
	void print() override { std::cout << "D2::print()" << std::endl; }
	~D2() override { std::cout << "D2::~D2() "; };
};
struct MII : public D1, public D2 { 
	//void print() override { std::cout << "MII::print()" << std::endl; }
	~MII() final { std::cout << "MII::~MII() "; };
};
void Exercise18_25() {

	Base1* pb1 = new MII;
	Base2* pb2 = new MII;
	D1* pd1 = new MII;
	D2* pd2 = new MII;
	MII* mii = new MII;
	// (0)
	// mii->print(); // error: ambiguos, if MII doesn't override print();
	// (a)
	pb1->print(); // Base->D1::print(), if override MII::print()
	// (b)
	pd1->print(); // D1::print(), if override MII::print()
	// (c)
	pd2->print(); // D2::print(), if override MII::print()
	// (d)
	delete pb2;    // ~MII(), ~D2(), Base2(), ~D1(), Base1(); +
	std::cout << std::endl;
	// (e)
	delete pd1;	  // ~MII(), ~D2(), ~Base2(), ~D1(), Base1();  
	std::cout << std::endl;
	// (f)
	delete pd2;  // same
	std::cout << std::endl;

}
/* --------------- Exercise 18.26-27 ----------------- */
namespace ex18_26_27 {
	struct Base1 {
		void print(int) const {};
	protected:
		int		ival;
		double  dval;
		char	cval;
	private:
		int		*id;
	};
	struct Base2 {
		void print(double) const {};
	protected:
		double	fval;
	private:
		double	dval;
	};
	struct Derived : public Base1 {
		void print(std::string) const {};
	protected:
		std::string sval;
		double		dval;
	};
	struct MI : public Derived, public Base2 {
		void print(const std::vector<double>&) const { /**/ };
		void print(int val) const { Base1::print(val); }
		void foo(double);
	protected:
		int					*ival;
		std::vector<double>  dvec;
	}; 

	void Exercise18_26() {
		MI mi;
		mi.print(42); // added int version to MI  that calls Base1::print(int)
	}
	void MI::foo(double cval) {
		int dval;

		// (a)
		MI::dvec;
		MI::ival;
		MI::cval;
		MI::sval;
		MI::fval;

		// MI::dval; // ambiguos
		Derived::dval;
		Base1::dval;

		Base1::ival; // hidden by MI *ival;

		// (b) yes

		// (c) 
		dval = Base1::dval + Derived::dval;
		// (d)
		Base2::fval = dvec.at(dvec.size() - 1);
		// (e)
		sval[0] = Base1::cval;
	}
} 
/* --------------- Exercise 18.28  ----------------- */
void dance(const Bear&) {}
void rummage(const Raccoon&) {}
std::ostream& operator <<(std::ostream& os, const ZooAnimal&) { return os; }
void virtual_inheritance() {
	Panda ying_yang("panda");
	dance(ying_yang);		// ok: passes Panda object as Bear
	rummage(ying_yang);		// ok: passes Panda object as Raccoon
	std::cout << ying_yang; // ok: passes Panda object as a ZooAnimal
}
namespace ex18_28 {
	struct Base {
		void bar(int);
	protected:
		int ival;
	};
	struct Derived1 : virtual public Base {
		void bar(char);
		void foo(char);
	protected:
		char cval;
	};
	struct Derived2 : virtual public Base {
		void foo(int);
	protected:
		int ival;
		char cval;
	};
	class VMI : public Derived1, public Derived2 {
		void access() {
			ival;		// Derived2::ival hides Base::ival 
			// cval;	// ambiguous call D1 D2 has cval
			//foo(1);	// ambiguous char and int equally good
			//foo('c'); // ambiguous char and int equally good
			bar('s');	// Derived1::bar(char) hides Base::bar(int)

		}
	};
	void Exercise18_28() {
		VMI vmi;

	}
};
/* --------------- Exercise 18.29_30  ----------------- */
namespace ex18_29_30 {
	using std::cout;
	using std::endl;
	struct Class { Class() { cout << "Class() "; } };
	struct Base : public Class {
		Base() : num(0) { cout << "Base() "; }
		Base(const Base& base) : num(base.num) { }
		explicit Base(int n) : num(n) {}

		int getNum() const { return num; }
	private:
		int num;
	};
	struct D1 : virtual public Base { 
		D1() { cout << "D1() "; } 
		D1(const D1& d) : Base(d) { }
		explicit D1(int n) : Base(n) {}
	};
	struct D2 : virtual public Base {
		D2() { cout << "D2() "; }
		D2(const D1& d) : Base(d) { }
		explicit D2(int n) : Base(n) { }
	}; 
	struct MI : public D1, public D2 { 
		MI() { cout << "MI() "; } 
		MI(const MI& mi) : Base(mi), D1(mi), D2(mi) { }
		explicit MI(int n) : Base(n), D1(n), D2(n) { } 
	};
	struct Final : public MI, public Class { 
		Final() { cout << "Final() "; } 
		Final(const Final& f) : Base(f), MI(f) { } 
		explicit Final(int n) : Base(n), MI(n) { } 
	};

	void Exercise18_29() {
		// (a)
		Final fin; cout << endl;
		// C: Class(), Base(), D1(), D2(), MI(), Class(), Final() // + correct
		// D: in reverse order;
		
		// (b)
		// one Base, two Class parts;

		// (c)
		Base* pb; Class* pc; MI* pmi; D2* pd2;
		// pb = new Class; // compile error
		pc = new Final;		
		//pmi = pb;       // compile error
		//pd2 = pmi;	  // 

	}
	void Exercise18_30() {
		Final f1(4);
		Final f2(f1);
		cout << f1.getNum() << " " << f2.getNum() << endl;
		cout << endl;
	}
};

//int main() {    
//	
//	ex18_29_30::Exercise18_30();
//	ex18_29_30::Exercise18_29();
//	virtual_inheritance(); 
//	Exercise18_25(); 
//	Exercise18_24();
//	Exercise18_20();
//	Exercise18_10();
//	Exercise18_6();
//	//Exercise18_5();
//}