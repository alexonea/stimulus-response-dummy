/*
 *  Common.cc
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

#include "Common.h"

namespace SRDummy
{
  char
  toText
  (CellType eType)
  {
    switch (eType)
    {
      case EMPTY: return ' ';
      case WALL: return '#';
      default: return '?';
    }
  }

  std::ostream&
  operator<<
  (std::ostream& os, CellType eType)
  {
    return os << toText(eType);
  }

  Coordinate
  getCoordinate
  (const Coordinate& current, Direction dir)
  {
    Coordinate next = current;
    switch (dir)
    {
      case SOUTH:     next.first++;                 break;
      case SOUTHEAST: next.first++; next.second++;  break;
      case SOUTHWEST: next.first++; next.second--;  break;
      case NORTH:     next.first--;                 break;
      case NORTHEAST: next.first--; next.second++;  break;
      case NORTHWEST: next.first--; next.second--;  break;
      case EAST:                    next.second++;  break;
      case WEST:                    next.second--;  break;
    }

    return next;
  }
}
