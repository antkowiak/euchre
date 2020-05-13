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
#include "euchre_utils.h"

namespace rda
{
    namespace euchre
    {
        // player in a euchre game
        class euchre_player
        {
        protected:
            const uint8_t m_seat_index;
            const euchre_seat_position m_seat_position = euchre_seat_position::SELF;

            uint8_t m_dealer_index = 4;
            euchre_seat_position m_dealer_position = euchre_seat_position::INVALID;

            euchre_card m_up_card;
            euchre_hand m_hand;

            euchre_perception m_left_perception;
            euchre_perception m_partner_perception;
            euchre_perception m_right_perception;

        public:
            euchre_player(const uint8_t index)
                : m_seat_index(index)
            {
                m_left_perception.seat_position = euchre_seat_position::LEFT;
                m_partner_perception.seat_position = euchre_seat_position::ACROSS;
                m_right_perception.seat_position = euchre_seat_position::RIGHT;
            }

            virtual ~euchre_player() = default;

            virtual void reset()
            {
                m_dealer_index = 4;
                m_dealer_position = euchre_seat_position::INVALID;

                m_up_card = euchre_card();
                m_hand.clear();

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

            euchre_hand &get_hand()
            {
                return m_hand;
            }

            void update_perceptions_after_deal(const uint8_t dealer_index, const euchre_card &up_card)
            {
                // save the up card
                m_up_card = up_card;

                // set the dealer's position in relation to ourself
                m_dealer_position = euchre_utils::relative_seat_position(m_seat_index, dealer_index);

                m_left_perception.update_after_deal(dealer_index, up_card);

                //m_left_perception.up_card = up_card;
                //m_partner_perception.up_card = up_card;
                //m_right_perception.up_card = up_card;

                //////

                // for players who aren't the dealer, make sure we remember that they do not have the up-card in their hand
                if (m_dealer_position != euchre_seat_position::LEFT)
                    m_left_perception.cards_not_in_hand.push_back(up_card);
                if (m_dealer_position != euchre_seat_position::ACROSS)
                    m_partner_perception.cards_not_in_hand.push_back(up_card);
                if (m_dealer_position != euchre_seat_position::RIGHT)
                    m_right_perception.cards_not_in_hand.push_back(up_card);

                // update each perception of where the dealer is relatively
                switch (m_dealer_position)
                {
                    case euchre_seat_position::SELF:
                        m_left_perception.dealer_position = euchre_seat_position::RIGHT;
                        m_partner_perception.dealer_position = euchre_seat_position::ACROSS;
                        m_right_perception.dealer_position = euchre_seat_position::LEFT;
                        break;
                    case euchre_seat_position::LEFT:
                        m_left_perception.dealer_position = euchre_seat_position::SELF;
                        m_partner_perception.dealer_position = euchre_seat_position::RIGHT;
                        m_right_perception.dealer_position = euchre_seat_position::ACROSS;
                        break;
                    case euchre_seat_position::ACROSS:
                        m_left_perception.dealer_position = euchre_seat_position::LEFT;
                        m_partner_perception.dealer_position = euchre_seat_position::SELF;
                        m_right_perception.dealer_position = euchre_seat_position::RIGHT;
                        break;
                    case euchre_seat_position::RIGHT:
                        m_left_perception.dealer_position = euchre_seat_position::ACROSS;
                        m_partner_perception.dealer_position = euchre_seat_position::LEFT;
                        m_right_perception.dealer_position = euchre_seat_position::SELF;
                        break;
                    default:
                        break;
                }
            }

        }; // class player

    } // namespace euchre
} // namespace rda
