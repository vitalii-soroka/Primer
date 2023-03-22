#include <memory>
#include <iostream>
#include <string>
#include <functional>		// function, mem_fn
#include <algorithm>		// count_if
#include "Query_base.h"
#include "Sales_data.h"
#include "Screen.h"
#include "miniScreen.h"
#include "Token.h"

/* --------------- Exercise 19.1 ----------------- */
void* operator new(size_t size) {
	if (void* mem = std::malloc(size))
		return mem; 
	else
		throw std::bad_alloc();
}
void operator delete(void* mem) noexcept { free(mem); }

/* --------------- Exercise 19.2 ----------------- */
/* --------------- Exercise 19.3 ----------------- */
namespace ex19_3_4 {
	struct A { A() = default; A(int i) : ival(i) {} virtual ~A() = default; int ival = 0; };
	struct B : public A { B() = default; using A::A; ~B() override = default; };
	struct C : public B { C() = default; using B::B; ~C() override = default; };
	struct D : public B, public A { D() = default; D(int i,int j) : B(i), A(j) {} ~D() override = default; };

	void Exercise19_3() {
		// (a)
		// A* pa = new C;
		// B *bp = dynamic_cast<B*>(pa); // ok
		
		// (b)
		// B* pb = new B;
		// C* pc = dynamic_cast<C*>(pb); // error, pc is null
		// std::cout << pc << std::endl;

		// (c)
		A* pa = new D(5,10);
		B* bp = dynamic_cast<B*>(pa); // ok?, but D contains two parts of A 
		std::cout << bp->ival << std::endl; 
	}

/* --------------- Exercise 19.4 ----------------- */
	void Exercise19_4() {
		A* pa = new C;
		try {
			auto& cr = dynamic_cast<C&>(*pa);
			// usage of type C
		}
		catch (std::bad_cast) {
			// usage of type A
		}
	}
};
/* --------------- Exercise 19.5 ----------------- */
// When want to use dynamic type object's non-virtual member
/* --------------- Exercise 19.6  ----------------- */
void Exercise19_6() {
	using namespace chapter15;
	Query q1("one");
	Query q2("two");
	Query_base* query_base = nullptr;// new AndQuery(q1, q2);
	auto and_query = dynamic_cast<AndQuery*>(query_base);
	std::cout << (and_query != nullptr && typeid(*and_query) == typeid(AndQuery) ? "casted" : " not casted") << std::endl;
}
/* --------------- Exercise 19.7 ----------------- */
void Exercise19_7() {
	using namespace chapter15;
	Query q1("one");
	Query q2("two");
	Query_base* query_base = new AndQuery(q1, q2);
	auto query_ref = dynamic_cast<AndQuery&>(*query_base);
	std::cout << (typeid(query_ref) == typeid(AndQuery&) ? "casted" : " not casted") << std::endl;

}
/* --------------- Exercise 19.8 ----------------- */
void Exercise19_8() {
	using namespace chapter15;
	Query q1("one");
	Query q2("two");
	Query_base* qp1 = new AndQuery(q1, q2);
	Query_base* qp2 = new OrQuery(q1, q2);
	std::cout << "types " << (typeid(*qp1) == typeid(*qp2) ? "match" : "not match") << std::endl;
	std::cout << "is " << (typeid(*qp1) == typeid(AndQuery) ? "" : "not") << "AndQuery" << std::endl;

}
namespace RTTI {
	class Base {
		friend bool operator==(const Base&, const Base&);
	public:
		Base(int i) : ival(i) {}
		virtual ~Base() = default;
	protected:
		virtual bool equal(const Base&) const;
		int ival;
	};

	class Derived : public Base {
	public:
		using Base::Base;
		virtual ~Derived() = default;
	protected:
		bool equal(const Base&) const;
	};

	bool operator==(const Base& lhs, const Base& rhs) {
		// return false if typeids are different; otherwise makes a virtual call to equal
		return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
	}
	bool Base::equal(const Base& rhs) const {
		// do work..
		return ival == rhs.ival;
	}
	bool Derived::equal(const Base& rhs) const {
		 // we know types are equal, so cas't won't throw 
		auto r = dynamic_cast<const Derived&>(rhs);
		// do the work to compare objects..
		return ival == r.ival;
	}
	void RTTI_equal_test() {
		Base* base = new Base(2);			// base
		Base* derived1 = new Derived(2);	// base pointer to derived
		Derived* derived2 = new Derived(2);	// derived

		std::cout << "Base == (base*)derived: " << (operator==(*base, *derived1) ? "yes" : "no") << std::endl;
		std::cout << "derived == (base*)derived: " << (operator==(*derived1, *derived2) ? "yes" : "no") << std::endl;

	}
};

