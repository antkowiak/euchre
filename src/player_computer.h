#pragma once

#include "perception.h"
#include "player.h"

namespace rda
{
    namespace euchre
    {
        class player_computer : public player
        {
        private:
            perception left_perception;
            perception partner_perception;
            perception right_perception;

        }; // class player_computer

    } // namespace euchre
} // namespace rda
