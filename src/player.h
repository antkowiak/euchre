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
            hand m_hand;

            perception left_perception;
            perception partner_perception;
            perception right_perception;

        public:

            virtual ~player() = default;

            virtual void reset()
            {
                m_hand.clear();

                left_perception.reset();
                partner_perception.reset();
                right_perception.reset();
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

        }; // class player

    } // namespace euchre
} // namespace rda
