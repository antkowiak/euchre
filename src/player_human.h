#pragma once

//
// player_human.h - Human player in a euchre game
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include "player.h"

namespace rda
{
    namespace euchre
    {
        // human player in a euchre game
        class player_human : public player
        {
        public:
            player_human(const uint8_t pos)
                : player(pos)
            {
            }

        }; // class player_human

    } // namespace euchre
} // namespace rda
