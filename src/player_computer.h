#pragma once

//
// player_computer.h - Computer player in a euchre game
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include "player.h"

namespace rda
{
    namespace euchre
    {
        // computer player in a euchre game
        class player_computer : public player
        {
        public:
            player_computer(const uint8_t pos)
                : player(pos)
            {
            }

        }; // class player_computer

    } // namespace euchre
} // namespace rda
