#pragma once

// The "perception" of an opponent player

#include <cstdint>
#include <vector>

#include "card.h"

namespace rda
{
	namespace euchre
	{
		enum class e_seat_position : uint8_t
		{
			SELF    = 0,
			LEFT    = 1,
			ACROSS  = 2,
			RIGHT   = 3,
			INVALID = 4
		};

		class perception
		{
		public:
			// where this player is sitting, in relation
			e_seat_position seat_position = e_seat_position::INVALID;

			// where the dealer is sitting, in relation
			e_seat_position dealer_position = e_seat_position::INVALID;

			// the "up card"
			card up_card;

			// true if this player ordered up the card for trump
			bool ordered_up = false;

			// true if this player passed on ordering up the card
			bool passed_on_ordering_up = false;

			// true if this player called trump
			bool called_trump = false;

			// true if this player passed on calling trump
			bool passed_on_calling_trump = false;			


			// cards that this player has played
			std::vector<card> cards_played;

			// cards that are known to be in this player's hand
			std::vector<card> cards_in_hand;

			// cards that are known to NOT be in this player's hand
			std::vector<card> cards_not_in_hand;

			// reset the perception
			void reset()
			{
				seat_position = e_seat_position::INVALID;
				dealer_position = e_seat_position::INVALID;
				up_card = card();
				ordered_up = false;
				passed_on_ordering_up = false;
				called_trump = false;
				passed_on_calling_trump = false;

				cards_played.clear();
				cards_in_hand.clear();
				cards_not_in_hand.clear();
			}

		};
	}
}