#pragma once

//
// score_trump_call.h - Utility to score the calling of a trump suit
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <memory>
#include <unordered_set>

#include "fileio.h"
#include "json.h"

#include "euchre_card.h"
#include "euchre_hand.h"
#include "perception.h"

namespace rda
{
    namespace euchre
    {
        namespace score_trump_call
        {
            // the context of the game for scoring a particular trump suit
            struct score_context
            {
                std::shared_ptr<rda::json::node_object> m_file_data;

                e_suit m_suit = e_suit::INVALID;

                euchre_hand m_hand;
                euchre_card m_up_card;
                bool m_up_card_was_turned_down = false;
                euchre_seat_position m_dealer_position = euchre_seat_position::INVALID;

                perception m_left_perception;
                perception m_partner_perception;
                perception m_right_perception;
            }; // struct score_context

            namespace utils
            {
                // returns the right bower card for the given suit
                static euchre_card right_bower(const e_suit s)
                {
                    switch (s)
                    {
                        case e_suit::CLUBS:
                            return euchre_card(e_suit::CLUBS, e_rank::JACK);
                        case e_suit::DIAMONDS:
                            return euchre_card(e_suit::DIAMONDS, e_rank::JACK);
                        case e_suit::HEARTS:
                            return euchre_card(e_suit::HEARTS, e_rank::JACK);
                        case e_suit::SPADES:
                            return euchre_card(e_suit::SPADES, e_rank::JACK);
                        default:
                            return euchre_card();
                    }
                }

                // returns the left bower card for the given suit
                static euchre_card left_bower(const e_suit s)
                {
                    switch (s)
                    {
                        case e_suit::CLUBS:
                            return euchre_card(e_suit::SPADES, e_rank::JACK);
                        case e_suit::DIAMONDS:
                            return euchre_card(e_suit::HEARTS, e_rank::JACK);
                        case e_suit::HEARTS:
                            return euchre_card(e_suit::DIAMONDS, e_rank::JACK);
                        case e_suit::SPADES:
                            return euchre_card(e_suit::CLUBS, e_rank::JACK);
                        default:
                            return euchre_card();
                    }
                }

                // count the number of suits in a hand
                static size_t count_suits(const euchre_hand &h)
                {
                    std::unordered_set<e_suit> suits;
                    std::for_each(h.cbegin(), h.cend(), [&suits](auto &cd) {
                        suits.insert(cd.suit());
                    });

                    return suits.size();
                }

                // count the number of non-trump "winning" cards in a hand
                static size_t count_non_trump_winners(const score_context &ctx)
                {
                    size_t winners = 0;

                    // iterate through suits
                    for (auto s = e_suit::BEGIN; s != e_suit::END; ++s)
                    {
                        // for any suit that isn't being considered for trump
                        if (s != ctx.m_suit)
                        {
                            // check if contains ACE and KING suited, 2 winners
                            if (ctx.m_hand.contains({ euchre_card(s, e_rank::ACE), euchre_card(s, e_rank::KING)}))
                            {
                                winners += 2;
                                continue;
                            }

                            // check if ace is turned down and contains KING and QUEEN suited, 2 winners
                            if (ctx.m_up_card_was_turned_down &&
                                ctx.m_up_card == euchre_card(s, e_rank::ACE) &&
                                ctx.m_hand.contains({ euchre_card(s, e_rank::KING), euchre_card(s, e_rank::QUEEN)}))
                            {
                                winners += 2;
                                continue;
                            }

                            // check if king is turned down and contains ACE and QUEEN suited, 2 winners
                            if (ctx.m_up_card_was_turned_down &&
                                ctx.m_up_card == euchre_card(s, e_rank::KING) &&
                                ctx.m_hand.contains({ euchre_card(s, e_rank::ACE), euchre_card(s, e_rank::QUEEN)}))
                            {
                                winners += 2;
                                continue;
                            }

                            // check if contains ACE
                            if (ctx.m_hand.contains(euchre_card(s, e_rank::ACE)))
                            {
                                winners += 1;
                                continue;
                            }

                            // check if ace is turned down and contains king
                            if (ctx.m_up_card_was_turned_down &&
                                ctx.m_up_card == euchre_card(s, e_rank::ACE) &&
                                ctx.m_hand.contains(euchre_card(s, e_rank::KING)))
                            {
                                winners += 1;
                                continue;
                            }
                        }
                    }

                    return winners;
                }

