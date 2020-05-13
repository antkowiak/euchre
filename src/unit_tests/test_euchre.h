#pragma once

//
// test_euchre.h - Unit tests for euchre
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
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
            auto j = rda::json::node_object{"", std::vector<std::shared_ptr<rda::json::node>>()};

            auto trump_call = std::make_shared<rda::json::node_object>(rda::json::node_object("trump_call", std::vector<std::shared_ptr<rda::json::node>>()));
            trump_call->add_child(std::make_shared<rda::json::node_float>("trump_call_threshold", 14.0));

            trump_call->add_child(std::make_shared<rda::json::node_float>("have_right_bower_trump", 8.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_left_bower_trump", 6.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_ace_trump", 5.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_king_trump", 4.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_queen_trump", 3.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_ten_trump", 2.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_nine_trump", 1.0));

            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_right_bower_trump", 8.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_ace_trump", 5.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_king_trump", 4.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_queen_trump", 3.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_ten_trump", 2.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_nine_trump", 1.0));

            trump_call->add_child(std::make_shared<rda::json::node_float>("partner_would_pick_up_right_bower_trump", 6.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("partner_would_pick_up_ace_trump", 4.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("partner_would_pick_up_king_trump", 3.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("partner_would_pick_up_queen_trump", 2.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("partner_would_pick_up_ten_trump", 1.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("partner_would_pick_up_nine_trump", 0.5));

            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_right_bower_trump", -8.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_ace_trump", -6.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_king_trump", -5.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_queen_trump", -4.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_ten_trump", -3.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("would_pick_up_nine_trump", -2.0));

            trump_call->add_child(std::make_shared<rda::json::node_float>("have_one_suited", 20.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_two_suited", 5.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_three_suited", 1.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_four_suited", -2.0));

            trump_call->add_child(std::make_shared<rda::json::node_float>("have_four_non_trump_winners", 5.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_three_non_trump_winners", 5.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_two_non_trump_winners", 4.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("have_one_non_trump_winners", 2.0));

            trump_call->add_child(std::make_shared<rda::json::node_float>("partner_passed_on_up_card", -2.0));

            trump_call->add_child(std::make_shared<rda::json::node_float>("one_opponent_passed_on_up_card", 1.0));
            trump_call->add_child(std::make_shared<rda::json::node_float>("two_opponents_passed_on_up_card", 2.0));

            j.add_child(trump_call);

            std::cout << j.to_pretty_string() << std::endl;

            rda::fileio f("euchre.json");
            f.set(j.to_pretty_string());
            f.append("\n\n");
            //f.write();
        }

        static void test_002(const size_t testNum, TestInput &input)
        {
            /*
            using namespace rda::euchre;

            euchre_hand h;
            euchre_card up_card;
            euchre_seat_position dealer_pos = euchre_seat_position::LEFT;
            euchre_perception left_per(1);
            euchre_perception partner_per(2);
            euchre_perception right_per(3);

            //double score = score_trump_call::score(e_suit::SPADES, h, up_card, false, dealer_pos, left_per, partner_per, right_per);
            //static_cast<void>(score); // unused
            */
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
