#pragma once

#include <algorithm>
#include <cstdlib>
#include <vector>

#include "card.h"
#include "hand.h"
#include "random_seeder.h"

namespace rda
{
    namespace euchre
    {
        class deck
        {
        private:
            std::vector<rda::euchre::card> cards;
            std::vector<rda::euchre::card> discard_pile;

        public:
            deck()
            {
                init();
            }

            void init()
            {
                cards.clear();
                discard_pile.clear();

                for (auto s = rda::euchre::e_suit::CLUBS; s != e_suit::INVALID; ++s)
                    for (auto r = e_rank::NINE; r != e_rank::INVALID; ++r)
                        cards.push_back(card(s, r));
            }

            void shuffle()
            {
                rda::euchre::seed_randomizer();
                std::shuffle(cards.begin(), cards.end(), std::rand);
            }

            void deal(hand &hand, const size_t n)
            {
                if (n <= cards.size())
                {
                    hand.add_cards(std::vector<card>(cards.begin(), cards.begin() + n));
                    cards.erase(cards.begin(), cards.begin() + n);
                }
            }
        };

    } // namespace euchre
} // namespace rda
