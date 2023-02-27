#pragma once
#include <string>
class Pal;

class Base {
	friend class Pal;
public:
	std::size_t size() const { return n; }
	void pub_mem();
protected:
	std::size_t n;
	int prot_mem;
private:
	char priv_mem;
};

class Derived : private Base {
public:
	using Base::size;
protected:
	using Base::n;
};

struct Pub_Derv : public Base {
	int f() { return prot_mem; }
	// char g() { return priv_mem; } // error: private inaccessible
};
struct Priv_Derv : private Base {
	int f1() const { return prot_mem; }
};

struct Derived_from_Public : public Pub_Derv{
	int use_base() { return prot_mem; }
};
struct Derived_from_Private : public Priv_Derv {
	// error: Base::prot_mem is private in Priv_Dev
	// int use_base() { return prot_mem;  } 
};

class Sneaky : public Base {
	friend void clobber(Sneaky&);
	friend void clobber(Base&);
	int j;
};
// ok: clobber can access the private and protected members in Sneaky obj
void clobber(Sneaky& s) { s.j = s.prot_mem = 0; }
// error: clobber can't access the protected members in Base
//void clobber(Base& s) { s.j = s.prot_mem = 0; }

class Pal {
public:
	// ok: Base is a friend of pal
	int f(Base b) { return b.prot_mem; }
	// error: Pal not friend of Sneaky
	// int f2(Sneaky s) { return s.j; }
	// ok: Pal is a friend of Base class - parent of Sneaky
	int f3(Sneaky s) { return s.prot_mem;}
};

class D2 : public Pal {
public:
	// int mem(Base b) { return b.prot_mem;} // error: friendship doesn't inherit
};