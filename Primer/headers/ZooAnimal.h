#pragma once
class Endangered {
public:
	virtual void highlight() = 0;
	virtual ~Endangered() = default;
	double get_max_weight() const { return max_weight; }
private:
	double max_weight = 100.0;
};

class ZooAnimal {
public:
	explicit ZooAnimal(const std::string& name, bool onExhibit = false) : name(name), onExhibit(onExhibit) {}
	virtual void print() = 0;

	virtual ~ZooAnimal() { std::cout << "ZooAnimal::~ZooAnimal()" << std::endl; };
	double get_max_weight() const { return max_weight; }
private:
	std::string name;
	bool onExhibit;
	double max_weight = 400.0;
};

class Bear : public virtual ZooAnimal {
public:
	explicit Bear(const std::string& name, bool onExhibit) : ZooAnimal(name, onExhibit) {}
	virtual void toes() { std::cout << "Beard::toes" << std::endl; };
	virtual void print() { std::cout << "Bear::print" << std::endl; }

	~Bear() override { std::cout << "Bear::~Bear()" << std::endl; }
};

class Raccoon : public virtual ZooAnimal {
public:
	explicit Raccoon(const std::string& name, bool onExhibit) : ZooAnimal(name, onExhibit) {}

	~Raccoon() override { std::cout << "Raccon::~Raccon()" << std::endl; }
};

class Panda : public Bear, public Raccoon, public Endangered {
public:
	Panda(const std::string& name, bool onExhibit = false) : 
		ZooAnimal(name, onExhibit), Bear(name, onExhibit), 
		Raccoon(name, onExhibit), Endangered() {}
	void print() override { std::cout << "Panda::print" << std::endl; }
	void highlight() override { /**/ };
	void toes() override { std::cout << "Panda::toes" << std::endl; }
	void cuddle() const { /**/ }

	~Panda() final { std::cout << "Panda::~Panda()" << std::endl;}
};