#pragma once
#include <Windows.h>
#include "abst_games.h"



class game_player : public abst_games
{
public:
	//constuctors
	game_player();
	~game_player();


	//methods
	void game_inputs(int index) override;




	//gets and sets 
	int set_x_pos(int x) { return x_pos = x; }
	int set_y_pos(int y) { return y_pos = y; }
	inline int get_x_pos() const { return x_pos; }
	inline int get_y_pos() const { return y_pos; }

	inline bool get_is_active() const { return is_active; }
	inline int get_reset() const { return m_reset; }
	int set_reset(int value) { return m_reset = value; }


private:
	//variables
	int m_reset = 0;



};

