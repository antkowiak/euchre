#pragma once

//
// euchre_perception.h - The perception of another player in a euchre game
//
// Written by Ryan Antkowiak 
//

#include <cstdint>
#include <vector>

#include "euchre_card.h"
#include "euchre_constants.h"
#include "euchre_seat_position.h"
#include "euchre_trump_decision.h"
#include "euchre_utils.h"

namespace rda
{
    namespace euchre
    {
        // the perception of another player in a euchre game
        class euchre_perception
        {
        public:
            // the seat index where this player is sitting
            const uint8_t seat_index;

            // where the dealer is sitting, in relation
            uint8_t dealer_index = euchre_constants::INVALID_INDEX;
            euchre_seat_position dealer_position = euchre_seat_position::INVALID;

            // the "up card"
            euchre_card up_card;

            // decision the player made after being offerd the up card for trump
            e_trump_decision up_card_offer_decision = e_trump_decision::INVALID;

            // decision the player made after being offered to call any other trump suit
            e_trump_decision call_trump_offer_decision = e_trump_decision::INVALID;

            // cards that this player has played
            std::vector<euchre_card> cards_played;

            // cards that are known to be in this player's hand
            std::vector<euchre_card> cards_in_hand;

            // cards that are known to NOT be in this player's hand
            std::vector<euchre_card> cards_not_in_hand;

        public:
            // constructor
            euchre_perception(const uint8_t index)
                : seat_index(index)
            {
            }

            // reset the perception
            void reset()
            {
                dealer_index = euchre_constants::INVALID_INDEX;
                dealer_position = euchre_seat_position::INVALID;
                up_card = euchre_card();
                up_card_offer_decision = e_trump_decision::INVALID;
                call_trump_offer_decision = e_trump_decision::INVALID;

                cards_played.clear();
                cards_in_hand.clear();
                cards_not_in_hand.clear();
            }

            // update after deal
            void update_after_deal(const uint8_t dealer_index_, const euchre_card &up_card_)
            {
                up_card = up_card_;
                dealer_index = dealer_index_;
                dealer_position = euchre_utils::relative_seat_position(seat_index, dealer_index);

                if (dealer_position != euchre_seat_position::SELF)
                    cards_not_in_hand.push_back(up_card);
            }

            // update after up card offer
            void update_after_up_card_offer(const uint8_t offer_index, const e_trump_decision decision)
            {
                if (offer_index == seat_index)
                    up_card_offer_decision = decision;

                // if this is the perception of the dealer
                if (dealer_position == euchre_seat_position::SELF)
                {
                    // the up-card will *probably* either be in the hand, or not
                    if (is_ordering_up(decision))
                        cards_in_hand.push_back(up_card);
                    else
                        cards_not_in_hand.push_back(up_card);
                }
            }

            // update after trump offer
            void update_after_trump_offer(const uint8_t offer_index, const e_trump_decision decision)
            {
                if (offer_index == seat_index)
                    call_trump_offer_decision = decision;
            }

        }; // class euchre_perception

    } // namespace euchre

} // namespace rda
