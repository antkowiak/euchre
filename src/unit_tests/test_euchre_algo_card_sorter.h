#pragma once

//
// test_euchre_algo_card_sorter.h - Unit tests for euchre_algo_card_sorter.h.
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "unit_test_utils.h"

#include "../platform_defs.h"
#include "../euchre_algo_card_sorter.h"
#include "../euchre_card.h"
#include "../euchre_card_suit.h"
#include "../euchre_card_rank.h"

PUSH_WARN_DISABLE
WARN_DISABLE(4100, "-Wunused-parameter")

namespace rda
{
    namespace test_euchre_algo_card_sorter
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
            std::cout << "Running euchre_algo_card_sorter test: " << testNum << std::endl;
        }

        static void teardown(const size_t testNum, TestInput &input)
        {
        }

        //////////////////////////////////////////////////////////////////////////////////

        static void test_000(const size_t testNum, TestInput &input)
        {
            using namespace rda::euchre;
            using namespace rda::euchre::euchre_algo;

            ASSERT_TRUE(get_hoyle_suit(e_suit::INVALID) == e_suit::INVALID, "get_hoyle_suit(INVALID)");
            ASSERT_TRUE(get_hoyle_suit(e_suit::CLUBS) == e_suit::SPADES, "get_hoyle_suit(CLUBS)");
            ASSERT_TRUE(get_hoyle_suit(e_suit::DIAMONDS) == e_suit::HEARTS, "get_hoyle_suit(DIAMONDS)");
            ASSERT_TRUE(get_hoyle_suit(e_suit::HEARTS) == e_suit::DIAMONDS, "get_hoyle_suit(HEARTS)");
            ASSERT_TRUE(get_hoyle_suit(e_suit::SPADES) == e_suit::CLUBS, "get_hoyle_suit(SPADES)");
        }

        static void test_001(const size_t testNum, TestInput &input)
        {
            using namespace rda::euchre;
            using namespace rda::euchre::euchre_algo;

            auto deck = get_full_deck(e_suit::CLUBS);
            ASSERT_TRUE(deck.size() == 24);
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
    } // namespace test_euchre_algo_card_sorter
} // namespace rda

POP_WARN_DISABLE
