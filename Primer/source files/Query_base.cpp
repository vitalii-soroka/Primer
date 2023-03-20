#include "Query_base.h"
#include <algorithm>


namespace chapter15 {

    std::ostream& operator<<(std::ostream& os, const Query& q)
    {
        return os << q.rep();
    }

    chapter15::Query operator~(const  chapter15::Query& operand)
    {
        return std::shared_ptr<Query_base>(new NotQuery(operand));
    }

    chapter15::Query operator&(const  chapter15::Query& lhs, const  chapter15::Query& rhs)
    {
        return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
    }

    chapter15::Query operator|(const  chapter15::Query& lhs, const  chapter15::Query& rhs)
    {
     
        return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
    }

    chapter15::Query::Query(const std::string& s) : q(new WordQuery(s)) {}

    QueryResult  chapter15::NotQuery::eval(const TextQuery& text) const
    {

        auto result = query.eval(text);
        auto ret_lines = std::make_shared<std::set<line_no>>();
        auto beg = result.begin(), end = result.end();
        auto sz = result.get_file()->size();

        for (size_t n = 0; n != sz; ++n) {
            if (beg == end || *beg != n) {
                ret_lines->insert(n);
            }
            else if (beg != end) ++beg;
        }

        return QueryResult(rep(), ret_lines, result.get_file());
    }

    QueryResult  chapter15::AndQuery::eval(const TextQuery& text) const
    {
        auto right = rhs.eval(text), left = lhs.eval(text);
        auto ret_lines = std::make_shared<std::set<line_no>>();
        std::set_intersection(left.begin(), left.end(),
            right.begin(), right.end(), std::inserter(*ret_lines, ret_lines->begin()));
        return QueryResult(rep(), ret_lines, left.get_file());
    }

    QueryResult  chapter15::OrQuery::eval(const TextQuery& text) const
    {
        auto right = rhs.eval(text), left = lhs.eval(text);
        auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
        ret_lines->insert(right.begin(), right.end());
        return QueryResult(rep(), ret_lines, left.get_file());
    }
}