#pragma once

//
// euchre_scoreboard.h - The euchre game scoreboard
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>

namespace rda
{
	namespace euchre
	{
		class euchre_scoreboard
		{
		public:
			uint8_t team1_score = 0;
			uint8_t team2_score = 0;

			uint8_t team1_tricks = 0;
			uint8_t team2_tricks = 0;

			// reset the score
			void reset_score()
			{
				team1_score = 0;
				team2_score = 0;

				team1_tricks = 0;
				team2_tricks = 0;
			}

			// reset the hand
			void reset_hand()
			{
				team1_tricks = 0;
				team2_tricks = 0;
			}

			// return true if game is over
			bool is_over() const
			{
				return team1_score >= 10 || team2_score >= 10;
			}

		}; // class scoreboard

	} // namespace euchre

} // namespace rda
