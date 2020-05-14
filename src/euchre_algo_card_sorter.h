#pragma once

//
// euchre_algo_card_sorter.h - Algorithms to sort a vector of euchre cards
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <algorithm>
#include <random>
#include <vector>

#include "euchre_card.h"
#include "random_seeder.h"

namespace rda
{
    namespace euchre
    {
        namespace euchre_algo
        {
            // returns the "hoyle suit" of a trump suit (same color)
            static e_suit get_hoyle_suit(const e_suit trump_suit)
            {
                switch (trump_suit)
                {
                    case e_suit::CLUBS:
                        return e_suit::SPADES;
                    case e_suit::DIAMONDS:
                        return e_suit::HEARTS;
                    case e_suit::HEARTS:
                        return e_suit::DIAMONDS;
                    case e_suit::SPADES:
                        return e_suit::CLUBS;
                    default:
                        return e_suit::INVALID;
                }
            }

            // returns a sorted vector of cards of a trump shit
            static std::vector<euchre_card> get_trump_deck(const e_suit trump_suit)
            {
                const auto hoyle_suit = get_hoyle_suit(trump_suit);

                return {{trump_suit, e_rank::JACK}, {hoyle_suit, e_rank::JACK}, {trump_suit, e_rank::ACE}, {trump_suit, e_rank::KING}, {trump_suit, e_rank::QUEEN}, {trump_suit, e_rank::TEN}, {trump_suit, e_rank::NINE}};
            }

            // returns a sorted vector of cards of a hoyle suit
            static std::vector<euchre_card> get_hoyle_deck(const e_suit suit)
            {
                return {{suit, e_rank::ACE}, {suit, e_rank::KING}, {suit, e_rank::QUEEN}, {suit, e_rank::TEN}, {suit, e_rank::NINE}};
            }

            // returns sorted vector of cards for a given suit (with a specified trump suit)
            static std::vector<euchre_card> get_suit_deck(const e_suit suit, e_suit trump_suit)
            {
                if (suit == trump_suit)
                    return get_trump_deck(suit);

                if (suit == get_hoyle_suit(trump_suit))
                    return get_hoyle_deck(suit);

                return {{suit, e_rank::ACE}, {suit, e_rank::KING}, {suit, e_rank::QUEEN}, {suit, e_rank::JACK}, {suit, e_rank::TEN}, {suit, e_rank::NINE}};
            }

            // returns a sorted vector of cards of a full deck, with specified trump
            static std::vector<euchre_card> get_full_deck(const e_suit trump_suit)
            {
                // randomize the order of non trump suits
                std::vector<e_suit> non_trump_suits = {e_suit::CLUBS, e_suit::DIAMONDS, e_suit::HEARTS, e_suit::SPADES};
                non_trump_suits.erase(std::remove(non_trump_suits.begin(), non_trump_suits.end(), trump_suit));
                std::random_shuffle(non_trump_suits.begin(), non_trump_suits.end());

                // start with the trump cards
                auto full_deck = get_trump_deck(trump_suit);

                // iterate over the remaining suits, and append relevent sub-decks
                for (auto &suit : non_trump_suits)
                {
                    auto deck = get_suit_deck(suit, trump_suit);
                    full_deck.insert(full_deck.end(), deck.cbegin(), deck.cend());
                }

                return full_deck;
            }

        } // namespace euchre_algo

    } // namespace euchre

} // namespace rda
