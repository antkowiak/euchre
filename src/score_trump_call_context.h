#pragma once

//
// score_trump_call_context.h - Data context used when scoring trump
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <array>
#include <memory>
#include <numeric>

#include "fileio.h"
#include "json.h"

#include "euchre_card.h"
#include "euchre_card_rank.h"
#include "euchre_card_suit.h"
#include "euchre_hand.h"
#include "euchre_perception.h"
#include "euchre_seat_position.h"

namespace rda
{
    namespace euchre
    {
        // the context of the game for scoring a particular trump suit
        class score_trump_call_context
        {
        public:
            const e_suit m_suit;
            const euchre_hand m_hand;
            const euchre_card m_up_card;
            const bool m_up_card_was_turned_down;
            const euchre_seat_position m_dealer_seat_position;
            const euchre_perception m_left_perception;
            const euchre_perception m_partner_perception;
            const euchre_perception m_right_perception;

            std::shared_ptr<rda::json::node_object> m_file_data;

            uint8_t m_num_suits = 0;
            uint8_t m_num_non_trump_winners = 0;
            uint8_t m_num_opponents_passed_on_up_card = 0;

        public:
            score_trump_call_context(const e_suit suit,
                                     const euchre_hand &hand,
                                     const euchre_card &up_card,
                                     const bool up_card_was_turned_down,
                                     const euchre_seat_position dealer_seat_position,
                                     const euchre_perception &left_perception,
                                     const euchre_perception &partner_perception,
                                     const euchre_perception &right_perception)
                : m_suit(suit),
                  m_hand(hand),
                  m_up_card(up_card),
                  m_up_card_was_turned_down(up_card_was_turned_down),
                  m_dealer_seat_position(dealer_seat_position),
                  m_left_perception(left_perception),
                  m_partner_perception(partner_perception),
                  m_right_perception(right_perception)
            {
                rda::fileio f("euchre.json");
                f.read();
                m_file_data = rda::json::parse(f.to_string());

                m_num_suits = count_num_suits();
                m_num_non_trump_winners = count_num_non_trump_winners();
                m_num_opponents_passed_on_up_card = count_num_opponents_passed_on_up_card();
            }

        private:
            // count the number of suits in a hand
            uint8_t count_num_suits() const
            {
                std::array<uint8_t, static_cast<size_t>(e_suit::END)> suits{};

                std::for_each(m_hand.cbegin(), m_hand.cend(),
                    [&] (const auto &card)
                    {
                        suits[static_cast<size_t>(card.suit())] = 1;
                    });

                return std::accumulate(suits.begin(), suits.end(), 0);
            }

            // count the number of non-trump "winning" cards in a hand
            uint8_t count_num_non_trump_winners() const
            {
                uint8_t winners = 0;

                // iterate through suits
                for (auto s = e_suit::BEGIN; s != e_suit::END; ++s)
                {
                    // for any suit that isn't being considered for trump
                    if (s != m_suit)
                    {
                        // check if contains ACE and KING suited, 2 winners
                        if (m_hand.contains({euchre_card(s, e_rank::ACE), euchre_card(s, e_rank::KING)}))
                        {
                            winners += 2;
                            continue;
                        }

                        // check if ace is turned down and contains KING and QUEEN suited, 2 winners
                        if (m_up_card_was_turned_down &&
                            m_up_card == euchre_card(s, e_rank::ACE) &&
                            m_hand.contains({euchre_card(s, e_rank::KING), euchre_card(s, e_rank::QUEEN)}))
                        {
                            winners += 2;
                            continue;
                        }

                        // check if king is turned down and contains ACE and QUEEN suited, 2 winners
                        if (m_up_card_was_turned_down &&
                            m_up_card == euchre_card(s, e_rank::KING) &&
                            m_hand.contains({euchre_card(s, e_rank::ACE), euchre_card(s, e_rank::QUEEN)}))
                        {
                            winners += 2;
                            continue;
                        }

                        // check if contains ACE
                        if (m_hand.contains(euchre_card(s, e_rank::ACE)))
                        {
                            winners += 1;
                            continue;
                        }

                        // check if ace is turned down and contains king
                        if (m_up_card_was_turned_down &&
                            m_up_card == euchre_card(s, e_rank::ACE) &&
                            m_hand.contains(euchre_card(s, e_rank::KING)))
                        {
                            winners += 1;
                            continue;
                        }
                    }
                }

                return winners;
            }

            // count the number of opponents who passed on the up-card
            uint8_t count_num_opponents_passed_on_up_card() const
            {
                uint8_t opponents = 0;

                if (m_left_perception.passed_on_ordering_up)
                    ++opponents;

                if (m_right_perception.passed_on_ordering_up)
                    ++opponents;

                return opponents;
            }

        }; // class score_trump_call_context

    } // namespace euchre

} // namespace rda