/*
 *  Common.h
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

#ifndef SRC_COMMON_H
#define SRC_COMMON_H 1

#include <ostream>
#include <utility>

namespace SRDummy
{
  enum CellType
  {
    EMPTY = 0,
    WALL,
  };

  enum Direction
  {
    SOUTH = 0,
    SOUTHWEST,
    WEST,
    NORTHWEST,
    NORTH,
    NORTHEAST,
    EAST,
    SOUTHEAST,
  };

  extern char toText(CellType eType);
  extern std::ostream& operator<<(std::ostream& os, CellType eType);

  using Coordinate = std::pair<std::size_t, std::size_t>;
  extern Coordinate getCoordinate(const Coordinate& current, Direction dir);
}

#endif
