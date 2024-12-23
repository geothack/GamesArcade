#pragma once
class abst_games
{
protected:
	//methods
	virtual void update_game(int index) {}
	virtual void game_inputs(int index) {}


	//deconstructor
	virtual ~abst_games() {}


protected:
	//variables
	int x_pos, y_pos;
	bool is_active;
};

