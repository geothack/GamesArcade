#pragma once
#include <iostream>
#include <Windows.h>

class blackjack
{
public:
	//constructors
	blackjack() {}
	~blackjack() = default;


	//methods
	void generate_numbers();
	void game_inputs();
	void dealer_ai();


	//gets and sets
	inline int get_player_numbers() const  { return *m_player_numbers; }
	inline int get_dealer_numbers() const { return *m_dealer_numbers; }
	inline int get_player_bid_h() const { return m_player_bid_h; }
	inline int get_player_bid_t() const { return m_player_bid_t; }
	inline int get_player_bid() const { return m_player_bid; }
	int set_player_bid_h(int value) { return m_player_bid_h += value; }
	int set_player_bid_t(int value) { return m_player_bid_t = value; }
	int set_player_bid(int value) { return m_player_bid = value; }

	inline int get_player_money_h() const { return m_player_money_h; }
	inline int get_player_money_t() const { return m_player_money_t; }
	inline int get_player_money() const { return m_player_money; }
	int set_player_money_h(int value) { return m_player_money_h = value; }
	int set_player_money_t(int value) { return m_player_money_t = value; }
	int set_player_money(int value) { return m_player_money = value; }

	inline int get_fold() const { return m_fold; }
	int set_fold(int value) { return m_fold = value; }

	inline int get_hitme_index() const { return m_hitme_index; }
	int set_hitme_index(int index) { return m_hitme_index = index; }


	inline int get_dealer_hitme_index() const { return m_dealer_hitme_index; }
	int set_dealer_hitme_index(int index) { return m_dealer_hitme_index = index; }

	inline int get_dealer_total() const { return m_dealer_total; }
	int set_dealer_total(int total) { return m_dealer_total = total; }

	inline int get_player_total() const { return m_player_total; }
	int set_player_total(int total) { return m_player_total = total; }

	inline int get_reset_total() const { return m_reset_totals; }
	int set_reset_total(int total) { return m_reset_totals = total;  }
private:
	//variables
	int m_player_numbers[20], m_dealer_numbers[20];
	int m_player_bid_h = 0, m_player_bid_t, m_player_bid = 0;
	int m_player_money_h = 1, m_player_money_t = 0, m_player_money = 0;
	int m_fold = 0;
	int m_hitme_index = 0, m_dealer_hitme_index = 0;
	int m_dealer_total = 0, m_player_total = 0;
	int m_reset_totals = 0;

};

