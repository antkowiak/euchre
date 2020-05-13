#pragma once

//
// euchre_utils.h - Utility functions for euchre
//
// Written by Ryan Antkowiak (antkowiak@gmail.com)
//

#include <cstdint>

#include "perception.h"

namespace rda
{
	namespace euchre
	{
		namespace euchre_utils
		{
			// calculate where "other_pos" is sitting, relative to "pos"
			static euchre_seat_position relative_seat_position(const uint8_t pos, const uint8_t other_pos)
			{
				if (other_pos == pos)
					return euchre_seat_position::SELF;
				else if ((pos + 1) % 4 == pos)
					return euchre_seat_position::LEFT;
				else if ((pos + 2) % 4 == pos)
					return euchre_seat_position::ACROSS;
				else if ((pos + 3) % 4 == pos)
					return euchre_seat_position::RIGHT;

				return euchre_seat_position::INVALID;
			}

		} // namespace utils

	} // namespace euchre

} // namespace rda
