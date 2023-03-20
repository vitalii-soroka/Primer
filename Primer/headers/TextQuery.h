#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <string>

namespace chapter10 {

	class QueryResult;
	class TextQuery {
	public:
		using line_no = std::vector<std::string>::size_type;
		TextQuery(std::ifstream&);
		QueryResult query(const std::string&) const;

	private:
		std::shared_ptr<std::vector<std::string>> file;

		std::map<std::string,
			std::shared_ptr<std::set<line_no>>> wm;

	};
	class QueryResult {
		using line_no = std::vector<std::string>::size_type;
		friend std::ostream& print(std::ostream&, const QueryResult&);
	public:
		QueryResult(std::string s,
			std::shared_ptr<std::set<line_no>> p,
			std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) {};

		std::set<line_no>::iterator begin() const { return lines->begin(); }
		std::set<line_no>::iterator end() const { return lines->end(); }
		std::shared_ptr<std::vector<std::string>> get_file() const { return file; }
	private:
		std::string sought;
		std::shared_ptr < std::set<line_no>> lines;
		std::shared_ptr < std::vector<std::string>> file;
	};
}