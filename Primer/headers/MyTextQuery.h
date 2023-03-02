#pragma once
#ifndef MY_TEXT_QUERY_H
#define MY_TEXT_QUERY_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <string>
#include "DebugDelete.h">


using line_no = std::vector<std::string>::size_type;
class MyQueryResult;
class MyTextQuery {
public:
	MyTextQuery(std::ifstream&);
	MyQueryResult query(const std::string&) const;

private:
	std::shared_ptr<std::vector<std::string>> file;

	std::map<std::string,
		std::shared_ptr<std::set<line_no>>> wm;

};
class MyQueryResult {
	friend std::ostream& print(std::ostream&, const MyQueryResult&);
public:
	MyQueryResult(std::string s,
		std::shared_ptr<std::set<line_no>> p,
		std::shared_ptr<std::vector<std::string>> f) : 
		sought(s), lines(new std::set<line_no>(*p),DebugDelete()), file(f) {};


private:
	std::string sought;
	std::shared_ptr < std::set<line_no>> lines;
	std::shared_ptr < std::vector<std::string>> file;
}; 

#endif // !MY_TEXT_QUERY_H