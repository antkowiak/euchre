#pragma once

#include <algorithm>
#include <vector>

#include "card.h"

namespace rda
{
    namespace euchre
    {
        class hand
        {
        private:
            std::vector<card> cards;

        public:
            void add_card(const card &c)
            {
                cards.push_back(c);
            }

            void add_cards(const std::vector<card> &new_cards)
            {
                for (auto &c : new_cards)
                    cards.push_back(c);
            }

            void remove_card(const card &c)
            {
                std::remove(cards.begin(), cards.end(), c);
            }

            void clear()
            {
                cards.clear();
            }

        }; // class hand

    } // namespace euchre
} // namespace rda
