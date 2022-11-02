#pragma once

//
// euchre_seat_position.h - The relative seat position
//
// Written by Ryan Antkowiak 
//

#include <stdint.h>

namespace rda
{
    namespace euchre
    {
        // seat position in relation to the player
        enum class euchre_seat_position : uint8_t
        {
            SELF = 0,
            LEFT = 1,
            ACROSS = 2,
            RIGHT = 3,
            INVALID = 4

        }; // enum e_seat_position

    } // namespace euchre

} // namespace rda
