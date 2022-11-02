#pragma once

//
// euchre_player_computer.h - Computer player in a euchre game
//
// Written by Ryan Antkowiak 
//

#include <cstdint>

#include "euchre_player.h"

namespace rda
{
    namespace euchre
    {
        // computer player in a euchre game
        class euchre_player_computer : public euchre_player
        {
        public:
            euchre_player_computer(const uint8_t pos)
                : euchre_player(pos)
            {
            }

        }; // class euchre_player_computer

    } // namespace euchre

} // namespace rda