/* --------------- Exercise 19.9 ----------------- */
void Exercise19_9() {
	using RTTI::Base;
	using RTTI::Derived;

	int arr[10];
	Derived d(4);
	Base* p = &d;
	std::cout << typeid(42).name() << ", "
		<< typeid(arr).name() << ", "
		<< typeid(Sales_data).name() << ", "
		<< typeid(std::string).name() << ", "
		<< typeid(p).name() << ", "
		<< typeid(*p).name() << ", " << std::endl;
}
/* --------------- Exercise 19.10 ----------------- */
namespace ex19_10 {
	struct A { A() = default; virtual ~A() = default; };
	struct B : public A { using A::A; ~B() override = default; };
	struct C : public B { using B::B; ~C() override = default; };

	void Exercise19_10() {
		// (a) - A* + / struct ex10_10::A* __ptr64
		A* pa = new C;
		std::cout << typeid(pa).name() << std::endl;

		// (b) - A* +
		C cobj;
		A& ra = cobj;
		std::cout << typeid(&ra).name() << std::endl;

		// (c)  B -
		B* px = new B;
		A& rar = *px;
		std::cout << typeid(rar).name() << std::endl;
	}

}
/* --------------- Enumerationns ----------------- */

/* -------------- Pointers to Class Member ---------------- 


--------------------------------------------------------- */
/* --------------- Exercise 19.11  ----------------- */
// ordinary data pointer directly points to member of object
// pointer to a data points to member of class, not object of that class 
/* --------------- Exercise 19.12 ----------------- */
void Exercise19_12() {
	Screen<10, 10> screen;
	const std::string::size_type Screen<10,10>::* cdata = Screen<10,10>::curpos();
	auto s = screen.*cdata;
	std::cout << s << std::endl;
	
	char(miniScreen:: * pmf)() const;
	pmf = &miniScreen::get_cursor;
	char(miniScreen:: * pmf2)(miniScreen::pos, miniScreen::pos) const;
	pmf2 = &miniScreen::get;
	miniScreen mScreen, * pScreen = &mScreen;
	char c1 = (pScreen->*pmf)();
	char c2 = (pScreen->*pmf2)(0, 0);
	//std::cout << "screen: " << mScreen.*pmf() << std::endl;
	//std::cout << "screen: " << mScreen.*pmf2(2,3) << std::endl;

}
/* --------------- Exercise 19.13 ----------------- */
void Exercise19_13() {
	Sales_data sales;
	const std::string Sales_data::* pBookNo; /*= &Sales_data::bookNo;*/
}
namespace typeAlias {
	// type that can point to a member function of Screen
	// that returns a char and takes two pos arguments
	using Action = char(miniScreen::*)(miniScreen::pos, miniScreen::pos) const;

