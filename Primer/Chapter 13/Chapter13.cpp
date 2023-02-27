#pragma once
#include "HasPtr.h"
#include "numbered.h"
#include "Employee.h"
#include "StrBlob.h"
#include "TreeNode.h"
#include "Message.h"
#include <algorithm>
#include "StrVec.h"
#include "_String.h"
#include "Foo.h"

void Exercise13_5() {
	/*HasPtr p1("String");
	HasPtr p2(p1);
	p1.set_ps("Changed");

	p1.print(std::cout) << std::endl;
	p2.print(std::cout) << std::endl;

	p2 = p1;
	p1.print(std::cout) << std::endl;
	p2.print(std::cout) << std::endl;

	p1.set_ps("Second changed");
	p1.print(std::cout) << std::endl;
	p2.print(std::cout) << std::endl;*/

}
void Exercise13_14() {
	numbered a("name"), b = a, c = b;
	c = a;
	a.f();
	b.f();
	c.f();
}
void Exercise13_19() {
	Employee e1("Bob");
	Employee e2 = e1;
	Employee e3("Jack");

	e1.print(std::cout) << std::endl;
	e2.print(std::cout) << std::endl;
	e3.print(std::cout) << std::endl;


}
void Exercise13_22() {
	HasPtr p1("Hello");
	p1 = p1;
	p1.print(std::cout);
}
void Exercise13_26() {
	StrBlob sB1({ "One","Two","Third" });
	StrBlob sB2(sB1);
	sB1.push_back("Four");
	std::cout << sB1.size() << std::endl;
	std::cout << sB2.size() << std::endl;

	sB2 = sB1;
	std::cout << sB1.size() << std::endl;
	std::cout << sB2.size() << std::endl;

	sB1 = sB1;
	sB1.pop_back();
	std::cout << sB1.size() << std::endl;
	std::cout << sB2.size() << std::endl;
}
void Exercise13_27() {
	HasPtrRef r1("Hello");
	HasPtrRef r2(r1);
	HasPtrRef r3("Bye");
	r1.print(std::cout) << std::endl;
	r2.print(std::cout) << std::endl;
	r3.print(std::cout) << std::endl;

	r1 = r3;
	r1.print(std::cout) << std::endl;
	r2.print(std::cout) << std::endl;
	r3.print(std::cout) << std::endl;

	r1 = r1;
	r2 = r1;
	r3 = r1;
	r1.print(std::cout) << std::endl;
	r2.print(std::cout) << std::endl;
	r3.print(std::cout) << std::endl;

}
void Exercise13_28() {
	auto root = TreeNode("root");
	auto left = TreeNode("left");
	auto right = TreeNode("right");
}
void Exercise13_30() {
	auto p1 = HasPtr("one");
	auto p2 = HasPtr("two");
	swap(p1, p2);
	p1.print(std::cout) << std::endl;
	p2.print(std::cout) << std::endl;
}
void Exercise13_31() {
	std::vector<HasPtr> vh;
	vh.push_back(HasPtr("hello"));
	vh.push_back(HasPtr("you"));
	vh.push_back(HasPtr("me"));
	sort(vh.begin(), vh.end());


	for (auto p : vh) {
		p.print(std::cout) << std::endl;
	}
}
void Exercise13_33_38() {
	Folder f1, f2;
	Message m1("Message - 1"), m2("Message - 2"), m3("Message - 3");
	f1.save(m1); f1.save(m2); f1.save(m3);
	f2.save(m1);
	f1.print();
	f2.print();
	m1.print(std::cout) << std::endl;
}
void Exercise13_39() {
	StrVec strv;
	strv.push_back("One");
	std::cout << "Elements: " << strv.size() << ", capacity: " << strv.capacity() << std::endl;
	
	strv.reserve(25);
	strv.print_info(std::cout);

	strv.resize(10, "res");
	strv.print_info(std::cout);
	
	strv.resize(75, "res2");
	std::cout << "Elements: " << strv.size() << ", capacity: " << strv.capacity() << std::endl;
	
}
void Exercise13_40() {
	StrVec strv({ "One", "Two", "Three", "Four" });
	strv.print_info(std::cout) << std::endl;
}
void Exercise13_42() {
	// later
}
void Exercise13_43() {
	StrVec strv({ "1", "2", "3", "4" });
	strv.print_info(std::cout);
	/*strv.test();
	strv.print_info(std::cout) << std::endl;*/
}
void Exercise13_44() {
	const char ca[] = "hello";
	const char* cp = ca;
	_String st(cp), st1("hello"), st2;
	st.print();
	st = st1;
	st1.print();
	st1 = st2;
	st.print();
}
int f() { return 0; }
void Exercise13_45() {
	std::vector<int> vi(100);   
	int&& r1 = f();				// rvalue
	// int&& r2 = vi[0];		// lvalue
	// int&& r3 = r1;			// lvalue
	int&& r4 = vi[0] * f();		// rvalue

}
void Exercise13_48_50() {
	std::vector<_String> svec;
	_String s;
	for (int i = 0; i != 4; ++i) {
		std::cout << i << ' ';
		svec.push_back(s);			// copy operator called
		// svec.push_back("Hello"); // && move called
		// every time new memory allocated, elements moved by && operator
	}
	std::cout << std::endl;
}
void Exercise13_51() {
	// unque pointer supports move and move-assign operator
	// in clone function object is about to be destroyed
}
void Exercise13_54() {
	HasPtr h("helloworld");
	HasPtr h2 = h;
	HasPtr h3 = std::move(h2);
	h2 = h;
	h2 = std::move(h3);
	// if the original copy-assignment operator stay unchanged
	// compiler warns:
	// ambiguous overload for 'operator='
}
void FooTest() {
	//Foo& retFoo();
	//Foo retVal();
	
}
void Exercise13_56() {
	// infinity loop, because we sort lvalue;
	const Foo f;
	f.sorted();
}
void Exercise13_57() {
	// sorted&& called in sort&
}

//int main() {
//
//	Exercise13_56();
//
//	Exercise13_48_50();
//	Exercise13_44();
//	Exercise13_43();
//	Exercise13_40();
//	Exercise13_39();
//	Exercise13_33_38();
//	Exercise13_31();
//	std::cout << std::endl;
//	Exercise13_30();
//	Exercise13_28();
//	Exercise13_27();
//	Exercise13_26();
//	Exercise13_22();
//	Exercise13_19();
//	Exercise13_14();
//	Exercise13_5();
//	return 0;
//}