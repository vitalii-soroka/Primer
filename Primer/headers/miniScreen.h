#pragma once
#include <string>
struct miniScreen {
	using pos = std::string::size_type;
	using Action = miniScreen & (miniScreen::*)();
	enum Directions { HOME, FORWARD, BACK, UP, DOWN };

	miniScreen() = default;

	char get_cursor() const { return contents[cursor]; }
	// temp
	char get(pos x, pos y) const { return contents[x * width + y]; }

	miniScreen& move(Directions);

	miniScreen& home() { cursor = 0;  return *this; }
	miniScreen& forward() { return *this; }
	miniScreen& back() { return *this; }
	miniScreen& up() { return *this; }
	miniScreen& down() { return *this; }
	//
private:
	pos cursor = 0;
	pos height = 10;
	pos width = 10;
	std::string contents = "123412341234";
	static Action Menu[]; // function table
};

miniScreen& miniScreen::move(Directions cm) {
	return (this->*Menu[cm])(); // points to a member function
}

miniScreen::Action miniScreen::Menu[] = {
	&miniScreen::up,
	&miniScreen::home,
	&miniScreen::back,
	&miniScreen::down,
	&miniScreen::forward
};
