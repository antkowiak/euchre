#pragma once

//
// euchre_trump_decision.h - Result of decision when offered trump
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>

#include "platform_defs.h"

#include "euchre_card_suit.h"

PUSH_WARN_DISABLE
WARN_DISABLE_GCC("-Wunused-function")

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

        // convert a trump decision to a suit
        static e_suit decision_to_suit(const e_trump_decision decision)
        {
            switch (decision)
            {
                case e_trump_decision::CALL_CLUBS:
                case e_trump_decision::CALL_CLUBS_LONER:
                    return e_suit::CLUBS;

                case e_trump_decision::CALL_DIAMONDS:
                case e_trump_decision::CALL_DIAMONDS_LONER:
                    return e_suit::DIAMONDS;

                case e_trump_decision::CALL_HEARTS:
                case e_trump_decision::CALL_HEARTS_LONER:
                    return e_suit::HEARTS;

                case e_trump_decision::CALL_SPADES:
                case e_trump_decision::CALL_SPADES_LONER:
                    return e_suit::SPADES;

                default:
                    return e_suit::INVALID;
            }
        }

        // returns true if the decision represents a loner call
        static bool is_loner(const e_trump_decision decision)
        {
            switch (decision)
            {
                case e_trump_decision::ORDER_UP_LONER:
                case e_trump_decision::CALL_CLUBS_LONER:
                case e_trump_decision::CALL_DIAMONDS_LONER:
                case e_trump_decision::CALL_HEARTS_LONER:
                case e_trump_decision::CALL_SPADES_LONER:
                    return true;

                default:
                    return false;
            }
        }

        // returns true if the decision is actually ordering a trump
        static bool is_ordering_trump(const e_trump_decision decision)
        {
            return (decision != e_trump_decision::PASS && decision != e_trump_decision::INVALID);
        }

        // returns true if the decision is actually calling a suit
        static bool is_calling_suit(const e_trump_decision decision)
        {
            switch (decision)
            {
                case e_trump_decision::CALL_CLUBS:
                case e_trump_decision::CALL_CLUBS_LONER:
                case e_trump_decision::CALL_DIAMONDS:
                case e_trump_decision::CALL_DIAMONDS_LONER:
                case e_trump_decision::CALL_HEARTS:
                case e_trump_decision::CALL_HEARTS_LONER:
                case e_trump_decision::CALL_SPADES:
                case e_trump_decision::CALL_SPADES_LONER:
                    return true;

                default:
                    return false;
            }
        }

    } // namespace euchre

} // namespace rda

POP_WARN_DISABLE
