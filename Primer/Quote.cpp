#include "Quote.h"

double print_total(std::ostream& os, const Quote& item, size_t n) {
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn()
		<< " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}
//
// Quote
//
Quote::Quote() : bookNo(""),price (0.0) {
	std::cout << "\tQuote() called" << std::endl;
}
Quote::Quote(const Quote& q) : bookNo(q.bookNo), price(q.price){
	std::cout << "\tQuote(const Quote&) called" << std::endl;
}
Quote::Quote(Quote&& q) noexcept : bookNo(std::move(q.bookNo)), price(std::move(q.price)){
	std::cout << "\tQuote(Quote&& q) called" << std::endl;
}
Quote& Quote::operator=(const Quote& rhs){

	std::cout << "\toperator=(const Quote&) called" << std::endl;

	if (this != &rhs) {
		bookNo = rhs.bookNo;
		price = rhs.price;
	}

	return *this;
}
Quote& Quote::operator=(Quote&& rhs) noexcept{
	std::cout << "\toperator=(Quote&&) called" << std::endl;
	if (this != &rhs) {
		bookNo = std::move(rhs.bookNo);
		price = std::move(rhs.price);
	}
	return *this;
}
std::ostream& Quote::debug(std::ostream& os) const
{
	return os << "ISBN: " << bookNo << std::endl <<
		"\t price: " << price;
}
//
// Disc_quote
//
Disc_quote::Disc_quote() : Quote(), quantity(0),discount(0.0) { 
	std::cout << "\tDisc_Quote called" << std::endl;
}
Disc_quote::Disc_quote(const Disc_quote& dq) : 
	Quote(dq), quantity(dq.quantity), discount(dq.discount) 
{
	std::cout << "\tDisc_quote(const Disc_quote&) called" << std::endl;
}
Disc_quote::Disc_quote(Disc_quote&& dq) noexcept  :
	Quote(std::move(dq)), quantity(std::move(dq.quantity)), discount(std::move(dq.discount))
{
	std::cout << "\tDisc_quote(Disc_quote&&) called" << std::endl;
}
Disc_quote& Disc_quote::operator=(const Disc_quote& rhs) {
	std::cout << "\toperator=(const Disc_quote&) called" << std::endl;
	if (&rhs != this) {
		Quote::operator=(rhs);
		quantity = rhs.quantity;
		discount = rhs.discount;
	}
	return *this;
}
Disc_quote& Disc_quote::operator=(Disc_quote&& rhs) noexcept  {
	std::cout << "\toperator=(Disc_quote&&) called" << std::endl;
	if (&rhs != this) {
		Quote::operator=(std::move(rhs));
		quantity = std::move(rhs.quantity);
		discount = std::move(rhs.discount);
	}
	return *this;
}
//
// Bulk_quote
//
Bulk_quote::Bulk_quote() : Disc_quote() {
	std::cout << "\tBulk_quote() called" << std::endl;
}
Bulk_quote::Bulk_quote(Bulk_quote&& bq) noexcept : Disc_quote(std::move(bq)) {
	std::cout << "\tBulk_quote(Bulk_quote&&) called" << std::endl;
}
Bulk_quote::Bulk_quote(const Bulk_quote& bq) : Disc_quote(bq) {
	std::cout << "\tBulk_quote(const Bulk_quote&) called" << std::endl;
}
Bulk_quote& Bulk_quote::operator=(const Bulk_quote& rhs) {
	std::cout << "\toperator=(const Bulk_quote& rhs) called" << std::endl;
	Disc_quote::operator=(rhs);
	return *this;
}
Bulk_quote& Bulk_quote::operator=(Bulk_quote&& rhs) noexcept {
	std::cout << "\toperator=(Bulk_quote&&) called" << std::endl;
	Disc_quote::operator=(std::move(rhs));
	return *this;
}
double Bulk_quote::net_price(std::size_t cnt) const
{
	if (cnt >= quantity)
		return cnt * (1 - discount) * price;
	return cnt * price;
}
std::ostream& Bulk_quote::debug(std::ostream& os) const
{
	return this->Quote::debug(os) << std::endl <<
		"\t min_qty: " << quantity << std::endl <<
		"\t discount: " << discount;
}
//
// Limit_quote
//
double Limit_quote::net_price(std::size_t cnt) const
{
	if (cnt <= quantity)
		return cnt * (1 - discount) * price;
	else
		return quantity * (1 - discount) * price + (cnt - quantity) * price;
}
std::ostream& Limit_quote::debug(std::ostream& os) const
{
	return this->Quote::debug(os) << std::endl <<
		"\t min_qty: " << quantity << std::endl <<
		"\t discount: " << discount << std::endl <<
		"\t max_qty: " << max_qty;

}