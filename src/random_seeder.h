#pragma once

//
// random_seeder.h - Seed a random engine with the time
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>

namespace rda
{
    namespace euchre
    {
        // returns static (singleton) instance of a random generator
        static void seed_randomizer()
        {
            static bool seeded = false;

            // seed the random engine once
            if (!seeded)
            {
                std::srand(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
                seeded = true;
            }
        }

    } // namespace euchre
} // namespace rda
