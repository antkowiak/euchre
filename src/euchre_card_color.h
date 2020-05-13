#pragma once

//
// euchre_card_color.h - Color of a euchre card
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>

namespace rda
{
    namespace euchre
    {
        // card color
        enum class e_color : uint8_t
        {
            BLACK = 0,
            BEGIN = 0,
            RED = 1,
            INVALID = 2,
            END = 2
        }; // enum color

    } // namespace euchre

} // namespace rda
