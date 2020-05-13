#pragma once

//
// score_trump_call.h - Utility to score the calling of a trump suit
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <memory>

#include "fileio.h"
#include "json.h"

#include "euchre_card.h"
#include "euchre_hand.h"
#include "euchre_perception.h"
#include "euchre_utils.h"
#include "score_trump_call_context.h"

namespace rda
{
    namespace euchre
    {
        namespace score_trump_call
        {
            // score having the right bower of trump
            static double score_have_right_bower_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_right_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_utils::right_bower(ctx.m_suit)))
                        return s;
                return 0.0f;
            }

            // score having the left bower of trump
            static double score_have_left_bower_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_left_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_utils::left_bower(ctx.m_suit)))
                        return s;
                return 0.0f;
            }

            // score having the ace of trump
            static double score_have_ace_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_ace_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_card(ctx.m_suit, e_rank::ACE)))
                        return s;
                return 0.0f;
            }

            // score having the king of trump
            static double score_have_king_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_king_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_card(ctx.m_suit, e_rank::KING)))
                        return s;
                return 0.0f;
            }

            // score having the queen of trump
            static double score_have_queen_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_queen_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_card(ctx.m_suit, e_rank::QUEEN)))
                        return s;
                return 0.0f;
            }

            // score having the ten of trump
            static double score_have_ten_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_ten_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_card(ctx.m_suit, e_rank::TEN)))
                        return s;
                return 0.0f;
            }

            // score having the nine of trump
            static double score_have_nine_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_nine_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(euchre_card(ctx.m_suit, e_rank::NINE)))
                        return s;
                return 0.0f;
            }

            // score would pick up right bower trump
            static double score_would_pick_up_right_bower_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/would_pick_up_right_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_utils::right_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score would pick up left bower trump
            static double score_would_pick_up_left_bower_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/would_pick_up_left_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_utils::left_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score would pick up ace trump
            static double score_would_pick_up_ace_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/would_pick_up_ace_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::ACE))
                        return s;
                return 0.0f;
            }

            // score would pick up king trump
            static double score_would_pick_up_king_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/would_pick_up_king_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::KING))
                        return s;
                return 0.0f;
            }

            // score would pick up queen trump
            static double score_would_pick_up_queen_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/would_pick_up_queen_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::QUEEN))
                        return s;
                return 0.0f;
            }

            // score would pick up ten trump
            static double score_would_pick_up_ten_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/would_pick_up_ten_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::TEN))
                        return s;
                return 0.0f;
            }

            // score would pick up nine trump
            static double score_would_pick_up_nine_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/would_pick_up_nine_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::SELF &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::NINE))
                        return s;
                return 0.0f;
            }

            // score partner would pick up right bower trump
            static double score_partner_would_pick_up_right_bower_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/partner_would_pick_up_right_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_utils::right_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score partner would pick up left bower trump
            static double score_partner_would_pick_up_left_bower_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/partner_would_pick_up_left_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_utils::left_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score partner would pick up ace trump
            static double score_partner_would_pick_up_ace_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/partner_would_pick_up_ace_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::ACE))
                        return s;
                return 0.0f;
            }

            // score partner would pick up king trump
            static double score_partner_would_pick_up_king_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/partner_would_pick_up_king_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::KING))
                        return s;
                return 0.0f;
            }

            // score partner would pick up queen trump
            static double score_partner_would_pick_up_queen_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/partner_would_pick_up_queen_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::QUEEN))
                        return s;
                return 0.0f;
            }

            // score partner would pick up ten trump
            static double score_partner_would_pick_up_ten_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/partner_would_pick_up_ten_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::TEN))
                        return s;
                return 0.0f;
            }

            // score partner would pick up nine trump
            static double score_partner_would_pick_up_nine_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/partner_would_pick_up_nine_trump");
                if (s != 0.0f)
                    if (ctx.m_dealer_seat_position == euchre_seat_position::ACROSS &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::NINE))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up right bower trump
            static double score_opponent_would_pick_up_right_bower_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/opponent_would_pick_up_right_bower_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_seat_position == euchre_seat_position::LEFT || ctx.m_dealer_seat_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_utils::right_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up left bower trump
            static double score_opponent_would_pick_up_left_bower_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/opponent_would_pick_up_left_bower_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_seat_position == euchre_seat_position::LEFT || ctx.m_dealer_seat_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_utils::left_bower(ctx.m_suit))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up ace trump
            static double score_opponent_would_pick_up_ace_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/opponent_would_pick_up_ace_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_seat_position == euchre_seat_position::LEFT || ctx.m_dealer_seat_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::ACE))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up king trump
            static double score_opponent_would_pick_up_king_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/opponent_would_pick_up_king_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_seat_position == euchre_seat_position::LEFT || ctx.m_dealer_seat_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::KING))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up queen trump
            static double score_opponent_would_pick_up_queen_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/opponent_would_pick_up_queen_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_seat_position == euchre_seat_position::LEFT || ctx.m_dealer_seat_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::QUEEN))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up ten trump
            static double score_opponent_would_pick_up_ten_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/opponent_would_pick_up_ten_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_seat_position == euchre_seat_position::LEFT || ctx.m_dealer_seat_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::TEN))
                        return s;
                return 0.0f;
            }

            // score opponent would pick up nine trump
            static double score_opponent_would_pick_up_nine_trump(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/opponent_would_pick_up_nine_trump");
                if (s != 0.0f)
                    if ((ctx.m_dealer_seat_position == euchre_seat_position::LEFT || ctx.m_dealer_seat_position == euchre_seat_position::RIGHT) &&
                        ctx.m_up_card == euchre_card(ctx.m_suit, e_rank::NINE))
                        return s;
                return 0.0f;
            }

            // score having one suit
            static double score_have_one_suited(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_one_suited");
                if (s != 0.0f)
                    if (ctx.m_num_suits == 1)
                        return s;
                return 0.0f;
            }

            // score having two suits
            static double score_have_two_suited(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_two_suited");
                if (s != 0.0f)
                    if (ctx.m_num_suits == 2)
                        return s;
                return 0.0f;
            }

            // score having three suits
            static double score_have_three_suited(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_three_suited");
                if (s != 0.0f)
                    if (ctx.m_num_suits == 3)
                        return s;
                return 0.0f;
            }

            // score having four suits
            static double score_have_four_suited(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_four_suited");
                if (s != 0.0f)
                    if (ctx.m_num_suits == 4)
                        return s;
                return 0.0f;
            }

            // score having four non trump winners
            static double score_have_four_non_trump_winners(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_four_non_trump_winners");
                if (s != 0.0f)
                    if (ctx.m_num_non_trump_winners == 4)
                        return s;
                return 0.0f;
            }

            // score having three non trump winners
            static double score_have_three_non_trump_winners(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_three_non_trump_winners");
                if (s != 0.0f)
                    if (ctx.m_num_non_trump_winners == 3)
                        return s;
                return 0.0f;
            }

            // score having two non trump winners
            static double score_have_two_non_trump_winners(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_two_non_trump_winners");
                if (s != 0.0f)
                    if (ctx.m_num_non_trump_winners == 2)
                        return s;
                return 0.0f;
            }

            // score having one non trump winners
            static double score_have_one_non_trump_winners(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_one_non_trump_winners");
                if (s != 0.0f)
                    if (ctx.m_num_non_trump_winners == 1)
                        return s;
                return 0.0f;
            }

            // score having zero non trump winners
            static double score_have_zero_non_trump_winners(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/have_zero_non_trump_winners");
                if (s != 0.0f)
                    if (ctx.m_num_non_trump_winners == 0)
                        return s;
                return 0.0f;
            }

            // score partner passed on up card
            static double score_partner_passed_on_up_card(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/partner_passed_on_up_card");
                if (s != 0.0f)
                    if (ctx.m_up_card_was_turned_down == false &&
                        ctx.m_suit == ctx.m_up_card.suit() &&
                        ctx.m_partner_perception.up_card_offer_decision == e_trump_decision::PASS)
                        return s;
                return 0.0f;
            }

            // score one opponent passed on up card
            static double score_one_opponent_passed_on_up_card(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/one_opponent_passed_on_up_card");
                if (s != 0.0f)
                    if (ctx.m_up_card_was_turned_down == false &&
                        ctx.m_suit == ctx.m_up_card.suit() &&
                        ctx.m_num_opponents_passed_on_up_card == 1)
                        return s;
                return 0.0f;
            }

            // score two opponents passed on up card
            static double score_two_opponents_passed_on_up_card(const score_trump_call_context &ctx)
            {
                const double s = ctx.get_score_value("trump_call/two_opponents_passed_on_up_card");
                if (s != 0.0f)
                    if (ctx.m_up_card_was_turned_down == false &&
                        ctx.m_suit == ctx.m_up_card.suit() &&
                        ctx.m_num_opponents_passed_on_up_card == 2)
                        return s;
                return 0.0f;
            }

            // score the calling of a trump suit, given the provided game state
            static score_trump_call_context score(const e_suit suit,
                                                  const euchre_hand &hand,
                                                  const euchre_card &up_card,
                                                  const bool up_card_was_turned_down,
                                                  const euchre_seat_position dealer_seat_position,
                                                  const euchre_perception &left_perception,
                                                  const euchre_perception &partner_perception,
                                                  const euchre_perception &right_perception)
            {
                rda::fileio f("euchre.json");
                f.read();

                score_trump_call_context ctx(suit,
                                             hand,
                                             up_card,
                                             up_card_was_turned_down,
                                             dealer_seat_position,
                                             left_perception,
                                             partner_perception,
                                             right_perception);

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
                ctx.set_total_score(total);

                return ctx;
            }

        } // namespace score_trump_call

    } // namespace euchre

} // namespace rda
