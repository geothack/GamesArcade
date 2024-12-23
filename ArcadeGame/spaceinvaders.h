#pragma once
#include "abst_games.h"
class spaceinvaders : public abst_games
{
public:
	//constructors
	spaceinvaders();
	~spaceinvaders() = default;

	//methods
	void update_game(int index) override;


	//gets and sets 
	inline int get_x_pos() const { return x_pos; }
	inline int get_y_pos() const { return y_pos; }
	int set_x_pos(int x) { return x_pos = x; }
	int set_y_pos(int y) { return y_pos = y; }

	inline bool get_is_active() const { return is_active; }
	bool set_is_active(bool value) { return is_active = value; }

	int set_speed(int s) { return m_speed = s; }

private:
	//variables 

	static int m_speed;




};

