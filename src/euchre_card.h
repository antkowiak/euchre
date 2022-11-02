#pragma once

//
// euchre_card.h - Playing card in a euchre deck
//
// Written by Ryan Antkowiak 
//

#include <cstdint>
#include <sstream>
#include <string>

#include "euchre_card_color.h"
#include "euchre_card_rank.h"
#include "euchre_card_suit.h"

namespace rda
{
    namespace euchre
    {
        // playing card in a euchre deck
        class euchre_card
        {
        public:
            // default constructor
            euchre_card()
                : m_suit(e_suit::INVALID), m_rank(e_rank::INVALID)
            {
            }

            // initializing constructor
            euchre_card(const e_suit s, const e_rank r)
                : m_suit(s), m_rank(r)
            {
            }

            // returns the card color
            e_color color() const
            {
                if (m_suit == e_suit::INVALID)
                    return e_color::INVALID;
                if (m_suit == e_suit::CLUBS || m_suit == e_suit::SPADES)
                    return e_color::BLACK;
                return e_color::RED;
            }

            // returns the card suit
            e_suit suit() const
            {
                return m_suit;
            }

            // returns the card rank
            e_rank rank() const
            {
                return m_rank;
            }

            // returns true if the cards are equal
            bool operator==(const euchre_card &rhs) const
            {
                return (m_rank == rhs.m_rank) && (m_suit == rhs.m_suit);
            }

            // returns string representation of the card
            std::string to_string() const
            {
                std::stringstream ss;

                ss << "[" << rda::euchre::to_string(m_rank)
                   << rda::euchre::to_string(m_suit) << "]";

                return ss.str();
            }

        private:
            // the card suit
            e_suit m_suit;

            // the card rank
            e_rank m_rank;

        }; // class euchre_card

    } // namespace euchre

} // namespace rda
