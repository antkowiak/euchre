#pragma once

//
// euchre_player_human.h - Human player in a euchre game
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>

#include "euchre_player.h"

namespace rda
{
    namespace euchre
    {
        // human player in a euchre game
        class euchre_player_human : public euchre_player
        {
        public:
            euchre_player_human(const uint8_t pos)
                : euchre_player(pos)
            {
            }

        }; // class euchre_player_human

    } // namespace euchre

} // namespace rda
