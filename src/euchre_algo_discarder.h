#pragma once

//
// euchre_algo_discarder.h - Algorithm to discard a card from a euchre hand
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <algorithm>
#include <vector>

#include "euchre_card.h"
#include "euchre_card_rank.h"
#include "euchre_card_suit.h"
#include "euchre_constants.h"
#include "euchre_hand.h"
#include "random_seeder.h"

namespace rda
{
    namespace euchre
    {
        namespace euchre_algo
        {
            // returns true if the card is a trump card (when suit is trump)
            static bool is_trump_card(const euchre_card &card, const e_suit trump_suit)
            {
                // if the suit matches, it is trump
                if (card.suit() == trump_suit)
                    return true;

                // if it is a jack, look for the left bower
                if (card.rank() == e_rank::JACK)
                {
                    if (trump_suit == e_suit::CLUBS)
                        return card.suit() == e_suit::SPADES;
                    if (trump_suit == e_suit::DIAMONDS)
                        return card.suit() == e_suit::HEARTS;
                    if (trump_suit == e_suit::HEARTS)
                        return card.suit() == e_suit::DIAMONDS;
                    if (trump_suit == e_suit::SPADES)
                        return card.suit() == e_suit::CLUBS;
                }

                return false;
            }

            // sorter for cards that are trump suit
            struct trump_card_sorter
            {
                e_suit trump_suit = e_suit::INVALID;

                trump_card_sorter(const e_suit trump_suit_)
                    : trump_suit(trump_suit_)
                {
                }

                // compares rank, but accounts for special case with jacks
                bool operator()(const euchre_card &c1, const euchre_card &c2) const
                {
                    // compare both jacks
                    if (c1.rank() == c2.rank())
                        return c1.suit() == trump_suit;

                    // c1 is a jack, so it is higher
                    if (c1.rank() == e_rank::JACK)
                        return true;

                    // c2 is a jack, so it is higher
                    if (c2.rank() == e_rank::JACK)
                        return false;

                    // no jacks, just compare ranks
                    return c1.rank() > c2.rank();
                }
            };

            // sorter for cards that are not trump
            struct non_trump_card_sorter
            {
                // only compares rank
                bool operator()(const euchre_card &c1, const euchre_card &c2) const
                {
                    return c1.rank() > c2.rank();
                }
            };

            // attempt to discard the weakest card from a hand, when trump_suit is trump
            static void discarder(euchre_hand &hand, const euchre_card &card_added, const e_suit trump_suit)
            {
                // sanity check that the hand has the appropriate number of cards
                if (hand.size() != euchre_constants::EUCHRE_HAND_SIZE + 1)
                    return;

                // sanity check that the added card is actually in the hand
                if (!hand.contains(card_added))
                    return;

                // copy the cards from the hand into a local vector for convenience
                std::vector<euchre_card> input(hand.cbegin(), hand.cend());

                // set up vectors
                std::vector<euchre_card> trumps;
                std::vector<euchre_card> clubs;
                std::vector<euchre_card> diamonds;
                std::vector<euchre_card> hearts;
                std::vector<euchre_card> spades;

                // distribute the cards into the appropriate piles
                for (auto &card : input)
                {
                    if (is_trump_card(card, trump_suit))
                        trumps.push_back(card);
                    else if (card.suit() == e_suit::CLUBS)
                        clubs.push_back(card);
                    else if (card.suit() == e_suit::DIAMONDS)
                        diamonds.push_back(card);
                    else if (card.suit() == e_suit::HEARTS)
                        hearts.push_back(card);
                    else if (card.suit() == e_suit::SPADES)
                        spades.push_back(card);
                }

                // sort all the vectors
                std::sort(trumps.begin(), trumps.end(), trump_card_sorter(trump_suit));
                std::sort(clubs.begin(), clubs.end(), non_trump_card_sorter());
                std::sort(diamonds.begin(), diamonds.end(), non_trump_card_sorter());
                std::sort(hearts.begin(), hearts.end(), non_trump_card_sorter());
                std::sort(spades.begin(), spades.end(), non_trump_card_sorter());

                // make a vector of cards for cards to keep. start with all trumps.
                std::vector<euchre_card> output(trumps.cbegin(), trumps.cend());

                // if there are 6 cards in the hand, we need to actually discard a trump
                while (output.size() > euchre_constants::EUCHRE_HAND_SIZE)
                    output.pop_back();

                if (output.size() == euchre_constants::EUCHRE_HAND_SIZE)
                {
                    hand.set_cards(output);
                    return;
                }

                // make a vector of vectors of remaining cards
                std::vector<std::vector<euchre_card>> remaining;

                if (!clubs.empty())
                    remaining.push_back(clubs);
                if (!diamonds.empty())
                    remaining.push_back(diamonds);
                if (!hearts.empty())
                    remaining.push_back(hearts);
                if (!spades.empty())
                    remaining.push_back(spades);

                // shuffle the order we consider suits
                seed_randomizer();
                std::random_shuffle(remaining.begin(), remaining.end());

                // iterate over remaining containers. find the lowest rank that could short-suit
                euchre_card lowest_short_suit_card(e_suit::INVALID, e_rank::ACE);

                for (auto &v : remaining)
                    if (v.size() == 1)
                        if (v.front().rank() < lowest_short_suit_card.rank())
                            lowest_short_suit_card = v.front();

                // if we found a non-winner card that can short-suit the hand, discard it
                if (hand.contains(lowest_short_suit_card) && lowest_short_suit_card.rank() != e_rank::ACE)
                {
                    hand.remove_card(lowest_short_suit_card);
                    return;
                }

                // can't short-suit the hand, so just find the lowest rank card
                euchre_card lowest_card(e_suit::INVALID, e_rank::ACE);

                for (auto &v : remaining)
                    for (auto &c : v)
                    {
                        if (c.rank() <= lowest_card.rank())
                            lowest_card = c;
                    }

                if (hand.contains(lowest_card))
                {
                    hand.remove_card(lowest_card);
                    return;
                }

                // shouldn't get here... but ensure the hand does not have more than 5 cards
                if (hand.size() > euchre_constants::EUCHRE_HAND_SIZE)
                {
                    std::vector<euchre_card> h(hand.cbegin(), hand.cend());
                    h.resize(euchre_constants::EUCHRE_HAND_SIZE);
                    hand.set_cards(h);
                }
            }

        } // namespace euchre_algo

    } // namespace euchre

} // namespace rda
