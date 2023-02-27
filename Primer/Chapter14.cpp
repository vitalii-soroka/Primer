
#include "String.h"
#include "StrBlob.h"
#include "Sales_data.h"
#include "StrVec.h"
#include <algorithm>
#include <vector>
#include "ioString.h"
#include "isEqual.h"
#include <functional> // plus, negate
#include "Calculator.h"
#include "SmallInt.h"

void Exercise14_5() {

	String s("Hello");
	std::cout << s << std::endl;
}
void Exercise14_10() {
	// 1 good
	// 2 basic obj // wrong 
	Sales_data d1, d2;
	std::cin >> d1;
	std::cin >> d2;
	std::cout << d1 << std::endl;
	std::cout << d2 << std::endl;

}
void Exercise14_16() {
	StrBlob b1({ "Hello", "world", "no"});
	StrBlob b2({ "Hello", "world", "no"});
	std::cout << (b1 != b2) << std::endl;
	String s1("Hello");
	String s2("Hello");
	std::cout << (s1 != s2) << std::endl;
	StrVec sv1({ "hey" });
	StrVec sv2({ "hey" });
	std::cout << (sv1 != sv2) << std::endl;
}
void testStr() {
	StrBlob a1 = { "hi","bye","now" };
	StrBlobPtr p(a1);
	*p = "okay";
	std::cout << p->size() << std::endl;
	std::cout << (*p).size() << std::endl;
	
}
void Exercise14_32() {
	StrBlob sb{ "hello","world" };
	StrBlobPtr iter = sb.begin();
	StrBlobPtrPointer p(&iter);
	(*p).deref();
	std::cout << p->deref() << std::endl;
}
void TestPrintString() {
	PrintString printer;
	printer("Hello");
	PrintString errors(std::cerr, '\n');
	errors("Errors");
	std::vector<std::string> vs{"hello", "word", "end"};
	std::for_each(vs.begin(), vs.end(),PrintString(std::cout, '\n'));
}
void Exercise14_36() {
	ReadString reader;
	PrintString printer;

	std::vector<std::string> svec;

	for (std::string tmp; !(tmp = reader()).empty(); svec.push_back(tmp));
	for (const auto& s : svec) printer(s);

	std::cout << reader();
}
void Exercise14_37() {
	std::vector<int> ivec{ 3,2,1,5,6,6,8,6,10 };
	std::replace_if(ivec.begin(),ivec.end(),isEqual(6),0);
	std::for_each(ivec.begin(), ivec.end(), 
		[](const auto& x) { std::cout << x << ' '; });
}
void Exercise14_38() {
	std::vector<std::string> svec{ "one","two","hello","nuts" };
	for (auto i = 0; i != 10; ++i) {
		auto wc = std::count_if(svec.begin(), svec.end(), SizeComp(i+1));
		std::cout << wc << " word of length: " << i+1 << std::endl;
	}
}
void Exercise14_39() {
	std::vector<std::string> svec
		{ "onesssssssssss","twossssssssssssssss","hello","nuts" };
	auto wc = std::count_if(svec.begin(), svec.end(), inSizeRange(1, 10));
	std::cout << wc << " words 1-9" << std::endl;
	std::cout << svec.size() - wc << " word more than 10 " << std::endl;
}
void LibraryFunctions() {
	std::negate<int> intNegate;

	std::plus<int> intAdd;
	int sum = intAdd(10, 20);

	sum = intNegate(intAdd(10,20));

	std::vector<std::string> svec{ "h","mn","ssc" };
	std::sort(svec.begin(), svec.end(), 
		std::greater<std::string>());

	std::vector<std::string*> nameTable;
	// error
	// std::sort(svec.begin(), svec.end(),
	//  	[](std::string* a, std::string* b) {return *a < *b; });
	// ok
	std::sort(svec.begin(), svec.end(),
		std::less<std::string>());
}
void Exercise14_42() {
	using std::placeholders::_1;
	auto c = std::bind(std::greater<int>(),_1,20);
	std::vector<int> ivec{ 1,1025,3045,4 };
	std::cout <<
		std::count_if(ivec.begin(), ivec.end(), c) 
		<< std::endl;

	std::vector <std::string> svec{ "pooh","double","pooh","bool" };
	std::cout <<
		*std::find_if(svec.begin(), svec.end(),
			std::bind(std::not_equal_to<std::string>(), _1, "pooh")) 
		<< std::endl;

	std::transform(ivec.begin(),ivec.end(), ivec.begin(),
		std::bind(std::multiplies<int>(),_1,2));
	std::for_each(ivec.begin(), ivec.end(),
		[](const auto& x) { std::cout << x << ' '; });
	std::cout << std::endl;
}
void Exercise14_43()  {
	auto data = { 2,5,7 };

	int number = 9;
	std::modulus<int> mod;
	auto pred = [mod,number](int i) { return 0 == mod(number, i); };                                                                               
	
	auto is_divides = std::any_of(data.begin(), data.end(), pred);
	std::cout << is_divides << std::endl;
	std::cout << ( is_divides ? "True" : "False" ) << std::endl;

}
// **** //
void Exercise14_44() {
	IntCalculator calculator;
	while (std::cout << "\nEnter n o n \n", true) {
		int lhs, rhs;
		std::string op;
		std::cin >> lhs >> op >> rhs;

		std::cout << calculator[op](lhs, rhs);
	}
}
void SmallIntTest() {
	SmallInt si;
	si = 4;
	auto n = static_cast<int>(si) + 3;
} 
void Exercise14_45() {
	Sales_data a("bookno",10,30);
	double d = 4.0 + static_cast<double>(a);
	std::string str("Hello");
	auto s = static_cast<std::string>(a) + str;
	std::cout << d << " " << s << std::endl;

}

//int main() {
//	 
//	
//	Exercise14_45();
//	Exercise14_44();
//	Exercise14_43();
//	Exercise14_42();
//	LibraryFunctions();
//	Exercise14_39();
//	Exercise14_38();
//	Exercise14_37();
//	Exercise14_36();
//	TestPrintString();
//	Exercise14_32();
//	testStr();
//	Exercise14_16();
//	Exercise14_10();
//	Exercise14_5();
//	return 0;
//}