#pragma once

//
// test_euchre_algo_card_sorter.h - Unit tests for euchre_algo_card_sorter.h.
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "unit_test_utils.h"

#include "../platform_defs.h"
#include "../euchre_algo_card_sorter.h"
#include "../euchre_card.h"
#include "../euchre_card_suit.h"
#include "../euchre_card_rank.h"
#include "../random_seeder.h"

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

            auto deck = get_trump_deck(e_suit::CLUBS);
            ASSERT_TRUE(deck.size() == 7);
            ASSERT_TRUE(deck[0] == euchre_card{e_suit::CLUBS, e_rank::JACK});
            ASSERT_TRUE(deck[1] == euchre_card{e_suit::SPADES, e_rank::JACK});
            ASSERT_TRUE(deck[2] == euchre_card{e_suit::CLUBS, e_rank::ACE});
            ASSERT_TRUE(deck[3] == euchre_card{e_suit::CLUBS, e_rank::KING});
            ASSERT_TRUE(deck[4] == euchre_card{e_suit::CLUBS, e_rank::QUEEN});
            ASSERT_TRUE(deck[5] == euchre_card{e_suit::CLUBS, e_rank::TEN});
            ASSERT_TRUE(deck[6] == euchre_card{e_suit::CLUBS, e_rank::NINE});
        }

        static void test_002(const size_t testNum, TestInput &input)
        {
            using namespace rda::euchre;
            using namespace rda::euchre::euchre_algo;

            auto deck = get_hoyle_deck(e_suit::DIAMONDS);
            ASSERT_TRUE(deck.size() == 5);
            ASSERT_TRUE(deck[0] == euchre_card{e_suit::DIAMONDS, e_rank::ACE});
            ASSERT_TRUE(deck[1] == euchre_card{e_suit::DIAMONDS, e_rank::KING});
            ASSERT_TRUE(deck[2] == euchre_card{e_suit::DIAMONDS, e_rank::QUEEN});
            ASSERT_TRUE(deck[3] == euchre_card{e_suit::DIAMONDS, e_rank::TEN});
            ASSERT_TRUE(deck[4] == euchre_card{e_suit::DIAMONDS, e_rank::NINE});
        }

        static void test_003(const size_t testNum, TestInput &input)
        {
            using namespace rda::euchre;
            using namespace rda::euchre::euchre_algo;

            auto deck = get_suit_deck(e_suit::SPADES, e_suit::HEARTS);
            ASSERT_TRUE(deck.size() == 6);
            ASSERT_TRUE(deck[0] == euchre_card{e_suit::SPADES, e_rank::ACE});
            ASSERT_TRUE(deck[1] == euchre_card{e_suit::SPADES, e_rank::KING});
            ASSERT_TRUE(deck[2] == euchre_card{e_suit::SPADES, e_rank::QUEEN});
            ASSERT_TRUE(deck[3] == euchre_card{e_suit::SPADES, e_rank::JACK});
            ASSERT_TRUE(deck[4] == euchre_card{e_suit::SPADES, e_rank::TEN});
            ASSERT_TRUE(deck[5] == euchre_card{e_suit::SPADES, e_rank::NINE});
        }

        static void test_004(const size_t testNum, TestInput &input)
        {
            using namespace rda::euchre;
            using namespace rda::euchre::euchre_algo;

            ASSERT_TRUE(get_suit_deck(e_suit::DIAMONDS, e_suit::DIAMONDS).size() == 7);
            ASSERT_TRUE(get_suit_deck(e_suit::HEARTS, e_suit::DIAMONDS).size() == 5);
            ASSERT_TRUE(get_suit_deck(e_suit::CLUBS, e_suit::DIAMONDS).size() == 6);
            ASSERT_TRUE(get_suit_deck(e_suit::SPADES, e_suit::DIAMONDS).size() == 6);
        }

        static void test_005(const size_t testNum, TestInput &input)
        {
            using namespace rda::euchre;
            using namespace rda::euchre::euchre_algo;

            auto deck = get_full_deck(e_suit::CLUBS);
            ASSERT_TRUE(deck.size() == 24);
        }

        static void test_006(const size_t testNum, TestInput &input)
        {
            using namespace rda::euchre;
            using namespace rda::euchre::euchre_algo;

            auto deck = get_full_deck(e_suit::HEARTS);
            ASSERT_TRUE(deck.size() == 24);
            ASSERT_TRUE(deck[0] == euchre_card{e_suit::HEARTS, e_rank::JACK});
            ASSERT_TRUE(deck[1] == euchre_card{e_suit::DIAMONDS, e_rank::JACK});
            ASSERT_TRUE(deck[2] == euchre_card{e_suit::HEARTS, e_rank::ACE});

            const size_t heart_count = std::count_if(deck.cbegin(), deck.cend(), [](auto a) { return a.suit() == e_suit::HEARTS; });
            ASSERT_TRUE(heart_count == 6);

            const size_t diamond_count = std::count_if(deck.cbegin(), deck.cend(), [](auto a) { return a.suit() == e_suit::DIAMONDS; });
            ASSERT_TRUE(diamond_count == 6);

            const size_t club_count = std::count_if(deck.cbegin(), deck.cend(), [](auto a) { return a.suit() == e_suit::CLUBS; });
            ASSERT_TRUE(club_count == 6);

            const size_t spade_count = std::count_if(deck.cbegin(), deck.cend(), [](auto a) { return a.suit() == e_suit::SPADES; });
            ASSERT_TRUE(spade_count == 6);
        }

        static void test_007(const size_t testNum, TestInput &input)
        {
            using namespace rda::euchre;
            using namespace rda::euchre::euchre_algo;

            ASSERT_TRUE(get_effective_suit(euchre_card{e_suit::HEARTS, e_rank::ACE}, e_suit::CLUBS) == e_suit::HEARTS);
            ASSERT_TRUE(get_effective_suit(euchre_card{e_suit::HEARTS, e_rank::JACK}, e_suit::CLUBS) == e_suit::HEARTS);

            ASSERT_TRUE(get_effective_suit(euchre_card{e_suit::CLUBS, e_rank::ACE}, e_suit::CLUBS) == e_suit::CLUBS);
            ASSERT_TRUE(get_effective_suit(euchre_card{e_suit::CLUBS, e_rank::JACK}, e_suit::CLUBS) == e_suit::CLUBS);

            ASSERT_TRUE(get_effective_suit(euchre_card{e_suit::SPADES, e_rank::JACK}, e_suit::CLUBS) == e_suit::CLUBS);
            ASSERT_TRUE(get_effective_suit(euchre_card{e_suit::SPADES, e_rank::ACE}, e_suit::CLUBS) == e_suit::SPADES);
        }

        static void test_008(const size_t testNum, TestInput &input)
        {
            using namespace rda::euchre;
            using namespace rda::euchre::euchre_algo;

            ASSERT_TRUE(is_right_bower(euchre_card{e_suit::DIAMONDS, e_rank::JACK}, e_suit::DIAMONDS));
            ASSERT_TRUE(is_right_bower(euchre_card{e_suit::HEARTS, e_rank::JACK}, e_suit::HEARTS));
            ASSERT_TRUE(is_right_bower(euchre_card{e_suit::CLUBS, e_rank::JACK}, e_suit::CLUBS));
            ASSERT_TRUE(is_right_bower(euchre_card{e_suit::SPADES, e_rank::JACK}, e_suit::SPADES));

            ASSERT_FALSE(is_right_bower(euchre_card{e_suit::SPADES, e_rank::JACK}, e_suit::CLUBS));
            ASSERT_FALSE(is_right_bower(euchre_card{e_suit::SPADES, e_rank::JACK}, e_suit::DIAMONDS));
            ASSERT_FALSE(is_right_bower(euchre_card{e_suit::SPADES, e_rank::JACK}, e_suit::HEARTS));

            ASSERT_TRUE(is_left_bower(euchre_card{e_suit::DIAMONDS, e_rank::JACK}, e_suit::HEARTS));
            ASSERT_TRUE(is_left_bower(euchre_card{e_suit::HEARTS, e_rank::JACK}, e_suit::DIAMONDS));
            ASSERT_TRUE(is_left_bower(euchre_card{e_suit::CLUBS, e_rank::JACK}, e_suit::SPADES));
            ASSERT_TRUE(is_left_bower(euchre_card{e_suit::SPADES, e_rank::JACK}, e_suit::CLUBS));

            ASSERT_FALSE(is_left_bower(euchre_card{e_suit::SPADES, e_rank::JACK}, e_suit::SPADES));
            ASSERT_FALSE(is_left_bower(euchre_card{e_suit::SPADES, e_rank::JACK}, e_suit::DIAMONDS));
            ASSERT_FALSE(is_left_bower(euchre_card{e_suit::SPADES, e_rank::JACK}, e_suit::HEARTS));
        }

        static void test_009(const size_t testNum, TestInput &input)
        {
            using namespace rda::euchre::euchre_algo;
            using namespace rda::euchre;

            auto deck = get_full_deck(e_suit::HEARTS);
            seed_randomizer();
            std::random_shuffle(deck.begin(), deck.end());

            sort_deck_by_suit(deck, e_suit::HEARTS);

            ASSERT_TRUE(deck.size() == 24);

            ASSERT_TRUE(deck[0] == euchre_card{e_suit::HEARTS, e_rank::JACK});
            ASSERT_TRUE(deck[1] == euchre_card{e_suit::DIAMONDS, e_rank::JACK});
            ASSERT_TRUE(deck[2] == euchre_card{e_suit::HEARTS, e_rank::ACE});
            ASSERT_TRUE(deck[3] == euchre_card{e_suit::HEARTS, e_rank::KING});
            ASSERT_TRUE(deck[4] == euchre_card{e_suit::HEARTS, e_rank::QUEEN});
            ASSERT_TRUE(deck[5] == euchre_card{e_suit::HEARTS, e_rank::TEN});
            ASSERT_TRUE(deck[6] == euchre_card{e_suit::HEARTS, e_rank::NINE});

            ASSERT_TRUE(deck[7] == euchre_card{e_suit::CLUBS, e_rank::ACE});
            ASSERT_TRUE(deck[8] == euchre_card{e_suit::CLUBS, e_rank::KING});
            ASSERT_TRUE(deck[9] == euchre_card{e_suit::CLUBS, e_rank::QUEEN});
            ASSERT_TRUE(deck[10] == euchre_card{e_suit::CLUBS, e_rank::JACK});
            ASSERT_TRUE(deck[11] == euchre_card{e_suit::CLUBS, e_rank::TEN});
            ASSERT_TRUE(deck[12] == euchre_card{e_suit::CLUBS, e_rank::NINE});

            ASSERT_TRUE(deck[13] == euchre_card{e_suit::DIAMONDS, e_rank::ACE});
            ASSERT_TRUE(deck[14] == euchre_card{e_suit::DIAMONDS, e_rank::KING});
            ASSERT_TRUE(deck[15] == euchre_card{e_suit::DIAMONDS, e_rank::QUEEN});
            ASSERT_TRUE(deck[16] == euchre_card{e_suit::DIAMONDS, e_rank::TEN});
            ASSERT_TRUE(deck[17] == euchre_card{e_suit::DIAMONDS, e_rank::NINE});

            ASSERT_TRUE(deck[18] == euchre_card{e_suit::SPADES, e_rank::ACE});
            ASSERT_TRUE(deck[19] == euchre_card{e_suit::SPADES, e_rank::KING});
            ASSERT_TRUE(deck[20] == euchre_card{e_suit::SPADES, e_rank::QUEEN});
            ASSERT_TRUE(deck[21] == euchre_card{e_suit::SPADES, e_rank::JACK});
            ASSERT_TRUE(deck[22] == euchre_card{e_suit::SPADES, e_rank::TEN});
            ASSERT_TRUE(deck[23] == euchre_card{e_suit::SPADES, e_rank::NINE});
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
