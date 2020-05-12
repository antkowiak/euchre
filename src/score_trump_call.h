#pragma once

//
// score_trump_call.h - Utility to score the calling of a trump suit
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <memory>

#include "fileio.h"
#include "json.h"

#include "card.h"
#include "hand.h"
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

                hand m_hand;
                card m_up_card;
                e_seat_position m_dealer_position = e_seat_position::INVALID;

                perception m_left_perception;
                perception m_partner_perception;
                perception m_right_perception;
            }; // struct score_context

            // returns the right bauer card for the given suit
            static card right_bauer(const e_suit s)
            {
                switch (s)
                {
                case e_suit::CLUBS:
                    return card(e_suit::CLUBS, e_rank::JACK);
                case e_suit::DIAMONDS:
                    return card(e_suit::DIAMONDS, e_rank::JACK);
                case e_suit::HEARTS:
                    return card(e_suit::HEARTS, e_rank::JACK);
                case e_suit::SPADES:
                    return card(e_suit::SPADES, e_rank::JACK);
                default:
                    return card();
                }
            }

            // returns the left bauder card for the given suit
            static card left_bauer(const e_suit s)
            {
                switch (s)
                {
                case e_suit::CLUBS:
                    return card(e_suit::SPADES, e_rank::JACK);
                case e_suit::DIAMONDS:
                    return card(e_suit::HEARTS, e_rank::JACK);
                case e_suit::HEARTS:
                    return card(e_suit::DIAMONDS, e_rank::JACK);
                case e_suit::SPADES:
                    return card(e_suit::CLUBS, e_rank::JACK);
                default:
                    return card();
                }
            }

            // score having the right bower of trump
            static double score_have_right_bower_trump(const score_context& ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_right_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(right_bauer(ctx.m_suit)))
                        return s;
                return 0.0f;
            }

            // score having the left bauer of trump
            static double score_have_left_bower_trump(const score_context& ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_left_bower_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(left_bauer(ctx.m_suit)))
                        return s;
                return 0.0f;
            }

            // score having the ace of trump
            static double score_have_ace_trump(const score_context& ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_ace_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(card(ctx.m_suit, e_rank::ACE)))
                        return s;
                return 0.0f;
            }

            // score having the king of trump
            static double score_have_king_trump(const score_context& ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_king_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(card(ctx.m_suit, e_rank::KING)))
                        return s;
                return 0.0f;
            }

            // score having the queen of trump
            static double score_have_queen_trump(const score_context& ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_queen_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(card(ctx.m_suit, e_rank::QUEEN)))
                        return s;
                return 0.0f;
            }

            // score having the ten of trump
            static double score_have_ten_trump(const score_context& ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_ten_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(card(ctx.m_suit, e_rank::TEN)))
                        return s;
                return 0.0f;
            }

            // score having the nine of trump
            static double score_have_nine_trump(const score_context& ctx)
            {
                const double s = ctx.m_file_data->get_float_by_path("trump_call/have_nine_trump");
                if (s != 0.0f)
                    if (ctx.m_hand.contains(card(ctx.m_suit, e_rank::NINE)))
                        return s;
                return 0.0f;
            }


            static double score(const e_suit s,
                                const hand &h,
                                const card &up_card,
                                e_seat_position dealer_position,
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

                return total;
            }

        } // namespace score_trump_call
    }     // namespace euchre
} // namespace rda
