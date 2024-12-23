#pragma once
#include "game_buffer.h"
#include <iostream>
#include "game_window.h"
#include "breakout.h"
#include "game_player.h"
#include "game_bullet.h"
#include <string>
#include "spaceinvaders.h"
#include "blackjack.h"


class game_mode
{
public:
	//constructors 
	game_mode();
	~game_mode();



	//methods 
	void update();
	void draw_games(const int width, const int height);
	void create_buffers(const int width, const int height);
	void control_game_states();
	void set_games(const int width, const int height);
	void choose_game();
	void create_arrays();
	void set_player();
	void game_hit_detection();
	void handle_game();
	

	//gets and sets 
	inline const bool get_is_game_in_play() { return m_game_is_playing; }
	

private:
	//variables 
	bool m_game_is_playing = false;

	enum game
	{
		start,
		break_out,
		space_invaders,
		pong,
		black_jack,
		win,
		lose
	};

	game m_game;

	game_window m_game_window;
	game_player m_game_player;
	game_player m_enemy_player;//pong ai player;

	game_bullet m_game_bullet;//regular bullet / ball
	game_bullet m_space_bullet_2;//space invaders second bullet
	game_bullet m_enemy_bullet;//space aliens bullet

	//heap allocated two dimensional array with smart pointers 
	std::unique_ptr<std::unique_ptr<breakout[]>[]> m_breakout = std::make_unique<std::unique_ptr<breakout[]>[]>(15);
	
	
	//had to stack allocated in order for aliens to bounce accross screen properly 
	spaceinvaders m_spaceinvaders[45];

	blackjack m_blackjack;

	const int m_width = 80;
	const int m_height = 30;
	game_buffer m_front_buffer, m_back_buffer, m_reset_buffer;

	int m_score_h = 0, m_score_t = 0, m_score = 0, m_lives = 5, m_time_h = 0, m_time_t = 0, m_time = 0;
	std::string m_score_text = "SCORE ";
	std::string m_lives_text = "LIVES ";
	std::string m_time_text = "TIME ";
	std::string m_lose_text = "You lost :( with a score of ";
	std::string m_continue_text = "Press Enter [p] to continue";
	std::string m_win_text = "You Won! :) with a score of ";
	std::string m_player_text = "PLAYER";
	std::string m_dealer_text = "DEALER";
	std::string m_hitme_text = "HIT [H]";
	std::string m_stay_text = "STAY [S]";
	std::string m_fold_text = "FOLD [F]";
	std::string m_bet_text = "BET [B] ";
	std::string m_bank_text = "BANK ";


	
	int m_player_cards_t = 0, m_player_cards = 0;
	int m_dealer_cards_t = 0, m_dealer_cards = 0;

	static int m_counter, m_alien_fire;

	int m_random_alien;
	int double_digit = 0;

};

