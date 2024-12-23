#pragma once
#include <iostream>
#include <Windows.h>



class game_window
{
public:
	//constructors
	game_window() = default;
	~game_window() = default;

	//methods
	void create_window(const int width, const int height);
	void set_cursor(const int x, const int y);


	//gets and sets
	inline int get_width() const { return m_width; } 
	inline int get_height() const { return m_height; }

private:
	//variables
	int m_width, m_height;
	HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);

};

