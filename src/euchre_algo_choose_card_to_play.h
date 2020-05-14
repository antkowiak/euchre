#pragma once

//
// euchre_algo_choose_card_to_play.h - Algorithm to choose what card to play
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <algorithm>
#include <vector>

#include "euchre_algo_card_sorter.h"
#include "euchre_card.h"
#include "euchre_hand.h"
#include "euchre_seat_position.h"

namespace rda
{
	namespace euchre
	{
		namespace euchre_algo_choose_card_to_play
		{
			// choose what card to play, if we are leading the trick
			static euchre_card choose_card_to_lead(
				const std::vector<euchre_card>& cards_played,
				const e_suit trump_suit,
				const euchre_hand& hand,
				const euchre_seat_position who_called_trump,
				const uint8_t num_tricks_team,
				const uint8_t num_tricks_opponent,
				const bool is_loner)
			{
				// start with all cards in hand
				std::vector<euchre_card> hand_cards(hand.cbegin(), hand.cend());

				return euchre_card();
			}

			// choose what card to play, if someone else already led
			static euchre_card choose_card_to_follow(
				const std::vector<euchre_card>& cards_played,
				const e_suit trump_suit,
				const euchre_hand& hand,
				const euchre_seat_position who_called_trump,
				const uint8_t num_tricks_team,
				const uint8_t num_tricks_opponent,
				const bool is_loner)
			{
				// start with all cards in hand
				std::vector<euchre_card> hand_cards(hand.cbegin(), hand.cend());

				// what suit was lead
				const e_suit suit_lead = euchre_algo::get_effective_suit(cards_played.front(), trump_suit);

				// check if this hand can follow suit
				const bool can_follow_suit = std::any_of(hand_cards.cbegin(), hand_cards.cend(),
					[trump_suit, suit_lead] (auto& c)
					{
						return euchre_algo::get_effective_suit(c.suit(), trump_suit) == suit_lead;
					});

				// if we can follow suit, remove all cards that aren't the suit lead
				hand_cards.erase(std::remove_if(hand_cards.begin(), hand_cards.end(),
					[trump_suit, suit_lead](auto& c) {
						return euchre_algo::get_effective_suit(c.suit(), trump_suit) != suit_lead;
					}),
					hand_cards.end());

				// if there is only one card, return it
				if (hand_cards.size() == 1)
					return hand_cards.front();

				// we have multiple cards that can be played... Now to choose one.

				// TODO

				return euchre_card();
			}

			// choose what card to play
			static euchre_card choose_card(
				const std::vector<euchre_card>& cards_played,
				const e_suit trump_suit,
				const euchre_hand & hand,
				const euchre_seat_position who_called_trump,
				const uint8_t num_tricks_team,
				const uint8_t num_tricks_opponent,
				const bool is_loner)

			{
				if (hand.empty())
					return euchre_card();

				else if (hand.size() == 1)
					return *(hand.cbegin());

				else if (cards_played.empty())
					return choose_card_to_lead(cards_played, trump_suit, hand, who_called_trump, num_tricks_team, num_tricks_opponent, is_loner);

				else
					return choose_card_to_follow(cards_played, trump_suit, hand, who_called_trump, num_tricks_team, num_tricks_opponent, is_loner);
			}

		} // namespace euchre_algo_choose_card_to_play

	} // namespace euchre

} // namespace rda
