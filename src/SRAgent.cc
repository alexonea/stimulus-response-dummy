/*
 *  SRAgent.cc
 *
 *  Copyright (C) 2019 Alexandru N. Onea <alexandru.onea@toporcomputing.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "SRAgent.h"

namespace SRDummy
{
  std::ostream&
  operator<<
  (std::ostream& os, Action a)
  {
    switch (a)
    {
      case GO_NORTH:  return os << "NORTH";
      case GO_EAST:   return os << "EAST";
      case GO_SOUTH:  return os << "SOUTH";
      case GO_WEST:   return os << "WEST";
    }

    return os << "INVALID";
  }

  template <>
  Action
  stimulusResponse
  (const bool (&vFeatures) [8])
  {
    bool bX1 = (vFeatures[1] || vFeatures[2]);
    bool bX2 = (vFeatures[3] || vFeatures[4]);
    bool bX3 = (vFeatures[5] || vFeatures[6]);
    bool bX4 = (vFeatures[7] || vFeatures[0]);

    if (bX1 && !bX2)
      return GO_EAST;

    if (bX2 && !bX3)
      return GO_SOUTH;

    if (bX3 && !bX4)
      return GO_WEST;

    if (bX4 && !bX1)
      return GO_NORTH;

    return GO_NORTH;
  }
}