                // count the number of opponents who passed on the up-card
                size_t count_opponents_passed_on_up_card(const score_context &ctx)
                {
                    size_t opponents = 0;

                    if (ctx.m_left_perception.passed_on_ordering_up)
                        ++opponents;

                    if (ctx.m_right_perception.passed_on_ordering_up)
                        ++opponents;

                    return opponents;
                }

            } // namespace utils

            // score having the right bower of trump
            static double score_have_right_bower_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_right_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(utils::right_bower(ctx.m_suit)))
                        return s;
                return 0.0f;
            }

            // score having the left bower of trump
            static double score_have_left_bower_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_left_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(utils::left_bower(ctx.m_suit)))
                        return s;
                return 0.0f;
            }

            // score having the ace of trump
            static double score_have_ace_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_ace_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_card(ctx.m_suit, e_rank::ACE)))
                        return s;
                return 0.0f;
            }

            // score having the king of trump
            static double score_have_king_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_king_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_card(ctx.m_suit, e_rank::KING)))
                        return s;
                return 0.0f;
            }

            // score having the queen of trump
            static double score_have_queen_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_queen_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_card(ctx.m_suit, e_rank::QUEEN)))
                        return s;
                return 0.0f;
            }

            // score having the ten of trump
            static double score_have_ten_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_ten_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_card(ctx.m_suit, e_rank::TEN)))
                        return s;
                return 0.0f;
            }

            // score having the nine of trump
            static double score_have_nine_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_nine_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_card(ctx.m_suit, e_rank::NINE)))
                        return s;
                return 0.0f;
            }

            // score would pick up right bower trump
            static double score_would_pick_up_right_bower_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/would_pick_up_right_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == utils::right_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score would pick up left bower trump
            static double score_would_pick_up_left_bower_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/would_pick_up_left_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == utils::left_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score would pick up ace trump
            static double score_would_pick_up_ace_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/would_pick_up_ace_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::ACE))
                        return s;
                return 0.0f;
            }

            // score would pick up king trump
            static double score_would_pick_up_king_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/would_pick_up_king_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::KING))
                        return s;
                return 0.0f;
            }

            // score would pick up queen trump
            static double score_would_pick_up_queen_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/would_pick_up_queen_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::QUEEN))
                        return s;
                return 0.0f;
            }

            // score would pick up ten trump
            static double score_would_pick_up_ten_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/would_pick_up_ten_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::TEN))
                        return s;
                return 0.0f;
            }

            // score would pick up nine trump
            static double score_would_pick_up_nine_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/would_pick_up_nine_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::NINE))
                        return s;
                return 0.0f;
            }

            // score partner would pick up right bower trump
            static double score_partner_would_pick_up_right_bower_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/partner_would_pick_up_right_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == utils::right_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score partner would pick up left bower trump
            static double score_partner_would_pick_up_left_bower_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/partner_would_pick_up_left_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == utils::left_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score partner would pick up ace trump
            static double score_partner_would_pick_up_ace_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/partner_would_pick_up_ace_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::ACE))
                        return s;
                return 0.0f;
            }

            // score partner would pick up king trump
            static double score_partner_would_pick_up_king_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/partner_would_pick_up_king_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::KING))
                        return s;
                return 0.0f;
            }

            // score partner would pick up queen trump
            static double score_partner_would_pick_up_queen_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/partner_would_pick_up_queen_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::QUEEN))
                        return s;
                return 0.0f;
            }

            // score partner would pick up ten trump
            static double score_partner_would_pick_up_ten_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/partner_would_pick_up_ten_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::TEN))
                        return s;
                return 0.0f;
            }

            // score partner would pick up nine trump
            static double score_partner_would_pick_up_nine_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/partner_would_pick_up_nine_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::NINE))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up right bower trump
            static double score_opponent_would_pick_up_right_bower_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/opponent_would_pick_up_right_bower_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_position == euchre_seat_position::LEFT || ctx.m_dealer_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == utils::right_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up left bower trump
            static double score_opponent_would_pick_up_left_bower_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/opponent_would_pick_up_left_bower_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_position == euchre_seat_position::LEFT || ctx.m_dealer_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == utils::left_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up ace trump
            static double score_opponent_would_pick_up_ace_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/opponent_would_pick_up_ace_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_position == euchre_seat_position::LEFT || ctx.m_dealer_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::ACE))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up king trump
            static double score_opponent_would_pick_up_king_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/opponent_would_pick_up_king_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_position == euchre_seat_position::LEFT || ctx.m_dealer_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::KING))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up queen trump
            static double score_opponent_would_pick_up_queen_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/opponent_would_pick_up_queen_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_position == euchre_seat_position::LEFT || ctx.m_dealer_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::QUEEN))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up ten trump
            static double score_opponent_would_pick_up_ten_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/opponent_would_pick_up_ten_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_position == euchre_seat_position::LEFT || ctx.m_dealer_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::TEN))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up nine trump
            static double score_opponent_would_pick_up_nine_trump(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/opponent_would_pick_up_nine_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_position == euchre_seat_position::LEFT || ctx.m_dealer_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::NINE))
                        return s;
                return 0.0f;
            }

            // score having one suit
            static double score_have_one_suited(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_one_suited");
                if (s != 0.0f)
                    if (utils::count_suits(ctx.m_hand) == 1)
                        return s;
                return 0.0f;
            }

            // score having two suits
            static double score_have_two_suited(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_two_suited");
                if (s != 0.0f)
                    if (utils::count_suits(ctx.m_hand) == 2)
                        return s;
                return 0.0f;
            }

            // score having three suits
            static double score_have_three_suited(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_three_suited");
                if (s != 0.0f)
                    if (utils::count_suits(ctx.m_hand) == 3)
                        return s;
                return 0.0f;
            }

            // score having four suits
            static double score_have_four_suited(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_four_suited");
                if (s != 0.0f)
                    if (utils::count_suits(ctx.m_hand) == 4)
                        return s;
                return 0.0f;
            }

            // score having four non trump winners
            static double score_have_four_non_trump_winners(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_four_non_trump_winners");
                if (s != 0.0f)
                    if (utils::count_non_trump_winners(ctx) == 4)
                        return s;
                return 0.0f;
            }

            // score having three non trump winners
            static double score_have_three_non_trump_winners(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_three_non_trump_winners");
                if (s != 0.0f)
                    if (utils::count_non_trump_winners(ctx) == 3)
                        return s;
                return 0.0f;
            }

            // score having two non trump winners
            static double score_have_two_non_trump_winners(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_two_non_trump_winners");
                if (s != 0.0f)
                    if (utils::count_non_trump_winners(ctx) == 2)
                        return s;
                return 0.0f;
            }

            // score having one non trump winners
            static double score_have_one_non_trump_winners(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_one_non_trump_winners");
                if (s != 0.0f)
                    if (utils::count_non_trump_winners(ctx) == 1)
                        return s;
                return 0.0f;
            }

            // score having zero non trump winners
            static double score_have_zero_non_trump_winners(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_zero_non_trump_winners");
                if (s != 0.0f)
                    if (utils::count_non_trump_winners(ctx) == 0)
                        return s;
                return 0.0f;
            }

            // score partner passed on up card
            static double score_partner_passed_on_up_card(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/partner_passed_on_up_card");
                if (s != 0.0f)
                    if (ctx.m_up_card_was_turned_down == false &&
                        ctx.m_suit == ctx.m_up_card.suit() &&
                        ctx.m_partner_perception.passed_on_ordering_up)
                        return s;
                return 0.0f;
            }

            // score one opponent passed on up card
            static double score_one_opponent_passed_on_up_card(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/one_opponent_passed_on_up_card");
                if (s != 0.0f)
                    if (ctx.m_up_card_was_turned_down == false &&
                        ctx.m_suit == ctx.m_up_card.suit() &&
                        utils::count_opponents_passed_on_up_card(ctx) == 1)
                        return s;
                return 0.0f;
            }

            // score two opponents passed on up card
            static double score_two_opponents_passed_on_up_card(const score_context &ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/two_opponents_passed_on_up_card");
                if (s != 0.0f)
                    if (ctx.m_up_card_was_turned_down == false &&
                        ctx.m_suit == ctx.m_up_card.suit() &&
                        utils::count_opponents_passed_on_up_card(ctx) == 2)
                        return s;
                return 0.0f;
            }

            // score the calling of a trump suit, given the provided game state
            static double score(const e_suit s,
                                const euchre_hand &h,
                                const euchre_card&up_card,
                                const bool up_card_turned_down,
                                euchre_seat_position dealer_position,
                                const perception &left_perception,
                                const perception &partner_perception,
                                const perception &right_perception)
            {
                rda::fileio f("euchre.json");
                f.read();

                score_context ctx;
                ctx.m_file_data = rda::json::parse(f.to_string());
                ctx.m_suit = s;
                ctx.m_hand = h;
                ctx.m_up_card = up_card;
                ctx.m_up_card_was_turned_down = up_card_turned_down;
                ctx.m_dealer_position = dealer_position;
                ctx.m_left_perception = left_perception;
                ctx.m_partner_perception = partner_perception;
                ctx.m_right_perception = right_perception;

                double total = 0.0f;
                total += score_have_right_bower_trump(ctx);
                total += score_have_left_bower_trump(ctx);
                total += score_have_ace_trump(ctx);
                total += score_have_king_trump(ctx);
                total += score_have_queen_trump(ctx);
                total += score_have_ten_trump(ctx);
                total += score_have_nine_trump(ctx);
                total += score_would_pick_up_right_bower_trump(ctx);
                total += score_would_pick_up_left_bower_trump(ctx);
                total += score_would_pick_up_ace_trump(ctx);
                total += score_would_pick_up_king_trump(ctx);
                total += score_would_pick_up_queen_trump(ctx);
                total += score_would_pick_up_ten_trump(ctx);
                total += score_would_pick_up_nine_trump(ctx);
                total += score_partner_would_pick_up_right_bower_trump(ctx);
                total += score_partner_would_pick_up_left_bower_trump(ctx);
                total += score_partner_would_pick_up_ace_trump(ctx);
                total += score_partner_would_pick_up_king_trump(ctx);
                total += score_partner_would_pick_up_queen_trump(ctx);
                total += score_partner_would_pick_up_ten_trump(ctx);
                total += score_partner_would_pick_up_nine_trump(ctx);
                total += score_opponent_would_pick_up_right_bower_trump(ctx);
                total += score_opponent_would_pick_up_left_bower_trump(ctx);
                total += score_opponent_would_pick_up_ace_trump(ctx);
                total += score_opponent_would_pick_up_king_trump(ctx);
                total += score_opponent_would_pick_up_queen_trump(ctx);
                total += score_opponent_would_pick_up_ten_trump(ctx);
                total += score_opponent_would_pick_up_nine_trump(ctx);
                total += score_have_one_suited(ctx);
                total += score_have_two_suited(ctx);
                total += score_have_three_suited(ctx);
                total += score_have_four_suited(ctx);
                total += score_have_four_non_trump_winners(ctx);
                total += score_have_three_non_trump_winners(ctx);
                total += score_have_two_non_trump_winners(ctx);
                total += score_have_one_non_trump_winners(ctx);
                total += score_have_zero_non_trump_winners(ctx);
                total += score_partner_passed_on_up_card(ctx);
                total += score_one_opponent_passed_on_up_card(ctx);
                total += score_two_opponents_passed_on_up_card(ctx);
                return total;
            }

        } // namespace score_trump_call

    } // namespace euchre

} // namespace rda
