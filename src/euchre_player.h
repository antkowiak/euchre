#pragma once

//
// euchre_player.h - Player in a euchre game
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <sstream>
#include <string>

#include "euchre_card.h"
#include "euchre_hand.h"
#include "euchre_perception.h"
#include "euchre_trump_decision.h"
#include "euchre_utils.h"
#include "score_trump_call.h"
#include "score_trump_call_context.h"

namespace rda
{
    namespace euchre
    {
        // player in a euchre game
        class euchre_player
        {
        protected:
            // index 0-3 where this player is sitting
            const uint8_t m_seat_index;

            // index 0-3 where the dealer is sitting
            uint8_t m_dealer_index = 4;

            // where the dealer sits, relative to this player
            euchre_seat_position m_dealer_position = euchre_seat_position::INVALID;

            // the card that is currently observed to be turned up
            euchre_card m_up_card;

            // the current called suit
            e_suit m_suit_called_trump = e_suit::INVALID;

            // the player's hand of cards remaining
            euchre_hand m_hand;

            // all the info that this player knows about the opponent to the left
            euchre_perception m_left_perception;

            // all the info that this player knows about the partner across
            euchre_perception m_partner_perception;

            // all the info that this player knows about the opponent to the right
            euchre_perception m_right_perception;

        public:
            // constructor
            euchre_player(const uint8_t seat_index)
                : m_seat_index(seat_index),
                  m_left_perception((seat_index + 1) % 4),
                  m_partner_perception((seat_index + 2) % 4),
                  m_right_perception((seat_index + 3) % 4)
            {
            }

            // virtual destructor
            virtual ~euchre_player() = default;

            // reset the player
            virtual void reset()
            {
                m_dealer_index = 4;
                m_dealer_position = euchre_seat_position::INVALID;

                m_up_card = euchre_card();
                m_suit_called_trump = e_suit::INVALID;
                m_hand.clear();

                m_left_perception.reset();
                m_partner_perception.reset();
                m_right_perception.reset();
            }

            // return string representation of this player
            std::string to_string() const
            {
                std::stringstream ss;
                ss << m_hand.to_string();
                return ss.str();
            }

            // return a reference to this player's hand
            euchre_hand &get_hand()
            {
                return m_hand;
            }

            // update perceptions of over players, after the initial cards have been dealt
            void update_perceptions_after_deal(const uint8_t dealer_index, const euchre_card &up_card)
            {
                // save the up card
                m_up_card = up_card;

                // set the dealer's position in relation to ourself
                m_dealer_index = dealer_index;
                m_dealer_position = euchre_utils::relative_seat_position(m_seat_index, dealer_index);

                m_left_perception.update_after_deal(dealer_index, up_card);
                m_partner_perception.update_after_deal(dealer_index, up_card);
                m_right_perception.update_after_deal(dealer_index, up_card);
            }

            // handle an offer of making the up_card trump
            e_trump_decision offer_up_card_trump(const euchre_card &up_card)
            {
                const score_trump_call_context ctx = score_trump_call::score(up_card.suit(),
                                                                             m_hand,
                                                                             up_card,
                                                                             false,
                                                                             m_dealer_position,
                                                                             m_left_perception,
                                                                             m_partner_perception,
                                                                             m_right_perception);

                if (ctx.get_total_score() >= ctx.get_loner_call_threshold())
                    return e_trump_decision::ORDER_UP_LONER;

                if (ctx.get_total_score() >= ctx.get_trump_call_threshold())
                    return e_trump_decision::ORDER_UP;

                return e_trump_decision::PASS;
            }

            // update perceptions of other players, after getting the result of an offer of trump from an up-card
            void update_perceptions_after_up_card_offer(const uint8_t seat_index, const e_trump_decision decision)
            {
                if (decision == e_trump_decision::ORDER_UP || decision == e_trump_decision::ORDER_UP_LONER)
                    m_suit_called_trump = m_up_card.suit();

                m_left_perception.update_after_up_card_offer(seat_index, decision);
                m_partner_perception.update_after_up_card_offer(seat_index, decision);
                m_right_perception.update_after_up_card_offer(seat_index, decision);
            }

            // handle an offer of calling any trump suit
            e_trump_decision offer_trump()
            {
                // TODO
                return e_trump_decision::INVALID;
            }

            void update_perceptions_after_trump_offer(const uint8_t seat_index, const e_trump_decision decision)
            {
                if (is_calling_suit(decision))
                    m_suit_called_trump = decision_to_suit(decision);

                const e_suit suit = decision_to_suit(decision);

                if (suit != e_suit::INVALID)
                    m_suit_called_trump = suit;

                m_left_perception.update_after_trump_offer(seat_index, decision);
                m_partner_perception.update_after_trump_offer(seat_index, decision);
                m_right_perception.update_after_trump_offer(seat_index, decision);
            }

        }; // class player

    } // namespace euchre
} // namespace rda
