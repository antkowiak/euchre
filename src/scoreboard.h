#pragma once

//
// scoreboard.h - The euchre game scoreboard
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>

namespace rda
{
	namespace euchre
	{
		class scoreboard
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

		}; // class scoreboard

	} // namespace euchre

} // namespace rda
