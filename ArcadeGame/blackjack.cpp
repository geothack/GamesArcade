#include "blackjack.h"

void blackjack::generate_numbers()
{
	for (auto i = 0; i != 20; i++)
	{
		m_player_numbers[i] = rand() % (9 - 1 + 1) + 1;
		m_dealer_numbers[i] = rand() % (9 - 1 + 1) + 1;
	}
}

void blackjack::game_inputs()
{
	if (GetKeyState(72) & 0x8000)//H hit me
	{
		Sleep(50);
		m_hitme_index++;
	}
	if (GetKeyState(66) & 0x8000)//B bet
	{
		Sleep(50);
		if (m_player_money_t != 0 || m_player_money_h != 0)
		{
			m_player_bid_t++;
			if (m_player_money_t != 0)
				m_player_money_t--;

			if (m_player_money_h != 0 && m_player_money_t == 0)
			{
				m_player_money_h--;
				m_player_money_t = 9;
			}
			
		}
	}
	if (GetKeyState(83) & 0x8000)//S stay
	{
		Sleep(50);
		this->dealer_ai();
	}
	if (GetKeyState(70) & 0x8000)//F fold
	{
		m_fold = 1;
	}
	
}

void blackjack::dealer_ai()
{
	if (m_dealer_total >= 17)
	{
		if (m_dealer_total > m_player_total)
		{
			m_player_bid = 0;
			m_player_bid_t = 0;
			m_player_bid_h = 0;
			m_hitme_index = 0;
			m_dealer_hitme_index = 0;
			m_reset_totals = 1;
			generate_numbers();
		}

		if (m_dealer_total < m_player_total)
		{
			if (m_player_bid_t != 0)
			{
				m_player_bid_t = m_player_bid_t * 2;
			}
			if (m_player_bid_h != 0)
			{
				m_player_money_h = m_player_bid_h * 2;
			}


			m_player_bid = 0;
			m_player_bid_t = 0;
			m_player_bid_h = 0;
			m_hitme_index = 0;
			m_dealer_hitme_index = 0;
			m_reset_totals = 1;
			generate_numbers();
		}

		if (m_dealer_total == m_player_total)
		{
			if (m_player_bid_t != 0)
			{
				m_player_bid_t = m_player_bid_t;
			}
			if (m_player_bid_h != 0)
			{
				m_player_money_h = m_player_bid_h;
			}


			m_player_bid = 0;
			m_player_bid_t = 0;
			m_player_bid_h = 0;
			m_hitme_index = 0;
			m_dealer_hitme_index = 0;
			m_reset_totals = 1;
			generate_numbers();
		}
	}

	if (m_dealer_total <= 16)
	{
		Sleep(50);
		m_dealer_hitme_index++;
		if (m_dealer_total <= 16)
		{
			m_dealer_hitme_index++;
			if (m_dealer_total > m_player_total)
			{
				m_player_bid = 0;
				m_player_bid_t = 0;
				m_player_bid_h = 0;
				m_hitme_index = 0;
				m_dealer_hitme_index = 0;
				m_reset_totals = 1;
				generate_numbers();
			}

			if (m_dealer_total < m_player_total)
			{
				if (m_player_bid_t != 0)
				{
					m_player_bid_t = m_player_bid_t * 2;
				}
				if (m_player_bid_h != 0)
				{
					m_player_money_h = m_player_bid_h * 2;
				}


				m_player_bid = 0;
				m_player_bid_t = 0;
				m_player_bid_h = 0;
				m_hitme_index = 0;
				m_dealer_hitme_index = 0;
				m_reset_totals = 1;
				generate_numbers();
			}
			if (m_dealer_total == m_player_total)
			{
				if (m_player_bid_t != 0)
				{
					m_player_bid_t = m_player_bid_t;
				}
				if (m_player_bid_h != 0)
				{
					m_player_money_h = m_player_bid_h;
				}


				m_player_bid = 0;
				m_player_bid_t = 0;
				m_player_bid_h = 0;
				m_hitme_index = 0;
				m_dealer_hitme_index = 0;
				m_reset_totals = 1;
				generate_numbers();
			}
			if (m_dealer_total <= 16)
			{
				m_dealer_hitme_index++;
				if (m_dealer_total > m_player_total)
				{
					m_player_bid = 0;
					m_player_bid_t = 0;
					m_player_bid_h = 0;
					m_hitme_index = 0;
					m_dealer_hitme_index = 0;
					m_reset_totals = 1;
					generate_numbers();
				}

				if (m_dealer_total < m_player_total)
				{
					if (m_player_bid_t != 0)
					{
						m_player_bid_t = m_player_bid_t * 2;
					}
					if (m_player_bid_h != 0)
					{
						m_player_money_h = m_player_bid_h * 2;
					}


					m_player_bid = 0;
					m_player_bid_t = 0;
					m_player_bid_h = 0;
					m_hitme_index = 0;
					m_dealer_hitme_index = 0;
					m_reset_totals = 1;
					generate_numbers();
				}
				if (m_dealer_total == m_player_total)
				{
					if (m_player_bid_t != 0)
					{
						m_player_bid_t = m_player_bid_t;
					}
					if (m_player_bid_h != 0)
					{
						m_player_money_h = m_player_bid_h;
					}


					m_player_bid = 0;
					m_player_bid_t = 0;
					m_player_bid_h = 0;
					m_hitme_index = 0;
					m_dealer_hitme_index = 0;
					m_reset_totals = 1;
					generate_numbers();
				}
			}
			else
			{
				if (m_dealer_total > m_player_total)
				{
					m_player_bid = 0;
					m_player_bid_t = 0;
					m_player_bid_h = 0;
					m_hitme_index = 0;
					m_dealer_hitme_index = 0;
					m_reset_totals = 1;
					generate_numbers();
				}

				if (m_dealer_total < m_player_total)
				{
					if (m_player_bid_t != 0)
					{
						m_player_bid_t = m_player_bid_t * 2;
					}
					if (m_player_bid_h != 0)
					{
						m_player_money_h = m_player_bid_h * 2;
					}


					m_player_bid = 0;
					m_player_bid_t = 0;
					m_player_bid_h = 0;
					m_hitme_index = 0;
					m_dealer_hitme_index = 0;
					m_reset_totals = 1;
					generate_numbers();
				}
				if (m_dealer_total == m_player_total)
				{
					if (m_player_bid_t != 0)
					{
						m_player_bid_t = m_player_bid_t;
					}
					if (m_player_bid_h != 0)
					{
						m_player_money_h = m_player_bid_h;
					}


					m_player_bid = 0;
					m_player_bid_t = 0;
					m_player_bid_h = 0;
					m_hitme_index = 0;
					m_dealer_hitme_index = 0;
					m_reset_totals = 1;
					generate_numbers();
				}
			}
		}
		else
		{
			if (m_dealer_total > m_player_total)
			{
				m_player_bid = 0;
				m_player_bid_t = 0;
				m_player_bid_h = 0;
				m_hitme_index = 0;
				m_dealer_hitme_index = 0;
				m_reset_totals = 1;
				generate_numbers();
			}

			if (m_dealer_total < m_player_total)
			{
				if (m_player_bid_t != 0)
				{
					m_player_bid_t = m_player_bid_t * 2;
				}
				if (m_player_bid_h != 0)
				{
					m_player_money_h = m_player_bid_h * 2;
				}


				m_player_bid = 0;
				m_player_bid_t = 0;
				m_player_bid_h = 0;
				m_hitme_index = 0;
				m_dealer_hitme_index = 0;
				m_reset_totals = 1;
				generate_numbers();
			}
			if (m_dealer_total == m_player_total)
			{
				if (m_player_bid_t != 0)
				{
					m_player_bid_t = m_player_bid_t;
				}
				if (m_player_bid_h != 0)
				{
					m_player_money_h = m_player_bid_h;
				}


				m_player_bid = 0;
				m_player_bid_t = 0;
				m_player_bid_h = 0;
				m_hitme_index = 0;
				m_dealer_hitme_index = 0;
				m_reset_totals = 1;
				generate_numbers();
			}
		}
	}
}
