/*
 *  World.cc
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

#include "World.h"

#include <sstream>

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

  World::World
  (std::size_t nRows, std::size_t nCols)
  : m_pImpl{new WorldImpl{nRows, nCols}}
  {}

  std::string
  World::toString
  () const
  {
    std::stringstream ss;

    const std::size_t nSize = m_pImpl->m_nRows * m_pImpl->m_nCols;

    for (std::size_t iPos = 0; iPos <= m_pImpl->m_nCols; ++iPos)
      ss << "#";

    for (std::size_t iPos = 0; iPos < nSize; ++iPos)
    {
      if (iPos % m_pImpl->m_nCols == 0)
        ss << "#\n#";

      ss << m_pImpl->m_vCells[iPos];
    }

    ss << "#\n#";

    for (std::size_t iPos = 0; iPos <= m_pImpl->m_nCols; ++iPos)
      ss << "#";

    ss << "\n";

    return ss.str();
  }
}
