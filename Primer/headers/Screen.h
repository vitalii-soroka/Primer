#ifndef SCREEN_H
#define SCREEN_H

#pragma once
#include <string>
#include <iostream>

template<unsigned, unsigned> class Screen;

template<unsigned h, unsigned w>
std::ostream& operator<< (std::ostream&, const Screen<h,w>&);

template<unsigned _h, unsigned _w>
class Screen {
	typedef std::string::size_type pos;
	friend std::ostream& operator<< <_h,_w> (std::ostream&, const Screen<_h,_w>&);
public:
	Screen() = default;
	Screen(char c) : height(_h), width(_w), contents(_h* _w, c) {}

	char get() const { return contents[cursor]; }

	Screen& move(pos r, pos c);

private:
	pos cursor = 0;
	pos height, width;
	std::string contents;
};

template<unsigned _h,unsigned _w>
Screen<_h,_w>& Screen<_h,_w>::move(pos r, pos c) {
	pos row = r * width;
	cursor = row + c;	
	return* this;
}

template<unsigned h, unsigned w>
std::ostream& operator<<(std::ostream& os, const Screen<h,w>& screen) {

	for (auto i = 0; i < screen.height; ++i){
		os << screen.contents.substr(0, w) << std::endl;
	}
	return os;
}

#endif // SCREEN_H