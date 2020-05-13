#pragma once

//
// euchre_game.h - The euchre game
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "euchre_card.h"
#include "euchre_deck.h"
#include "euchre_hand.h"
#include "euchre_player_computer.h"
#include "euchre_player_human.h"
#include "euchre_scoreboard.h"

namespace rda
{
    namespace euchre
    {
        class euchre_game
        {
        public:
            // constructor
            euchre_game()
            {
                players.push_back(std::make_unique<euchre_player>(euchre_player_human(0)));
                players.push_back(std::make_unique<euchre_player>(euchre_player_computer(1)));
                players.push_back(std::make_unique<euchre_player>(euchre_player_computer(2)));
                players.push_back(std::make_unique<euchre_player>(euchre_player_computer(3)));

                init_game();
            }

            // initialize the euchre game
            void init_game()
            {
                up_card = euchre_card();
                trump_suit = e_suit::INVALID;
                scoreboard.reset_score();

                for (auto& player : players)
                    player->reset();
            }

            // initialize a euchre hand
            void init_hand()
            {
                up_card = euchre_card();
                trump_suit = e_suit::INVALID;
                scoreboard.reset_hand();

                for (auto &player : players)
                    player->reset();
            }

            // return string representation of this euchre game
            std::string to_string() const
            {
                std::stringstream ss;

                for (size_t i = 0; i < 4; ++i)
                    ss << "players[" << i << "]:" << std::endl
                       << players[i]->to_string();

                ss << "up card: " << up_card.to_string() << std::endl;

                return ss.str();
            }

            // play the euchre game
            void play()
            {
                dealer = determine_dealer();

                while (!scoreboard.is_over())
                {
                    play_hand();

                    ++dealer;
                    dealer = dealer % 4;
                }
            }

            void play_hand()
            {
                init_hand();
                shuffle_deck();
                deal_hand();
                update_perceptions_after_deal();

                // TODO - Offer trump to the players (for "ordering up")

                std::cout << to_string() << std::endl;
            }

            // shuffle the deck
            void shuffle_deck()
            {
                deck.init();
                deck.shuffle();
            }

            // deal a hand
            void deal_hand()
            {
                const static std::vector<uint8_t> DEAL_STRATEGY = {3, 2, 3, 2, 2, 3, 2, 3};

                uint8_t deal_pos = (dealer + 1) % 4;

                for (auto &a : DEAL_STRATEGY)
                {
                    deck.deal(players[deal_pos]->get_hand(), a);
                    ++deal_pos;
                    deal_pos = deal_pos % 4;
                }

                up_card = deck.draw();
            }

            // update player perceptions after initial card deal
            void update_perceptions_after_deal()
            {
                for (auto& player : players)
                    player->update_perceptions_after_deal(dealer, up_card);
            }

            // determine seat position of the dealer
            uint8_t determine_dealer() const
            {
                static const euchre_card JACK_CLUBS(e_suit::CLUBS, e_rank::JACK);
                static const euchre_card JACK_SPADES(e_suit::SPADES, e_rank::JACK);

                // the deck for determining the dealer
                euchre_deck dealer_deck;
                dealer_deck.init();
                dealer_deck.shuffle();

                // draw cards until a black jack is found
                uint8_t position = 0;
                while (!dealer_deck.empty())
                {
                    euchre_hand h;
                    dealer_deck.deal(h, 1);

                    // if a black jack was found, this position is dealer
                    if (h.contains(JACK_CLUBS) || h.contains(JACK_SPADES))
                        return position;

                    // cycle the position among 4 seats
                    ++position;
                    position = position % 4;
                }

                return 0;
            }

        private:
            // the card that is turned up for trump calling
            euchre_card up_card;

            // the trump suit
            e_suit trump_suit = e_suit::INVALID;

            // the dealer position
            uint8_t dealer = 0;

            // the deck of cards
            euchre_deck deck;

            // the scoreboard
            euchre_scoreboard scoreboard;

            // vector of the 4 players
            std::vector<std::unique_ptr<euchre_player>> players;

        }; // class euchre_game

    } // namespace euchre

} // namespace rda
