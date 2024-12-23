#include "game_bullet.h"

game_bullet::game_bullet()
{
	is_active = true;
}

void game_bullet::game_inputs(int index)
{
	switch (index)
	{
	case 1://breakout
		if (GetKeyState(32) & 0x8000)
		{
			m_is_flying = true;
			
		}
			break;
	case 2:
		if (GetKeyState(32) & 0x8000)
		{
			is_active = true;
			m_is_flying = true;

		}

		break;
	
		

	default:
		x_pos = 0;
		y_pos = 0;
		break;
	}
}

void game_bullet::update_game(int index)
{
	switch (index)
	{
	case 1: //breakout
		if (m_is_flying)
		{
			x_pos = x_pos + m_speed_x;
			y_pos = y_pos + m_speed_y;
		}
		if (x_pos >= 79)
			m_speed_x = m_speed_x * -1;

		if (x_pos <= 1)
			m_speed_x = m_speed_x * -1;

		if (y_pos <= 1)
			m_speed_y = m_speed_y * -1;

		if (y_pos >= 29)
		{
			m_is_flying = false;
			m_speed_x = 1;
			m_speed_y = -1;
			x_pos = 40;
			y_pos = 27;
			//- lives

		}
		break;
	case 2://spaceinvaders
		if (m_is_flying)
		{		
			y_pos--;
		}
		if (y_pos <= 0)
		{
			is_active = false;
			m_is_flying = false;
			y_pos = 23;
		}
		break;
	case 3://enemy alien
		if (m_is_flying)
		{
			y_pos++;
		}
		if (y_pos >= 29)
		{
			is_active = false;
			m_is_flying = false;
			
		}
		break;
	case 4://pong
		if (m_is_flying)
		{
			x_pos = x_pos - m_speed_x;
			y_pos = y_pos + m_speed_y;
		}
		if (y_pos <= 1)
		{
			m_speed_y = 1;
		}
		if (y_pos >= 29)
		{
			m_speed_y = -1;
		}


		break;

	default:
		x_pos = 0;
		y_pos = 0;
		break;
	}

	
		
}
