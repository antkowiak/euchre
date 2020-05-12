#pragma once

//
// hand.h - Hand of cards in a euchre game
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <algorithm>
#include <vector>

#include "card.h"

namespace rda
{
    namespace euchre
    {
        // hand of cards in a euchre game
        class hand
        {
        private:
            // the cards in the hand
            std::vector<card> cards;

        public:
            // add one card to the hand
            void add_card(const card &c)
            {
                cards.push_back(c);
            }

            // add vector of cards to the hand
            void add_cards(const std::vector<card> &new_cards)
            {
                std::copy(new_cards.cbegin(), new_cards.cend(), cards.end());
            }

            // remove a card from the hand
            void remove_card(const card &c)
            {
                auto unused = std::remove(cards.begin(), cards.end(), c);
                static_cast<void>(unused);
            }

            // clear all cards from the hand
            void clear()
            {
                cards.clear();
            }

            // return the number of cards in the hand
            size_t size() const
            {
                return cards.size();
            }

            // returns true if the hand is empty
            bool empty() const
            {
                return cards.empty();
            }

        }; // class hand

    } // namespace euchre
} // namespace rda
