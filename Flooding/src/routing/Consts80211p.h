//
// Copyright (C) 2011 David Eckhoff <eckhoff@cs.fau.de>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#ifndef CONSTANTS_802_11p
#define CONSTANTS_802_11p

#include <stdint.h>

/** @brief Channels as reserved by the FCC
 *
 */
namespace Channels {
enum ChannelNumber {
	CRIT_SOL = 172,
	SCH1 = 174,
	SCH2 = 176,
	CCH = 178,
	SCH3 = 180,
	SCH4 = 182,
	HPPS = 184
};
}

enum t_channel {
	type_CCH=0,
	type_SCH,
};

#endif
