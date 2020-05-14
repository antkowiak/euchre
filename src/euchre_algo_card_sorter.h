#pragma once

//
// euchre_algo_card_sorter.h - Algorithms to sort a vector of euchre cards
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <algorithm>
#include <map>
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
                rda::euchre::seed_randomizer();
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

            // return the effective suit of a card, given the trump suit
            static e_suit get_effective_suit(const euchre_card &card, const e_suit trump_suit)
            {
                if (card.rank() == e_rank::JACK && get_hoyle_suit(card.suit()) == trump_suit)
                    return trump_suit;
                else
                    return card.suit();
            }

            // metrics on a collection of cards
            struct deck_metrics
            {
                // the trump suit
                e_suit trump_suit = e_suit::INVALID;

                // count of trump suits
                std::map<e_suit, uint8_t> suit_counts;

                // constructor
                deck_metrics(const e_suit trump, const std::vector<euchre_card> &deck)
                    : trump_suit(trump)
                {
                    std::for_each(deck.cbegin(), deck.cend(), [this](auto &c) {
                        this->suit_counts[get_effective_suit(c, this->trump_suit)]++;
                    });
                }
            };

            // returns true if the card is the right bower of given trump suit
            static bool is_right_bower(const euchre_card &card, const e_suit trump)
            {
                return (card.rank() == e_rank::JACK && card.suit() == trump);
            }

            // returns true if the card is the left bower of given trump suit
            static bool is_left_bower(const euchre_card &card, const e_suit trump)
            {
                return (card.rank() == e_rank::JACK && card.suit() == get_hoyle_suit(trump));
            }

            // return true if 'c' is the highest card of it's suit in the deck, given a trump suit, and a list of excepted cards
            static bool is_highest_of_non_trump_suit_except(const euchre_card &c,
                                                            const std::vector<euchre_card> &deck,
                                                            const e_suit trump_suit,
                                                            const std::vector<euchre_card> &except)
            {
                const e_suit hoyle_suit = get_hoyle_suit(trump_suit);

                return false;

                // TODO
            }

            // comparator to compare euchre cards
            class card_comp_by_suit
            {
            private:
                const deck_metrics &metrics;

            public:
                card_comp_by_suit(const deck_metrics &dm)
                    : metrics(dm)
                {
                }

                // returns true if c1 comes before c2 in the sort
                bool operator()(const euchre_card &c1, const euchre_card &c2) const
                {
                    // if the cards are equal, just return
                    if (c1 == c2)
                        return false;

                    // right bower is always first
                    if (is_right_bower(c1, metrics.trump_suit))
                        return true;

                    if (is_right_bower(c2, metrics.trump_suit))
                        return false;

                    // left bower comes before any card except the right bower
                    if (is_left_bower(c1, metrics.trump_suit))
                        return true;

                    if (is_left_bower(c2, metrics.trump_suit))
                        return false;

                    // both cards are trump, return true if c1 is higher trump
                    if (c1.suit() == metrics.trump_suit && c2.suit() == metrics.trump_suit)
                        return c1.rank() > c2.rank();

                    // if only c1 is trump, return true since c1 is higher
                    if (c1.suit() == metrics.trump_suit)
                        return true;

                    // if only c2 is trump, return false, since c2 is higher
                    if (c2.suit() == metrics.trump_suit)
                        return false;

                    // if suits are not the same
                    if (c1.suit() != c2.suit())
                        return c1.suit() < c2.suit();

                    // if suits are the same, just compare ranks
                    return c1.rank() > c2.rank();
                }
            };

            // sort a vector of cards, given a trump suit
            static void sort_deck_by_suit(std::vector<euchre_card> &deck, const e_suit trump_suit)
            {
                // create metrics for the deck
                const deck_metrics dm(trump_suit, deck);
                // sort the deck
                std::sort(deck.begin(), deck.end(), card_comp_by_suit(dm));
            }

        } // namespace euchre_algo

    } // namespace euchre

} // namespace rda