	miniScreen& action(miniScreen& sc, Action act = &miniScreen::get) {
		std::cout << (sc.*act)(0, 0) << std::endl;
		return sc;
	}
	void typeAlias() {
		Action get = &miniScreen::get; // get points to the get member of Screen
		// action takes a reference to a Screen and a pointer to a Screen member function

		miniScreen mScreen;
		action(mScreen, get);
		action(mScreen, &miniScreen::get);
		action(mScreen);
	}
}
/* --------------- Exercise 19.14 ----------------- */
void Exercise19_14() {
	// illegal in my case 
	 
	// pointer to member function that takes -no- parameters
	auto pmf = &miniScreen::get_cursor;
	// pointer to member function that takes -two- parameters
	//pmf = &miniScreen::get;
}
/* --------------- Exercise 19.15 ----------------- */
// as for me main difference that member function pointer points to specific member in class
// ordinary function pointer points to a
// member function - is not callable
/* --------------- Exercise 19.16 ----------------- */
using ex19_16_alias = double(Sales_data::*)() const;
void Exercise19_16() {
	ex19_16_alias avg = &Sales_data::avg_price;
	Sales_data s;
	std::cout << "price: " << (s.*avg)() << std::endl;
}
/* --------------- Exercise 19.17 ----------------- */
using ex19_17_alias = miniScreen& (miniScreen::*)();
void Exercise19_17() {
	ex19_17_alias move = &miniScreen::home;
	miniScreen sc;
	(sc.*move)();
}
/* --------------- Exercise 19.18 ----------------- */
void Exercise19_18() {
	std::vector<std::string> svec{ "one","two","","four",""};
	// std::function<bool(const std::string*)> fp = &std::string::empty;
	//auto it = std::find_if(svec.begin(), svec.end(), function);
	auto function = std::mem_fn(&std::string::empty);
	auto it = std::count_if(svec.begin(), svec.end(), std::bind(&std::string::empty, std::placeholders::_1));
	std::cout << it << " empty string(s)" << std::endl;

	// 
	auto f = std::bind(&std::string::empty, std::placeholders::_1);
	std::cout << "empty first: " << f(*svec.begin()); // ok: argument is a string f will use .* to call empty
	std::cout << "empty ([0]pointer)" << f(&svec[0]); // ok: argument is a pointer t ostring f will use .-> to call empty
}
/* --------------- Exercise 19.19 ----------------- */
void Exercise19_19() {
	double price = 10.0; 
	Sales_data sale1("book1");
	Sales_data sale2("book2");
	Sales_data sale3("book3", 1 , 1 );
	Sales_data sale4("book4", 10 , 20 );
	std::vector<Sales_data> sdata{ sale1,sale2,sale3,sale4 }; 
	// mem_fn to be able use auto
	auto function = std::mem_fn(&Sales_data::avg_price);	//  bind it to avg_price member function
	// predicate to pass it in find_if algorithm
	auto predicate = [&function,&price](Sales_data data) { return function(data) > price; };

	auto it = std::find_if(sdata.begin(), sdata.end(), predicate);

	std::cout << "first sale: " << it->isbn() << std::endl;
}

/* ------------------ Nested Classes ----------------------

 class members that are type of a union are not automatically destroyed
--------------------------------------------------------- */
/* --------------- Exercise 19.20 ----------------- */
// skip for now
/* --------------- Exercise 19.21_22 ----------------- */
void Exercise19_21_22() {
	Token intToken; intToken = 12;
	Token strToken; strToken = "string";
	Token charToken; charToken = 'x';
	Token saleToken; saleToken = Sales_data();

	intToken.print(std::cout) << std::endl;
	strToken.print(std::cout) << std::endl;
	charToken.print(std::cout) << std::endl;
	saleToken.print(std::cout) << "\n\n";
	
	intToken = 3.4;
	strToken = Sales_data("sale", 1, 2);
	saleToken = "new string";

	intToken.print(std::cout) << std::endl;
	strToken.print(std::cout) << std::endl;
	charToken.print(std::cout) << std::endl;
	saleToken.print(std::cout) << std::endl;

	
}

/* --------------- Exercise 19.23 ----------------- */
void Exercise19_23() {
	Token temp; temp.operator=(Sales_data("test", 10,10));
	Token token(std::move(temp));
	token.print(std::cout) << std::endl;
}
/* --------------- Exercise 19.24 ----------------- */
// see Token.h
void Exercise19_24() {
	Token token; 
	token.operator=("token");
	token.operator=(token);  // proceeds checks and self assign tok = t.tok
	token.print(std::cout) << std::endl;

}
/* --------------- Exercise 19.25 ----------------- */
// see Token.h

namespace unions_test{
	union Token {
		char cval;
		int ival;
		double dval;
	};
	static union {   // anonymous union
		char cval;
		int ival;
		double dval;
	};
}

int main() {

	Exercise19_24();
	Exercise19_23();
	Exercise19_21_22();
	Exercise19_19();
	Exercise19_18();
	Exercise19_16();
	typeAlias::typeAlias();
	Exercise19_12();
	ex19_10::Exercise19_10();
	Exercise19_9();
	RTTI::RTTI_equal_test();
	Exercise19_8();
	Exercise19_7();
	Exercise19_6();
	ex19_3_4::Exercise19_3();
	return 0;
}