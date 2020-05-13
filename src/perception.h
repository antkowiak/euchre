#pragma once

//
// perception.h - The perception of another player in a euchre game
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>
#include <vector>

#include "euchre_card.h"
#include "euchre_seat_position.h"
#include "euchre_utils.h"

namespace rda
{
    namespace euchre
    {
        // the perception of another player in a euchre game
        class perception
        {
        public:
            // where this player is sitting, in relation
            euchre_seat_position seat_position = euchre_seat_position::INVALID;

            // where the dealer is sitting, in relation
            euchre_seat_position dealer_position = euchre_seat_position::INVALID;

            // the "up card"
            euchre_card up_card;

            // true if this player ordered up the card for trump
            bool ordered_up = false;

            // true if this player passed on ordering up the card
            bool passed_on_ordering_up = false;

            // true if this player called trump
            bool called_trump = false;

            // true if this player passed on calling trump
            bool passed_on_calling_trump = false;

            // cards that this player has played
            std::vector<euchre_card> cards_played;

            // cards that are known to be in this player's hand
            std::vector<euchre_card> cards_in_hand;

            // cards that are known to NOT be in this player's hand
            std::vector<euchre_card> cards_not_in_hand;

            // reset the perception
            void reset()
            {
                seat_position = euchre_seat_position::INVALID;
                dealer_position = euchre_seat_position::INVALID;
                up_card = euchre_card();
                ordered_up = false;
                passed_on_ordering_up = false;
                called_trump = false;
                passed_on_calling_trump = false;

                cards_played.clear();
                cards_in_hand.clear();
                cards_not_in_hand.clear();
            }

            // update after deal
            void update_after_deal(const uint8_t dealer, const euchre_card& up_card_)
            {
                up_card = up_card_;
                //dealer_position = dealer;
                // TODO



            }

        }; // class perception

    } // namespace euchre
} // namespace rda