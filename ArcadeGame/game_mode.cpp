#include "game_mode.h"


int game_mode::m_counter = 0;
int game_mode::m_alien_fire = 0;

game_mode::game_mode()
{
	m_game = game::start;
	m_game_is_playing = true;
	m_game_window.create_window(m_width, m_height);
	create_buffers(m_width, m_height);
	
}

game_mode::~game_mode()
{
}

void game_mode::update()
{
	draw_games(m_width,m_height);
	control_game_states();
	game_hit_detection();
	handle_game();


	
}

void game_mode::draw_games(const int width, const int height)
{
	

	for (auto i = 0; i < height; i++)
	{
		for (auto j = 0; j < width; j++)
		{
			m_game_window.set_cursor(j, i);
			std::cout << m_front_buffer.get_char(j, i);
		}
	}

	m_front_buffer = m_back_buffer;
	m_back_buffer = m_reset_buffer;
}

void game_mode::create_buffers(const int width, const int height)
{
	m_front_buffer = game_buffer(width, height);
	
	m_back_buffer = game_buffer(width, height);
	
	m_reset_buffer = game_buffer(width, height);

	for (auto i = 0; i != width; i++)
		for (auto j = 0; j != height; j++)
			m_reset_buffer.set_char(i, j, ' ');

	m_front_buffer = m_reset_buffer;
	m_back_buffer = m_reset_buffer;
}

void game_mode::control_game_states()
{
	switch (m_game)
	{
	case start:	
		system("cls");
		m_game_player.set_reset(0);
		choose_game();
		break;

	case break_out:
		set_games(m_width, m_height);		
		m_game_player.game_inputs(1);
		m_game_bullet.game_inputs(1);
		m_game_bullet.update_game(1);
		break;

	case space_invaders:
		set_games(m_width, m_height);
		m_game_player.game_inputs(2);
		m_game_bullet.game_inputs(2);
		m_game_bullet.update_game(2);
		m_space_bullet_2.game_inputs(2);
		m_space_bullet_2.update_game(2);	
		m_enemy_bullet.update_game(3);
		break;

	case pong:
		set_games(m_width, m_height);
		m_game_player.game_inputs(3);
		m_game_bullet.update_game(4);
		break;

	case black_jack:
		set_games(m_width, m_height);
		m_blackjack.game_inputs();
		break;

	case win:
		set_games(m_width, m_height);
		m_lives = 5;		
		m_game_player.game_inputs(8);
		break;

	case lose:		
		m_blackjack.set_fold(0);
		set_games(m_width, m_height);
		m_lives = 5;				
		m_game_player.game_inputs(8);
		break;

	default:
		m_game_is_playing = false;
		break;
	}
}

