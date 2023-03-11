#include <iostream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include "Sales_data.h"

/* -------------------------------- Tuple ----------------------------------

----------------------------------------------------------------------------*/

void Exercise17_1_2() {
	std::tuple<int, int, int> int_tuple{ 10,20,30 };
	using std::string;
	std::tuple<string,
			std::vector<string>, 
			std::pair<string, 
			int>> complex_tuple;

}
void Exercise17_3() {
	// later
}

/* ---------------- Exercise 17.4 --------------- */
// index of store
typedef std::tuple<std::vector<Sales_data>::size_type,
	std::vector<Sales_data>::const_iterator,
	std::vector<Sales_data>::const_iterator> matches;

std::vector<matches>
findBook(const std::vector<std::vector<Sales_data>>& files,
	const std::string& book) {
	std::vector<matches> ret; // initially empty
	// for each store find the range of matching books, if any
	for (auto it = files.cbegin(); it != files.cend(); ++it) {
		// find the range of Sales_data that have the same ISBN
		auto found = std::equal_range(it->cbegin(),
			it->cend(),
			book,
			compareIsbn);
		if (found.first != found.second) {
			ret.push_back(std::make_tuple(it - files.cbegin(),
				found.first,
				found.second));
		}
	}
	return ret; // empty if no matches found
}

void reportResults(std::istream& in, std::ostream& os,
	const std::vector<std::vector<Sales_data>> &files) {
	std::string s; // book to look for

	while (in >> s) {
		auto trans = findBook(files, s); // stores that sold this book
		if (trans.empty()) {
			std::cout << s << " not found in any stores" << std::endl;
			continue;
		}
		for (const auto& store : trans) { // for every store with a sale
			// get <n> return member from the tuple in store
			os << "store " << std::get<0>(store) << " sales: "
				<< std::accumulate(std::get<1>(store), std::get<2>(store),
					Sales_data(s))
				<< std::endl;
		}
	}
}

void Exercise17_4() {

}

/* ---------------- Exercise 17.5 --------------- */
typedef std::pair<std::vector<Sales_data>::size_type,
	std::pair<std::vector<Sales_data>::const_iterator,
	std::vector<Sales_data>::const_iterator>> pair_matches;

std::vector<pair_matches>
pair_findBook(const std::vector<std::vector<Sales_data>>& files,
	const std::string& book) {
	std::vector<pair_matches> ret; //empty

	for (auto it = files.cbegin(); it != files.cend(); ++it) {
		
		auto found = std::equal_range(it->cbegin(),
			it->cend(), book, compareIsbn);
		if (found.first != found.second) {
			ret.push_back(std::make_pair(it - files.cbegin(),
				std::make_pair(found.first,found.second)));
		}
	}
	return ret;
}

void Exercise17_5() {

}

/* ---------------- Exercise 17.6 --------------- */
template <typename _size_t, typename _It>
struct my_match {
	my_match(_size_t i, _It b, _It e) 
		: index(i), begin(b), end(e) {}
	
	_It begin, end;
	size_t index;
};

typedef my_match <std::vector<Sales_data>::size_type,
	std::vector<Sales_data>::const_iterator> my_matches;

std::vector<my_matches>
without_findBook(std::vector<std::vector<Sales_data>>& files,
	const std::string& book) {
	std::vector<my_matches> ret; //empty

	for (auto it = files.cbegin(); it != files.cend(); ++it) {
		auto found = std::equal_range(it->cbegin(),it->cend(),
			book /* Sales_data < operator used */);
		if (found.first != found.second) {
			my_matches match(it - files.cbegin(),found.first,found.second);
			ret.push_back(match);
		}
	}
	return ret;
}

void Exercise17_6() {

}

/* ---------------- Exercise 17.7 --------------- */
void Exercise17_7() {
	// prefer tuple version, it's easier to write, understand and read
}

/* ---------------- Exercise 17.7 --------------- */
void Exercise17_8() {
	// incorrect addition, due to Sales_data() - init empty object
	// ISBN will be different from one we found
	// and + works only if ISBN are same
}

int main() {

}