#pragma once
#include "TextQuery.h"

using chapter10::TextQuery;
using chapter10::QueryResult;

namespace chapter15 {

	class Query_base {
		friend class Query;
	protected:
		using line_no = TextQuery::line_no;

		virtual ~Query_base() = default;
	private:
		virtual QueryResult eval(const TextQuery&) const = 0;
		virtual std::string rep() const = 0;
	};

	// interface class to manage the Query_base inheritance hierarchy
	class Query {
		friend std::ostream& operator<<(std::ostream&, const Query&);
		friend Query operator~(const Query&);
		friend Query operator|(const Query&, const Query&);
		friend Query operator&(const Query&, const Query&);
		//friend std::ostream& operator<<(std::ostream&, const Query&);
	public:
		Query(const std::string& s);

		QueryResult eval(const TextQuery& t) const { return q->eval(t); }
		std::string rep() const { return q->rep(); }
	private:
		Query(std::shared_ptr<Query_base> query) : q(query) {}
		std::shared_ptr<Query_base> q;
	};

	class WordQuery : public Query_base {
		friend class Query;
	public:
		explicit WordQuery(const std::string& s) : query_word(s) {}
		QueryResult eval(const TextQuery& t) const override { return t.query(query_word); }
		std::string rep() const override { return query_word; }

		std::string query_word;
	};

	class NotQuery : public Query_base {
		friend Query operator~(const Query&);

		NotQuery(const Query& q) : query(q) {}
		std::string rep() const { return "~(" + query.rep() + ")"; }

		QueryResult eval(const TextQuery&) const override;
		Query query;

	};

	class BinaryQuery : public Query_base {
	protected:
		BinaryQuery(const Query& l, const Query& r, std::string s) :
			lhs(l), rhs(r), opSym(s) {}
		std::string rep() const {
			return "(" + lhs.rep() + " "
				+ opSym + " "
				+ rhs.rep() + ")";
		}

		Query lhs, rhs;		// right and left hand operands
		std::string opSym;	// name of operator
	};

	class AndQuery : public BinaryQuery {
		friend Query operator& (const Query&, const Query&);
	public:
		AndQuery(const Query& left, const Query& right) : BinaryQuery(left, right, "&") {}

		// concrete class : AndQuery inherits rep and defines pure virtual
		QueryResult eval(const TextQuery&) const;

	};

	class OrQuery : public BinaryQuery {
		friend Query operator| (const Query&, const Query&);
	public:
		OrQuery(const Query& left, const Query& right) :
			BinaryQuery(left, right, "|") {}
		QueryResult eval(const TextQuery&) const;
	};
}