#pragma once

//
// euchre_utils.h - Utility functions for euchre
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>

#include "euchre_card.h"
#include "euchre_perception.h"

namespace rda
{
    namespace euchre
    {
        namespace euchre_utils
        {
            // calculate where "other_pos" is sitting, relative to "pos"
            static euchre_seat_position relative_seat_position(const uint8_t index, const uint8_t other_index)
            {
                if (other_index == index)
                    return euchre_seat_position::SELF;
                else if ((index + 1) % 4 == other_index)
                    return euchre_seat_position::LEFT;
                else if ((index + 2) % 4 == other_index)
                    return euchre_seat_position::ACROSS;
                else if ((index + 3) % 4 == other_index)
                    return euchre_seat_position::RIGHT;

                return euchre_seat_position::INVALID;
            }

            // returns the right bower card for the given suit
            static euchre_card right_bower(const e_suit s)
            {
                switch (s)
                {
                    case e_suit::CLUBS:
                        return euchre_card(e_suit::CLUBS, e_rank::JACK);
                    case e_suit::DIAMONDS:
                        return euchre_card(e_suit::DIAMONDS, e_rank::JACK);
                    case e_suit::HEARTS:
                        return euchre_card(e_suit::HEARTS, e_rank::JACK);
                    case e_suit::SPADES:
                        return euchre_card(e_suit::SPADES, e_rank::JACK);
                    default:
                        return euchre_card();
                }
            }

            // returns the left bower card for the given suit
            static euchre_card left_bower(const e_suit s)
            {
                switch (s)
                {
                    case e_suit::CLUBS:
                        return euchre_card(e_suit::SPADES, e_rank::JACK);
                    case e_suit::DIAMONDS:
                        return euchre_card(e_suit::HEARTS, e_rank::JACK);
                    case e_suit::HEARTS:
                        return euchre_card(e_suit::DIAMONDS, e_rank::JACK);
                    case e_suit::SPADES:
                        return euchre_card(e_suit::CLUBS, e_rank::JACK);
                    default:
                        return euchre_card();
                }
            }

        } // namespace euchre_utils

    } // namespace euchre

} // namespace rda