void game_mode::set_games(const int width, const int height)
{
	for (auto i = 0; i != m_height; i++)
	{
		for (auto j = 0; j != m_width; j++)
		{
			//breakout
			if (m_game == game::break_out)
			{
				for (auto bx = 0; bx != 80; bx++)
				{
					for (auto by = 0; by != 15; by++)
					{
						if(m_breakout[by][bx].get_is_active())
						if(m_breakout[by][bx].get_x_pos() == bx && m_breakout[by][bx].get_y_pos() == by)
						m_back_buffer.set_char(bx, by, '#');
					}
				}

				if (m_game_player.get_is_active())
					if (m_game_player.get_x_pos() >= j - 3 && m_game_player.get_x_pos() <= j + 3 
						&& m_game_player.get_y_pos() == i - 1)
						m_back_buffer.set_char(j, i, '_');

				if (m_game_bullet.get_is_active())
					if (m_game_bullet.get_x_pos() == j && m_game_bullet.get_y_pos() == i - 1)
						m_back_buffer.set_char(j, i, 'O');

				

			}//breakout

			if (m_game == game::space_invaders)//spaceinvaders
			{

				if (i == 2)
				{
					for (auto s = 0; s != 45; s++)
					{
						if (m_spaceinvaders[s].get_is_active())
							if (m_spaceinvaders[s].get_x_pos() == j)
								m_back_buffer.set_char(j, i, 'X');  
					}
				}


				if (m_game_player.get_is_active())
					if (m_game_player.get_x_pos() == j && m_game_player.get_y_pos() == i - 1)
						m_back_buffer.set_char(j, i, '^');

				if (m_game_bullet.get_is_active())
				{
					if (m_game_bullet.get_x_pos() == j  && m_game_bullet.get_y_pos() == i)
						m_back_buffer.set_char(j, i, '|');					
				}
				if (m_space_bullet_2.get_is_active())
				{
					if (m_space_bullet_2.get_x_pos() == j && m_space_bullet_2.get_y_pos() == i)
						m_back_buffer.set_char(j, i, '|');			
				}

				if (m_enemy_bullet.get_is_active())
				{
					if (m_enemy_bullet.get_x_pos() == j && m_enemy_bullet.get_y_pos() == i)
						m_back_buffer.set_char(j, i, '|');
				}

			}//space invaders

			if (m_game == game::pong)//pong
			{
				

				if (m_game_player.get_x_pos() == j && m_game_player.get_y_pos() >= i && m_game_player.get_y_pos() <= i + 6)
					m_back_buffer.set_char(j, i, '|');

				if (m_game_bullet.get_x_pos() == j && m_game_bullet.get_y_pos() == i)
					m_back_buffer.set_char(j, i, 'O');

				if (j == m_width / 2)
					m_back_buffer.set_char(j, i, '|');


				if (m_enemy_player.get_x_pos() == j && m_enemy_player.get_y_pos() >= i && m_enemy_player.get_y_pos() <= i + 6)
					m_back_buffer.set_char(j, i, '|');

				



			}//pong


			if (m_game == game::black_jack)//blackjack
			{
				if (i == 0 && j == 1)
				{
					for (auto t = 0; t != m_player_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_player_text[t]);
					}
				}

				if (i == 4 && j == 4)
				{
					auto str = std::to_string(m_blackjack.get_player_numbers());
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}

				if (i == 4 && j == 6)
				{				
					m_back_buffer.set_char(j, i, '+');
				}

				if (i == 4 && j == 8)
				{
					auto str = std::to_string(m_blackjack.get_player_numbers() + 1);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}
				if (m_blackjack.get_hitme_index() == 0)
				{
					if (i == 4 && j == 10)
					{
						m_back_buffer.set_char(j, i, '=');
					}

					if (i == 4 && j == 12)
					{
						auto str = std::to_string(m_player_cards_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 4 && j == 13)
					{
						auto str = std::to_string(m_player_cards);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}

				if (m_blackjack.get_hitme_index() == 1)
				{
					if (i == 4 && j == 10)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 4 && j == 12)
					{
						auto str = std::to_string(m_blackjack.get_player_numbers() + 2);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 4 && j == 14)
					{
						m_back_buffer.set_char(j, i, '=');
					}

					if (i == 4 && j == 16)
					{
						auto str = std::to_string(m_player_cards_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 4 && j == 17)
					{
						auto str = std::to_string(m_player_cards);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}

				if (m_blackjack.get_hitme_index() == 2)
				{
					if (i == 4 && j == 10)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 4 && j == 12)
					{
						auto str = std::to_string(m_blackjack.get_player_numbers() + 2);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 4 && j == 14)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 4 && j == 16)
					{
						auto str = std::to_string(m_blackjack.get_player_numbers() + 3);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 4 && j == 18)
					{
						m_back_buffer.set_char(j, i, '=');
					}

					if (i == 4 && j == 20)
					{
						auto str = std::to_string(m_player_cards_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 4 && j == 21)
					{
						auto str = std::to_string(m_player_cards);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}

				if (m_blackjack.get_hitme_index() == 3)
				{
					if (i == 4 && j == 10)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 4 && j == 12)
					{
						auto str = std::to_string(m_blackjack.get_player_numbers() + 2);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 4 && j == 14)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 4 && j == 16)
					{
						auto str = std::to_string(m_blackjack.get_player_numbers() + 3);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 4 && j == 18)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 4 && j == 20)
					{
						auto str = std::to_string(m_blackjack.get_player_numbers() + 4);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 4 && j == 22)
					{
						m_back_buffer.set_char(j, i, '=');
					}

					if (i == 4 && j == 24)
					{
						auto str = std::to_string(m_player_cards_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 4 && j == 25)
					{
						auto str = std::to_string(m_player_cards);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}

				if (m_blackjack.get_hitme_index() >= 4)
				{
					if (i == 4 && j == 10)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 4 && j == 12)
					{
						auto str = std::to_string(m_blackjack.get_player_numbers() + 2);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 4 && j == 14)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 4 && j == 16)
					{
						auto str = std::to_string(m_blackjack.get_player_numbers() + 3);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 4 && j == 18)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 4 && j == 20)
					{
						auto str = std::to_string(m_blackjack.get_player_numbers() + 4);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 4 && j == 22)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 4 && j == 24)
					{
						auto str = std::to_string(m_blackjack.get_player_numbers() + 5);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 4 && j == 26)
					{
						m_back_buffer.set_char(j, i, '=');
					}

					if (i == 4 && j == 28)
					{
						auto str = std::to_string(m_player_cards_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 4 && j == 29)
					{
						auto str = std::to_string(m_player_cards);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}
				
				if (i == 13 && j == 1)
				{
					for (auto t = 0; t != m_hitme_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_hitme_text[t]);
					}
				}

				if (i == 13 && j == 10)
				{
					for (auto t = 0; t != m_stay_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_stay_text[t]);
					}
				}


				if (i == 13 && j == 20)
				{
					for (auto t = 0; t != m_bet_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_bet_text[t]);
					}
				}

				if (i == 13 && j == 30)
				{
					auto str = std::to_string(m_blackjack.get_player_bid_h());
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}

				if (i == 13 && j == 31)
				{
					auto str = std::to_string(m_blackjack.get_player_bid_t());
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}

				if (i == 13 && j == 32)
				{
					auto str = std::to_string(m_blackjack.get_player_bid());
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}


				if (i == 13 && j == 37)
				{
					for (auto t = 0; t != m_bank_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_bank_text[t]);
					}
				}

				if (i == 13 && j == 44)
				{
					auto str = std::to_string(m_blackjack.get_player_money_h());
					const char* s = str.c_str();				
					m_back_buffer.set_char(j, i, *s);
				}

				if (i == 13 && j == 45)
				{
					auto str = std::to_string(m_blackjack.get_player_money_t());
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}

				if (i == 13 && j == 46)
				{
					auto str = std::to_string(m_blackjack.get_player_money());
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}
				
				if (i == 13 && j == 55)
				{
					for (auto t = 0; t != m_fold_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_fold_text[t]);
					}
				}


				if (i == m_height / 2)
					m_back_buffer.set_char(j, i, '-');

				if (i == 16 && j == 1)
				{
					for (auto t = 0; t != m_dealer_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_dealer_text[t]);
					}
				}


				if (m_blackjack.get_dealer_hitme_index() == 0)
				{
					if (i == 20 && j == 4)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers());
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 6)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 8)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 1);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 10)
					{
						m_back_buffer.set_char(j, i, '=');
					}

					if (i == 20 && j == 12)
					{
						auto str = std::to_string(m_dealer_cards_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 20 && j == 13)
					{
						auto str = std::to_string(m_dealer_cards);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}

				if (m_blackjack.get_dealer_hitme_index() == 1)
				{
					if (i == 20 && j == 4)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers());
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 6)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 8)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 1);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 10)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 12)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 2);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}


					if (i == 20 && j == 14)
					{
						m_back_buffer.set_char(j, i, '=');
					}

					if (i == 20 && j == 16)
					{
						auto str = std::to_string(m_dealer_cards_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 20 && j == 17)
					{
						auto str = std::to_string(m_dealer_cards);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}

				if (m_blackjack.get_dealer_hitme_index() == 2)
				{
					if (i == 20 && j == 4)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers());
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 6)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 8)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 1);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 10)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 12)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 2);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}


					if (i == 20 && j == 14)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 16)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 3);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}


					if (i == 20 && j == 18)
					{
						m_back_buffer.set_char(j, i, '=');
					}

					if (i == 20 && j == 20)
					{
						auto str = std::to_string(m_dealer_cards_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 20 && j == 21)
					{
						auto str = std::to_string(m_dealer_cards);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}

				if (m_blackjack.get_dealer_hitme_index() == 3)
				{
					if (i == 20 && j == 4)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers());
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 6)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 8)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 1);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 10)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 12)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 2);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}


					if (i == 20 && j == 14)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 16)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 3);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 18)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 20)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 4);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}


					if (i == 20 && j == 22)
					{
						m_back_buffer.set_char(j, i, '=');
					}

					if (i == 20 && j == 24)
					{
						auto str = std::to_string(m_dealer_cards_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 20 && j == 25)
					{
						auto str = std::to_string(m_dealer_cards);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}

				if (m_blackjack.get_dealer_hitme_index() == 4)
				{
					if (i == 20 && j == 4)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers());
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 6)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 8)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 1);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 10)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 12)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 2);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}


					if (i == 20 && j == 14)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 16)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 3);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 18)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 20)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 4);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}

					if (i == 20 && j == 22)
					{
						m_back_buffer.set_char(j, i, '+');
					}

					if (i == 20 && j == 24)
					{
						auto str = std::to_string(m_blackjack.get_dealer_numbers() + 5);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}


					if (i == 20 && j == 26)
					{
						m_back_buffer.set_char(j, i, '=');
					}

					if (i == 20 && j == 28)
					{
						auto str = std::to_string(m_dealer_cards_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 20 && j == 28)
					{
						auto str = std::to_string(m_dealer_cards);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}



			}//blackjack


			//lives score and timer
			if (m_game != game::lose || m_game != game::win)
			{
				if (m_game != game::black_jack)
				{
					if (i == 29 && j == 1)
						for (auto t = 0; t != m_score_text.length(); t++)
						{
							j++;
							m_back_buffer.set_char(j, i, m_score_text[t]);
						}
					if (i == 29 && j == 8)
					{
						auto str = std::to_string(m_score_h);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 29 && j == 9)
					{
						auto str = std::to_string(m_score_t);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
					if (i == 29 && j == 10)
					{
						auto str = std::to_string(m_score);
						const char* s = str.c_str();
						m_back_buffer.set_char(j, i, *s);
					}
				}

				if (i == 29 && j == 36)
				{
					for (size_t t = 0; t < m_time_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_time_text[t]);
					}
				}

				if (i == 29 && j == 42)
				{
					auto str = std::to_string(m_time_h);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}
				if (i == 29 && j == 43)
				{
					auto str = std::to_string(m_time_t);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}
				if (i == 29 && j == 44)
				{
					auto str = std::to_string(m_time);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}

				if (i == 29 && j == 65)
					for (auto t = 0; t != m_lives_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_lives_text[t]);
					}

				if (i == 29 && j == 73)
				{
					auto str = std::to_string(m_lives);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}
			}//lives score and timer




			if (m_game == game::lose)//lose
			{
				if (i == 1 && j == 1)
				{
					for (auto t = 0; t != m_lose_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_lose_text[t]);
					}
				}

				if (i == 1 && j == 30)
				{
					auto str = std::to_string(m_score_h);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}
				if (i == 1 && j == 31)
				{
					auto str = std::to_string(m_score_t);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}
				if (i == 1 && j == 32)
				{
					auto str = std::to_string(m_score);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}

				if (i == 3 && j == 1)
				{
					for (auto t = 0; t != m_continue_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_continue_text[t]);
					}
				}
								
			}//lose

			if (m_game == game::win)//win
			{
				if (i == 1 && j == 1)
				{
					for (auto t = 0; t != m_win_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_win_text[t]);
					}
				}

				if (i == 1 && j == 30)
				{
					auto str = std::to_string(m_score_h);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}
				if (i == 1 && j == 31)
				{
					auto str = std::to_string(m_score_t);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}
				if (i == 1 && j == 32)
				{
					auto str = std::to_string(m_score);
					const char* s = str.c_str();
					m_back_buffer.set_char(j, i, *s);
				}

				if (i == 3 && j == 1)
				{
					for (auto t = 0; t != m_continue_text.length(); t++)
					{
						j++;
						m_back_buffer.set_char(j, i, m_continue_text[t]);
					}
				}
			}//win
		}
	}
}

