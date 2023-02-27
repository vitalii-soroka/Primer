#pragma once

#ifndef BASKET_H
#define BASKET_H
#include "Quote.h"
#include <memory>
#include <iostream>
#include <set>


class Basket {
public:
	Basket() = default;

	void add_item(const std::shared_ptr<Quote>& sale) { items.insert(sale); }
	// defined to prevent user from allocating shared ptr directly
	void add_item(const Quote&);
	void add_item(Quote&&);

	double total_receipt(std::ostream&) const;
private:
	static bool compare(const std::shared_ptr<Quote>& lhs,
		const std::shared_ptr<Quote>& rhs)
	{
		return lhs->isbn() < rhs->isbn();
	}
	// holds multiple quotes ordered by compare
	std::multiset<std::shared_ptr<Quote>, decltype(compare)*> items{ compare };
};

#endif // BASKET_H