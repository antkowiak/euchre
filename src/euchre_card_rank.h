#pragma once

//
// euchre_card_rank.h - Rank of a euchre card
//
// Written by Ryan Antkowiak 
//

#include <cstdint>

namespace rda
{
    namespace euchre
    {
        // card rank
        enum class e_rank : uint8_t
        {
            NINE = 9,
            BEGIN = 9,
            TEN = 10,
            JACK = 11,
            QUEEN = 12,
            KING = 13,
            ACE = 14,
            INVALID = 15,
            END = 15
        }; // enum e_rank

        // operator for iterating over card ranks
        static e_rank operator++(e_rank &rhs)
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

        // convert a rank to a string
        static std::string to_string(const e_rank &r)
        {
            switch (r)
            {
                case e_rank::NINE:
                    return "9";
                case e_rank::TEN:
                    return "10";
                case e_rank::JACK:
                    return "J";
                case e_rank::QUEEN:
                    return "Q";
                case e_rank::KING:
                    return "K";
                case e_rank::ACE:
                    return "A";
                default:
                    return "X";
            }
        }

    } // namespace euchre

} // namespace rda