void game_mode::choose_game()
{	
	std::cout << "Welcome To The Select Screen :)\n\n";
	std::cout << "Enter [1] : To Play Breakout\n";
	std::cout << "Enter [2] : To Play SpaceInvaders\n";
	std::cout << "Enter [3] : To Play Pong\n";
	std::cout << "Enter [4] : To Play Blackjack\n";
	std::cout << "Enter [5] : To Quit\n\n";
	if(m_time > 0 || m_time_t > 1)
	std::cout << "Please press and hold backspace\nunitl all characters that may have been enter are gone Thanks\n\n";
	int select;
	std::cin >> select;
	switch (select)
	{
	case 1:
		m_game = game::break_out;
		create_arrays();
		set_player();
		m_score = 0;
		m_score_t = 0;
		m_score_h = 0;
		m_time = 0;
		m_time_t = 0;
		m_time_h = 0;
		break;
	case 2:
		m_game = game::space_invaders;
		create_arrays();
		set_player();
		m_score = 0;
		m_score_t = 0;
		m_score_h = 0;
		m_time = 0;
		m_time_t = 0;
		m_time_h = 0;
		break;
	case 3:
		m_game = game::pong;
		set_player();
		m_score = 0;
		m_score_t = 0;
		m_score_h = 0;
		m_time = 0;
		m_time_t = 0;
		m_time_h = 0;
		break;
	case 4:
		m_game = game::black_jack;
		m_blackjack.generate_numbers();	
		m_blackjack.set_player_money_h(1);
		m_score = 0;
		m_score_t = 0;
		m_score_h = 0;
		m_time = 0;
		m_time_t = 0;
		m_time_h = 0;
		break;
	case 5:
		m_game_is_playing = false;
		break;
	default:
		std::cout << "Sorry I don't get that \n";
		std::cin >> select;
		break;
	}
}

