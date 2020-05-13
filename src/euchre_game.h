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
#include "euchre_constants.h"
#include "euchre_deck.h"
#include "euchre_hand.h"
#include "euchre_player_computer.h"
#include "euchre_player_human.h"
#include "euchre_scoreboard.h"
#include "euchre_trump_decision.h"

namespace rda
{
    namespace euchre
    {
        // the euchre game
        class euchre_game
        {
        private:
            // the card that is turned up for trump calling
            euchre_card up_card;

            // the trump suit
            e_suit suit_called_trump = e_suit::INVALID;

            // true if this hand is being played alone
            bool loner = false;

            // index of the player who called trump
            uint8_t trump_caller_index = euchre_constants::INVALID_INDEX;

            // the dealer position
            uint8_t dealer_index = euchre_constants::INVALID_INDEX;

            // the deck of cards
            euchre_deck deck;

            // the scoreboard
            euchre_scoreboard scoreboard;

            // vector of the players
            std::vector<std::unique_ptr<euchre_player>> players;

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
                suit_called_trump = e_suit::INVALID;
                loner = false;
                trump_caller_index = euchre_constants::INVALID_INDEX;

                scoreboard.reset_score();

                for (auto &player : players)
                    player->reset();
            }

            // initialize a euchre hand
            void init_hand()
            {
                up_card = euchre_card();
                suit_called_trump = e_suit::INVALID;
                loner = false;
                trump_caller_index = euchre_constants::INVALID_INDEX;

                scoreboard.reset_hand();

                for (auto &player : players)
                    player->reset();
            }

            // return string representation of this euchre game
            std::string to_string() const
            {
                std::stringstream ss;

                for (auto &player : players)
                    ss << "player: " << std::endl
                       << player->to_string();

                ss << "up card: " << up_card.to_string() << std::endl;

                return ss.str();
            }

            // play the euchre game
            void play_game()
            {
                dealer_index = determine_dealer();

                while (!scoreboard.is_over())
                {
                    play_hand();

                    ++dealer_index;
                    dealer_index = dealer_index % euchre_constants::NUM_PLAYERS;
                }
            }

            // determine seat position of the dealer
            uint8_t determine_dealer() const
            {
                // the deck for determining the dealer
                euchre_deck dealer_deck;
                dealer_deck.init();
                dealer_deck.shuffle();

                uint8_t position = 0;

                // draw cards until a black jack is found
                while (!dealer_deck.empty())
                {
                    // if a black jack was drawn, this position is dealer
                    if (euchre_utils::is_black_jack(dealer_deck.draw()))
                        return position;

                    // cycle the position among player seats
                    ++position;
                    position = position % euchre_constants::NUM_PLAYERS;
                }

                return 0;
            }

            void play_hand()
            {
                init_hand();
                shuffle_deck();
                deal_hand();
                offer_up_card_trump_to_players();
                offer_trump_to_players();

                // TODO - continue playing hand

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

                uint8_t deal_pos = (dealer_index + 1) % euchre_constants::NUM_PLAYERS;

                for (auto &a : DEAL_STRATEGY)
                {
                    deck.deal(players[deal_pos]->get_hand(), a);
                    ++deal_pos;
                    deal_pos = deal_pos % euchre_constants::NUM_PLAYERS;
                }

                up_card = deck.draw();

                update_perceptions_after_deal();
            }

            // update player perceptions after initial card deal
            void update_perceptions_after_deal()
            {
                for (auto &player : players)
                    player->update_perceptions_after_deal(dealer_index, up_card);
            }

            // let players choose if they want the up-card to be trump
            void offer_up_card_trump_to_players()
            {
                for (uint8_t index = 0; index < euchre_constants::NUM_PLAYERS; ++index)
                {
                    const uint8_t offer_index = (dealer_index + 1 + index) % euchre_constants::NUM_PLAYERS;
                    const e_trump_decision decision = players[offer_index]->offer_up_card_trump(up_card);

                    update_perceptions_after_up_card_offer(offer_index, decision);

                    if (is_ordering_up(decision))
                    {
                        trump_caller_index = offer_index;
                        loner = is_loner(decision);
                        suit_called_trump = up_card.suit();
                    }
                }

                if (suit_called_trump != e_suit::INVALID)
                    players[dealer_index]->pick_up_card(up_card);
            }

            // update player perceptions after a player was offered to order up trump
            void update_perceptions_after_up_card_offer(const uint8_t seat_index, const e_trump_decision decision)
            {
                for (auto &player : players)
                    player->update_perceptions_after_up_card_offer(seat_index, decision);
            }

            // let players choose to call trump, if it hasn't been called already
            void offer_trump_to_players()
            {
                if (suit_called_trump == e_suit::INVALID)
                {
                    for (uint8_t index = 0; index < euchre_constants::NUM_PLAYERS; ++index)
                    {
                        const uint8_t offer_index = (dealer_index + 1 + index) % euchre_constants::NUM_PLAYERS;
                        const e_trump_decision decision = players[offer_index]->offer_trump();

                        update_perceptions_after_trump_offer(offer_index, decision);

                        if (is_calling_suit(decision))
                        {
                            suit_called_trump = decision_to_suit(decision);
                            loner = is_loner(decision);
                            break;
                        }
                    }
                }
            }

            // update player perceptions after a player was offered to call any trump
            void update_perceptions_after_trump_offer(const uint8_t seat_index, const e_trump_decision decision)
            {
                for (auto &player : players)
                    player->update_perceptions_after_trump_offer(seat_index, decision);
            }

        }; // class euchre_game

    } // namespace euchre

} // namespace rda
