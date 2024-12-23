#include "spaceinvaders.h"

int spaceinvaders::m_speed = 1;

spaceinvaders::spaceinvaders() 
{
	is_active = true;
}

void spaceinvaders::update_game(int index)
{

	x_pos += m_speed;

	if (x_pos >= 79)
	{
		m_speed = -1;
	}

	if (x_pos <= 1)
	{
		m_speed = 1;
	}
}