void game_mode::create_arrays()
{
	if (m_game == game::break_out)
	{
		for (int i = 0; i != 15; ++i)
		{
			m_breakout[i] = std::make_unique<breakout[]>(80);
			for (int j = 0; j != 80; ++j)
			{
				m_breakout[i][j] = breakout(i * 80 + j); // Initialize each element
			}
		}

		for (int i = 0; i != 15; ++i)
		{
			for (int j = 0; j != 80; ++j)
			{
				
				if (j % 3)
					m_breakout[i][j].set_x_pos(j);
				if (i % 3)
					m_breakout[i][j].set_y_pos(i);
			}

		}
	}
	if (m_game == game::space_invaders)
	{
		m_game_bullet.set_is_active(false);
		m_space_bullet_2.set_is_active(false);
		m_enemy_bullet.set_is_active(false);
		for (auto i = 0; i != 45; i++)
		{
			m_spaceinvaders[i].set_is_active(true);
			if(i % 2 == 0)
			m_spaceinvaders[i].set_x_pos(i);
			m_spaceinvaders[i].set_y_pos(1);
		}
	}
	
}

void game_mode::set_player()
{
	if (m_game == game::break_out || m_game == game::space_invaders)
	{
		m_game_player.set_x_pos(m_width / 2);
		m_game_player.set_y_pos(24);
		m_game_bullet.set_x_pos(m_width / 2 - 1);
		m_game_bullet.set_y_pos(23);
		m_space_bullet_2.set_x_pos(m_width / 2 + 1);
		m_space_bullet_2.set_y_pos(23);
	}

	if (m_game == game::pong)
	{
		m_game_player.set_x_pos(3);
		m_game_player.set_y_pos((m_height / 2) + 3);
		m_enemy_player.set_x_pos(77);
		m_enemy_player.set_y_pos((m_height / 2) + 3);
		m_game_bullet.set_x_pos((m_width / 2) - 1);
		m_game_bullet.set_y_pos(m_height / 2);
		m_game_bullet.set_is_flying(true);
	}
	
}

