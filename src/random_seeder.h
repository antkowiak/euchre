#pragma once

#include <cstdlib>
#include <ctime>

namespace rda
{
    namespace euchre
    {
        static void seed_randomizer()
        {
            static bool seeded = false;

            if (!seeded)
            {
                std::srand(std::time(nullptr));
                seeded = true;
            }
        }

    } // namespace euchre
} // namespace rda
