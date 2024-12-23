#include "game_player.h"

game_player::game_player() 
{
	is_active = true;
}

game_player::~game_player()
{
}

void game_player::game_inputs(int index)
{
	switch (index)
	{
	case 1://breakout
		if (GetKeyState(65) & 0x8000)
		{
			if (x_pos > 1)
				x_pos -= 2;
		}
		else if (GetKeyState(68) & 0x8000)
		{
			if (x_pos < 79)
				x_pos += 2;
		}
		break;
		
	case 2:
		if (GetKeyState(65) & 0x8000)
		{
			if (x_pos > 1)
				x_pos--;
		}
		else if (GetKeyState(68) & 0x8000)
		{
			if (x_pos < 79)
				x_pos++;
		}
		break;
	case 3: //pong
		if (GetKeyState(87) & 0x8000)
		{
			if (y_pos > 6)
				y_pos--;
		}
		else if (GetKeyState(83) & 0x8000)
		{
			if (y_pos < 29)
				y_pos++;
		}
		break;
	
	case 8:
		if (GetKeyState(80) & 0x8000)
		{
			m_reset = 1;
		}
		break;
	default:
		x_pos = 0;
		y_pos = 0;
		break;
	}
}
