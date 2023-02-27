#pragma once
#include <iostream>
#include <string>

class Quote {
public:
	Quote();									// memberwise default initialize
	Quote(const Quote&);						// memberwise copy
	Quote(Quote&&) noexcept;					// memberwise move copy
	Quote& operator=(const Quote&);				// copy assign
	Quote& operator=(Quote&&) noexcept;			// move assign

	Quote(const std::string& book, double sales_price) :
		bookNo(book), price(sales_price) { }
	// returns a dynamically allocated copy of itself
	virtual Quote* clone() const& { return new Quote(*this); }
	virtual Quote* clone()&& { return new Quote(std::move(*this)); }

	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return n * price; }
	virtual std::ostream& debug(std::ostream&) const;

	virtual ~Quote() = default;
private:
	std::string bookNo;
protected:
	double price;

};

class Disc_quote : public Quote {
public:
	Disc_quote();
	Disc_quote(const Disc_quote&);
	Disc_quote(Disc_quote&&) noexcept;
	Disc_quote(const std::string& book, double price, std::size_t qty, double disc) :
		Quote(book, price), quantity(qty), discount(disc) {}

	Disc_quote& operator=(const Disc_quote&);
	Disc_quote& operator=(Disc_quote&&) noexcept;

	
	double net_price(std::size_t) const = 0;

	virtual ~Disc_quote() = default;
protected:
	std::size_t quantity;
	double discount;

};

class Bulk_quote : public Disc_quote {
public:
	Bulk_quote();
	// Bulk_quote(const std::string& book, double price, std::size_t qty, double disc) :
	//	Disc_quote(book, price, qty, disc) {}
	using Disc_quote::Disc_quote;

	Bulk_quote(const Bulk_quote&);
	Bulk_quote(Bulk_quote&&) noexcept;
	Bulk_quote& operator=(const Bulk_quote&);
	Bulk_quote& operator=(Bulk_quote&&) noexcept;

	Bulk_quote* clone() const& override { return new Bulk_quote(*this); }
	Bulk_quote* clone() && override { return new Bulk_quote(std::move(*this)); }

	~Bulk_quote() = default;

	double net_price(std::size_t) const override;
	std::ostream& debug(std::ostream&) const override;
};

class Limit_quote : public Disc_quote {
public:
	Limit_quote() = default;
	Limit_quote(const std::string& book, double p, std::size_t qty, double disc, int limit) :
		Disc_quote(book, p, qty, disc), max_qty(limit) {}

	double net_price(std::size_t) const override;
	std::ostream& debug(std::ostream&) const override;

private:
	std::size_t max_qty = 0;
};

double print_total(std::ostream&, const Quote&, size_t);
