#include <iostream>
#include <memory>
#include <vector>
#include "Quote.h"
#include "Basket.h"
#include "MyGeometry.h"
#include "Query_base.h"

void Exercise15_6() {
	Quote quote("q_book", 50);
	Bulk_quote bulk_quote("bq_book", 50, 3, 0.5);

	print_total(std::cout, quote, 4);
	print_total(std::cout, bulk_quote, 4);
}
void Exercise15_7() {
	Bulk_quote bulk_quote("bq_book", 100, 2, 0.5);
	Limit_quote limit_quote("li_book", 100, 2, 0.5, 4);

	print_total(std::cout, bulk_quote, 10);
	print_total(std::cout, limit_quote, 10);
}
void Exercise15_11() {
	Quote quote("q_book", 50);
	Bulk_quote bulk_quote("bq_book", 100, 2, 0.5);
	Limit_quote limit_quote("li_book", 100, 2, 0.5, 4);

	quote.debug(std::cout) << std::endl;
	bulk_quote.debug(std::cout) << std::endl;
	limit_quote.debug(std::cout) << std::endl;

}
void Exercise15_21() {
	//std::cout << check_rect({0,0}, {0,1}, {1,1}, {1,0}) << std::endl;
	Rectangle rect1("Rectangle", { 0,0 }, { 0,25 }, { 100,25 }, { 25,0 });
	//Rectangle rect2("incorrect rect",{ 0, 0 }, {0,1}, {1,1}, {100,0});
	Quadrangle quad1("Quadrangle", { 0, 0 }, { 0,25 }, { 25,25 }, { 25,0 });

	rect1.print_info(std::cout) << std::endl << "\t perimeter: " << rect1.perimeter() << std::endl;
	quad1.print_info(std::cout) << std::endl << "\t perimeter: " << quad1.perimeter() << std::endl;
}
void Exercise15_26() {
	std::cout << "Bulk_quote empty declaration" << std::endl;
	Bulk_quote quote;

	std::cout << "Bulk_quote copy declaration" << std::endl;
	Bulk_quote quote_copy(quote);

	std::cout << "Bulk_quote move declaration" << std::endl;
	Bulk_quote quote_move(std::move(quote));

	std::cout << "Quote pointer to Bulk Quote" << std::endl;
	Quote* pquote = new Bulk_quote; Quote q;
	pquote->debug(std::cout) << std::endl;
	q.debug(std::cout) << std::endl;

}
void Exercise15_28_29() {
	std::vector<Quote> qve; qve.reserve(5);
	qve.push_back(Quote("book", 10));
	qve.push_back(Bulk_quote("book", 10, 5, 0.4));
	for (const auto& q : qve) std::cout << q.net_price(8) << std::endl;

	std::cout << std::endl;

	std::vector<std::shared_ptr<Quote>> qvec;
	qvec.push_back(std::make_shared<Quote>("book", 10));
	qvec.push_back(std::make_shared<Bulk_quote>("book", 10, 5, 0.4));
	for (const auto& q : qvec) std::cout << q->net_price(8) << std::endl;
}
void Exercise15_30() {
	Basket basket;
	basket.add_item(Quote("GH789", 10));
	basket.add_item(Bulk_quote("KJ891", 10, 1, 0.5));
	basket.add_item(Bulk_quote("KJ891", 10, 1, 0.5));
	basket.add_item(Bulk_quote("KJ891", 10, 1, 0.5));
	basket.total_receipt(std::cout);
}
void Exercise15_34() {
	const std::string hello = "hello";
	Query q(hello);
	TextQuery tq();
	std::ifstream fs("text.txt");
	print(std::cout, q.eval(fs));
	std::cout << q;	
}
void Exercise15_39() {
	
	std::ifstream fs("text.txt");
	TextQuery tq(fs);

	Query q = ~Query("Alice"); 
	print(std::cout, q.eval(tq));
	q = Query("Alice") & Query("Emma");
	print(std::cout, q.eval(tq));
	q = Query("Alice") | Query("hair");
	print(std::cout, q.eval(tq));
}
void Exercise15_42() {

}
//
//int main() {
//	
//	Exercise15_39();
//	Exercise15_34();
//	Exercise15_30();
//	//Exercise15_28_29();
//	// ++
//	//Exercise15_26(); 
//	
//	//Exercise15_21();
//	//Exercise15_11();
//	//Exercise15_7();
//	//Exercise15_6();
//	return 0;
//}