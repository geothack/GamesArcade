#pragma once
#include <Windows.h>
#include "abst_games.h"


class game_bullet : public  abst_games
{
public:
	//constructors
	game_bullet();
	~game_bullet() = default;


	//methods
	void game_inputs(int index) override;
	void update_game(int index) override;



	//gets and sets
	int set_x_pos(int x) { return x_pos = x; }
	int set_y_pos(int y) { return y_pos = y; }
	inline int get_x_pos() const { return x_pos; }
	inline int get_y_pos() const { return y_pos; }

	inline bool get_is_active() const { return is_active; }
	bool set_is_active(bool value) { return is_active = value; }
	inline int get_speed_x() const { return m_speed_x; }
	int set_speed_x(int value) { return m_speed_x = m_speed_x * value; }
	inline int get_speed_y() const { return m_speed_y; }
	int set_speed_y(int value) { return m_speed_y = m_speed_y * value; }

	inline bool get_is_flying() const { return m_is_flying; }
	bool set_is_flying(bool value) { return m_is_flying = value; }

private:
	//variables 
	bool  m_is_flying;
	
	int m_speed_x = 1, m_speed_y = -1;


	



};

