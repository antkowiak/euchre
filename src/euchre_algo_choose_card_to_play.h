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
#include "euchre_utils.h"
#include "euchre_seat_position.h"

namespace rda
{
    namespace euchre
    {
        namespace euchre_algo_choose_card_to_play
        {
            // game context for making decisions
            struct euchre_algo_choose_card_to_play_context
            {
                euchre_algo_choose_card_to_play_context(
                    const std::vector<euchre_card> &cards_played_,
                    const e_suit trump_suit_,
                    const euchre_hand &hand_,
                    const std::vector<euchre_card> hand_cards_,
                    const euchre_seat_position who_called_trump_,
                    const uint8_t trick_num_,
                    const uint8_t num_tricks_team_,
                    const uint8_t num_tricks_opponent_,
                    const bool is_loner_)
                    : cards_played(cards_played_),
                      trump_suit(trump_suit_),
                      hand(hand_),
                      hand_cards(hand_cards_),
                      who_called_trump(who_called_trump_),
                      trick_num(trick_num_),
                      num_tricks_team(num_tricks_team_),
                      num_tricks_opponent(num_tricks_opponent_),
                      is_loner(is_loner_)
                {
                }

                // cards played (by other players) so far for this trick
                const std::vector<euchre_card> &cards_played;

                // the trump suit
                const e_suit trump_suit;

                // the player's euchre hand
                const euchre_hand &hand;

                // cards in the player's euchre hand
                const std::vector<euchre_card> hand_cards;

                // the seat position who called trump
                const euchre_seat_position who_called_trump;

                // the trick number 0-4
                const uint8_t trick_num;

                // the number of tricks our team has taken
                const uint8_t num_tricks_team;

                // the number of tricks the opponent team has taken
                const uint8_t num_tricks_opponent;

                // true if this hand is being played alone by the caller of trump
                const bool is_loner;
            };

            // predicate to check if a hand contains a card
            static bool pred_hand_contains(const euchre_algo_choose_card_to_play_context &ctx, const euchre_card &card)
            {
                return std::find(ctx.hand_cards.cbegin(), ctx.hand.cend(), euchre_utils::right_bower(ctx.trump_suit)) != ctx.hand_cards.cend();
            }

            // predicate to check if this player called trump
            static bool pred_self_called_trump(const euchre_algo_choose_card_to_play_context &ctx)
            {
                return ctx.who_called_trump == euchre_seat_position::SELF;
            }

            // predicate to check if this player's partner called trump
            static bool pred_partner_called_trump(const euchre_algo_choose_card_to_play_context &ctx)
            {
                return ctx.who_called_trump == euchre_seat_position::ACROSS;
            }

            // predicate to check if an opponent player called trump
            static bool pred_opponent_called_trump(const euchre_algo_choose_card_to_play_context &ctx)
            {
                return ctx.who_called_trump == euchre_seat_position::LEFT ||
                       ctx.who_called_trump == euchre_seat_position::RIGHT;
            }

            // predicate to check if this is the first trick of the hand
            static bool pred_first_trick_of_hand(const euchre_algo_choose_card_to_play_context &ctx)
            {
                return ctx.trick_num == 0;
            }

            // predicate to check if this player called a loner
            static bool pred_self_called_loner(const euchre_algo_choose_card_to_play_context &ctx)
            {
                return ctx.is_loner && ctx.who_called_trump == euchre_seat_position::SELF;
            }

            // predicate to check if an opponent player has called a loner
            static bool pred_opponent_called_loner(const euchre_algo_choose_card_to_play_context &ctx)
            {
                return (ctx.is_loner && (ctx.who_called_trump == euchre_seat_position::LEFT || ctx.who_called_trump == euchre_seat_position::RIGHT));
            }

            // returns a true pair of a card to play has been selected
            static std::pair<bool, euchre_card> no_match()
            {
                return {false, euchre_card()};
            }

            static std::pair<bool, euchre_card> check_call_trump_leading_right(const euchre_algo_choose_card_to_play_context &ctx)
            {
                if (!pred_self_called_trump(ctx))
                    return no_match();

                if (!pred_first_trick_of_hand(ctx))
                    return no_match();

                if (pred_hand_contains(ctx, euchre_utils::right_bower(ctx.trump_suit)))
                    return {true, euchre_utils::right_bower(ctx.trump_suit)};

                return no_match();
            }

            // choose what card to play, if we are leading the trick
            static euchre_card choose_card_to_lead(const euchre_algo_choose_card_to_play_context &ctx)
            {
                // start with all cards in hand
                std::vector<euchre_card> hand_cards(ctx.hand.cbegin(), ctx.hand.cend());

                // TODO
                return hand_cards.front();
            }

            // choose what card to play, if someone else already led
            static euchre_card choose_card_to_follow(const euchre_algo_choose_card_to_play_context &ctx)
            {
                // start with all cards in hand
                std::vector<euchre_card> hand_cards(ctx.hand.cbegin(), ctx.hand.cend());

                // what suit was lead
                const e_suit suit_lead = euchre_algo::get_effective_suit(ctx.cards_played.front(), ctx.trump_suit);

                // check if this hand can follow suit
                const bool can_follow_suit = std::any_of(hand_cards.cbegin(), hand_cards.cend(),
                                                         [ctx, suit_lead](auto &c) {
                                                             return euchre_algo::get_effective_suit(c.suit(), trump_suit) == ctx.suit_lead;
                                                         });

                // if we can follow suit, remove all cards that aren't the suit lead
                hand_cards.erase(std::remove_if(hand_cards.begin(), hand_cards.end(),
                                                [ctx, suit_lead](auto &c) {
                                                    return euchre_algo::get_effective_suit(c.suit(), trump_suit) != ctx.suit_lead;
                                                }),
                                 hand_cards.end());

                // if there is only one card, return it
                if (hand_cards.size() == 1)
                    return hand_cards.front();

                // we have multiple cards that can be played... Now to choose one.

                // TODO

                return hand_cards.front();
            }

            // choose what card to play
            static euchre_card choose_card(
                const std::vector<euchre_card> &cards_played_,
                const e_suit trump_suit_,
                const euchre_hand &hand_,
                const euchre_seat_position who_called_trump_,
                const uint8_t trick_num_,
                const uint8_t num_tricks_team_,
                const uint8_t num_tricks_opponent_,
                const bool is_loner_)

            {
                euchre_algo_choose_card_to_play_context ctx(
                    cards_played_,
                    trump_suit_,
                    hand_,
                    std::vector<euchre_card>(hand_.cbegin(), hand_.cend()),
                    who_called_trump_,
                    trick_num_,
                    num_tricks_team_,
                    num_tricks_opponent_,
                    is_loner_);

                if (ctx.hand.empty())
                    return euchre_card();

                else if (ctx.hand.size() == 1)
                    return *(ctx.hand.cbegin());

                else if (ctx.cards_played.empty())
                    return choose_card_to_lead(ctx);

                else
                    return choose_card_to_follow(ctx);
            }

        } // namespace euchre_algo_choose_card_to_play

    } // namespace euchre

} // namespace rda
