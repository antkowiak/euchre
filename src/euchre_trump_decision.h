#pragma once

//
// euchre_trump_decision.h - Result of decision when offered trump
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>

namespace rda
{
    namespace euchre
    {
        enum class e_trump_decision : uint8_t
        {
            PASS = 0,
            BEGIN = 0,

            ORDER_UP = 1,
            ORDER_UP_LONER = 2,

            CALL_CLUBS = 3,
            CALL_CLUBS_LONER = 4,

            CALL_DIAMONDS = 5,
            CALL_DIAMONDS_LONER = 6,

            CALL_HEARTS = 7,
            CALL_HEARTS_LONER = 8,

            CALL_SPADES = 9,
            CALL_SPADES_LONER = 10,

            INVALID = 11,
            END = 11

        }; // enum e_trump_decision

    } // namespace euchre

} // namespace rda
