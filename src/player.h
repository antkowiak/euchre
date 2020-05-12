#pragma once

//
// player.h - Player in a euchre game
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <sstream>
#include <string>

#include "hand.h"
#include "perception.h"

namespace rda
{
    namespace euchre
    {
        // player in a euchre game
        class player
        {
        protected:
            const uint8_t m_position;
            hand m_hand;
            e_seat_position m_dealer_position = e_seat_position::INVALID;
            card m_up_card;

            perception m_left_perception;
            perception m_partner_perception;
            perception m_right_perception;

        public:

            player(const uint8_t pos)
                : m_position(pos)
            {
                m_left_perception.seat_position = e_seat_position::LEFT;
                m_partner_perception.seat_position = e_seat_position::ACROSS;
                m_right_perception.seat_position = e_seat_position::RIGHT;
            }

            virtual ~player() = default;

            virtual void reset()
            {
                m_hand.clear();
                m_dealer_position = e_seat_position::INVALID;
                m_up_card = card();

                m_left_perception.reset();
                m_partner_perception.reset();
                m_right_perception.reset();
            }

            std::string to_string() const
            {
                std::stringstream ss;
                ss << m_hand.to_string();
                return ss.str();
            }

            hand& get_hand()
            {
                return m_hand;
            }

            void update_perceptions_after_deal(const uint8_t dealer, const card & up_card)
            {
                // save the up card
                m_up_card = up_card;
                m_left_perception.up_card = up_card;
                m_partner_perception.up_card = up_card;
                m_right_perception.up_card = up_card;

                // set the dealer's position in relation to ourself
                if (dealer == m_position)
                    m_dealer_position = e_seat_position::SELF;
                else if ((m_position + 1) % 4 == dealer)
                    m_dealer_position = e_seat_position::LEFT;
                else if ((m_position + 2) % 4 == dealer)
                    m_dealer_position = e_seat_position::ACROSS;
                else if ((m_position + 3) % 4 == dealer)
                    m_dealer_position = e_seat_position::RIGHT;

                // for players who aren't the dealer, make sure we remember that they do not have the up-card in their hand
                if (m_dealer_position != e_seat_position::LEFT)
                    m_left_perception.cards_not_in_hand.push_back(up_card);
                if (m_dealer_position != e_seat_position::ACROSS)
                    m_partner_perception.cards_not_in_hand.push_back(up_card);
                if (m_dealer_position != e_seat_position::RIGHT)
                    m_right_perception.cards_not_in_hand.push_back(up_card);

                // update each perception of where the dealer is relatively
                switch (m_dealer_position)
                {
                case e_seat_position::SELF:
                    m_left_perception.dealer_position = e_seat_position::RIGHT;
                    m_partner_perception.dealer_position = e_seat_position::ACROSS;
                    m_right_perception.dealer_position = e_seat_position::LEFT;
                    break;
                case e_seat_position::LEFT:
                    m_left_perception.dealer_position = e_seat_position::SELF;
                    m_partner_perception.dealer_position = e_seat_position::RIGHT;
                    m_right_perception.dealer_position = e_seat_position::ACROSS;
                    break;
                case e_seat_position::ACROSS:
                    m_left_perception.dealer_position = e_seat_position::LEFT;
                    m_partner_perception.dealer_position = e_seat_position::SELF;
                    m_right_perception.dealer_position = e_seat_position::RIGHT;
                    break;
                case e_seat_position::RIGHT:
                    m_left_perception.dealer_position = e_seat_position::ACROSS;
                    m_partner_perception.dealer_position = e_seat_position::LEFT;
                    m_right_perception.dealer_position = e_seat_position::SELF;
                    break;
                }
            }

        }; // class player

    } // namespace euchre
} // namespace rda
