#pragma once
#include "abst_games.h"
#include <iostream>


class breakout : public abst_games
{
public:
	//constructors
	breakout() = default;
	breakout(int value) : m_value(value), m_is_active(true) {}
	

	~breakout() = default;




	//methods
	
	

	//gets and sets 
	inline int get_x_pos() const { return x_pos; }
	inline int get_y_pos() const { return y_pos; }
	int set_x_pos(int x) { return x_pos = x; }
	int set_y_pos(int y) { return y_pos = y; }

	inline bool get_is_active() const { return m_is_active; }
	bool set_is_active(bool value) { return m_is_active = value; }

private:
	//variables
	int m_width = 70, m_height = 5;
	int m_value;
	bool m_is_active = false;


};

