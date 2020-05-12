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
                cards.insert(cards.end(), new_cards.cbegin(), new_cards.cend());
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

            // return true if hand contains a card
            bool contains(const card &c) const
            {
                return std::find(cards.cbegin(), cards.cend(), c) != cards.cend();
            }

            // returns true if hand contains all of given cards
            bool contains(const std::vector<card> &c) const
            {
                for (auto &a : c)
                    if (std::find(cards.cbegin(), cards.cend(), a) == cards.cend())
                        return false;

                return true;
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

            // const iterator for beginning of cards
            std::vector<card>::const_iterator cbegin() const
            {
                return cards.cbegin();
            }

            // const iterator for end of cards
            std::vector<card>::const_iterator cend() const
            {
                return cards.cend();
            }

        }; // class hand

    } // namespace euchre
} // namespace rda
