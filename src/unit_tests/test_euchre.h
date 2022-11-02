#pragma once

//
// test_euchre.h - Unit tests for euchre
//
// Written by Ryan Antkowiak 
//

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "unit_test_utils.h"

#include "../platform_defs.h"

#include "../fileio.h"
#include "../json.h"

#include "../euchre_card.h"
#include "../euchre_deck.h"
#include "../euchre_hand.h"
#include "../euchre_perception.h"
#include "../euchre_player.h"
#include "../euchre_player_computer.h"
#include "../euchre_player_human.h"
#include "../random_seeder.h"
#include "../score_trump_call.h"

PUSH_WARN_DISABLE
WARN_DISABLE(4100, "-Wunused-parameter")

namespace rda
{
    namespace test_euchre
    {
        using unit_test_utils::ASSERT_FALSE;
        using unit_test_utils::ASSERT_NO_THROW;
        using unit_test_utils::ASSERT_THROWS;
        using unit_test_utils::ASSERT_THROWS_OUT_OF_RANGE;
        using unit_test_utils::ASSERT_TRUE;

        struct TestInput
        {
        };

        static void setup(const size_t testNum, TestInput &input)
        {
            std::cout << "Running euchre test: " << testNum
                      << std::endl;
        }

        static void teardown(const size_t testNum, TestInput &input)
        {
        }

        //////////////////////////////////////////////////////////////////////////////////

        static void test_000(const size_t testNum, TestInput &input)
        {
            rda::euchre::euchre_deck d;
            std::cout << d.to_string();
        }

        static void test_001(const size_t testNum, TestInput &input)
        {
        }

        static void test_002(const size_t testNum, TestInput &input)
        {
        }

        static void test_003(const size_t testNum, TestInput &input)
        {
        }

        static void test_004(const size_t testNum, TestInput &input)
        {
        }

        static void test_005(const size_t testNum, TestInput &input)
        {
        }

        static void test_006(const size_t testNum, TestInput &input)
        {
        }

        static void test_007(const size_t testNum, TestInput &input)
        {
        }

        static void test_008(const size_t testNum, TestInput &input)
        {
        }

        static void test_009(const size_t testNum, TestInput &input)
        {
        }

        static void run_tests()
        {
            // vector to hold functions to unit tests
            std::vector<std::function<void(const size_t, TestInput &)>> test_vec;

            // add all unit tests to the vector
            test_vec.push_back(test_000);
            test_vec.push_back(test_001);
            test_vec.push_back(test_002);
            test_vec.push_back(test_003);
            test_vec.push_back(test_004);
            test_vec.push_back(test_005);
            test_vec.push_back(test_006);
            test_vec.push_back(test_007);
            test_vec.push_back(test_008);
            test_vec.push_back(test_009);

            // run each unit test
            for (size_t i = 0; i < test_vec.size(); ++i)
            {
                TestInput input;
                setup(i, input);
                test_vec[i](i, input);
                teardown(i, input);
            }
        }
    } // namespace test_euchre
} // namespace rda

POP_WARN_DISABLE
