#pragma once

//
// euchre_card_suit.h - Suit of a euchre card
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>

namespace rda
{
    namespace euchre
    {
        // card suit
        enum class e_suit : uint8_t
        {
            CLUBS = 0,
            BEGIN = 0,
            DIAMONDS = 1,
            HEARTS = 2,
            SPADES = 3,
            INVALID = 4,
            END = 4
        }; // enum suit

        // operator for iterating over suits
        static e_suit operator++(e_suit &rhs)
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

        // convert a suit to a string
        static std::string to_string(const e_suit &s)
        {
            switch (s)
            {
                case e_suit::CLUBS:
                    return "C";
                case e_suit::DIAMONDS:
                    return "D";
                case e_suit::HEARTS:
                    return "H";
                case e_suit::SPADES:
                    return "S";
                default:
                    return "X";
            }
        }

    } // namespace euchre

} // namespace rda
