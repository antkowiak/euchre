#pragma once

//
// player_computer.h - Computer player in a euchre game
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include "perception.h"
#include "player.h"

namespace rda
{
    namespace euchre
    {
        // computer player in a euchre game
        class player_computer : public player
        {
        private:
            perception left_perception;
            perception partner_perception;
            perception right_perception;

        }; // class player_computer

    } // namespace euchre
} // namespace rda
