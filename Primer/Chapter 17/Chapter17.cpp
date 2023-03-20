#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <fstream>		// file stream

#include <random>
#include <tuple>
#include <bitset>		
#include <regex>        // regular expressions
#include <iomanip>      // io manipulators that takes arguments

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
	const std::vector<std::vector<Sales_data>>& files) {
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
				std::make_pair(found.first, found.second)));
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
		auto found = std::equal_range(it->cbegin(), it->cend(),
			book /* Sales_data < operator used */);
		if (found.first != found.second) {
			my_matches match(it - files.cbegin(), found.first, found.second);
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

	std::ostream& print(std::ostream& os) const {
		/*for (size_t i = 0; i != _size_t; ++i)
			os << i + 1 << " ";

		os << std::endl;

		for (size_t i = 0; i != _size_t; ++i)
			os << (answers.test(i) ? 'Y' : 'N') << " ";
		return os;*/
		os << answers.to_string();
		return os;
	}
	bool check(std::size_t i, bool expected = true) const {
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
std::pair<std::size_t, std::size_t>
get_grade(Quiz<_size_t> a, Quiz<_size_t> b) {

	std::size_t grade = 0;
	for (std::size_t i = 0; i != _size_t; ++i) {
		if (a.check(i) == b.check(i)) ++grade;
	}
	return std::make_pair(grade, _size_t);
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

/* -------------------------- Regular Expression ----------------------------
	Syntactic correctness of a regular expression is evaluated at a run time
--
	compiling regular expression can be a surprisingly slow operation.
	avoid creating more regex object that needed,
	f.e - create outside the loop
----------------------------------------------------------------------------*/
void regular_Expression() {
	// find ei follow any character except c
	std::string pattern("[^c]ei");
	// whole word in which pattern appears
	pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
	std::regex reg(pattern, std::regex::icase);
	std::smatch results;		// object to hold the result
	// test string
	std::string test_str = "receipt freind object to hold the result theif";
	for (std::sregex_iterator
		it(test_str.begin(), test_str.end(), reg),
		end_it; it != end_it; ++it)
	{
		auto pos = it->prefix().length();   // size of prefix
		pos = pos > 40 ? pos - 40 : 0;		// we want up to 40 characters
		std::cout << it->prefix().str().substr(pos)  // last part of the suffix
			<< "\n\t\t>>> " << it->str() << " <<<\n" // matched word
			<< it->suffix().str().substr(0, 40)
			<< std::endl;
	}

	//if (std::regex_search(test_str, results, reg)) { // if match
	//	std::cout << results.str() << std::endl;
	//}
}
void regex_file_search() {
	std::regex reg("([[:alnum:]]+)\\.(cpp|cxx|cc)$", std::regex::icase);
	std::smatch result;
	std::string filename;
	while (std::cin >> filename) {
		if (std::regex_search(filename, result, reg)) {
			std::cout << result.str(1) << std::endl; // print current match
		}
	}
}
void regex_error_test() {
	try {
		// missing ] bracket, throws regex_error
		std::regex r("[[:alnum:]+\\.(cpp|cxx|cc)$", std::regex::icase);
	}
	catch (std::regex_error e) {
		std::cout << e.what() << "\ncode: " << e.code() << std::endl;
	}
}

/* ---------------- Exercise 17.15-16 --------------- */
void regex_read_check(const std::string& pattern, const std::string& name = "") {
	//std::string pattern, input;
	//pattern = "[[:alpha:]]*[^c]ei[[:alpha:]]*";
	std::string input;
	std::regex reg(pattern);
	std::smatch result;
	while (std::cin >> input) {
		std::cout << "word"
			<< (std::regex_match(input, result, reg) ? " " : " doesn't")
			<< " contains " << name << " rule" << std::endl;
	}
}
void Exercise17_15() {
	std::string pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
	regex_read_check(pattern, "..[^c]ei..");
}
void Exercise17_16() {
	regex_read_check("[^c]ei", "[^cei]");
}

/* ---------------- Exercise 17.18 --------------- */
void Exercise17_18() {
	std::set<std::string> dict{ "albeit","neighbor" }; // set of ei
	std::string ei_pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
	std::string input("label movei albeit before freind after neighbor theif");

	std::regex reg(ei_pattern, std::regex::icase);
	std::smatch match;

	for (std::sregex_iterator end_it, it(input.begin(), input.end(), reg);
		it != end_it; ++it)
	{
		// if no word in dictionary - that's mistake
		if (dict.find(it->str()) != dict.end()) continue;
		// count index for suffix and prefix display size
		size_t pos = it->prefix().length();
		pos = pos > 5 ? pos - 5 : 0;

		std::cout
			<< it->prefix().str().substr(pos)
			<< it->str()
			<< it->suffix().str().substr(0, 5)
			<< std::endl;
	}
}

/* ---------------- Exercise 17.19 --------------- */
// Ex 17.19 It's okay to call m[4].str() without checking match, 
// because m[4] and m[6] should be equal, if no match then
// they both are equal

/* ---------------- Exercise 17.20 --------------- */
bool number_is_valid(const std::smatch& m) {

	std::regex r(" +"); // for any number of spaces
	
	if (m[1].matched)  // if open parenthesis before area code
		// the area must be followed by a close parenthesis
		// and followed immediately by the rest of the numbers or space
		return m[3].matched &&
		(m[4].matched == 0 || std::regex_match(m[4].str(), r));
	else
		// then there can't be a close after the area code
		// the delimiters between the others two components must match
		return !m[3].matched
		&& std::regex_match(m[4].str(), r)
		&& std::regex_match(m[6].str(), r);


	return true;
}
void numbers_test(const std::string& number) {
	std::string phone_pattern
		= "(\\()?(\\d{3})(\\))?([-.])?(\\d{3})([-.])?(\\d{4}))";

	std::regex reg(phone_pattern);
	std::smatch match;
	std::string line;

	// for each record
	while (std::getline(std::cin, line)) {
		// for each matching phone
		for (std::sregex_iterator it(line.begin(), line.end(), reg), end_it;
			it != end_it; ++it) {
			if (number_is_valid(*it)) {
				std::cout << "valid: " << it->str() << std::endl;
			}
			else {
				std::cout << "not valid: " << it->str() << std::endl;
			}
		}
	}
}

/* ---------------- Exercise 17.21 --------------- */
struct PeronInfo {
	std::string name;
	std::vector<std::string> phones;
};
void Exercise17_21_22() {

	PeronInfo person1; person1.name = "Bob"; person1.phones 
		= {"3806362733","(380)676-7893"};
	PeronInfo person2; person2.name = "David"; person2.phones 
		= {"(380)6768903","380  676 8789"};

	std::vector<PeronInfo> people{ person1,person2};

	// ex 17.22
	std::string pattern
		= "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	// ex 17.23
	std::string pattern2
		= "(\\()?(\\d{3})(\\))?(-|.| +)?(\\d{3})(-|.| +)?(\\d{4})";

	std::regex r(pattern2);
	std::smatch m;

	// to do --
	for (const auto& entry : people) { 
		//std::ostringstream formatted, badNums; //
		std::cout << entry.name << ": " << std::endl;
		for (const auto& num : entry.phones) {
				if (std::regex_match(num,m,r) && number_is_valid(m)) {
					std::cout << "\tvalid: " << m.str() << std::endl;
				}
				else {
					std::cout << "\tnot valid: " << num << std::endl;
				}
		}
			//if (!valid(num)) {
				// string in badNums
				//badNums << " " << num;
			//}
			//else
				//formatted << " ";// << format(num);
		}
	/*
		//if (badNums.str().empty()) // there were no bad numbers
		//	os << entry.name << " " // print the name
		//	<< formatted.str() << endl; // and reformatted numbers
		//else // otherwise, print the name and bad numbers
		//	cerr << "input error: " << entry.name << " invalid number(s) " << badNums.str() <<
		//	endl;
	
	}*/
}
void Exercise17_23() {
	std::string zip_pattern = "(\\d{5})([/. ]?)(\\d{4})?";
	std::regex r(zip_pattern);
	std::smatch sm;
	std::vector<std::string> zips{ "123451234","12345/","12345/1234","123"};

	for (const auto& zip : zips) {
		if (std::regex_match(zip, sm, r)) {
			std::cout << "zip is valid: " << sm.str() << std::endl;
		}
		else {
			std::cout << "zip is not valid: " << zip << std::endl;
		}
	}


}

/* ---------------- Exercise 17.24 --------------- */
void reg_rep_test() {
	std::string phone
		= "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	std::string fmt = "$2.$5.$7";

	std::regex r(phone);
	std::string number = "(908) 555-1800";
	std::cout << std::regex_replace(number, r, fmt) << std::endl;
}
void Exercise17_24() {
	std::string phone =
		"(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
	std::regex r(phone);
	std::smatch m;
	std::string s = "morgan (201)555-2368 862-555-0123";
	std::string fmt = "$2.$5.$7"; //
	// replace all occurncies 
	std::cout << std::regex_replace(s, r, fmt) << std::endl;

	using std::regex_constants::format_no_copy;
	std::cout << "no copy: " << std::regex_replace(s, r, fmt, format_no_copy) << std::endl;
	
}
/* ---------------- Exercise 17.25 --------------- */
void Exercise17_25() {
	std::string phone =
		"(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";

	std::regex r(phone);
	std::smatch m;
	std::string s = "morgan (201)555-2368 862-555-0123";
	std::string fmt = "$2.$5.$7"; //
	// replace first occurnce

	std::regex_search(s,m, r);
	std::cout << "first only: " << m.prefix().str()
		<< std::regex_replace(m.str(), r, fmt) <<
		std::endl;

	//std::cout << "first only: " << std::regex_replace(s, r, fmt,
	//	std::regex_constants::format_first_only) << std::endl;
}
/* ---------------- Exercise 17.26 --------------- */
void Exercise17_26() {
	// temp solution
	std::string phone =
		"(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";

	std::regex r(phone);
	std::smatch m;
	std::string morgan = "morgan (201)555-2368 862-555-0123 056-455-3214";
	std::string semen = "semen (201)555-2368";
	std::vector<std::string> phones{morgan,semen};
	std::string fmt = "$2.$5.$7"; //
	
	

	for (auto& p : phones) {
		bool f = true;
		
		for (std::sregex_iterator it(p.begin(), p.end(), r), next(it), end_it;
			it != end_it; ++it)
		{
			if (f) {
				std::cout << "without first: " << it->prefix().str();
				f = !f;
				if (++next == end_it) 
					std::cout << std::regex_replace(it->str(), r, fmt);
				continue;
			}
			std::cout << it->prefix() << std::regex_replace(it->str(), r, fmt);
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;
}
/* ---------------- Exercise 17.27 --------------- */
void Exercise17_27() {
	std::string zip("(\\d{5})([-. ])?(\\d{4})");
	std::regex r(zip);
	std::string codes("12345 1234 123451234 12345.1234");
	std::string fmt = "$1-$3";
	std::cout << std::regex_replace(codes, r, fmt) << std::endl;
}
/* -------------------------- Random Numbers -------------------------------
bernoulli_distribution
----------------------------------------------------------------------------*/
/* ---------------- Exercise 17.28 --------------- */
unsigned Exercise17_28(unsigned min = 0, unsigned max = 100) {
	// declare as static, to not generate same random number on every call 
	static std::default_random_engine e;
	static std::uniform_int_distribution<unsigned> u(min, max);
	return u(e);
}
/* ---------------- Exercise 17.28-30 --------------- */
unsigned Exercise17_29_30(
	unsigned seed = std::default_random_engine::default_seed,
	unsigned min = 0,
	unsigned max = 100) {

	static std::default_random_engine engine(seed);
	static std::uniform_int_distribution<unsigned> u(min, max);

	return u(engine);
}
/* ---------------- Exercise 17.31 --------------- */
// same values will be on every loop
/* ---------------- Exercise 17.33 --------------- */
// resp will be out of scope in while
/* ---------------- Exercise 17.33 --------------- */
// small version
void Exercise17_33() {
	static std::default_random_engine e(time(0));	// somewhat random
	// filling word map
	std::map<std::string, std::vector<std::string>> word_map;
	word_map["k"] = { "okay","ok","good" };
	word_map["y"] = { "why" };
	word_map["u"] = { "you","yuo"};
	word_map["thk"] = { "thanks", "thank you", "ty" };
	// sample text
	std::string text = "Are you k ? y dont u send me ? k thk";
	// stream to read words in string
	std::istringstream isstream(text);
	// each word
	std::string word;
	// while not end of string
	while (isstream >> word) {
		auto map_it = word_map.find(word);
		// no word in map if find == end iterator
		if (map_it != word_map.cend()) {
			std::uniform_int_distribution<unsigned> u(0, map_it->second.size() - 1);
			// i know about this extra space, i'm too lazy
			std::cout << " " << map_it->second[u(e)];
		}
		else
			std::cout << " " << word;
	}
	std::cout << std::endl;
}
/* -------------------------- IO Library Revisited -------------------------------
endl is manipulator, writes newline and flush the buffer
--
hex, oct, dec affects only integral operands; floating point values is unaffected
--
setprecision and other manipulators that takes arguments are defined in the
iomanip header
--
unless you need to control the presentation of floating number,(money, percentage),
usually best let the libraty choose the notation
--
setw, like endl doesn't change the internal state of output stream.
----------------------------------------------------------------------------*/

/* ---------------- Exercise 17.34 ----------------- */
void formatIO_test() {

	std::cout << 10.0 << std::endl;
	std::cout << std::showpoint << 10.0 << std::noshowpoint << std::endl;

	std::cout << "default format: " << 100 * std::sqrt(2.0) << '\n'
		<< "scientific: " << std::scientific << 100 * std::sqrt(2.0) <<
		'\n'
		<< "fixed decimal: " << std::fixed << 100 * std::sqrt(2.0) <<
		'\n'
		<< "hexadecimal: " << std::hexfloat << 100 * std::sqrt(2.0) <<
		'\n'
		<< "use defaults: " << std::defaultfloat << 100 * std::sqrt(2.0) <<
		"\n\n";


	std::cout << "Precision: " << std::cout.precision()
		<< ", Value: " << std::sqrt(2.0) << std::endl;

	std::cout.precision(12);
	std::cout << "Precision: " << std::cout.precision()
		<< ", Value: " << std::sqrt(2.0) << std::endl;

	std::cout << std::setprecision(3);
	std::cout << "Precision: " << std::cout.precision()
		<< ", Value: " << std::sqrt(2.0) << std::endl;

	std::cout << "default bool values: " << true << " " << false
		<< "\nalpha bool values: " << std::boolalpha
		<< true << " " << false << std::noboolalpha << std::endl;

	std::cout << std::uppercase << std::showbase;
	std::cout << "default: " << 20 << " " << 1024 << std::endl;
	std::cout << "octal: " << std::oct << 20 << " " << 1024 << std::endl;
	std::cout << "hex: " << std::hex << 20 << " " << 1024 << std::endl;
	std::cout << "decimal: " << std::dec << 20 << " " << 1024
		<< std::nouppercase << std::noshowbase << std::endl;
}
void padFormat_test() {
	char ch;
	std::cin >> std::noskipws;
	while (std::cin >> ch) {
		std::cout << ch;
	}
	std::cin >> std::skipws;

	int i = -16;
	double d = 3.14159;
	// pad the first column to use a minimum of 12 positions in the output
	std::cout << "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n';

	// pad the first column and left-justify all columns
	std::cout << std::left
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n'
		<< std::right;		// restore normal justification 

	// pad the first column and right-justify all collumns
	std::cout << std::right
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n';

	// pad the first column but put the padding internal to the field
	std::cout << std::internal
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << i << "next col" << '\n';

	// pad the first column, using # as the pad characters
	std::cout << std::setfill('#')
		<< "i: " << std::setw(12) << i << "next col" << '\n'
		<< "d: " << std::setw(12) << d << "next col" << '\n'
		<< std::setfill(' '); // restore the normal pad characters
}
/* ---------------- Exercise 17.35 ----------------- */
void Exercise17_35() {
	std::cout << "hexadecimal: " << std::uppercase
		<< std::hexfloat << 100 * sqrt(2.0)
		<< "\n\n" << std::defaultfloat << std::nouppercase;
}
/* ---------------- Exercise 17.36 ----------------- */
void Exercise17_36() {
	using std::setw;
	using std::left;
	using std::right;

	auto num = 100 * std::sqrt(2.0);

	std:: cout 
	<< left << setw(15) << "default:" << setw(25) << right << num << '\n'
	<< left << setw(15) << "scientific:" << std::scientific << setw(25) << right << num << '\n'
	<< left << setw(15) << "fixed decimal:" << setw(25) << std::fixed << right << num << '\n'
	<< left << setw(15) << "hexidecimal:" << setw(25) << std::hexfloat << right << num << '\n'
	<< left << setw(15) << "default float:" << setw(25) << std::defaultfloat << right << num
	<< "\n\n";

}
/* ---------------- Exercise 17.37-- ----------------- */
void unformatted_Input() {
	/*char ch;
	while (std::cin.get(ch)) 
		std::cout.put(ch);*/	
	int ch;
	while ((ch = std::cin.get()) != EOF) 
		std::cout.put(ch);
		
}
/* ---------------- Exercise 17.38 ----------------- */
void Exercise17_38() {
	std::ifstream file("data/text.txt");
	char p[32]; // using as array not pointer to array to output
	while (file.getline(p,32,' ')) { // read word until ' ' or up to 32 characters 
		std::cout << p << std::endl;
	}

}
/* ---------------- Exercise 17.39 ----------------- */
void Exercise17_39() {
	std::fstream inOut("data/marker.txt", std::fstream::ate | std::fstream::in | std::fstream::out);
	if (!inOut) {
		std::cerr << "Unable to open file!" << std::endl;
		throw EXIT_FAILURE;
	}
	// inOut is opened in ate mode, so it starts at the end
	auto end_mark = inOut.tellg();		// remember end of file pos
	inOut.seekg(0, std::fstream::beg);  // reposition to start of the file
	std::size_t cnt = 0;			    // accumulator for the byte count
	std::string line;					// hold each line of input
	// while haven't hit an error and still not end of file, get new line
	while (inOut && inOut.tellg() != end_mark && std::getline(inOut,line)) {
		cnt += line.size() + 1;			// +1 taking into account newline character '\n'
		auto mark = inOut.tellg();		// remember position 
		inOut.seekg(0, std::fstream::end);// set write marker to the end

		inOut << cnt;					// write length
		// print separator if not last line
		if (mark != end_mark) inOut << " ";

		inOut.seekg(mark);				// restore the read poisiton
	}
	inOut.seekg(0, std::fstream::end);
	inOut << "\n";
}
/* ---------------- Exercise 17.39 ----------------- */
void Exercise17_39_my() {
	std::fstream file("data/mymarker.txt", std::fstream::ate | std::fstream::in | std::fstream::out);
	if (!file) {
		std::cerr << "Can't open file!" << std::endl;
		return;
	}
	
	auto end_pos = file.tellg();  // end of file position
	file.seekg(0, std::fstream::beg); // set to start
	std::string line;
	std::size_t count = 0;

	while (file && file.tellg() != end_pos && std::getline(file,line)) {
		
		count += line.size() + 1;
		auto mark_pos = file.tellg();

		file.seekg(0, std::fstream::end);
		file << count;

		if (mark_pos != end_pos) file << " ";

		file.seekg(mark_pos);
	}
	file.seekg(0, std::fstream::end);
	file << '\n';
}

//int main() {
//
//	Exercise17_39_my();
//	//Exercise17_39();
//	Exercise17_38();
//	unformatted_Input();
//	Exercise17_36();
//	Exercise17_35();
//	padFormat_test();
//	/*formatIO_test();
//	Exercise17_33();
//	std::cout << Exercise17_28() << std::endl;
//	std::cout << Exercise17_28() << std::endl;
//	Exercise17_27();
//	Exercise17_26();
//	Exercise17_25();
//	Exercise17_24();
//	reg_rep_test();
//	Exercise17_23();
//	Exercise17_21_22();
//	regex_file_search();
//	Exercise17_18();
//	regular_Expression();
//	Exercise17_16();
//	Exercise17_15();
//	regex_error_test();
//	Exercise17_11_12_13();
//	Exercise17_10();
//	Exercise17_9();*/
//}