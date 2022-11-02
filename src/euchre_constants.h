#pragma once

//
// euchre_constants.h - Constant values for euchre games
//
// Written by Ryan Antkowiak 
//

#include <cstdint>

namespace rda
{
    namespace euchre
    {
        class euchre_constants
        {
        public:
            const static uint8_t NUM_PLAYERS = 4;

            const static uint8_t INVALID_INDEX = 4;

            const static uint8_t EUCHRE_HAND_SIZE = 5;

        }; // class euchre_constants

    } // namespace euchre

} // namespace rda
