#include <iostream>

class numbered {
public:
	numbered() : mysn(++last_id), name(""){}
	numbered(const std::string& s) : mysn(++last_id), name(s) {}
	numbered(const numbered& rhs):mysn(++last_id), name(rhs.name){}
	numbered& operator=(const numbered& rhs) { name = rhs.name; return *this; }

	void f();
private:
	static int last_id;
	std::string name;
	int mysn;
};