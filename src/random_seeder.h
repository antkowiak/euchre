#pragma once

//
// random_seeder.h - Seed a random engine with the time
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdlib>
#include <ctime>
#include <random>

namespace rda
{
    namespace euchre
    {
        // returns static (singleton) instance of a random generator
        static std::default_random_engine random_engine()
        {
            static std::default_random_engine engine{};
            static bool seeded = false;

            // seed the random engine once
            if (!seeded)
            {
                engine.seed(static_cast<unsigned int>(std::time(nullptr)));
                seeded = true;
            }

            return engine;
        }

    } // namespace euchre
} // namespace rda
