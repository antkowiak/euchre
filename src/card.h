#pragma once

//
// card.h - Playing card in a euchre deck
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>
#include <sstream>
#include <string>

namespace rda
{
    namespace euchre
    {
        // card color
        enum class e_color : uint8_t
        {
            BLACK = 0,
            BEGIN = 0,
            RED = 1,
            INVALID = 2,
            END = 2
        }; // enum color

        // card suit
        enum class e_suit
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
        }; // enum rank

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

        // convert a suit to a string
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

        // playing card in a euchre deck
        class card
        {
        public:
            // default constructor
            card()
                : m_suit(e_suit::INVALID), m_rank(e_rank::INVALID)
            {
            }

            // initializing constructor
            card(const e_suit s, const e_rank r)
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
            bool operator==(const card &rhs) const
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

        }; // class card

    } // namespace euchre
} // namespace rda