void game_mode::game_hit_detection()
{
	if (m_game == game::break_out)//breakout
	{
		for (auto i = 0; i != 15; ++i)
		{
			for (auto j = 0; j != 80; ++j)
			{
				if (m_breakout[i][j].get_x_pos() == m_game_bullet.get_x_pos() &&
					m_breakout[i][i].get_y_pos() == m_game_bullet.get_y_pos())
				{
					m_breakout[i][j].set_is_active(false);
					m_breakout[i][j].set_x_pos(0);
					m_breakout[i][j].set_y_pos(0);
					m_game_bullet.set_speed_y(-1);
					m_score++;
				}
			}
		}

		if (m_game_bullet.get_x_pos() >= m_game_player.get_x_pos() - 3 && m_game_bullet.get_x_pos() <= m_game_player.get_x_pos() + 3 &&
			m_game_bullet.get_y_pos() == m_game_player.get_y_pos())
		{
			m_game_bullet.set_speed_y(-1);
		}

	}//breakout

	if (m_game == game::space_invaders)//spaceinvaders
	{
		for (auto i = 0; i < 45; i++)
		{
			//move aliens
			m_spaceinvaders[i].update_game(0);

			//hit detection
			if (m_spaceinvaders[i].get_x_pos() == m_game_bullet.get_x_pos() && m_spaceinvaders[i].get_y_pos() == m_game_bullet.get_y_pos()
				|| m_spaceinvaders[i].get_x_pos() == m_space_bullet_2.get_x_pos() && m_spaceinvaders[i].get_y_pos() == m_space_bullet_2.get_y_pos())
			{
				m_spaceinvaders[i].set_is_active(false);				
				m_spaceinvaders[i].set_x_pos(m_width / 2);
				m_game_bullet.set_is_active(false);
				m_game_bullet.set_is_flying(false);
				m_space_bullet_2.set_is_active(false);
				m_space_bullet_2.set_is_flying(false);
				m_score += 2;
			}
			
			

			
		}

		if (m_enemy_bullet.get_x_pos() == m_game_player.get_x_pos() && m_enemy_bullet.get_y_pos() == m_game_player.get_y_pos())
		{
			m_enemy_bullet.set_is_active(false);
			m_enemy_bullet.set_is_flying(false);
			m_enemy_bullet.set_speed_y(3);
			m_lives--;
		}


	}//spaceinvaders

	if (m_game == game::pong)
	{
		if (m_game_bullet.get_x_pos() == m_game_player.get_x_pos() && m_game_bullet.get_y_pos() >= m_game_player.get_y_pos() - 6
			&& m_game_bullet.get_y_pos() <= m_game_player.get_y_pos() + 2)
		{
			m_game_bullet.set_speed_x(-1);
		}
		if (m_game_bullet.get_x_pos() == m_enemy_player.get_x_pos() && m_game_bullet.get_y_pos() >= m_enemy_player.get_y_pos() - 6
			&& m_game_bullet.get_y_pos() <= m_enemy_player.get_y_pos() + 2)
		{
			m_game_bullet.set_speed_x(-1);
		}
	}
	
}

