/*
 *  WorldImpl.h
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

#ifndef SRC_WORLDIMPL_H
#define SRC_WORLDIMPL_H 1

#include <vector>

#include "Common.h"
#include "World.h"

namespace SRDummy
{
  class World::WorldImpl
  {
  public:
    WorldImpl(std::size_t nRows, std::size_t nCols);

    WorldImpl(const WorldImpl& other);
    WorldImpl& operator=(const WorldImpl& other);

    WorldImpl(WorldImpl&& other) noexcept;
    WorldImpl& operator=(WorldImpl&& other) noexcept;

    void swap(WorldImpl& other) noexcept;

    bool isEmpty(const Coordinate& c);
    bool isValidCoordinate(const Coordinate& c);
    std::size_t toPos(const Coordinate& c);
    std::size_t toPos(std::size_t iX, std::size_t iY);
  private:
    std::size_t m_nRows;
    std::size_t m_nCols;

    using CellRepr = std::vector<CellType>;
    CellRepr    m_vCells;

    friend class World;
  };
}

#endif
