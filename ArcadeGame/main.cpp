#include "game_mode.h"




int main() {
   
	game_mode m_gm;
	
	while (m_gm.get_is_game_in_play())
	{
		m_gm.update();
	}
  
}