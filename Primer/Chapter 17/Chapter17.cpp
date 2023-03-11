#include <iostream>
#include <tuple>
#include <vector>
#include <bitset>		
#include <string>
#include <algorithm>	// equal_range
#include <numeric>      // accumulate
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

/* ---------------- Exercise 17.8 --------------- */
void Exercise17_8() {
	// incorrect addition, due to Sales_data() - init empty object
	// ISBN will be different from one we found
	// and + works only if ISBN are same
}
/* ---------------- Exercise 17.9 --------------- */
void Exercise17_9() {
	// bitset of 64 bits, 32  initialized, else 0...(100000)
	std::bitset<64> bitvec(32);
	std::cout << bitvec.to_string() << std::endl;

	// bitset of 32 bits, 20 initialized, else 0...(11110110100110110101)
	std::bitset<32> bv(1010101);
	std::cout << bv.to_string() << std::endl;

	// takes string from input, crop to 8 bits
	std::string bstr;	
	std::cin >> bstr;
	std::bitset<8>bvs(bstr);
	std::cout << bvs.to_string() << std::endl;
}
/* ---------------- Exercise 17.10 --------------- */
void Exercise17_10() {
	std::bitset<64> bset;		 
	std::pair<size_t, size_t> prev{ 1,2 }; // pair of n-1 and n-2 elements
	bset.set(0);						   // initial indexes
	bset.set(1);
	size_t n = 3; 	                       // index of next bit index
	while (n < bset.size()) {
		prev.first = prev.second;
		prev.second = n;
		bset.set(n - 1);				   // -1 for indexes from 0
		n = prev.first + prev.second;	   // updating index
	}
	std::cout << "Fibonacci bits: " << bset.to_string() << std::endl;
}
/* ------------ Exercise 17.11-12-13 ------------- */

template <std::size_t _size_t>
struct Quiz {
	Quiz() = default;
	Quiz(const std::string& answ) : answers(answ) {}
	Quiz(unsigned long long num) : answers((std::string)num) {}

	std::ostream& print(std::ostream& os) const  {
		/*for (size_t i = 0; i != _size_t; ++i) 
			os << i + 1 << " ";

		os << std::endl;

		for (size_t i = 0; i != _size_t; ++i)
			os << (answers.test(i) ? 'Y' : 'N') << " ";
		return os;*/
		os << answers.to_string();
		return os;
	}
	bool check(std::size_t i, bool expected = true) const  {
		return expected == answers.test(i);
	}
	void update(std::size_t i, bool expected = true) {
		answers.set(i, expected);
	}
	bool check_and_update(std::size_t i, bool expected = true) {
		bool ret = check(i, expected);
		if (!ret) answers.flip(i);
		return ret;
	}

	std::size_t size() const { return answers.size(); }
private:
	std::bitset<_size_t> answers;
};

// grade method 
template <std::size_t _size_t>
std::pair<std::size_t,std::size_t>
get_grade(Quiz<_size_t> a, Quiz<_size_t> b) {

	std::size_t grade = 0;
	for (std::size_t i = 0; i != _size_t; ++i) {
		if (a.check(i) == b.check(i)) ++grade;
	}
	return std::make_pair(grade,_size_t);
}

void Exercise17_11_12_13() {
	//10-11
	Quiz<10> quiz("1000110001");
	quiz.print(std::cout) << std::endl;

	// 12 / 13
	Quiz<10> answers("1010110101");
	answers.print(std::cout) << std::endl;
	auto grades = get_grade(quiz, answers);
	std::cout << "Results: " << grades.first
		<< " / " << grades.second << std::endl;



}

/* ---------------- Exercise 17.10 --------------- */

int main() {
	Exercise17_11_12_13();
	Exercise17_10();
	Exercise17_9();
}