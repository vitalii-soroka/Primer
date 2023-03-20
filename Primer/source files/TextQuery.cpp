#include "TextQuery.h"

using std::string;
using std::istringstream;
using std::set;
using std::ostream;
using std::shared_ptr;
using std::endl;

namespace chapter10 {
    string make_plural(size_t sz, const string& word, const string& ending)
    {
        return (sz > 1) ? word + ending : word;
    }
    TextQuery::TextQuery(std::ifstream& is) : file(new std::vector<std::string>) {
        string text;
        while (getline(is, text)) {
            file->push_back(text);
            int n = file->size() - 1;

            istringstream line(text);
            string word;
            while (line >> word) {
                auto& lines = wm[word];
                // pointer is null first time value written
                if (!lines) {
                    lines.reset(new set<line_no>);
                }
                lines->insert(n);
            }
        }
    }
    QueryResult TextQuery::query(const string& sought) const {
        // will return pointer to no data obj if not found
        static shared_ptr<set<line_no>> nodata(new set<line_no>);
        auto loc = wm.find(sought);

        if (loc == wm.end()) {
            return QueryResult(sought, nodata, file);
        }
        else
            return QueryResult(sought, loc->second, file);
    }
    ostream& print(std::ostream& os, const QueryResult& qr) {

        os << qr.sought << " occurs " << qr.lines->size() << ' '
            << (qr.lines->size() > 1 ? " times" : " time") << endl; // make_plural(qr.lines->size(), "time", "s")
        for (auto num : *qr.lines) {
            os << "\t (line " << num + 1 << ") " << *(qr.file->begin() + num) << endl;
        }
        return os;
    }
}