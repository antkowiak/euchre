
//
// main.cpp - Euchre program entry point
//
// Written by Ryan Antkowiak 
//

#include <iostream>
#include <string>

#include "euchre_game.h"

#include "unit_tests/test_euchre.h"
#include "unit_tests/test_euchre_algo_card_sorter.h"

// euchre program entry point
int main()
{
    // run unit tests
    rda::test_euchre::run_tests();
    rda::test_euchre_algo_card_sorter::run_tests();

    rda::euchre::euchre_game game;
    //game.play_game();

    return 0;
}
