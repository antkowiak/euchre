#pragma once

//
// euchre_player.h - Player in a euchre game
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <algorithm>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "euchre_algo_discarder.h"
#include "euchre_card.h"
#include "euchre_card_rank.h"
#include "euchre_card_suit.h"
#include "euchre_constants.h"
#include "euchre_hand.h"
#include "euchre_perception.h"
#include "euchre_seat_position.h"
#include "euchre_trump_decision.h"
#include "euchre_utils.h"
#include "random_seeder.h"
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
            uint8_t m_dealer_index = euchre_constants::INVALID_INDEX;

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
                  m_left_perception((seat_index + 1) % euchre_constants::NUM_PLAYERS),
                  m_partner_perception((seat_index + 2) % euchre_constants::NUM_PLAYERS),
                  m_right_perception((seat_index + 3) % euchre_constants::NUM_PLAYERS)
            {
            }

            // virtual destructor
            virtual ~euchre_player() = default;

            // reset the player
            virtual void reset()
            {
                m_dealer_index = euchre_constants::INVALID_INDEX;
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
                // score the situation
                const score_trump_call_context ctx = score_trump_call::score(up_card.suit(),
                                                                             m_hand,
                                                                             up_card,
                                                                             false,
                                                                             m_dealer_position,
                                                                             m_left_perception,
                                                                             m_partner_perception,
                                                                             m_right_perception);

                // check if should order up for a loner
                if (ctx.get_total_score() >= ctx.get_loner_call_threshold())
                    return e_trump_decision::ORDER_UP_LONER;

                // check if should order up
                if (ctx.get_total_score() >= ctx.get_trump_call_threshold())
                    return e_trump_decision::ORDER_UP;

                // not a good hand, pass
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

            // pick up the up-card into the player's hand
            void pick_up_card(const euchre_card &card)
            {
                m_hand.add_card(card);
                euchre_algo::discarder(m_hand, card, card.suit());
            }

            // handle an offer of calling any trump suit
            e_trump_decision offer_trump()
            {
                // start with all suits
                std::vector<e_suit> suits = {e_suit::CLUBS, e_suit::DIAMONDS, e_suit::HEARTS, e_suit::SPADES};

                // remove the "up card" suit from consideration
                auto unused = std::remove(suits.begin(), suits.end(), m_up_card.suit());
                static_cast<void>(unused);

                // randomize the order of the suits
                rda::euchre::seed_randomizer();
                std::random_shuffle(suits.begin(), suits.end());

                // create a vector for all of the suit scoring contexts
                std::vector<score_trump_call_context> contexts;

                // initialize max_score and best index
                double max_score = std::numeric_limits<double>::lowest();
                size_t best_score_index = 0;

                // iterate over the suits
                for (size_t i = 0; i < suits.size(); ++i)
                {
                    // create the score context for this suit
                    contexts.push_back(score_trump_call::score(suits[i],
                                                               m_hand,
                                                               m_up_card,
                                                               false,
                                                               m_dealer_position,
                                                               m_left_perception,
                                                               m_partner_perception,
                                                               m_right_perception));

                    // extract the score
                    const double suit_score = contexts[i].get_total_score();

                    // check if the score is the best
                    if (suit_score > max_score)
                    {
                        max_score = suit_score;
                        best_score_index = i;
                    }
                }

                // if a best score was found
                if (best_score_index < contexts.size())
                {
                    // check if the score meets or exceeds the loner-call threshold
                    if (contexts[best_score_index].get_total_score() >= contexts[best_score_index].get_loner_call_threshold())
                        return suit_to_loner_call(contexts[best_score_index].m_suit);

                    // check if the score meets or exceeds the trump-call threshold
                    if (contexts[best_score_index].get_total_score() >= contexts[best_score_index].get_trump_call_threshold())
                        return suit_to_call(contexts[best_score_index].m_suit);
                }

                // not a good enough hand, so pass
                return e_trump_decision::PASS;
            }

            // update perceptino of other players, after getting results of an offer for someone to call trump
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

        }; // class euchre_player

    } // namespace euchre

} // namespace rda
