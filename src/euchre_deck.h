#pragma once

//
// euchre_deck.h - Euchre deck of cards
//
// Written by Ryan Antkowiak 
//

#include <algorithm>
#include <cstdlib>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "euchre_card.h"
#include "euchre_hand.h"
#include "random_seeder.h"

namespace rda
{
    namespace euchre
    {
        // euchre deck of cards
        class euchre_deck
        {
        private:
            // cards in the deck
            std::vector<euchre_card> cards;

            // discarded cards
            std::vector<euchre_card> discard_pile;

        public:
            // default constructor
            euchre_deck()
            {
            }

            // initialize cards in a euchre deck
            void init()
            {
                cards.clear();
                discard_pile.clear();

                for (auto s = rda::euchre::e_suit::BEGIN; s != e_suit::END; ++s)
                    for (auto r = e_rank::BEGIN; r != e_rank::END; ++r)
                        cards.push_back(euchre_card(s, r));
            }

            // shuffle the deck
            void shuffle()
            {
                rda::euchre::seed_randomizer();
                std::random_shuffle(cards.begin(), cards.end());
            }

            // deal n cards out of the deck and into hand
            void deal(euchre_hand &hand, const size_t n)
            {
                if (n <= cards.size())
                {
                    hand.add_cards(std::vector<euchre_card>(cards.cbegin(), cards.cbegin() + n));
                    cards.erase(cards.begin(), cards.begin() + n);
                }
            }

            // draw one card from top of the deck
            euchre_card draw()
            {
                euchre_card c;

                if (!cards.empty())
                {
                    c = cards[0];
                    cards.erase(cards.begin(), cards.begin() + 1);
                }

                return c;
            }

            // put cards into the discard pile
            void discard(const std::vector<euchre_card> &d)
            {
                std::copy(d.cbegin(), d.cend(), discard_pile.end());
            }

            // return the number of cards in the deck
            size_t size() const
            {
                return cards.size();
            }

            // return the number of discarded cards
            size_t size_discard() const
            {
                return discard_pile.size();
            }

            // return true if the deck is empty
            size_t empty() const
            {
                return cards.empty();
            }

            // return a string representation of the deck
            std::string to_string() const
            {
                std::stringstream ss;

                ss << "cards:  ";
                for (auto &c : cards)
                    ss << " " << c.to_string();
                ss << std::endl;

                ss << "discard:";
                for (auto &d : discard_pile)
                    ss << " " << d.to_string();

                ss << std::endl;

                return ss.str();
            }

        }; // class euchre_deck

    } // namespace euchre

} // namespace rda