void game_mode::handle_game()
{
	if (m_game == game::break_out)
	{
		if (!m_game_bullet.get_is_flying())
		{
			m_game_bullet.set_x_pos(m_game_player.get_x_pos());
			m_game_bullet.set_y_pos(m_game_player.get_y_pos() - 1);			
		}
		if (m_game_bullet.get_y_pos() >= 28)
		{
			m_lives--;		
		}
		if (m_lives <= -1)
		{
			m_game = game::lose;
			system("cls");
		}

		if (m_time_h >= 1 && m_time_t >= 2)
		{
			m_game = game::win;
			system("cls");
		}
		if (m_score_h >= 2)
		{
			m_game = game::win;
			system("cls");
		}
	}

	if (m_game == game::space_invaders)
	{

		if (!m_game_bullet.get_is_flying())
		{
			m_game_bullet.set_x_pos(m_game_player.get_x_pos() - 1);		
			m_game_bullet.set_y_pos(m_game_player.get_y_pos());
		}

		if (!m_space_bullet_2.get_is_flying())
		{
			m_space_bullet_2.set_x_pos(m_game_player.get_x_pos() + 1);
			m_space_bullet_2.set_y_pos(m_game_player.get_y_pos());
		}
	
		
		m_spaceinvaders[0].set_x_pos(m_spaceinvaders[1].get_x_pos() - 2);

		m_alien_fire++;

		if (m_alien_fire >= 100)
		{
			m_random_alien = rand() & (45 - 1 + 1) + 1;
			m_alien_fire = 0;
		}
		if (m_spaceinvaders[m_random_alien].get_is_active())
		{
			if (!m_enemy_bullet.get_is_flying())
			{
				m_enemy_bullet.set_x_pos(m_spaceinvaders[m_random_alien].get_x_pos());
				m_enemy_bullet.set_y_pos(m_spaceinvaders[m_random_alien].get_y_pos()+ 2);
				m_enemy_bullet.set_is_active(true);
			}
			m_enemy_bullet.set_is_flying(true);

		}
		else
		{
			m_random_alien = rand() & (45 - 1 + 1) + 1;
		}

		if (m_lives <= -1)
		{
			m_game = game::lose;
			system("cls");
		}

		
		if (m_score_t >= 3)
		{
			m_game = game::win;
			system("cls");
		}
	}


	if (m_game == game::pong)//pong
	{
		if (m_game_bullet.get_x_pos() <= 0)
		{
			m_lives--;
			m_game_bullet.set_x_pos((m_width / 2) + 1);
			m_game_bullet.set_y_pos(m_height / 2);
			m_game_bullet.set_speed_x(-1);			
			m_game_bullet.set_speed_y(-1);
			
		}
		if (m_game_bullet.get_x_pos() >= 79)
		{		
			m_game_bullet.set_x_pos((m_width / 2) - 1);
			m_game_bullet.set_y_pos(m_height / 2);
			m_game_bullet.set_speed_x(-1);
			m_game_bullet.set_speed_y(-1);
			m_score++;
		}

		//enemy pong ai
		if (m_game_bullet.get_y_pos() < m_enemy_player.get_y_pos() - 8)
		{
			m_enemy_player.set_y_pos(m_enemy_player.get_y_pos() - 1);
		}

		if (m_game_bullet.get_y_pos() > m_enemy_player.get_y_pos() + 4)
		{
			m_enemy_player.set_y_pos(m_enemy_player.get_y_pos() + 1);
		}

		//



		if (m_lives <= -1)
		{
			m_game = game::lose;
			system("cls");
		}


		if (m_score_t >= 1)
		{
			m_game = game::win;
			system("cls");
		}


	}//pong


	if (m_game == game::black_jack)//blackjack
	{
		if (m_blackjack.get_hitme_index() == 0)
		{
			m_blackjack.set_player_total(m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1));
			if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) <= 19)
			{
				m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) ;
				
				if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) <= 9)
				{
					m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1);
				}
				else
				{
					m_player_cards_t = 1;
					m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) - 10;
				}
			}
			else if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) >= 20)
			{
				m_player_cards_t = 2;
				m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1)  - 20;
			}
		}

		if (m_blackjack.get_hitme_index() == 1)
		{
			m_blackjack.set_player_total(m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2));
			if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2)  <= 19)
			{
				m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2);
				m_blackjack.set_player_total(m_player_cards);
				if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) <= 9)
				{
					m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2);
				}
				else
				{
					m_player_cards_t = 1;
					m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) - 10;
				}
			}
			else if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) >= 20)
			{
				m_player_cards_t = 2;
				m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) - 20;
			}
			
		}

		if (m_blackjack.get_hitme_index() == 2)
		{
			m_blackjack.set_player_total(m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3));
			if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
				  <= 19)
			{
				m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3);
				m_blackjack.set_player_total(m_player_cards);
				if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3) <= 9)
				{
					m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3);
				}
				else
				{
					m_player_cards_t = 1;
					m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3) - 10;
				}
			}
			else if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
				  >= 20)
			{
				m_player_cards_t = 2;
				m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3) - 20;
			}

			
		}

		if (m_blackjack.get_hitme_index() == 3)
		{
			m_blackjack.set_player_total(m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3) + (m_blackjack.get_player_numbers() + 4));
			if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
				+ (m_blackjack.get_player_numbers() + 4)  <= 19)
			{
				m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
					+ (m_blackjack.get_player_numbers() + 4);
				m_blackjack.set_player_total(m_player_cards);
				if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
					+ (m_blackjack.get_player_numbers() + 4) <= 9 && m_player_cards_t == 2)
				{
					m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
						+ (m_blackjack.get_player_numbers() + 4);
				}
				else
				{
					m_player_cards_t = 1;
					m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
						+ (m_blackjack.get_player_numbers() + 4) - 10;
				}
			}
			else if(m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
				+ (m_blackjack.get_player_numbers() + 4)  >= 20)
			{
				m_player_cards_t = 2;
				m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
					+ (m_blackjack.get_player_numbers() + 4)  - 20;
			}

			
		}

		if (m_blackjack.get_hitme_index() == 4)
		{
			m_blackjack.set_player_total(m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3) + (m_blackjack.get_player_numbers() + 4) + (m_blackjack.get_player_numbers() + 5));
			if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
				+ (m_blackjack.get_player_numbers() + 4) + (m_blackjack.get_player_numbers() + 5) <= 19)
			{
				m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
					+ (m_blackjack.get_player_numbers() + 4) + (m_blackjack.get_player_numbers() + 5);
				m_blackjack.set_player_total(m_player_cards);
				if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
					+ (m_blackjack.get_player_numbers() + 4) + (m_blackjack.get_player_numbers() + 5) <= 9)
				{
					m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
						+ (m_blackjack.get_player_numbers() + 4) + (m_blackjack.get_player_numbers() + 5);
				}
				else
				{
					m_player_cards_t = 1;
					m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
						+ (m_blackjack.get_player_numbers() + 4) - 10 + (m_blackjack.get_player_numbers() + 5);
				}
			}
			else if (m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
				+ (m_blackjack.get_player_numbers() + 4) + (m_blackjack.get_player_numbers() + 5) >= 20)
			{
				m_player_cards_t = 2;
				m_player_cards = m_blackjack.get_player_numbers() + (m_blackjack.get_player_numbers() + 1) + (m_blackjack.get_player_numbers() + 2) + (m_blackjack.get_player_numbers() + 3)
					+ (m_blackjack.get_player_numbers() + 4) + (m_blackjack.get_player_numbers() + 5) - 20;
			}

			

			
		}

		
		//dealer hitme control

		if (m_blackjack.get_dealer_hitme_index() == 0)
		{
			m_blackjack.set_dealer_total(m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1));
			if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) <= 19)
			{
				m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1);
				
				if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) <= 9)
				{
					m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1);
				}
				else
				{
					m_dealer_cards_t = 1;
					m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) - 10;
				}
			}
			else if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) >= 20)
			{
				m_dealer_cards_t = 2;
				m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) - 20;
			}
		}

		if (m_blackjack.get_dealer_hitme_index() == 1)
		{
			m_blackjack.set_dealer_total(m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2));
			if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) <= 19)
			{
				m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2);
				
				if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) <= 9)
				{
					m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2);
				}
				else
				{
					m_dealer_cards_t = 1;
					m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) - 10;
				}
			}
			else if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) >= 20)
			{
				m_dealer_cards_t = 2;
				m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) - 20;
			}

		}

		if (m_blackjack.get_dealer_hitme_index() == 2)
		{
			m_blackjack.set_dealer_total(m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3));
			if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
				<= 19)
			{
				m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3);
				
				if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3) <= 9)
				{
					m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3);
				}
				else
				{
					m_dealer_cards_t = 1;
					m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3) - 10;
				}
			}
			else if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
				>= 20)
			{
				m_dealer_cards_t = 2;
				m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3) - 20;
			}


		}

		if (m_blackjack.get_dealer_hitme_index() == 3)
		{
			m_blackjack.set_dealer_total(m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3) + (m_blackjack.get_dealer_numbers() + 4));
			if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
				+ (m_blackjack.get_dealer_numbers() + 4) <= 19)
			{
				m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
					+ (m_blackjack.get_dealer_numbers() + 4);
				
				if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
					+ (m_blackjack.get_dealer_numbers() + 4) <= 9 && m_dealer_cards_t == 2)
				{
					m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
						+ (m_blackjack.get_dealer_numbers() + 4);
				}
				else
				{
					m_dealer_cards_t = 1;
					m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
						+ (m_blackjack.get_dealer_numbers() + 4) - 10;
				}
			}
			else if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
				+ (m_blackjack.get_dealer_numbers() + 4) >= 20)
			{
				m_dealer_cards_t = 2;
				m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
					+ (m_blackjack.get_dealer_numbers() + 4) - 20;
			}


		}

		if (m_blackjack.get_dealer_hitme_index() == 4)
		{
			m_blackjack.set_dealer_total(m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3) + (m_blackjack.get_dealer_numbers() + 4) + (m_blackjack.get_dealer_numbers() + 5));
			if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
				+ (m_blackjack.get_dealer_numbers() + 4) + (m_blackjack.get_dealer_numbers() + 5) <= 19)
			{
				m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
					+ (m_blackjack.get_dealer_numbers() + 4) + (m_blackjack.get_dealer_numbers() + 5);
				m_blackjack.set_dealer_total(m_dealer_cards);
				if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
					+ (m_blackjack.get_dealer_numbers() + 4) + (m_blackjack.get_dealer_numbers() + 5) <= 9)
				{
					m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
						+ (m_blackjack.get_dealer_numbers() + 4) + (m_blackjack.get_dealer_numbers() + 5);
				}
				else
				{
					m_dealer_cards_t = 1;
					m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
						+ (m_blackjack.get_dealer_numbers() + 4) - 10 + (m_blackjack.get_dealer_numbers() + 5);
				}
			}
			else if (m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
				+ (m_blackjack.get_dealer_numbers() + 4) + (m_blackjack.get_dealer_numbers() + 5) >= 20)
			{
				m_dealer_cards_t = 2;
				m_dealer_cards = m_blackjack.get_dealer_numbers() + (m_blackjack.get_dealer_numbers() + 1) + (m_blackjack.get_dealer_numbers() + 2) + (m_blackjack.get_dealer_numbers() + 3)
					+ (m_blackjack.get_dealer_numbers() + 4) + (m_blackjack.get_dealer_numbers() + 5) - 20;
			}



			  
		}


		if (m_blackjack.get_reset_total() == 1)
		{
			m_player_cards_t = 0;
			m_dealer_cards_t = 0;
			m_blackjack.set_reset_total(0);
		}


		if (m_blackjack.get_player_bid_t() > 9)
		{
			m_blackjack.set_player_bid_h(1);
			m_blackjack.set_player_bid_t(0);
		}


		if (m_blackjack.get_player_money_h() >= 4)
		{
			m_game = game::win;
			system("cls");
		}

		if (m_blackjack.get_player_money_h() == 0 && m_blackjack.get_player_money_t() == 0)
		{
			m_game = game::lose;
			system("cls");
		}

		if (m_blackjack.get_fold() == 1)
		{
			m_game = game::lose;
			system("cls");
		}


	}//blackjack


	if (m_game != game::start || m_game != game::win || m_game != game::lose)
	{
		m_counter++;
		if (m_counter % 10 == 0)
		{
			m_time++;
			m_counter = 0;
		}

		if (m_time > 9)
		{
			m_time_t++;
			m_time = 0;
		}
		if (m_time_t > 9)
		{
			m_time_h++;
			m_time_t = 0;
		}

		if (m_score > 9)
		{
			m_score_t++;
			m_score = 0;
		}

		if (m_score_t > 9)
		{
			m_score_h++;
			m_score_t = 0;
		}
	}

	if (m_game == game::lose || m_game == game::win)
	{
		if (m_game_player.get_reset() == 1)
		{
			m_game = game::start;			
		}
	}
}




