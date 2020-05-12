#pragma once

#include <cstdint>

namespace rda
{
	namespace euchre
	{
		enum class e_color : uint8_t
		{
			BLACK = 0,
			RED   = 1,
			INVALID = 2
		}; // enum color

		enum class e_suit
		{
			CLUBS    = 0,
			DIAMONDS = 1,
			HEARTS   = 2,
			SPADES   = 3,
			INVALID  = 4
		}; // enum suit

		static e_suit operator++(e_suit & rhs)
		{
			switch (rhs)
			{
			case e_suit::CLUBS:
				rhs = e_suit::DIAMONDS;
				break;
			case e_suit::DIAMONDS:
				rhs = e_suit::HEARTS;
				break;
			case e_suit::HEARTS:
				rhs = e_suit::SPADES;
				break;
			case e_suit::SPADES:
			default:
				rhs = e_suit::INVALID;
				break;
			}
			return rhs;
		}

		enum class e_rank : uint8_t
		{
			NINE    = 9,
			TEN     = 10,
			JACK    = 11,
			QUEEN   = 12,
			KING    = 13,
			ACE     = 14,
			INVALID = 15
		}; // enum rank

		static e_rank operator++(e_rank& rhs)
		{
			switch (rhs)
			{
			case e_rank::NINE:
				rhs = e_rank::TEN;
				break;
			case e_rank::TEN:
				rhs = e_rank::JACK;
				break;
			case e_rank::JACK:
				rhs = e_rank::QUEEN;
				break;
			case e_rank::QUEEN:
				rhs = e_rank::KING;
				break;
			case e_rank::KING:
				rhs = e_rank::ACE;
				break;
			case e_rank::ACE:
			default:
				rhs = e_rank::INVALID;
				break;
			}
			return rhs;
		}

		class card
		{
		public:

			card()
				: m_suit(e_suit::INVALID), m_rank(e_rank::INVALID)
			{
			}

			card(const e_suit s, const e_rank r)
				: m_suit(s), m_rank(r)
			{
			}

			e_color color() const
			{
				if (m_suit == e_suit::INVALID)
					return e_color::INVALID;
				if (m_suit == e_suit::CLUBS || m_suit == e_suit::SPADES)
					return e_color::BLACK;
				return e_color::RED;
			}

			e_suit suit() const
			{
				return m_suit;
			}

			e_rank rank() const
			{
				return m_rank;
			}

			bool operator == (const card& rhs) const
			{
				return (m_rank == rhs.m_rank) && (m_suit == rhs.m_suit);
			}

		private:
			e_suit m_suit;
			e_rank m_rank;
		}; // class card

	} // namespace euchre
} // namespace rda
